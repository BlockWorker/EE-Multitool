
#include "FT8.h"
#include "FT8_commands.h"

/* FT8xx Memory Commands - used with FT8_memWritexx and FT8_memReadxx */
#define MEM_WRITE	0x80	/* FT8xx Host Memory Write */
#define MEM_READ	0x00	/* FT8xx Host Memory Read */

volatile uint16_t cmdOffset = 0x0000; /* used to navigate command ring buffer */

uint8_t cmdQueue[4096] = {0};
uint16_t cmdQueueLength = 0x0000;

#define cmdQueueSpace (4096 - cmdQueueLength)

typedef enum uint8_t {
    CALLBACK_VOID = 0,
    CALLBACK_INT8,
    CALLBACK_INT16,
    CALLBACK_INT32
} CALLBACK_TYPE;

typedef struct {
    CALLBACK_TYPE type;
    uint8_t* sendBuf;
    uint8_t* data;
    void* callback;
    void* context;
} SPI_CALLBACK_DATA;

typedef struct {
    VOID_CALLBACK callback;
    void* context;
} VOIDCB_DATA;

void queue8(uint8_t data) {
    cmdQueue[cmdQueueLength++] = data;
}

void queue16(uint16_t data) {
    cmdQueue[cmdQueueLength++] = (uint8_t) data;
    cmdQueue[cmdQueueLength++] = (uint8_t) (data >> 8);
}

void queue32(uint32_t data) {
    cmdQueue[cmdQueueLength++] = (uint8_t) data;
    cmdQueue[cmdQueueLength++] = (uint8_t) (data >> 8);
    cmdQueue[cmdQueueLength++] = (uint8_t) (data >> 16);
    cmdQueue[cmdQueueLength++] = (uint8_t) (data >> 24);
}

void alignQueue() {
    while (cmdQueueLength % 4 != 0) cmdQueue[cmdQueueLength++] = 0;
}

void SPIMemFreeHandler(DRV_SPI_BUFFER_EVENT event, DRV_SPI_BUFFER_HANDLE bufferHandle, void* context) {
    free(context);
}

void SPIEventHandler(DRV_SPI_BUFFER_EVENT event, DRV_SPI_BUFFER_HANDLE bufferHandle, void* context) {
    SPI_CALLBACK_DATA* cb;
    uint16_t d;
    uint32_t e;
    switch (event) {
        case DRV_SPI_BUFFER_EVENT_COMPLETE:
            cb = (SPI_CALLBACK_DATA*) context;
            free(cb->sendBuf);
            switch (cb->type) {
                case CALLBACK_VOID:
                    ((VOID_CALLBACK) cb->callback)(cb->context);
                    free(cb);
                    break;
                case CALLBACK_INT8:
                    ((INT8_CALLBACK) cb->callback)(cb->data[4], cb->context);
                    free(cb->data);
                    free(cb);
                    break;
                case CALLBACK_INT16:
                    d = cb->data[4];
                    d |= (cb->data[5] << 8);
                    ((INT16_CALLBACK) cb->callback)(d, cb->context);
                    free(cb->data);
                    free(cb);
                    break;
                case CALLBACK_INT32:
                    e = cb->data[4];
                    e |= (cb->data[5] << 8);
                    e |= (cb->data[6] << 16);
                    e |= (cb->data[7] << 24);
                    ((INT32_CALLBACK) cb->callback)(e, cb->context);
                    free(cb->data);
                    free(cb);
                    break;
                default:
                    break;
            }
            break;
        case DRV_SPI_BUFFER_EVENT_ERROR:
            SYS_DEBUG_PRINT(SYS_ERROR_FATAL, "Display SPI: Transfer Error!");
            break;
        default:
            break;
    }
}

void SPITransferStartCallback(DRV_SPI_BUFFER_EVENT event, DRV_SPI_BUFFER_HANDLE bufferHandle, void* context) {
    PLIB_SPI_SlaveSelectEnable(SPI_ID_4);
}

void SPITransferEndCallback(DRV_SPI_BUFFER_EVENT event, DRV_SPI_BUFFER_HANDLE bufferHandle, void* context) {
    PLIB_SPI_SlaveSelectDisable(SPI_ID_4);
    PLIB_SPI_BufferClear(SPI_ID_4);
}

const DRV_SPI_CLIENT_DATA lsCfg = {
    .baudRate = 5000000,
    .operationStarting = SPITransferStartCallback,
    .operationEnded = SPITransferEndCallback
};

const DRV_SPI_CLIENT_DATA hsCfg = {
    .baudRate = 19800000,
    .operationStarting = SPITransferStartCallback,
    .operationEnded = SPITransferEndCallback
};

int FT8_cmdWrite(uint8_t cmd, uint8_t arg) {
    uint8_t* buf = malloc(3);
    if (buf == NULL) return -2;
    buf[0] = cmd;
    buf[1] = arg;
    buf[2] = 0x00;
    DRV_SPI_BUFFER_HANDLE handle;
    DRV_SPI1_BufferAddWrite2(buf, 3, SPIMemFreeHandler, buf, &handle);
    return handle == DRV_SPI_BUFFER_HANDLE_INVALID ? -1 : 0;
}

int FT8_cmdWriteC(uint8_t cmd, uint8_t arg, VOID_CALLBACK cb, void* context) {
    uint8_t* buf = malloc(3);
    if (buf == NULL) return -2;
    buf[0] = cmd;
    buf[1] = arg;
    buf[2] = 0x00;
    DRV_SPI_BUFFER_HANDLE handle;
    SPI_CALLBACK_DATA* cbd = malloc(sizeof (SPI_CALLBACK_DATA));
    if (cbd == NULL) return -2;
    cbd->type = CALLBACK_VOID;
    cbd->sendBuf = buf;
    cbd->data = NULL;
    cbd->callback = cb;
    cbd->context = context;
    DRV_SPI1_BufferAddWrite2(buf, 3, SPIEventHandler, cbd, &handle);
    return handle == DRV_SPI_BUFFER_HANDLE_INVALID ? -1 : 0;
}

int FT8_memSendAddrRaw(uint32_t ftAddress, bool read) {
    uint8_t* buf = malloc(3);
    if (buf == NULL) return -2;
    buf[0] = (uint8_t) (ftAddress >> 16) | (read ? MEM_READ : MEM_WRITE);
    buf[1] = (uint8_t) (ftAddress >> 8);
    buf[2] = (uint8_t) ftAddress;
    DRV_SPI_BUFFER_HANDLE handle;
    DRV_SPI1_BufferAddWrite2(buf, 3, SPIMemFreeHandler, buf, &handle);
    return handle == DRV_SPI_BUFFER_HANDLE_INVALID ? -1 : 0;
}

int FT8_memRead8(uint32_t ftAddress, INT8_CALLBACK cb, void* context) {
    uint8_t* buf = malloc(3);
    if (buf == NULL) return -2;
    buf[0] = (uint8_t) (ftAddress >> 16) | MEM_READ;
    buf[1] = (uint8_t) (ftAddress >> 8);
    buf[2] = (uint8_t) ftAddress;
    DRV_SPI_BUFFER_HANDLE handle;
    SPI_CALLBACK_DATA* cbd = malloc(sizeof (SPI_CALLBACK_DATA));
    if (cbd == NULL) return -2;
    cbd->type = CALLBACK_INT8;
    cbd->sendBuf = buf;
    cbd->data = malloc(5);
    if (cbd->data == NULL) return -2;
    cbd->callback = cb;
    cbd->context = context;
    DRV_SPI1_BufferAddWriteRead2(buf, 3, cbd->data, 5, SPIEventHandler, cbd, &handle);
    return handle == DRV_SPI_BUFFER_HANDLE_INVALID ? -1 : 0;
}

int FT8_memRead16(uint32_t ftAddress, INT16_CALLBACK cb, void* context) {
    uint8_t* buf = malloc(3);
    if (buf == NULL) return -2;
    buf[0] = (uint8_t) (ftAddress >> 16) | MEM_READ;
    buf[1] = (uint8_t) (ftAddress >> 8);
    buf[2] = (uint8_t) ftAddress;
    DRV_SPI_BUFFER_HANDLE handle;
    SPI_CALLBACK_DATA* cbd = malloc(sizeof (SPI_CALLBACK_DATA));
    if (cbd == NULL) return -2;
    cbd->type = CALLBACK_INT16;
    cbd->sendBuf = buf;
    cbd->data = malloc(6);
    if (cbd->data == NULL) return -2;
    cbd->callback = cb;
    cbd->context = context;
    DRV_SPI1_BufferAddWriteRead2(buf, 3, cbd->data, 6, SPIEventHandler, cbd, &handle);
    return handle == DRV_SPI_BUFFER_HANDLE_INVALID ? -1 : 0;
}

int FT8_memRead32(uint32_t ftAddress, INT32_CALLBACK cb, void* context) {
    uint8_t* buf = malloc(3);
    if (buf == NULL) return -2;
    buf[0] = (uint8_t) (ftAddress >> 16) | MEM_READ;
    buf[1] = (uint8_t) (ftAddress >> 8);
    buf[2] = (uint8_t) ftAddress;
    DRV_SPI_BUFFER_HANDLE handle;
    SPI_CALLBACK_DATA* cbd = malloc(sizeof (SPI_CALLBACK_DATA));
    if (cbd == NULL) return -2;
    cbd->type = CALLBACK_INT32;
    cbd->sendBuf = buf;
    cbd->data = malloc(8);
    if (cbd->data == NULL) return -2;
    cbd->callback = cb;
    cbd->context = context;
    DRV_SPI1_BufferAddWriteRead2(buf, 3, cbd->data, 8, SPIEventHandler, cbd, &handle);
    return handle == DRV_SPI_BUFFER_HANDLE_INVALID ? -1 : 0;
}

int FT8_memReadBuffer(uint32_t ftAddress, uint8_t* buffer, uint32_t offset, uint32_t length, VOID_CALLBACK cb, void* context) {
    uint8_t* buf = malloc(3);
    if (buf == NULL) return -2;
    buf[0] = (uint8_t) (ftAddress >> 16) | MEM_READ;
    buf[1] = (uint8_t) (ftAddress >> 8);
    buf[2] = (uint8_t) ftAddress;
    DRV_SPI_BUFFER_HANDLE handle;
    SPI_CALLBACK_DATA* cbd = malloc(sizeof (SPI_CALLBACK_DATA));
    if (cbd == NULL) return -2;
    cbd->type = CALLBACK_VOID;
    cbd->sendBuf = buf;
    cbd->data = NULL;
    cbd->callback = cb;
    cbd->context = context;
    DRV_SPI1_BufferAddWriteRead2(buf, 3, buffer + offset, length, SPIEventHandler, cbd, &handle);
    return handle == DRV_SPI_BUFFER_HANDLE_INVALID ? -1 : 0;
}

int FT8_memWrite8(uint32_t ftAddress, uint8_t ftData8) {
    uint8_t* buf = malloc(4);
    if (buf == NULL) return -2;
    buf[0] = (uint8_t) (ftAddress >> 16) | MEM_WRITE;
    buf[1] = (uint8_t) (ftAddress >> 8);
    buf[2] = (uint8_t) ftAddress;
    buf[3] = ftData8;
    DRV_SPI_BUFFER_HANDLE handle;
    DRV_SPI1_BufferAddWrite2(buf, 4, SPIMemFreeHandler, buf, &handle);
    return handle == DRV_SPI_BUFFER_HANDLE_INVALID ? -1 : 0;
}

int FT8_memWrite8C(uint32_t ftAddress, uint8_t ftData8, VOID_CALLBACK cb, void* context) {
    uint8_t* buf = malloc(4);
    if (buf == NULL) return -2;
    buf[0] = (uint8_t) (ftAddress >> 16) | MEM_WRITE;
    buf[1] = (uint8_t) (ftAddress >> 8);
    buf[2] = (uint8_t) ftAddress;
    buf[3] = ftData8;
    DRV_SPI_BUFFER_HANDLE handle;
    SPI_CALLBACK_DATA* cbd = malloc(sizeof (SPI_CALLBACK_DATA));
    if (cbd == NULL) return -2;
    cbd->type = CALLBACK_VOID;
    cbd->sendBuf = buf;
    cbd->data = NULL;
    cbd->callback = cb;
    cbd->context = context;
    DRV_SPI1_BufferAddWrite2(buf, 4, SPIEventHandler, cbd, &handle);
    return handle == DRV_SPI_BUFFER_HANDLE_INVALID ? -1 : 0;
}

int FT8_memWrite8Raw(uint8_t ftData8) {
    uint8_t* buf = malloc(1);
    if (buf == NULL) return -2;
    buf[0] = ftData8;
    DRV_SPI_BUFFER_HANDLE handle;
    DRV_SPI1_BufferAddWrite2(buf, 1, SPIMemFreeHandler, buf, &handle);
    return handle == DRV_SPI_BUFFER_HANDLE_INVALID ? -1 : 0;
}

int FT8_memWrite8RawC(uint8_t ftData8, VOID_CALLBACK cb, void* context) {
    uint8_t* buf = malloc(1);
    if (buf == NULL) return -2;
    buf[0] = ftData8;
    DRV_SPI_BUFFER_HANDLE handle;
    SPI_CALLBACK_DATA* cbd = malloc(sizeof (SPI_CALLBACK_DATA));
    if (cbd == NULL) return -2;
    cbd->type = CALLBACK_VOID;
    cbd->sendBuf = buf;
    cbd->data = NULL;
    cbd->callback = cb;
    cbd->context = context;
    DRV_SPI1_BufferAddWrite2(buf, 1, SPIEventHandler, cbd, &handle);
    return handle == DRV_SPI_BUFFER_HANDLE_INVALID ? -1 : 0;
}

int FT8_memWrite16(uint32_t ftAddress, uint16_t ftData16) {
    uint8_t* buf = malloc(5);
    if (buf == NULL) return -2;
    buf[0] = (uint8_t) (ftAddress >> 16) | MEM_WRITE;
    buf[1] = (uint8_t) (ftAddress >> 8);
    buf[2] = (uint8_t) ftAddress;
    buf[3] = (uint8_t) ftData16;
    buf[4] = (uint8_t) (ftData16 >> 8);
    DRV_SPI_BUFFER_HANDLE handle;
    DRV_SPI1_BufferAddWrite2(buf, 5, SPIMemFreeHandler, buf, &handle);
    return handle == DRV_SPI_BUFFER_HANDLE_INVALID ? -1 : 0;
}

int FT8_memWrite16C(uint32_t ftAddress, uint16_t ftData16, VOID_CALLBACK cb, void* context) {
    uint8_t* buf = malloc(5);
    if (buf == NULL) return -2;
    buf[0] = (uint8_t) (ftAddress >> 16) | MEM_WRITE;
    buf[1] = (uint8_t) (ftAddress >> 8);
    buf[2] = (uint8_t) ftAddress;
    buf[3] = (uint8_t) ftData16;
    buf[4] = (uint8_t) (ftData16 >> 8);
    DRV_SPI_BUFFER_HANDLE handle;
    SPI_CALLBACK_DATA* cbd = malloc(sizeof (SPI_CALLBACK_DATA));
    if (cbd == NULL) return -2;
    cbd->type = CALLBACK_VOID;
    cbd->sendBuf = buf;
    cbd->data = NULL;
    cbd->callback = cb;
    cbd->context = context;
    DRV_SPI1_BufferAddWrite2(buf, 5, SPIEventHandler, cbd, &handle);
    return handle == DRV_SPI_BUFFER_HANDLE_INVALID ? -1 : 0;
}

int FT8_memWrite16Raw(uint16_t ftData16) {
    uint8_t* buf = malloc(2);
    if (buf == NULL) return -2;
    buf[0] = (uint8_t) ftData16;
    buf[1] = (uint8_t) (ftData16 >> 8);
    DRV_SPI_BUFFER_HANDLE handle;
    DRV_SPI1_BufferAddWrite2(buf, 2, SPIMemFreeHandler, buf, &handle);
    return handle == DRV_SPI_BUFFER_HANDLE_INVALID ? -1 : 0;
}

int FT8_memWrite16RawC(uint16_t ftData16, VOID_CALLBACK cb, void* context) {
    uint8_t* buf = malloc(2);
    if (buf == NULL) return -2;
    buf[0] = (uint8_t) ftData16;
    buf[1] = (uint8_t) (ftData16 >> 8);
    DRV_SPI_BUFFER_HANDLE handle;
    SPI_CALLBACK_DATA* cbd = malloc(sizeof (SPI_CALLBACK_DATA));
    if (cbd == NULL) return -2;
    cbd->type = CALLBACK_VOID;
    cbd->sendBuf = buf;
    cbd->data = NULL;
    cbd->callback = cb;
    cbd->context = context;
    DRV_SPI1_BufferAddWrite2(buf, 2, SPIEventHandler, cbd, &handle);
    return handle == DRV_SPI_BUFFER_HANDLE_INVALID ? -1 : 0;
}

int FT8_memWrite32(uint32_t ftAddress, uint32_t ftData32) {
    uint8_t* buf = malloc(7);
    if (buf == NULL) return -2;
    buf[0] = (uint8_t) (ftAddress >> 16) | MEM_WRITE;
    buf[1] = (uint8_t) (ftAddress >> 8);
    buf[2] = (uint8_t) ftAddress;
    buf[3] = (uint8_t) ftData32;
    buf[4] = (uint8_t) (ftData32 >> 8);
    buf[5] = (uint8_t) (ftData32 >> 16);
    buf[6] = (uint8_t) (ftData32 >> 24);
    DRV_SPI_BUFFER_HANDLE handle;
    DRV_SPI1_BufferAddWrite2(buf, 7, SPIMemFreeHandler, buf, &handle);
    return handle == DRV_SPI_BUFFER_HANDLE_INVALID ? -1 : 0;
}

int FT8_memWrite32C(uint32_t ftAddress, uint32_t ftData32, VOID_CALLBACK cb, void* context) {
    uint8_t* buf = malloc(7);
    if (buf == NULL) return -2;
    buf[0] = (uint8_t) (ftAddress >> 16) | MEM_WRITE;
    buf[1] = (uint8_t) (ftAddress >> 8);
    buf[2] = (uint8_t) ftAddress;
    buf[3] = (uint8_t) ftData32;
    buf[4] = (uint8_t) (ftData32 >> 8);
    buf[5] = (uint8_t) (ftData32 >> 16);
    buf[6] = (uint8_t) (ftData32 >> 24);
    DRV_SPI_BUFFER_HANDLE handle;
    SPI_CALLBACK_DATA* cbd = malloc(sizeof (SPI_CALLBACK_DATA));
    if (cbd == NULL) return -2;
    cbd->type = CALLBACK_VOID;
    cbd->sendBuf = buf;
    cbd->data = NULL;
    cbd->callback = cb;
    cbd->context = context;
    DRV_SPI1_BufferAddWrite2(buf, 7, SPIEventHandler, cbd, &handle);
    return handle == DRV_SPI_BUFFER_HANDLE_INVALID ? -1 : 0;
}

int FT8_memWrite32Raw(uint32_t ftData32) {
    uint8_t* buf = malloc(4);
    if (buf == NULL) return -2;
    buf[0] = (uint8_t) ftData32;
    buf[1] = (uint8_t) (ftData32 >> 8);
    buf[2] = (uint8_t) (ftData32 >> 16);
    buf[3] = (uint8_t) (ftData32 >> 24);
    DRV_SPI_BUFFER_HANDLE handle;
    DRV_SPI1_BufferAddWrite2(buf, 4, SPIMemFreeHandler, buf, &handle);
    return handle == DRV_SPI_BUFFER_HANDLE_INVALID ? -1 : 0;
}

int FT8_memWrite32RawC(uint32_t ftData32, VOID_CALLBACK cb, void* context) {
    uint8_t* buf = malloc(4);
    if (buf == NULL) return -2;
    buf[0] = (uint8_t) ftData32;
    buf[1] = (uint8_t) (ftData32 >> 8);
    buf[2] = (uint8_t) (ftData32 >> 16);
    buf[3] = (uint8_t) (ftData32 >> 24);
    DRV_SPI_BUFFER_HANDLE handle;
    SPI_CALLBACK_DATA* cbd = malloc(sizeof (SPI_CALLBACK_DATA));
    if (cbd == NULL) return -2;
    cbd->type = CALLBACK_VOID;
    cbd->sendBuf = buf;
    cbd->data = NULL;
    cbd->callback = cb;
    cbd->context = context;
    DRV_SPI1_BufferAddWrite2(buf, 4, SPIEventHandler, cbd, &handle);
    return handle == DRV_SPI_BUFFER_HANDLE_INVALID ? -1 : 0;
}

int FT8_memWriteBuffer(uint32_t ftAddress, uint8_t* buffer, uint32_t offset, uint32_t length) {
    uint8_t* buf = malloc(length + 3);
    if (buf == NULL) return -2;
    buf[0] = (uint8_t) (ftAddress >> 16) | MEM_WRITE;
    buf[1] = (uint8_t) (ftAddress >> 8);
    buf[2] = (uint8_t) ftAddress;
    memcpy(buf + 3, buffer + offset, length);
    DRV_SPI_BUFFER_HANDLE handle;
    DRV_SPI1_BufferAddWrite2(buf, length + 3, SPIMemFreeHandler, buf, &handle);
    return handle == DRV_SPI_BUFFER_HANDLE_INVALID ? -1 : 0;
}

int FT8_memWriteBufferC(uint32_t ftAddress, uint8_t* buffer, uint32_t offset, uint32_t length, VOID_CALLBACK cb, void* context) {
    uint8_t* buf = malloc(length + 3);
    if (buf == NULL) return -2;
    buf[0] = (uint8_t) (ftAddress >> 16) | MEM_WRITE;
    buf[1] = (uint8_t) (ftAddress >> 8);
    buf[2] = (uint8_t) ftAddress;
    memcpy(buf + 3, buffer + offset, length);
    DRV_SPI_BUFFER_HANDLE handle;
    SPI_CALLBACK_DATA* cbd = malloc(sizeof (SPI_CALLBACK_DATA));
    if (cbd == NULL) return -2;
    cbd->type = CALLBACK_VOID;
    cbd->sendBuf = buf;
    cbd->data = NULL;
    cbd->callback = cb;
    cbd->context = context;
    DRV_SPI1_BufferAddWrite2(buf, length + 3, SPIEventHandler, cbd, &handle);
    return handle == DRV_SPI_BUFFER_HANDLE_INVALID ? -1 : 0;
}

int FT8_memWriteBufferRaw(uint8_t* buffer, uint32_t offset, uint32_t length) {
    uint8_t* buf = malloc(length);
    if (buf == NULL) return -2;
    memcpy(buf, buffer + offset, length);
    DRV_SPI_BUFFER_HANDLE handle;
    DRV_SPI1_BufferAddWrite2(buf, length, SPIMemFreeHandler, buf, &handle);
    return handle == DRV_SPI_BUFFER_HANDLE_INVALID ? -1 : 0;
}

int FT8_memWriteBufferRawC(uint8_t* buffer, uint32_t offset, uint32_t length, VOID_CALLBACK cb, void* context) {
    uint8_t* buf = malloc(length);
    if (buf == NULL) return -2;
    memcpy(buf, buffer + offset, length);
    DRV_SPI_BUFFER_HANDLE handle;
    SPI_CALLBACK_DATA* cbd = malloc(sizeof (SPI_CALLBACK_DATA));
    if (cbd == NULL) return -2;
    cbd->type = CALLBACK_VOID;
    cbd->sendBuf = buf;
    cbd->data = NULL;
    cbd->callback = cb;
    cbd->context = context;
    DRV_SPI1_BufferAddWrite2(buf, length, SPIEventHandler, cbd, &handle);
    return handle == DRV_SPI_BUFFER_HANDLE_INVALID ? -1 : 0;
}


/*int FT8_memWrite_flash_buffer(uint32_t ftAddress, const uint8_t *data, uint16_t len)
{
    uint16_t count;

    FT8_cs_set();
    spi_transmit((uint8_t)(ftAddress >> 16) | MEM_WRITE);
    spi_transmit((uint8_t)(ftAddress >> 8));
    spi_transmit((uint8_t)(ftAddress));

    len = (len + 3)&(~3);

    for(count=0;count<len;count++)
    {
        spi_transmit(fetch_flash_byte(data+count));
    }

    FT8_cs_clear();
}*/



void busyReadCallback(uint16_t data, void* context); //predef

void busyTimerCallback(uintptr_t context, uint32_t currTick) {
    FT8_memRead16(REG_CMD_READ, busyReadCallback, (void*) context);
}

void busyReadCallback(uint16_t data, void* context) {
    if (data == 0xFFF) {
        FT8_memWrite8(REG_CPURESET, 1);
        FT8_memWrite16(REG_CMD_READ, 0);
        FT8_memWrite16(REG_CMD_WRITE, 0);
        cmdOffset = 0;
        FT8_memWrite8(REG_CPURESET, 0);
        SYS_TMR_CallbackSingle(10, (uintptr_t) context, busyTimerCallback);
    } else if (data == cmdOffset) {
        VOIDCB_DATA* cb = context;
        cb->callback(cb->context);
    } else SYS_TMR_CallbackSingle(5, (uintptr_t) context, busyTimerCallback);
}

int FT8_busy(VOID_CALLBACK cb, void* context) {
    VOIDCB_DATA* cbd = malloc(sizeof (VOIDCB_DATA));
    if (cbd == NULL) return -2;
    cbd->callback = cb;
    cbd->context = context;
    return FT8_memRead16(REG_CMD_READ, busyReadCallback, cbd); /* read the graphics processor read pointer */
}

int FT8_get_touch_tag(INT32_CALLBACK cb, void* context) {
    return FT8_memRead32(REG_TOUCH_TAG, cb, context);
}

void FT8_inc_cmdoffset(uint16_t increment) {
    cmdOffset += increment;
    cmdOffset &= 0x0fff;
}

/* order the command co-processor to start processing its FIFO queue and call cb on completion */
int FT8_cmd_execute(VOID_CALLBACK cb, void* context) {
    if (cmdQueueLength == 0) return 0;
    int r = FT8_memWriteBuffer(FT8_RAM_CMD + cmdOffset, cmdQueue, 0, cmdQueueLength);
    memset(cmdQueue, 0, cmdQueueLength);
    FT8_inc_cmdoffset(cmdQueueLength);
    cmdQueueLength = 0;
    r += FT8_memWrite16(REG_CMD_WRITE, cmdOffset);
    if (cb != NULL) r += FT8_busy(cb, context);
    return r;
}

/* order the command co-processor to start processing its FIFO queue */
int FT8_cmd_start() {
    return FT8_cmd_execute(NULL, NULL);
}

void cmdOffsetReadCallback(uint16_t data, void* context) {
    cmdOffset = data;
    if (context != NULL) {
        VOIDCB_DATA* cb = context;
        cb->callback(cb->context);
    }
}

int FT8_get_cmdoffset(VOID_CALLBACK cb, void* context) {
    VOIDCB_DATA* cbd;
    if (cb == NULL) cbd = NULL;
    else {
        cbd = malloc(sizeof (VOIDCB_DATA));
        if (cbd == NULL) return -2;
        cbd->callback = cb;
        cbd->context = context;
    }
    if (FT8_memRead16(REG_CMD_WRITE, cmdOffsetReadCallback, cbd) < 0) {
        cmdOffset = 0;
        if (cb != NULL) cb(context);
    }
    return 0;
}

/* make current value of cmdOffset available while limiting access to that var to the FT8_commands module */
uint16_t FT8_report_cmdoffset() {
    return cmdOffset;
}

/* Begin a co-processor command */
void FT8_start_cmd(uint32_t command) {
    queue32(command);
}

/* Write a string to co-processor memory in context of a command */
void queue_string(const char *text) {
    int i = 0;
    do {
        queue8(text[i]);
    } while (text[i++] != 0);
    alignQueue();
}

/* commands to draw graphics objects: */

int FT8_cmd_text(int16_t x0, int16_t y0, int16_t font, uint16_t options, const char* text) {
    if (cmdQueueSpace < strlen(text) + 16) return -1;
    FT8_start_cmd(CMD_TEXT);
    queue16(x0);
    queue16(y0);
    queue16(font);
    queue16(options);
    queue_string(text);
    return 0;
}

int FT8_cmd_button(int16_t x0, int16_t y0, int16_t w0, int16_t h0, int16_t font, uint16_t options, const char* text) {
    if (cmdQueueSpace < strlen(text) + 20) return -1;
    FT8_start_cmd(CMD_BUTTON);
    queue16(x0);
    queue16(y0);
    queue16(w0);
    queue16(h0);
    queue16(font);
    queue16(options);
    queue_string(text);
    return 0;
}

/* draw a clock */
int FT8_cmd_clock(int16_t x0, int16_t y0, int16_t r0, uint16_t options, uint16_t hours, uint16_t minutes, uint16_t seconds, uint16_t millisecs) {
    if (cmdQueueSpace < 20) return -1;
    FT8_start_cmd(CMD_CLOCK);
    queue16(x0);
    queue16(y0);
    queue16(r0);
    queue16(options);
    queue16(hours);
    queue16(minutes);
    queue16(seconds);
    queue16(millisecs);
    return 0;
}

int FT8_cmd_bgcolor(uint32_t color) {
    if (cmdQueueSpace < 8) return -1;
    FT8_start_cmd(CMD_BGCOLOR);
    queue32(color & 0xffffff);
    return 0;
}

int FT8_cmd_fgcolor(uint32_t color) {
    if (cmdQueueSpace < 8) return -1;
    FT8_start_cmd(CMD_FGCOLOR);
    queue32(color & 0xffffff);
    return 0;
}

int FT8_cmd_gradcolor(uint32_t color) {
    if (cmdQueueSpace < 8) return -1;
    FT8_start_cmd(CMD_GRADCOLOR);
    queue32(color & 0xffffff);
    return 0;
}

int FT8_cmd_gauge(int16_t x0, int16_t y0, int16_t r0, uint16_t options, uint16_t major, uint16_t minor, uint16_t val, uint16_t range) {
    if (cmdQueueSpace < 20) return -1;
    FT8_start_cmd(CMD_GAUGE);
    queue16(x0);
    queue16(y0);
    queue16(r0);
    queue16(options);
    queue16(major);
    queue16(minor);
    queue16(val);
    queue16(range);
    return 0;
}

int FT8_cmd_gradient(int16_t x0, int16_t y0, uint32_t rgb0, int16_t x1, int16_t y1, uint32_t rgb1) {
    if (cmdQueueSpace < 20) return -1;
    FT8_start_cmd(CMD_GRADIENT);
    queue16(x0);
    queue16(y0);
    queue32(rgb0 & 0xffffff);
    queue16(x1);
    queue16(y1);
    queue32(rgb1 & 0xffffff);
    return 0;
}

int FT8_cmd_keys(int16_t x0, int16_t y0, int16_t w0, int16_t h0, int16_t font, uint16_t options, const char* text) {
    if (cmdQueueSpace < strlen(text) + 20) return -1;
    FT8_start_cmd(CMD_KEYS);
    queue16(x0);
    queue16(y0);
    queue16(w0);
    queue16(h0);
    queue16(font);
    queue16(options);
    queue_string(text);
    return 0;
}

int FT8_cmd_progress(int16_t x0, int16_t y0, int16_t w0, int16_t h0, uint16_t options, uint16_t val, uint16_t range) {
    if (cmdQueueSpace < 20) return -1;
    FT8_start_cmd(CMD_PROGRESS);
    queue16(x0);
    queue16(y0);
    queue16(w0);
    queue16(h0);
    queue16(options);
    queue16(val);
    queue16(range);
    alignQueue();
    return 0;
}

int FT8_cmd_scrollbar(int16_t x0, int16_t y0, int16_t w0, int16_t h0, uint16_t options, uint16_t val, uint16_t size, uint16_t range) {
    if (cmdQueueSpace < 20) return -1;
    FT8_start_cmd(CMD_SCROLLBAR);
    queue16(x0);
    queue16(y0);
    queue16(w0);
    queue16(h0);
    queue16(options);
    queue16(val);
    queue16(size);
    queue16(range);
    return 0;
}

int FT8_cmd_slider(int16_t x0, int16_t y0, int16_t w0, int16_t h0, uint16_t options, uint16_t val, uint16_t range) {
    if (cmdQueueSpace < 20) return -1;
    FT8_start_cmd(CMD_SLIDER);
    queue16(x0);
    queue16(y0);
    queue16(w0);
    queue16(h0);
    queue16(options);
    queue16(val);
    queue16(range);
    alignQueue();
    return 0;
}

int FT8_cmd_dial(int16_t x0, int16_t y0, int16_t r0, uint16_t options, uint16_t val) {
    if (cmdQueueSpace < 16) return -1;
    FT8_start_cmd(CMD_DIAL);
    queue16(x0);
    queue16(y0);
    queue16(r0);
    queue16(options);
    queue16(val);
    alignQueue();
    return 0;
}

int FT8_cmd_toggle(int16_t x0, int16_t y0, int16_t w0, int16_t font, uint16_t options, uint16_t state, const char* text) {
    if (cmdQueueSpace < strlen(text) + 20) return -1;
    FT8_start_cmd(CMD_TOGGLE);
    queue16(x0);
    queue16(y0);
    queue16(w0);
    queue16(font);
    queue16(options);
    queue16(state);
    queue_string(text);
    return 0;
}


#ifdef FT8_81X_ENABLE
int FT8_cmd_setbase(uint32_t _base)
{
	if (cmdQueueSpace < 8) return -1;
    FT8_start_cmd(CMD_SETBASE);
    queue32(_base);
    return 0;
}
#endif

#ifdef FT8_81X_ENABLE
int FT8_cmd_setbitmap(uint32_t addr, uint16_t fmt, uint16_t width, uint16_t height)
{
	if (cmdQueueSpace < 16) return -1;
    FT8_start_cmd(CMD_SETBITMAP);
    queue32(addr);
    queue16(fmt);
    queue16(width);
    queue16(height);
    return 0;
}
#endif


int FT8_cmd_number(int16_t x0, int16_t y0, int16_t font, uint16_t options, int32_t number)
{
	if (cmdQueueSpace < 16) return -1;
    FT8_start_cmd(CMD_NUMBER);
    queue16(x0);
    queue16(y0);
    queue16(font);
    queue16(options);
    queue32(number);
    return 0;
}


/* commands to operate on memory: */

int FT8_cmd_memzero(uint32_t ptr, uint32_t num)
{
	if (cmdQueueSpace < 12) return -1;
    FT8_start_cmd(CMD_MEMZERO);
    queue32(ptr);
    queue32(num);
    return 0;
}


int FT8_cmd_memset(uint32_t ptr, uint8_t value, uint32_t num)
{
	if (cmdQueueSpace < 16) return -1;
    FT8_start_cmd(CMD_MEMSET);
    queue32(ptr);
    queue32(value);
    queue32(num);
    return 0;
}


int FT8_cmd_memwrite(uint32_t dest, uint32_t num, const uint8_t *data)
{
	if (cmdQueueSpace < num + 12) return -1;
    FT8_start_cmd(CMD_MEMWRITE);
    queue32(dest);
    queue32(num);
    memcpy(cmdQueue + cmdQueueLength, data, num);
    cmdQueueLength += num;
    alignQueue();
    return 0;
}


int FT8_cmd_memcpy(uint32_t dest, uint32_t src, uint32_t num)
{
	if (cmdQueueSpace < 16) return -1;
    FT8_start_cmd(CMD_MEMCPY);
    queue32(dest);
    queue32(src);
    queue32(num);
    return 0;
}


int FT8_cmd_append(uint32_t ptr, uint32_t num)
{
	if (cmdQueueSpace < 12) return -1;
    FT8_start_cmd(CMD_APPEND);
    queue32(ptr);
    queue32(num);
    return 0;
}


///* this is meant to be called outside display-list building, it includes executing the command and waiting for completion, does not support cmd-burst */
//void FT8_cmd_inflate(uint32_t ptr, const uint8_t *data, uint16_t len)
//{
//	FT8_start_cmd(CMD_INFLATE);
//
//	spi_transmit((uint8_t)(ptr));
//	spi_transmit((uint8_t)(ptr >> 8));
//	spi_transmit((uint8_t)(ptr >> 16));
//	spi_transmit((uint8_t)(ptr >> 24));
//
//	FT8_inc_cmdoffset(4);
//	FT8_cs_clear();
//	
//	block_transfer(data, len);
//}
//
//
///* this is meant to be called outside display-list building, it includes executing the command and waiting for completion, does not support cmd-burst */
//void FT8_cmd_loadimage(uint32_t ptr, uint32_t options, const uint8_t *data, uint16_t len)
//{
//	FT8_start_cmd(CMD_LOADIMAGE);
//
//	spi_transmit((uint8_t)(ptr));
//	spi_transmit((uint8_t)(ptr >> 8));
//	spi_transmit((uint8_t)(ptr >> 16));
//	spi_transmit((uint8_t)(ptr >> 24));
//
//	spi_transmit((uint8_t)(options));
//	spi_transmit((uint8_t)(options >> 8));
//	spi_transmit((uint8_t)(options >> 16));
//	spi_transmit((uint8_t)(options >> 24));
//
//	FT8_inc_cmdoffset(8);
//	FT8_cs_clear();
//
//#ifdef FT8_81X_ENABLE
//	if((options & FT8_OPT_MEDIAFIFO) == 0) /* data is not transmitted thru the Media-FIFO */
//#endif
//	{
//		block_transfer(data, len);
//	}
//}


#ifdef FT8_81X_ENABLE
int FT8_cmd_mediafifo(uint32_t ptr, uint32_t size)
{
	if (cmdQueueSpace < 12) return -1;
    FT8_start_cmd(CMD_MEDIAFIFO);
    queue32(ptr);
    queue32(size);
    return 0;
}
#endif


/* commands for setting the bitmap transform matrix: */

int FT8_cmd_translate(int32_t tx, int32_t ty)
{
	if (cmdQueueSpace < 12) return -1;
    FT8_start_cmd(CMD_TRANSLATE);
    queue32(tx);
    queue32(ty);
    return 0;
}


int FT8_cmd_scale(int32_t sx, int32_t sy)
{
	if (cmdQueueSpace < 12) return -1;
    FT8_start_cmd(CMD_SCALE);
    queue32(sx);
    queue32(sy);
    return 0;
}


int FT8_cmd_rotate(int32_t ang)
{
	if (cmdQueueSpace < 8) return -1;
    FT8_start_cmd(CMD_ROTATE);
    queue32(ang);
    return 0;
}


//void FT8_cmd_getmatrix(int32_t a, int32_t b, int32_t c, int32_t d, int32_t e, int32_t f)
//{
//	FT8_start_cmd(CMD_SETMATRIX);
//
//	spi_transmit((uint8_t)(a));
//	spi_transmit((uint8_t)(a >> 8));
//	spi_transmit((uint8_t)(a >> 16));
//	spi_transmit((uint8_t)(a >> 24));
//
//	spi_transmit((uint8_t)(b));
//	spi_transmit((uint8_t)(b >> 8));
//	spi_transmit((uint8_t)(b >> 16));
//	spi_transmit((uint8_t)(b >> 24));
//
//	spi_transmit((uint8_t)(c));
//	spi_transmit((uint8_t)(c >> 8));
//	spi_transmit((uint8_t)(c >> 16));
//	spi_transmit((uint8_t)(c >> 24));
//
//	spi_transmit((uint8_t)(d));
//	spi_transmit((uint8_t)(d >> 8));
//	spi_transmit((uint8_t)(d >> 16));
//	spi_transmit((uint8_t)(d >> 24));
//
//	spi_transmit((uint8_t)(e));
//	spi_transmit((uint8_t)(e >> 8));
//	spi_transmit((uint8_t)(e >> 16));
//	spi_transmit((uint8_t)(e >> 24));
//
//	spi_transmit((uint8_t)(f));
//	spi_transmit((uint8_t)(f >> 8));
//	spi_transmit((uint8_t)(f >> 16));
//	spi_transmit((uint8_t)(f >> 24));
//
//	FT8_inc_cmdoffset(24);
//
//	if(cmd_burst == 0)
//	{
//		FT8_cs_clear();
//	}
//}


/* other commands: */

int FT8_cmd_calibrate(void)
{
	if (cmdQueueSpace < 8) return -1;
    FT8_start_cmd(CMD_CALIBRATE);
    queue32(0);
    return 0;
}


int FT8_cmd_interrupt(uint32_t ms)
{
	if (cmdQueueSpace < 8) return -1;
    FT8_start_cmd(CMD_INTERRUPT);
    queue32(ms);
    return 0;
}


#ifdef FT8_81X_ENABLE
int FT8_cmd_romfont(uint32_t font, uint32_t romslot)
{
	if (cmdQueueSpace < 12) return -1;
    FT8_start_cmd(CMD_ROMFONT);
    queue32(font & 0xffff);
    queue32(romslot & 0xffff);
    return 0;
}
#endif


int FT8_cmd_setfont(uint32_t font, uint32_t ptr)
{
	if (cmdQueueSpace < 12) return -1;
    FT8_start_cmd(CMD_SETFONT);
    queue32(font);
    queue32(ptr);
    return 0;
}


#ifdef FT8_81X_ENABLE
int FT8_cmd_setfont2(uint32_t font, uint32_t ptr, uint32_t firstchar)
{
	if (cmdQueueSpace < 16) return -1;
    FT8_start_cmd(CMD_SETFONT2);
    queue32(font);
    queue32(ptr);
    queue32(firstchar);
    return 0;
}
#endif


#ifdef FT8_81X_ENABLE
int FT8_cmd_setrotate(uint32_t r)
{
	if (cmdQueueSpace < 8) return -1;
    FT8_start_cmd(CMD_SETROTATE);
    queue32(r);
    return 0;
}
#endif


#ifdef FT8_81X_ENABLE
int FT8_cmd_setscratch(uint32_t handle)
{
	if (cmdQueueSpace < 8) return -1;
    FT8_start_cmd(CMD_SETSCRATCH);
    queue32(handle);
    return 0;
}
#endif


int FT8_cmd_sketch(int16_t x0, int16_t y0, uint16_t w0, uint16_t h0, uint32_t ptr, uint16_t format)
{
	if (cmdQueueSpace < 20) return -1;
    FT8_start_cmd(CMD_SKETCH);
    queue16(x0);
    queue16(y0);
    queue16(w0);
    queue16(h0);
    queue32(ptr);
    queue16(format);
    alignQueue();
    return 0;
}


int FT8_cmd_snapshot(uint32_t ptr)
{
	if (cmdQueueSpace < 8) return -1;
    FT8_start_cmd(CMD_SNAPSHOT);
    queue32(ptr);
    return 0;
}


#ifdef FT8_81X_ENABLE
int FT8_cmd_snapshot2(uint32_t fmt, uint32_t ptr, int16_t x0, int16_t y0, int16_t w0, int16_t h0)
{
	if (cmdQueueSpace < 20) return -1;
    FT8_start_cmd(CMD_SNAPSHOT2);
    queue32(fmt);
    queue32(ptr);
    queue16(x0);
    queue16(y0);
    queue16(w0);
    queue16(h0);
    return 0;
}
#endif


int FT8_cmd_spinner(int16_t x0, int16_t y0, uint16_t style, uint16_t scale)
{
	if (cmdQueueSpace < 12) return -1;
    FT8_start_cmd(CMD_SPINNER);
    queue16(x0);
    queue16(y0);
    queue16(style);
    queue16(scale);
    return 0;
}


int FT8_cmd_track(int16_t x0, int16_t y0, int16_t w0, int16_t h0, int16_t tag)
{
	if (cmdQueueSpace < 16) return -1;
    FT8_start_cmd(CMD_TRACK);
    queue16(x0);
    queue16(y0);
    queue16(w0);
    queue16(h0);
    queue16(tag);
    alignQueue();
    return 0;
}


///* commands that return values by writing to the command-fifo */
///* this is handled by having this functions return the offset address on the command-fifo from
//   which the results can be fetched after execution: FT8_memRead32(FT8_RAM_CMD + offset) */
///* note: yes, these are different than the functions in the Programmers Guide from FTDI,
//	this is because I have no idea why anyone would want to pass "result" as an actual argument to these functions
//	when this only marks the offset the command-processor is writing to, it may even be okay to not transfer anything at all,
//	just advance the offset by 4 bytes */
//
///*
//example of using FT8_cmd_memcrc:
//
// offset = FT8_cmd_memcrc(my_ptr_to_some_memory_region, some_amount_of_bytes);
// FT8_cmd_execute();
// crc32 = FT8_memRead32(FT8_RAM_CMD + offset);
//
//*/
//
//uint16_t FT8_cmd_memcrc(uint32_t ptr, uint32_t num)
//{
//	uint16_t offset;
//
//	FT8_start_cmd(CMD_MEMCRC);
//
//	spi_transmit((uint8_t)(ptr));
//	spi_transmit((uint8_t)(ptr >> 8));
//	spi_transmit((uint8_t)(ptr >> 16));
//	spi_transmit((uint8_t)(ptr >> 24));
//
//	spi_transmit((uint8_t)(num));
//	spi_transmit((uint8_t)(num >> 8));
//	spi_transmit((uint8_t)(num >> 16));
//	spi_transmit((uint8_t)(num >> 24));
//
//	spi_transmit(0);
//	spi_transmit(0);
//	spi_transmit(0);
//	spi_transmit(0);
//
//	FT8_inc_cmdoffset(8);
//	offset = cmdOffset;
//	FT8_inc_cmdoffset(4);
//
//	if(cmd_burst == 0)
//	{
//		FT8_cs_clear();
//	}
//
//	return offset;
//}
//
//
//uint16_t FT8_cmd_getptr(void)
//{
//	uint16_t offset;
//
//	FT8_start_cmd(CMD_GETPTR);
//
//	spi_transmit(0);
//	spi_transmit(0);
//	spi_transmit(0);
//	spi_transmit(0);
//
//	offset = cmdOffset;
//	FT8_inc_cmdoffset(4);
//
//	if(cmd_burst == 0)
//	{
//		FT8_cs_clear();
//	}
//
//	return offset;
//}
//
//
//uint16_t FT8_cmd_regread(uint32_t ptr)
//{
//	uint16_t offset;
//
//	FT8_start_cmd(CMD_REGREAD);
//
//	spi_transmit((uint8_t)(ptr));
//	spi_transmit((uint8_t)(ptr >> 8));
//	spi_transmit((uint8_t)(ptr >> 16));
//	spi_transmit((uint8_t)(ptr >> 24));
//
//	spi_transmit(0);
//	spi_transmit(0);
//	spi_transmit(0);
//	spi_transmit(0);
//
//	FT8_inc_cmdoffset(4);
//	offset = cmdOffset;
//	FT8_inc_cmdoffset(4);
//
//	if(cmd_burst == 0)
//	{
//		FT8_cs_clear();
//	}
//
//	return offset;
//}
//
//
///* be aware that this returns the first offset pointing to "width", in order to also read
//"height" you need to:
//
// offset = FT8_cmd_getprops(my_last_picture_pointer);
// FT8_cmd_execute();
// width = FT8_memRead32(FT8_RAM_CMD + offset);
// offset += 4;
// offset &= 0x0fff;
// height = FT8_memRead32(FT8_RAM_CMD + offset);
//*/
//
//uint16_t FT8_cmd_getprops(uint32_t ptr)
//{
//	uint16_t offset;
//
//	FT8_start_cmd(CMD_REGREAD);
//
//	spi_transmit((uint8_t)(ptr));
//	spi_transmit((uint8_t)(ptr >> 8));
//	spi_transmit((uint8_t)(ptr >> 16));
//	spi_transmit((uint8_t)(ptr >> 24));
//
//	spi_transmit(0);
//	spi_transmit(0);
//	spi_transmit(0);
//	spi_transmit(0);
//
//	spi_transmit(0);
//	spi_transmit(0);
//	spi_transmit(0);
//	spi_transmit(0);
//
//	FT8_inc_cmdoffset(4);
//	offset = cmdOffset;
//	FT8_inc_cmdoffset(4);
//
//	if(cmd_burst == 0)
//	{
//		FT8_cs_clear();
//	}
//
//	return offset;
//}


/* meta-commands, sequences of several display-list entries condensed into simpler to use functions at the price of some overhead */

int FT8_cmd_begindisplay(bool color, bool stencil, bool tag, uint32_t clearColor) {
    if (FT8_cmd_memzero(FT8_RAM_DL, 8192) < 0) return -1;
    if (cmdQueueSpace < 12) return -1;
    queue32(CMD_DLSTART);
    queue32(DL_CLEAR_RGB | (clearColor & 0xffffff));
    queue32(CLEAR(color, stencil, tag));
    return 0;
}

int FT8_cmd_color(uint32_t color) {
    if (cmdQueueSpace < 4) return -1;
    queue32(DL_COLOR_RGB | (color & 0xffffff));
    return 0;
}

int FT8_cmd_point(int16_t x0, int16_t y0, uint16_t size)
{
	if (cmdQueueSpace < 16) return -1;
    queue32(BEGIN(FT8_POINTS));
    queue32(POINT_SIZE(16 * size));
    queue32(VERTEX2F(16 * x0, 16 * y0));
    queue32(END());
    return 0;
}


int FT8_cmd_line(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t width)
{
	if (cmdQueueSpace < 20) return -1;
	queue32(BEGIN(FT8_LINES));
    queue32(LINE_WIDTH(16 * width));
    queue32(VERTEX2F(16 * x0, 16 * y0));
    queue32(VERTEX2F(16 * x1, 16 * y1));
    queue32(END());
    return 0;
}


int FT8_cmd_rect(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t corner)
{
	if (cmdQueueSpace < 20) return -1;
    queue32(BEGIN(FT8_RECTS));
    queue32(LINE_WIDTH(16 * corner));
    queue32(VERTEX2F(16 * x0, 16 * y0));
    queue32(VERTEX2F(16 * x1, 16 * y1));
    queue32(END());
    return 0;
}

int FT8_cmd_enddisplay() {
    if (cmdQueueSpace < 8) return -1;
    queue32(DISPLAY());
    queue32(CMD_SWAP);
    return 0;
}


/* FT811 / FT813 binary-blob from FTDIs AN_336 to patch the touch-engine for Goodix GT911 / GT9271 touch controllers */
#ifdef FT8_HAS_GT911

#if	defined (__AVR__)
#include <avr/pgmspace.h>
#else
#define PROGMEM
#endif

const uint16_t FT8_GT911_len = 1184;
const uint8_t FT8_GT911_data[1184] PROGMEM ={
    26, 255, 255, 255, 32, 32, 48, 0, 4, 0, 0, 0, 2, 0, 0, 0,
    34, 255, 255, 255, 0, 176, 48, 0, 120, 218, 237, 84, 221, 111, 84, 69, 20, 63, 51, 179, 93, 160, 148, 101, 111, 76, 5, 44, 141, 123, 111, 161, 11, 219, 154, 16, 9, 16, 17, 229, 156, 75, 26, 11, 13, 21, 227, 3, 16, 252, 184, 179,
    45, 219, 143, 45, 41, 125, 144, 72, 67, 100, 150, 71, 189, 113, 18, 36, 17, 165, 100, 165, 198, 16, 32, 17, 149, 196, 240, 128, 161, 16, 164, 38, 54, 240, 0, 209, 72, 130, 15, 38, 125, 48, 66, 82, 30, 76, 19, 31, 172, 103, 46,
    139, 24, 255, 4, 227, 157, 204, 156, 51, 115, 102, 206, 231, 239, 220, 5, 170, 94, 129, 137, 75, 194, 216, 98, 94, 103, 117, 115, 121, 76, 131, 177, 125, 89, 125, 82, 123, 60, 243, 58, 142, 242, 204, 185, 243, 188, 118, 156,
    227, 155, 203, 238, 238, 195, 251, 205, 229, 71, 92, 28, 169, 190, 184, 84, 143, 113, 137, 53, 244, 103, 181, 237, 87, 253, 113, 137, 233, 48, 12, 198, 165, 181, 104, 139, 25, 84, 253, 155, 114, 74, 191, 0, 54, 138, 163,
    12, 62, 131, 207, 129, 23, 217, 34, 91, 31, 128, 65, 246, 163, 175, 213, 8, 147, 213, 107, 35, 203, 94, 108, 3, 111, 40, 171, 83, 24, 15, 165, 177, 222, 116, 97, 23, 188, 140, 206, 150, 42, 102, 181, 87, 78, 86, 182, 170, 134,
    215, 241, 121, 26, 243, 252, 2, 76, 115, 217, 139, 222, 206, 173, 136, 132, 81, 61, 35, 185, 39, 113, 23, 46, 199, 76, 178, 54, 151, 183, 224, 0, 40, 189, 28, 149, 182, 58, 131, 79, 152, 30, 76, 34, 98, 234, 162, 216, 133, 141,
    102, 39, 170, 40, 192, 101, 53, 201, 146, 191, 37, 77, 44, 177, 209, 74, 211, 5, 206, 187, 5, 6, 216, 47, 53, 96, 123, 22, 50, 103, 251, 192, 84, 17, 74, 227, 185, 56, 106, 51, 91, 161, 96, 182, 163, 48, 171, 141, 139, 65, 152,
    66, 66, 11, 102, 43, 158, 75, 36, 80, 147, 184, 147, 139, 112, 17, 235, 216, 103, 111, 239, 245, 92, 10, 175, 194, 40, 44, 58, 125, 5, 59, 112, 50, 103, 245, 4, 78, 192, 5, 156, 194, 51, 60, 191, 134, 75, 110, 173, 237, 46, 192,
    121, 156, 192, 115, 184, 218, 120, 67, 63, 115, 46, 11, 102, 10, 97, 232, 50, 235, 114, 182, 148, 118, 178, 41, 188, 12, 135, 77, 202, 124, 12, 96, 238, 35, 161, 234, 189, 129, 23, 249, 212, 139, 230, 25, 53, 48, 205, 52, 93,
    163, 117, 53, 154, 170, 81, 85, 163, 178, 70, 69, 66, 167, 241, 14, 46, 241, 1, 226, 136, 152, 179, 197, 59, 184, 148, 254, 49, 132, 48, 15, 176, 137, 192, 76, 131, 196, 105, 104, 162, 86, 81, 160, 165, 255, 26, 173, 162, 137,
    86, 145, 210, 183, 192, 55, 175, 194, 211, 60, 91, 120, 230, 184, 174, 27, 41, 131, 155, 40, 224, 29, 87, 179, 232, 16, 55, 55, 7, 165, 147, 81, 23, 165, 49, 101, 54, 224, 75, 180, 81, 108, 18, 29, 226, 69, 225, 110, 175, 224,
    42, 212, 25, 47, 130, 193, 110, 234, 192, 215, 252, 56, 74, 162, 24, 46, 251, 174, 54, 106, 68, 245, 14, 9, 155, 160, 22, 120, 207, 104, 240, 29, 90, 178, 140, 28, 24, 220, 47, 166, 112, 61, 251, 208, 192, 111, 56, 239, 238,
    93, 255, 251, 62, 99, 32, 193, 75, 61, 190, 235, 123, 229, 110, 218, 194, 85, 79, 225, 59, 98, 20, 238, 227, 235, 220, 11, 221, 149, 25, 180, 116, 194, 159, 111, 96, 192, 24, 213, 59, 139, 179, 156, 215, 69, 230, 19, 24, 35,
    135, 117, 206, 171, 206, 162, 67, 129, 234, 61, 235, 11, 104, 103, 84, 64, 223, 167, 254, 40, 163, 101, 92, 84, 43, 150, 46, 249, 219, 205, 7, 116, 11, 91, 104, 61, 57, 75, 223, 8, 48, 25, 28, 119, 252, 222, 113, 49, 86, 249,
    74, 180, 211, 156, 181, 61, 215, 168, 157, 7, 251, 199, 150, 242, 250, 91, 58, 132, 94, 121, 7, 53, 151, 139, 98, 6, 165, 153, 69, 214, 32, 110, 211, 100, 101, 31, 89, 45, 81, 98, 23, 205, 205, 197, 209, 109, 186, 198, 35,
    141, 191, 249, 25, 60, 132, 223, 153, 251, 98, 20, 239, 146, 139, 20, 217, 250, 41, 250, 137, 58, 177, 90, 57, 79, 51, 108, 233, 20, 253, 194, 187, 49, 222, 205, 114, 141, 96, 48, 175, 219, 107, 54, 111, 138, 22, 154, 103,
    108, 79, 58, 252, 179, 178, 79, 164, 195, 2, 153, 36, 39, 170, 199, 201, 167, 197, 85, 106, 8, 59, 177, 81, 46, 56, 2, 230, 75, 114, 17, 55, 112, 188, 65, 208, 137, 77, 114, 10, 115, 55, 58, 208, 197, 173, 122, 87, 6, 140,
    110, 42, 208, 124, 163, 70, 108, 241, 104, 18, 245, 98, 214, 187, 134, 53, 42, 221, 22, 182, 133, 211, 116, 148, 177, 194, 209, 192, 85, 90, 199, 58, 55, 203, 2, 229, 19, 137, 187, 161, 228, 154, 112, 203, 145, 125, 244,
    188, 220, 118, 228, 41, 201, 181, 41, 195, 144, 215, 183, 51, 80, 250, 21, 217, 16, 217, 200, 235, 109, 227, 188, 122, 218, 142, 60, 170, 224, 112, 240, 184, 130, 229, 224, 113, 5, 223, 148, 163, 80, 165, 183, 130, 187,
    132, 116, 64, 238, 161, 85, 220, 115, 139, 205, 98, 227, 244, 29, 102, 125, 7, 37, 243, 123, 223, 11, 26, 92, 63, 243, 116, 61, 191, 138, 123, 244, 160, 84, 186, 74, 31, 5, 174, 247, 119, 135, 199, 248, 253, 135, 242, 97,
    102, 145, 190, 144, 14, 85, 238, 221, 231, 193, 158, 48, 205, 25, 120, 248, 15, 220, 29, 158, 9, 70, 185, 30, 103, 229, 33, 254, 23, 237, 160, 172, 62, 193, 90, 222, 224, 232, 14, 200, 56, 90, 104, 142, 227, 120, 110, 6,
    21, 211, 203, 65, 150, 99, 151, 220, 247, 87, 164, 50, 159, 49, 239, 234, 58, 142, 0, 109, 108, 123, 18, 79, 227, 36, 100, 248, 222, 205, 96, 127, 120, 26, 171, 228, 69, 63, 36, 17, 252, 200, 17, 116, 242, 187, 227, 88, 143,
    247, 2, 75, 191, 6, 130, 59, 188, 11, 55, 240, 31, 243, 122, 152, 226, 183, 207, 154, 73, 188, 39, 219, 43, 105, 222, 87, 41, 143, 141, 140, 175, 73, 112, 184, 252, 61, 184, 16, 90, 250, 35, 168, 82, 119, 176, 57, 116, 94,
    200, 150, 22, 190, 179, 44, 104, 12, 235, 84, 149, 102, 252, 89, 154, 193, 99, 228, 106, 242, 125, 248, 64, 194, 255, 223, 127, 242, 83, 11, 255, 2, 70, 214, 226, 128, 0, 0
};
#endif


/* init, has to be executed with the SPI setup to 11 MHz or less as required by FT8xx */
uint8_t initTimeout = 0;

void testListCallback(uintptr_t context, uint32_t currTick) {
    FT8_cmd_begindisplay(true, true, true, 0x000000);
    FT8_cmd_color(0xffffff);
    FT8_cmd_text(160, 50, 29, FT8_OPT_CENTER, "Wait!");
    FT8_cmd_spinner(160, 100, 0, 0);
    FT8_cmd_enddisplay();
    FT8_cmd_start();
}

void initFinalCallback(void* context) {
    FT8_get_cmdoffset(NULL, NULL); /* just to be safe */
    SYS_TMR_CallbackSingle(100, 0, testListCallback);
}

void initIDReadCallback(uint8_t data, void* context); //predef

void initTimerCallback(uintptr_t context, uint32_t currTick) {
    switch (context) {
        case 0:
            DisplayENOn();
            SYS_TMR_CallbackSingle(21, 1, initTimerCallback);
            break;
        case 1:
            if (FT8_HAS_CRYSTAL != 0) {
                FT8_cmdWrite(FT8_CLKEXT, 0); /* setup FT8xx for external clock */
            } else {
                FT8_cmdWrite(FT8_CLKINT, 0); /* setup FT8xx for internal clock */
            }
            FT8_cmdWrite(FT8_ACTIVE, 0); /* start FT8xx */
            SYS_TMR_CallbackSingle(500, 2, initTimerCallback);
            break;
        case 2:
            FT8_memRead8(REG_ID, initIDReadCallback, NULL);
            break;
        case 3:
            FT8_busy(initFinalCallback, NULL);
            break;
        default:
            break;
    }
}

void initPart2(void* context) {
    /* configure Touch */
    FT8_memWrite8(REG_TOUCH_MODE, FT8_TMODE_CONTINUOUS); /* enable touch */
    FT8_memWrite16(REG_TOUCH_RZTHRESH, FT8_TOUCH_RZTHRESH); /* eliminate any false touches */

    /* disable Audio for now */
    FT8_memWrite8(REG_VOL_PB, 0x00); /* turn recorded audio volume down */
    FT8_memWrite8(REG_VOL_SOUND, 0x00); /* turn synthesizer volume off */
    FT8_memWrite16(REG_SOUND, 0x6000); /*	set synthesizer to mute */

    /* write a basic display-list to get things started */
    FT8_memWrite32(FT8_RAM_DL, DL_CLEAR_RGB);
    FT8_memWrite32(FT8_RAM_DL + 4, (DL_CLEAR | CLR_COL | CLR_STN | CLR_TAG));
    FT8_memWrite32(FT8_RAM_DL + 8, DL_DISPLAY); /* end of display list */
    FT8_memWrite32(REG_DLSWAP, FT8_DLSWAP_FRAME);

    /* nothing is being displayed yet... the pixel clock is still 0x00 */
    FT8_memWrite8(REG_GPIO, 0x80); /* enable the DISP signal to the LCD panel, it is set to output in REG_GPIO_DIR by default */
    FT8_memWrite8(REG_PCLK, FT8_PCLK); /* now start clocking data to the LCD panel */
    FT8_memWrite8(REG_PWM_DUTY, 64); /* turn on backlight to some value that needs to be adjusted or not... */

    SYS_TMR_CallbackSingle(2, 3, initTimerCallback);
}

void initIDReadCallback(uint8_t data, void* context) {
    if (data != 0x7C) {
        if (++initTimeout > 100) return;
        SYS_TMR_CallbackSingle(5, 2, initTimerCallback);
        return;
    }

    // successfully booted FT81 at this point //

    FT8_memWrite8(REG_PWM_DUTY, 0); /* turn off backlight */

    /* Initialize Display */
    FT8_memWrite16(REG_HSIZE, FT8_HSIZE); /* active display width */
    FT8_memWrite16(REG_HCYCLE, FT8_HCYCLE); /* total number of clocks per line, incl front/back porch */
    FT8_memWrite16(REG_HOFFSET, FT8_HOFFSET); /* start of active line */
    FT8_memWrite16(REG_HSYNC0, FT8_HSYNC0); /* start of horizontal sync pulse */
    FT8_memWrite16(REG_HSYNC1, FT8_HSYNC1); /* end of horizontal sync pulse */
    FT8_memWrite16(REG_VSIZE, FT8_VSIZE); /* active display height */
    FT8_memWrite16(REG_VCYCLE, FT8_VCYCLE); /* total number of lines per screen, incl pre/post */
    FT8_memWrite16(REG_VOFFSET, FT8_VOFFSET); /* start of active screen */
    FT8_memWrite16(REG_VSYNC0, FT8_VSYNC0); /* start of vertical sync pulse */
    FT8_memWrite16(REG_VSYNC1, FT8_VSYNC1); /* end of vertical sync pulse */
    FT8_memWrite8(REG_SWIZZLE, FT8_SWIZZLE); /* FT8xx output to LCD - pin order */
    FT8_memWrite8(REG_PCLK_POL, FT8_PCLKPOL); /* LCD data is clocked in on this PCLK edge */
    FT8_memWrite8C(REG_CSPREAD, FT8_CSPREAD, initPart2, NULL); /* helps with noise, when set to 1 fewer signals are changed simultaneously, reset-default: 1 */

    /* Don't set PCLK yet - wait for just after the first display list */
}

void FT8_init() {
    DRV_SPI1_ClientConfigure(&lsCfg);
    PLIB_SPI_SlaveSelectDisable(SPI_ID_4);
    PLIB_SPI_BufferClear(SPI_ID_4);

    DisplayENOff();
    SYS_TMR_CallbackSingle(10, 0, initTimerCallback);
}

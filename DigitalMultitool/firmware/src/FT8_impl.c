
/*
 *  FT8 library implementation
 */

#include "FT8_impl.h"

void DELAY_MS(int time) {
    int cycles = time * (SYS_CLK_FREQ / 2000);
    int st = _CP0_GET_COUNT();
    while (_CP0_GET_COUNT() - st < cycles);
}

void FT8_pdn_set() {
    //clear inverted PD pin
    DisplayENOff();
}

void FT8_pdn_clear() {
    //set inverted PD pin
    DisplayENOn();
}

void FT8_cs_set() {
    //select 0
    PLIB_SQI_ChipSelectSet(SQI_ID_0, SQI_CS_0);
}

void FT8_cs_clear() {
    //select 1
    PLIB_SQI_ChipSelectSet(SQI_ID_0, SQI_CS_1);
}

void spi_transmit2(uint8_t data, bool single) {
    //todo: read datasheet again about this
    if (single) {
        PLIB_SQI_ControlWordSet(SQI_ID_0, false, SQI_CS_0,
                SQI_LANE_SINGLE, SQI_CMD_TRANSMIT, 1);
    } else {
        PLIB_SQI_ControlWordSet(SQI_ID_0, false, SQI_CS_0,
                SQI_LANE_QUAD, SQI_CMD_TRANSMIT, 1);
    }
    PLIB_SQI_TransmitData(SQI_ID_0, data);
}

uint8_t spi_receive2(uint8_t data, bool single) {
    //todo: see transmit
    if (single) {
        PLIB_SQI_ControlWordSet(SQI_ID_0, false, SQI_CS_0,
                SQI_LANE_SINGLE, SQI_CMD_RECEIVE, 1);
    } else {
        PLIB_SQI_ControlWordSet(SQI_ID_0, false, SQI_CS_0,
                SQI_LANE_QUAD, SQI_CMD_RECEIVE, 1);
    }
    return PLIB_SQI_ReceiveData(SQI_ID_0);
}

int fetch_flash_byte(uint8_t* addr) {
    return 0;
}

void disp_init() {
    PLIB_SQI_ConfigWordSet(SQI_ID_0,
            true,
            SQI_CS_OEN_0,
            SQI_DATA_OEN_QUAD,
            false, true, false,
            false, false, 
            SQI_DATA_FORMAT_MSBF, 
            SQI_DATA_MODE_0, 
            SQI_XFER_MODE_PIO);
    
    PLIB_SQI_ClockDividerSet(SQI_ID_0, CLK_DIV_4); // ~6 MHz clock for init
    PLIB_SQI_ClockEnable(SQI_ID_0);
    while (!PLIB_SQI_ClockIsStable(SQI_ID_0));
    
    //maybe interrupt enables, buffer thresholds???
    
    FT8_init();
    
    PLIB_SQI_ClockDisable(SQI_ID_0);
    PLIB_SQI_ClockDividerSet(SQI_ID_0, CLK_DIV_1); // ~25 MHz clock (FT81x max)
    PLIB_SQI_ClockEnable(SQI_ID_0);
    while (!PLIB_SQI_ClockIsStable(SQI_ID_0));
}


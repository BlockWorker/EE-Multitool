
/*
 *  FT8 library implementation
 */

#ifndef _FT8_IMPL_H    /* Guard against multiple inclusion */
#define _FT8_IMPL_H

#include "app.h"

/* Provide C++ Compatibility */
#ifdef __cplusplus
extern "C" {
#endif

    void spi_transmit2(uint8_t data, bool single);
    void spi_transmit(uint8_t data) {
        spi_transmit2(data, false);
    }
    uint8_t spi_receive2(uint8_t data, bool single);
    uint8_t spi_receive(uint8_t data) {
        return spi_receive2(data, false);
    }
    void FT8_cs_set();
    void FT8_cs_clear();
    int fetch_flash_byte(uint8_t* addr);
    void FT8_pdn_set();
    void FT8_pdn_clear();
    void DELAY_MS(int time);
    
    void disp_init();

/* Provide C++ Compatibility */
#ifdef __cplusplus
}
#endif

#endif /* _FT8_IMPL_H */

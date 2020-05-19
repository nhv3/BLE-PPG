
#ifndef I2C_H__
#define I2C_H__

#ifdef __cplusplus
extern "C" {
#endif

    #include <stdio.h>
#include "boards.h"
#include "app_util_platform.h"
#include "app_error.h"
#include "nrf_drv_twi.h"
#include "nrf_delay.h"


#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "nrf_log_default_backends.h"
    
    
    #include "app_error.h" //for APP_ERROR_CHECK(err_code);
    #include "SEGGER_RTT.h"

    void I2C_init(uint32_t BA_SDA_PIN, uint32_t BA_SCL_PIN);
    
    void write_byte( uint8_t address, uint8_t subAddress, uint8_t data);
    
    void write_bytes(uint8_t address, uint8_t * data, uint8_t n_bytes);
    
    void read_bytes( uint8_t address, uint8_t subAddress, uint8_t * dest, uint8_t n_bytes);
    
    uint8_t read_byte(uint8_t address, uint8_t subAddress);
    
    void I2C_handler(nrf_drv_twi_evt_t const * p_event, void * p_context);

#ifdef __cplusplus
}
#endif

#endif /* I2C_H__ */

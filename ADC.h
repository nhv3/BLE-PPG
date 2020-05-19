
#ifndef MA_ADC_H__
#define MA_ADC_H__

#ifdef __cplusplus
extern "C" {
#endif
#include "SEGGER_RTT.h"    
    #include "nrf_drv_saadc.h"
//    void ADC_init(void);
//    int16_t return_adc(void);
//    void ADC_callback(nrf_drv_saadc_evt_t const * p_event);

void timer_handler(nrf_timer_event_t event_type, void * p_context);
void saadc_sampling_event_init(void);
void saadc_sampling_event_enable(void);
void saadc_callback(nrf_drv_saadc_evt_t const * p_event);
void saadc_init(void);
//int16_t return_adc(void);
#ifdef __cplusplus
}
#endif

#endif

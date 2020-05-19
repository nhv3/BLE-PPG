#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "nrf.h"
#include "nrf_drv_saadc.h"
#include "nrf_drv_ppi.h"
#include "nrf_drv_timer.h"
#include "boards.h"
#include "app_error.h"
#include "nrf_delay.h"
#include "app_util_platform.h"
#include "nrf_pwr_mgmt.h"
#include "segger_RTT.h"
#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "nrf_log_default_backends.h"

#define SAMPLES_IN_BUFFER 8
volatile uint8_t state = 1;
int16_t adc_val;

static const nrf_drv_timer_t m_timer = NRF_DRV_TIMER_INSTANCE(3);//change from 0 to 3 to work with BLE
static nrf_saadc_value_t     m_buffer_pool[2][SAMPLES_IN_BUFFER];
static nrf_ppi_channel_t     m_ppi_channel;
static uint32_t              m_adc_evt_counter;


void timer_handler(nrf_timer_event_t event_type, void * p_context)
{

}


void saadc_sampling_event_init(void)
{
    ret_code_t err_code;

    err_code = nrf_drv_ppi_init();
    SEGGER_RTT_printf(0, "Done setup 4.1");
    APP_ERROR_CHECK(err_code);

    nrf_drv_timer_config_t timer_cfg = NRF_DRV_TIMER_DEFAULT_CONFIG;
    timer_cfg.bit_width = NRF_TIMER_BIT_WIDTH_32;
    err_code = nrf_drv_timer_init(&m_timer, &timer_cfg, timer_handler);
    APP_ERROR_CHECK(err_code);

    SEGGER_RTT_printf(0, "Done setup 4.1");

    /* setup m_timer for compare event every 400ms */
    uint32_t ticks = nrf_drv_timer_ms_to_ticks(&m_timer, 2);//was 2 chanign to 20
    nrf_drv_timer_extended_compare(&m_timer,
                                   NRF_TIMER_CC_CHANNEL0,
                                   ticks,
                                   NRF_TIMER_SHORT_COMPARE0_CLEAR_MASK,
                                   false);
    nrf_drv_timer_enable(&m_timer);

    uint32_t timer_compare_event_addr = nrf_drv_timer_compare_event_address_get(&m_timer,
                                                                                NRF_TIMER_CC_CHANNEL0);
    uint32_t saadc_sample_task_addr   = nrf_drv_saadc_sample_task_get();

    /* setup ppi channel so that timer compare event is triggering sample task in SAADC */
    err_code = nrf_drv_ppi_channel_alloc(&m_ppi_channel);
    APP_ERROR_CHECK(err_code);

    err_code = nrf_drv_ppi_channel_assign(m_ppi_channel,
                                          timer_compare_event_addr,
                                          saadc_sample_task_addr);
    APP_ERROR_CHECK(err_code);
}


void saadc_sampling_event_enable(void)
{
    ret_code_t err_code = nrf_drv_ppi_channel_enable(m_ppi_channel);

    APP_ERROR_CHECK(err_code);
}


void saadc_callback(nrf_drv_saadc_evt_t const * p_event)
{
    //SEGGER_RTT_printf(0, "ADC 5 ...\n");
    if (p_event->type == NRF_DRV_SAADC_EVT_DONE)
    {
        ret_code_t err_code;

        err_code = nrf_drv_saadc_buffer_convert(p_event->data.done.p_buffer, SAMPLES_IN_BUFFER);
        APP_ERROR_CHECK(err_code);

//        int i;
//        //SEGGER_RTT_printf(0, "ADC event number: %d", (int)m_adc_evt_counter);
//        //SEGGER_RTT_printf(0, "ADC 6 ...\n");
//
//        for (i = 0; i < SAMPLES_IN_BUFFER; i++)
//        {
//        
//            SEGGER_RTT_printf(0, "%d\n", p_event->data.done.p_buffer[i]);
//            //SEGGER_RTT_printf(0, "ADC 7 ...\n");
//        }
//        m_adc_evt_counter++;

                int avg_sample = 0;
        int i;

        for (i = 0; i < SAMPLES_IN_BUFFER; i++)	
        {
              avg_sample += p_event->data.done.p_buffer[i]; // take N samples in a row
        }
        avg_sample /= i; // average all the samples out
        //SEGGER_RTT_printf(0, "Avg_sample: %d\r\n", avg_sample);

        adc_val = abs(avg_sample);
    }
}


void saadc_init(void)
{
    ret_code_t err_code;
    nrf_saadc_channel_config_t channel_2_config =
        NRF_DRV_SAADC_DEFAULT_CHANNEL_CONFIG_SE(NRF_SAADC_INPUT_AIN2);

    err_code = nrf_drv_saadc_init(NULL, saadc_callback);
    APP_ERROR_CHECK(err_code);

    channel_2_config.gain = NRF_SAADC_GAIN1_4;
    channel_2_config.reference = NRF_SAADC_REFERENCE_INTERNAL;

    err_code = nrf_drv_saadc_channel_init(0, &channel_2_config);
    APP_ERROR_CHECK(err_code);

    err_code = nrf_drv_saadc_buffer_convert(m_buffer_pool[0], SAMPLES_IN_BUFFER);
    APP_ERROR_CHECK(err_code);

    err_code = nrf_drv_saadc_buffer_convert(m_buffer_pool[1], SAMPLES_IN_BUFFER);
    APP_ERROR_CHECK(err_code);

}
//
//#include "ADC.h"
//#include "nrf_delay.h"
//#define ADC_SAMPLES_IN_BUFFER   1
//static nrf_saadc_value_t     m_buffer_pool[2][ADC_SAMPLES_IN_BUFFER];
////static nrf_saadc_value_t m_buffer[ADC_SAMPLES_IN_BUFFER];
//float VBATT                     = 0.0;
//uint16_t adc_val; 
///*
// 5, // AIN3 (P0.05)
// 2, // AIN0 (P0.02)
// VBAT = (127.0f/100.0f) * 3.30f * ((float)analogRead(VbatMon))/4095.0f; //actual battery voltage
// */
//
//void ADC_init(void)
//{
//    ret_code_t err_code;
//
//    nrf_drv_saadc_config_t saadc_config = NRF_DRV_SAADC_DEFAULT_CONFIG;
//    saadc_config.resolution = NRF_SAADC_RESOLUTION_12BIT;
//
////    nrf_saadc_channel_config_t channel_0_config =
////        NRF_DRV_SAADC_DEFAULT_CHANNEL_CONFIG_SE(NRF_SAADC_INPUT_AIN0);
////    channel_0_config.gain = NRF_SAADC_GAIN1_6;
////    channel_0_config.reference = NRF_SAADC_REFERENCE_INTERNAL;
////	
////    nrf_saadc_channel_config_t channel_1_config =
////        NRF_DRV_SAADC_DEFAULT_CHANNEL_CONFIG_SE(NRF_SAADC_INPUT_AIN1);
////    channel_1_config.gain = NRF_SAADC_GAIN1_6;
////    channel_1_config.reference = NRF_SAADC_REFERENCE_INTERNAL;
//	
//    nrf_saadc_channel_config_t channel_2_config =
//        NRF_DRV_SAADC_DEFAULT_CHANNEL_CONFIG_SE(NRF_SAADC_INPUT_AIN2);
//    channel_2_config.gain = NRF_SAADC_GAIN1_4;
//    channel_2_config.reference = NRF_SAADC_REFERENCE_INTERNAL;
//
//        err_code = nrf_drv_saadc_init(&saadc_config, ADC_callback);
//    APP_ERROR_CHECK(err_code);
//
////    err_code = nrf_drv_saadc_channel_init(0, &channel_0_config);
////    APP_ERROR_CHECK(err_code);
////    err_code = nrf_drv_saadc_channel_init(1, &channel_1_config);
////    APP_ERROR_CHECK(err_code);
//    err_code = nrf_drv_saadc_channel_init(2, &channel_2_config);
//    APP_ERROR_CHECK(err_code);
//
//    err_code = nrf_drv_saadc_buffer_convert(m_buffer_pool[0],ADC_SAMPLES_IN_BUFFER);
//    APP_ERROR_CHECK(err_code);   
//    err_code = nrf_drv_saadc_buffer_convert(m_buffer_pool[1],ADC_SAMPLES_IN_BUFFER);
//    APP_ERROR_CHECK(err_code);
//
////    //nrf_drv_saadc_config_t saadc_config;
////    nrf_saadc_channel_config_t channel_config =
////    NRF_DRV_SAADC_DEFAULT_CHANNEL_CONFIG_SE(NRF_SAADC_INPUT_AIN2);// was NRF_SAADC_INPUT_AIN2 for LMP
////
////
////
//////    nrf_saadc_config_t adc_config;
//////    adc_config.resolution       = NRF_SAADC_RESOLUTION_8BIT;
//////    adc_config.buffer           = m_buffer;
//////    adc_config.buffer_size      = ADC_SAMPLES_IN_BUFFER;
//////    adc_config.oversample       = ;
////  
////    //nrf_saadc_channel_config_t channel_0_config;
/////* Configure channel */
////channel_config.acq_time 	= NRF_SAADC_ACQTIME_40US;
////channel_config.burst 		= NRF_SAADC_BURST_ENABLED;
////channel_config.gain		= NRF_SAADC_GAIN1_6;
////channel_config.mode		= NRF_SAADC_MODE_SINGLE_ENDED;
////channel_config.pin_p		= NRF_SAADC_INPUT_VDD;
////channel_config.pin_n		= NRF_SAADC_INPUT_DISABLED;
////channel_config.reference	 = NRF_SAADC_REFERENCE_INTERNAL;
////channel_config.resistor_n	= NRF_SAADC_RESISTOR_DISABLED;
////channel_config.resistor_p  = NRF_SAADC_RESISTOR_DISABLED;
//// 
////    //channel_config.
////    //nrf_saadc_resolution_set( NRF_SAADC_RESOLUTION_8BIT );
////    //APP_ERROR_CHECK(err_code);
////    //NRF_SAADC_RESOLUTION_12BIT 
////
////    err_code = nrf_drv_saadc_init(NULL, ADC_callback);
////    APP_ERROR_CHECK(err_code);
////    
////    err_code = nrf_drv_saadc_channel_init(0, &channel_config);
////    APP_ERROR_CHECK(err_code);
////    
////    err_code = nrf_drv_saadc_buffer_convert(m_buffer_pool[0], ADC_SAMPLES_IN_BUFFER);
////    APP_ERROR_CHECK(err_code);
////
////    err_code = nrf_drv_saadc_buffer_convert(m_buffer_pool[1], ADC_SAMPLES_IN_BUFFER);
////    APP_ERROR_CHECK(err_code);
////    //SEGGER_RTT_printf(0, "adc done ...\n");
//}
//
//
//
//void ADC_callback(nrf_drv_saadc_evt_t const * p_event)
//{
//    if (p_event->type == NRF_DRV_SAADC_EVT_DONE)
//    {
//
//
//        ret_code_t err_code;
//        
//
//        err_code = nrf_drv_saadc_buffer_convert(p_event->data.done.p_buffer, ADC_SAMPLES_IN_BUFFER);
//        APP_ERROR_CHECK(err_code);
//
//
////                int avg_sample = 0;
////        int i;
////
////        for (i = 0; i < ADC_SAMPLES_IN_BUFFER; i++)	
////        {
////              avg_sample += p_event->data.done.p_buffer[i]; // take N samples in a row
////        }
////        avg_sample /= i; // average all the samples out
////        //SEGGER_RTT_printf(0, "Avg_sample: %d\r\n", avg_sample);
////
////        adc_val = abs(avg_sample);
//        
//        adc_val = abs(p_event->data.done.p_buffer[0]);
//        return_adc();
//        //VBATT           = ((float)p_event->data.done.p_buffer[3]) * 3.60f / 1024.0f;
//       
//        //SEGGER_RTT_printf(0, "ADC, %d\n ", p_event->data.done.p_buffer[0]);
//
//
//
//
//        //VBATT           = VBATT * (139.0f/100.0f) * 3.30f;
//        //batteryVoltage  = (uint16_t)(VBATT * 100.0f);
//    }
//}
//
int16_t return_adc( void )
{
    return adc_val;
}

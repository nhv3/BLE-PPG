#include <stdint.h>
#include <string.h>
#include "nrf_gpio.h"
#include "sensor_service.h"
#include "ble_srv_common.h"
#include "app_error.h"
#include "sensor_service.h"
#include <stdio.h>
#include "nrf_delay.h"
extern volatile BLE_CONNECTED;
extern uint16_t stream_service;
extern uint16_t prog_service;

// function for some housekeeping of ble connections related to the sensor service and characteristic
void ble_sensor_service_on_ble_evt(ble_evt_t const * p_ble_evt, void * p_context)
{
    // SENSOR_JOB: Step 3.D Implement switch case handling BLE events related to sensor service. 
		ble_os_t * p_sensor_service =(ble_os_t *) p_context;
		switch (p_ble_evt->header.evt_id)
{
    case BLE_GAP_EVT_CONNECTED:
        p_sensor_service->conn_handle = p_ble_evt->evt.gap_evt.conn_handle;
        BLE_CONNECTED = true; 

        break;
    case BLE_GAP_EVT_DISCONNECTED:
        p_sensor_service->conn_handle = BLE_CONN_HANDLE_INVALID;
        BLE_CONNECTED = false; 
        break;
    default:
        // No implementation needed.
        break;
}
		
}


/**@brief Function for adding sensor new characterstic to "Our service" that we initiated in the previous tutorial. 
 *
 * @param[in]   p_sensor_service        Our Service structure.
 *
 */
static uint32_t sensor_char1_add(ble_os_t * p_sensor_service)
{
    // SENSOR_JOB: Step 2.A, Add a custom characteristic UUID
		uint32_t            err_code;
		ble_uuid_t          char_uuid;
		ble_uuid128_t       base_uuid = BLE_UUID_SENSOR_BASE_UUID;
		char_uuid.uuid      = BLE_UUID_SENSOR_CHARAC1_UUID;
		err_code = sd_ble_uuid_vs_add(&base_uuid, &char_uuid.type);
		APP_ERROR_CHECK(err_code);  
    
    // SENSOR_JOB: Step 2.F Add read/write properties to sensor characteristic
    ble_gatts_char_md_t char_md;
    memset(&char_md, 0, sizeof(char_md));
		char_md.char_props.read = 1;
		char_md.char_props.write = 1;

    
    // SENSOR_JOB: Step 3.A, Configuring Client Characteristic Configuration Descriptor metadata and add to char_md structure
    ble_gatts_attr_md_t cccd_md;
    memset(&cccd_md, 0, sizeof(cccd_md));
		BLE_GAP_CONN_SEC_MODE_SET_OPEN(&cccd_md.read_perm);
		BLE_GAP_CONN_SEC_MODE_SET_OPEN(&cccd_md.write_perm);
		cccd_md.vloc                = BLE_GATTS_VLOC_STACK;    
		char_md.p_cccd_md           = &cccd_md;
		char_md.char_props.notify   = 1;

   
    
    // SENSOR_JOB: Step 2.B, Configure the attribute metadata
    ble_gatts_attr_md_t attr_md;
    memset(&attr_md, 0, sizeof(attr_md));  
		attr_md.vloc        = BLE_GATTS_VLOC_STACK;
    
    
    // SENSOR_JOB: Step 2.G, Set read/write security levels to sensor characteristic
    BLE_GAP_CONN_SEC_MODE_SET_OPEN(&attr_md.read_perm);
		BLE_GAP_CONN_SEC_MODE_SET_OPEN(&attr_md.write_perm);
    
    // SENSOR_JOB: Step 2.C, Configure the characteristic value attribute
    ble_gatts_attr_t    attr_char_value;
    memset(&attr_char_value, 0, sizeof(attr_char_value));
		attr_char_value.p_uuid      = &char_uuid;
		attr_char_value.p_attr_md   = &attr_md;
    
    // SENSOR_JOB: Step 2.H, Set characteristic length in number of bytes
		attr_char_value.max_len     = 2;
		attr_char_value.init_len    = 2;
		uint8_t value[2]            = {0x00,0x00};
		attr_char_value.p_value     = value;

    // SENSOR_JOB: Step 2.E, Add sensor new characteristic to the service
		err_code = sd_ble_gatts_characteristic_add(p_sensor_service->service_handle,
                                   &char_md,
                                   &attr_char_value,
                                   &p_sensor_service->char1_handles);
		APP_ERROR_CHECK(err_code);
    return NRF_SUCCESS;
}

// sensor 2

static uint32_t sensor_char2_add(ble_os_t * p_sensor_service)
{
    // SENSOR_JOB: Step 2.A, Add a custom characteristic UUID
		uint32_t            err_code;
		ble_uuid_t          char_uuid;
		ble_uuid128_t       base_uuid = BLE_UUID_SENSOR_BASE_UUID;
		char_uuid.uuid      = BLE_UUID_SENSOR_CHARAC2_UUID;
		err_code = sd_ble_uuid_vs_add(&base_uuid, &char_uuid.type);
		APP_ERROR_CHECK(err_code);  
    
    // SENSOR_JOB: Step 2.F Add read/write properties to sensor characteristic
    ble_gatts_char_md_t char_md;
    memset(&char_md, 0, sizeof(char_md));
		char_md.char_props.read = 1;
		char_md.char_props.write = 1;

    
    // SENSOR_JOB: Step 3.A, Configuring Client Characteristic Configuration Descriptor metadata and add to char_md structure
    ble_gatts_attr_md_t cccd_md;
    memset(&cccd_md, 0, sizeof(cccd_md));
		BLE_GAP_CONN_SEC_MODE_SET_OPEN(&cccd_md.read_perm);
		BLE_GAP_CONN_SEC_MODE_SET_OPEN(&cccd_md.write_perm);
		cccd_md.vloc                = BLE_GATTS_VLOC_STACK;    
		char_md.p_cccd_md           = &cccd_md;
		char_md.char_props.notify   = 1;

   
    
    // SENSOR_JOB: Step 2.B, Configure the attribute metadata
    ble_gatts_attr_md_t attr_md;
    memset(&attr_md, 0, sizeof(attr_md));  
		attr_md.vloc        = BLE_GATTS_VLOC_STACK;
    
    
    // SENSOR_JOB: Step 2.G, Set read/write security levels to sensor characteristic
    BLE_GAP_CONN_SEC_MODE_SET_OPEN(&attr_md.read_perm);
		BLE_GAP_CONN_SEC_MODE_SET_OPEN(&attr_md.write_perm);
    
    // SENSOR_JOB: Step 2.C, Configure the characteristic value attribute
    ble_gatts_attr_t    attr_char_value;
    memset(&attr_char_value, 0, sizeof(attr_char_value));
		attr_char_value.p_uuid      = &char_uuid;
		attr_char_value.p_attr_md   = &attr_md;
    
    // SENSOR_JOB: Step 2.H, Set characteristic length in number of bytes
		attr_char_value.max_len     =20;
		attr_char_value.init_len    = 20;
		uint8_t value[20]            = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
		attr_char_value.p_value     = value;

    // SENSOR_JOB: Step 2.E, Add sensor new characteristic to the service
		err_code = sd_ble_gatts_characteristic_add(p_sensor_service->service_handle,
                                   &char_md,
                                   &attr_char_value,
                                   &p_sensor_service->char2_handles);
		APP_ERROR_CHECK(err_code);
    return NRF_SUCCESS;
}

// sensor 3

static uint32_t sensor_char3_add(ble_os_t * p_sensor_service)
{
    // SENSOR_JOB: Step 2.A, Add a custom characteristic UUID
		uint32_t            err_code;
		ble_uuid_t          char_uuid;
		ble_uuid128_t       base_uuid = BLE_UUID_SENSOR_BASE_UUID;
		char_uuid.uuid      = BLE_UUID_SENSOR_CHARAC3_UUID;
		err_code = sd_ble_uuid_vs_add(&base_uuid, &char_uuid.type);
		APP_ERROR_CHECK(err_code);  
    
    // SENSOR_JOB: Step 2.F Add read/write properties to sensor characteristic
    ble_gatts_char_md_t char_md;
    memset(&char_md, 0, sizeof(char_md));
		char_md.char_props.read = 1;
		char_md.char_props.write = 1;

    
    // SENSOR_JOB: Step 3.A, Configuring Client Characteristic Configuration Descriptor metadata and add to char_md structure
    ble_gatts_attr_md_t cccd_md;
    memset(&cccd_md, 0, sizeof(cccd_md));
		BLE_GAP_CONN_SEC_MODE_SET_OPEN(&cccd_md.read_perm);
		BLE_GAP_CONN_SEC_MODE_SET_OPEN(&cccd_md.write_perm);
		cccd_md.vloc                = BLE_GATTS_VLOC_STACK;    
		char_md.p_cccd_md           = &cccd_md;
		char_md.char_props.notify   = 1;

   
    
    // SENSOR_JOB: Step 2.B, Configure the attribute metadata
    ble_gatts_attr_md_t attr_md;
    memset(&attr_md, 0, sizeof(attr_md));  
		attr_md.vloc        = BLE_GATTS_VLOC_STACK;
    
    
    // SENSOR_JOB: Step 2.G, Set read/write security levels to sensor characteristic
    BLE_GAP_CONN_SEC_MODE_SET_OPEN(&attr_md.read_perm);
		BLE_GAP_CONN_SEC_MODE_SET_OPEN(&attr_md.write_perm);
    
    // SENSOR_JOB: Step 2.C, Configure the characteristic value attribute
    ble_gatts_attr_t    attr_char_value;
    memset(&attr_char_value, 0, sizeof(attr_char_value));
		attr_char_value.p_uuid      = &char_uuid;
		attr_char_value.p_attr_md   = &attr_md;
    
    // SENSOR_JOB: Step 2.H, Set characteristic length in number of bytes
		attr_char_value.max_len     = 2;
		attr_char_value.init_len    = 2;
		uint8_t value[2]            = {0x00,0x00};
		attr_char_value.p_value     = value;

    // SENSOR_JOB: Step 2.E, Add sensor new characteristic to the service
		err_code = sd_ble_gatts_characteristic_add(p_sensor_service->service_handle,
                                   &char_md,
                                   &attr_char_value,
                                   &p_sensor_service->char3_handles);
		APP_ERROR_CHECK(err_code);
    return NRF_SUCCESS;
}
// sensor 4

static uint32_t sensor_char4_add(ble_os_t * p_sensor_service)
{
    // SENSOR_JOB: Step 2.A, Add a custom characteristic UUID
		uint32_t            err_code;
		ble_uuid_t          char_uuid;
		ble_uuid128_t       base_uuid = BLE_UUID_SENSOR_BASE_UUID;
		char_uuid.uuid      = BLE_UUID_SENSOR_CHARAC4_UUID;
		err_code = sd_ble_uuid_vs_add(&base_uuid, &char_uuid.type);
		APP_ERROR_CHECK(err_code);  
    
    // SENSOR_JOB: Step 2.F Add read/write properties to sensor characteristic
    ble_gatts_char_md_t char_md;
    memset(&char_md, 0, sizeof(char_md));
		char_md.char_props.read = 1;
		char_md.char_props.write = 1;

    
    // SENSOR_JOB: Step 3.A, Configuring Client Characteristic Configuration Descriptor metadata and add to char_md structure
    ble_gatts_attr_md_t cccd_md;
    memset(&cccd_md, 0, sizeof(cccd_md));
		BLE_GAP_CONN_SEC_MODE_SET_OPEN(&cccd_md.read_perm);
		BLE_GAP_CONN_SEC_MODE_SET_OPEN(&cccd_md.write_perm);
		cccd_md.vloc                = BLE_GATTS_VLOC_STACK;    
		char_md.p_cccd_md           = &cccd_md;
		char_md.char_props.notify   = 1;

   
    
    // SENSOR_JOB: Step 2.B, Configure the attribute metadata
    ble_gatts_attr_md_t attr_md;
    memset(&attr_md, 0, sizeof(attr_md));  
		attr_md.vloc        = BLE_GATTS_VLOC_STACK;
    
    
    // SENSOR_JOB: Step 2.G, Set read/write security levels to sensor characteristic
    BLE_GAP_CONN_SEC_MODE_SET_OPEN(&attr_md.read_perm);
		BLE_GAP_CONN_SEC_MODE_SET_OPEN(&attr_md.write_perm);
    
    // SENSOR_JOB: Step 2.C, Configure the characteristic value attribute
    ble_gatts_attr_t    attr_char_value;
    memset(&attr_char_value, 0, sizeof(attr_char_value));
		attr_char_value.p_uuid      = &char_uuid;
		attr_char_value.p_attr_md   = &attr_md;
    
    // SENSOR_JOB: Step 2.H, Set characteristic length in number of bytes
		attr_char_value.max_len     = 8;
		attr_char_value.init_len    = 2;
		uint8_t value[2]            = {0x00,0x00};
		attr_char_value.p_value     = value;

    // SENSOR_JOB: Step 2.E, Add sensor new characteristic to the service
		err_code = sd_ble_gatts_characteristic_add(p_sensor_service->service_handle,
                                   &char_md,
                                   &attr_char_value,
                                   &p_sensor_service->char4_handles);
		APP_ERROR_CHECK(err_code);
    return NRF_SUCCESS;
}

// sensor 5

static uint32_t sensor_char5_add(ble_os_t * p_sensor_service)
{
    // SENSOR_JOB: Step 2.A, Add a custom characteristic UUID
		uint32_t            err_code;
		ble_uuid_t          char_uuid;
		ble_uuid128_t       base_uuid = BLE_UUID_SENSOR_BASE_UUID;
		char_uuid.uuid      = BLE_UUID_SENSOR_CHARAC5_UUID;
		err_code = sd_ble_uuid_vs_add(&base_uuid, &char_uuid.type);
		APP_ERROR_CHECK(err_code);  
    
    // SENSOR_JOB: Step 2.F Add read/write properties to sensor characteristic
    ble_gatts_char_md_t char_md;
    memset(&char_md, 0, sizeof(char_md));
		char_md.char_props.read = 1;
		char_md.char_props.write = 1;

    
    // SENSOR_JOB: Step 3.A, Configuring Client Characteristic Configuration Descriptor metadata and add to char_md structure
    ble_gatts_attr_md_t cccd_md;
    memset(&cccd_md, 0, sizeof(cccd_md));
		BLE_GAP_CONN_SEC_MODE_SET_OPEN(&cccd_md.read_perm);
		BLE_GAP_CONN_SEC_MODE_SET_OPEN(&cccd_md.write_perm);
		cccd_md.vloc                = BLE_GATTS_VLOC_STACK;    
		char_md.p_cccd_md           = &cccd_md;
		char_md.char_props.notify   = 1;

   
    
    // SENSOR_JOB: Step 2.B, Configure the attribute metadata
    ble_gatts_attr_md_t attr_md;
    memset(&attr_md, 0, sizeof(attr_md));  
		attr_md.vloc        = BLE_GATTS_VLOC_STACK;
    
    
    // SENSOR_JOB: Step 2.G, Set read/write security levels to sensor characteristic
    BLE_GAP_CONN_SEC_MODE_SET_OPEN(&attr_md.read_perm);
		BLE_GAP_CONN_SEC_MODE_SET_OPEN(&attr_md.write_perm);
    
    // SENSOR_JOB: Step 2.C, Configure the characteristic value attribute
    ble_gatts_attr_t    attr_char_value;
    memset(&attr_char_value, 0, sizeof(attr_char_value));
		attr_char_value.p_uuid      = &char_uuid;
		attr_char_value.p_attr_md   = &attr_md;
    
    // SENSOR_JOB: Step 2.H, Set characteristic length in number of bytes
		attr_char_value.max_len     = 16;
		attr_char_value.init_len    = 16;
		uint8_t value[16]           = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
		attr_char_value.p_value     = value;

    // SENSOR_JOB: Step 2.E, Add sensor new characteristic to the service
		err_code = sd_ble_gatts_characteristic_add(p_sensor_service->service_handle,
                                   &char_md,
                                   &attr_char_value,
                                   &p_sensor_service->char5_handles);
		APP_ERROR_CHECK(err_code);
    return NRF_SUCCESS;
}

/**@brief Function for initiating sensor new service.
 *
 * @param[in]   p_sensor_service        Our Service structure.
 *
 */
void sensor_service_init(ble_os_t * p_sensor_service)
{
    uint32_t   err_code; // Variable to hold return codes from library and softdevice functions

    // FROM_SERVICE_TUTORIAL: Declare 16-bit service and 128-bit base UUIDs and add them to the BLE stack
    ble_uuid_t        service_uuid;
    ble_uuid128_t     base_uuid = BLE_UUID_SENSOR_BASE_UUID;
    service_uuid.uuid = BLE_UUID_SENSOR_SERVICE_UUID;
    err_code = sd_ble_uuid_vs_add(&base_uuid, &service_uuid.type);
    APP_ERROR_CHECK(err_code);    
    
    // SENSOR_JOB: Step 3.B, Set sensor service connection handle to default value. I.e. an invalid handle since we are not yet in a connection.
		p_sensor_service->conn_handle = BLE_CONN_HANDLE_INVALID;

    // FROM_SERVICE_TUTORIAL: Add sensor service
		err_code = sd_ble_gatts_service_add(BLE_GATTS_SRVC_TYPE_PRIMARY,
                                        &service_uuid,
                                        &p_sensor_service->service_handle);
    
    APP_ERROR_CHECK(err_code);
    
    // SENSOR_JOB: Call the function sensor_char_add() to add sensor new characteristic to the service. 
    sensor_char1_add(p_sensor_service);
    sensor_char2_add(p_sensor_service);
    sensor_char3_add(p_sensor_service);
    sensor_char4_add(p_sensor_service);
    sensor_char5_add(p_sensor_service);


    //Set up handle capture 
    stream_service = p_sensor_service->char2_handles.value_handle;
    prog_service = p_sensor_service->char3_handles.value_handle;

}

// ALREADY_DONE_FOR_YOU: Function to be called when updating characteristic value
void sensor1_characteristic_update(ble_os_t *p_sensor_service, int32_t *temp)
{
    // SENSOR_JOB: Step 3.E, Update characteristic value
		if (p_sensor_service->conn_handle != BLE_CONN_HANDLE_INVALID)
		{
				uint16_t               len = 2;
				ble_gatts_hvx_params_t hvx_params;
				memset(&hvx_params, 0, sizeof(hvx_params));

				hvx_params.handle = p_sensor_service->char1_handles.value_handle;
				hvx_params.type   = BLE_GATT_HVX_NOTIFICATION;
				hvx_params.offset = 0;
				hvx_params.p_len  = &len;
				hvx_params.p_data = (uint8_t*)temp;  

				sd_ble_gatts_hvx(p_sensor_service->conn_handle, &hvx_params);
		}

}

// Sensor 2

void sensor2_characteristic_update(ble_os_t *p_sensor_service, uint8_t *ch1)
{
    // SENSOR_JOB: Step 3.E, Update characteristic value
		if (p_sensor_service->conn_handle != BLE_CONN_HANDLE_INVALID)
		{
				uint16_t               len =20;
				ble_gatts_hvx_params_t hvx_params;
				memset(&hvx_params, 0, sizeof(hvx_params));

				hvx_params.handle = p_sensor_service->char2_handles.value_handle;
				hvx_params.type   = BLE_GATT_HVX_NOTIFICATION;
				hvx_params.offset = 0;
				hvx_params.p_len  = &len;
				hvx_params.p_data = ch1;  

				sd_ble_gatts_hvx(p_sensor_service->conn_handle, &hvx_params);
		}

}

// Sensor 3

void sensor3_characteristic_update(ble_os_t *p_sensor_service, uint8_t *ch2)
{
    // SENSOR_JOB: Step 3.E, Update characteristic value
		if (p_sensor_service->conn_handle != BLE_CONN_HANDLE_INVALID)
		{
				uint16_t               len = 8;
				ble_gatts_hvx_params_t hvx_params;
				memset(&hvx_params, 0, sizeof(hvx_params));

				hvx_params.handle = p_sensor_service->char3_handles.value_handle;
				hvx_params.type   = BLE_GATT_HVX_NOTIFICATION;
				hvx_params.offset = 0;
				hvx_params.p_len  = &len;
				hvx_params.p_data = ch2;  

				sd_ble_gatts_hvx(p_sensor_service->conn_handle, &hvx_params);
		}

}

// Sensor 4

void sensor4_characteristic_update(ble_os_t *p_sensor_service, uint8_t *ch3)
{
    // SENSOR_JOB: Step 3.E, Update characteristic value
		if (p_sensor_service->conn_handle != BLE_CONN_HANDLE_INVALID)
		{
				uint16_t               len = 8;
				ble_gatts_hvx_params_t hvx_params;
				memset(&hvx_params, 0, sizeof(hvx_params));

				hvx_params.handle = p_sensor_service->char4_handles.value_handle;
				hvx_params.type   = BLE_GATT_HVX_NOTIFICATION;
				hvx_params.offset = 0;
				hvx_params.p_len  = &len;
				hvx_params.p_data = ch3;  

				sd_ble_gatts_hvx(p_sensor_service->conn_handle, &hvx_params);
		}

}

// Sensor 5

void sensor5_characteristic_update(ble_os_t *p_sensor_service, int32_t *ch4)
{
    // SENSOR_JOB: Step 3.E, Update characteristic value
		if (p_sensor_service->conn_handle != BLE_CONN_HANDLE_INVALID)
		{
				uint16_t               len = 16;
				ble_gatts_hvx_params_t hvx_params;
				memset(&hvx_params, 0, sizeof(hvx_params));

				hvx_params.handle = p_sensor_service->char5_handles.value_handle;
				hvx_params.type   = BLE_GATT_HVX_NOTIFICATION;
				hvx_params.offset = 0;
				hvx_params.p_len  = &len;
				hvx_params.p_data = (uint8_t*)ch4;  

				sd_ble_gatts_hvx(p_sensor_service->conn_handle, &hvx_params);
		}

}


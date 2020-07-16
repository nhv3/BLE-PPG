#ifndef SENSOR_SERVICE_H__
#define SENSOR_SERVICE_H__

#include <stdint.h>
#include "ble.h"
#include "ble_srv_common.h"

// Defining 16-bit service and 128-bit base UUIDs
#define BLE_UUID_SENSOR_BASE_UUID             {{0x23, 0xD1, 0x13, 0xEF, 0x5F, 0x78, 0x23, 0x15, 0xDE, 0xEF, 0x12, 0x12, 0x00, 0x00, 0x00, 0x00}} // 128-bit base UUID
#define BLE_UUID_SERVICE_UUID          0xFFFF    // Just a random, but recognizable value
#define BLE_UUID_SENSOR_SERVICE_UUID          0xB001    // Just a random, but recognizable value

// Defining 16-bit characteristic UUID
#define BLE_UUID_SENSOR_CHARAC1_UUID          0xC001 // 
#define BLE_UUID_SENSOR_CHARAC2_UUID          0xC002 //
#define BLE_UUID_SENSOR_CHARAC3_UUID          0xC003 //
#define BLE_UUID_SENSOR_CHARAC4_UUID          0xC004 //
#define BLE_UUID_SENSOR_CHARAC5_UUID          0xC005 //

// This structure contains various status information for sensor service. 
// The name is based on the naming convention used in Nordics SDKs. 
// 'ble indicates that it is a Bluetooth Low Energy relevant structure and 
// os is short for Our Service). 
typedef struct
{
    uint16_t                    conn_handle;    /**< Handle of the current connection (as provided by the BLE stack, is BLE_CONN_HANDLE_INVALID if not in a connection).*/
    uint16_t                    service_handle; /**< Handle of Our Service (as provided by the BLE stack). */
    // SENSOR_JOB: Step 2.D, Add handles for the characteristic attributes to sensor struct
    ble_gatts_char_handles_t char1_handles;
    ble_gatts_char_handles_t char2_handles;
    ble_gatts_char_handles_t char3_handles;
    ble_gatts_char_handles_t char4_handles;
    ble_gatts_char_handles_t char5_handles;
}ble_os_t;

/**@brief Function for handling BLE Stack events related to sensor service and characteristic.
 *
 * @details Handles all events from the BLE stack of interest to Our Service.
 *
 * @param[in]   p_sensor_service       Our Service structure.
 * @param[in]   p_ble_evt  Event received from the BLE stack.
 */
void ble_sensor_service_on_ble_evt(ble_evt_t const * p_ble_evt, void * p_context);

/**@brief Function for initializing sensor new service.
 *
 * @param[in]   p_sensor_service       Pointer to Our Service structure.
 */
void sensor_service_init(ble_os_t * p_sensor_service);

/**@brief Function for updating and sending new characteristic values
 *
 * @details The application calls this function whenever sensor timer_timeout_handler triggers
 *
 * @param[in]   p_sensor_service                     Our Service structure.
 * @param[in]   characteristic_value     New characteristic value.
 */
void sensor1_characteristic_update(ble_os_t *p_sensor_service, uint8_t *temp);
void sensor2_characteristic_update(ble_os_t *p_sensor_service, uint8_t *ch1);
void sensor3_characteristic_update(ble_os_t *p_sensor_service, uint8_t *ch2);
void sensor4_characteristic_update(ble_os_t *p_sensor_service, uint8_t *ch3);
void sensor5_characteristic_update(ble_os_t *p_sensor_service, int32_t *ch4);

#endif  /* _ SENSOR_SERVICE_H__ */

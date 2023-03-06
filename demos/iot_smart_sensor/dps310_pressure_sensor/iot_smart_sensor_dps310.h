#ifndef _IOT_SMART_SENSOR_DPS310_H_
#define _IOT_SMART_SENSOR_DPS310_H_

#include "iot_smart_sensor_config.h"
#include "cyhal.h"
#include "stdint.h"

/* Parameters necessary for configuring i2c */
#define OVERSAMPLING            7
#define I2C_MASTER_FREQUENCY    1000000

cyhal_i2c_cfg_t i2c_master_config;

/* I2C master configuration */
/* Define the I2C master configuration structure */

cyhal_i2c_t mI2C;

/**
 * @brief Initializes the DPS310 pressure sensor and the required i2c connection.
 */
void smartSensorInitialization(void);

/**
 * @brief Reads a single temperature value from the sensor
 * @param[in] pointer for storing the temperature value
 * @ret 0 if success
 */
uint16_t readTemperature(float *temperaure_fp);

/**
 * @brief Reads a single pressure value from the sensor.
 * @param[in] pointer for storing the pressure value
 * @ret 0 if success
 */
uint16_t readPressure(float *pressure_fp);

#endif /* _IOT_SMART_SENSOR_DEMO_MQTT_H_ */

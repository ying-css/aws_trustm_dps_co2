#ifndef _IOT_SMART_SENSOR_CONFIG_H_
#define _IOT_SMART_SENSOR_CONFIG_H_

/* Enable/disable the sensor used for the smart sensor demo. Comment out to disable */
/* Enable dps310 smart sensor */
#define SMART_SENSOR_DPS310_EN

#ifdef SMART_SENSOR_DPS310_EN
#include "iot_smart_sensor_dps310.h"

/* I2C pins used for communicating with the dps310 sensor */
#define DPS_I2C_SCL P5_4
#define DPS_I2C_SDA P5_5

#endif /* SMART_SENSOR_DPS310_EN */

#endif /* _IOT_SMART_SENSOR_CONFIG_H_ */

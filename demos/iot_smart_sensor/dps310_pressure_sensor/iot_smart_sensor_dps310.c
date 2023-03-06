/******************************************************************************
* File Name: iot_smart_sensor_dps310.c
*
* Description: This is the source code for the DPS310 pressure sensor Application
*
* Related Document: See Readme.md
*
*******************************************************************************
* (c) 2020-2021, Cypress Semiconductor Corporation. All rights reserved.
*******************************************************************************
* This software, including source code, documentation and related materials
* ("Software"), is owned by Cypress Semiconductor Corporation or one of its
* subsidiaries ("Cypress") and is protected by and subject to worldwide patent
* protection (United States and foreign), United States copyright laws and
* international treaty provisions. Therefore, you may use this Software only
* as provided in the license agreement accompanying the software package from
* which you obtained this Software ("EULA").
*
* If no EULA applies, Cypress hereby grants you a personal, non-exclusive,
* non-transferable license to copy, modify, and compile the Software source
* code solely for use in connection with Cypress's integrated circuit products.
* Any reproduction, modification, translation, compilation, or representation
* of this Software except as specified above is prohibited without the express
* written permission of Cypress.
*
* Disclaimer: THIS SOFTWARE IS PROVIDED AS-IS, WITH NO WARRANTY OF ANY KIND,
* EXPRESS OR IMPLIED, INCLUDING, BUT NOT LIMITED TO, NONINFRINGEMENT, IMPLIED
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. Cypress
* reserves the right to make changes to the Software without notice. Cypress
* does not assume any liability arising out of the application or use of the
* Software or any product or circuit described in the Software. Cypress does
* not authorize its products for use in any products where a malfunction or
* failure of the Cypress product may reasonably be expected to result in
* significant property damage, injury or death ("High Risk Product"). By
* including Cypress's product in a High Risk Product, the manufacturer of such
* system or application assumes all risk of such use and in doing so agrees to
* indemnify Cypress against all liability.
*******************************************************************************/

#include "iot_smart_sensor_config.h"
#include "iot_smart_sensor_dps310.h"

/**/
#include "FreeRTOS.h"

/* DPS310 library */
#include "dps310.h"

/* Includes needed for the dps310 library */
#include "cy_pdl.h"
#include "cyhal.h"
#include "cybsp.h"
#include "cy_retarget_io.h"

//#define CYHAL_I2C_MODE_MASTER (false)

void smartSensorInitialization(void)
{
    //const cyhal_clock_divider_t mClockDiv;
    cy_rslt_t result;

    // set the i2c master configuration
    // i2c_master_config = {false, 0, I2C_MASTER_FREQUENCY};
    i2c_master_config.is_slave = false;
    i2c_master_config.address = 0;
    i2c_master_config.frequencyhal_hz = I2C_MASTER_FREQUENCY;

    /* Initialize the I2C */
    result = cyhal_i2c_init(&mI2C, DPS_I2C_SDA, DPS_I2C_SCL, NULL);
    if (result != CY_RSLT_SUCCESS)
    {
    	configPRINTF( (  "i2c initialization failed \r\n" ) );
    }

    /* Configure the I2C resource to be master */
    result = cyhal_i2c_configure(&mI2C, &i2c_master_config);
    if (result != CY_RSLT_SUCCESS)
    {
    	configPRINTF( ( "Failed to configure I2C \r\n" ) );
    }

    /* Print message to the console */
    //configPRINTF( ( "Initializing DPS310 Pressure sensor\r\n" ) );

    /* Initialize the pressure sensor */
    DPS310_init(&mI2C);

    configPRINTF( ( "Sensor Initialization Complete\r\n" ) );
}

uint16_t readTemperature(float *temperaure_fp)
{
	uint16_t ret;

	/* Lets the DPS310 perform a single temperature measurement with the last (or standard) configuration
	 * The result will be written to the parameter temperature
	 * Oversampling can be a value from 0 to 7
	 * The DPS310 will perform 2^oversampling internal temperature measurements and combine them to one result with higher precision
	 * measurements. Higher precision takes more time. Consult datasheet for more information.
	 */
	ret = DPS310_measureTempOnce_oversample(temperaure_fp, OVERSAMPLING);
	if (ret != 0)
	{
		configPRINTF( ( "Failed to read temperature data from sensor\r\n" ) );
	}
	else
	{
		configPRINTF( ( "Temperature: %f degree Celsius\r\n", *temperaure_fp ) );
	}

	return ret;
}

uint16_t readPressure(float *pressure_fp)
{
	uint16_t ret;

	/* Pressure measurement behaves similar to temperature measurement */
	ret = DPS310_measurePressureOnce_oversample(pressure_fp, OVERSAMPLING);
	if (ret != 0)
	{
		configPRINTF( ( "Failed to read pressure data from sensor\r\n" ) );
	}
	else
	{
		configPRINTF( ( "Pressure: %f Pascal\r\n", *pressure_fp ) );
	}

	return ret;
}

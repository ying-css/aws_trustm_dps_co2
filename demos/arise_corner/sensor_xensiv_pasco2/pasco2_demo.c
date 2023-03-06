/*
 * pasco2_demo.c
 *
 *  Created on: 23-Sep-2021
 *      Author: Narayanaswam
 */
/*****************************************************************************
** File name: pasco2_demo.c
**
** Description: This file uses PASCO2 library APIs to demonstrate the use of
** CO2 sensor.
**
** ===========================================================================
** Copyright (C) 2021 Infineon Technologies AG. All rights reserved.
** ===========================================================================
**
** ===========================================================================
** Infineon Technologies AG (INFINEON) is supplying this file for use
** exclusively with Infineon's sensor products. This file can be freely
** distributed within development tools and software supporting such
** products.
**
** THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
** OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
** MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
** INFINEON SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR DIRECT, INDIRECT,
** INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES, FOR ANY REASON
** WHATSOEVER.
** ===========================================================================
*/

/* Header file from system */
#include <stdio.h>

/* Header file includes */
#include "cybsp.h"
#include "cyhal.h"

/* Header file for local task */
#include "pasco2_demo.h"

/* Header file for the pasco2 library */
#include "mtb_pasco2.h"

/**/
#include "FreeRTOSConfig.h"

/* Output pin for sensor PSEL line */
#define MTB_PASCO2_PSEL (P5_3)
/* Pin state to enable I2C channel of sensor */
#define MTB_PASCO2_PSEL_I2C_ENABLE (0U)
/* Output pin for PAS CO2 Wing Board power switch */
#define MTB_PASCO2_POWER_SWITCH (P10_5)
/* Pin state to enable power to sensor on PAS CO2 Wing Board*/
#define MTB_PASCO2_POWER_ON (1U)

/* Output pin for PAS CO2 Wing Board LED OK */
#define MTB_PASCO2_LED_OK (P6_2)//(P9_0)
/* Output pin for PAS CO2 Wing Board LED WARNING  */
#define MTB_PASCO2_LED_WARNING (P6_3)//(P9_1)

/* I2C SCL pin used for the i2c communication with the sensor */
#define PASCO2_I2C_SCL_PIN  (P9_0)
/* I2C SDA pin used for the i2c communication with the sensor */
#define PASCO2_I2C_SDA_PIN (P9_1)

/* Pin state for PAS CO2 Wing Board LED off. */
#define MTB_PASCO_LED_STATE_OFF (0U)
/* Pin state for PAS CO2 Wing Board LED on. */
#define MTB_PASCO_LED_STATE_ON (1U)

/* I2C bus frequency */
#define I2C_MASTER_FREQUENCY (100000U)
/*******************************************************************************
 * Global Variables
 ******************************************************************************/

/* I2C variables */
cyhal_i2c_t cyhal_i2c_co2;
/* initialize i2c library*/
cyhal_i2c_cfg_t i2c_master_config_co2 = {false,
                                     0,
                                     I2C_MASTER_FREQUENCY};

/* CO2 driver context */
mtb_pasco2_context_t mtb_pasco2_context;

/*******************************************************************************
 * Function Name: pasco2_init
 *******************************************************************************
 * Summary:
 *   Initializes context object of PASCO2 library, sets default parameters values
 *   for sensor and continuously acquire data from sensor.
 *
 * Parameters:
 *   arg: thread
 *
 * Return:
 *   none
 *******************************************************************************/
void pasco2_init(void)
{
    cy_rslt_t result;

    result = cyhal_i2c_init(&cyhal_i2c_co2, PASCO2_I2C_SDA_PIN, PASCO2_I2C_SCL_PIN, NULL);
    if (result != CY_RSLT_SUCCESS)
    {
        //configPRINTF( ( "CO2 i2c init(1) failed\r\n" ) );
        CY_ASSERT(0);
    }
//    else if (result == CY_RSLT_SUCCESS)
//    {
//    	configPRINTF( ( "CO2 i2c init(1) successful\r\n" ) );
//    }
    result = cyhal_i2c_configure(&cyhal_i2c_co2, &i2c_master_config_co2);
    if (result != CY_RSLT_SUCCESS)
    {
        //configPRINTF( ( "CO2 i2c configure(2) failed\r\n" ) );
        CY_ASSERT(0);
    }
//    else if (result == CY_RSLT_SUCCESS)
//    {
//    	configPRINTF( ( "CO2 i2c configure(2) successful\r\n" ) );
//    }

    cyhal_system_delay_ms( 5000 );

    /* Initialize PAS CO2 sensor with default parameter values */
    result = mtb_pasco2_init(&mtb_pasco2_context, &cyhal_i2c_co2);
    if (result != CY_RSLT_SUCCESS)
    {
        /* Sensor gave a warning regarding over-voltage, temperature, or communication problem */
        switch (CY_RSLT_GET_CODE(result))
        {
            case MTB_PASCO2_SENSOR_NOT_FOUND:
                /*  */
            	configPRINTF( ("PAS CO2 Wing Board not found\r\n") );
                break;
            case MTB_PASCO2_SENSOR_NOT_READY:
            	/* Sensor is nor ready */
            	configPRINTF( ("CO2 Sensor is not ready\r\n") );
            	break;
            case MTB_PASCO2_CONFIGURATION_ERROR:
            	/* The configuration for the co2 sensor is not correct */
            	configPRINTF( ("CO2 Sensor configuration Error\r\n") );
            	break;
            default:
            	configPRINTF( ("An unexpected occurred during initialization of CO2 sensor\r\n") );
                break;
        }
        CY_ASSERT(0);
    }
    else
    {
    	configPRINTF( ("CO2 Sensor init successful\r\n") );
    }
}

/*******************************************************************************
 * Function Name: pasco2_get_ppm
 *******************************************************************************
 * Summary:
 *   Initializes context object of PASCO2 library, sets default parameters values
 *   for sensor and continuously acquire data from sensor.
 *
 * Parameters:
 *   arg: thread
 *
 * Return:
 *   none
 *******************************************************************************/
void pasco2_get_ppm(uint16_t *co2_ppm)
{
	cy_rslt_t result;

    /* Read CO2 value from sensor */
    result = mtb_pasco2_get_ppm(&mtb_pasco2_context, co2_ppm);

    if (result == CY_RSLT_SUCCESS)
    {
        /* New CO2 value is successfully read from sensor and print it to serial console */
        configPRINTF( ( "CO2 PPM Level: %d\r\n", *co2_ppm ) );
    }
    else if (CY_RSLT_GET_TYPE(result) == CY_RSLT_TYPE_INFO)
    {
        /* Sensor gave other information than CO2 value */
        if (CY_RSLT_GET_CODE(result) == MTB_PASCO2_PPM_PENDING)
        {
            /* New value is not available yet */
        	configPRINTF( ("CO2 PPM value is not ready\r\n") );
        }
        else if (CY_RSLT_GET_CODE(result) == MTB_PASCO2_SENSOR_BUSY)
        {
            /* Sensor is busy in internal processing */
        	configPRINTF( ("CO2 sensor is busy\r\n") );
        }
        else
        {
        	configPRINTF( ("An unexpected occurred when accessing the CO2 sensor\r\n") );
        }
    }
    else if (CY_RSLT_GET_TYPE(result) == CY_RSLT_TYPE_WARNING)
    {
        /* Sensor gave a warning regarding over-voltage, temperature, or communication problem */
        switch (CY_RSLT_GET_CODE(result))
        {
            case MTB_PASCO2_VOLTAGE_ERROR:
                /* Sensor detected over-voltage problem */
            	configPRINTF( ("CO2 Sensor Over-Voltage Error\r\n") );
                break;
            case MTB_PASCO2_TEMPERATURE_ERROR:
                /* Sensor detected temperature problem */
            	configPRINTF( ("CO2 Sensor Temperature Error\r\n") );
                break;
            case MTB_PASCO2_COMMUNICATION_ERROR:
                /* Sensor detected communication problem with MCU */
            	configPRINTF( ("CO2 Sensor Communication Error\r\n") );
                break;
            default:
            	configPRINTF( ("Unexpected error\r\n") );
                break;
        }
    }
}



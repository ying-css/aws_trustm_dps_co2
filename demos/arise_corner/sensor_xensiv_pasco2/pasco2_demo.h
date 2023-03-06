/*
 * pasco2_demo.h
 *
 *  Created on: 23-Sep-2021
 *      Author: Narayanaswam
 */

#ifndef PASCO2_DEMO_H_
#define PASCO2_DEMO_H_

/******************************************************************************
** File Name:   pasco2_task.h
**
** Description: This file contains the function prototypes and constants used
**   in pasco2_task.c.
**
** Related Document: See README.md
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

#pragma once

/* Header file includes */
#include "cyabs_rtos.h"
#include "cycfg.h"

/* Header file for library */
#include "mtb_pasco2.h"

/*******************************************************************************
 * Macros
 ******************************************************************************/

/* I2C SCL pin used by the pas co2 sensor */
//#define PASCO2_I2C_SCL_PIN (P9_0)
/* I2C SDA pin used by the pas co2 sensor */
//#define PASCO2_I2C_SDA_PIN (P9_1)

/*******************************************************************************
 * Global Variables
 *******************************************************************************/
extern mtb_pasco2_context_t mtb_pasco2_context;

/*******************************************************************************
 * Functions
 *******************************************************************************/

/**
 * @brief Initializes the pas co2 sensor and the required i2c channel for communication.
 */
void pasco2_init(void);

/**
 * @brief Reads a single temperature value from the sensor
 * @param[in] pointer for storing the temperature value
 * @ret 0 if success
 */
void pasco2_get_ppm(uint16_t *co2_ppm);

#endif /* PASCO2_DEMO_H_ */

/**
 * @file        bgt60_pal_mtb.h
 * @author      Infineon Technologies AG
 * @brief       Radar BGT60 PSoC 6 PAL Implementation 
 * @copyright   Copyright (c) 2021 Infineon Technologies AG
 *
 * SPDX-License-Identifier: MIT
 */
#ifndef BGT60_PAL_MTB_H_
#define BGT60_PAL_MTB_H_

#include <stdint.h>
#include "cyhal.h"
#include "cybsp.h"
#include "xensiv_bgt60_types.h"

/**
 * @brief Structure for GPIO pins
 */
typedef struct 
{
    cyhal_gpio_t pin_target;                                         /**< reads the target */
    cyhal_gpio_t pin_phase;                                          /**< reads the phase  */
}mtb_bgt60_gpio_t;

/**
 * @brief       Initialize the PSoC6 GPIO
 * @return      GPIO error code
 * @retval      OK if success
 * @retval      ERROR if Initialization error
 */
xensiv_bgt60_error_t mtb_bgt60_gpio_init(mtb_bgt60_gpio_t *obj, cyhal_gpio_t pin_phase, cyhal_gpio_t pin_target);

/**
 * @brief       Deinitializes the PSoC6 GPIO
 * @return      GPIO error code
 * @retval      OK if success
 * @retval      ERROR if Deinitialization error
 */
xensiv_bgt60_error_t mtb_bgt60_gpio_deinit(mtb_bgt60_gpio_t *obj);

/**
 * @brief       Reads the PSoC6 GPIO voltage level
 * @return      GPIO voltage level
 * @retval      GPIO_LOW if voltage low
 * @retval      GPIO_HIGH if voltage high
 */
xensiv_gpio_level_t mtb_bgt60_phase_read(const void *ctx);

/**
 * @brief       Reads the PS0C6 GPIO voltage level
 * @return      GPIO voltage level
 * @retval      GPIO_LOW if voltage low
 * @retval      GPIO_HIGH if voltage high
 */
xensiv_gpio_level_t mtb_bgt60_target_read(const void *ctx);

/**
 * @brief       Delay in milliseconds
 * @param[in]   ms - Delay time in milliseconds 
 * @return      void 
 */ 
void mtb_bgt60_delay(uint32_t ms);

#endif /*BGT60_PAL_MTB_H_*/
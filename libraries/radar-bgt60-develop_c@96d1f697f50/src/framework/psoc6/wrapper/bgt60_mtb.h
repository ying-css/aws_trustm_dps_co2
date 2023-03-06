/**
 * @file        bgt60_mtb.h
 * @author      Infineon Technologies AG
 * @brief       Radar BGT60 PSoC 6 API
 * @copyright   Copyright (c) 2021 Infineon Technologies AG
 *
 * SPDX-License-Identifier: MIT
 */
#ifndef BGT60_MTB_H_
#define BGT60_MTB_H_

#include <stdint.h>
#include "xensiv_bgt60_types.h"
#include "bgt60_pal_mtb.h"

typedef  xensiv_bgt60_motion_t    motion_t;
typedef  xensiv_bgt60_direction_t direction_t;
typedef  xensiv_bgt60_error_t     error_t;

/**
 * @brief BGT60 radar object including PSoC6 HAL specialization
 */
typedef struct 
{
    xensiv_bgt60_t radar;
    mtb_bgt60_gpio_t pal_gpio;
}mtb_bgt60_t;

/**
 * @brief           Initialize the PSoC 6 GPIO for target and phase detection
 * @param[in]       obj Pointer to radar BGT60 object
 * @param[in]       target_det Pin number of the target detect pin
 * @param[in]       phase_det Pin number of the phase detect pin
 * @return          BGT60 error code
 * @retval          OK always
 */
error_t     mtb_bgt60_init(mtb_bgt60_t* obj, cyhal_gpio_t phase_det, cyhal_gpio_t target_det);

/**
 * @brief           De-Initialize the PSoC 6 GPIO for target and phase detection
 * @param[in]       obj Pointer to radar BGT60 object
 * @retval          OK always
 */
error_t     mtb_bgt60_deinit(mtb_bgt60_t* obj);

/**
 * @brief           Read out target-detect-pin
 * @param[in]       obj Pointer to radar BGT60 object
 * @param[in,out]   motion This variable stores the actual state of the target-detect-pin
 *                  Possible Values:
 *                      - NO_MOTION
 *                      - MOTION
 *
 * @return          BGT60 error code
 * @retval          OK always
 */
error_t     mtb_bgt60_get_motion(mtb_bgt60_t* obj, motion_t* motion);

/**
 * @brief           Read out phase-detect-pin
 * @param[in]       obj Pointer to radar BGT60 object
 * @param[in,out]   direction This variable stores the actual state of the phase-detect-pin
 *                  Possible Values:
 *                      - NO_DIR
 *                      - APPROACHING
 *                      - DEPARTING
 * @return          BGT60 error code
 * @retval          OK always
 */
error_t     mtb_bgt60_get_direction(mtb_bgt60_t* obj, direction_t* direction);

#endif /** BGT60_MTB_H_ **/
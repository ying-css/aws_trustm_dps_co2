/**
 * @file        xensiv_bgt60.h
 * @author      Infineon Technologies AG
 * @brief       Radar BGT60 API
 * @copyright   Copyright (c) 2021 Infineon Technologies AG
 *
 * SPDX-License-Identifier: MIT
 */

#include <stddef.h>
#include "xensiv_bgt60.h"

#ifndef XENSIV_BGT60_ASSERT
#include <assert.h>
#define XENSIV_BGT60_ASSERT(c)             assert(c)
#endif

/**
 * @brief       Reads out target detect radar output
 * @param[in]   dev bgt60 device handle
 * @return      motion_t
 * @retval      MOTION if motion detected
 * @retval      NO_MOTION if no motion detected
 */
xensiv_bgt60_motion_t xensiv_bgt60_get_motion(xensiv_bgt60_t * dev)
{
    xensiv_bgt60_motion_t m;

    XENSIV_BGT60_ASSERT(NULL != dev);

    xensiv_gpio_level_t level = dev->td_read(dev->ctx);

    if(GPIO_LEVEL_LOW == level)
    {
        m = MOTION;
    }
    else if(GPIO_LEVEL_HIGH == level)
    {
        m = NO_MOTION;
    }

    return m;
}

/**
 * @brief       Reads out phase detect radar output
 * @param[in]   dev bgt60 device handle
 * @return      direction_t
 * @retval      APPROACHING if target is approaching to the sensor
 * @retval      DEPARTING if target is departing from the sensor
 * @retval      NO_DIR if no motion detected
 */
xensiv_bgt60_direction_t xensiv_bgt60_get_direction(xensiv_bgt60_t * dev)
{
    xensiv_bgt60_direction_t d = NO_DIR;

    XENSIV_BGT60_ASSERT(NULL != dev);

    xensiv_bgt60_motion_t m = xensiv_bgt60_get_motion(dev);

    if(MOTION == m)
    {
        xensiv_gpio_level_t level = dev->pd_read(dev->ctx);

        if(GPIO_LEVEL_LOW == level)
        {
            d = DEPARTING;
        }
        else if(GPIO_LEVEL_HIGH== level)
        {
            d = APPROACHING;
        }
    }

    return d;
}
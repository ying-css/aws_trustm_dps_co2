/**
 * @file        bgt60_mtb.c
 * @author      Infineon Technologies AG
 * @brief       Radar BGT60 PSoC 6 API
 * @copyright   Copyright (c) 2021 Infineon Technologies AG
 *
 * SPDX-License-Identifier: MIT
 */
#include "bgt60_mtb.h"
#include "xensiv_bgt60.h"

error_t  mtb_bgt60_init(mtb_bgt60_t* obj, cyhal_gpio_t phase_det, cyhal_gpio_t target_det)
{
    error_t error;

    obj->radar.spi_transfer = NULL; 
    obj->radar.pd_read = &mtb_bgt60_phase_read;
    obj->radar.td_read = &mtb_bgt60_target_read;
    obj->radar.delay   = &mtb_bgt60_delay;
    obj->radar.ctx    = &(obj->pal_gpio);

    error = mtb_bgt60_gpio_init(&(obj->pal_gpio), phase_det, target_det);
    if(error != OK)
    {
        return INTF_ERROR;
    }

    return OK;
}

error_t  mtb_bgt60_get_motion(mtb_bgt60_t* obj, motion_t* motion)
{
    *motion = xensiv_bgt60_get_motion(&(obj->radar));
    return OK;
}

error_t  mtb_bgt60_get_direction(mtb_bgt60_t* obj, direction_t* direction)
{
    *direction = xensiv_bgt60_get_direction(&(obj->radar));
    return OK;
}

error_t  mtb_bgt60_deinit(mtb_bgt60_t* obj)
{
    return mtb_bgt60_gpio_deinit(&(obj->pal_gpio));
}
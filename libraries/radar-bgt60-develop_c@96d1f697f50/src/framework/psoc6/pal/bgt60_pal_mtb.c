/**
 * @file        bgt60_pal_mtb.c
 * @author      Infineon Technologies AG
 * @brief       Radar BGT60 PSoC 6 PAL Implementation
 * @copyright   Copyright (c) 2020-2021 Infineon Technologies AG
 *
 * SPDX-License-Identifier: MIT
 */
#include "bgt60_pal_mtb.h"

void mtb_bgt60_delay(uint32_t ms)
{
    cyhal_system_delay_ms(ms);
}

xensiv_bgt60_error_t mtb_bgt60_gpio_init(mtb_bgt60_gpio_t *obj, cyhal_gpio_t pin_phase, cyhal_gpio_t pin_target)
{
    cy_rslt_t result = CY_RSLT_SUCCESS;
    result = cyhal_gpio_init(pin_phase, CYHAL_GPIO_DIR_INPUT, CYHAL_GPIO_DRIVE_NONE, 0u);
    if (result == CY_RSLT_SUCCESS)
    {
        obj->pin_phase = pin_phase;
    }
    else
        return INTF_ERROR; /**Return Interface error**/

    result = cyhal_gpio_init(pin_target, CYHAL_GPIO_DIR_INPUT, CYHAL_GPIO_DRIVE_NONE, 0u);
    if (result == CY_RSLT_SUCCESS)
    {
        obj->pin_target = pin_target;
    }
    else
        return INTF_ERROR; /**Return Interface error**/

    return OK;
}

xensiv_gpio_level_t mtb_bgt60_phase_read(const void *ctx)
{
    mtb_bgt60_gpio_t *mtb_bgt60_context = (mtb_bgt60_gpio_t *)ctx;
    return (xensiv_gpio_level_t)cyhal_gpio_read(mtb_bgt60_context->pin_phase);
}

xensiv_gpio_level_t mtb_bgt60_target_read(const void *ctx)
{
    mtb_bgt60_gpio_t *mtb_bgt60_context = (mtb_bgt60_gpio_t *)ctx;
    return (xensiv_gpio_level_t)cyhal_gpio_read(mtb_bgt60_context->pin_target);
}

xensiv_bgt60_error_t mtb_bgt60_gpio_deinit(mtb_bgt60_gpio_t *obj)
{
    cyhal_gpio_free(obj->pin_phase);
    cyhal_gpio_free(obj->pin_target);
    return OK;
}
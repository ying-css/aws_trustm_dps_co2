/**
 * @file        xensiv_bgt60.h
 * @author      Infineon Technologies AG
 * @brief       Radar BGT60 API
 * @copyright   Copyright (c) 2021 Infineon Technologies AG
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef XENSIV_BGT60_H_
#define XENSIV_BGT60_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "xensiv_bgt60_types.h"

/**
 * \addtogroup bgt60api
 * @{
 */

xensiv_bgt60_motion_t    xensiv_bgt60_get_motion     (xensiv_bgt60_t * dev);

xensiv_bgt60_direction_t xensiv_bgt60_get_direction  (xensiv_bgt60_t * dev);

/** @} */

#ifdef __cplusplus
}
#endif

#endif /** XENSIV_BGT60_H_ **/

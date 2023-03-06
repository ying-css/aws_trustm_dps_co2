/**
 * @file        xensiv_bgt60_types.h
 * @author      Infineon Technologies AG
 * @brief       Radar BGT60 types 
 * @copyright   Copyright (c) 2021 Infineon Technologies AG
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef XENSIV_BGT60_TYPES_H_
#define XENSIV_BGT60_TYPES_H_

#include <stdint.h>

/**
 * @addtogroup bgt60api
 * @{
 */

/**
 * @brief States of motion
 */
typedef enum 
{
    NO_MOTION       = 1,        /**< No presence */
    MOTION          = 2         /**< Presence */
}xensiv_bgt60_motion_t;

/**
 * @brief States of direction
 */
typedef enum 
{
    NO_DIR          = 0,        /**< No direction due to no motion */
    APPROACHING     = 1,        /**< Target approaching */
    DEPARTING       = 2         /**< Target departing */
}xensiv_bgt60_direction_t;

/**
 * @brief Error codes
 */
typedef enum
{
    OK              =  0,       /**< No error */
    INTF_ERROR      = -1,       /**< Interface error */
    CONF_ERROR      = -2,       /**< Configuration error */
    READ_ERROR      = -3,       /**< Read error */
    WRITE_ERROR     = -4,       /**< Write error */
}xensiv_bgt60_error_t;

/**
 * @brief GPIO logic levels
 */
typedef enum 
{
    GPIO_LEVEL_LOW  = 0,        /**< Level low */
    GPIO_LEVEL_HIGH = 1         /**< Level high */
}xensiv_gpio_level_t;

/**
 * @brief SPI Reset types
 */
typedef enum 
{
  XENSIV_BGT60_RESET_SW   = 0x000002,   
  XENSIV_BGT60_RESET_FSM  = 0x000004, 
  XENSIV_BGT60_RESET_FIFO = 0x000008,
} xensiv_bgt60_reset_t;

/** @} */

/**
 * @brief Platform abstraction layer
 * @addtogroup pal
 * @{
 */

/**
 * @brief       Reads phase detect output HAL function pointer
 * @param[in]   ctx PAL context
 * @return      gpio_level_t 
 */
typedef xensiv_gpio_level_t (*xensiv_bgt60_pd_read_t)(const void * ctx);

/**
 * @brief       Reads target detect output HAL function pointer
 * @param[in]   ctx PAL context
 * @return      gpio_level_t 
 */
typedef xensiv_gpio_level_t (*xensiv_bgt60_td_read_t)(const void * ctx);

/**
 * @brief       SPI transfer HAL function pointer
 * @param[in]   ctx         PAL context
 * @param[in]   tx_data     Transmit data
 * @param[out]  rx_data     Receive data
 * @param[in]   bytes       Number of bytes to be transfered
 * @return      Radar status
 */
typedef int32_t (*xensiv_bgt60_spi_transfer_t)(const void * ctx, const uint8_t * tx_data, uint8_t * rx_data, uint32_t bytes);

/**
 * @brief       Delay in milliseconds HAL function pointer
 * @param[in]   ms  Delay time in milliseconds 
 * @return      void 
 */ 
typedef void (*xensiv_bgt60_delay_t)(uint32_t ms);

 /** @} */

 /**
 * @addtogroup bgt60api
 * @{
 */

/**
 * @brief BGT60 device handle
 */
typedef struct xensiv_bgt60
{
    xensiv_bgt60_spi_transfer_t spi_transfer;   /**< SPI transfer function pointer */
    xensiv_bgt60_pd_read_t pd_read;             /**< Read phase-detect function pointer */
    xensiv_bgt60_td_read_t td_read;             /**< Read target-detect function pointer */
    xensiv_bgt60_delay_t delay;                 /**< Delay milliseconds function pointer */
    const void * ctx;                           /**< PAL context */
} xensiv_bgt60_t;

/** @} */

#endif /** XENSIV_BGT60_TYPES_H_ **/
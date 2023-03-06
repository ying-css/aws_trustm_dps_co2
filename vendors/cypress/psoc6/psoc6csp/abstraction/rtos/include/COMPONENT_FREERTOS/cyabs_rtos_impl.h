/***************************************************************************//**
* \file cyabs_rtos_impl.h
*
* \brief
* Internal definitions for RTOS abstraction layer
*
********************************************************************************
* \copyright
* Copyright 2019 Cypress Semiconductor Corporation
* SPDX-License-Identifier: Apache-2.0
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/

#ifndef INCLUDED_CYABS_RTOS_IMPL_H_
#define INCLUDED_CYABS_RTOS_IMPL_H_

#include <FreeRTOS.h>
#include <semphr.h>
#include <task.h>
#include <event_groups.h>
#include <timers.h>

#ifdef __cplusplus
extern "C" {
#endif

/******************************************************
*                 Constants
******************************************************/
#define CY_RTOS_MIN_STACK_SIZE      300                     /** Minimum stack size */
#define CY_RTOS_ALIGNMENT           0x00000008UL            /** Minimum alignment for RTOS objects */
#define CY_RTOS_ALIGNMENT_MASK      0x00000007UL            /** Mask for checking the alignement of crated RTOS objects */

/******************************************************
*                   Enumerations
******************************************************/

typedef enum cy_thread_priority
{
    CY_RTOS_PRIORITY_MIN = 0,
    CY_RTOS_PRIORITY_LOW = (configMAX_PRIORITIES / 7) * 1,
    CY_RTOS_PRIORITY_BELOWNORMAL = (configMAX_PRIORITIES / 7) * 2,
    CY_RTOS_PRIORITY_NORMAL = (configMAX_PRIORITIES / 7) * 3,
    CY_RTOS_PRIORITY_ABOVENORMAL = (configMAX_PRIORITIES / 7) * 4,
    CY_RTOS_PRIORITY_HIGH = (configMAX_PRIORITIES / 7) * 5,
    CY_RTOS_PRIORITY_REALTIME = (configMAX_PRIORITIES / 7) * 6,
    CY_RTOS_PRIORITY_MAX = configMAX_PRIORITIES - 1,
} cy_thread_priority_t;

/******************************************************
*                 Type Definitions
******************************************************/

typedef QueueHandle_t cy_queue_t;
typedef SemaphoreHandle_t cy_semaphore_t;
typedef SemaphoreHandle_t cy_mutex_t;
typedef TaskHandle_t cy_thread_t;
typedef EventGroupHandle_t cy_event_t;
typedef TimerHandle_t cy_timer_t;
typedef uint32_t cy_timer_callback_arg_t;
typedef void *cy_thread_arg_t;
typedef uint32_t cy_time_t;
typedef BaseType_t cy_rtos_error_t;

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* ifndef INCLUDED_CYABS_RTOS_IMPL_H_ */

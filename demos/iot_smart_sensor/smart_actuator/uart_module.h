/*
 * uart_module.h
 *
 *  Created on: 05-Aug-2021
 *      Author: Narayanaswam
 */

#ifndef DEMOS_SMART_ACTUATOR_DEMO_UART_MODULE_H_
#define DEMOS_SMART_ACTUATOR_DEMO_UART_MODULE_H_

#include "cyhal.h"
#include "cybsp.h"
#include "cy_pdl.h"

#define UART_RX_PIN P9_0
#define UART_TX_PIN	P9_1

/* Temporary buffer and data for testing the connection using loop-back */
#define SA_RX_SIZE_BYTES 6
#define SA_TX_SIZE_BYTES 6

/* Extern flags for setting the status of the uart module operations */
extern bool uart_module_read_complete;

void uart_module_init(void);
void uart_module_read(uint8_t * rx_buf_add, uint8_t no_of_bytes);
void uart_module_write(uint8_t * tx_buf_add, uint8_t no_of_bytes);
void uart_module_deinit(void);

#endif /* DEMOS_SMART_ACTUATOR_DEMO_UART_MODULE_H_ */

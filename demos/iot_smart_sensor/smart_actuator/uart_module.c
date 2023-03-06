/*
 * uart_module.c
 *
 *  Created on: 05-Aug-2021
 *      Author: Narayanaswam
 */

#include "cyhal.h"
#include "cybsp.h"
#include "cy_pdl.h"
#include "uart_module.h"
#include "FreeRTOSConfig.h"

#define DATA_BITS_8     8
#define STOP_BITS_1     1
#define BAUD_RATE       115200
#define INT_PRIORITY	3
#define UART_DELAY      10u

/* Variable Declarations */
cyhal_uart_t uart_obj;

/* Initialize the UART configuration structure */
const cyhal_uart_cfg_t uart_config =
{
	.data_bits = DATA_BITS_8,
    .stop_bits = STOP_BITS_1,
    .parity = CYHAL_UART_PARITY_NONE,
    .rx_buffer = NULL,
    .rx_buffer_size = NULL
};

bool uart_module_read_complete = false;

/* Event handler callback function */
void uart_event_handler(void *handler_arg, cyhal_uart_event_t event)
{
    (void) handler_arg;
    if ((event & CYHAL_UART_IRQ_TX_ERROR) == CYHAL_UART_IRQ_TX_ERROR)
    {
        /* An error occurred in Tx */
        /* Insert application code to handle Tx error */
    }
    else if ((event & CYHAL_UART_IRQ_TX_DONE) == CYHAL_UART_IRQ_TX_DONE)
    {
        /* All Tx data has been transmitted */
        /* Insert application code to handle Tx done */
    }
    else if ((event & CYHAL_UART_IRQ_RX_DONE) == CYHAL_UART_IRQ_RX_DONE)
    {
    	/* Set the flag to indicate that the read operation is complete */
    	uart_module_read_complete = true;
        /* All Rx data has been received */
        /* Insert application code to handle Rx done */
//    	for (int i = 0; i < SA_RX_SIZE_BYTES; i++)
//    	{
//    		if (uart_temp_rx_buf[i] == uart_temp_tx_buf[i])
//    		{
//    			configPRINTF( ( "Byte %d is: %d\r\n", i, uart_temp_rx_buf[i] ) );
//    		}
//    		else
//    		{
//    			configPRINTF( ( "Received data is different from transmitted data" ) );
//    		}
//    	}
    }
}

/*
 * @Brief This functions initializes the uart peripheral with the provided parameters and
 * 		  also sets the required interrupts and call backs for receive and transmit
 * */
void uart_module_init(void)
{
	cy_rslt_t result;

	/* Initialize the UART Block */
	result = cyhal_uart_init(&uart_obj, UART_TX_PIN, UART_RX_PIN, NULL, &uart_config);

	/* Set the baud rate */
	result = cyhal_uart_set_baud(&uart_obj, BAUD_RATE, NULL);

	/* Assert if the initialization failed */
	CY_ASSERT(CY_RSLT_SUCCESS == result);

    /* The UART callback handler registration */
    cyhal_uart_register_callback(&uart_obj, uart_event_handler, NULL);

    /* Enable required UART events */
    cyhal_uart_enable_event(&uart_obj, (cyhal_uart_event_t)(CYHAL_UART_IRQ_TX_DONE | CYHAL_UART_IRQ_TX_ERROR | CYHAL_UART_IRQ_RX_DONE), INT_PRIORITY, true);

//    /* Begin asynchronous TX transfer */
//    cyhal_uart_write_async(&uart_obj, (void*) tx_buf, tx_length);
//    cyhal_system_delay_ms(UART_DELAY);
}

/*
 * @Brief This functions starts asynchronous read of the number of bytes mentioned in the
 *        arguments. The read data is saved to the buffer provided by the user
 * */
void uart_module_read(uint8_t * rx_buf_add, uint8_t no_of_bytes)
{
	cy_rslt_t result;

	if (false == cyhal_uart_is_rx_active(&uart_obj))
	{
	    /* Start the asynchronous receive */
	    result = cyhal_uart_read_async(&uart_obj, (void*) rx_buf_add, no_of_bytes);
	}

	/* Assert if the read failed */
	//CY_ASSERT(CY_RSLT_SUCCESS == result);
}

/*
 * @Brief
 * */
void uart_module_write(uint8_t * tx_buf_add, uint8_t no_of_bytes)
{
	cy_rslt_t result;

	if (false == cyhal_uart_is_tx_active(&uart_obj))
	{
	    /* Start the asynchronous write */
	    result = cyhal_uart_write_async(&uart_obj, (void*) tx_buf_add, no_of_bytes);
	}

	/* Assert if the write failed */
	//CY_ASSERT(CY_RSLT_SUCCESS == result);
}


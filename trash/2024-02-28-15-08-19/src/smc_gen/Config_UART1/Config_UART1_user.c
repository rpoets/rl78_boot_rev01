/***********************************************************************************************************************
* DISCLAIMER
* This software is supplied by Renesas Electronics Corporation and is only intended for use with Renesas products.
* No other uses are authorized. This software is owned by Renesas Electronics Corporation and is protected under all
* applicable laws, including copyright laws. 
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING THIS SOFTWARE, WHETHER EXPRESS, IMPLIED
* OR STATUTORY, INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
* NON-INFRINGEMENT.  ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED.TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY
* LAW, NEITHER RENESAS ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES SHALL BE LIABLE FOR ANY DIRECT,
* INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY REASON RELATED TO THIS SOFTWARE, EVEN IF RENESAS OR
* ITS AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* Renesas reserves the right, without notice, to make changes to this software and to discontinue the availability 
* of this software. By using this software, you agree to the additional terms and conditions found by accessing the 
* following link:
* http://www.renesas.com/disclaimer
*
* Copyright (C) 2021, 2023 Renesas Electronics Corporation. All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* File Name        : Config_UART1_user.c
* Component Version: 1.6.0
* Device(s)        : R7F123FLG3xFB
* Description      : This file implements device driver for Config_UART1.
***********************************************************************************************************************/
/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "r_cg_macrodriver.h"
#include "r_cg_userdefine.h"
#include "Config_UART1.h"
/* Start user code for include. Do not edit comment generated here */
#include "config.h"
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
Pragma directive
***********************************************************************************************************************/
#pragma interrupt r_Config_UART1_interrupt_send(vect=INTST1)
#pragma interrupt r_Config_UART1_interrupt_receive(vect=INTSR1)
/* Start user code for pragma. Do not edit comment generated here */
#if CFG_DEBUG
#define DOUT(a)		do { r_printf a; } while(0)
#else
#define DOUT(a)
#endif

/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
extern volatile uint8_t * gp_uart1_tx_address;    /* uart1 transmit buffer address */
extern volatile uint16_t g_uart1_tx_count;        /* uart1 transmit data number */
extern volatile uint8_t * gp_uart1_rx_address;    /* uart1 receive buffer address */
extern volatile uint16_t g_uart1_rx_count;        /* uart1 receive data number */
extern uint16_t g_uart1_rx_length;                /* uart1 receive data length */
/* Start user code for global. Do not edit comment generated here */
MD_STATUS Uart1_Status;
extern void v_printf(const char * format, ...);
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: R_Config_UART1_Create_UserInit
* Description  : This function adds user code after initializing UART1.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_Config_UART1_Create_UserInit(void)
{
    /* Start user code for user init. Do not edit comment generated here */	
	/* End user code. Do not edit comment generated here */
}

/***********************************************************************************************************************
* Function Name: r_Config_UART1_callback_sendend
* Description  : This function is a callback function when UART1 finishes transmission.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
static void r_Config_UART1_callback_sendend(void)
{
    /* Start user code for r_Config_UART1_callback_sendend. Do not edit comment generated here */
    Uart1_Status = 0;
	/* End user code. Do not edit comment generated here */
}

/***********************************************************************************************************************
* Function Name: r_Config_UART1_callback_receiveend
* Description  : This function is a callback function when UART1 finishes reception.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
static void r_Config_UART1_callback_receiveend(void)
{
    /* Start user code for r_Config_UART1_callback_receiveend. Do not edit comment generated here */
	Uart1_Status = 0;
    /* End user code. Do not edit comment generated here */
}

/***********************************************************************************************************************
* Function Name: r_Config_UART1_callback_error
* Description  : This function is a callback function when UART1 reception error occurs.
* Arguments    : err_type -
*                    error type info
* Return Value : None
***********************************************************************************************************************/
static void r_Config_UART1_callback_error(uint8_t err_type)
{
    /* Start user code for r_Config_UART1_callback_error. Do not edit comment generated here */
	Uart1_Status = err_type;
    /* End user code. Do not edit comment generated here */
}

/***********************************************************************************************************************
* Function Name: r_Config_UART1_callback_softwareoverrun
* Description  : This function is a callback when UART1 receives an overflow data.
* Arguments    : rx_data -
*                    receive data
* Return Value : None
***********************************************************************************************************************/
static void r_Config_UART1_callback_softwareoverrun(uint16_t rx_data)
{
    /* Start user code for r_Config_UART1_callback_softwareoverrun. Do not edit comment generated here */
	//Uart1_Status = err_type;
    /* End user code. Do not edit comment generated here */
}

/***********************************************************************************************************************
* Function Name: r_Config_UART1_interrupt_send
* Description  : This function is UART1 send interrupt service routine.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
static void __near r_Config_UART1_interrupt_send(void)
{
    if (g_uart1_tx_count > 0U)
    {
        SDR10L = *gp_uart1_tx_address;
        gp_uart1_tx_address++;
        g_uart1_tx_count--;
    }
    else
    {
        r_Config_UART1_callback_sendend();
    }
}

/***********************************************************************************************************************
* Function Name: r_Config_UART1_interrupt_receive
* Description  : This function is UART1 receive interrupt service routine.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
static void __near r_Config_UART1_interrupt_receive(void)
{
    uint8_t rx_data;
    uint8_t err_type;

    err_type = (uint8_t)(SSR11 & 0x0007U);
    SIR11 = (uint16_t)err_type;

    if (0U != err_type)
    {
        r_Config_UART1_callback_error(err_type);
    }

    rx_data = SDR11L;

    if (g_uart1_rx_length > g_uart1_rx_count)
    {
        *gp_uart1_rx_address = rx_data;
        gp_uart1_rx_address++;
        g_uart1_rx_count++;

        if (g_uart1_rx_length == g_uart1_rx_count)
        {
            r_Config_UART1_callback_receiveend();
        }
    }
    else
    {
        r_Config_UART1_callback_softwareoverrun(rx_data);
    }
}

/* Start user code for adding. Do not edit comment generated here */
/***********************************************************************************************************************
* Function Name: 
* Description  : 
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void dd_UART1_init(void)
{
	R_Config_UART1_Create();	//Also included R_Systeminit()
	R_Config_UART1_Start();
}
/***********************************************************************************************************************
* Function Name: 
* Description  : putchar define printf STD Out stream to UART1 (2024-02-02)
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
int __far putchar(int c)
{
	uint8_t tmp_char = (uint8_t)c;
	Uart1_Status = 99;
	
	R_Config_UART1_Send(&tmp_char, 1);
	
	for(uint16_t i=0; i < UART_TX_END_TIMEOUT ; i++)
	{		
		if(!Uart1_Status) //only sendend INT
			return 0;					
		
		else
			NOP();				
	}	
	DOUT(("Error: UART1 Tx Time_Out\n\r"));
	return 1;
}
/***********************************************************************************************************************
* Function Name: 
* Description  : 
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void r_printf(const char * format, ...)
{
	//To Add, App Timer Suspend
	printf_tiny(format); //compiler support function
	//To Add, App Timer Resume

#if false	
	v_printf(format);
#endif	

#if false /* float display */
	va_list args;
	
	//To Add, App Timer Suspend
	va_start(args, format);	
	vprintf(format, args);	//compiler support function
	va_end(args);
	//To Add, App Timer Resume
#endif
}



/* End user code. Do not edit comment generated here */

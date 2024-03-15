/**********************************************************************************************************************
 * DISCLAIMER
 * This software is supplied by Renesas Electronics Corporation and is only intended for use with Renesas products. No
 * other uses are authorized. This software is owned by Renesas Electronics Corporation and is protected under all
 * applicable laws, including copyright laws.
 * THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING
 * THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED. TO THE MAXIMUM
 * EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES
 * SHALL BE LIABLE FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY REASON RELATED TO
 * THIS SOFTWARE, EVEN IF RENESAS OR ITS AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
 * Renesas reserves the right, without notice, to make changes to this software and to discontinue the availability of
 * this software. By using this software, you agree to the additional terms and conditions found by accessing the
 * following link:
 * http://www.renesas.com/disclaimer
 *
 * Copyright (C) 2020-2022 Renesas Electronics Corporation. All rights reserved.
 *********************************************************************************************************************/
/***********************************************************************/
/*                                                                     */
/*  FILE        :Main.c or Main.cpp                                    */
/*  DATE        :                                                      */
/*  DESCRIPTION :Main Program                                          */
/*  CPU TYPE    :                                                      */
/*                                                                     */
/*  NOTE:THIS IS A TYPICAL EXAMPLE.                                    */
/*                                                                     */
/***********************************************************************/
#include "r_cg_macrodriver.h"
#include "config.h"
#include "atypedef.h"
/*****************************************************************************
* MACRO DEFINITIONS
*****************************************************************************/
/* polyspace:begin<MISRA-C:19.10:Not a defect:Not a defect.> If the debug feature is disabled, DOUT macros are removed. */
/* polyspace:begin<MISRA-C:19.4:Not a defect:Not a defect.> If the debug feature is disabled, DOUT macros are removed. */
#if CFG_DEBUG
#define DOUT(a)		do { r_printf a; } while(0)
#else
#define DOUT(a)
#endif
extern void r_printf(const char * format, ...);

void app_main(void);
extern void __near INTC_intp1_interrupt(void);

extern void R_Config_UART1_Start(void);
extern void R_Config_INTC_INTP1_Start(void);	//for SW2
extern volatile bool SWkey_flag;
extern volatile bool SWkey_flag_app;

extern uint16_t read_bl_session_key(void);
extern uint8_t read_bl_app_mode(void);
extern void bl_app_mode_config(uint8_t code);

extern void sw_reset(void);
extern void write_bl_session_key(uint16_t data);
extern uint8_t ClearBootparaValue(void);

void INTP1_check(void)
{
	INTC_intp1_interrupt();	//function in boot
	//SWkey_flag = true;	
}


void app_main(void)
{
	ClearBootparaValue();
	bl_app_mode_config(APP_SIGNATURE);	
	
	BSP_ENABLE_INTERRUPT();		
	R_Config_UART1_Start();
	R_Config_INTC_INTP1_Start();	//for SW2
		
	
    DOUT(("App bl_session_key: 0x%x \n\r", read_bl_session_key()));
	DOUT(("App bl_app_mode: 0x%x \n\r", read_bl_app_mode()));
	
	write_bl_session_key(0xABCD);
	
	while(true)
	{		
		if(SWkey_flag_app)
		{
			for(uint16_t i=0; i <20; i++)
			{
				P8_bit.no0 = 1U;	//Debug_LED 2
				R_BSP_SoftwareDelay(100, BSP_DELAY_MILLISECS);
				P8_bit.no0 = 0U;	
				R_BSP_SoftwareDelay(100, BSP_DELAY_MILLISECS);
			}
			sw_reset();
			return;
		}		
	}
}

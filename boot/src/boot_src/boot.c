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
#include "typedef.h"

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

void bl_main(void);
extern void R_Config_UART1_Start(void);
extern void R_Config_INTC_INTP1_Start(void);

extern volatile bool SWkey_flag;
//extern void INTP1_check(void);
extern void bl_app_mode_config(uint8_t code);
extern void reset_cause(void);
extern uint16_t read_hw_version(void);
extern branch_mode_ret_e startup_branch(void);

extern test_BlFlashDriver(void);
extern bool CheckAppCRC32(void);
extern bool CheckAppCRC32_woTable(void);


void bl_main(void)
{
	bl_app_mode_config(BL_SIGNATURE);	
	
	BSP_ENABLE_INTERRUPT();
	R_Config_UART1_Start();
	//reset_cause();
	DOUT(("HW_VERSION 0x%x \n\r", read_hw_version()));
	
	branch_mode_ret_e branch_mode = startup_branch();
	//my_RL78_test();
	
	
    test_BlFlashDriver();
	CheckAppCRC32();
	//CheckAppCRC32_woTable();
	
	
	if (branch_mode == ENUM_RET_RUN_APP)
		return;
	else
	{
		R_Config_INTC_INTP1_Start();	//for SW2		
		DOUT(("<Hello BL Mode>\n\r"));			
	}
}













#if false
	while(true)
	{
		//INTP1_check();	//funtion call in flash --> OK
		if(SWkey_flag)
		{
			for(uint16_t i=0; i <10; i++)
			{
				P8_bit.no1 = 1U;	//Debug_LED 1
				R_BSP_SoftwareDelay(100, BSP_DELAY_MILLISECS);
				P8_bit.no1 = 0U;	
				R_BSP_SoftwareDelay(100, BSP_DELAY_MILLISECS);
			}
			
			return;
		}
	}
	
	
	void my_RL78_test(void)
{
	//Origin data signed : MS bit '1' --> '1' fadding, unsigned all '0' fadding
	/* int16 promotion */ 
	int16_t i_16_tmp = 0x8000;
	uint32_t ui_32_tmp = 0;
	
	ui_32_tmp = i_16_tmp;
	DOUT(("int16 promotion ui_32_tmp up 0x%x \n\r", ui_32_tmp>>16));
	DOUT(("int16 promotion ui_32_tmp down 0x%x \n\r", ui_32_tmp));
	
	
	uint16_t ui_16_tmp = 0x8000;
	ui_32_tmp = ui_16_tmp;
	DOUT(("uint16 promotion ui_32_tmp up 0x%x \n\r", ui_32_tmp>>16));
	DOUT(("uint16 promotion ui_32_tmp down 0x%x \n\r", ui_32_tmp));
			
	
	int32_t i_32_tmp = 0;	
	i_32_tmp = i_16_tmp;
	DOUT(("int16 promotion i_32_tmp up 0x%x \n\r", ui_32_tmp>>16));
	DOUT(("int16 promotion i_32_tmp down 0x%x \n\r", ui_32_tmp));
	
	
	i_32_tmp = ui_16_tmp;
	DOUT(("uint16 promotion i_32_tmp up 0x%x \n\r", ui_32_tmp>>16));
	DOUT(("uint16 promotion i_32_tmp down 0x%x \n\r", ui_32_tmp));
	
	/* Literal Test */
	ui_32_tmp = 44*1024;
	DOUT(("44*1024 ui_32_tmp up 0x%x \n\r", ui_32_tmp>>16));
	DOUT(("44*1024 ui_32_tmp up down 0x%x \n\r", ui_32_tmp));
	
	ui_32_tmp = 44u*1024;
	DOUT(("44*1024 ui_32_tmp up 0x%x \n\r", ui_32_tmp>>16));
	DOUT(("44*1024 ui_32_tmp up down 0x%x \n\r", ui_32_tmp));
	
	ui_32_tmp = 44*1024u;
	DOUT(("44*1024u ui_32_tmp up 0x%x \n\r", ui_32_tmp>>16));
	DOUT(("44*1024u ui_32_tmp up down 0x%x \n\r", ui_32_tmp));
	
	ui_32_tmp = 44u*1024u;
	DOUT(("44u*1024u ui_32_tmp up 0x%x \n\r", ui_32_tmp>>16));
	DOUT(("44u*1024u ui_32_tmp up down 0x%x \n\r", ui_32_tmp));
	
	ui_32_tmp = (uint16_t)(44*1024);
	DOUT(("(uint16_t)(44*1024) ui_32_tmp up 0x%x \n\r", ui_32_tmp>>16));
	DOUT(("(uint16_t)(44*1024) ui_32_tmp up down 0x%x \n\r", ui_32_tmp));
	
}

#endif
/**********************************************************************************************************************
    Program Name    : Sample program for Renesas Flash Driver (RFD RL78 Type02) (Data Flash)
    
    File Name       : r_flash_sample_dataflash_rl78f2x.c
    Program Version : V1.00.00
    Device(s)       : RL78/F23 microcontroller
    Description     : Sample program for Data Flash Control
**********************************************************************************************************************/

/**********************************************************************************************************************
    DISCLAIMER
    This software is supplied by Renesas Electronics Corporation and is only intended for use with
    Renesas products. No other uses are authorized. This software is owned by Renesas Electronics
    Corporation and is protected under all applicable laws, including copyright laws.
    THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING THIS SOFTWARE,
    WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED.
    TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS ELECTRONICS CORPORATION NOR
    ANY OF ITS AFFILIATED COMPANIES SHALL BE LIABLE FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR
    CONSEQUENTIAL DAMAGES FOR ANY REASON RELATED TO THIS SOFTWARE, EVEN IF RENESAS OR ITS AFFILIATES HAVE
    BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
    Renesas reserves the right, without notice, to make changes to this software and to discontinue the
    availability of this software. By using this software, you agree to the additional terms and conditions
    found by accessing the following link:
    http://www.renesas.com/disclaimer
    
    Copyright (C) 2022 Renesas Electronics Corporation. All rights reserved.
**********************************************************************************************************************/

/**********************************************************************************************************************
 Includes   <System Includes> , "Project Includes"
 *********************************************************************************************************************/
#include "r_smc_entry.h"
#include "sample_control_data_flash.h"
#include "sample_defines.h"
#include "sample_dataflash_config.h"
#include "sample_data_initsct.h"
#include "r_rfd_common_api.h"
#include "r_rfd_rl78_data_flash_if.h"

/**********************************************************************************************************************
  Prototype declaration
**********************************************************************************************************************/
int sample_dataflash_main(void);

/**********************************************************************************************************************
 * Function name : sample_dataflash_main
 *********************************************************************************************************************/
/**
 *  Sample main.
 *  
 *  @param[in]      -
 *  @return         Execution result status
 *                  - SAMPLE_ENUM_RET_STS_OK               : Successful completion
 *                  - SAMPLE_ENUM_RET_ERR_PARAMETER        : Parameter error
 *                  - SAMPLE_ENUM_RET_ERR_MODE_MISMATCHED  : Mode mismatched error
 *                  - SAMPLE_ENUM_RET_ERR_CONFIGURATION    : Configuration error
 *                  - SAMPLE_ENUM_RET_ERR_CHECK_WRITE_DATA : Check write data error
 *                  - SAMPLE_ENUM_RET_ERR_CMD_ERASE        : Erase command error
 *                  - SAMPLE_ENUM_RET_ERR_CMD_WRITE        : Write command error
 *                  - SAMPLE_ENUM_RET_ERR_CMD_BLANKCHECK   : Blankcheck command error
 *                  - SAMPLE_ENUM_RET_ERR_CMD_IVERIFY      : IVerify command error
 */
/*********************************************************************************************************************/
int sample_dataflash_main(void)
{
    /* Local variable definition */
    e_rfd_ret_t    l_e_rfd_status_flag;
    e_sample_ret_t l_e_sam_ret_value;
    uint16_t       l_u16_count;
    uint8_t        l_au08_write_data[DF_WRITE_DATA_LENGTH];
    uint32_t       l_mclk_freq;

#if (COMPILER_CC == COMPILER)
    Sample_Data_INITSCT();
#endif

    l_mclk_freq = R_BSP_GetFclkFreqHz();
    l_mclk_freq = (l_mclk_freq + L_MCLK_ROUNDUP_VALUE)/L_MCLK_FREQ_1MHz;

    /* Create writing data */
    for (l_u16_count = 0u; l_u16_count < DF_WRITE_DATA_LENGTH; l_u16_count++)
    {
        l_au08_write_data[l_u16_count] = (uint8_t)((l_u16_count+1) & SAMPLE_VALUE_U08_MASK1_8BIT);
    }
    
    /* Check whether HOCO is already started */
    if (SAMPLE_VALUE_U01_MASK0_1BIT == HIOSTOP)
    {
        /* Initialize RFD */
        l_e_rfd_status_flag = R_RFD_Init((uint8_t)l_mclk_freq);
        
        if (R_RFD_ENUM_RET_STS_OK == l_e_rfd_status_flag)
        {
            /* Data flash blankcheck, erase, write, and iverify */
            l_e_sam_ret_value = Sample_DataFlashControl(DF_WRITE_ADDRESS, DF_WRITE_DATA_LENGTH, l_au08_write_data);
        }
        else
        {
            /* Failed to initialize RFD */
            l_e_sam_ret_value = SAMPLE_ENUM_RET_ERR_PARAMETER;
        }
    }
    else
    {
        /* HOCO is not started */
        l_e_sam_ret_value = SAMPLE_ENUM_RET_ERR_CONFIGURATION;
    }
    
    return ((int)l_e_sam_ret_value);
}
/**********************************************************************************************************************
 End of function sample_dataflash_main
 *********************************************************************************************************************/

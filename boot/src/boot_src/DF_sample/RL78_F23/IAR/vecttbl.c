/***********************************************************************************************************************
* DISCLAIMER
* This software is supplied by Renesas Electronics Corporation and is only intended for use with Renesas products. No 
* other uses are authorized. This software is owned by Renesas Electronics Corporation and is protected under all 
* applicable laws, including copyright laws. 
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING
* THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY, 
* FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED. TO THE MAXIMUM 
* EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES 
* SHALL BE LIABLE FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY REASON RELATED TO THIS 
* SOFTWARE, EVEN IF RENESAS OR ITS AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* Renesas reserves the right, without notice, to make changes to this software and to discontinue the availability of 
* this software. By using this software, you agree to the additional terms and conditions found by accessing the 
* following link:
* http://www.renesas.com/disclaimer
*
* Copyright (C) 2022 Renesas Electronics Corporation. All rights reserved.
***********************************************************************************************************************/
/***********************************************************************************************************************
* File Name    : vecttbl.c
* Description  : 
***********************************************************************************************************************/
/***********************************************************************************************************************
* History : DD.MM.YYYY Version  Description
*         : 28.02.2022 1.20     First Release
*
***********************************************************************************************************************/

/*************************************************
 * Includes  <System Includes> , "Project Includes"
 *************************************************/
#include "platform.h"

/*************************************************
 * Private global variables and functions
 *************************************************/
/* Option byte setting(When using IAR) */
#pragma location = "OPTBYTE"
__root const uint8_t opbyte0 = 0x6E;    /* 01101110 */
                                        /* |||||||| */
                                        /* |||||||+-- Watchdog timer     */
                                        /* |||||||    operation stopped  */
                                        /* |||||||    in HALT/STOP mode  */
                                        /* ||||+++--- Watchdog timer     */
                                        /* ||||       overflow time is   */
                                        /* ||||       2^16 / fIL =       */
                                        /* ||||       3799.18 ms         */
                                        /* |||+------ Watchdog timer     */
                                        /* |||        operation disabled */
                                        /* |++------- 100% window open   */
                                        /* |          period             */
                                        /* +--------- Interval interrupt */
                                        /*            is not used        */
#pragma location = "OPTBYTE"
__root const uint8_t opbyte1 = 0x6F;    /* 01101111 */
                                        /* |||||||| */
                                        /* +++|++++-- LVD reset mode */
                                        /*    +------ Control of clock monitor operation is enabled */
#pragma location = "OPTBYTE"
__root const uint8_t opbyte2 = 0xE8;    /* 11101000 */
                                        /*   |||||| */
                                        /*   |+++++-- 40 MHz */
                                        /*   +------- Selects P130 as a general port pin (output only) */
#pragma location = "OPTBYTE"
__root const uint8_t opbyte3 = 0xA5;    /* 10100101 */
                                        /* | |   || */
                                        /* +-|---++-- OCD: enables on-chip debugging function */
                                        /*   +------- Enables flash serial programming operation. */
#pragma location = "OPTBYTE"
__root const uint8_t opbyte4 = 0xFE;    /* Enables read of on-chip debug and flash serial programming security ID */

/* Security ID Codes for On-Chip Debugging setting(When using IAR) */
#pragma location = "SECUID"
__root const uint8_t secuid[16] =
{BSP_CFG_SECUID0_VALUE, BSP_CFG_SECUID1_VALUE, BSP_CFG_SECUID2_VALUE, BSP_CFG_SECUID3_VALUE,
 BSP_CFG_SECUID4_VALUE, BSP_CFG_SECUID5_VALUE, BSP_CFG_SECUID6_VALUE, BSP_CFG_SECUID7_VALUE,
 BSP_CFG_SECUID8_VALUE, BSP_CFG_SECUID9_VALUE, BSP_CFG_SECUIDA_VALUE, BSP_CFG_SECUIDB_VALUE,
 BSP_CFG_SECUIDC_VALUE, BSP_CFG_SECUIDD_VALUE, BSP_CFG_SECUIDE_VALUE, BSP_CFG_SECUIDF_VALUE};

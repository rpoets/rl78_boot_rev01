/**********************************************************************************************************************
    Program Name    : Sample program for Renesas Flash Driver (RFD RL78 Type02)
    
    File Name       : sample_defines.h
    Program Version : V1.00.00
    Device(s)       : RL78/F24 microcontroller
    Description     : Sample defines
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
    
    Copyright (C) 2021-2022 Renesas Electronics Corporation. All rights reserved.
**********************************************************************************************************************/

#ifndef SAMPLE_DEFINES_H
#define SAMPLE_DEFINES_H

/* Defines */
#define SAMPLE_VALUE_U08_MASK1_FSQ_STATUS_ERR_CFDF_SEQUENCER  (0x10u)
#define SAMPLE_VALUE_U08_MASK1_FSQ_STATUS_ERR_EXTRA_SEQUENCER (0x20u)
#define SAMPLE_VALUE_U08_MASK1_FSQ_STATUS_ERR_ERASE           (0x01u)
#define SAMPLE_VALUE_U08_MASK1_FSQ_STATUS_ERR_WRITE           (0x02u)
#define SAMPLE_VALUE_U08_MASK1_FSQ_STATUS_ERR_IVERIFY         (0x04u)
#define SAMPLE_VALUE_U08_MASK1_FSQ_STATUS_ERR_BLANKCHECK      (0x08u)

#define SAMPLE_VALUE_U32_DF_BASE_ADDR                         (0x000F1000u)
#define SAMPLE_VALUE_U08_SHIFT_ADDR_TO_BLOCK_CF               (10u)
#define SAMPLE_VALUE_U08_SHIFT_ADDR_TO_BLOCK_DF               (10u)

#define SAMPLE_VALUE_U01_MASK0_1BIT                           (0u)
#define SAMPLE_VALUE_U01_MASK1_1BIT                           (1u)
#define SAMPLE_VALUE_U08_MASK0_8BIT                           (0x00u)
#define SAMPLE_VALUE_U08_MASK1_8BIT                           (0xFFu)

#endif /* end of SAMPLE_DEFINES_H */

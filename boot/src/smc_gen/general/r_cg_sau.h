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
* File Name        : r_cg_sau.h
* Version          : 1.0.30
* Device(s)        : R7F123FLG3xFB
* Description      : General header file for SAU peripheral.
***********************************************************************************************************************/

#ifndef SAU_H
#define SAU_H

/***********************************************************************************************************************
Macro definitions (Register bit)
***********************************************************************************************************************/
/*
    Peripheral Enable Register 0 (PER0)
*/
/* Control of serial array unit 1 input clock supply (SAU1EN) */
#define _00_SAU1_CLOCK_STOP              (0x00U)    /* stops supply of input clock */
#define _08_SAU1_CLOCK_SUPPLY            (0x08U)    /* enables input clock supply */
/* Control of serial array unit 0 input clock supply (SAU0EN) */
#define _00_SAU0_CLOCK_STOP              (0x00U)    /* stops supply of input clock */
#define _04_SAU0_CLOCK_SUPPLY            (0x04U)    /* enables input clock supply */

/*
    Serial Clock Select Register m (SPSm)
*/
/* Section of operation clock (CKm1) (PRSm13 - PRSm10) */
#define _0000_SAU_CKM1_FCLK_0            (0x0000U)    /* CKm1 - fCLK */
#define _0010_SAU_CKM1_FCLK_1            (0x0010U)    /* CKm1 - fCLK/2^1 */
#define _0020_SAU_CKM1_FCLK_2            (0x0020U)    /* CKm1 - fCLK/2^2 */
#define _0030_SAU_CKM1_FCLK_3            (0x0030U)    /* CKm1 - fCLK/2^3 */
#define _0040_SAU_CKM1_FCLK_4            (0x0040U)    /* CKm1 - fCLK/2^4 */
#define _0050_SAU_CKM1_FCLK_5            (0x0050U)    /* CKm1 - fCLK/2^5 */
#define _0060_SAU_CKM1_FCLK_6            (0x0060U)    /* CKm1 - fCLK/2^6 */
#define _0070_SAU_CKM1_FCLK_7            (0x0070U)    /* CKm1 - fCLK/2^7 */
#define _0080_SAU_CKM1_FCLK_8            (0x0080U)    /* CKm1 - fCLK/2^8 */
#define _0090_SAU_CKM1_FCLK_9            (0x0090U)    /* CKm1 - fCLK/2^9 */
#define _00A0_SAU_CKM1_FCLK_10           (0x00A0U)    /* CKm1 - fCLK/2^10 */
#define _00B0_SAU_CKM1_FCLK_11           (0x00B0U)    /* CKm1 - fCLK/2^11 */
#define _000F_SAU_CKM1_CLEAR             (0x000FU)    /* clear bit4 - bit7 */
/* Section of operation clock (CKm0) (PRSm03 - PRSm00) */
#define _0000_SAU_CKM0_FCLK_0            (0x0000U)    /* CKm0 - fCLK */
#define _0001_SAU_CKM0_FCLK_1            (0x0001U)    /* CKm0 - fCLK/2^1 */
#define _0002_SAU_CKM0_FCLK_2            (0x0002U)    /* CKm0 - fCLK/2^2 */
#define _0003_SAU_CKM0_FCLK_3            (0x0003U)    /* CKm0 - fCLK/2^3 */
#define _0004_SAU_CKM0_FCLK_4            (0x0004U)    /* CKm0 - fCLK/2^4 */
#define _0005_SAU_CKM0_FCLK_5            (0x0005U)    /* CKm0 - fCLK/2^5 */
#define _0006_SAU_CKM0_FCLK_6            (0x0006U)    /* CKm0 - fCLK/2^6 */
#define _0007_SAU_CKM0_FCLK_7            (0x0007U)    /* CKm0 - fCLK/2^7 */
#define _0008_SAU_CKM0_FCLK_8            (0x0008U)    /* CKm0 - fCLK/2^8 */
#define _0009_SAU_CKM0_FCLK_9            (0x0009U)    /* CKm0 - fCLK/2^9 */
#define _000A_SAU_CKM0_FCLK_10           (0x000AU)    /* CKm0 - fCLK/2^10 */
#define _000B_SAU_CKM0_FCLK_11           (0x000BU)    /* CKm0 - fCLK/2^11 */
#define _00F0_SAU_CKM0_CLEAR             (0x00F0U)    /* clear bit0 - bit3 */

/*
    Serial Mode Register mn (SMRmn)
*/
#define _0020_SAU_SMRMN_INITIALVALUE     (0x0020U)
/* Selection of macro clock (MCK) of channel n (CKSmn) */
#define _0000_SAU_CLOCK_SELECT_CKM0      (0x0000U)    /* operation clock CKm0 set by the SPSm register */
#define _8000_SAU_CLOCK_SELECT_CKM1      (0x8000U)    /* operation clock CKm1 set by the SPSm register */
/* Selection of transfer clock (fTCLK) of channel n (CCSmn) */
#define _0000_SAU_CLOCK_MODE_CKS         (0x0000U)    /* divided operation clock fMCK specified by the CKSmn bit */
#define _4000_SAU_CLOCK_MODE_TI0N        (0x4000U)    /* clock input fSCK from the SCKp pin */
/* Selection of start trigger source (STSmn) */
#define _0000_SAU_TRIGGER_SOFTWARE       (0x0000U)    /* only software trigger is valid */
#define _0100_SAU_TRIGGER_RXD            (0x0100U)    /* valid edge of the RXDq pin */
/* Controls inversion of level of receive data of channel n in UART mode (SISmn0) */
#define _0000_SAU_EDGE_FALLING           (0x0000U)    /* falling edge is detected as the start bit */
#define _0040_SAU_EDGE_RISING            (0x0040U)    /* rising edge is detected as the start bit */
/* Setting of operation mode of channel n (MDmn2, MDmn1) */
#define _0000_SAU_MODE_CSI               (0x0000U)    /* CSI mode */
#define _0002_SAU_MODE_UART              (0x0002U)    /* UART mode */
#define _0004_SAU_MODE_IIC               (0x0004U)    /* simplified IIC mode */
/* Selection of interrupt source of channel n (MDmn0) */
#define _0000_SAU_TRANSFER_END           (0x0000U)    /* transfer end interrupt */
#define _0001_SAU_BUFFER_EMPTY           (0x0001U)    /* buffer empty interrupt */

/*
    Serial Communication Operation Setting Register mn (SCRmn)
*/
/* Setting of operation mode of channel n (TXEmn, RXEmn) */
#define _0000_SAU_NOT_COMMUNICATION      (0x0000U)    /* does not start communication */
#define _4000_SAU_RECEPTION              (0x4000U)    /* reception only */
#define _8000_SAU_TRANSMISSION           (0x8000U)    /* transmission only */
#define _C000_SAU_RECEPTION_TRANSMISSION (0xC000U)    /* reception and transmission */
/* Selection of data and clock phase in CSI mode (DAPmn, CKPmn) */
#define _0000_SAU_TIMING_1               (0x0000U)    /* type 1 */
#define _1000_SAU_TIMING_2               (0x1000U)    /* type 2 */
#define _2000_SAU_TIMING_3               (0x2000U)    /* type 3 */
#define _3000_SAU_TIMING_4               (0x3000U)    /* type 4 */
/* Setting of parity bit in UART mode (PTCmn1 - PTCmn0) */
#define _0000_SAU_PARITY_NONE            (0x0000U)    /* none parity */
#define _0100_SAU_PARITY_ZERO            (0x0100U)    /* zero parity */
#define _0200_SAU_PARITY_EVEN            (0x0200U)    /* even parity */
#define _0300_SAU_PARITY_ODD             (0x0300U)    /* odd parity */
/* Selection of data transfer sequence in CSI and UART modes (DIRmn) */
#define _0000_SAU_MSB                    (0x0000U)    /* inputs/outputs data with MSB first */
#define _0080_SAU_LSB                    (0x0080U)    /* inputs/outputs data with LSB first */
/* Setting of stop bit in UART mode (SLCmn1, SLCmn0) */
#define _0000_SAU_STOP_NONE              (0x0000U)    /* no stop bit */
#define _0010_SAU_STOP_1                 (0x0010U)    /* stop bit length = 1 bit */
#define _0020_SAU_STOP_2                 (0x0020U)    /* stop bit length = 2 bits (mn = 00, 10 only) */
/* Setting of data length in CSI, UART mode (DLSmn3 - DLSmn0) */
#define _0006_SAU_LENGTH_7               (0x0006U)    /* 7 bits */
#define _0007_SAU_LENGTH_8               (0x0007U)    /* 8 bits */
#define _0008_SAU_LENGTH_9               (0x0008U)    /* 9 bits */
#define _0009_SAU_LENGTH_10              (0x0009U)    /* 10 bits */
#define _000A_SAU_LENGTH_11              (0x000AU)    /* 11 bits */
#define _000B_SAU_LENGTH_12              (0x000BU)    /* 12 bits */
#define _000C_SAU_LENGTH_13              (0x000CU)    /* 13 bits */
#define _000D_SAU_LENGTH_14              (0x000DU)    /* 14 bits */
#define _000E_SAU_LENGTH_15              (0x000EU)    /* 15 bits */
#define _000F_SAU_LENGTH_16              (0x000FU)    /* 16 bits */

/*
    Serial Flag Clear Trigger Register mn (SIRmn)
*/
/* Clear trigger of framing error flag of channel n (FECTmn) */
#define _0000_SAU_FEF_UNCLEARED          (0x0000U)    /* not cleared */
#define _0004_SAU_FEF_CLEARED            (0x0004U)    /* clears the FEFmn bit of the SSRmn register to 0 */
/* Clear trigger of parity error flag of channel n (PECTmn) */
#define _0000_SAU_PEF_UNCLEARED          (0x0000U)    /* not cleared */
#define _0002_SAU_PEF_CLEARED            (0x0002U)    /* clears the PEFmn bit of the SSRmn register to 0 */
/* Clear trigger of overrun error flag of channel n (OVCTmn) */
#define _0000_SAU_OVF_UNCLEARED          (0x0000U)    /* not cleared */
#define _0001_SAU_OVF_CLEARED            (0x0001U)    /* clears the OVFmn bit of the SSRmn register to 0 */

/*
    Serial Status Register mn (SSRmn)
*/
/* Communication status indication flag of channel n (TSFmn) */
#define _0000_SAU_COMM_STOPED            (0x0000U)    /* communication is stopped or suspended */
#define _0040_SAU_COMM_IN_PROGRESS       (0x0040U)    /* communication is in progress */
/* Buffer register status indication flag of channel n (BFFmn) */
#define _0000_SAU_VALID_DATA_NOT_STORED  (0x0000U)    /* valid data is not stored in the SDRmn register */
#define _0020_SAU_VALID_DATA_STORED      (0x0020U)    /* valid data is stored in the SDRmn register */
/* Framing error detection flag of channel n (FEFmn) */
#define _0000_SAU_FRAMING_ERR_NOT_OCCUR  (0x0000U)    /* no error occurs */
#define _0004_SAU_FRAMING_ERR_OCCUR      (0x0004U)    /* an error occurs (during UART reception) */
/* Parity error detection flag of channel n (PEFmn) */
#define _0000_SAU_PARITY_ERR_NOT_OCCUR   (0x0000U)    /* no error occurs */
#define _0002_SAU_PARITY_ERR_OCCUR       (0x0002U)    /* an error occurs (during UART reception) or 
                                                         ACK is not detected (during I2C transmission) */
/* Overrun error detection flag of channel n (OVFmn) */
#define _0000_SAU_OVERRUN_NOT_OCCUR      (0x0000U)    /* no error occurs */
#define _0001_SAU_OVERRUN_OCCUR          (0x0001U)    /* an overrun error occurs */

/*
    Serial Channel Start Register m (SSm)
*/
/* Operation start trigger of channel 1 (SSm1) */
#define _0000_SAU_CH1_START_TRG_OFF      (0x0000U)    /* no trigger operation */
#define _0002_SAU_CH1_START_TRG_ON       (0x0002U)    /* sets SEm1 to 1 and enters the communication wait status */
/* Operation start trigger of channel 0 (SSm0) */
#define _0000_SAU_CH0_START_TRG_OFF      (0x0000U)    /* no trigger operation */
#define _0001_SAU_CH0_START_TRG_ON       (0x0001U)    /* sets SEm0 to 1 and enters the communication wait status */

/*
    Serial Channel Stop Register m (STm)
*/
/* Operation stop trigger of channel 1 (STm1) */
#define _0000_SAU_CH1_STOP_TRG_OFF       (0x0000U)    /* no trigger operation */
#define _0002_SAU_CH1_STOP_TRG_ON        (0x0002U)    /* clears SEm1 to 0 and stops the communication operation */
/* Operation stop trigger of channel 0 (STm0) */
#define _0000_SAU_CH0_STOP_TRG_OFF       (0x0000U)    /* no trigger operation */
#define _0001_SAU_CH0_STOP_TRG_ON        (0x0001U)    /* clears SEm0 to 0 and stops the communication operation */

/*
    Serial Channel Enable Status Register m (SEm)
*/
/* Indication of operation enable/stop status of channel 1 (SEm1) */
#define _0000_SAU_CH1_OPERATION_DISABLE  (0x0000U)    /* operation stops */
#define _0002_SAU_CH1_OPERATION_ENABLE   (0x0002U)    /* operation is enabled */
/* Indication of operation enable/stop status of channel 0 (SEm0) */
#define _0000_SAU_CH0_OPERATION_DISABLE  (0x0000U)    /* operation stops */
#define _0001_SAU_CH0_OPERATION_ENABLE   (0x0001U)    /* operation is enabled */

/*
    Serial Output Enable Register m (SOEm)
*/
/* Serial output enable/disable of channel 1 (SOEm1) */
#define _0000_SAU_CH1_OUTPUT_DISABLE     (0x0000U)    /* stops output by serial communication operation */
#define _0002_SAU_CH1_OUTPUT_ENABLE      (0x0002U)    /* enables output by serial communication operation */
/* Serial output enable/disable of channel 0 (SOEm0) */
#define _0000_SAU_CH0_OUTPUT_DISABLE     (0x0000U)    /* stops output by serial communication operation */
#define _0001_SAU_CH0_OUTPUT_ENABLE      (0x0001U)    /* enables output by serial communication operation */

/*
    Serial Output Register m (SOm)
*/
/* Serial clock output of channel 1 (CKOm1) */
#define _0000_SAU_CH1_CLOCK_OUTPUT_0     (0x0000U)    /* serial clock output value is 0 */
#define _0200_SAU_CH1_CLOCK_OUTPUT_1     (0x0200U)    /* serial clock output value is 1 */
/* Serial clock output of channel 0 (CKOm0) */
#define _0000_SAU_CH0_CLOCK_OUTPUT_0     (0x0000U)    /* serial clock output value is 0 */
#define _0100_SAU_CH0_CLOCK_OUTPUT_1     (0x0100U)    /* serial clock output value is 1 */
/* Serial data output of channel 1 (SOm1) */
#define _0000_SAU_CH1_DATA_OUTPUT_0      (0x0000U)    /* serial data output value is 0 */
#define _0002_SAU_CH1_DATA_OUTPUT_1      (0x0002U)    /* serial data output value is 1 */
/* Serial data output of channel 0 (SOm0) */
#define _0000_SAU_CH0_DATA_OUTPUT_0      (0x0000U)    /* serial data output value is 0 */
#define _0001_SAU_CH0_DATA_OUTPUT_1      (0x0001U)    /* serial data output value is 1 */

/*
    Serial Output Level Register m (SOLm)
*/
/* Selects inversion of the level of the transmit data of channel 1 in UART mode (SOLm1) */
#define _0000_SAU_CHANNEL1_NORMAL        (0x0000U)    /* communication data is output as is */
#define _0002_SAU_CHANNEL1_INVERTED      (0x0002U)    /* communication data is inverted and output */
/* Selects inversion of the level of the transmit data of channel 0 in UART mode (SOLm0) */
#define _0000_SAU_CHANNEL0_NORMAL        (0x0000U)    /* communication data is output as is */
#define _0001_SAU_CHANNEL0_INVERTED      (0x0001U)    /* communication data is inverted and output */

/*
    Serial Slave Select Enable Register m (SSEm)
*/
/* Channel 1 SSImn input setting in CSI communication and slave mode (SSEm1) */
#define _0000_SAU_CH1_SSI_INPUT_DISABLE  (0x0000U)    /* disables SSImn pin input */
#define _0002_SAU_CH1_SSI_INPUT_ENABLE   (0x0002U)    /* enables SSImn pin input */
/* Channel 0 SSImn input setting in CSI communication and slave mode (SSEm0) */
#define _0000_SAU_CH0_SSI_INPUT_DISABLE  (0x0000U)    /* disables SSImn pin input */
#define _0001_SAU_CH0_SSI_INPUT_ENABLE   (0x0001U)    /* enables SSImn pin input */

/*
    Noise Filter Enable Register 0 (NFEN0)
*/
/* Use of noise filter of RXD1 pin (SNFEN10) */
#define _00_SAU_RXD1_FILTER_OFF          (0x00U)    /* noise filter off */
#define _04_SAU_RXD1_FILTER_ON           (0x04U)    /* noise filter on */
/* Use of noise filter of RXD0 pin (SNFEN00) */
#define _00_SAU_RXD0_FILTER_OFF          (0x00U)    /* noise filter off */
#define _01_SAU_RXD0_FILTER_ON           (0x01U)    /* noise filter on */

/* SAU Used Flag */
#define _00_SAU_IIC_MASTER_FLAG_CLEAR    (0x00U)
#define _01_SAU_IIC_SEND_FLAG            (0x01U)
#define _02_SAU_IIC_RECEIVE_FLAG         (0x02U)
#define _04_SAU_IIC_SENDED_ADDRESS_FLAG  (0x04U)

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
Global functions
***********************************************************************************************************************/
/* Start user code for function. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
#endif

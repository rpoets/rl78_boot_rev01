/******************************************************************************
* VERSION ID configuration
******************************************************************************/
#define HW_VERSION 0xABCD
#define SW_VERSION 0xDCBA
#define TOUCH_ID 0x17
#define DISPLAY_ID 0x12

/******************************************************************************
* TYPE DEFINITIONS
******************************************************************************/
typedef unsigned short				ret_t;

/******************************************************************************
* Debug configuration
******************************************************************************/
#define CFG_DEBUG 1

/******************************************************************************
* IIC TRX Timeout configuration
******************************************************************************/
#define IIC00_TRX_END_TIMEOUT 250 //400kHz 1byte expect
#define IICA0_TRX_END_TIMEOUT 125 //1MHz 1byte expect
#define IICA0_START_WAIT_TIME 64 //MAX 255

/******************************************************************************
* UART Timeout configuration
******************************************************************************/
#define UART_TX_END_TIMEOUT 400 //115200 1byte expect

/******************************************************************************
* IIC Addr configuration
******************************************************************************/
#define EEP_ADDR_ID 0xB0
#define EEP_ADDR_MEM 0xA0

#define SER_UH983 0x30
#define DES_UH984 0x30

#define serAddr  0x30
#define	desAddr0  0x70
#define	desAlias0  0x70

/******************************************************************************
* dd_rotary_encoder
******************************************************************************/
#define CFG_ROTARY_ENCODER_MAX		2
#define CFG_ROTARY_ENCODER_LIST		\
{	\
	{ PIN_PA20, PIN_PA19 },	\
	{ PIN_PA21, PIN_PA22 },	\
}

#define CFG_ROTARY_ENCODER_INIT_POS 127

/******************************************************************************
* MACRO DEFINITIONS
******************************************************************************/

#define _BIT0   0x01        /* .... ...X */
#define _BIT1   0x02        /* .... ..X. */
#define _BIT2   0x04        /* .... .X.. */
#define _BIT3   0x08        /* .... X... */
#define _BIT4   0x10        /* ...X .... */
#define _BIT5   0x20        /* ..X. .... */
#define _BIT6   0x40        /* .X.. .... */
#define _BIT7   0x80        /* X... .... */

#define _BIT8   0x0100
#define _BIT9   0x0200
#define _BIT10  0x0400
#define _BIT11  0x0800
#define _BIT12  0x1000
#define _BIT13  0x2000
#define _BIT14  0x4000
#define _BIT15  0x8000

#define _BIT16  0x00010000
#define _BIT17  0x00020000
#define _BIT18  0x00040000
#define _BIT19  0x00080000
#define _BIT20  0x00100000
#define _BIT21  0x00200000
#define _BIT22  0x00400000
#define _BIT23  0x00800000

#define _BIT24  0x01000000
#define _BIT25  0x02000000
#define _BIT26  0x04000000
#define _BIT27  0x08000000
#define _BIT28  0x10000000
#define _BIT29  0x20000000
#define _BIT30  0x40000000
#define _BIT31  0x80000000

/*
	Error codes
*/
#define E_OK						0
#define E_ERROR						1
#define E_FLASHODDACCESS			2
#define E_FLASHNOTERASED			3
#define E_ACCESSERROR				4
#define E_PROTECTIONERROR			5
#define E_NOTSTARTOFSECTOR			6
#define E_PROGRAMERASEIMPOSSIBLE	7
#define E_ERRRANGE					8
#define E_ERRNOTAVAIL				9
#define E_ERRBUSY					10
#define E_ERRVALUE					11
#define E_PAR						12
#define E_OVERFLOW					13
#define E_TIMEOUT					14
#define E_COLLISION					15

/* RENESAS OPTIMIZING LINKER GENERATED FILE 2024.03.13 */
/*** variable information ***/
#pragma saddr _g_u08_cpu_frequency /* count:6,size:1,near,r_rfd_common_api.obj */
#pragma saddr _g_u08_fset_cpu_frequency /* count:3,size:1,near,r_rfd_common_api.obj */
#pragma saddr _SWkey_flag /* count:2,size:1,near,task.obj */
/* #pragma saddr _sg_u08_psw_ie_state */ /* count:2,size:1,near,static,r_rfd_common_userown.obj */
#pragma saddr _gp_uart1_tx_address /* count:5,size:2,near,Config_UART1.obj */
#pragma saddr _g_uart1_tx_count /* count:4,size:2,near,Config_UART1.obj */
#pragma saddr _Uart1_Status /* count:4,size:2,near,Config_UART1_user.obj */
#pragma saddr _bootpara /* count:10,size:10,near,task.obj */
#pragma saddr _gp_uart1_rx_address /* count:1,size:2,near,Config_UART1.obj */
#pragma saddr _g_uart1_rx_count /* count:1,size:2,near,Config_UART1.obj */
#pragma saddr _g_uart1_rx_length /* count:1,size:2,near,Config_UART1.obj */
/* #pragma saddr _blfd_dsec_table */ /* count:5,size:10,near,const,dd_flash.obj */
/* #pragma saddr _g_bsp_delay_time */ /* count:2,size:24,near,const,r_bsp_common.obj */
/* #pragma saddr _blfd_psec_table */ /* count:2,size:30,near,const,dd_flash.obj */
/* #pragma saddr _g_fih_hz */ /* count:1,size:128,near,const,mcu_clocks.obj */
/* #pragma saddr _Crc32Ieee8023Table */ /* count:2,size:1024,near,static,crc.obj */

/*** function information ***/
#pragma callt _r_printf /* count:13,far,Config_UART1_user.obj */
#pragma callt _BL_CheckCFDFSeqEnd /* count:10,far,dd_flash.obj */
#pragma callt _R_RFD_SetFlashMemoryMode /* count:8,far,r_rfd_common_api.obj */
#pragma callt _R_RFD_EraseCodeFlashReq /* count:3,far,r_rfd_code_flash_api.obj */
#pragma callt _R_RFD_BlankCheckCodeFlashReq /* count:3,far,r_rfd_code_flash_api.obj */
#pragma callt _R_RFD_WriteCodeFlashReq /* count:2,far,r_rfd_code_flash_api.obj */
#pragma callt _R_RFD_IVerifyCodeFlashReq /* count:2,far,r_rfd_code_flash_api.obj */
#pragma callt _R_Config_UART1_Start /* count:2,far,Config_UART1.obj */
#pragma callt _putchar /* count:2,far,Config_UART1_user.obj */
#pragma callt _R_Config_UART1_Create /* count:2,far,Config_UART1.obj */
#pragma callt _get_fclk_freq_hz /* count:2,far,mcu_clocks.obj */
#pragma callt _R_Config_PORT_Create_UserInit /* count:1,far,Config_PORT_user.obj */
#pragma callt _R_Config_INTC_Create_UserInit /* count:1,far,Config_INTC_user.obj */
#pragma callt _R_Config_UART1_Create_UserInit /* count:1,far,Config_UART1_user.obj */
#pragma callt _bsp_init_hardware /* count:1,far,r_bsp_init.obj */
#pragma callt _R_BSP_GetFclkFreqHz /* count:1,far,r_bsp_common.obj */
#pragma callt _bl_app_mode_config /* count:1,far,task.obj */
#pragma callt _read_hw_version /* count:1,far,task.obj */
#pragma callt _R_Config_INTC_INTP1_Start /* count:1,far,Config_INTC.obj */
#pragma callt _R_RFD_CheckCFDFSeqEndStep2 /* count:1,far,r_rfd_common_control_api.obj */
#pragma callt _R_RFD_GetSeqErrorStatus /* count:1,far,r_rfd_common_control_api.obj */
#pragma callt _R_SAU1_Create /* count:1,far,r_cg_sau_common.obj */
#pragma callt _R_RFD_HOOK_EnterCriticalSection /* count:1,far,r_rfd_common_userown.obj */
#pragma callt _hdwinit /* count:1,far,hdwinit.obj */
#pragma callt _R_RFD_ClearSeqRegister /* count:1,far,r_rfd_common_control_api.obj */
#pragma callt _R_RFD_HOOK_ExitCriticalSection /* count:1,far,r_rfd_common_userown.obj */
#pragma callt _R_Systeminit /* count:1,far,r_cg_systeminit.obj */
#pragma callt _R_RFD_CheckCFDFSeqEndStep1 /* count:1,far,r_rfd_common_control_api.obj */
#pragma callt _R_Config_PORT_Create /* count:1,far,Config_PORT.obj */
#pragma callt _bsp_init_system /* count:1,far,r_bsp_init.obj */
#pragma callt _R_RFD_CheckFlashMemoryMode /* count:1,far,r_rfd_common_api.obj */
/* #pragma callt _R_RFD_Init */ /* count:1,far,r_rfd_common_api.obj */
/* #pragma callt _R_Config_UART1_Send */ /* count:1,far,Config_UART1.obj */
/* #pragma callt _R_Config_INTC_Create */ /* count:1,far,Config_INTC.obj */
/* #pragma callt _InitBlFlashDriver */ /* count:1,far,dd_flash.obj */
/* #pragma callt _bl_main */ /* count:1,far,boot.obj */
/* #pragma callt _Calc_CRC32Ieee8023 */ /* count:1,far,crc.obj */
/* #pragma callt _mcu_clock_setup */ /* count:1,far,mcu_clocks.obj */
/* #pragma callt _startup_branch */ /* count:1,far,task.obj */
/* #pragma callt _test_BlFlashDriver */ /* count:1,far,dd_flash.obj */
/* #pragma callt _AppFlashEraseBlock */ /* count:1,far,dd_flash.obj */
/* #pragma callt _CheckAppCRC32 */ /* count:1,far,crc.obj */
/* #pragma callt _BL_Code_INITSCT */ /* count:1,far,dd_flash.obj */
/* #pragma callt _AppFlashWrite64B */ /* count:1,far,dd_flash.obj */
/* #pragma callt _if_r_Config_INTC_intp1_interrupt */ /* count:1,near,Config_INTC_user.obj */
/* #pragma callt _if_r_Config_UART1_interrupt_send */ /* count:1,near,Config_UART1_user.obj */
/* #pragma callt _ForceReset */ /* count:0,far,unref,task.obj */
/* #pragma callt _R_RFD_ForceReset */ /* count:0,far,unref,r_rfd_common_control_api.obj */
/* #pragma callt _INTC_intp1_interrupt */ /* count:0,near,unref,task.obj */
/* #pragma callt _R_Config_PORT_ReadPmnValues */ /* count:0,far,unref,Config_PORT.obj */
/* #pragma callt _bl_app_mode_check */ /* count:0,far,unref,task.obj */
/* #pragma callt _read_sw_version */ /* count:0,far,unref,task.obj */
/* #pragma callt _read_touch_id */ /* count:0,far,unref,task.obj */
/* #pragma callt _read_display_id */ /* count:0,far,unref,task.obj */
/* #pragma callt _R_RFD_GetSecurityAndBootFlags */ /* count:0,far,unref,r_rfd_common_get_api.obj */
/* #pragma callt _R_SAU0_Create */ /* count:0,far,unref,r_cg_sau_common.obj */
/* #pragma callt _R_SAU0_Set_PowerOn */ /* count:0,far,unref,r_cg_sau_common.obj */
/* #pragma callt _R_SAU0_Set_PowerOff */ /* count:0,far,unref,r_cg_sau_common.obj */
/* #pragma callt _R_SAU1_Set_PowerOn */ /* count:0,far,unref,r_cg_sau_common.obj */
/* #pragma callt _R_SAU1_Set_PowerOff */ /* count:0,far,unref,r_cg_sau_common.obj */
/* #pragma callt _R_RFD_CheckExtraSeqEndStep2 */ /* count:0,far,unref,r_rfd_common_control_api.obj */
/* #pragma callt _R_RFD_ForceStopSeq */ /* count:0,far,unref,r_rfd_common_control_api.obj */
/* #pragma callt _R_Config_INTC_INTP1_Stop */ /* count:0,far,unref,Config_INTC.obj */
/* #pragma callt _dd_UART1_init */ /* count:0,far,unref,Config_UART1_user.obj */
/* #pragma callt _R_RFD_CheckExtraSeqEndStep1 */ /* count:0,far,unref,r_rfd_common_control_api.obj */
/* #pragma callt _R_RFD_SetBootAreaImmediately */ /* count:0,far,unref,r_rfd_common_extension_api.obj */
/* #pragma callt _r_rfd_wait_count */ /* count:0,far,unref,r_rfd_common_api.obj */
/* #pragma callt _R_RFD_WriteDataFlashReq */ /* count:0,far,unref,r_rfd_data_flash_api.obj */
/* #pragma callt _R_Pins_Create */ /* count:0,far,unref,Pin.obj */
/* #pragma callt _R_RFD_GetFSW */ /* count:0,far,unref,r_rfd_common_get_api.obj */
/* #pragma callt _R_Config_UART1_Receive */ /* count:0,far,unref,Config_UART1.obj */
/* #pragma callt _R_RFD_EraseDataFlashReq */ /* count:0,far,unref,r_rfd_data_flash_api.obj */
/* #pragma callt _R_Config_UART1_Stop */ /* count:0,far,unref,Config_UART1.obj */
/* #pragma callt _R_RFD_BlankCheckDataFlashReq */ /* count:0,far,unref,r_rfd_data_flash_api.obj */
/* #pragma callt _R_RFD_IVerifyDataFlashReq */ /* count:0,far,unref,r_rfd_data_flash_api.obj */
/* #pragma callt _R_RFD_SetDataFlashAccessMode */ /* count:0,far,unref,r_rfd_common_api.obj */
/* #pragma callt _isr_jump_uart1_handler */ /* count:0,near,unref,interrupt,static,isr_handler.obj */
/* #pragma callt _isr_jump_intp1_handler */ /* count:0,near,unref,interrupt,static,isr_handler.obj */
/* #pragma callt _AppFlashErase */ /* count:0,far,unref,dd_flash.obj */
/* #pragma callt _BL_CodeFlashControl */ /* count:0,far,unref,dd_flash.obj */
/* #pragma callt _R_BSP_SoftwareDelay */ /* count:0,far,unref,r_bsp_common.obj */


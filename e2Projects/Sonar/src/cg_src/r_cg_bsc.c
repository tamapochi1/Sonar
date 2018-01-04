/***********************************************************************************************************************
* DISCLAIMER
* This software is supplied by Renesas Electronics Corporation and is only intended for use with Renesas products.
* No other uses are authorized. This software is owned by Renesas Electronics Corporation and is protected under all
* applicable laws, including copyright laws. 
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIESREGARDING THIS SOFTWARE, WHETHER EXPRESS, IMPLIED
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
* Copyright (C) 2015, 2017 Renesas Electronics Corporation. All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* File Name    : r_cg_bsc.c
* Version      : Code Generator for RX71M V1.01.00.05 [26 May 2017]
* Device(s)    : R5F571MFDxFB
* Tool-Chain   : CCRX
* Description  : This file implements device driver for BSC module.
* Creation Date: 2017/12/28
***********************************************************************************************************************/

/***********************************************************************************************************************
Pragma directive
***********************************************************************************************************************/
/* Start user code for pragma. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "r_cg_macrodriver.h"
#include "r_cg_bsc.h"
/* Start user code for include. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
#include "r_cg_userdefine.h"

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
/* Start user code for global. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: R_BSC_Create
* Description  : This function initializes the Bus module.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_BSC_Create(void)
{
    /* Set BSC control registers */
    BSC.CSRECEN.WORD = _0002_BSC_RCVEN1_ENABLED | _0004_BSC_RCVEN2_ENABLED | _0008_BSC_RCVEN3_ENABLED | 
                       _0010_BSC_RCVEN4_ENABLED | _0020_BSC_RCVEN5_ENABLED | _0200_BSC_RCVENM1_ENABLED | 
                       _0400_BSC_RCVENM2_ENABLED | _0800_BSC_RCVENM3_ENABLED | _1000_BSC_RCVENM4_ENABLED | 
                       _2000_BSC_RCVENM5_ENABLED;
    BSC.BUSPRI.WORD = _0000_BSC_BPRA_FIX | _0000_BSC_BPRO_FIX | _0000_BSC_BPIB_FIX | _0000_BSC_BPGB_FIX | 
                      _0000_BSC_BPHB_FIX | _0000_BSC_BPFB_FIX | _0000_BSC_BPEB_FIX;

    /* Set high-drive output */
    PORT5.DSCR.BYTE = _01_P50_HIGHDRIVE_ENABLE | _04_P52_HIGHDRIVE_ENABLE | _08_P53_HIGHDRIVE_ENABLE;
    PORTA.DSCR.BYTE = _FF_PORTA_HIGHDRIVE_ENABLE;
    PORTB.DSCR.BYTE = _01_PB0_HIGHDRIVE_ENABLE | _02_PB1_HIGHDRIVE_ENABLE | _04_PB2_HIGHDRIVE_ENABLE | 
                      _08_PB3_HIGHDRIVE_ENABLE | _10_PB4_HIGHDRIVE_ENABLE | _20_PB5_HIGHDRIVE_ENABLE | 
                      _40_PB6_HIGHDRIVE_ENABLE | _80_PB7_HIGHDRIVE_ENABLE;
    PORTD.DSCR.BYTE = _FF_PORTD_HIGHDRIVE_ENABLE;
    PORTE.DSCR.BYTE = _FF_PORTE_HIGHDRIVE_ENABLE;
    /* Set address output enable registers */
    MPC.PFAOE0.BYTE = _01_BSC_A8E_ENABLED | _02_BSC_A9E_ENABLED | _04_BSC_A10E_ENABLED | _08_BSC_A11E_ENABLED | 
                      _10_BSC_A12E_ENABLED | _20_BSC_A13E_ENABLED | _40_BSC_A14E_ENABLED | _80_BSC_A15E_ENABLED;

    /* Set external bus control registers */
    MPC.PFBCR0.BYTE |= _01_BSC_ADRLE_ENABLED | _10_BSC_DHE_ENABLED;
    MPC.PFBCR1.BYTE |= _00_BSC_ALEOE_DISABLED | _10_BSC_MDSDE_ENABLED | _40_BSC_DQM1E_ENABLED;
    /* Set BC0# pin */
    PORTA.PMR.BYTE &= 0xFEU;
    /* Set WR0# pin */
    PORT5.PMR.BYTE &= 0xFEU;
    /* Set RD# pin */
    PORT5.PMR.BYTE &= 0xFBU;
    /* Set CKE pin */
    PORT6.PMR.BYTE &= 0xDFU;
    /* Set SDCS# pin */
    PORT6.PMR.BYTE &= 0xFDU;
    /* Set RAS# pin */
    PORT6.PMR.BYTE &= 0xFBU;
    /* Set CAS# pin */
    PORT6.PMR.BYTE &= 0xF7U;
    /* Set WE# pin */
    PORT6.PMR.BYTE &= 0xEFU;
    /* Set DQM0 pin */
    PORT6.PMR.BYTE &= 0xBFU;
    /* Set DQM1 pin */
    PORT6.PMR.BYTE &= 0x7FU;

    /* Set external bus and on-chip rom settings */
    SYSTEM.SCKCR.BIT.PSTOP1 = 1U;
    SYSTEM.SYSCR0.WORD = _5A01_BSC_ROME_ENABLED | _5A02_BSC_EXBE_ENABLED;
    SYSTEM.SCKCR.BIT.PSTOP1 = 0U;
}
/***********************************************************************************************************************
* Function Name: R_BSC_InitializeSDRAM
* Description  : This function initial SDRAM setting.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_BSC_InitializeSDRAM(void)
{
    /* Set SDCS control registers */
    BSC.SDCCR.BIT.EXENB = 0U;
    /* Wait for EXENB bit is clear to 0 */
    while (0U != BSC.SDCCR.BIT.EXENB);

    BSC.SDRFEN.BIT.RFEN = 0U;
    BSC.SDSELF.BIT.SFEN = 0U;
    /* Wait for status bits in SDSR are 0 */
    while (0x00U != BSC.SDSR.BYTE);

    BSC.SDIR.WORD = _0005_BSC_ARFI_8 | _0020_BSC_ARFC_2 | _0000_BSC_PRC_3;
    BSC.SDICR.BIT.INIRQ = _01_BSC_INIT_SEQUENCE_START;
    /* Wait for status bits in SDSR are 0 */
    while (0x00U != BSC.SDSR.BYTE);

    BSC.SDCCR.BYTE = _00_BSC_BSIZE_16;
    BSC.SDMOD.WORD = _0020_BSC_MODE_REG_VALUE;
    BSC.SDTR.LONG = _00000002_BSC_CL_2 | _00000100_BSC_WR_2 | _00000000_BSC_RP_1 | _00000000_BSC_RCD_1 | 
                    _00020000_BSC_RAS_3;
    BSC.SDADR.BYTE = _02_BSC_MXC_BIT_SHIFT_10;
    BSC.SDAMOD.BYTE = _00_BSC_SD_CONTINUOUS_DISABLED;
    BSC.SDCMOD.BYTE = _00_BSC_SD_EMODE_SAME;
    BSC.SDRFCR.WORD = _3E7_BSC_RFC_VALUE | _3000_BSC_REFW_4;
    BSC.SDRFEN.BIT.RFEN = 1U;
    BSC.SDCCR.BIT.EXENB = 1U;
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

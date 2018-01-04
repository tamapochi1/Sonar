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
* File Name    : r_cg_hardware_setup.c
* Version      : Code Generator for RX71M V1.01.00.05 [26 May 2017]
* Device(s)    : R5F571MFDxFB
* Tool-Chain   : CCRX
* Description  : This file implements system initializing function.
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
#include "r_cg_cgc.h"
#include "r_cg_bsc.h"
#include "r_cg_scifa.h"
#include "r_cg_riic.h"
/* Start user code for include. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
#include "r_cg_userdefine.h"

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
/* Start user code for global. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: r_undefined_exception
* Description  : This function is undefined interrupt service routine.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void r_undefined_exception(void)
{
    /* Start user code. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
}
/***********************************************************************************************************************
* Function Name: R_Systeminit
* Description  : This function initializes every macro.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_Systeminit(void)
{
    /* Enable writing to registers related to operating modes, LPC, CGC and software reset */
    SYSTEM.PRCR.WORD = 0xA50BU; 

    /* Enable writing to MPC pin function control registers */
    MPC.PWPR.BIT.B0WI = 0U;
    MPC.PWPR.BIT.PFSWE = 1U;

    /* Initialize non-existent pins */
    PORT1.PDR.BYTE = 0x03U;
    PORT9.PDR.BYTE = 0xF0U;
    PORTF.PDR.BYTE = 0x1FU;
    PORTG.PDR.BYTE = 0xFFU;

    /* Set peripheral settings */
    R_CGC_Create();
    R_BSC_Create();
    R_SCIFA10_Create();
    R_SCIFA11_Create();
    R_RIIC0_Create();

    /* Register undefined interrupt */
    R_BSP_InterruptWrite(BSP_INT_SRC_UNDEFINED_INTERRUPT,(bsp_int_cb_t)r_undefined_exception);

    /* Register BL1 group interrupt TEI0 */
    R_BSP_InterruptWrite(BSP_INT_SRC_BL1_RIIC0_TEI0,(bsp_int_cb_t)r_riic0_transmitend_interrupt);

    /* Register BL1 group interrupt EEI0 */
    R_BSP_InterruptWrite(BSP_INT_SRC_BL1_RIIC0_EEI0,(bsp_int_cb_t)r_riic0_error_interrupt);

    /* Register AL0 group interrupt TEIF10 */
    R_BSP_InterruptWrite(BSP_INT_SRC_AL0_SCIFA10_TEIF10,(bsp_int_cb_t)r_scifa10_teif_interrupt);

    /* Register AL0 group interrupt ERIF10 */
    R_BSP_InterruptWrite(BSP_INT_SRC_AL0_SCIFA10_ERIF10,(bsp_int_cb_t)r_scifa10_erif_interrupt);

    /* Register AL0 group interrupt BRIF10 */
    R_BSP_InterruptWrite(BSP_INT_SRC_AL0_SCIFA10_BRIF10,(bsp_int_cb_t)r_scifa10_brif_interrupt);

    /* Register AL0 group interrupt TEIF11 */
    R_BSP_InterruptWrite(BSP_INT_SRC_AL0_SCIFA11_TEIF11,(bsp_int_cb_t)r_scifa11_teif_interrupt);

    /* Register AL0 group interrupt ERIF11 */
    R_BSP_InterruptWrite(BSP_INT_SRC_AL0_SCIFA11_ERIF11,(bsp_int_cb_t)r_scifa11_erif_interrupt);

    /* Register AL0 group interrupt BRIF11 */
    R_BSP_InterruptWrite(BSP_INT_SRC_AL0_SCIFA11_BRIF11,(bsp_int_cb_t)r_scifa11_brif_interrupt);

    /* Disable writing to MPC pin function control registers */
    MPC.PWPR.BIT.PFSWE = 0U;    
    MPC.PWPR.BIT.B0WI = 1U;     

    /* Enable protection */
    SYSTEM.PRCR.WORD = 0xA500U;  
}
/***********************************************************************************************************************
* Function Name: HardwareSetup
* Description  : This function initializes hardware setting.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void HardwareSetup(void)
{
    R_Systeminit();
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
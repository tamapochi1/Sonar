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
 * Copyright (C) 2014(2016) Renesas Electronics Corporation. All rights reserved.
 ***********************************************************************************************************************/
/*******************************************************************************
 * File Name    : r_usb_rsk_lowpower.c
 * Description  : RX64M RSK processing
 ******************************************************************************
 * History : DD.MM.YYYY Version Description
 *         : 08.01.2014 1.00 First Release
 *         : 26.12.2014 1.10 RX71M is added
 *         : 30.09.2015 1.11 RX63N/RX631 is added.
 *         : 30.09.2016 1.20 RX65N/RX651 is added.
 ******************************************************************************/

/******************************************************************************
 Includes   <System Includes> , "Project Includes"
 ******************************************************************************/
#include "r_usb_basic_if.h"
#include "r_usb_pcdc_apl_config.h"

#if defined(USE_LPW)

#include "r_usb_rsk_lowpower.h"

#if OPERATION_MODE == USB_UART
#include "r_usb_pcdc_if.h"
#include "r_usb_rsk_sci.h"
#endif /* OPERATION_MODE == USB_UART */

/******************************************************************************
 Constant macro definitions
 ******************************************************************************/

/******************************************************************************
 Private global variables and functions
 ******************************************************************************/
static void usb_cpu_detach_sleep (void);
static void usb_cpu_suspend_sleep (void);

/******************************************************************************
 Renesas Abstracted RSK functions
 ******************************************************************************/

/******************************************************************************
 Function Name   : usb_cpu_detach_sleep
 Description     :
 Arguments       : none
 Return value    : none
 ******************************************************************************/
static void usb_cpu_detach_sleep (void)
{
    uint8_t dtcst;

    /* Protect register (protect off)
     b0    PRC0     Protect bit0
     b1    PRC1     Protect bit1
     b2    Reserved 0
     b3    PRC3     Protect bit3
     b7-b4 Reserved 0
     b15-b8 PRKEY   PRC Key code bit
     */
    SYSTEM.PRCR.WORD = 0xA503; /* protect off */

    /* DTC Transfer disable
     b0    DTCST    DTC module start bit
     b7-b1 Reserved 0
     */
    dtcst = DTC.DTCST.BIT.DTCST; /* Store DTCST */
    DTC.DTCST.BIT.DTCST = 0;

    /* RTC control register3 (Sub clock OSC input disable)
     b0      RTCEN    Sub clock OSC input enable/disable
     b7-b1   Reserved 0
     */
    RTC.RCR3.BIT.RTCEN = 0;

    /* Sub clock Oscillator control register (SOSTP=Sub clock enable)
     b0      SOSTP    Sub clock Oscillator stop bit
     b7-b1   Reserved 0
     */
    SYSTEM.SOSCCR.BIT.SOSTP = 1;

    /* Standby control register (Software Standby Shift)
     b7-b0  Reserved 0
     b12-b8 STS      Standby timer select bit
     b13    Reserved 0
     b14    OPE      Output port enable bit
     b15    SSBY     Software standby bit
     */
    SYSTEM.SBYCR.BIT.SSBY = 1;

    /* Deep Standby control register (Deep Standby Shift)
     b0-b1 DEEPCUT  RAM off bit
     b5-b2 Reserved 0
     b6    IOKEEP   IO port keep bit
     b7    DPSBY    Deep standby bit
     */
    SYSTEM.DPSBYCR.BIT.DPSBY = 0;

    /* Standby control register (Bus Signal Output status keep)
     b7-b0  Reserved 0
     b12-b8 STS      Standby timer select bit
     b13    Reserved 0
     b14    OPE      Output port enable bit
     b15    SSBY     Software standby bit
     */
    SYSTEM.SBYCR.BIT.OPE = 1;

    /* Oscillator stop detect control register (disable)
     b0     OSTDIE   Oscillator stop detect interrupt enable
     b1-b6  Reserved 0
     b7     OSTDE    Oscillator stop detect enable
     */
    SYSTEM.OSTDCR.BYTE = 0x00;
    while (0 != SYSTEM.OSTDCR.BYTE)
    {
        /* none */
    }

    hw_usb_pset_enb_rsme();

#if OPERATION_MODE == USB_UART
    SCI_TXD_PIN_CLEAR
    SCI_RXD_PIN_CLEAR
#endif /* OPERATION_MODE == USB_UART */

#if USB_CFG_USE_USBIP == USB_CFG_IP0
    ICU.IPR[IPR_USB_USBR0].BYTE = 7; /* Set Interrupt Priority USBR0 */
    ICU.IER[IER_USB_USBR0].BIT.IEN2 = 1; /* Enable Interrupt USBR0       */
    while (1 != ICU.IER[IER_USB_USBR0].BIT.IEN2)
    {
        /* none */
    }
#else  /* USB_CFG_USE_USBIP == USB_CFG_IP0 */
    ICU.IPR[IPR_USB_USBR1].BYTE = 7; /* Set Interrupt Priority USBR0 */
    ICU.IER[IER_USB_USBR1].BIT.IEN3 = 1; /* Enable Interrupt USBR0       */
    while (1 != ICU.IER[IER_USB_USBR1].BIT.IEN3)
    {
        /* none */
    }
#endif /* USB_CFG_USE_USBIP == USB_CFG_IP0 */

    wait(); /* Wait */

#if OPERATION_MODE == USB_UART
    SCI_TXD_PIN_RESUME
    SCI_RXD_PIN_RESUME
#endif /* OPERATION_MODE == USB_UART */

    DTC.DTCST.BIT.DTCST = dtcst; /* Restore DTCST */
} /* End of function usb_cpu_detach_sleep */

/******************************************************************************
 Function Name   : usb_cpu_suspend_sleep
 Description     :
 Arguments       : none
 Return value    : none
 ******************************************************************************/
static void usb_cpu_suspend_sleep (void)
{
    /* Protect register (protect off)
     b0    PRC0     Protect bit0
     b1    PRC1     Protect bit1
     b2    Reserved 0
     b3    PRC3     Protect bit3
     b7-b4 Reserved 0
     b15-b8 PRKEY   PRC Key code bit
     */
    SYSTEM.PRCR.WORD = 0xA503; /* protect off */

    /* Standby control register (Software Standby Shift)
     b7-b0  Reserved 0
     b12-b8 STS      Standby timer select bit
     b13    Reserved 0
     b14    OPE      Output port enable bit
     b15    SSBY     Software standby bit
     */
    SYSTEM.SBYCR.BIT.SSBY = 0;
    while ( 0 != SYSTEM.SBYCR.BIT.SSBY)
    {
        /* none */
    }

    wait(); /* Wait */
} /* End of function usb_cpu_suspend_sleep */


/******************************************************************************
 Function Name   : low_power_mcu
 Description     :
 Arguments       : none
 Return value    : none
 ******************************************************************************/
void low_power_mcu(void)
{
    usb_info_t  info;
    usb_ctrl_t  ctrl;
    usb_err_t   ret_code = USB_SUCCESS;

    ctrl.module = USB_CFG_USE_USBIP;
    ret_code = R_USB_GetInformation(&ctrl, &info);
    if (USB_SUCCESS != ret_code)
    {
        return;
    }

    if (USB_STS_DETACH == info.status)
    {
        usb_cpu_detach_sleep();
    }
    else if (USB_STS_SUSPEND == info.status)
    {
        usb_cpu_suspend_sleep();
    }
    else
    {
    }
} /* End of function low_power_mcu */
#endif /* defined(USE_LPW) */

/******************************************************************************
 End  Of File
 ******************************************************************************/

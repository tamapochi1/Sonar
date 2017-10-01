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
 * File Name    : r_usb_pcdc_apl.c
 * Description  : USB Peripheral Communications Devices Class Sample Code
 *******************************************************************************
 * History : DD.MM.YYYY Version Description
 *         : 08.01.2014 1.00 First Release
 *         : 26.12.2014 1.10 RX71M is added
 *         : 30.09.2015 1.11 RX63N/RX631 is added.
 *         : 30.09.2016 1.20 RX65N/RX651 is added.
 ******************************************************************************/

/******************************************************************************
 Includes   <System Includes> , "Project Includes"
 ******************************************************************************/
#include    "r_usb_pcdc_apl.h"

#if OPERATION_MODE == USB_ECHO
/******************************************************************************
 Macro definitions
 ***************************************************************************#***/

/******************************************************************************
 Private global variables and functions
 ******************************************************************************/
static void     usb_pin_setting (void);
static uint8_t  g_buf[DATA_LEN];

const static usb_descriptor_t usb_descriptor =
{   
    g_apl_device,                   /* Pointer to the device descriptor */
    g_apl_configuration,            /* Pointer to the configuration descriptor for Full-speed */
    USB_NULL,                       /* Pointer to the configuration descriptor for Hi-speed */
    USB_NULL,                       /* Pointer to the qualifier descriptor */
    g_apl_string_table              /* Pointer to the string descriptor table */
};

/******************************************************************************
 Renesas Peripheral Communications Devices Class Sample Code functions
 ******************************************************************************/

/******************************************************************************
 Function Name   : usb_main
 Description     : Peripheral CDC application main process
 Arguments       : none
 Return value    : none
 ******************************************************************************/
void usb_main (void)
{
    usb_ctrl_t  ctrl;
    usb_cfg_t   cfg;

    usb_pin_setting(); /* USB MCU pin setting */

    ctrl.module     = USE_USBIP;
    ctrl.type       = USB_PCDC;
    cfg.usb_speed   = USB_SUPPORT_SPEED; /* USB_HS/USB_FS */
    cfg.usb_mode    = USB_PERI;
    cfg.p_usb_reg   = (usb_descriptor_t *)&usb_descriptor;
    R_USB_Open(&ctrl, &cfg); /* Initializes the USB module */

    /* Loop back between PC(TerminalSoft) and USB MCU */
    while (1)
    {
        switch (R_USB_GetEvent(&ctrl))
        {
            case USB_STS_CONFIGURED :
            case USB_STS_WRITE_COMPLETE :
                ctrl.type = USB_PCDC;
                R_USB_Read(&ctrl, g_buf, DATA_LEN);
            break;
            
            case USB_STS_READ_COMPLETE :
                R_USB_Write(&ctrl, g_buf, ctrl.size);
            break;
            
            case USB_STS_SUSPEND :
            case USB_STS_DETACH :
#if defined(USE_LPW)
                 low_power_mcu();
#endif /* defined(USE_LPW) */
            break;

            default :
            break;
        }
    }
} /* End of function usb_main() */

/******************************************************************************
 Function Name   : usb_pin_setting
 Description     : USB Pin Setting
 Arguments       : none
 Return value    : none
 ******************************************************************************/
static void usb_pin_setting (void)
{
    R_BSP_RegisterProtectDisable(BSP_REG_PROTECT_LPC_CGC_SWR);
    R_BSP_RegisterProtectDisable(BSP_REG_PROTECT_MPC);

#if USE_USBIP == USE_USBIP0
    PORT1.PMR.BIT.B6    = 0u;
    MPC.P16PFS.BYTE     = 0x11; /* USB0_VBUS */
    PORT1.PMR.BIT.B6    = 1u;

#else   /* USE_USBIP == USE_USBIP0 */
    PORT1.PMR.BIT.B1        = 0u;
    MPC.P11PFS.BYTE         = 0x14; /* USBA_VBUS */
    PORT1.PMR.BIT.B1        = 1u;

#endif  /* USE_USBIP == USE_USBIP0 */

    R_BSP_RegisterProtectEnable(BSP_REG_PROTECT_MPC);
    R_BSP_RegisterProtectEnable(BSP_REG_PROTECT_LPC_CGC_SWR);
}/* End of function usb_pin_setting */
/******************************************************************************
 End of function usb_mcu_init
 ******************************************************************************/
#endif  /* OPERATION_MODE == USB_ECHO */

/******************************************************************************
 End  Of File
 ******************************************************************************/


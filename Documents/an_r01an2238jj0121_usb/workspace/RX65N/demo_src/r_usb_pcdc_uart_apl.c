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

#if OPERATION_MODE == USB_UART
/******************************************************************************
 Macro definitions
 ***************************************************************************#***/

/******************************************************************************
 Private global variables and functions
 ******************************************************************************/
static  void        usb_pin_setting (void);
static  uint8_t     g_usb_data[DATA_LEN];
static  uint8_t     g_sci_data[DATA_LEN];

static  uint32_t    g_read_size = 0UL;
static  uint8_t     g_is_usb_bulk_writing = USB_NO;
static  uint8_t     g_is_usb_interrupt_writing = USB_NO;
static  usb_pcdc_linecoding_t g_line_coding;


const static usb_descriptor_t usb_descriptor =
{   
    g_apl_device,                   /* Pointer to the device descriptor */
    g_apl_configuration,            /* Pointer to the configuration descriptor for Full-speed */
    USB_NULL,                       /* Pointer to the configuration descriptor for Hi-speed */
    USB_NULL,                       /* Pointer to the qualifier descriptor */
    g_apl_string_table              /* Pointer to the string descriptor table */
};

uint8_t     g_is_serial_state = 0;
uint8_t     g_serial_state[2];

    sci_hdl_t   console;

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
    uint16_t    size;
    usb_err_t   err;
    sci_err_t   sci_err;

    usb_pin_setting(); /* USB MCU pin setting */

    USB_RSK_SCI_INIT();

#if (USE_USBIP == USE_USBIP0)
    ctrl.module     = USB_IP0;
#endif

#if (USE_USBIP == USE_USBIP1)
    ctrl.module     = USB_IP1;
#endif

    ctrl.type       = USB_PCDC;
    cfg.usb_speed   = USB_SUPPORT_SPEED; /* USB_HS/USB_FS */
    cfg.usb_mode = USB_PERI;
    cfg.p_usb_reg     = (usb_descriptor_t *)&usb_descriptor;
    R_USB_Open(&ctrl, &cfg); /* Initializes the USB module */

    while (1)
    {
        switch (R_USB_GetEvent(&ctrl))
        {
            case USB_STS_CONFIGURED :
                ctrl.type = USB_PCDC;
                R_USB_Read(&ctrl, g_usb_data, DATA_LEN);
            break;
            
            case USB_STS_WRITE_COMPLETE :
                if (USB_PCDC == ctrl.type)
                {
                    /* Bulk IN(CDC data) transfer has been completed */
                    g_is_usb_bulk_writing = USB_NO;
                }
                else
                {
                    /* Interrupt IN(SerialState) transfer has been completed */
                    g_is_usb_interrupt_writing = USB_NO;
                }
            break;
            
            case USB_STS_READ_COMPLETE :
                g_read_size = ctrl.size;    /* Bulk OUT data size */
            break;

            case USB_STS_REQUEST : /* Receive Class Request */
                if (USB_PCDC_SET_LINE_CODING == (ctrl.setup.type & USB_BREQUEST))
                {
                    ctrl.type = USB_REQUEST;
                    R_USB_Read(&ctrl, (uint8_t *) &g_line_coding, LINE_CODING_LENGTH);
                }
                else if (USB_PCDC_GET_LINE_CODING == (ctrl.setup.type & USB_BREQUEST))
                {
                    ctrl.type = USB_REQUEST;
                    R_USB_Write(&ctrl, (uint8_t *) &g_line_coding, LINE_CODING_LENGTH);
                }
                else
                {
                    /* none */
                }
            break;

            case USB_STS_REQUEST_COMPLETE : /* Complete Class Request */
                if (USB_PCDC_SET_LINE_CODING == (ctrl.setup.type & USB_BREQUEST))
                {
                    /* RS-232C Line set.(Parameter : line_coding) */
                    usb_cpu_Sci_Set1(&g_line_coding);
                }
                else if (USB_PCDC_GET_LINE_CODING == (ctrl.setup.type & USB_BREQUEST))
                {
                    /* none */
                }
                else if (USB_PCDC_SET_CONTROL_LINE_STATE == (ctrl.setup.type & USB_BREQUEST))
                {
                    /* DTR & RTS set value store */

                    /* RS-232 signal RTS & DTR Set */
                    /* If RTS/DTR control function is prepared, calls this function here */
                }
                else
                {
                    /* none */
                }
            break;

            case USB_STS_SUSPEND :
            case USB_STS_DETACH :
#if defined(USE_LPW)
                low_power_mcu();
#endif /* defined(USE_LPW) */
            break;
            
            case USB_STS_NONE:
                if (USB_NO == g_is_usb_bulk_writing)
                {
                    /* Check whether SCI data is reveived or not */ 
                    sci_err = R_SCI_Control(console, SCI_CMD_RX_Q_BYTES_AVAIL_TO_READ, (void *)&size);
                    
                    if ((size > 0UL) && (SCI_SUCCESS == sci_err))
                    {
                        /* Receive the SCI data */
                        sci_err = R_SCI_Receive(console, (uint8_t *)&g_sci_data, size);
                        if (SCI_SUCCESS == sci_err)
                        {
                            /* Send the received SCI data to USB Host */
                            ctrl.type = USB_PCDC;
                            err = R_USB_Write(&ctrl, (uint8_t *)&g_sci_data, size);
                            if (USB_SUCCESS == err)
                            {
                                g_is_usb_bulk_writing = USB_YES;
                            }
                        }
                    }
                }
                if (g_read_size > 0UL)
                {
                    /* Check whether the sending of SCI data is possible or not */ 
                    sci_err = R_SCI_Control(console, SCI_CMD_TX_Q_BYTES_FREE, (void *)&size);
                    if ((size >= g_read_size) && (SCI_SUCCESS == sci_err))
                    {
                        /* Sending the received USB data(Bulk OUT) to COM */
                        sci_err = R_SCI_Send(console, (uint8_t *)&g_usb_data, g_read_size);
                        if (SCI_SUCCESS == sci_err)
                        {
                            g_read_size = 0UL;

                            ctrl.type = USB_PCDC;
                            R_USB_Read(&ctrl, g_usb_data, DATA_LEN);
                        }
                    }
                }
                if (USB_NO == g_is_usb_interrupt_writing)
                {
                    /* Check whether the SerialState information is or not*/
                    if (0 != g_is_serial_state)
                    {
                        /* Send the SerialState information for SCI to USB Host */
                        ctrl.type = USB_PCDCC;
                        err = R_USB_Write(&ctrl, (uint8_t *)&g_serial_state, 2);
                        if (USB_SUCCESS == err)
                        {
                            g_is_usb_interrupt_writing = USB_YES;
                            g_is_serial_state = 0;
                        }
                    }
                }
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

    PORT1.PMR.BIT.B6    = 0u;
    MPC.P16PFS.BYTE     = 0x11; /* USB0_VBUS */
    PORT1.PMR.BIT.B6    = 1u;

    R_BSP_RegisterProtectEnable(BSP_REG_PROTECT_MPC);
    R_BSP_RegisterProtectEnable(BSP_REG_PROTECT_LPC_CGC_SWR);
}/* End of function usb_pin_setting */
/******************************************************************************
 End of function usb_mcu_init
 ******************************************************************************/
#endif  /* OPERATION_MODE == USB_UART */

/******************************************************************************
 End  Of File
 ******************************************************************************/


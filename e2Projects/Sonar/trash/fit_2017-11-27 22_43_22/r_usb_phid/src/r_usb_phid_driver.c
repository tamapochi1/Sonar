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
 * Copyright (C) 2015(2017) Renesas Electronics Corporation. All rights reserved.
 ***********************************************************************************************************************/
/***********************************************************************************************************************
 * File Name    : r_usb_phid_driver.c
 * Description  : USB HID application code
 ***********************************************************************************************************************/
/**********************************************************************************************************************
 * History : DD.MM.YYYY Version Description
 *         : 30.09.2015 1.11 First Release
 *         : 30.09.2016 1.20 RX65N/RX651 is added.
 *         : 26.01.2017 1.21 phid_read_complete(),phid_write_complete is fixed.
 *         : 30.09.2017 1.22 Changed function names
 *                           "phid_write_complete"->"usb_phid_write_complete"
 *                           "phid_read_complete"->"usb_phid_read_complete"
 ***********************************************************************************************************************/

/******************************************************************************
 Includes   <System Includes> , "Project Includes"
 ******************************************************************************/

#include "r_usb_basic_if.h"
#include "r_usb_typedef.h"
#include "r_usb_extern.h"
#include "r_usb_bitdefine.h"
#include "r_usb_reg_access.h"
#include "r_usb_phid_if.h"
#include "r_usb_phid.h"

/******************************************************************************
 Private global variables and functions
 ******************************************************************************/


/******************************************************************************
 Exported global functions (to be accessed by other files)
 ******************************************************************************/
usb_utr_t g_usb_phid_smpl_trn_msg;

/******************************************************************************
 Renesas Abstracted USB Driver functions
 ******************************************************************************/

/******************************************************************************
 Function Name   : usb_phid_data_trans
 Description     : Start of data transfer
 Arguments       : uint16_t pipe            : Pipe number
                 : uint32_t size            : Data size
                 : uint8_t  *ptable         : Pointer to the data area
                 : usb_cb_t complete        : Callback function
 Return value    : none
 ******************************************************************************/
void usb_phid_data_trans (uint16_t pipe, uint32_t size, uint8_t * ptable, usb_cb_t complete)
{

    g_usb_phid_smpl_trn_msg.keyword = pipe; /* Set pipe no. for USB transfer. */
    g_usb_phid_smpl_trn_msg.p_tranadr = ptable; /* Transfer data Start address */
    g_usb_phid_smpl_trn_msg.tranlen = size; /* Transfer data length */
    g_usb_phid_smpl_trn_msg.complete = complete; /* Callback function */

    /* Peripheral HID Transfer Start. */
    usb_pstd_transfer_start((usb_utr_t *) &g_usb_phid_smpl_trn_msg);
}
/******************************************************************************
 End of function usb_phid_data_trans
 ******************************************************************************/

/******************************************************************************
 Function Name   : usb_phid_write_complete
 Description     : CallBack Function
 Arguments       : usb_utr_t    *mess   : Pointer to usb_utr_t structure
                 : uint16_t     data1   : Not used
                 : uint16_t     data2   : Not used
 Return          : none
 ******************************************************************************/
void usb_phid_write_complete (usb_utr_t *mess, uint16_t data1, uint16_t data2)
{
    usb_ctrl_t ctrl;

    ctrl.pipe   = mess->keyword;                      /* Pipe number setting */
    ctrl.type   = USB_PHID;                           /* PHID class  */
    ctrl.module = USB_CFG_USE_USBIP;
    ctrl.type   = USB_PHID;                           /* HID Data class  */
    if (USB_DATA_NONE == mess->status)
    {
        ctrl.status = USB_SUCCESS;
    }
    else
    {
        ctrl.status = USB_ERR_NG;
    }
    usb_set_event(USB_STS_WRITE_COMPLETE, &ctrl);
}
/******************************************************************************
 End of function usb_phid_write_complete
 ******************************************************************************/

/******************************************************************************
 Function Name   : usb_phid_read_complete
 Description     : CallBack Function
 Arguments       : usb_utr_t    *mess   : Pointer to usb_utr_t structure
                 : uint16_t     data1   : Not used
                 : uint16_t     data2   : Not used
 Return          : none
 ******************************************************************************/
void usb_phid_read_complete (usb_utr_t *mess, uint16_t data1, uint16_t data2)
{
    usb_ctrl_t ctrl;

    /* Set Receive data length */
    ctrl.size   = g_usb_read_request_size[USB_CFG_USE_USBIP][mess->keyword] - mess->tranlen;
    ctrl.pipe   = mess->keyword;                    /* Pipe number setting */
    ctrl.module = USB_CFG_USE_USBIP;

    ctrl.type   = USB_PHID;                         /* Device class setting  */
    switch (mess->status)
    {
        case USB_DATA_OK :
            ctrl.status = USB_SUCCESS;
        break;
        case USB_DATA_SHT :
            ctrl.status = USB_ERR_SHORT;
        break;
        case USB_DATA_OVR :
            ctrl.status = USB_ERR_OVER;
        break;
        case USB_DATA_ERR :
        default :
            ctrl.status = USB_ERR_NG;
        break;
    }
    usb_set_event(USB_STS_READ_COMPLETE, &ctrl);
}
/******************************************************************************
 End of function usb_phid_read_complete
 ******************************************************************************/


/******************************************************************************
 End  Of File
 ******************************************************************************/

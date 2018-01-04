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
* File Name    : r_cg_riic.c
* Version      : Code Generator for RX71M V1.01.00.05 [26 May 2017]
* Device(s)    : R5F571MFDxFB
* Tool-Chain   : CCRX
* Description  : This file implements device driver for RIIC module.
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
#include "r_cg_riic.h"
/* Start user code for include. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
#include "r_cg_userdefine.h"

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
uint8_t    g_riic0_mode_flag;               /* RIIC0 master transmit receive flag */
uint8_t    g_riic0_state;                   /* RIIC0 state */
uint16_t   g_riic0_slave_address;           /* RIIC0 slave address */
uint8_t *  gp_riic0_tx_address;             /* RIIC0 transmit buffer address */
uint16_t   g_riic0_tx_count;                /* RIIC0 transmit data number */
uint8_t *  gp_riic0_rx_address;             /* RIIC0 receive buffer address */
uint16_t   g_riic0_rx_count;                /* RIIC0 receive data number */
uint16_t   g_riic0_rx_length;               /* RIIC0 receive data length */
uint8_t    g_riic0_dummy_read_count;        /* RIIC0 count for dummy read */
/* Start user code for global. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: R_RIIC0_Create
* Description  : This function initializes the RIIC0 Bus Interface.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_RIIC0_Create(void)
{
    MSTP(RIIC0) = 0U;                /* Cancel RIIC0 module stop state */
    RIIC0.ICCR1.BIT.ICE = 0U;        /* SCL and SDA pins in inactive state */
    RIIC0.ICCR1.BIT.IICRST = 1U;     /* RIIC reset */
    RIIC0.ICCR1.BIT.ICE = 1U;        /* Internal reset */

    /* Set transfer bit rate */
    RIIC0.ICMR1.BYTE |= _10_IIC_PCLK_DIV_2;
    RIIC0.ICBRL.BYTE = _FF_IIC0_SCL_LOW_LEVEL_PERIOD;
    RIIC0.ICBRH.BYTE = _F8_IIC0_SCL_HIGH_LEVEL_PERIOD;

    /* Set ICMR2 and ICMR3 */
    RIIC0.ICMR2.BYTE = _00_IIC_NO_OUTPUT_DELAY;
    RIIC0.ICMR3.BIT.NF = 0U;

    /* Set ICFER */
    RIIC0.ICFER.BYTE = _00_IIC_TIMEOUT_FUNCTION_DISABLE | _02_IIC_MASTER_ARBITRATION_ENABLE | 
                       _00_IIC_NACK_ARBITRATION_DISABLE | _00_IIC_SLAVE_ARBITRATION_DISABLE | 
                       _10_IIC_NACK_SUSPENSION_ENABLE | _20_IIC_NOISE_FILTER_USED | _00_IIC_FASTPLUS_MODE_DISABLE;

    /* Set ICIER */
    RIIC0.ICIER.BYTE = _00_IIC_TIMEOUT_INTERRUPT_DISABLE | _02_IIC_ARBITRATION_LOST_INTERRUPT_ENABLE | 
                       _04_IIC_START_CONDITION_INTERRUPT_ENABLE | _08_IIC_STOP_CONDITION_INTERRUPT_ENABLE | 
                       _10_IIC_NACK_INTERRUPT_ENABLE | _20_IIC_RECEIVE_DATA_INTERRUPT_ENABLE | 
                       _40_IIC_TRANSMIT_END_INTERRUPT_ENABLE | _80_IIC_TRANSMIT_EMPTY_INTERRUPT_ENABLE;

    /* Cancel internal reset */
    RIIC0.ICCR1.BIT.IICRST = 0U;

    /* Set interrupt priority */
    IPR(RIIC0, TXI0) = _0F_IIC_PRIORITY_LEVEL15;
    IPR(RIIC0, RXI0) = _0F_IIC_PRIORITY_LEVEL15;

    /* Set SCL0 pin */
    MPC.P12PFS.BYTE = 0x0FU;
    PORT1.PMR.BYTE |= 0x04U;

    /* Set SDA0 pin */
    MPC.P13PFS.BYTE = 0x0FU;
    PORT1.PMR.BYTE |= 0x08U;
}

/***********************************************************************************************************************
* Function Name: R_RIIC0_Start
* Description  : This function starts the RIIC0 Bus Interface.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_RIIC0_Start(void)
{
    /* Clear interrupt flag */
    IR(RIIC0, TXI0) = 0U;
    IR(RIIC0, RXI0) = 0U;

    /* Enable RIIC0 interrupt */
    IEN(RIIC0, TXI0) = 1U;
    IEN(RIIC0, RXI0) = 1U;
    ICU.GENBL1.BIT.EN13 = 1U;
    ICU.GENBL1.BIT.EN14 = 1U;
}

/***********************************************************************************************************************
* Function Name: R_RIIC0_Stop
* Description  : This function stops the RIIC0 Bus Interface.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_RIIC0_Stop(void)
{
    /* Clear interrupt flag */
    IR(RIIC0, TXI0) = 0U;
    IR(RIIC0, RXI0) = 0U;

    /* Disable RIIC0 interrupt */
    IEN(RIIC0, TXI0) = 0U;
    IEN(RIIC0, RXI0) = 0U;
    ICU.GENBL1.BIT.EN13 = 0U;
    ICU.GENBL1.BIT.EN14 = 0U;
}

/***********************************************************************************************************************
* Function Name: R_RIIC0_Master_Send
* Description  : This function write data to a slave device.
* Arguments    : adr -
*                    address of slave device
*                txbuf -
*                    transmit buffer pointer
*                txnum -
*                    transmit data length
* Return Value : status -
*                    MD_OK or MD_ARGERROR
***********************************************************************************************************************/
MD_STATUS R_RIIC0_Master_Send(uint16_t adr, uint8_t * const tx_buf, uint16_t tx_num)
{
    MD_STATUS status = MD_OK;

    if (1U == RIIC0.ICCR2.BIT.BBSY)
    {
        status = MD_ERROR1;
    }
    else if (0x07FFU < adr)
    {
        status = MD_ERROR2;
    }
    else 
    {
        /* Set parameter */
        g_riic0_tx_count = tx_num;
        gp_riic0_tx_address = tx_buf;
        g_riic0_slave_address = adr;
        g_riic0_mode_flag = _0D_IIC_MASTER_TRANSMIT;
        
        if (0xFFU > g_riic0_slave_address)
        {
            g_riic0_state = _01_IIC_MASTER_SENDS_ADR_7_W;
        } 
        else 
        {
            g_riic0_state = _02_IIC_MASTER_SENDS_ADR_10A_W;
        }

        R_RIIC0_StartCondition();  /* Issue a start condition */
    }

    return (status);
}

/***********************************************************************************************************************
* Function Name: R_RIIC0_Master_Receive
* Description  : This function read data from a slave device.
* Arguments    : adr -
*                    address of slave device
*                rx_buf -
*                    receive buffer pointer
*                rx_num -
*                    receive data length
* Return Value : status -
*                    MD_OK or MD_ARGERROR
***********************************************************************************************************************/
MD_STATUS R_RIIC0_Master_Receive(uint16_t adr, uint8_t * const rx_buf, uint16_t rx_num)
{
    MD_STATUS status = MD_OK;

    if (1U == RIIC0.ICCR2.BIT.BBSY)
    {
        status = MD_ERROR1;
    }
    else if (0x07FFU < adr)
    {
        status = MD_ERROR2;
    }
    else if (0xFFU < adr)
    {
        /* Master receive for 10bit address is not supported */
        status = MD_ERROR3;
    }
    else 
    {
        /* Set parameter */
        g_riic0_rx_length = rx_num;
        g_riic0_rx_count = 0U;
        gp_riic0_rx_address = rx_buf;
        g_riic0_slave_address = adr;
        g_riic0_dummy_read_count = 0U;
        g_riic0_mode_flag = _0C_IIC_MASTER_RECEIVE;

        if (0xFFU > g_riic0_slave_address)
        {
            g_riic0_state = _00_IIC_MASTER_SENDS_ADR_7_R;
        }

        R_RIIC0_StartCondition();  /* Issue a start condition */
    }
    
    return (status);
}



/***********************************************************************************************************************
* Function Name: R_RIIC0_StartCondition
* Description  : This function generate I2C start condition.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_RIIC0_StartCondition(void)
{
    RIIC0.ICCR2.BIT.ST = 1U;    /* Set start condition flag */
}

/***********************************************************************************************************************
* Function Name: R_RIIC0_StopCondition
* Description  : This function generate I2C stop condition.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_RIIC0_StopCondition(void)
{
    RIIC0.ICCR2.BIT.SP = 1U;    /* Set stop condition flag */
}




/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

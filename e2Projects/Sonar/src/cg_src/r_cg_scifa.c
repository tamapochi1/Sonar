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
* File Name    : r_cg_scifa.c
* Version      : Code Generator for RX71M V1.01.00.05 [26 May 2017]
* Device(s)    : R5F571MFDxFB
* Tool-Chain   : CCRX
* Description  : This file implements device driver for SCIF module.
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
#include "r_cg_scifa.h"
/* Start user code for include. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
#include "r_cg_userdefine.h"

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
uint8_t * gp_scifa10_tx_address;         /* SCIFA10 transmit buffer address */
uint16_t  g_scifa10_tx_count;            /* SCIFA10 transmit data number */
uint8_t * gp_scifa10_rx_address;         /* SCIFA10 receive buffer address */
uint16_t  g_scifa10_rx_count;            /* SCIFA10 receive data number */
uint16_t  g_scifa10_rx_length;           /* SCIFA10 receive data length */
uint8_t * gp_scifa11_tx_address;         /* SCIFA11 transmit buffer address */
uint16_t  g_scifa11_tx_count;            /* SCIFA11 transmit data number */
uint8_t * gp_scifa11_rx_address;         /* SCIFA11 receive buffer address */
uint16_t  g_scifa11_rx_count;            /* SCIFA11 receive data number */
uint16_t  g_scifa11_rx_length;           /* SCIFA11 receive data length */
/* Start user code for global. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: R_SCIFA10_Create
* Description  : This function initializes SCIFA10.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_SCIFA10_Create(void)
{
    volatile uint16_t dummy;

    /* Cancel SCIFA10 module stop state */
    MSTP(SCIFA10) = 0U;

    /* Clear transmit/receive enable bits */
    SCIFA10.SCR.BIT.TE = 0U;
    SCIFA10.SCR.BIT.RE = 0U;

    /* Reset transmit/receive FIFO data register operation */
    SCIFA10.FCR.BIT.TFRST = 1U;
    SCIFA10.FCR.BIT.RFRST = 1U;

    /* Read and clear status flags */
    dummy = SCIFA10.FSR.WORD;
    SCIFA10.FSR.WORD = 0x00U;

    dummy = (uint16_t) SCIFA10.LSR.BIT.ORER;
    SCIFA10.LSR.BIT.ORER = 0U;

    /* Set transmission/reception format */
    SCIFA10.SMR.WORD = _0080_SCIF_CLOCK_SYNCHRONOUS_MODE;
    SCIFA10.SEMR.BYTE = _00_SCIF_NOISE_FILTER_DISABLE | _00_SCIF_DATA_TRANSFER_LSB_FIRST;

    /* Set clock enable bits */
    SCIFA10.SCR.WORD = _0002_SCIF_EXTERNAL_SCK_INPUT;

    /* Set FIFO trigger conditions */
    SCIFA10.FTCR.WORD = _0000_SCIF_TX_FIFO_TRIGGER_NUM_0 | _0080_SCIF_TX_TRIGGER_TFTC_VALID | 
                        _0100_SCIF_RX_FIFO_TRIGGER_NUM_1 | _8000_SCIF_RX_TRIGGER_RFTC_VALID;
    SCIFA10.FCR.WORD = _0000_SCIF_LOOPBACK_DISABLE | _0000_SCIF_MODEM_CONTROL_DISABLE;

    /* Disable transmit/receive FIFO data register reset operation */
    SCIFA10.FCR.BIT.TFRST = 0U;
    SCIFA10.FCR.BIT.RFRST = 0U;

    /* Set interrupt priority */
    IPR(SCIFA10, TXIF10) = _0F_SCIF_PRIORITY_LEVEL15;
    IPR(SCIFA10, RXIF10) = _0F_SCIF_PRIORITY_LEVEL15;

    /* Set RXD10 pin */
    MPC.P81PFS.BYTE = 0x0AU;
    PORT8.PMR.BYTE |= 0x02U;

    /* Set TXD10 pin */
    MPC.P82PFS.BYTE = 0x0AU;
    PORT8.PMR.BYTE |= 0x04U;

    /* Set SCK10 pin */
    MPC.P80PFS.BYTE = 0x0AU;
    PORT8.PMR.BYTE |= 0x01U;
}
/***********************************************************************************************************************
* Function Name: R_SCIFA10_Start
* Description  : This function starts SCIFA10.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_SCIFA10_Start(void)
{
    /* Clear interrupt flag */
    IR(SCIFA10, TXIF10) = 0U;
    IR(SCIFA10, RXIF10) = 0U;

    /* Enable SCIF interrupt */
    IEN(SCIFA10, TXIF10) = 1U;
    ICU.GENAL0.BIT.EN8 = 1U;
    IEN(SCIFA10, RXIF10) = 1U;
    ICU.GENAL0.BIT.EN9 = 1U;
    ICU.GENAL0.BIT.EN10 = 1U;
}
/***********************************************************************************************************************
* Function Name: R_SCIFA10_Stop
* Description  : This function stops SCIFA10.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_SCIFA10_Stop(void)
{
    /* Disable serial receive */
    SCIFA10.SCR.BIT.RE = 0U;

    /* Disable serial transmit */
    SCIFA10.SCR.BIT.TE = 0U;

    /* Disable TXIF interrupt */
    SCIFA10.SCR.BIT.TIE = 0U;

    /* Disable RXIF, ERIF, DRIF and BRIF interrupt */
    SCIFA10.SCR.BIT.RIE = 0U;

    /* Disable SCIF interrupt */
    IR(SCIFA10, TXIF10) = 0U;
    IEN(SCIFA10, TXIF10) = 0U;
    ICU.GENAL0.BIT.EN8 = 0U;
    IR(SCIFA10, RXIF10) = 0U;
    IEN(SCIFA10, RXIF10) = 0U;
    ICU.GENAL0.BIT.EN9 = 0U;
    ICU.GENAL0.BIT.EN10 = 0U;
}
/***********************************************************************************************************************
* Function Name: R_SCIFA10_Serial_Receive
* Description  : This function receives SCIFA10 data.
* Arguments    : rx_buf -
*                    receive buffer pointer (Not used when receive data handled by DTC or DMAC)
*                rx_num -
*                    buffer size (Not used when receive data handled by DTC or DMAC)
* Return Value : status -
*                    MD_OK or MD_ARGERROR
***********************************************************************************************************************/
MD_STATUS R_SCIFA10_Serial_Receive(uint8_t * const rx_buf, uint16_t rx_num)
{
    MD_STATUS status = MD_OK;

    if (1 > rx_num)
    {
        status = MD_ARGERROR;
    }
    else
    {
        g_scifa10_rx_count = 0U;
        g_scifa10_rx_length = rx_num;
        gp_scifa10_rx_address = rx_buf;
        SCIFA10.FTCR.BIT.RFTC = _01_SCIF_RX_TRIG_NUM;
        SCIFA10.SCR.BIT.RE = 1U;
        SCIFA10.SCR.BIT.RIE = 1U;
        SCIFA10.SCR.BIT.REIE = 1U;
    }

    return (status);
}
/***********************************************************************************************************************
* Function Name: R_SCIFA10_Serial_Send
* Description  : This function transmits SCIFA10 data.
* Arguments    : tx_buf -
*                    transfer buffer pointer (Not used when transmit data handled by DTC or DMAC)
*                tx_num -
*                    buffer size (Not used when transmit data handled by DTC or DMAC)
* Return Value : status -
*                    MD_OK or MD_ARGERROR
***********************************************************************************************************************/
MD_STATUS R_SCIFA10_Serial_Send(uint8_t * const tx_buf, uint16_t tx_num)
{
    MD_STATUS status = MD_OK;

    if (1 > tx_num)
    {
        status = MD_ARGERROR;
    }
    else
    {
        gp_scifa10_tx_address = tx_buf;
        g_scifa10_tx_count = tx_num;
        SCIFA10.SCR.BIT.TE = 1U;
        SCIFA10.SCR.BIT.TIE = 1U;
    }

    return (status);
}
/***********************************************************************************************************************
* Function Name: R_SCIFA10_Serial_Send_Receive
* Description  : This function transmits and receives SCIFA10 data.
* Arguments    : tx_buf -
*                    transmit buffer pointer (Not used when transmit data handled by DTC or DMAC)
*                tx_num -
*                    transmit buffer size (Not used when transmit data handled by DTC or DMAC)
*                rx_buf -
*                    receive buffer pointer (Not used when receive data handled by DTC or DMAC)
*                rx_num -
*                    receive buffer size (Not used when receive data handled by DTC or DMAC)
* Return Value : status -
*                    MD_OK or MD_ARGERROR
***********************************************************************************************************************/
MD_STATUS R_SCIFA10_Serial_Send_Receive(uint8_t * const tx_buf, uint16_t tx_num, uint8_t * const rx_buf, uint16_t rx_num)
{
    MD_STATUS status = MD_OK;

    if (1 > tx_num)
    {
        status = MD_ARGERROR;
    }
    else
    {
        g_scifa10_tx_count = tx_num;
        gp_scifa10_tx_address = tx_buf;
        g_scifa10_rx_count = 0U;
        g_scifa10_rx_length = rx_num;
        gp_scifa10_rx_address = rx_buf;

        /* Set TE, TIE, RE, RIE bits simultaneously */
        SCIFA10.SCR.WORD |= 0xF0U;
    }

    return (status);
}
/***********************************************************************************************************************
* Function Name: R_SCIFA11_Create
* Description  : This function initializes SCIFA11.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_SCIFA11_Create(void)
{
    volatile uint16_t dummy;

    /* Cancel SCIFA11 module stop state */
    MSTP(SCIFA11) = 0U;

    /* Clear transmit/receive enable bits */
    SCIFA11.SCR.BIT.TE = 0U;
    SCIFA11.SCR.BIT.RE = 0U;

    /* Reset transmit/receive FIFO data register operation */
    SCIFA11.FCR.BIT.TFRST = 1U;
    SCIFA11.FCR.BIT.RFRST = 1U;

    /* Read and clear status flags */
    dummy = SCIFA11.FSR.WORD;
    SCIFA11.FSR.WORD = 0x00U;

    dummy = (uint16_t) SCIFA11.LSR.BIT.ORER;
    SCIFA11.LSR.BIT.ORER = 0U;

    /* Set transmission/reception format */
    SCIFA11.SMR.WORD = _0000_SCIF_CLOCK_PCLK | _0080_SCIF_CLOCK_SYNCHRONOUS_MODE;
    SCIFA11.SEMR.BYTE = _00_SCIF_NOISE_FILTER_DISABLE | _00_SCIF_DATA_TRANSFER_LSB_FIRST;

    /* Set clock enable bits */
    SCIFA11.SCR.WORD = _0000_SCIF_INTERNAL_SCK_OUTPUT;

    /* Clear modulation duty register select */
    SCIFA11.SEMR.BIT.MDDRS = 0U;

    /* Set bit rate */
    SCIFA11.BRR = 0x00U;

    /* Set FIFO trigger conditions */
    SCIFA11.FTCR.WORD = _0000_SCIF_TX_FIFO_TRIGGER_NUM_0 | _0080_SCIF_TX_TRIGGER_TFTC_VALID | 
                        _0100_SCIF_RX_FIFO_TRIGGER_NUM_1 | _8000_SCIF_RX_TRIGGER_RFTC_VALID;
    SCIFA11.FCR.WORD = _0000_SCIF_LOOPBACK_DISABLE | _0000_SCIF_MODEM_CONTROL_DISABLE;

    /* Disable transmit/receive FIFO data register reset operation */
    SCIFA11.FCR.BIT.TFRST = 0U;
    SCIFA11.FCR.BIT.RFRST = 0U;

    /* Set interrupt priority */
    IPR(SCIFA11, TXIF11) = _0F_SCIF_PRIORITY_LEVEL15;
    IPR(SCIFA11, RXIF11) = _0F_SCIF_PRIORITY_LEVEL15;

    /* Set RXD11 pin */
    MPC.P76PFS.BYTE = 0x0AU;
    PORT7.PMR.BYTE |= 0x40U;

    /* Set TXD11 pin */
    MPC.P77PFS.BYTE = 0x0AU;
    PORT7.PMR.BYTE |= 0x80U;

    /* Set SCK11 pin */
    MPC.P75PFS.BYTE = 0x0AU;
    PORT7.PMR.BYTE |= 0x20U;
}
/***********************************************************************************************************************
* Function Name: R_SCIFA11_Start
* Description  : This function starts SCIFA11.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_SCIFA11_Start(void)
{
    /* Clear interrupt flag */
    IR(SCIFA11, TXIF11) = 0U;
    IR(SCIFA11, RXIF11) = 0U;

    /* Enable SCIF interrupt */
    IEN(SCIFA11, TXIF11) = 1U;
    ICU.GENAL0.BIT.EN12 = 1U;
    IEN(SCIFA11, RXIF11) = 1U;
    ICU.GENAL0.BIT.EN13 = 1U;
    ICU.GENAL0.BIT.EN14 = 1U;
}
/***********************************************************************************************************************
* Function Name: R_SCIFA11_Stop
* Description  : This function stops SCIFA11.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_SCIFA11_Stop(void)
{
    /* Disable serial receive */
    SCIFA11.SCR.BIT.RE = 0U;

    /* Disable serial transmit */
    SCIFA11.SCR.BIT.TE = 0U;

    /* Disable TXIF interrupt */
    SCIFA11.SCR.BIT.TIE = 0U;

    /* Disable RXIF, ERIF, DRIF and BRIF interrupt */
    SCIFA11.SCR.BIT.RIE = 0U;

    /* Disable SCIF interrupt */
    IR(SCIFA11, TXIF11) = 0U;
    IEN(SCIFA11, TXIF11) = 0U;
    ICU.GENAL0.BIT.EN12 = 0U;
    IR(SCIFA11, RXIF11) = 0U;
    IEN(SCIFA11, RXIF11) = 0U;
    ICU.GENAL0.BIT.EN13 = 0U;
    ICU.GENAL0.BIT.EN14 = 0U;
}
/***********************************************************************************************************************
* Function Name: R_SCIFA11_Serial_Receive
* Description  : This function receives SCIFA11 data.
* Arguments    : rx_buf -
*                    receive buffer pointer (Not used when receive data handled by DTC or DMAC)
*                rx_num -
*                    buffer size (Not used when receive data handled by DTC or DMAC)
* Return Value : status -
*                    MD_OK or MD_ARGERROR
***********************************************************************************************************************/
MD_STATUS R_SCIFA11_Serial_Receive(uint8_t * const rx_buf, uint16_t rx_num)
{
    MD_STATUS status = MD_OK;

    if (1 > rx_num)
    {
        status = MD_ARGERROR;
    }
    else
    {
        g_scifa11_rx_count = 0U;
        g_scifa11_rx_length = rx_num;
        gp_scifa11_rx_address = rx_buf;
        SCIFA11.FTCR.BIT.RFTC = _01_SCIF_RX_TRIG_NUM;
        SCIFA11.SCR.BIT.RE = 1U;
        SCIFA11.SCR.BIT.RIE = 1U;
        SCIFA11.SCR.BIT.REIE = 1U;
    }

    return (status);
}
/***********************************************************************************************************************
* Function Name: R_SCIFA11_Serial_Send
* Description  : This function transmits SCIFA11 data.
* Arguments    : tx_buf -
*                    transfer buffer pointer (Not used when transmit data handled by DTC or DMAC)
*                tx_num -
*                    buffer size (Not used when transmit data handled by DTC or DMAC)
* Return Value : status -
*                    MD_OK or MD_ARGERROR
***********************************************************************************************************************/
MD_STATUS R_SCIFA11_Serial_Send(uint8_t * const tx_buf, uint16_t tx_num)
{
    MD_STATUS status = MD_OK;

    if (1 > tx_num)
    {
        status = MD_ARGERROR;
    }
    else
    {
        gp_scifa11_tx_address = tx_buf;
        g_scifa11_tx_count = tx_num;
        SCIFA11.SCR.BIT.TE = 1U;
        SCIFA11.SCR.BIT.TIE = 1U;
    }

    return (status);
}
/***********************************************************************************************************************
* Function Name: R_SCIFA11_Serial_Send_Receive
* Description  : This function transmits and receives SCIFA11 data.
* Arguments    : tx_buf -
*                    transmit buffer pointer (Not used when transmit data handled by DTC or DMAC)
*                tx_num -
*                    transmit buffer size (Not used when transmit data handled by DTC or DMAC)
*                rx_buf -
*                    receive buffer pointer (Not used when receive data handled by DTC or DMAC)
*                rx_num -
*                    receive buffer size (Not used when receive data handled by DTC or DMAC)
* Return Value : status -
*                    MD_OK or MD_ARGERROR
***********************************************************************************************************************/
MD_STATUS R_SCIFA11_Serial_Send_Receive(uint8_t * const tx_buf, uint16_t tx_num, uint8_t * const rx_buf, uint16_t rx_num)
{
    MD_STATUS status = MD_OK;

    if (1 > tx_num)
    {
        status = MD_ARGERROR;
    }
    else
    {
        g_scifa11_tx_count = tx_num;
        gp_scifa11_tx_address = tx_buf;
        g_scifa11_rx_count = 0U;
        g_scifa11_rx_length = rx_num;
        gp_scifa11_rx_address = rx_buf;

        /* Set TE, TIE, RE, RIE bits simultaneously */
        SCIFA11.SCR.WORD |= 0xF0U;
    }

    return (status);
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

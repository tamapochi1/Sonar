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
* File Name    : r_cg_riic.h
* Version      : Code Generator for RX71M V1.01.00.05 [26 May 2017]
* Device(s)    : R5F571MFDxFB
* Tool-Chain   : CCRX
* Description  : This file implements device driver for RIIC module.
* Creation Date: 2017/12/28
***********************************************************************************************************************/
#ifndef RIIC_H
#define RIIC_H

/***********************************************************************************************************************
Macro definitions (Register bit)
***********************************************************************************************************************/
/*
    I2C bus control register 1 (ICCR1)
*/
/* I2C bus interface enable (ICE) */
#define _00_IIC_BUS_DISABLE                          (0x00U) /* SCL and SDA pins in inactive state */
#define _80_IIC_BUS_ENABLE                           (0x80U) /* SCL and SDA pins in active state */

/*
    I2C bus control register 2 (ICCR2)
*/
/* Master/slave mode (MST) */
#define _00_IIC_SLAVE_MODE                           (0x00U) /* Slave mode */
#define _40_IIC_MASTER_MODE                          (0x40U) /* Master mode */

/*
    I2C bus mode register 1 (ICMR1)
*/
/* Internal reference clock selection CKS[2:0] */
#define _00_IIC_PCLK_DIV_1                           (0x00U) /* PCLK/1 clock */
#define _10_IIC_PCLK_DIV_2                           (0x10U) /* PCLK/2 clock */
#define _20_IIC_PCLK_DIV_4                           (0x20U) /* PCLK/4 clock */
#define _30_IIC_PCLK_DIV_8                           (0x30U) /* PCLK/8 clock */
#define _40_IIC_PCLK_DIV_16                          (0x40U) /* PCLK/16 clock */
#define _50_IIC_PCLK_DIV_32                          (0x50U) /* PCLK/32 clock */
#define _60_IIC_PCLK_DIV_64                          (0x60U) /* PCLK/64 clock */
#define _70_IIC_PCLK_DIV_128                         (0x70U) /* PCLK/128 clock */

/*
    I2C bus mode register 2 (ICMR2)
*/
/* Timeout detection time selection (TMOS) */
#define _00_IIC_TIMEOUT_LONG_MODE                    (0x00U) /* Long mode */
#define _01_IIC_TIMEOUT_SHORT_MODE                   (0x01U) /* Short mode */
/* Timeout L count control (TMOL) */
#define _00_IIC_TIMEOUT_SCL_LOW_DISABLE              (0x00U) /* Disable timeout count while SCL is low */
#define _02_IIC_TIMEOUT_SCL_LOW_ENABLE               (0x02U) /* Enable timeout count while SCL is low */
/* Timeout H count control (TMOH) */
#define _00_IIC_TIMEOUT_SCL_HIGH_DISABLE             (0x00U) /* Disable timeout count while SCL is high */
#define _04_IIC_TIMEOUT_SCL_HIGH_ENABLE              (0x04U) /* Enable timeout count while SCL is high */
/* SDA output delay counter (SDDL) */
#define _00_IIC_NO_OUTPUT_DELAY                      (0x00U) /* No output delay */
#define _10_IIC_1_CYCLE                              (0x10U) /* Output delay 1 cycle */
#define _20_IIC_2_CYCLES                             (0x20U) /* Output delay 2 cycles */
#define _30_IIC_3_CYCLES                             (0x30U) /* Output delay 3 cycles */
#define _40_IIC_4_CYCLES                             (0x40U) /* Output delay 4 cycles */
#define _50_IIC_5_CYCLES                             (0x50U) /* Output delay 5 cycles */
#define _60_IIC_6_CYCLES                             (0x60U) /* Output delay 6 cycles */
#define _70_IIC_7_CYCLES                             (0x70U) /* Output delay 7 cycles */
/* SDA output delay counter (SDDL) */
#define _00_IIC_NO_OUTPUT_DELAY                      (0x00U) /* No output delay */
#define _10_IIC_1_OR_2_CYCLES                        (0x10U) /* Output delay 1 or 2 cycles */
#define _20_IIC_3_OR_4_CYCLES                        (0x20U) /* Output delay 3 or 4 cycles */
#define _30_IIC_5_OR_6_CYCLES                        (0x30U) /* Output delay 5 or 6 cycles */
#define _40_IIC_7_OR_8_CYCLES                        (0x40U) /* Output delay 7 or 8 cycles */
#define _50_IIC_9_OR_10_CYCLES                       (0x50U) /* Output delay 9 or 10 cycles */
#define _60_IIC_11_OR_12_CYCLES                      (0x60U) /* Output delay 11 or 12 cycles */
#define _70_IIC_13_OR_14_CYCLES                      (0x70U) /* Output delay 13 or 14 cycles */
/* SDA output delay clock source selection (DLCS) */
#define _00_IIC_INTERNAL_CLOCK                       (0x00U) /* Internal clock as delay clock */
#define _80_IIC_INTERNAL_CLOCK_DIV_2                 (0x80U) /* Internal clock / 2 as delay clock */

/*
    I2C bus mode register 3 (ICMR3)
*/
/* Noise filter stage selection (NF) */
#define _00_IIC_NOISE_FILTER_1                       (0x00U) /* 1-stage filter */
#define _01_IIC_NOISE_FILTER_2                       (0x01U) /* 2-stage filter */
#define _02_IIC_NOISE_FILTER_3                       (0x02U) /* 3-stage filter */
#define _03_IIC_NOISE_FILTER_4                       (0x03U) /* 4-stage filter */
/* RDRF flag set timing selection (RDRFS) */
#define _00_IIC_RDRF_NINTH                           (0x00U) /* RDRF set at rising edge of the 9th SCL clock cycle */
#define _20_IIC_RDRF_EIGHT                           (0x20U) /* RDRF set at rising edge of the 8th SCL clock cycle */
/*  SMBus/I2C bus selection (SMBS) */
#define _00_IIC_IICBUS                               (0x00U) /* IIC bus is selected */
#define _80_IIC_SMBUS                                (0x80U) /* SMBus is selected */

/*
    I2C bus function enable register (ICFER)
*/
/* Timeout function enable (TMOE) */
#define _00_IIC_TIMEOUT_FUNCTION_DISABLE             (0x00U) /* Timeout function disable */
#define _01_IIC_TIMEOUT_FUNCTION_ENABLE              (0x01U) /* Timeout function enable */
/* Master arbitration-lost detection enable (MALE) */
#define _00_IIC_MASTER_ARBITRATION_DISABLE           (0x00U) /* Master arbitration-lost-detection disabled */
#define _02_IIC_MASTER_ARBITRATION_ENABLE            (0x02U) /* Master arbitration-lost-detection enabled */
/* NACK transmission arbitration-lost detection enable (NALE) */
#define _00_IIC_NACK_ARBITRATION_DISABLE             (0x00U) /* NACK arbitration-lost detection disabled */
#define _04_IIC_NACK_ARBITRATION_ENABLE              (0x04U) /* NACK arbitration-lost detection enabled */
/* Slave transmission arbitration-lost detection enable (SALE) */
#define _00_IIC_SLAVE_ARBITRATION_DISABLE            (0x00U) /* Slave arbitration-lost detection disabled */
#define _08_IIC_SLAVE_ARBITRATION_ENABLE             (0x08U) /* Slave arbitration-lost detection enabled */
/* NACK reception transfer suspension enable (NACKE) */
#define _00_IIC_NACK_SUSPENSION_DISABLE              (0x00U) /* Transfer operation not suspended during NACK */ 
#define _10_IIC_NACK_SUSPENSION_ENABLE               (0x10U) /* Transfer operation suspended during NACK */
/* Digital noise filter circuit enable (NFE) */
#define _00_IIC_NOISE_FILTER_UNUSED                  (0x00U) /* Digital noise filter circuit unused */
#define _20_IIC_NOISE_FILTER_USED                    (0x20U) /* Digital noise filter circuit used */
/* SCL Synchronous Circuit Enable (SCLE) */
#define _00_IIC_SCL_SYNCHRONOUS_UNUSED               (0x00U) /* SCL synchronous circuit unused */
#define _40_IIC_SCL_SYNCHRONOUS_USED                 (0x40U) /* SCL synchronous circuit used */
/* Fast-mode Plus Enable (FMPE) */
#define _00_IIC_FASTPLUS_MODE_DISABLE                (0x00U) /* Fastplus mode disable */
#define _80_IIC_FASTPLUS_MODE_ENABLE                 (0x80U) /* Fastplus mode enable */

/*
    I2C bus status enable register (ICSER)
*/
/* Slave address register 0 enable (SAR0E) */
#define _00_IIC_SLAVE_0_DISABLE                      (0x00U) /* Slave address in SARL0 and SARU0 is disabled */
#define _01_IIC_SLAVE_0_ENABLE                       (0x01U) /* Slave address in SARL0 and SARU0 is enabled */
/* Slave address register 1 enable (SAR1E) */
#define _00_IIC_SLAVE_1_DISABLE                      (0x00U) /* Slave address in SARL1 and SARU1 is disabled */
#define _02_IIC_SLAVE_1_ENABLE                       (0x02U) /* Slave address in SARL1 and SARU1 is enabled */
/* Slave address register 2 enable (SAR2E) */
#define _00_IIC_SLAVE_2_DISABLE                      (0x00U) /* Slave address in SARL2 and SARU2 is disabled */
#define _04_IIC_SLAVE_2_ENABLE                       (0x04U) /* Slave address in SARL2 and SARU2 is enabled */
/* General call address enable (GCAE) */
#define _00_IIC_GENERAL_CALL_ADDRESS_DISABLE         (0x00U) /* General call address detection is disabled */
#define _08_IIC_GENERAL_CALL_ADDRESS_ENABLE          (0x08U) /* General call address detection is enabled */
/* Device-ID address detection enable (DIDE) */
#define _00_IIC_DEVICEID_DETECT_DISABLE              (0x00U) /* Device-id address detection is disabled */
#define _20_IIC_DEVICEID_DETECT_ENABLE               (0x20U) /* Device-id address detection is enabled */
/* Host address enable (HOAE) */
#define _00_IIC_HOST_ADDRESS_DETECT_DISABLE          (0x00U) /* Host address detection is disabled */
#define _80_IIC_HOST_ADDRESS_DETECT_ENABLE           (0x80U) /* Host address detection is enabled */

/*
    I2C bus interrupt enable register (ICIER)
*/
/* Timeout interrupt enable (TMOIE) */
#define _00_IIC_TIMEOUT_INTERRUPT_DISABLE            (0x00U) /* Timeout interrupt (TMOI) disabled */
#define _01_IIC_TIMEOUT_INTERRUPT_ENABLE             (0x01U) /* Timeout interrupt (TMOI) enabled */
/* Arbitration-lost interrupt enable (ALIE) */
#define _00_IIC_ARBITRATION_LOST_INTERRUPT_DISABLE   (0x00U) /* Arbitration-lost interrupt (ALI) disabled */
#define _02_IIC_ARBITRATION_LOST_INTERRUPT_ENABLE    (0x02U) /* Arbitration-lost interrupt (ALI) enabled */
/* Start condition detection interrupt enable (STIE) */
#define _00_IIC_START_CONDITION_INTERRUPT_DISABLE    (0x00U) /* Start condition detection interrupt (STI) disabled */
#define _04_IIC_START_CONDITION_INTERRUPT_ENABLE     (0x04U) /* Start condition detection interrupt (STI) enabled */
/* Stop condition detection interrupt enable (SPIE) */
#define _00_IIC_STOP_CONDITION_INTERRUPT_DISABLE     (0x00U) /* Stop condition detection interrupt (SPI) disabled */
#define _08_IIC_STOP_CONDITION_INTERRUPT_ENABLE      (0x08U) /* Stop condition detection interrupt (SPI) enabled */
/* NACK reception interrupt enable (NAKIE) */
#define _00_IIC_NACK_INTERRUPT_DISABLE               (0x00U) /* NACK reception interrupt (NAKI) disabled */
#define _10_IIC_NACK_INTERRUPT_ENABLE                (0x10U) /* NACK reception interrupt (NAKI) enabled */
/* Receive data full interrupt enable (RIE) */
#define _00_IIC_RECEIVE_DATA_INTERRUPT_DISABLE       (0x00U) /* Receive data full interrupt (RXI) disabled */
#define _20_IIC_RECEIVE_DATA_INTERRUPT_ENABLE        (0x20U) /* Receive data full interrupt (RXI) enabled */
/* Transmit end interrupt enable (TEIE) */
#define _00_IIC_TRANSMIT_END_INTERRUPT_DISABLE       (0x00U) /* Transmit end interrupt (TEI) disabled */
#define _40_IIC_TRANSMIT_END_INTERRUPT_ENABLE        (0x40U) /* Transmit end interrupt (TEI) enabled */
/* Transmit data empty interrupt enable (TIE) */
#define _00_IIC_TRANSMIT_EMPTY_INTERRUPT_DISABLE     (0x00U) /* Transmit data empty interrupt (TXI) disabled */
#define _80_IIC_TRANSMIT_EMPTY_INTERRUPT_ENABLE      (0x80U) /* Transmit data empty interrupt (TXI) enabled */

/*
    Slave address register U0 (SARU0)
*/
/* 7-bit/10-bit address format selection (FS) */
#define _00_IIC_SARU0_7_BIT                          (0x00U) /* 7-bit address format is selected */
#define _01_IIC_SARU0_10_BIT                         (0x01U) /* 10-bit address format is selected */

/*
    Slave address register U1 (SARU1)
*/
/* 7-bit/10-bit address format selection (FS) */
#define _00_IIC_SARU1_7_BIT                          (0x00U) /* 7-bit address format is selected */
#define _01_IIC_SARU1_10_BIT                         (0x01U) /* 10-bit address format is selected */

/*
    Slave address register U2 (SARU2)
*/
/* 7-bit/10-bit address format selection (FS) */
#define _00_IIC_SARU2_7_BIT                          (0x00U) /* 7-bit address format is selected */
#define _01_IIC_SARU2_10_BIT                         (0x01U) /* 10-bit address format is selected */

/*
    Interrupt Source Priority Register n (IPRn)
*/
/* Interrupt Priority Level Select (IPR[3:0]) */
#define _00_IIC_PRIORITY_LEVEL0                      (0x00U) /* Level 0 (interrupt disabled) */
#define _01_IIC_PRIORITY_LEVEL1                      (0x01U) /* Level 1 */
#define _02_IIC_PRIORITY_LEVEL2                      (0x02U) /* Level 2 */
#define _03_IIC_PRIORITY_LEVEL3                      (0x03U) /* Level 3 */
#define _04_IIC_PRIORITY_LEVEL4                      (0x04U) /* Level 4 */
#define _05_IIC_PRIORITY_LEVEL5                      (0x05U) /* Level 5 */
#define _06_IIC_PRIORITY_LEVEL6                      (0x06U) /* Level 6 */
#define _07_IIC_PRIORITY_LEVEL7                      (0x07U) /* Level 7 */
#define _08_IIC_PRIORITY_LEVEL8                      (0x08U) /* Level 8 */
#define _09_IIC_PRIORITY_LEVEL9                      (0x09U) /* Level 9 */
#define _0A_IIC_PRIORITY_LEVEL10                     (0x0AU) /* Level 10 */
#define _0B_IIC_PRIORITY_LEVEL11                     (0x0BU) /* Level 11 */
#define _0C_IIC_PRIORITY_LEVEL12                     (0x0CU) /* Level 12 */
#define _0D_IIC_PRIORITY_LEVEL13                     (0x0DU) /* Level 13 */
#define _0E_IIC_PRIORITY_LEVEL14                     (0x0EU) /* Level 14 */
#define _0F_IIC_PRIORITY_LEVEL15                     (0x0FU) /* Level 15 (highest) */

/* Master State Flags */
#define _00_IIC_MASTER_SENDS_ADR_7_R                 (0x00U) /* Master sends 7 bits address with read */
#define _01_IIC_MASTER_SENDS_ADR_7_W                 (0x01U) /* Master sends 7 bits address with write */
#define _02_IIC_MASTER_SENDS_ADR_10A_W               (0x02U) /* Master sends first 10 bits address with write */
#define _03_IIC_MASTER_SENDS_ADR_10A_R               (0x03U) /* Master sends first 10 bits address with read */
#define _04_IIC_MASTER_SENDS_ADR_10B                 (0x04U) /* Master sends second 10 bits address */
#define _05_IIC_MASTER_SENDS_DATA                    (0x05U) /* Master sends data */
#define _06_IIC_MASTER_SENDS_END                     (0x06U) /* Master sends prepares to stop */
#define _07_IIC_MASTER_SENDS_STOP                    (0x07U) /* Master sends stopping */
#define _08_IIC_MASTER_RECEIVES_START                (0x08U) /* Master receive to start */
#define _09_IIC_MASTER_RECEIVES_DATA                 (0x09U) /* Master is receiving data */
#define _0A_IIC_MASTER_RECEIVES_STOPPING             (0x0AU) /* Master receive prepares to stop */
#define _0B_IIC_MASTER_RECEIVES_STOP                 (0x0BU) /* Master receive stopping */
#define _0C_IIC_MASTER_RECEIVE                       (0x0CU) /* Master receive mode */
#define _0D_IIC_MASTER_TRANSMIT                      (0x0DU) /* Master transmit mode */
#define _0E_IIC_MASTER_RECEIVES_RESTART              (0x0EU) /* Master receive restarting */

/* Slave State Flags */
#define _10_IIC_SLAVE_RECEIVES_DATA                  (0x10U) /* Slave receiving data */
#define _11_IIC_SLAVE_SENDS_DATA                     (0x11U) /* Slave sending data */
#define _12_IIC_SLAVE_SENDS_END                      (0x12U) /* Slave send prepares to stop */
#define _13_IIC_SLAVE_SENDS_STOP                     (0x13U) /* Slave send stopping */
#define _14_IIC_SLAVE_RECEIVES_STOP                  (0x14U) /* Slave receive stopping */
#define _15_IIC_SLAVE_WAIT_START_CONDITION           (0x15U) /* Slave is waiting for start condition */
#define _16_IIC_SLAVE_RECEIVE                        (0x16U) /* Slave receive mode */
#define _17_IIC_SLAVE_TRANSMIT                       (0x17U) /* Slave transmit mode */

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/
#define _F8_IIC0_SCL_HIGH_LEVEL_PERIOD               (0xF8U) /* SCL clock high-level period setting */
#define _FF_IIC0_SCL_LOW_LEVEL_PERIOD                (0xFFU) /* SCL clock low-level period setting */

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
Global functions
***********************************************************************************************************************/
void R_RIIC0_Create(void);
void R_RIIC0_Start(void);
void R_RIIC0_Stop(void);
MD_STATUS R_RIIC0_Master_Send(uint16_t adr, uint8_t * const tx_buf, uint16_t txnum);
MD_STATUS R_RIIC0_Master_Receive(uint16_t adr, uint8_t * const rx_buf, uint16_t rxnum);
void R_RIIC0_StartCondition(void);
void R_RIIC0_StopCondition(void);
static void r_riic0_callback_transmitend(void);
static void r_riic0_callback_receiveend(void);
static void r_riic0_callback_receiveerror(MD_STATUS status);

/* Start user code for function. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
#endif

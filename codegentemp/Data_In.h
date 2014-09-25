/*******************************************************************************
* File Name: Data_In.h  
* Version 2.0
*
* Description:
*  This file containts Control Register function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_Data_In_H) /* Pins Data_In_H */
#define CY_PINS_Data_In_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Data_In_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v2_0 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Data_In__PORT == 15 && ((Data_In__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    Data_In_Write(uint8 value) ;
void    Data_In_SetDriveMode(uint8 mode) ;
uint8   Data_In_ReadDataReg(void) ;
uint8   Data_In_Read(void) ;
uint8   Data_In_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Data_In_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define Data_In_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define Data_In_DM_RES_UP          PIN_DM_RES_UP
#define Data_In_DM_RES_DWN         PIN_DM_RES_DWN
#define Data_In_DM_OD_LO           PIN_DM_OD_LO
#define Data_In_DM_OD_HI           PIN_DM_OD_HI
#define Data_In_DM_STRONG          PIN_DM_STRONG
#define Data_In_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define Data_In_MASK               Data_In__MASK
#define Data_In_SHIFT              Data_In__SHIFT
#define Data_In_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Data_In_PS                     (* (reg8 *) Data_In__PS)
/* Data Register */
#define Data_In_DR                     (* (reg8 *) Data_In__DR)
/* Port Number */
#define Data_In_PRT_NUM                (* (reg8 *) Data_In__PRT) 
/* Connect to Analog Globals */                                                  
#define Data_In_AG                     (* (reg8 *) Data_In__AG)                       
/* Analog MUX bux enable */
#define Data_In_AMUX                   (* (reg8 *) Data_In__AMUX) 
/* Bidirectional Enable */                                                        
#define Data_In_BIE                    (* (reg8 *) Data_In__BIE)
/* Bit-mask for Aliased Register Access */
#define Data_In_BIT_MASK               (* (reg8 *) Data_In__BIT_MASK)
/* Bypass Enable */
#define Data_In_BYP                    (* (reg8 *) Data_In__BYP)
/* Port wide control signals */                                                   
#define Data_In_CTL                    (* (reg8 *) Data_In__CTL)
/* Drive Modes */
#define Data_In_DM0                    (* (reg8 *) Data_In__DM0) 
#define Data_In_DM1                    (* (reg8 *) Data_In__DM1)
#define Data_In_DM2                    (* (reg8 *) Data_In__DM2) 
/* Input Buffer Disable Override */
#define Data_In_INP_DIS                (* (reg8 *) Data_In__INP_DIS)
/* LCD Common or Segment Drive */
#define Data_In_LCD_COM_SEG            (* (reg8 *) Data_In__LCD_COM_SEG)
/* Enable Segment LCD */
#define Data_In_LCD_EN                 (* (reg8 *) Data_In__LCD_EN)
/* Slew Rate Control */
#define Data_In_SLW                    (* (reg8 *) Data_In__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Data_In_PRTDSI__CAPS_SEL       (* (reg8 *) Data_In__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Data_In_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Data_In__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Data_In_PRTDSI__OE_SEL0        (* (reg8 *) Data_In__PRTDSI__OE_SEL0) 
#define Data_In_PRTDSI__OE_SEL1        (* (reg8 *) Data_In__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Data_In_PRTDSI__OUT_SEL0       (* (reg8 *) Data_In__PRTDSI__OUT_SEL0) 
#define Data_In_PRTDSI__OUT_SEL1       (* (reg8 *) Data_In__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Data_In_PRTDSI__SYNC_OUT       (* (reg8 *) Data_In__PRTDSI__SYNC_OUT) 


#if defined(Data_In__INTSTAT)  /* Interrupt Registers */

    #define Data_In_INTSTAT                (* (reg8 *) Data_In__INTSTAT)
    #define Data_In_SNAP                   (* (reg8 *) Data_In__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Data_In_H */


/* [] END OF FILE */

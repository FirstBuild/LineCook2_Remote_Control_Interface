/*******************************************************************************
* File Name: Data_In.c  
* Version 2.0
*
* Description:
*  This file contains API to enable firmware control of a Pins component.
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "cytypes.h"
#include "Data_In.h"

/* APIs are not generated for P15[7:6] on PSoC 5 */
#if !(CY_PSOC5A &&\
	 Data_In__PORT == 15 && ((Data_In__MASK & 0xC0) != 0))


/*******************************************************************************
* Function Name: Data_In_Write
********************************************************************************
*
* Summary:
*  Assign a new value to the digital port's data output register.  
*
* Parameters:  
*  prtValue:  The value to be assigned to the Digital Port. 
*
* Return: 
*  None
*  
*******************************************************************************/
void Data_In_Write(uint8 value) 
{
    uint8 staticBits = (Data_In_DR & (uint8)(~Data_In_MASK));
    Data_In_DR = staticBits | ((uint8)(value << Data_In_SHIFT) & Data_In_MASK);
}


/*******************************************************************************
* Function Name: Data_In_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  Data_In_DM_STRONG     Strong Drive 
*  Data_In_DM_OD_HI      Open Drain, Drives High 
*  Data_In_DM_OD_LO      Open Drain, Drives Low 
*  Data_In_DM_RES_UP     Resistive Pull Up 
*  Data_In_DM_RES_DWN    Resistive Pull Down 
*  Data_In_DM_RES_UPDWN  Resistive Pull Up/Down 
*  Data_In_DM_DIG_HIZ    High Impedance Digital 
*  Data_In_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void Data_In_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(Data_In_0, mode);
}


/*******************************************************************************
* Function Name: Data_In_Read
********************************************************************************
*
* Summary:
*  Read the current value on the pins of the Digital Port in right justified 
*  form.
*
* Parameters:  
*  None
*
* Return: 
*  Returns the current value of the Digital Port as a right justified number
*  
* Note:
*  Macro Data_In_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 Data_In_Read(void) 
{
    return (Data_In_PS & Data_In_MASK) >> Data_In_SHIFT;
}


/*******************************************************************************
* Function Name: Data_In_ReadDataReg
********************************************************************************
*
* Summary:
*  Read the current value assigned to a Digital Port's data output register
*
* Parameters:  
*  None 
*
* Return: 
*  Returns the current value assigned to the Digital Port's data output register
*  
*******************************************************************************/
uint8 Data_In_ReadDataReg(void) 
{
    return (Data_In_DR & Data_In_MASK) >> Data_In_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(Data_In_INTSTAT) 

    /*******************************************************************************
    * Function Name: Data_In_ClearInterrupt
    ********************************************************************************
    * Summary:
    *  Clears any active interrupts attached to port and returns the value of the 
    *  interrupt status register.
    *
    * Parameters:  
    *  None 
    *
    * Return: 
    *  Returns the value of the interrupt status register
    *  
    *******************************************************************************/
    uint8 Data_In_ClearInterrupt(void) 
    {
        return (Data_In_INTSTAT & Data_In_MASK) >> Data_In_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 

#endif /* CY_PSOC5A... */

    
/* [] END OF FILE */

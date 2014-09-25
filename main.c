/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include <project.h>
#define DMA_1_BYTES_PER_BURST 127
#define DMA_1_REQUEST_PER_BURST 0
#define DMA_1_SRC_BASE (CYDEV_PERIPH_BASE)
#define DMA_1_DST_BASE (CYDEV_SRAM_BASE)
/*define for the number of samples to be transferred to memory on each switch press*/
#define NO_OF_SAMPLES 3
uint16 screen_buffer[NO_OF_SAMPLES];

int main()
{
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
/* Variable declarations for DMA_1 */
/* Move these variable declarations to the top of the function */
uint8 DMA_1_Chan;
uint8 DMA_1_TD[3];

/* DMA Configuration for DMA_1 */
#define DMA_1_BYTES_PER_BURST 2
#define DMA_1_REQUEST_PER_BURST 1
#define DMA_1_SRC_BASE (CYDEV_PERIPH_BASE)
#define DMA_1_DST_BASE (CYDEV_SRAM_BASE)
/*define for the number of samples to be transferred to memory on each switch press*/
#define NO_OF_SAMPLES 3
DMA_1_Chan = DMA_1_DmaInitialize(DMA_1_BYTES_PER_BURST, DMA_1_REQUEST_PER_BURST, 
    HI16(DMA_1_SRC_BASE), HI16(DMA_1_DST_BASE));
DMA_1_TD[0] = CyDmaTdAllocate();
DMA_1_TD[1] = CyDmaTdAllocate();
DMA_1_TD[2] = CyDmaTdAllocate();
CyDmaTdSetConfiguration(DMA_1_TD[0], 2, DMA_1_TD[1], TD_INC_DST_ADR | TD_AUTO_EXEC_NEXT);
CyDmaTdSetConfiguration(DMA_1_TD[1], 2, DMA_1_TD[2], TD_INC_DST_ADR | TD_AUTO_EXEC_NEXT);
CyDmaTdSetConfiguration(DMA_1_TD[2], 2, DMA_1_TD[0], DMA_1__TD_TERMOUT_EN | TD_INC_DST_ADR);
CyDmaTdSetAddress(DMA_1_TD[0], LO16((uint32)ShiftReg_1_SHIFT_REG_VALUE_LSB_PTR), LO16((uint32)screen_buffer));
CyDmaTdSetAddress(DMA_1_TD[1], LO16((uint32)ShiftReg_2_SHIFT_REG_VALUE_LSB_PTR), LO16((uint32)screen_buffer));
CyDmaTdSetAddress(DMA_1_TD[2], LO16((uint32)ShiftReg_3_SHIFT_REG_VALUE_LSB_PTR), LO16((uint32)screen_buffer));
CyDmaChSetInitialTd(DMA_1_Chan, DMA_1_TD[0]);
CyDmaChEnable(DMA_1_Chan, 1);

	
	
	
    /* CyGlobalIntEnable; */ /* Uncomment this line to enable global interrupts. */
    for(;;)
    {
 
   /* Place your application code here. */
    }
}

/* [] END OF FILE */

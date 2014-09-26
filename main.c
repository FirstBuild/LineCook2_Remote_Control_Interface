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
#include "e3/include/e3-hsm.h"
#include "e3/include/e3-timer.h"

#define COOKDEVICE_HSM(SIGNAL, STATE, SUBSTATE, PERMIT)                                                     \
    SIGNAL(RECEIVED_COOKING_INSTRUCTIONS_FROM_USER)                                                         \
    SIGNAL(READY_TO_PREHEAT)                                                                                \
    SIGNAL(PREHEAT_COMPLETE)                                                                                \
    SIGNAL(RECEIVED_OK_TO_START_COOKING_FROM_USER)                                                          \
    SIGNAL(COOKING_COMPLETE)                                                                                \
    STATE(readyForCook, readyForCook_enter, readyForCook_exit,                                              \
        PERMIT(RECEIVED_COOKING_INSTRUCTIONS_FROM_USER,sendCookCommandToIO))                                          \
    STATE(sendCookCommandToIO, sendCookCommandToIO_enter, sendCookCommandToIO_exit,                                                       \
        PERMIT(READY_TO_PREHEAT,preheat))                                                                   \
    STATE(preheat, preheat_enter, preheat_exit,                                                             \
         PERMIT(PREHEAT_COMPLETE,waitForUserFoodReady))                                                     \
    STATE(waitForUserFoodReady, waitForUserFoodReady_enter, waitForUserFoodReady_exit,                      \
        PERMIT(RECEIVED_OK_TO_START_COOKING_FROM_USER,convBaking))                                          \
    STATE(convBaking, convBaking_enter, convBaking_exit,                                                    \
        PERMIT(COOKING_COMPLETE,readyForCook))                                                              \

typedef struct microwave {
    e3_hsm_t microwave_sm;
    e3_timer_t preheat_run_timer;
} microwave_t;

static void readyForCook_enter(microwave_t *microwave) ;
static void readyForCook_exit(microwave_t *microwave) ;
static void sendCookCommandToIO_enter(microwave_t *microwave) ;
static void sendCookCommandToIO_exit(microwave_t *microwave) ;
static void preheat_enter(microwave_t *microwave) ;
static void preheat_tick(microwave_t *microwave) ;
static void preheat_exit(microwave_t *microwave);
static void waitForUserFoodReady_enter(microwave_t *microwave) ;
static void waitForUserFoodReady_exit(microwave_t *microwave) ;
static void convBaking_enter(microwave_t *microwave) ;
static void convBaking_exit(microwave_t *microwave) ;

E3_HSM_DEFINE(COOKDEVICE_HSM)

static void readyForCook_enter(microwave_t *microwave) {

}

static void readyForCook_exit(microwave_t *microwave) {
}

static void sendCookCommandToIO_enter(microwave_t *microwave) {

}

static void sendCookCommandToIO_exit(microwave_t *microwave) {
}

static void preheat_enter(microwave_t *microwave) {

    e3_timer_create(&microwave->preheat_run_timer, 0, (e3_timer_function_t) preheat_tick, microwave);
}

static void preheat_tick(microwave_t *microwave) {

    e3_timer_create(&microwave->preheat_run_timer, 0, (e3_timer_function_t) preheat_tick, microwave);
    //e3_hsm_dispatch(&microwave->microwave_sm, PREHEAT_COMPLETE);
}

static void preheat_exit(microwave_t *microwave) {
}

static void waitForUserFoodReady_enter(microwave_t *microwave) {

}

static void waitForUserFoodReady_exit(microwave_t *microwave) {
}

static void convBaking_enter(microwave_t *microwave) {

}

static void convBaking_exit(microwave_t *microwave) {
}


#define DMA_1_BYTES_PER_BURST 2
#define DMA_1_REQUEST_PER_BURST 1
#define DMA_1_SRC_BASE (CYDEV_PERIPH_BASE)
#define DMA_1_DST_BASE (CYDEV_SRAM_BASE)
/*define for the number of samples to be transferred to memory on each switch press*/
#define NO_OF_SAMPLES 3
uint16 screen_buffer[NO_OF_SAMPLES];

#define TIMEOUT	200u
#define READ_BUFFER_SIZE	05u
#define SLAVE_ADDRESS	0x08
#define MAIN_LOOP_DELAY	10u

uint8 MasterReadBuffer[READ_BUFFER_SIZE];

int main()
{
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    /* Variable declarations for DMA_1 */
    /* Move these variable declarations to the top of the function */
    uint8 DMA_1_Chan;
    uint8 DMA_1_TD[3];

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

    uint16 timeout;
	uint32 masterStatus;
	

	CyDelay(1000);	/* wait for P5LP to enable I2C pullups, etc. */
	
    CyGlobalIntEnable; /* Uncomment this line to enable global interrupts. */
	
	I2C_Start();
    
	microwave_t microwave;
   
    e3_hsm_create(&microwave.microwave_sm, readyForCook);
    
    uint8 MasterWriteBuffer[] = {0x01,0x00,0x01,0x01,0x17};
    
	
    I2C_MasterWriteBuf(SLAVE_ADDRESS,MasterWriteBuffer,sizeof(MasterWriteBuffer),I2C_MODE_COMPLETE_XFER );
    CyDelay(5000);
	
    /* CyGlobalIntEnable; */ /* Uncomment this line to enable global interrupts. */
    for(;;)
    {
        e3_timer_tick();
        
        masterStatus = 0;
		timeout = TIMEOUT;
		I2C_MasterClearStatus();
		I2C_MasterClearReadBuf();
	    I2C_MasterReadBuf(SLAVE_ADDRESS, MasterReadBuffer, sizeof(MasterReadBuffer), I2C_MODE_COMPLETE_XFER);
		while(!(masterStatus & I2C_MSTAT_RD_CMPLT) && timeout)
		{
			masterStatus = I2C_MasterStatus();
			timeout--;
		}

    }
}

/* [] END OF FILE */

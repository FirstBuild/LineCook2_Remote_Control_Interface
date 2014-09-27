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

uint32 WriteCommandPacket(uint8 cmd, uint8 param1, uint8 param2);


#define DMA_1_BYTES_PER_BURST 2
#define DMA_1_REQUEST_PER_BURST 1
#define DMA_1_SRC_BASE (CYDEV_PERIPH_BASE)
#define DMA_1_DST_BASE (CYDEV_SRAM_BASE)
/*define for the number of samples to be transferred to memory on each switch press*/
#define NO_OF_SAMPLES 3
uint16 screen_buffer[NO_OF_SAMPLES];

#define TIMEOUT	200u
#define READ_BUFFER_SIZE	05u
#define MAIN_LOOP_DELAY	10u

/* I2C slave address to communicate with */
#define SLAVE_ADDRESS  (0x08u)

/* Buffer and packet size */
#define BUFFER_SIZE     (5u)
#define PACKET_SIZE     (BUFFER_SIZE)

/* Packet positions */
#define PACKET_SOP_POS  (0u)
#define PACKET_CMD_POS  (1u)
#define PACKET_STS_POS  (PACKET_CMD_POS)
#define PACKET_EOP_POS  (4u)

/* Start and end of packet markers */
#define PACKET_SOP      (0x01u)
#define PACKET_EOP      (0x17u)

/* Command valid status */
#define STS_CMD_DONE    (0x00u)
#define STS_CMD_FAIL    (0xFFu)

/* Command valid status */
#define TRANSFER_CMPLT    (0x00u)
#define TRANSFER_ERROR    (0xFFu)


uint8 MasterReadBuffer[READ_BUFFER_SIZE];

/* Set USBUART buffer to maximum packet size of the IN and OUT bulk endpoints. */
#define USB_EP_BUFFER_LEN	64u

/* define constants for Carriage Return, Line Feed and Backspace */
#define CARRIAGE_RETURN	0x0d
#define LINE_FEED	0x0a
#define BACKSPACE	0x08

#define UART_BUFFER_SIZE 3

#define FALSE	0u
#define TRUE	1u


#define PACKET_START  0x01u
#define PACKET_END    0x17u

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
	
	/* USB buffer and byte count / pointer */
	uint8 usb_byte_count;
    uint8 usb_buffer[USB_EP_BUFFER_LEN];
	
	uint8 commandReady = 0;
	
	/* temp buffer and byte counter / pointer */
	uint8 temp_buffer_pointer = 0;
	uint8 tempBuffer[UART_BUFFER_SIZE];

	
	CyDelay(1000);	/* wait for P5LP to enable I2C pullups, etc. */
	
    CyGlobalIntEnable; /* Uncomment this line to enable global interrupts. */
	
	/* Start USBFS Operation with 3V operation */
    USBUART_Start(0u, USBUART_5V_OPERATION);

    /* Wait for Device to enumerate */
    while(!USBUART_GetConfiguration());

    /* Enumeration is done, enable OUT endpoint to receive data from Host */
    USBUART_CDC_Init();
	
	
	I2C_Start();
    
	microwave_t microwave;
	memset(&microwave.microwave_sm,0,sizeof(e3_hsm_t));
   
    e3_hsm_create(&microwave.microwave_sm, readyForCook);
    
    uint8 cookButton[] = {0x01u,0x01,0x00,0x00,0x17u};
	uint8 pushEnter[] = {0x01u,0x5,0x09,0x0,0x17u};
	uint8 start[] = {0x01u,0x5,0x0a,0x0,0x17u};
	uint8 pushOff[] = {0x01u,0x5,0x0b,0x0,0x17u};
    
	for(;;)
    {
		
		/* main loop checks for USBUART input and manages/updates I2C buffer */
		
		/* check if there is USB traffic to process */
		if(USBUART_DataIsReady() != 0u)	/* Check for input data from PC */
        {   
            usb_byte_count = USBUART_GetAll(usb_buffer);	/* Read received data and re-enable OUT endpoint */
            if(usb_byte_count != 0u)
            {
				/* if current character is a carriage return and 3 characters have been received, copy temp buffer to I2C buffer and add a LINE FEED */
				if(usb_buffer[0] == PACKET_START && usb_buffer[4] == PACKET_END)
				{
					WriteCommandPacket(usb_buffer[1], usb_buffer[2], usb_buffer[3]);
					
					// Clear buffers
					usb_buffer[0] = 0;
					usb_buffer[4] = 0;
				}
            }
        }
	
		
	}
	

//		
//		CyDelay(5000);
//		WriteCommandPacket(cookButton);
//    	CyDelay(500);
//		WriteCommandPacket(pushEnter);
//    	CyDelay(500);
//		WriteCommandPacket(start);
//    	CyDelay(10000);
//		WriteCommandPacket(pushOff);
//    	
//    for(;;)
//    {
//        e3_timer_tick();
//        
//        masterStatus = 0;
//		timeout = TIMEOUT;
//		I2C_MasterClearStatus();
//		I2C_MasterClearReadBuf();
//	    I2C_MasterReadBuf(SLAVE_ADDRESS, MasterReadBuffer, sizeof(MasterReadBuffer), I2C_MODE_COMPLETE_XFER);
//		while(!(masterStatus & I2C_MSTAT_RD_CMPLT) && timeout)
//		{
//			masterStatus = I2C_MasterStatus();
//			timeout--;
//		}
//
//    }
}


/*******************************************************************************
* WriteCommandPacket(): Writes command packet to I2C slave
*******************************************************************************/
uint32 WriteCommandPacket(uint8 cmd, uint8 param1, uint8 param2)
{
    uint8  buffer[BUFFER_SIZE];
    uint32 status = TRANSFER_ERROR;

    /* Initialize buffer with packet */
    buffer[PACKET_SOP_POS] = PACKET_SOP;
    buffer[PACKET_CMD_POS] = cmd;
	buffer[PACKET_CMD_POS + 1] = param1;
	buffer[PACKET_CMD_POS + 2] = param2;
    buffer[PACKET_EOP_POS] = PACKET_EOP;

    (void) I2C_MasterWriteBuf(SLAVE_ADDRESS, buffer, PACKET_SIZE, I2C_MODE_COMPLETE_XFER);

    while (0u == (I2C_MasterStatus() & I2C_MSTAT_WR_CMPLT))
    {
        /* Waits until master completes write transfer */
    }

    /* Displays transfer status */
    if (0u == (I2C_MSTAT_ERR_XFER & I2C_MasterStatus()))
    {
        /* Check if all bytes was written */
        if(I2C_MasterGetWriteBufSize() == BUFFER_SIZE)
        {
            status = TRANSFER_CMPLT;
        }
    }

    (void) I2C_MasterClearStatus();

    return (status);
}

/* [] END OF FILE */

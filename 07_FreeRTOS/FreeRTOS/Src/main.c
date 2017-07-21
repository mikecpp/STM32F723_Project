#include <string.h>

#include "main.h"
#include "stm32f723_system.h"
#include "uart.h"
#include "stm32f723e_discovery_lcd.h"
#include "stm32_gui.h"
#include "cmsis_os.h"

#define blckqSTACK_SIZE   configMINIMAL_STACK_SIZE
#define QUEUE_SIZE        (uint32_t) 1

osMessageQId osQueue;
uint32_t Count = 0;

static void ThreadDisplay(const void *arg);
static void ThreadCount(const void *arg);

static void ThreadDisplay(const void *arg)
{
    osEvent event;
    static uint32_t count = 0;
    static char msg[32];
    
    while(1) {
        event = osMessageGet(osQueue, 100);
        if(event.status == osEventMessage) {
            count = event.value.v;
            sprintf(msg, "Count = %d", count);
            GUI_DisplayStringAtLine(5, (uint8_t*) msg);
        }
    }
}

static void ThreadCount(const void *arg)
{
    while(1) {
        if(osMessagePut(osQueue, Count, 100) != osOK) {
            printf("osMessagePut error !\r\n");
        }
        else {
            Count++;
            osDelay(1000);
        }    
    }
}

int main(void)
{
    MPU_ConfigPSRAM();  
    CPU_CACHE_Enable();

    system_init();
      
    if(uart_init(UART_6, 115200) != 0) {
        return -1;
    }
    uart_consol(UART_6);
    
    printf("Start FreeRTOS Test ...\r\n");
    
    GUI_Register(&stm32_gui_interface); 
    GUI_Init();

    GUI_Clear(GUI_COLOR_BLACK); 
    GUI_SetBackColor(GUI_COLOR_BLACK);
    GUI_SetTextColor(GUI_COLOR_YELLOW);
    GUI_DisplayStringAtLine(3, (uint8_t*) "Hello Mike");

    osMessageQDef(osqueue, QUEUE_SIZE, uint16_t);
    osQueue = osMessageCreate(osMessageQ(osqueue), NULL);
    
    osThreadDef(Display, ThreadDisplay, osPriorityBelowNormal, 0, blckqSTACK_SIZE); 
    osThreadCreate(osThread(Display), NULL);
    
    osThreadDef(Count, ThreadCount, osPriorityBelowNormal, 0, blckqSTACK_SIZE);
    osThreadCreate(osThread(Count), NULL);
    
    osKernelStart();
    
    while (1) {
    }
}

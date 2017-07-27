#include <string.h>

#include "main.h"
#include "stm32f723_system.h"
#include "uart.h"
#include "stm32f723e_discovery_lcd.h"
#include "stm32_gui.h"
#include "cmsis_os.h"

#define blckqSTACK_SIZE   configMINIMAL_STACK_SIZE
#define QUEUE_SIZE        (uint32_t) 1

osMutexId count_mutex;
uint32_t count = 0;

static void printCount(char* thread_name);
static void thread_1(const void *arg);
static void thread_2(const void *arg);

static char msg[32];

static void printCount(char* thread_name)
{
    osMutexWait(count_mutex, osWaitForever);
    sprintf(msg, "%s:%d\r\n", thread_name, count++); 
    printf("%s", msg);
    osMutexRelease(count_mutex);
}

static void thread_1(const void *arg)
{
    while(1) {
        printCount("thread_1");
        osDelay(1000);
    }
}

static void thread_2(const void *arg)
{
    while(1) {
        printCount("thread_2");
        osDelay(1000);
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

    count_mutex = osMutexCreate(osMutexCreate(count_mutex));
    
    osThreadDef(One, thread_1, osPriorityBelowNormal, 0, blckqSTACK_SIZE); 
    osThreadCreate(osThread(One), NULL);
    
    osThreadDef(Two, thread_2, osPriorityBelowNormal, 0, blckqSTACK_SIZE);
    osThreadCreate(osThread(Two), NULL);
    
    osKernelStart();
    
    while (1) {
    }
}

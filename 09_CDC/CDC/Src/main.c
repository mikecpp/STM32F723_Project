#include <string.h>

#include "main.h" 
#include "stm32f723_system.h"
#include "uart.h"
#include "stm32f723e_discovery_lcd.h"
#include "stm32_gui.h"
#include "cmsis_os.h"

#define blckqSTACK_SIZE   configMINIMAL_STACK_SIZE
#define QUEUE_SIZE        (uint32_t) 1

USBD_HandleTypeDef USBD_Device; 

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
    
    USBD_Init(&USBD_Device, &VCP_Desc, 0);
    USBD_RegisterClass(&USBD_Device, USBD_CDC_CLASS);
    USBD_CDC_RegisterInterface(&USBD_Device, &USBD_CDC_fops);
    USBD_Start(&USBD_Device);
   
    int  count = 0;
    while (1) {
        printf("Count = %d \r\n", count++);
        delay_ms(1000);
    }
}

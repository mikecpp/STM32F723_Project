#include "main.h"
#include "stm32f723_system.h"
#include "uart.h"

static void CPU_CACHE_Enable(void);

int main(void)
{
    int count = 0;
    
    CPU_CACHE_Enable();

    system_init();
      
    if(uart_init(UART_6, 115200) != 0) {
        return -1;
    }
    uart_consol(UART_6);
    
    printf("Hello Mike !\r\n");
    
    while (1)
    {
        printf("Count = %d \r\n", count++);
        delay_ms(1000);
    }
}

static void CPU_CACHE_Enable(void)
{
    SCB_EnableICache();
    SCB_EnableDCache();
}

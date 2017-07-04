#include "main.h"
#include "stm32f723_system.h"
#include "uart.h"
#include "cli.h"

static void CPU_CACHE_Enable(void);

int main(void)
{
    CPU_CACHE_Enable();

    system_init();
      
    if(uart_init(UART_6, 115200) != 0) {
        return -1;
    }
    uart_consol(UART_6);
    cli_init(UART_6);
    
    printf("Start CLI ...\r\n");
    
    while (1)
    {
        cli_process();
    }
}

static void CPU_CACHE_Enable(void)
{
    SCB_EnableICache();
    SCB_EnableDCache();
}

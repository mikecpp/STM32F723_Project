#include "main.h"
#include "stm32f723_system.h"
#include "uart.h"
#include "stm32_i2c.h"
#include "oled1602.h"

static void CPU_CACHE_Enable(void)
{
    SCB_EnableICache();
    SCB_EnableDCache();
}

int main(void)
{
    int count = 0;
    char msg[16];

    CPU_CACHE_Enable();
    
    system_init();
    uart_init(UART_6, 115200);
    uart_consol(UART_6);
    
    i2c_register_driver(&stm32_i2c_drv);     
    oled1602_init(I2C_2);
    
    printf("Hello Mike !\r\n");
    oled1602_cursor(0, 0);
    oled1602_puts("Hello Mike");
    
    while (1)
    {
        printf("count = %d \r\n", count++);
        sprintf(msg, "Count = %d", count);
        oled1602_cursor(0, 1);
        oled1602_puts(msg);
        delay_ms(1000);
    }
}    

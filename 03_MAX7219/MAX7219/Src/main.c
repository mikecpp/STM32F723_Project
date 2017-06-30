#include "main.h"
#include "stm32f723_system.h"
#include "uart.h"
#include "stm32_i2c.h"
#include "stm32_spi.h"
#include "max7219.h"

static void CPU_CACHE_Enable(void)
{
    SCB_EnableICache();
    SCB_EnableDCache();
}

int main(void)
{
    int count = 0;

    CPU_CACHE_Enable();
    
    system_init();
    uart_init(UART_6, 115200);
    uart_consol(UART_6);
    
    i2c_register_driver(&stm32_i2c_drv);     
    spi_register_driver(&stm32_spi_drv);
    
    max7219_init(SPI_1);

    printf("MAX7219 Test !!! \r\n"); 
    
    while (1)
    {
        printf("Count = %d \r\n", count++);
        max7219_char('0' + count % 10);
        delay_ms(1000);
    }
}    

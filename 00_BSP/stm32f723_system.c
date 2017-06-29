#include "stm32f723_system.h"
#include "stm32f723_uart.h"
#include "stm32f723_i2c.h"

static void SystemClock_Config(void);

int system_init(void)
{
    HAL_Init();

    SystemClock_Config();   
    
    return 0;
}

void delay_ms(uint32_t millis)
{
    HAL_Delay(millis);
}

/**
  * @brief  System Clock Configuration
  *         The system Clock is configured as follow : 
  *            System Clock source            = PLL (HSE)
  *            SYSCLK(Hz)                     = 216000000
  *            HCLK(Hz)                       = 216000000
  *            AHB Prescaler                  = 1
  *            APB1 Prescaler                 = 4
  *            APB2 Prescaler                 = 2
  *            HSE Frequency(Hz)              = 25000000
  *            PLL_M                          = 25
  *            PLL_N                          = 432
  *            PLL_P                          = 2
  *            PLL_Q                          = 9
  *            VDD(V)                         = 3.3
  *            Main regulator output voltage  = Scale1 mode
  *            Flash Latency(WS)              = 7
  * @param  None
  * @retval None
  */
void SystemClock_Config(void)
{
    RCC_ClkInitTypeDef RCC_ClkInitStruct;
    RCC_OscInitTypeDef RCC_OscInitStruct;

    /* Enable HSE Oscillator and activate PLL with HSE as source */
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
    RCC_OscInitStruct.HSEState = RCC_HSE_ON;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
    RCC_OscInitStruct.PLL.PLLM = 25;
    RCC_OscInitStruct.PLL.PLLN = 432;  
    RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
    RCC_OscInitStruct.PLL.PLLQ = 9;

    if(HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
    {
        while(1) {};
    }
  
    /* Activate the OverDrive to reach the 216 Mhz Frequency */
    if(HAL_PWREx_EnableOverDrive() != HAL_OK)
    {
        while(1) {};
    }
  
    /* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2 
       clocks dividers */
    RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;  
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;  
    if(HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_7) != HAL_OK)
    {
        while(1) {};
    }
}

void HAL_UART_MspInit(UART_HandleTypeDef *huart)
{  
    GPIO_InitTypeDef  GPIO_InitStruct;
  
    // UART_2
    USART2_TX_GPIO_CLK_ENABLE();
    USART2_RX_GPIO_CLK_ENABLE();

    USART2_CLK_ENABLE(); 
  
    GPIO_InitStruct.Pin       = USART2_TX_PIN;
    GPIO_InitStruct.Mode      = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull      = GPIO_PULLUP;
    GPIO_InitStruct.Speed     = GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.Alternate = USART2_TX_AF;

    HAL_GPIO_Init(USART2_TX_GPIO_PORT, &GPIO_InitStruct);

    GPIO_InitStruct.Pin       = USART2_RX_PIN;
    GPIO_InitStruct.Alternate = USART2_RX_AF;

    HAL_GPIO_Init(USART2_RX_GPIO_PORT, &GPIO_InitStruct);
    
    // UART_6
    USART6_TX_GPIO_CLK_ENABLE();
    USART6_RX_GPIO_CLK_ENABLE();

    USART6_CLK_ENABLE();

    GPIO_InitStruct.Pin       = USART6_TX_PIN;
    GPIO_InitStruct.Mode      = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull      = GPIO_PULLUP;
    GPIO_InitStruct.Speed     = GPIO_SPEED_HIGH;
    GPIO_InitStruct.Alternate = USART6_TX_AF;

    HAL_GPIO_Init(USART6_TX_GPIO_PORT, &GPIO_InitStruct);

    GPIO_InitStruct.Pin       = USART6_RX_PIN;
    GPIO_InitStruct.Alternate = USART6_RX_AF;

    HAL_GPIO_Init(USART6_RX_GPIO_PORT, &GPIO_InitStruct);    
}

void HAL_UART_MspDeInit(UART_HandleTypeDef *huart)
{
    // UART_2    
    USART2_FORCE_RESET();
    USART2_RELEASE_RESET();

    HAL_GPIO_DeInit(USART2_TX_GPIO_PORT, USART2_TX_PIN);
    HAL_GPIO_DeInit(USART2_RX_GPIO_PORT, USART2_RX_PIN);
    
    // UART_6
    USART6_FORCE_RESET();
    USART6_RELEASE_RESET();

    HAL_GPIO_DeInit(USART6_TX_GPIO_PORT, USART6_TX_PIN);
    HAL_GPIO_DeInit(USART6_RX_GPIO_PORT, USART6_RX_PIN);
}

void HAL_I2C_MspInit(I2C_HandleTypeDef *hi2c)
{
    GPIO_InitTypeDef  GPIO_InitStruct;
    
    I2C1_SCL_GPIO_CLK_ENABLE(); 
    I2C1_SDA_GPIO_CLK_ENABLE();

    I2C1_CLK_ENABLE(); 

    GPIO_InitStruct.Pin       = I2C1_SCL_PIN;
    GPIO_InitStruct.Mode      = GPIO_MODE_AF_OD;
    GPIO_InitStruct.Pull      = GPIO_PULLUP;
    GPIO_InitStruct.Speed     = GPIO_SPEED_HIGH;
    GPIO_InitStruct.Alternate = I2C1_SCL_AF;
    HAL_GPIO_Init(I2C1_SCL_GPIO_PORT, &GPIO_InitStruct);      

    GPIO_InitStruct.Pin       = I2C1_SDA_PIN;
    GPIO_InitStruct.Alternate = I2C1_SDA_AF;
    
    HAL_GPIO_Init(I2C1_SDA_GPIO_PORT, &GPIO_InitStruct);    
    
    I2C2_SCL_GPIO_CLK_ENABLE(); 
    I2C2_SDA_GPIO_CLK_ENABLE();

    I2C2_CLK_ENABLE(); 

    GPIO_InitStruct.Pin       = I2C2_SCL_PIN;
    GPIO_InitStruct.Mode      = GPIO_MODE_AF_OD;
    GPIO_InitStruct.Pull      = GPIO_PULLUP;
    GPIO_InitStruct.Speed     = GPIO_SPEED_HIGH;
    GPIO_InitStruct.Alternate = I2C2_SCL_AF;
    HAL_GPIO_Init(I2C2_SCL_GPIO_PORT, &GPIO_InitStruct);      

    GPIO_InitStruct.Pin       = I2C2_SDA_PIN;
    GPIO_InitStruct.Alternate = I2C2_SDA_AF;
    
    HAL_GPIO_Init(I2C2_SDA_GPIO_PORT, &GPIO_InitStruct);    
}

void HAL_I2C_MspDeInit(I2C_HandleTypeDef *hi2c)
{
    I2C1_FORCE_RESET();
    I2C1_RELEASE_RESET();

    HAL_GPIO_DeInit(I2C1_SCL_GPIO_PORT, I2C1_SCL_PIN);
    HAL_GPIO_DeInit(I2C1_SDA_GPIO_PORT, I2C1_SDA_PIN);

    I2C2_FORCE_RESET();
    I2C2_RELEASE_RESET();

    HAL_GPIO_DeInit(I2C2_SCL_GPIO_PORT, I2C2_SCL_PIN);
    HAL_GPIO_DeInit(I2C2_SDA_GPIO_PORT, I2C2_SDA_PIN);
}

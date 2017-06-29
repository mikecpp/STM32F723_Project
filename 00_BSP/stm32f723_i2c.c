#include "stm32f723_i2c.h"

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

#include <stdio.h>

#include "i2c.h"

#define I2C_MAX_NUM         4
#define I2C_ADDRESS         0x3C << 1
#define I2C_SPEEDCLOCK      400000 
#define I2C_TIMEOUT         10000    // 1 second

I2C_HandleTypeDef m_i2c_handle[I2C_MAX_NUM];

I2C_HandleTypeDef* i2c_handle(uint8_t id)
{
    I2C_HandleTypeDef *p_i2c_handle = NULL; 
    
    switch(id) {
        case I2C_1:
            p_i2c_handle = &m_i2c_handle[0]; 
            p_i2c_handle->Instance = I2C1;  
            break;
        case I2C_2:
            p_i2c_handle = &m_i2c_handle[1];
            p_i2c_handle->Instance = I2C2;
            break;
        default: 
            return NULL;
    }
       
    return p_i2c_handle;
}

int i2c_init(uint8_t id)
{
    I2C_HandleTypeDef *p_i2c_handle = i2c_handle(id);

    p_i2c_handle->Init.ClockSpeed      = I2C_SPEEDCLOCK; 
    p_i2c_handle->Init.DutyCycle       = I2C_DUTYCYCLE_2;
    p_i2c_handle->Init.OwnAddress1     = 0x00;
    p_i2c_handle->Init.OwnAddress2     = 0x00;
    p_i2c_handle->Init.AddressingMode  = I2C_ADDRESSINGMODE_7BIT;
    p_i2c_handle->Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
    p_i2c_handle->Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
    p_i2c_handle->Init.NoStretchMode   = I2C_NOSTRETCH_DISABLE;  
  
    if(HAL_I2C_Init(p_i2c_handle) != HAL_OK) {
        return -1;
    }

    return 0;
}

int i2c_write_byte(uint8_t id, uint8_t addr, uint8_t value)
{
    I2C_HandleTypeDef *p_i2c_handle = i2c_handle(id);
   
    if(HAL_I2C_Master_Transmit(p_i2c_handle, addr, (uint8_t*) &value, 1, I2C_TIMEOUT) != HAL_OK) {
        return -1;
    }    
    
    return 0;
}

int i2c_read_byte(uint8_t id, uint8_t addr, uint8_t *value)
{
    I2C_HandleTypeDef *p_i2c_handle = i2c_handle(id);    
    
    if(HAL_I2C_Master_Receive(p_i2c_handle, addr, value, 1, I2C_TIMEOUT) != HAL_OK) {
        return -1;
    }    

    return 0;
}

int i2c_write(uint8_t id, uint8_t addr, uint8_t *buf, int len)
{
    I2C_HandleTypeDef *p_i2c_handle = i2c_handle(id);    
    uint32_t ret;
    
    if(HAL_I2C_Master_Transmit(p_i2c_handle, addr, buf, len, I2C_TIMEOUT) != HAL_OK) {
        ret = HAL_I2C_GetError(p_i2c_handle);
        return ret;
    }    
    
    return 0; 
}

int i2c_read(uint8_t id, uint8_t addr, uint8_t *buf, int len) 
{
    I2C_HandleTypeDef *p_i2c_handle = i2c_handle(id);    
    uint32_t ret;   
    
    if(HAL_I2C_Master_Receive(p_i2c_handle, addr, buf, len, I2C_TIMEOUT) != HAL_OK) {
        ret = HAL_I2C_GetError(p_i2c_handle); 
        return ret;
    }
    
    return 0;    
}

int i2c_write_reg(uint8_t id, uint8_t addr, uint8_t reg, uint8_t value)
{
    uint32_t ret_code;
    uint8_t buf[2];
    
    buf[0] = reg;
    buf[1] = value;
    
    ret_code = i2c_write(id, addr, (uint8_t*) buf, 2);
    
    return ret_code;
}

int i2c_read_reg(uint8_t id, uint8_t addr, uint8_t reg, uint8_t *value)
{
    uint32_t ret_code;
    
    ret_code = i2c_write_byte(id, addr, reg); 
    ret_code = i2c_read_byte(id, addr, value);
    
    return ret_code;
}

int i2c_write_reg_word(uint8_t id, uint8_t addr, uint8_t reg, uint16_t value)
{
    uint32_t ret_code;
    uint8_t buf[3];
    
    buf[0] = reg;
    buf[1] = (value & 0xFF00) >> 8;
    buf[2] = value & 0x00FF;
    
    ret_code = i2c_write(id, addr, buf, 3);
    
    return ret_code;
}

int i2c_read_reg_word(uint8_t id, uint8_t addr, uint8_t reg, uint16_t *value)
{
    uint32_t ret_code;
    uint8_t buf[2];
    
    ret_code = i2c_write_byte(id, addr, reg);   
    ret_code = i2c_read(id, addr, buf, 2);
    
    *value  = buf[1] << 8;  // HIGH BYTE
    *value += buf[0];       // LOW  BYTE
    
    return ret_code;
}

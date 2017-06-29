#ifndef __I2C_H__
#define __I2C_H__

#ifdef STM32L476xx
    #include "stm32l4xx_hal.h"
    #include "stm32l4xx_hal_i2c.h"
    #include "stm32l476_system.h"
#endif

#ifdef STM32F103xE
    #include "stm32f1xx_hal.h"
    #include "stm32f1xx_hal_i2c.h"
    #include "stm32f103_system.h"
#endif

#ifdef STM32F412Zx
    #include "stm32f4xx_hal.h"
    #include "stm32f4xx_hal_i2c.h"
    #include "stm32f412_system.h"    
#endif

#ifdef STM32F429xx
    #include "stm32f4xx_hal.h"
    #include "stm32f4xx_hal_i2c.h"
    #include "stm32f429_system.h"    
#endif

#ifdef STM32F407xx
    #include "stm32f4xx_hal.h"
    #include "stm32f4xx_hal_i2c.h"
    #include "stm32f407_system.h"    
#endif

typedef enum {
    I2C_1,
    I2C_2
} I2C_ID;

int i2c_init(uint8_t id); 
int i2c_write_byte(uint8_t id, uint8_t addr, uint8_t value); 
int i2c_read_byte(uint8_t id, uint8_t addr, uint8_t *value); 
int i2c_write(uint8_t id, uint8_t addr, uint8_t *buf, int len);
int i2c_read(uint8_t id, uint8_t addr, uint8_t *buf, int len);
int i2c_write_reg(uint8_t id, uint8_t addr, uint8_t reg, uint8_t value); 
int i2c_read_reg(uint8_t id, uint8_t addr, uint8_t reg, uint8_t *value);
int i2c_write_reg_word(uint8_t id, uint8_t addr, uint8_t reg, uint16_t value); 
int i2c_read_reg_word(uint8_t id, uint8_t addr, uint8_t reg, uint16_t *value);

#endif//_I2C_STM32F4_H__
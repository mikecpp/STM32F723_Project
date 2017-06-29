#ifndef __SPI_H__
#define __SPI_H__

#ifdef STM32L476xx
    #include "stm32l4xx_hal.h"
    #include "stm32l4xx_hal_spi.h"
    #include "stm32l476_system.h"
#endif

#ifdef STM32F103xE
    #include "stm32f1xx_hal.h"
    #include "stm32f1xx_hal_spi.h"
    #include "stm32f103_system.h"
#endif

#ifdef STM32F429xx
    #include "stm32f4xx_hal.h"
    #include "stm32f4xx_hal_spi.h"
    #include "stm32f429_system.h"
    #include "stm32f429_spi.h"
#endif

#ifdef STM32F412Zx
    #include "stm32f4xx_hal.h"
    #include "stm32f4xx_hal_spi.h"
    #include "stm32f412_system.h"
    #include "stm32f412_spi.h"
#endif

typedef enum {
    SPI_0,
    SPI_1,
    SPI_2
} SPI_ID;

int spi_init(uint8_t id);
int spi_write_read(uint8_t id, uint8_t *pWrite, uint8_t *pRead, uint16_t len);
int spi_write(uint8_t id, uint8_t *pData, uint16_t len);

#endif//__SPI_H__

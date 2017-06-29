#include "spi.h"

#define SPI_MAX_NUM         2
#define SPI_TIMEOUT         10000    // 1 second

SPI_HandleTypeDef m_spi_handle[SPI_MAX_NUM];

SPI_HandleTypeDef* spi_handle(uint8_t id)
{
    SPI_HandleTypeDef *p_spi_handle = NULL; 
    
    switch(id) {
        case SPI_1:
            p_spi_handle = &m_spi_handle[0]; 
            p_spi_handle->Instance = SPI1;  
            break;
        case SPI_2:
            p_spi_handle = &m_spi_handle[1];
            p_spi_handle->Instance = SPI2;
            break;
        default: 
            return NULL;
    }
       
    return p_spi_handle;
}

void spi_ss_low(uint8_t id)
{
    if(id == SPI_1) {
        HAL_GPIO_WritePin(SPI1_NSS_GPIO_PORT, SPI1_NSS_PIN, GPIO_PIN_RESET);    
    }
    
    if(id == SPI_2) {
        HAL_GPIO_WritePin(SPI2_NSS_GPIO_PORT, SPI2_NSS_PIN, GPIO_PIN_RESET);           
    }
}

void spi_ss_high(uint8_t id)
{
    if(id == SPI_1) {
        HAL_GPIO_WritePin(SPI1_NSS_GPIO_PORT, SPI1_NSS_PIN, GPIO_PIN_SET);    
    }
    
    if(id == SPI_2) {
        HAL_GPIO_WritePin(SPI2_NSS_GPIO_PORT, SPI2_NSS_PIN, GPIO_PIN_SET);           
    }    
}

//////////////////////////////////////////////////////////////////////////////
// SPI
//
int spi_init(uint8_t id)
{
    SPI_HandleTypeDef *p_spi_handle = spi_handle(id);    
    
    p_spi_handle->Init.BaudRatePrescaler  = SPI_BAUDRATEPRESCALER_8; 
    p_spi_handle->Init.Direction          = SPI_DIRECTION_2LINES;
    p_spi_handle->Init.CLKPhase           = SPI_PHASE_1EDGE;
    p_spi_handle->Init.CLKPolarity        = SPI_POLARITY_LOW; 
    p_spi_handle->Init.CRCCalculation     = SPI_CRCCALCULATION_DISABLE;
    p_spi_handle->Init.CRCPolynomial      = 7;
    p_spi_handle->Init.DataSize           = SPI_DATASIZE_8BIT;
    p_spi_handle->Init.FirstBit           = SPI_FIRSTBIT_MSB;
    p_spi_handle->Init.NSS                = SPI_NSS_SOFT;
    p_spi_handle->Init.TIMode             = SPI_TIMODE_DISABLE;
    p_spi_handle->Init.Mode               = SPI_MODE_MASTER;
    
    if(HAL_SPI_Init(p_spi_handle) != HAL_OK) {
        return -1;
    }    
    
    return 0;
}

int spi_write_read(uint8_t id, uint8_t *pWrite, uint8_t *pRead, uint16_t len)
{
    HAL_StatusTypeDef status = HAL_OK;
    SPI_HandleTypeDef *p_spi_handle = spi_handle(id);    
    
    spi_ss_low(id);
  
    status = HAL_SPI_TransmitReceive(p_spi_handle, pWrite, pRead, len, SPI_TIMEOUT);

    spi_ss_high(id);
    
    if(status != HAL_OK) {
        return -1;
    }    
    
    return 0;
}

int spi_write(uint8_t id, uint8_t *pData, uint16_t len)
{
    HAL_StatusTypeDef status = HAL_OK;
    SPI_HandleTypeDef *p_spi_handle = spi_handle(id);    

    spi_ss_low(id);
    
    status = HAL_SPI_Transmit(p_spi_handle, pData, len, SPI_TIMEOUT);

    spi_ss_high(id);
    
    if(status != HAL_OK) {
        return -1;
    }    
    
    return 0;
}

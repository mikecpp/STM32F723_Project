#include "stm32_gui.h"
#include "stm32f723e_discovery_lcd.h"

GUI_Interface_T stm32_gui_interface = 
{
    .GUI_Init           = STM32_GUI_Init, 
    .GUI_GetXSize       = STM32_GUI_GetXSize,
    .GUI_GetYSize       = STM32_GUI_GetYSize,
    .GUI_ReadPixel      = STM32_GUI_ReadPixel,
    .GUI_DrawPixel      = STM32_GUI_DrawPixel,
    .GUI_Clear          = STM32_GUI_Clear,
    .GUI_DrawBitmap     = STM32_GUI_DrawBitmap,
    .GUI_DrawRGBImage   = STM32_GUI_DrawRGBImage
};

int32_t STM32_GUI_Init(void)
{
    BSP_LCD_Init();
    
    return 0;
}

int32_t STM32_GUI_GetXSize(void)
{
    uint32_t width = BSP_LCD_GetXSize();
    
    return width;
}

int32_t STM32_GUI_GetYSize(void)
{
    uint32_t height = BSP_LCD_GetYSize();
    
    return height;
}

int32_t STM32_GUI_ReadPixel(uint16_t Xpos, uint16_t Ypos, uint32_t *Color)
{
    *Color = BSP_LCD_ReadPixel(Xpos, Ypos);
       
    return 0;
}

int32_t STM32_GUI_DrawPixel(uint16_t Xpos, uint16_t Ypos, uint32_t Color)
{
    BSP_LCD_DrawPixel(Xpos, Ypos, Color); 
    
    return 0;
}

int32_t STM32_GUI_Clear(uint32_t Color)
{
    BSP_LCD_Clear(Color);  
    
    return 0;
}

int32_t STM32_GUI_DrawBitmap(uint16_t Xpos, uint16_t Ypos, uint8_t *pbmp)
{
    return 0;
}

int32_t STM32_GUI_DrawRGBImage(uint16_t Xpos, uint16_t Ypos, uint16_t Xsize, uint16_t Ysize, uint8_t *pbmp)
{
    return 0;
}

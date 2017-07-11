#include <string.h>

#include "main.h"
#include "stm32f723_system.h"
#include "uart.h"
#include "frame.h"

static void print_hex(char *data, uint16_t len)
{
    int  i;
    char *ptr = data;
    
    printf("len = %d \r\n", len);
    
    while(ptr < (data + len)) { 
        for(i=0; i<16; i++) {
            printf("%02X ", *(ptr++));
            if(ptr >= (data + len)) {
                break;
            }
        }
        printf("\r\n");
    }    
}    

static char input[256], output[550];

#define FRAME_LEN  32

static void test_frame(void)
{
    uint16_t len_enc, len_dec;
    int i;
    
    for(i=0; i<FRAME_LEN; i++) {
        input[i] = i;
    }

    frame_encode((char*) input, FRAME_LEN, (char*) output, &len_enc); 
    print_hex(output, len_enc);
    
    memset((char*) input, 0x00, FRAME_LEN);
    
    int32_t ret;
    
    ret = frame_decode((char*) output, len_enc, (char*) input, &len_dec);
    if(ret != 0) {
        printf("ret = %d \r\n", ret);
    }
    print_hex(input, len_dec);
}

int main(void)
{
    CPU_CACHE_Enable();

    system_init();
      
    if(uart_init(UART_6, 115200) != 0) {
        return -1;
    }
    uart_consol(UART_6);
    
    printf("Start Frame Test ...\r\n");
    
    test_frame();
    
    while (1)
    {
        delay_ms(1000);
    }
}

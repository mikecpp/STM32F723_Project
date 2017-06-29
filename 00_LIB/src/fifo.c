#include <stdio.h>
#include <string.h>

#include "fifo.h"

#define MAX_HANDLE      10

typedef struct {
    char *buffer;
    char *start;
    char *end;
    int  len;
} fifo_t;    

static fifo_t m_table[MAX_HANDLE];
static int    m_handle = -1;

int fifo_init(char *buffer, int len)
{
    m_handle++;
    if(m_handle >= MAX_HANDLE) {
        return -1;
    }
    
    m_table[m_handle].buffer = buffer;
    m_table[m_handle].start  = buffer + (len - 1);
    m_table[m_handle].end    = buffer;
    m_table[m_handle].len    = len;
    
    return m_handle;
}

int fifo_write(int handle, char *data, int len)
{
    int i;
    int count = 0;
    
    for(i=0; i<len; i++) {      
        if((m_table[handle].end) >= (m_table[handle].buffer + m_table[handle].len)) {
            m_table[handle].end = m_table[handle].buffer;    // Wrap
        }
        
        if((m_table[handle].end) == m_table[handle].start) { // Overflow
            return count;
        }
               
        *(m_table[handle].end) = *(data + i);    
        m_table[handle].end++;
        count++;
    }    
    
    return count;
}

int fifo_read(int handle, char *data, int len)
{
    int i;
    int count = 0;
    
    for(i=0; i<len; i++) {      
        if((m_table[handle].start + 1) >= (m_table[handle].buffer + m_table[handle].len)) {
            m_table[handle].start = m_table[handle].buffer;  // Wrap
        }
        else {
            m_table[handle].start++;               
        }
 
        if(m_table[handle].start == m_table[handle].end) {   // Underflow
            if(m_table[handle].start == m_table[handle].buffer) { 
                m_table[handle].start = m_table[handle].buffer + (m_table[handle].len - 1);;
            } 
            else {
                m_table[handle].start--;
            }    
            return count;
        }
       
        *(data + i) = *(m_table[handle].start); 
        count++;
    }    
    
    return count;
}

int fifo_clean(int handle)
{
    m_table[handle].start  = m_table[handle].buffer + (m_table[handle].len - 1);
    m_table[handle].end    = m_table[handle].buffer;
    
    return 0;
}

int fifo_available(int handle)
{
    if((m_table[handle].start + 1) == (m_table[handle].buffer + m_table[handle].len)) {
        if(m_table[handle].end == m_table[handle].buffer) {
            return 0; // Empty
        }
    }
     
    if((m_table[handle].start + 1) == m_table[handle].end) {
        return 0; // Empty
    }    
    
    return 1;
}

//////////////////////////////////////////////////////////////////////////////
// Test Code
//

#define MAX_BUF_LEN     19

static char m_buffer[MAX_BUF_LEN];

void fifo_test(void)
{
    int  handle;
    char buf[MAX_BUF_LEN];
    int ret;
    
    handle = fifo_init(m_buffer, MAX_BUF_LEN);
   
    ret = fifo_write(handle, "ABCDEFGHIJ", 10);
    printf("ret = %d \r\n", ret);
    if(ret < 10) {
        printf(">>> Overflow !!!\r\n");
    }   

    ret = fifo_write(handle, "1234567890", 10);
    printf("ret = %d \r\n", ret);
    if(ret < 10) {
        printf(">>> Overflow !!!\r\n");
    }   
       
    int i;
    for(i=0; i<4; i++) {
        memset(buf, 0x00, 5);
        if(fifo_available(handle)) {        
            ret = fifo_read(handle, buf, 5);
            if(ret < 5) {
                printf(">>> Underflow !!!\r\n");
            }
        
            buf[5] = 0x00;
            printf("%d: %s %d\r\n", i, buf, ret);
        }    
    }    

    ret = fifo_write(handle, "ABCDEFGHIJ", 10);
    printf("ret = %d \r\n", ret);
    if(ret < 10) {
        printf(">>> Overflow !!!\r\n");
    }   
    
    ret = fifo_write(handle, "1234567890", 10);
    printf("ret = %d \r\n", ret);
    if(ret < 10) {
        printf(">>> Overflow !!!\r\n");
    }   
    
    for(i=0; i<4; i++) {
        memset(buf, 0x00, 10);
        if(fifo_available(handle)) {
            ret = fifo_read(handle, buf, 10);
            if(ret < 10) {
                printf(">>> Underflow !!!\r\n");
            }           
            buf[10] = 0x00;
            printf("%d: %s %d\r\n", i, buf, ret);
        }    
    }    
}

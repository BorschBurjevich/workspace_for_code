#ifndef SET_DEVICE_H_
#define SET_DEVICE_H_
#define MSB_FIRST (1U)
#define DEBUG (MSB_FIRST)

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int write_then_read_device(char *buf_write, int size);

int set_device(char *p_buf, char *data_for_reciever, int n_bytes, int len_device_data, char addr_transmit,
               char addr_reciever);

int solve_CRC(char *p_buf, int n_bytes);

char *read_word(char *buf_read, int size);

int write_word(char *buf_write, int size);


static void delay_ms(int ms) // установка задержки в милисек. 
{
    int c;
    c = clock() + ms;
    while (clock() < c);
}


#endif /*SET_DEVICE_H_*/

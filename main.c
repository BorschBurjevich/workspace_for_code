/*****************************************************************************
 * Test_1.c
 *****************************************************************************/

#include "set_device.h"

int main(void) {
    char *p_buf;// глобальный указатель на буфер приёма/передачи
    int status;
    int size_data = 2;
    int size_buf = 7 + size_data; // размер буфера в байтах
    char *data;// данные на передачу
    char transmit = 0x10;
    char reciev = 0x12;


    p_buf = (char *) malloc(sizeof(char) * size_buf);
    data = (char *) malloc(sizeof(char) * size_data);
    /*подыгрыш*/
    data[0] = 0x07;
    data[1] = 0xAA;
    status = set_device(p_buf, data, size_buf, size_data, transmit, reciev);
    if (status == 0x2) {
        printf("Set device is finished with code error: %i\n", status);
    } else if (status == 0x1) {
        printf("Set device is finished with code error: %i\n", status);
    }
    free(p_buf);
    free(data);
    /* Begin adding your custom code here */
    return 0;
}


		


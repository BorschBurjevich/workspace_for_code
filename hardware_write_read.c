#include "set_device.h"

// 0 - �������� ���������
int write_word(char *buf_write, int size) {
    int counter;
#if DEBUG == MSB_FIRST                                        // ���� ���������� ��������� msbfirst
    /*������� �������� �� ����������*/                            // �������� ������ �� ������������� ���������
    return 0;
#endif

#if DEBUG != MSB_FIRST                                        //���� ���������� ��������� lsbfirst
    for	(counter = 0; counter < size; counter++)
    {
        buf_write[counter] = (buf_write[counter] & 0xF0)>>4 | (buf_write[counter] & 0x0F)<<4;
        buf_write[counter] = (buf_write[counter] & 0xCC)>>2 | (buf_write[counter] & 0x33)<<2;
        buf_write[counter] = (buf_write[counter] & 0xAA)>>1 | (buf_write[counter] & 0x55)<<1;
    }
    /*������� �������� �� ����������*/
    return 0;
#endif
}

// ���������� ��������� �� ����� ������
char *read_word(char *buf_read, int size) {
    /*������� ������ �� ����������*/

#if DEBUG != MSB_FIRST                                        //���� ���������� ����� lsbfirst, ������������� �����
    for	(counter = 0; counter < size; counter++)
    {
        size[counter] = (size[counter] & 0xF0)>>4 | (size[counter] & 0x0F)<<4;
        size[counter] = (size[counter] & 0xCC)>>2 | (size[counter] & 0x33)<<2;
        size[counter] = (size[counter] & 0xAA)>>1 | (size[counter] & 0x55)<<1;
    }

#endif
    return buf_read;
}


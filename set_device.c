#include "set_device.h"

//Возвращает 0x0 - корректные данные
//0x1 - нет ответа от устройства
//0x2 - не сошлась контрольная сумма,данные приняты некорректн
int set_device(char *p_buf, char *data_for_reciever, int n_bytes, const int len_device_data, char addr_transmit,
               char addr_reciever) {
    int size_CRC = 4;        // предположительный размер для CRC
    char *save_p = 0;
    int counter, indx;
    int tmp = 0;
    int status = 0;
    save_p = p_buf;
    save_p[0] = 0x01;
    save_p[1] = 0x02;
    save_p[2] = 0x03;
    save_p[3] = 0x04;
    indx = 4;
    n_bytes += size_CRC;            // длина кодограммы на отправку с учётом поля для CRC
    save_p[indx++] = n_bytes;
    save_p[indx++] = addr_transmit;
    save_p[indx++] = addr_reciever;
    for (counter = 0; counter < len_device_data; counter++) {
        save_p[indx + counter] = data_for_reciever[counter];
    }
    indx++;
    tmp = solve_CRC;
    save_p[indx] = (char) (tmp & 0x000000ff);
    indx++;
    save_p[indx] = ((char) (tmp & 0x0000ff00)) >> 8;
    indx++;
    save_p[indx] = ((char) (tmp & 0x00ff0000)) >> 16;
    indx++;
    save_p[indx] = ((char) (tmp & 0xff000000)) >> 24;
    status = write_then_read_device(save_p, n_bytes);
    return status;
}

int solve_CRC(char *p_buf, int n_bytes) {
    int crc = 0;
    int counter;
    for (counter = 0; counter < n_bytes; counter++) {
        crc ^= p_buf[counter];
    }
    return crc;
}


//Возвращает 0x0 - корректные данные
//0x1 - нет ответа от устройства
//0x2 - не сошлась контрольная сумма,данные приняты некорректно
int write_then_read_device(char *buf_write, int size) {
    char *get_data;
    const int max_iteratior = 3;
    int counter;
    int crc;
    get_data = (char *) malloc(sizeof(char) * size);
    for (counter = 0; counter < max_iteratior; counter++) {
        write_word(buf_write, size);
        delay_ms(1000); // ждём 1 сек для получения ответа
        get_data = read_word(get_data, size); // читаем
        if (get_data[0] != 0x0) // пришли данные,разбор данных
        {

            int pr_crc = 0;
            int tmp = size;
            crc = solve_CRC(get_data, size);
            pr_crc = buf_write[tmp--] << 24;
            pr_crc |= buf_write[tmp--] << 16;
            pr_crc |= buf_write[tmp--] << 8;
            pr_crc |= buf_write[tmp];

            if (crc == pr_crc) // CRC совпало
            {
                return 0;  // корректные данные
            } else {
                return 0x2;    // данные не совпали
            }
        }
    }
    return 0x1;  // нет ответа от устройства
}

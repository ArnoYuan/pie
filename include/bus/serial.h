#ifndef __SERIAL_H__
#define __SERIAL_H__
#include <common/pie.h>

#ifdef __cplusplus
extern "C"{
#endif

#define MODULE_SERIAL(n)      MODULE_DEFINE(serial, n)
#define IMPORT_SERIAL(n)      IMPORT_MODULE(serial, n)
#define SERIAL(n)             MODULE(serial, n)


#define SERIAL_FLAG_IRQ_TX           0x01
#define SERIAL_FLAG_IRQ_RX           0x02
#define SERIAL_FLAG_DMA_TX           0x04
#define SERIAL_FLAG_DMA_RX           0x08
#define SERIAL_FLAG_INIT             0x10

#define SERIAL_EVENT_IRQ_TX           1
#define SERIAL_EVENT_IRQ_RX           2
#define SERIAL_EVENT_DMA_TX           3
#define SERIAL_EVENT_DMA_RX           4

#define SERIAL_RB_BUFSZ               100

#define SERIAL_CONFIG   {115200,SERIAL_DATABITS_8,SERIAL_STOPBITS_1,SERIAL_PARITY_NONE}

#define SERIAL_SET_CONFIG_DEFAULT(serial)                                  do {serial->config.baudrate = 115200;\
                                                                               serial->config.databits = SERIAL_DATABITS_8;\
                                                                               serial->config.stopbits = SERIAL_STOPBITS_1;\
                                                                               serial->config.parity = SERIAL_PARITY_NONE;\
                                                                           } while(0)
typedef enum{
    SERIAL_PARITY_NONE,
    SERIAL_PARITY_EVEN,
    SERIAL_PARITY_ODD,
}serial_parity_t;

typedef enum{
    SERIAL_DATABITS_7,
    SERIAL_DATABITS_8,
    SERIAL_DATABITS_9,
}serial_databits_t;

typedef enum{
    SERIAL_STOPBITS_1,
    SERIAL_STOPBITS_1_5,
    SERIAL_STOPBITS_2,
}serial_stopbits_t;


typedef struct serial_config {
    int baudrate;
    serial_databits_t databits;
    serial_stopbits_t stopbits;
    serial_parity_t parity;
} serial_config_t;

typedef struct serial_fifo {
    uint8_t *buffer;
    int put_index,get_index;
    int bufsz;
} serial_fifo_t;

typedef struct serial {
    uint8_t flags;
    const char* dev_name;
    list_t node;
    serial_config_t config;
    void *serial_rx;
    void *serial_tx;
    void *private_data;
    const struct serial_operations* ops;
} serial_t;

typedef struct serial_operations{
    int (*init)(serial_t* serial);
    int (*putc)(serial_t* serial, int ch);
    int (*getc)(serial_t* serial);
    int (*config)(serial_t* serial, int cmd, void* arg);
} serial_ops_t;

void serial_init(serial_t* serial, const serial_ops_t* ops);

int serial_write(serial_t* serial, const uint8_t* wr_data, size_t wr_len);

int serial_read(serial_t* serial, uint8_t* rd_data, size_t rd_len);

void serial_hw_isr(serial_t* serial, uint8_t event);

#ifdef __cplusplus
}
#endif
#endif
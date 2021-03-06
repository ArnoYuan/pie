/**
 * This is the difinition of i2c bit
 *
 * Author: Arno
 *
 * Created 2018/07/23
 */
#ifndef __I2C_BIT_H__
#define __I2C_BIT_H__

#ifdef __cplusplus
extern "C"{
#endif

#include <common/pie.h>
#include <bus/i2c.h>


typedef struct i2c_bit {
    i2c_t i2c;
	int delay_us;
	const struct i2c_bit_operations *ops;
} i2c_bit_t;

typedef struct i2c_bit_operations {
	int (*scl_set)(int state);
	int (*sda_set)(int state);
	int (*sda_get)(void);
    void (*enable_output)(void);
    void (*enable_input)(void);
	void (*udelay)(int us);
} i2c_bit_ops_t;

void i2c_bit_init(i2c_t* i2c, i2c_bit_t* i2c_bit);

#ifdef __cplusplus
}
#endif
#endif

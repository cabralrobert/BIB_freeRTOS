/*
 * I2C.h
 *
 *  Created on: 1 de mar de 2019
 *      Author: robertcabral
 */

#ifndef I2C_H_
#define I2C_H_

#include <fsl_i2c.h>

typedef enum mult_value_t
{
	MULT0 = 0,
	MULT1 = 1,
	MULT2 = 2,
	MULT4 = 4
} mult_value_t;

typedef enum icr_value_t
{
	ICR_0x00 = 0x00,
	ICR_0x07 = 0x07,
	ICR_0x0B = 0x0B,
	ICR_0x14 = 0x14,
	ICR_0x18 = 0x18
} icr_value_t;

typedef enum mode_direction_t
{
	TX,
	RX
} mode_direction_t;

typedef enum mode_transmition_t
{
	SLAVE,
	MASTER
} mode_transmition_t;

class I2C {
public:
	I2C(I2C_Type* base, uint8_t slaveAddress, mult_value_t mult = MULT0, icr_value_t icr = ICR_0x14);
	void start();
	void stop();
	void writeByte(uint8_t data);
	uint8_t readByte();
	status_t writeRegister(uint8_t registerAddress, uint8_t data);
	uint8_t readRegister(uint8_t registerAddress);
private:
	I2C_Type* base;
	mult_value_t mult;
	icr_value_t icr;
	uint8_t slaveAddress;
	void setMult(mult_value_t mult);
	void setICR(icr_value_t icr);
	void setACK(bool value);
	void repeatStart();
	void setDirection(mode_direction_t direction);
	void setMode(mode_transmition_t mode);
	void wait();
};

#endif /* I2C_H_ */

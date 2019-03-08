/*
 * I2C.cpp
 *
 *  Created on: 1 de mar de 2019
 *      Author: robertcabral
 */

#include <I2C.h>
#include <fsl_i2c.h>

I2C::I2C(I2C_Type* base, uint8_t slaveAddress, mult_value_t mult, icr_value_t icr) : mult(MULT0), icr(ICR_0x14) {

	this->slaveAddress = 0;
	this->base = base;
	this->slaveAddress = slaveAddress;

	if(this->base == I2C0)
		SIM->SCGC4 |= SIM_SCGC4_I2C0_MASK;
	else
		SIM->SCGC4 |= SIM_SCGC4_I2C1_MASK;


	SIM->SCGC5 |= SIM_SCGC5_PORTE_MASK;
	this->base->C1 = I2C_C1_IICEN_MASK;
	this->setMult(mult);
	this->setICR(icr);

	// Configuração de MUX no arquivo board/pin_mux.c

}

void I2C::setMult(mult_value_t mult){

	this->mult = mult;
	this->base->F |= I2C_F_MULT(mult);

}

void I2C::setICR(icr_value_t icr){

	this->icr = icr;
	this->base->F |= I2C_F_ICR(icr);

}

void I2C::setACK(bool value){

	if(!value)
		this->base->C1 |= I2C_C1_TXAK_MASK;
	else
		this->base->C1 &= ~(I2C_C1_TXAK_MASK);

}

void I2C::repeatStart(){

	this->base->C1 |= I2C_C1_RSTA_MASK;

}

void I2C::setDirection(mode_direction_t direction){

	switch (direction) {
		case RX:
			this->base->C1 &= ~(I2C_C1_TX_MASK);
			break;

		case TX:
			this->base->C1 |= I2C_C1_TX_MASK;
			break;

		default:
			break;
	}

}

void I2C::setMode(mode_transmition_t mode){

	switch (mode) {
		case SLAVE:
			this->base->C1 &= ~(I2C_C1_MST_MASK);
			break;

		case MASTER:
			this->base->C1 |= I2C_C1_MST_MASK;
			break;

		default:
			break;
	}

}

void I2C::start(){

	this->setMode(MASTER);
	this->setDirection(TX);

}

void I2C::stop(){

	this->setMode(SLAVE);
	this->setDirection(RX);

}

void I2C::wait(){

	while((this->base->S & I2C_S_IICIF_MASK) == 0);
	this->base->S |= I2C_S_IICIF_MASK;

}

void I2C::writeByte(uint8_t data){

	this->base->D = data;
	this->wait();

}

uint8_t I2C::readByte(){

	return this->base->D;

}

status_t I2C::writeRegister(uint8_t registerAddress, uint8_t data){

	// slaveAddress não especificado
	if(this->slaveAddress == 0)
		return (status_t) kStatus_Fail;

	this->start();
	this->writeByte((slaveAddress << 1) | TX);
	this->writeByte(registerAddress);
	this->writeByte(data);
	this->stop();

	return kStatus_Success;

}

uint8_t I2C::readRegister(uint8_t registerAddress){

	// slaveAddress não especificado
	if(this->slaveAddress == 0)
		return -1;

	this->start();
	this->writeByte((slaveAddress << 1) | TX);
	this->writeByte(registerAddress);

	this->repeatStart();

	this->writeByte((slaveAddress << 1) | RX);
	this->setDirection(RX);

	this->setACK(false);

	this->readByte();
	this->wait();
	this->stop();

	return(this->readByte());

}

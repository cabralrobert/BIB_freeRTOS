/*
 * GPIO.cpp
 *
 *  Created on: 1 de mar de 2019
 *      Author: robertcabral
 */

#include <GPIO.h>

GPIO::GPIO(GPIO_Type *base, uint32_t pin) {

	this->base = base;
	this->pin = pin;

}

void GPIO::setDirection(gpio_direction_t dir){
	switch (dir) {
			case INPUT:
				this->base->PDDR &= ~(1U << this->pin);
				break;

			case OUTPUT:
				this->base->PDDR |= (1U << this->pin);
				break;

			default:
				break;
		}
}

void GPIO::setValue(gpio_value_t value){
	switch (value) {
		case LOW:
			this->base->PCOR |= (1U << this->pin);
			break;

		case HIGH:
			this->base->PSOR |= (1U << this->pin);
			break;

		default:
			break;
	}
}

gpio_value_t GPIO::getValue(){
	return (gpio_value_t) ((this->base->PDIR >> this->pin) & 0b1);
}


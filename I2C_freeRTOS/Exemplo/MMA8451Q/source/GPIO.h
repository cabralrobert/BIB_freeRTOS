/*
 * GPIO.h
 *
 *  Created on: 1 de mar de 2019
 *      Author: robertcabral
 */

#ifndef GPIO_H_
#define GPIO_H_

#include <MKL25Z4.h>

typedef enum gpio_direction_t
{
	INPUT = 0,
	OUTPUT
} gpio_direction_t;

typedef enum gpio_value_t
{
	LOW = 0,
	HIGH
} gpio_value_t;

class GPIO {
public:
	GPIO(GPIO_Type *base, uint32_t pin);
	void setDirection(gpio_direction_t dir);
	void setValue(gpio_value_t value);
	gpio_value_t getValue();
private:
	uint32_t pin;
	GPIO_Type *base;
	uint8_t value;
};

#endif /* GPIO_H_ */

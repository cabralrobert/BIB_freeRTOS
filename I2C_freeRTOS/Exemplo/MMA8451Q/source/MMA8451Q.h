/*
 * Accelerometer.h
 *
 *  Created on: 7 de mar de 2019
 *      Author: robertcabral
 */

#ifndef MMA8451Q_H_
#define MMA8451Q_H_

#include <I2C.h>

#define MMA8451_I2C_ADDRESS 		(0x1D)
#define MMA8451_WHO_AM_I_REG		(0x0D)
#define CTRL_REG1 					(0x2A)
#define CTRL_REG2					(0x2B)
#define CTRL_REG3					(0x2C)
#define CTRL_REG4					(0x2D)
#define CTRL_REG5					(0x2E)

#define XYZ_DATA_CFG_REG 			(0x0E)

#define OUT_X_MSB					(0x01)
#define OUT_X_LSB					(0x02)

#define OUT_Y_MSB					(0x03)
#define OUT_Y_LSB					(0x04)

#define OUT_Z_MSB					(0x05)
#define OUT_Z_LSB					(0x06)

#define OFF_X						(0x2F)
#define OFF_Y						(0x30)
#define OFF_Z						(0x31)

#define CTRL_REG1_ACTIVE_MASK		(0x01)
#define CTRL_REG1_RESET				(0x00)

#define CTRL_REG1_ASPL_RATE_SHIFT	(0x6U)
#define CTRL_REG1_ASPL_RATE_RESET	(0x3F)

#define XYZ_DATA_CFG_HPF_OUT_MASK	(0x10)

#define XYZ_DATA_CFG_RANGE_SHIFT	(0x00)
#define XYZ_DATA_CFG_RANGE_RESET	(0x03)

#define CTRL_REG2_MODS_RESET		(0x03)
#define CTRL_REG2_MODS_SHIFT		(0x00)

#define MMA8451Q_SENSITIVITY_2G		(0x02)

#define CTRL_REG3_PP_OD_MASK		(0x00)

#define CTRL_REG4_INT_EN_DRDY_MASK	(0x01)

#define CTRL_REG5_INT_CFG_DRDY_MASK	(0x01)

typedef enum mma8451q_frequency_t
{
	MMA8451Q_FREQUENCY_50Hz 	= 0x0,
	MMA8451Q_FREQUENCY_12_5Hz 	= 0x1,
	MMA8451Q_FREQUENCY_6_25Hz 	= 0x2,
	MMA8451Q_FREQUENCY_1_56Hz 	= 0x3
} mma8451q_frequency_t;

typedef enum mma8451q_range_t
{
	MMA8451Q_RANGE_2G 			= 0x0,
	MMA8451Q_RANGE_4G 			= 0x1,
	MMA8451Q_RANGE_8G 			= 0x2
} mma8451q_range_t;

typedef enum mma8451q_power_t
{
	MMA8451Q_POWER_NORMAL				= 0x0,
	MMA8451Q_POWER_LOW_NOISE_LOW_POWER 	= 0x1,
	MMA8451Q_POWER_HIGH_RESOLUTION 		= 0x2,
	MMA8451Q_POWER_LOW_POWER			= 0x3
} mma8451q_power_t;

class MMA8451Q {
public:
	MMA8451Q(mma8451q_frequency_t freq = MMA8451Q_FREQUENCY_1_56Hz, mma8451q_range_t range = MMA8451Q_RANGE_2G, mma8451q_power_t power = MMA8451Q_POWER_HIGH_RESOLUTION);
	void setFilter();
	uint16_t getX();
	uint16_t getY();
	uint16_t getZ();
	void calibrate();

private:
	I2C i2c;
	mma8451q_frequency_t freq;
	mma8451q_range_t range;
	mma8451q_power_t power;
};

#endif /* MMA8451Q_H_ */

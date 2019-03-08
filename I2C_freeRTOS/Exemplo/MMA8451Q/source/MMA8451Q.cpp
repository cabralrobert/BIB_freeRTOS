#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL25Z4.h"
#include "fsl_debug_console.h"
#include <fsl_i2c.h>
#include <fsl_i2c_freertos.h>
#include <GPIO.h>
#include <I2C.h>
#include <MMA8451Q.h>
#include <task.h>


xTaskHandle task1_handle = NULL;
xTaskHandle task2_handle = NULL;
xTaskHandle task3_handle = NULL;


void readX(void *parameters){
	MMA8451Q mma8541q;
	uint16_t x = 0;
	GPIO ledRed(GPIOB, 18U);
	ledRed.setDirection(OUTPUT);
	mma8541q.setFilter();
	mma8541q.calibrate();

	while(1) {
		x = mma8541q.getX();

		if(x < 32767)
			ledRed.setValue(LOW);
		else
			ledRed.setValue(HIGH);

		vTaskResume(task2_handle);
		vTaskSuspend(task1_handle);
	}
}

void readY(void *parameters){
	MMA8451Q mma8541q;
	uint16_t y = 0;
	GPIO ledGreen(GPIOB, 19U);
	ledGreen.setDirection(OUTPUT);
	mma8541q.setFilter();
	mma8541q.calibrate();

	while(1) {
		y = mma8541q.getY();

		if(y < 32767)
			ledGreen.setValue(LOW);
		else
			ledGreen.setValue(HIGH);

		vTaskResume(task3_handle);
		vTaskSuspend(task2_handle);
	}
}

void readZ(void *parameters){
	MMA8451Q mma8541q;
	uint16_t z = 0;
	GPIO ledBlue(GPIOD, 1U);
	ledBlue.setDirection(OUTPUT);
	mma8541q.setFilter();
	mma8541q.calibrate();

	while(1) {
		z = mma8541q.getZ();

		if(z < 32767)
			ledBlue.setValue(LOW);
		else
			ledBlue.setValue(HIGH);

		vTaskResume(task1_handle);
		vTaskSuspend(task3_handle);
	}
}

int main(void) {

	BOARD_InitBootPins();
	BOARD_InitBootClocks();
	BOARD_InitBootPeripherals();
	BOARD_InitDebugConsole();

	xTaskCreate(readX, "X", configMINIMAL_STACK_SIZE, NULL, 1, &task1_handle);
	xTaskCreate(readY, "Y", configMINIMAL_STACK_SIZE, NULL, 1, &task2_handle);
	xTaskCreate(readZ, "Z", configMINIMAL_STACK_SIZE, NULL, 1, &task3_handle);

	vTaskStartScheduler();

	return 0 ;
}

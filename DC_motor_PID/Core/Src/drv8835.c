/*
 * drv8835.c
 *
 *  Created on: Jan 2, 2025
 *      Author: Szymkecz
 */

#include "main.h"
#include "drv8835.h"

void drv8835_init() {
	drv8835_mode_control(Phase_Enable_Mode);
	drv8835_set_motorA_direction(CCW);
	drv8835_set_motorA_speed(0);

	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_3);
}

void drv8835_mode_control(DRV8835_Mode mode) {
	if (mode == Phase_Enable_Mode)
		HAL_GPIO_WritePin(MODE_GPIO_Port, MODE_Pin, SET);
	else if (mode == In_In_Mode)
		HAL_GPIO_WritePin(MODE_GPIO_Port, MODE_Pin, RESET);
}

void drv8835_set_motorA_direction(DRV8835_Direction dir) {
	if (dir == CW)
		HAL_GPIO_WritePin(APHASE_GPIO_Port, APHASE_Pin, SET);
	else if (dir == CCW)
		HAL_GPIO_WritePin(APHASE_GPIO_Port, APHASE_Pin, RESET);
}

void drv8835_set_motorA_speed(uint16_t speed)
{
	if(speed >= htim2.Instance->ARR)
		speed = htim2.Instance->ARR;

	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_3, speed);
}


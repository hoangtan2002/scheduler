/*
 * led.c
 *
 *  Created on: Nov 13, 2022
 *      Author: tan
 */

#include "led.h"


void ledInit(){
	HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, OFF);
	HAL_GPIO_WritePin(LED_YELLOW_GPIO_Port, LED_YELLOW_Pin, OFF);
	HAL_GPIO_WritePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin, OFF);
	HAL_GPIO_WritePin(LED_BLUE_GPIO_Port, LED_BLUE_Pin, OFF);
	HAL_GPIO_WritePin(LED_WHITE_GPIO_Port, LED_WHITE_Pin, OFF);
}

void blinkLedRed(){
	HAL_GPIO_TogglePin(LED_RED_GPIO_Port, LED_RED_Pin);
}
void blinkLedYellow(){
	HAL_GPIO_TogglePin(LED_YELLOW_GPIO_Port, LED_YELLOW_Pin);
}
void blinkLedGreen(){
	HAL_GPIO_TogglePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin);
}
void blinkLedBlue(){
	HAL_GPIO_TogglePin(LED_BLUE_GPIO_Port, LED_BLUE_Pin);
}
void blinkLedWhite(){
	HAL_GPIO_TogglePin(LED_WHITE_GPIO_Port, LED_WHITE_Pin);

}


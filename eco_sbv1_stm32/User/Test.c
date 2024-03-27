/*
 * Test.c
 *
 *  Created on: Aug 15, 2023
 *      Author: v.taranov
 */


#include "Test.h"


static void enable_USB_ext(void)
{
	HAL_GPIO_WritePin(STM_GPIO1_GPIO_Port, STM_GPIO1_Pin, GPIO_PIN_SET);
}


static void enable_LTE(void)
{
	HAL_GPIO_WritePin(LTE_EN_GPIO_Port, LTE_EN_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GNSS_ANT_PWR_GPIO_Port, GNSS_ANT_PWR_Pin, GPIO_PIN_SET);
}


static void enable_ESP32(void)
{
	HAL_GPIO_WritePin(ESP32_EN_GPIO_Port, ESP32_EN_Pin, GPIO_PIN_SET);
}


static void enable_AI(void)
{
	HAL_GPIO_WritePin(AI_EN_GPIO_Port, AI_EN_Pin, GPIO_PIN_SET);
}

static void enable_CPU(void)
{
	HAL_GPIO_WritePin(CPU_RES_GPIO_Port, CPU_RES_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(CPU_EN_GPIO_Port, CPU_EN_Pin, GPIO_PIN_SET);
	HAL_Delay(200);
	HAL_GPIO_WritePin(CPU_RES_GPIO_Port, CPU_RES_Pin, GPIO_PIN_SET);
}

static void enable_SAUND_D1(void)
{
	HAL_GPIO_WritePin(A_S0_GPIO_Port, A_S0_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(A_S1_GPIO_Port, A_S1_Pin, GPIO_PIN_SET);
}


void v_test_init(void)
{
	enable_CPU();
	enable_USB_ext();
	enable_LTE();
	enable_ESP32();
	enable_AI();
	enable_SAUND_D1();
}

/*
 * motorprogram.c
 *
 *  Created on: Mar 20, 2024
 *      Author: Magic
 */

#include "motorconfig.h"
#include "motorinterface.h"
#include "main.h"


void Motor_ForWard()
{
	/*pin back word  2 motor should be low (first) */
	HAL_GPIO_WritePin(GPIO_PORT_Motion, GPIO_PIN_Right_BackWord, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIO_PORT_Motion, GPIO_PIN_Left_BackWord, GPIO_PIN_RESET);

	/*pin for word 2 motor should be high*/
	HAL_GPIO_WritePin(GPIO_PORT_Motion,GPIO_PIN_Left_ForWard , GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIO_PORT_Motion, GPIO_PIN_Right_ForWard, GPIO_PIN_SET);

}

void Motor_BackWard()
{
	/*pin for word  2 motor should be low (first) */

	HAL_GPIO_WritePin(GPIO_PORT_Motion,GPIO_PIN_Left_ForWard , GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIO_PORT_Motion, GPIO_PIN_Right_ForWard,GPIO_PIN_RESET );

	/*pin back word 2 motor should be high*/

	HAL_GPIO_WritePin(GPIO_PORT_Motion, GPIO_PIN_Right_BackWord,GPIO_PIN_SET );
	HAL_GPIO_WritePin(GPIO_PORT_Motion, GPIO_PIN_Left_BackWord, GPIO_PIN_SET );
}
void Motor_Right()
{

	/*pin right forward low  and right back word and left back word*/
	HAL_GPIO_WritePin(GPIO_PORT_Motion, GPIO_PIN_Right_ForWard,GPIO_PIN_RESET );
	HAL_GPIO_WritePin(GPIO_PORT_Motion, GPIO_PIN_Right_BackWord,GPIO_PIN_RESET );
	HAL_GPIO_WritePin(GPIO_PORT_Motion, GPIO_PIN_Left_BackWord, GPIO_PIN_RESET );

	/*pin left forward high*/

	HAL_GPIO_WritePin(GPIO_PORT_Motion,GPIO_PIN_Left_ForWard , GPIO_PIN_SET);
}
void Motor_Left()
{
	/*pin lift forward low  and lift back word and right back word*/

	HAL_GPIO_WritePin(GPIO_PORT_Motion,GPIO_PIN_Left_ForWard , GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIO_PORT_Motion, GPIO_PIN_Right_BackWord,GPIO_PIN_RESET );
	HAL_GPIO_WritePin(GPIO_PORT_Motion, GPIO_PIN_Left_BackWord, GPIO_PIN_RESET );

	/*pin right forward high*/
	HAL_GPIO_WritePin(GPIO_PORT_Motion, GPIO_PIN_Right_ForWard,GPIO_PIN_SET );

}
void Motor_Stop()
{
	HAL_GPIO_WritePin(GPIO_PORT_Motion,GPIO_PIN_Left_ForWard , GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIO_PORT_Motion, GPIO_PIN_Right_BackWord,GPIO_PIN_RESET );
	HAL_GPIO_WritePin(GPIO_PORT_Motion, GPIO_PIN_Left_BackWord, GPIO_PIN_RESET );
	HAL_GPIO_WritePin(GPIO_PORT_Motion, GPIO_PIN_Right_ForWard,GPIO_PIN_RESET );

}



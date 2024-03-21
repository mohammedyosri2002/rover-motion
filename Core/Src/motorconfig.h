/*
 * motorconfig.h
 *
 *  Created on: Mar 20, 2024
 *      Author: Magic
 */

#ifndef SRC_MOTORCONFIG_H_
#define SRC_MOTORCONFIG_H_
#include "main.h"

#define Stop                            '0'
#define ForWard                         '1'
#define BackWord                        '2'
#define Right                           '3'
#define Left                            '4'

#define Wating                          '7'

#define  Very_low                       '1'
#define  low                            '2'
#define  High                           '3'
#define  Very_High                      '4'

#define GPIO_PORT_Motion                GPIOA
#define GPIO_PIN_Right_ForWard         GPIO_PIN_4
#define GPIO_PIN_Left_ForWard          GPIO_PIN_3
#define GPIO_PIN_Right_BackWord        GPIO_PIN_6
#define GPIO_PIN_Left_BackWord         GPIO_PIN_5








#endif /* SRC_MOTORCONFIG_H_ */

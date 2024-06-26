/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2024 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "motorinterface.h"
#include "motorconfig.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
TIM_HandleTypeDef htim2;

UART_HandleTypeDef huart1;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_TIM2_Init(void);
static void MX_USART1_UART_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
uint8_t receivedData[1];
uint8_t receivedData2[1];
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
 * @brief  The application entry point.
 * @retval int
 */
int main(void)
{
	/* USER CODE BEGIN 1 */

	/* USER CODE END 1 */

	/* MCU Configuration--------------------------------------------------------*/

	/* Reset of all peripherals, Initializes the Flash interface and the Systick. */
	HAL_Init();

	/* USER CODE BEGIN Init */

	/* USER CODE END Init */

	/* Configure the system clock */
	SystemClock_Config();

	/* USER CODE BEGIN SysInit */

	/* USER CODE END SysInit */

	/* Initialize all configured peripherals */
	MX_GPIO_Init();
	MX_TIM2_Init();
	MX_USART1_UART_Init();
	/* USER CODE BEGIN 2 */

	HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_1 );
	HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_2 );
	/* USER CODE END 2 */
	/* Infinite loop */
	/* USER CODE BEGIN WHILE */
	while (1)
	{
		/* USER CODE END WHILE */
		receivedData[0]= Wating ;
		receivedData2[0]= Wating ;
		HAL_UART_Transmit(&huart1, "mode(0stop-1forward-2backword-3right-4lift)", 43, 100);
		while(receivedData[0]==Wating){
			HAL_UART_Receive(&huart1, receivedData, 1, 100);
		}
		HAL_UART_Transmit(&huart1, "speed(0-1-2-3-4)", 43, 100);
		while(receivedData2[0]==Wating){
			HAL_UART_Receive(&huart1, receivedData2, 1, 100);
		}
		switch (receivedData[0]){
		case Stop     :   Motor_Stop(); break;
		case ForWard  :   Motor_ForWard();Motor_Speed_Linear();break;
		case BackWord :   Motor_BackWard();Motor_Speed_Linear();break;
		case Right    :   Motor_ForWard(); Motor_Speed_Angular_Right(); break;
		case Left     :   Motor_ForWard();Motor_Speed_Angular_Left();break;
		default:;break;
		}

	}
	/*  HAL_UART_Receive(&huart1, receivedData, 1, 100);
		      if (receivedData[0] == '0'){
		        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, 0);
		        HAL_UART_Transmit(&huart1, "of", 2, 100);
		      } else if (receivedData[0] == '1'){
		        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, 1);
		        HAL_UART_Transmit(&huart1, "on", 2, 100);
		      }*/

	/* USER CODE BEGIN 3 */
}
/* USER CODE END 3 */


/**
 * @brief System Clock Configuration
 * @retval None
 */
void SystemClock_Config(void)
{
	RCC_OscInitTypeDef RCC_OscInitStruct = {0};
	RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

	/** Initializes the RCC Oscillators according to the specified parameters
	 * in the RCC_OscInitTypeDef structure.
	 */
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
	RCC_OscInitStruct.HSIState = RCC_HSI_ON;
	RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
	{
		Error_Handler();
	}

	/** Initializes the CPU, AHB and APB buses clocks
	 */
	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
			|RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
	{
		Error_Handler();
	}
}
void Motor_Linear_Spead_Very_Low()
{

	__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_2,16339);
	__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_1,16339);
}
void Motor_Linear_Spead_Low()
{
	__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_1,32677);
	__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_2,32677);
}
void Motor_Linear_Spead_High()
{
	__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_1,49015);
	__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_2,49015);
}
void Motor_Linear_Spead_Very_High()
{
	__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_1,49015);
	__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_2,49015);
}

void Motor_Speed_Linear()
{
	switch(receivedData2[0]){
	case Stop          :  Motor_Stop();break;
	case Very_low      :  Motor_Linear_Spead_Very_Low();break;
	case low           :  Motor_Linear_Spead_Low();break;
	case High          :  Motor_Linear_Spead_High();break;
	case Very_High     :  Motor_Linear_Spead_Very_High();break;
	}

}
void Motor_Angular_Spead_Right_Very_Low()
{

	__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_2,65535);
	__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_1,49015);
}
void Motor_Angular_Spead_Right_Low()
{
	__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_1,32677);
	__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_2,65535);
}
void Motor_Angular_Spead_Right_High()
{
	__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_1,16339);
	__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_2,65535);
}
void Motor_Angular_Spead_Right_Very_High()
{
	__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_1,0);
	__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_2,65535);
}
void Motor_Speed_Angular_Right()
{
	switch(receivedData2[0]){
	case Stop          :  Motor_Stop();break;
	case Very_low      :  Motor_Angular_Spead_Right_Very_Low();break;
	case low           :  Motor_Angular_Spead_Right_Low();break;
	case High          :  Motor_Angular_Spead_Right_High();break;
	case Very_High     :  Motor_Angular_Spead_Right_Very_High();break;
	}

}
void Motor_Angular_Spead_Left_Very_Low()
{

	__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_1,65535);
	__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_2,49015);
}
void Motor_Angular_Spead_Left_Low()
{
	__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_2,32677);
	__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_1,65535);
}
void Motor_Angular_Spead_Left_High()
{
	__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_2,16339);
	__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_1,65535);
}
void Motor_Angular_Spead_Left_Very_High()
{
	__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_2,0);
	__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_1,65535);
}
void Motor_Speed_Angular_Left()
{
	switch(receivedData2[0]){
	case Stop          :  Motor_Stop();break;
	case Very_low      :  Motor_Angular_Spead_Left_Very_Low();break;
	case low           :  Motor_Angular_Spead_Left_Low();break;
	case High          :  Motor_Angular_Spead_Left_High();break;
	case Very_High     :  Motor_Angular_Spead_Left_Very_High();break;
	}

}
/**
 * @brief TIM2 Initialization Function
 * @param None
 * @retval None
 */
static void MX_TIM2_Init(void)
{

	/* USER CODE BEGIN TIM2_Init 0 */

	/* USER CODE END TIM2_Init 0 */

	TIM_ClockConfigTypeDef sClockSourceConfig = {0};
	TIM_MasterConfigTypeDef sMasterConfig = {0};
	TIM_OC_InitTypeDef sConfigOC = {0};

	/* USER CODE BEGIN TIM2_Init 1 */

	/* USER CODE END TIM2_Init 1 */
	htim2.Instance = TIM2;
	htim2.Init.Prescaler = 0;
	htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
	htim2.Init.Period = 65535;
	htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
	if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
	{
		Error_Handler();
	}
	sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
	if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
	{
		Error_Handler();
	}
	if (HAL_TIM_PWM_Init(&htim2) != HAL_OK)
	{
		Error_Handler();
	}
	sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
	sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
	if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
	{
		Error_Handler();
	}
	sConfigOC.OCMode = TIM_OCMODE_PWM1;
	sConfigOC.Pulse = 0;
	sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
	sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
	if (HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
	{
		Error_Handler();
	}
	if (HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_2) != HAL_OK)
	{
		Error_Handler();
	}
	/* USER CODE BEGIN TIM2_Init 2 */

	/* USER CODE END TIM2_Init 2 */
	HAL_TIM_MspPostInit(&htim2);

}

/**
 * @brief USART1 Initialization Function
 * @param None
 * @retval None
 */
static void MX_USART1_UART_Init(void)
{

	/* USER CODE BEGIN USART1_Init 0 */

	/* USER CODE END USART1_Init 0 */

	/* USER CODE BEGIN USART1_Init 1 */

	/* USER CODE END USART1_Init 1 */
	huart1.Instance = USART1;
	huart1.Init.BaudRate = 9600;
	huart1.Init.WordLength = UART_WORDLENGTH_8B;
	huart1.Init.StopBits = UART_STOPBITS_1;
	huart1.Init.Parity = UART_PARITY_NONE;
	huart1.Init.Mode = UART_MODE_TX_RX;
	huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart1.Init.OverSampling = UART_OVERSAMPLING_16;
	if (HAL_UART_Init(&huart1) != HAL_OK)
	{
		Error_Handler();
	}
	/* USER CODE BEGIN USART1_Init 2 */

	/* USER CODE END USART1_Init 2 */

}

/**
 * @brief GPIO Initialization Function
 * @param None
 * @retval None
 */
static void MX_GPIO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	/* USER CODE BEGIN MX_GPIO_Init_1 */
	/* USER CODE END MX_GPIO_Init_1 */

	/* GPIO Ports Clock Enable */
	__HAL_RCC_GPIOD_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6, GPIO_PIN_RESET);

	/*Configure GPIO pins : PA3 PA4 PA5 PA6 */
	GPIO_InitStruct.Pin = GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	/* USER CODE BEGIN MX_GPIO_Init_2 */
	/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */
void Error_Handler(void)
{
	/* USER CODE BEGIN Error_Handler_Debug */
	/* User can add his own implementation to report the HAL error return state */
	__disable_irq();
	while (1)
	{
	}
	/* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
 * @brief  Reports the name of the source file and the source line number
 *         where the assert_param error has occurred.
 * @param  file: pointer to the source file name
 * @param  line: assert_param error line source number
 * @retval None
 */
void assert_failed(uint8_t *file, uint32_t line)
{
	/* USER CODE BEGIN 6 */
	/* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
	/* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

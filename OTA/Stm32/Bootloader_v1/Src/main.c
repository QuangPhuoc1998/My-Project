/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
#define GLOBAL_DEFINE 1
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stm32f769i_discovery.h"
#include "sys_timer.h"
#include "App_Bootloader.h"
#include "Mid_PCubeProtocol.h"
#include "Mid_FlashControl.h"
#include "Op_HeaderFlag.h"
#include "Op_HeaderFunction.h"
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

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void ProcessMain(void);
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
  MX_USART1_UART_Init();
  /* USER CODE BEGIN 2 */
	BSP_LED_Init(LED_GREEN);
	BSP_LED_Init(LED_RED);
	BSP_PB_Init(BUTTON_WAKEUP, BUTTON_MODE_GPIO);
	App_BootloaderInit();
	
	if(BSP_PB_GetState(BUTTON_WAKEUP) == 1)
	{
		// do nothing
	}
	else
	{
		App_BootloaderJumpToUserApp();
	}

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
		SysTimerLoop();
		ProcessMain();
  }
  /* USER CODE END 3 */
}
void ProcessMain(void)
{
	/*--- Process PCUBE ---*/
	Mid_PCubeProcess();
	/*--- Process Flash ---*/
	Mid_FlashEraseProcess();
	Mid_FlashWriteProcess();
	Mid_FlashReadProcess();
	
}
void SysTimer1msEvent(void)
{
	/*--- Watch dog for PCUBE receive ---*/
	if(g_ubRxWatchDogCnt > 0)
	{
		g_ubRxWatchDogCnt--;
	}
	else
	{
		g_ubRxIndexCount = 0;
	}
}
void SysTimer10msEvent(void)
{
	/*--- Check write data UART ---*/
	if(PCUBE_WRITE_START == C_ON && PCUBE_WRITE_DONE == C_OFF)
	{
		HAL_UART_Transmit_IT(&huart1, &g_aubTxRealData[0], 1);
		PCUBE_WRITE_START = C_OFF;
		PCUBE_WRITE_DONE  = C_ON;
	}
}
void SysTimer20msEvent(void)
{
	
}
void SysTimer50msEvent(void)
{
	
}
void SysTimer100msEvent(void)
{
	
}
void SysTimer500msEvent(void)
{
	
}
void SysTimer1000msEvent(void)
{
	BSP_LED_Toggle(LED_RED);
	/*--- Reset Cnt ---*/
	if(OP_RESET_FLAG ==  C_ON)
	{
		if(g_ubResetCnt > 0)
		{
			g_ubResetCnt--;
		}
		else
		{
			NVIC_SystemReset();
		}
	}
}
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
	static uint8_t ubTxIndex = 1;
	if(huart->Instance == USART1)
	{
		if(PCUBE_WRITE_DONE == C_ON)
		{
			HAL_UART_Transmit_IT(&huart1, &g_aubTxRealData[ubTxIndex], 1);
			ubTxIndex++;
			if(ubTxIndex == g_ubTxRealLen)
			{
				PCUBE_WRITE_DONE = C_OFF;
				ubTxIndex = 1;
			}
		}
	}
}
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	uint8_t ub_ETXIndex = 0;
	if(huart->Instance == USART1)
	{
		g_ubRxWatchDogCnt = TIME_10MS_BY_1MS;
		/*---*/
		if(g_ubRxIndexCount < PCUBE_HEADER_COUNT)
		{
			g_aubRxData[g_ubRxIndexCount] = g_ubRxDataBuffer;
			if(g_ubRxIndexCount == PCUBE_STX_INDEX)
			{
				if(g_aubRxData[g_ubRxIndexCount] != PCUBE_STX_DATA)
				{
					g_ubRxIndexCount = 0;
				}
				else
				{
					g_ubRxIndexCount++;
				}
			}
			else
			{
				g_ubRxIndexCount++;
			}
		}
		else if(g_ubRxIndexCount < (g_aubRxData[PCUBE_LEN_INDEX] + 2))
		{
			g_aubRxData[g_ubRxIndexCount] = g_ubRxDataBuffer;
			ub_ETXIndex = g_aubRxData[PCUBE_LEN_INDEX] + 2 - 1;
			if(g_ubRxIndexCount == ub_ETXIndex)
			{
				if(g_aubRxData[g_ubRxIndexCount] == PCUBE_ETX_DATA)
				{
					// pass
					g_ubRxRealLen = g_ubRxIndexCount+1;
					Ex_CopyArray(g_aubRxData, g_aubRxRealData, g_ubRxRealLen);
					PCUBE_RECEIVE_DONE_FLAG = C_ON;
					//
				}
				g_ubRxIndexCount = 0;
			}
			else
			{
				g_ubRxIndexCount++;
			}
		}
		else
		{
			g_ubRxIndexCount = 0;
		}
		/*---*/
		HAL_UART_Receive_IT(&huart1, &g_ubRxDataBuffer, 1);
  }
}
/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 25;
  RCC_OscInitStruct.PLL.PLLN = 432;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 2;
  RCC_OscInitStruct.PLL.PLLR = 2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Activate the Over-Drive mode
  */
  if (HAL_PWREx_EnableOverDrive() != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_7) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_USART1;
  PeriphClkInitStruct.Usart1ClockSelection = RCC_USART1CLKSOURCE_PCLK2;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
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

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

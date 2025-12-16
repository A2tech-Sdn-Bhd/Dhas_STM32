/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  *
  *
       ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⣤⣤⠶⠶⠶⠶⠤⠤⠤⣄⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
        ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣠⠔⠊⠉⠉⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠙⠛⠷⣦⣄⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
        ⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⡴⢶⣾⠋⢉⣉⣉⣛⣛⣍⣽⣄⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠙⠷⣤⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
        ⠀⠀⠀⠀⠀⠀⠀⠀⢀⣼⠴⠋⢀⡔⠉⠀⠀⣀⣠⣤⣤⣵⣼⣀⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠙⢦⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
        ⠀⠀⠀⠀⠀⠀⠀⣴⣏⡥⠔⠊⠉⣀⣤⠞⠉⠀⠀⠀⠀⠀⠈⡇⣨⠆⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⢿⣿⠿⠟⠛⠛⢿⣶⡶⣦⣤⣄⣀⠀⠀⠀⠀
        ⠀⠀⢀⠶⠒⠋⣹⠟⢉⣀⠤⠖⠛⠉⠀⢀⣠⠴⠚⠉⠉⠉⠉⠉⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢶⣦⡀⠀⠀⠀⠉⠁⠀⠀⠀⠉⠙⠻⣶⣄⠀
        ⠀⡴⠿⠒⠒⡾⠀⢠⠾⠁⠀⣀⡀⠀⣴⡋⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⠈⣿⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⢿⣇
        ⠘⠇⠀⢀⡞⠀⠀⠀⠀⢠⡾⠋⠀⠀⠈⠉⠉⠉⠉⠉⠉⠉⠉⠉⠻⠉⣻⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣹⣿⣿⡭⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣸⡏
        ⠀⠀⢠⠞⠀⠀⠀⠀⠀⠈⠀⠀⠀⠀⣀⣠⣤⠤⠤⠤⠤⠤⠤⠤⠔⠚⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⣤⣾⣿⣿⣿⡟⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢠⡿⠁
        ⠀⣰⠃⠀⠀⠀⠀⠀⠀⠀⠀⠀⣰⣿⣿⣿⣿⣶⣿⣧⣾⣤⣀⣀⣀⣰⡄⠀⢀⣀⣶⣤⣤⣾⣿⣿⣿⣿⣿⣿⣿⣿⡿⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣴⡟⠁⠀
        ⠐⠋⠀⠀⠀⠀⠀⠀⠀⠀⢀⣼⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠟⠉⠁⠀⠀⠀⠀⠀⠀⠀⠀⣀⠀⣀⣴⠟⠋⠀⠀⠀
        ⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣾⣿⠟⠋⠉⠉⠛⠿⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⠟⠋⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡀⣀⣼⠿⠋⠁⠀⠀⠀⠀⠀
        ⠀⠀⠀⠀⠀⠀⠀⠀⠀⣾⡿⠁⠀⠀⠀⠀⠀⠀⠈⠋⠙⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠋⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⢀⣠⣤⣶⡟⠋⠀⠀⠀⠀⠀⠀⠀⠀⠀
        ⠀⠀⠀⠀⠀⠀⣀⣴⠾⣏⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣠⣿⣿⣿⣿⣿⣷⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀
        ⠀⠀⠀⣠⠴⠋⠁⠀⠀⣿⣿⣦⣀⡄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣀⣀⣤⣶⣿⣿⣿⣿⣿⣿⣿⡿⢿⣆⠀⠀⠀⠀⠀⠀⠀⠀
        ⠀⠀⡼⠃⠀⠀⠀⠀⢰⣿⣿⣿⣿⣿⣶⣤⣤⣤⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⣀⣤⣴⣾⠟⠉⣿⣿⣿⣿⣿⣿⣿⡿⠿⣿⣧⠀⠻⠀⠀⠀⠀⠀⠀⠀⠀
        ⠀⠜⠁⠀⠀⠀⠀⠀⢸⡏⢸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⣶⣿⣶⣿⣿⣿⣿⣿⣿⣿⣏⡁⠉⠋⢁⣠⡾⠿⠛⣿⣿⡇⢹⣿⣿⣶⣌⠙⠇⠀⠀⠀⠀⠀⠀⠀⠀⠀
        ⠀⠀⠀⠀⠀⠀⠀⠀⢸⡇⢸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠟⠛⠻⢿⣯⡉⠉⠉⣅⣰⣶⠂⢠⣿⡟⢀⣾⣿⣆⠀⠉⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
        ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠁⠀⠻⠈⢿⣿⣿⣿⣏⠉⠉⠉⠉⠉⠉⢹⣿⣇⠀⠀⠀⠀⠀⠈⠀⠐⠋⠓⠀⠀⣼⣋⣴⡇⠀⠈⠉⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
        ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠙⠿⣧⡉⠀⠀⠀⠀⠀⠀⠘⣿⣿⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣸⣿⠋⠛⠇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
        ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢻⣄⠀⠀⠀⠀⠀⠀⠙⠛⠃⠀⠀⠀⠀⠀⠀⠀⠀⢀⠜⠉⠛⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
        ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠸⠿⣷⣄⠀⠀⠐⠒⠒⠒⠒⠒⠒⠒⠒⠀⠀⠀⣠⠂⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
        ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢹⠘⣷⣤⡀⠀⠀⠘⠛⠛⠂⠀⠀⠀⣠⡾⣿⡄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
        ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⠀⠘⣿⣿⣷⣦⣄⡀⠀⠀⣀⣴⣿⣿⠰⣿⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
        ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣀⣀⣀⣀⣀⠀⣀⡘⠀⠀⠸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠃⠀⢻⡀⠀⢀⣀⣀⣠⣤⣤⣄⣀⣀⣀⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
        ⠀⠀⠀⠀⠀⠀⠀⠀⢀⡾⠋⠉⠁⠀⠀⠈⠉⠉⢹⠇⠀⠀⠀⢹⣿⣿⣿⣿⣿⣿⣿⣿⡟⠀⠀⠘⢿⡛⠉⠉⠁⠀⠀⠀⠀⠀⠉⠙⢿⣦⡀⠀⠀⠀⠀⠀⠀⠀⠀
        ⠀⠀⠀⠀⠀⠀⠀⢠⣾⠀⠀⠀⠀⣀⣤⣴⣶⠾⠏⠀⠀⢣⠀⠀⢻⣿⣿⣿⡿⠋⢹⣿⠇⠀⠀⠀⠀⠙⢆⣀⣤⣤⣄⣀⡀⠀⠀⠀⠀⠙⢷⡄⠀⠀⠀⠀⠀⠀⠀
        ⠀⠀⠀⠀⠀⠀⠀⠉⠀⠀⠀⢀⡾⠛⠛⠻⣏⠀⠀⠀⠀⢸⣇⠀⠀⢿⣿⡛⠁⠀⣾⡿⠀⣠⠀⠀⠀⠀⠀⠙⣿⣿⣿⣿⣿⣷⡄⠀⠀⠀⠀⠙⠀⠀⠀⠀⠀⠀⠀
        ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡼⠁⠀⠀⠀⢹⣆⠀⠀⠀⢸⣿⡄⠀⠈⣿⡇⠀⢠⣿⠇⢰⡏⠀⠀⠀⠀⠀⣰⠇⠀⠀⠉⠉⠛⢿⡄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
        ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣷⠶⠶⠶⠶⠶⠿⣷⣤⣀⣸⣿⣷⠀⠀⠘⣷⠀⠘⠋⢀⣿⠁⣠⣶⠖⠚⢿⡿⠛⠛⠛⠛⠛⠛⠛⣿⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
        ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡇⠀⠀⠀⠀⠀⠀⠙⠃⠀⠉⠛⢿⡆⠀⠀⠸⣆⠀⣠⣾⠏⠸⠋⠁⠀⢀⡾⠀⠀⠀⠀⠀⠀⠀⠀⣿⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
        ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠹⠀⠀⠀⠙⠛⠛⠛⠀⠀⠀⠀⠀⠚⠁⠀⠀⠀⠀⠀⠀⠀⠀⣿⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
        ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠏⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀





  ******************************************************************************
  */

#include "main.h"


int main(void)
{


  HAL_Init();


  SystemClock_Config();


  MX_GPIO_Init();
  MX_TIM2_Init();
  MX_TIM3_Init();
  MX_TIM4_Init();
  MX_CAN2_Init();
  RC_intialize();
  watchdoginit(400,8);




  Freertos_start();


}


void StartmicrorosTask(void *argument)
{
//  MX_USB_DEVICE_Init();
//  microros_createnode();
//  microros_createsubscribers();
//  microros_createpublishers();


  for(;;)
  {
//    microros_spinnode();

    osDelay(10);
  }

}


uint64_t ok ;
void startmainTask(void *argument)
{
	CAN2_filterconfig();
	HAL_CAN_Start(&hcan2);

  for(;;)
  {
	watchdog();

	RC_update();


    if(x3cator_RC.auto_switch){
    x3cator_velocityset(0.0,0.0);
    }
    else{
    x3cator_velocityset(x3cator_RC.linear_vel,x3cator_RC.angular_vel);
    }


    ok++;
    HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_13);

    x3cator_update();


    osDelay(10);
  }
  /* USER CODE END startmainTask */
}


void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */

  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM1)
  {
    HAL_IncTick();
  }
  /* USER CODE BEGIN Callback 1 */

  /* USER CODE END Callback 1 */
}

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

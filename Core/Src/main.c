/* USER CODE BEGIN Header */
#include <stdbool.h>
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

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

COM_InitTypeDef BspCOMInit;

TIM_HandleTypeDef htim3;
TIM_HandleTypeDef htim4;
TIM_HandleTypeDef htim6;
TIM_HandleTypeDef htim12;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_TIM3_Init(void);
static void MX_TIM6_Init(void);
static void MX_TIM4_Init(void);
static void MX_TIM12_Init(void);
/* USER CODE BEGIN PFP */
static void toggleUserLed(void);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
TIM_OC_InitTypeDef sConfigOC1 = {0};
TIM_OC_InitTypeDef sConfigOC2 = {0};
TIM_OC_InitTypeDef sConfigOC3 = {0};
bool state_positive = true;
uint16_t lookup_index = 0;
const uint16_t lookup_size = 360; // must match array size below, which is auto-generated
const uint16_t lookup1[360] = { 500, 508, 517, 526, 534, 543, 552, 560, 569, 578, 586, 595, 603, 612, 620, 629, 637, 646, 654, 662, 671, 679, 687, 695, 703, 711, 719, 726, 734, 742, 750, 757, 764, 772, 779, 786, 793, 800, 807, 814, 821, 828, 834, 840, 847, 853, 859, 865, 871, 877, 883, 888, 894, 899, 904, 909, 914, 919, 924, 928, 933, 937, 941, 945, 949, 953, 956, 960, 963, 966, 969, 972, 975, 978, 980, 982, 985, 987, 989, 990, 992, 993, 995, 996, 997, 998, 998, 999, 999, 999, 1000, 999, 999, 999, 998, 998, 997, 996, 995, 993, 992, 990, 989, 987, 985, 982, 980, 978, 975, 972, 969, 966, 963, 960, 956, 953, 949, 945, 941, 937, 933, 928, 924, 919, 914, 909, 904, 899, 894, 888, 883, 877, 871, 865, 859, 853, 847, 840, 834, 828, 821, 814, 807, 800, 793, 786, 779, 772, 764, 757, 750, 742, 734, 726, 719, 711, 703, 695, 687, 679, 671, 662, 654, 646, 637, 629, 620, 612, 603, 595, 586, 578, 569, 560, 552, 543, 534, 526, 517, 508, 500, 491, 482, 473, 465, 456, 447, 439, 430, 421, 413, 404, 396, 387, 379, 370, 362, 353, 345, 337, 328, 320, 312, 304, 296, 288, 280, 273, 265, 257, 250, 242, 235, 227, 220, 213, 206, 199, 192, 185, 178, 171, 165, 159, 152, 146, 140, 134, 128, 122, 116, 111, 105, 100, 95, 90, 85, 80, 75, 71, 66, 62, 58, 54, 50, 46, 43, 39, 36, 33, 30, 27, 24, 21, 19, 17, 14, 12, 10, 9, 7, 6, 4, 3, 2, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 2, 3, 4, 6, 7, 9, 10, 12, 14, 17, 19, 21, 24, 27, 30, 33, 36, 39, 43, 46, 50, 54, 58, 62, 66, 71, 75, 80, 85, 90, 95, 100, 105, 111, 116, 122, 128, 134, 140, 146, 152, 159, 165, 171, 178, 185, 192, 199, 206, 213, 220, 227, 235, 242, 249, 257, 265, 273, 280, 288, 296, 304, 312, 320, 328, 337, 345, 353, 362, 370, 379, 387, 396, 404, 413, 421, 430, 439, 447, 456, 465, 473, 482, 491 };
const uint16_t lookup2[360] = { 933, 928, 924, 919, 914, 909, 904, 899, 894, 888, 883, 877, 871, 865, 859, 853, 847, 840, 834, 828, 821, 814, 807, 800, 793, 786, 779, 772, 764, 757, 750, 742, 734, 726, 719, 711, 703, 695, 687, 679, 671, 662, 654, 646, 637, 629, 620, 612, 603, 595, 586, 578, 569, 560, 552, 543, 534, 526, 517, 508, 500, 491, 482, 473, 465, 456, 447, 439, 430, 421, 413, 404, 396, 387, 379, 370, 362, 353, 345, 337, 328, 320, 312, 304, 296, 288, 280, 273, 265, 257, 250, 242, 235, 227, 220, 213, 206, 199, 192, 185, 178, 171, 165, 159, 152, 146, 140, 134, 128, 122, 116, 111, 105, 100, 95, 90, 85, 80, 75, 71, 66, 62, 58, 54, 50, 46, 43, 39, 36, 33, 30, 27, 24, 21, 19, 17, 14, 12, 10, 9, 7, 6, 4, 3, 2, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 2, 3, 4, 6, 7, 9, 10, 12, 14, 17, 19, 21, 24, 27, 30, 33, 36, 39, 43, 46, 50, 54, 58, 62, 66, 71, 75, 80, 85, 90, 95, 100, 105, 111, 116, 122, 128, 134, 140, 146, 152, 159, 165, 171, 178, 185, 192, 199, 206, 213, 220, 227, 235, 242, 249, 257, 265, 273, 280, 288, 296, 304, 312, 320, 328, 337, 345, 353, 362, 370, 379, 387, 396, 404, 413, 421, 430, 439, 447, 456, 465, 473, 482, 491, 499, 508, 517, 526, 534, 543, 552, 560, 569, 578, 586, 595, 603, 612, 620, 629, 637, 646, 654, 662, 671, 679, 687, 695, 703, 711, 719, 726, 734, 742, 749, 757, 764, 772, 779, 786, 793, 800, 807, 814, 821, 828, 834, 840, 847, 853, 859, 865, 871, 877, 883, 888, 894, 899, 904, 909, 914, 919, 924, 928, 933, 937, 941, 945, 949, 953, 956, 960, 963, 966, 969, 972, 975, 978, 980, 982, 985, 987, 989, 990, 992, 993, 995, 996, 997, 998, 998, 999, 999, 999, 1000, 999, 999, 999, 998, 998, 997, 996, 995, 993, 992, 990, 989, 987, 985, 982, 980, 978, 975, 972, 969, 966, 963, 960, 956, 953, 949, 945, 941, 937 };
const uint16_t lookup3[360] = { 66, 62, 58, 54, 50, 46, 43, 39, 36, 33, 30, 27, 24, 21, 19, 17, 14, 12, 10, 9, 7, 6, 4, 3, 2, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 2, 3, 4, 6, 7, 9, 10, 12, 14, 17, 19, 21, 24, 27, 30, 33, 36, 39, 43, 46, 50, 54, 58, 62, 66, 71, 75, 80, 85, 90, 95, 100, 105, 111, 116, 122, 128, 134, 140, 146, 152, 159, 165, 171, 178, 185, 192, 199, 206, 213, 220, 227, 235, 242, 249, 257, 265, 273, 280, 288, 296, 304, 312, 320, 328, 337, 345, 353, 362, 370, 379, 387, 396, 404, 413, 421, 430, 439, 447, 456, 465, 473, 482, 491, 499, 508, 517, 526, 534, 543, 552, 560, 569, 578, 586, 595, 603, 612, 620, 629, 637, 646, 654, 662, 671, 679, 687, 695, 703, 711, 719, 726, 734, 742, 749, 757, 764, 772, 779, 786, 793, 800, 807, 814, 821, 828, 834, 840, 847, 853, 859, 865, 871, 877, 883, 888, 894, 899, 904, 909, 914, 919, 924, 928, 933, 937, 941, 945, 949, 953, 956, 960, 963, 966, 969, 972, 975, 978, 980, 982, 985, 987, 989, 990, 992, 993, 995, 996, 997, 998, 998, 999, 999, 999, 1000, 999, 999, 999, 998, 998, 997, 996, 995, 993, 992, 990, 989, 987, 985, 982, 980, 978, 975, 972, 969, 966, 963, 960, 956, 953, 949, 945, 941, 937, 933, 928, 924, 919, 914, 909, 904, 899, 894, 888, 883, 877, 871, 865, 859, 853, 847, 840, 834, 828, 821, 814, 807, 800, 793, 786, 779, 772, 764, 757, 750, 742, 734, 726, 719, 711, 703, 695, 687, 679, 671, 662, 654, 646, 637, 629, 620, 612, 603, 595, 586, 578, 569, 560, 552, 543, 534, 526, 517, 508, 500, 491, 482, 473, 465, 456, 447, 439, 430, 421, 413, 404, 396, 387, 379, 370, 362, 353, 345, 337, 328, 320, 312, 304, 296, 288, 280, 273, 265, 257, 250, 242, 235, 227, 220, 213, 206, 199, 192, 185, 178, 171, 165, 159, 152, 146, 140, 134, 128, 122, 116, 111, 105, 100, 95, 90, 85, 80, 75, 71 };
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
  MX_TIM3_Init();
  MX_TIM6_Init();
  MX_TIM4_Init();
  MX_TIM12_Init();
  /* USER CODE BEGIN 2 */

  HAL_TIM_Base_Start_IT(&htim6);

  /* USER CODE END 2 */

  /* Initialize leds */
  BSP_LED_Init(LED_GREEN);

  /* Initialize USER push-button, will be used to trigger an interrupt each time it's pressed.*/
  BSP_PB_Init(BUTTON_USER, BUTTON_MODE_EXTI);

  /* Initialize COM1 port (115200, 8 bits (7-bit data + 1 stop bit), no parity */
  BspCOMInit.BaudRate   = 115200;
  BspCOMInit.WordLength = COM_WORDLENGTH_8B;
  BspCOMInit.StopBits   = COM_STOPBITS_1;
  BspCOMInit.Parity     = COM_PARITY_NONE;
  BspCOMInit.HwFlowCtl  = COM_HWCONTROL_NONE;
  if (BSP_COM_Init(COM1, &BspCOMInit) != BSP_ERROR_NONE)
  {
    Error_Handler();
  }

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  /*
   * Timer 6 interval should be steps / 2*output_frequency
   */
  HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
  HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_3);
  HAL_TIM_PWM_Start(&htim12, TIM_CHANNEL_2);
  __HAL_TIM_ENABLE_IT(&htim6, TIM_IT_UPDATE);
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);

  while(!__HAL_PWR_GET_FLAG(PWR_FLAG_VOSRDY)) {}

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSIDiv = RCC_HSI_DIV2;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2
                              |RCC_CLOCKTYPE_PCLK3;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB3CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure the programming delay
  */
  __HAL_FLASH_SET_PROGRAM_DELAY(FLASH_PROGRAMMING_DELAY_0);
}

/**
  * @brief TIM3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM3_Init(void)
{

  /* USER CODE BEGIN TIM3_Init 0 */
  /* USER CODE END TIM3_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  //TIM_OC_InitTypeDef sConfigOC = {0};

  /* USER CODE BEGIN TIM3_Init 1 */
  /* USER CODE END TIM3_Init 1 */
  htim3.Instance = TIM3;
  htim3.Init.Prescaler = 0;
  htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim3.Init.Period = 1000;
  htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim3) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim3, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_Init(&htim3) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC1.OCMode = TIM_OCMODE_PWM1;
  sConfigOC1.Pulse = 0;
  sConfigOC1.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC1.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC1, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM3_Init 2 */
  /* USER CODE END TIM3_Init 2 */
  HAL_TIM_MspPostInit(&htim3);

}

/**
  * @brief TIM4 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM4_Init(void)
{

  /* USER CODE BEGIN TIM4_Init 0 */

  /* USER CODE END TIM4_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  //TIM_OC_InitTypeDef sConfigOC = {0};

  /* USER CODE BEGIN TIM4_Init 1 */

  /* USER CODE END TIM4_Init 1 */
  htim4.Instance = TIM4;
  htim4.Init.Prescaler = 0;
  htim4.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim4.Init.Period = 1000;
  htim4.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim4.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim4) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim4, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_Init(&htim4) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim4, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC2.OCMode = TIM_OCMODE_PWM1;
  sConfigOC2.Pulse = 0;
  sConfigOC2.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC2.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_PWM_ConfigChannel(&htim4, &sConfigOC2, TIM_CHANNEL_3) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM4_Init 2 */

  /* USER CODE END TIM4_Init 2 */
  HAL_TIM_MspPostInit(&htim4);

}

/**
  * @brief TIM6 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM6_Init(void)
{

  /* USER CODE BEGIN TIM6_Init 0 */

  /* USER CODE END TIM6_Init 0 */

  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM6_Init 1 */

  /* USER CODE END TIM6_Init 1 */
  htim6.Instance = TIM6;
  htim6.Init.Prescaler = 64 - 1;
  htim6.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim6.Init.Period = 25;
  htim6.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim6) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim6, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM6_Init 2 */

  /* USER CODE END TIM6_Init 2 */

}

/**
  * @brief TIM12 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM12_Init(void)
{

  /* USER CODE BEGIN TIM12_Init 0 */

  /* USER CODE END TIM12_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  //TIM_OC_InitTypeDef sConfigOC = {0};

  /* USER CODE BEGIN TIM12_Init 1 */

  /* USER CODE END TIM12_Init 1 */
  htim12.Instance = TIM12;
  htim12.Init.Prescaler = 0;
  htim12.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim12.Init.Period = 1000;
  htim12.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim12.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim12) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim12, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_Init(&htim12) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC3.OCMode = TIM_OCMODE_PWM1;
  sConfigOC3.Pulse = 0;
  sConfigOC3.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC3.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_PWM_ConfigChannel(&htim12, &sConfigOC3, TIM_CHANNEL_2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM12_Init 2 */

  /* USER CODE END TIM12_Init 2 */
  HAL_TIM_MspPostInit(&htim12);

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
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_RESET);

  /*Configure GPIO pin : PC4 */
  GPIO_InitStruct.Pin = GPIO_PIN_4;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pin : PA8 */
  GPIO_InitStruct.Pin = GPIO_PIN_8;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /* USER CODE BEGIN MX_GPIO_Init_2 */
  GPIO_InitStruct.Pin = GPIO_PIN_5;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct); // Claim PA5 (user LED)
  /* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */
void toggleUserLed(void)
{
	HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	// TIM6 defines the sinusoidal frequency
	if(htim == &htim6)
	{
		lookup_index++;
		if(lookup_index >= lookup_size)
		{
			lookup_index = 0;
		}

		sConfigOC1.Pulse = lookup1[lookup_index];
		sConfigOC2.Pulse = lookup2[lookup_index];
		sConfigOC3.Pulse = lookup3[lookup_index];

		HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC1, TIM_CHANNEL_1);
		HAL_TIM_PWM_ConfigChannel(&htim4, &sConfigOC2, TIM_CHANNEL_3);
		HAL_TIM_PWM_ConfigChannel(&htim12, &sConfigOC3, TIM_CHANNEL_2);
	}
}
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

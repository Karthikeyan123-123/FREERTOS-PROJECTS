/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
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
#include "fatfs.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
#include "fatfs.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
uint8_t tx;
uint8_t rx;
uint8_t dummy = 0xFF;
uint8_t txBuf[512];
uint8_t rxBuf[512];
uint8_t status1;
uint8_t status2;

uint8_t ok = 1;

FATFS fs;
FIL file;
FRESULT fr;
UINT bytesRead;

char buffer[128];


#define SD_OK             0
#define SD_CMD_ERROR      1
#define SD_TOKEN_ERROR    2
#define SD_TIMEOUT        3
#define SD_WRITE_ERROR    4



#define SD_CS_PORT GPIOA
#define SD_CS_PIN  GPIO_PIN_4
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
void SD_Select(void);
void SD_Deselect(void);

uint8_t SD_SPI_TxRx(uint8_t data);

void SD_SendClockTrain(void);

uint8_t SD_SendCommand(uint8_t cmd,
                       uint32_t arg,
                       uint8_t crc);
int __io_putchar(int ch);
uint8_t SD_Init(void);
uint8_t SD_ReadBlock(uint32_t sector, uint8_t *buffer);
uint8_t SD_WriteBlock(uint32_t sector, uint8_t *buffer);




/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
SPI_HandleTypeDef hspi1;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_SPI1_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
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
  MX_SPI1_Init();
  MX_FATFS_Init();

  fr = f_mount(&fs, "", 1);

  if(fr != FR_OK)
  {
      printf("Mount Failed : %d\r\n", fr);
      Error_Handler();
  }

  fr = f_open(&file, "karthi.txt", FA_READ);

  if(fr != FR_OK)
  {
      printf("Open Failed : %d\r\n", fr);
      Error_Handler();
  }

  fr = f_read(&file,
              buffer,
              sizeof(buffer)-1,
              &bytesRead);

  if(fr != FR_OK)
  {
      printf("Read Failed : %d\r\n", fr);
      Error_Handler();
  }

  buffer[bytesRead] = '\0';

  printf("File Content:\r\n");
  printf("%s\r\n", buffer);

  f_close(&file);
  /* USER CODE BEGIN 2 */














  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
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
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

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

/**
  * @brief SPI1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI1_Init(void)
{

  /* USER CODE BEGIN SPI1_Init 0 */

  /* USER CODE END SPI1_Init 0 */

  /* USER CODE BEGIN SPI1_Init 1 */

  /* USER CODE END SPI1_Init 1 */
  /* SPI1 parameter configuration*/
  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_64;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI1_Init 2 */

  /* USER CODE END SPI1_Init 2 */

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
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);

  /*Configure GPIO pin : PA4 */
  GPIO_InitStruct.Pin = GPIO_PIN_4;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /* USER CODE BEGIN MX_GPIO_Init_2 */

  /* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */
uint8_t SD_SPI_TxRx(uint8_t data)
{
    uint8_t rx;

    HAL_SPI_TransmitReceive(&hspi1,
                            &data,
                            &rx,
                            1,
                            HAL_MAX_DELAY);

    return rx;
}

void SD_Select(void)
{
    HAL_GPIO_WritePin(SD_CS_PORT,
                      SD_CS_PIN,
                      GPIO_PIN_RESET);
}

void SD_Deselect(void)
{
    HAL_GPIO_WritePin(SD_CS_PORT,
                      SD_CS_PIN,
                      GPIO_PIN_SET);
}

void SD_SendClockTrain(void)
{
    SD_Deselect();

    for(int i = 0; i < 10; i++)
    {
        SD_SPI_TxRx(0xFF);
    }
}

uint8_t SD_SendCommand(uint8_t cmd,
                       uint32_t arg,
                       uint8_t crc)
{
    uint8_t response;

    SD_Select();

    /* Give the card 8 clocks after CS goes LOW */
    SD_SPI_TxRx(0xFF);

    SD_SPI_TxRx(0x40 | cmd);

    SD_SPI_TxRx((arg >> 24) & 0xFF);

    SD_SPI_TxRx((arg >> 16) & 0xFF);

    SD_SPI_TxRx((arg >> 8) & 0xFF);

    SD_SPI_TxRx(arg & 0xFF);

    SD_SPI_TxRx(crc);

    for(int i = 0; i < 10; i++)
    {
        response = SD_SPI_TxRx(0xFF);

        if(response != 0xFF)
            return response;
    }

    return 0xFF;
}

int __io_putchar(int ch)
{
    ITM_SendChar(ch);
    return ch;
}

uint8_t SD_Init()
{
    uint8_t r1;
    uint8_t ocr[4];
    uint32_t timeout;

    SD_SendClockTrain();

    SD_Deselect();



    r1 = SD_SendCommand(0, 0x00000000, 0x95);
    if(r1 != 0x01)
        return SD_CMD_ERROR;

    SD_Deselect();
    SD_SPI_TxRx(0xFF);

    r1 = SD_SendCommand(8, 0x000001AA, 0x87);
    if(r1 != 0x01)
        return SD_CMD_ERROR;

    for(int i=0;i<4;i++)
        ocr[i] = SD_SPI_TxRx(0xFF);

    SD_Deselect();
    SD_SPI_TxRx(0xFF);

    timeout = 10000;

    do
    {
        r1 = SD_SendCommand(55,0,0x01);

        SD_Deselect();
        SD_SPI_TxRx(0xFF);

        if(r1 > 1)
            return SD_CMD_ERROR;

        r1 = SD_SendCommand(41,0x40000000,0x01);

        SD_Deselect();
        SD_SPI_TxRx(0xFF);

        if(timeout-- == 0)
            return SD_TIMEOUT;

    }while(r1 != 0x00);

    r1 = SD_SendCommand(58,0,0x01);

    if(r1 != 0x00)
        return SD_CMD_ERROR;

    for(int i=0;i<4;i++)
        ocr[i] = SD_SPI_TxRx(0xFF);

    SD_Deselect();
    SD_SPI_TxRx(0xFF);

    return SD_OK;
}


uint8_t SD_ReadBlock(uint32_t sector, uint8_t *buffer)
{
    uint8_t token;
    uint8_t crc[2];
    uint32_t timeout = 100000;

    if(SD_SendCommand(17, sector, 0x01) != 0x00)
    {
        SD_Deselect();
        SD_SPI_TxRx(0xFF);
        return SD_CMD_ERROR;
    }

    do
    {
        token = SD_SPI_TxRx(0xFF);

        if(timeout-- == 0)
        {
            SD_Deselect();
            SD_SPI_TxRx(0xFF);
            return SD_TIMEOUT;
        }

    }while(token == 0xFF);

    if(token != 0xFE)
    {
        SD_Deselect();
        SD_SPI_TxRx(0xFF);
        return SD_TOKEN_ERROR;
    }

    for(int i=0;i<512;i++)
        buffer[i] = SD_SPI_TxRx(0xFF);

    crc[0] = SD_SPI_TxRx(0xFF);
    crc[1] = SD_SPI_TxRx(0xFF);

    SD_Deselect();
    SD_SPI_TxRx(0xFF);

    return SD_OK;
}

uint8_t SD_WriteBlock(uint32_t sector, uint8_t *buffer)
{
    uint8_t response;
    uint32_t timeout = 100000;

    if(SD_SendCommand(24, sector, 0x01) != 0x00)
    {
        SD_Deselect();
        SD_SPI_TxRx(0xFF);
        return SD_CMD_ERROR;
    }

    SD_SPI_TxRx(0xFE);

    for(int i=0;i<512;i++)
        SD_SPI_TxRx(buffer[i]);

    SD_SPI_TxRx(0xFF);
    SD_SPI_TxRx(0xFF);

    response = SD_SPI_TxRx(0xFF);
    response &= 0x1F;

    if(response != 0x05)
    {
        SD_Deselect();
        SD_SPI_TxRx(0xFF);
        return SD_WRITE_ERROR;
    }

    while(SD_SPI_TxRx(0xFF) == 0x00)
    {
        if(timeout-- == 0)
        {
            SD_Deselect();
            SD_SPI_TxRx(0xFF);
            return SD_TIMEOUT;
        }
    }

    SD_Deselect();
    SD_SPI_TxRx(0xFF);

    return SD_OK;
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
#ifdef USE_FULL_ASSERT
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

/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : usbd_custom_hid_if.c
 * @version        : v2.0_Cube
 * @brief          : USB Device Custom HID interface file.
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2022 STMicroelectronics.
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
#include "usbd_custom_hid_if.h"

/* USER CODE BEGIN INCLUDE */

/* USER CODE END INCLUDE */

extern uint8_t receiveBuffer[64];
extern uint8_t receiveCount;

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/

/* USER CODE END PV */

/** @addtogroup STM32_USB_OTG_DEVICE_LIBRARY
 * @brief Usb device.
 * @{
 */

/** @addtogroup USBD_CUSTOM_HID
 * @{
 */

/** @defgroup USBD_CUSTOM_HID_Private_TypesDefinitions USBD_CUSTOM_HID_Private_TypesDefinitions
 * @brief Private types.
 * @{
 */

/* USER CODE BEGIN PRIVATE_TYPES */

/* USER CODE END PRIVATE_TYPES */

/**
 * @}
 */

/** @defgroup USBD_CUSTOM_HID_Private_Defines USBD_CUSTOM_HID_Private_Defines
 * @brief Private defines.
 * @{
 */

/* USER CODE BEGIN PRIVATE_DEFINES */

/* USER CODE END PRIVATE_DEFINES */

/**
 * @}
 */

/** @defgroup USBD_CUSTOM_HID_Private_Macros USBD_CUSTOM_HID_Private_Macros
 * @brief Private macros.
 * @{
 */

/* USER CODE BEGIN PRIVATE_MACRO */

/* USER CODE END PRIVATE_MACRO */

/**
 * @}
 */

/** @defgroup USBD_CUSTOM_HID_Private_Variables USBD_CUSTOM_HID_Private_Variables
 * @brief Private variables.
 * @{
 */

/** Usb HID report descriptor. */
// __ALIGN_BEGIN static uint8_t CUSTOM_HID_ReportDesc_FS[USBD_CUSTOM_HID_REPORT_DESC_SIZE] __ALIGN_END =
// {
//   /* USER CODE BEGIN 0 */
//   0x00,
//   /* USER CODE END 0 */
//   0xC0    /*     END_COLLECTION	             */
// };

// 键盘用HID描述符
__ALIGN_BEGIN static uint8_t CUSTOM_HID_ReportDesc_FS[USBD_CUSTOM_HID_REPORT_DESC_SIZE] __ALIGN_END =
    {
        0x05, 0x01, // USAGE_PAGE (Generic Desktop)
        0x09, 0x06, // USAGE (Keyboard)		   /* 用途为键盘 */
        0xa1, 0x01, // COLLECTION (Application) /* 表示应用结合，必须以END_COLLECTION来结束 */
        0x05, 0x07, //   USAGE_PAGE (Keyboard)  /* 用途页为按键 */
        0x19, 0xe0, //   USAGE_MINIMUM (Keyboard LeftControl)  /* 用途最小值 左Ctrl */
        0x29, 0xe7, //   USAGE_MAXIMUM (Keyboard Right GUI)	  /* 用途最大值 右GUI */
        0x15, 0x00, //   LOGICAL_MINIMUM (0)	   /* 逻辑最小值 0 */
        0x25, 0x01, //   LOGICAL_MAXIMUM (1)	   /* 逻辑最大值 1 */
        0x75, 0x01, //   REPORT_SIZE (1)      /* 报告位大小(这个字段的宽度为1bit) */
        0x95, 0x08, //   REPORT_COUNT (8) 	 /* 输入报告第一个字节(报告位大小 8bit) */
        0x81, 0x02, //   INPUT (Data,Var,Abs) /* 报告为输入用 , 从左ctrl到右GUI 8bit刚好构成1个字节*/

        0x95, 0x01, //   REPORT_COUNT (1)	 /* 报告位数量  1个 */
        0x75, 0x08, //   REPORT_SIZE (8)      /* 输入报告的第二给字节(报告位大小 8bit) */
        0x81, 0x03, //   INPUT (Cnst,Var,Abs) /* 输入用的保留位，设备必须返回0 */

        0x95, 0x05, //   REPORT_COUNT (5)     /* 报告位数量 5个 */
        0x75, 0x01, //   REPORT_SIZE (1)		 /* 报告位大小，1bit */
        0x05, 0x08, //   USAGE_PAGE (LEDs)    /* 用途为LED */
        0x19, 0x01, //   USAGE_MINIMUM (Num Lock) /* 用途最小值 NUM Lock LED灯 */
        0x29, 0x05, //   USAGE_MAXIMUM (Kana)  /* 用途最大值 Kana 灯 */
        0x91, 0x02, //   OUTPUT (Data,Var,Abs) /* 输出用途，用于控制LED等 */

        0x95, 0x01, //   REPORT_COUNT (1)     /* 报告位数量 1个 */
        0x75, 0x03, //   REPORT_SIZE (3)      /* 报告位大小 3bit */
        0x91, 0x03, //   OUTPUT (Cnst,Var,Abs)/* 用于字节补齐，跟前面5个bit进行补齐 */

        0x95, 0x06, // 0x06,                    //   REPORT_COUNT (6)  /* 报告位数量 6个*/
        0x75, 0x08, //   REPORT_SIZE (8)		 /* 报告位大小 8bit */
        0x15, 0x00, //   LOGICAL_MINIMUM (0)		 /* 逻辑最小值0 */
        0x25, 0xFF, //   LOGICAL_MAXIMUM (255)    /* 逻辑最大值255 */
        0x05, 0x07, //   USAGE_PAGE (Keyboard)    /* 用途页为按键 */
        0x19, 0x00, //   USAGE_MINIMUM (Reserved (no event indicated)) /* 使用值最小为0 */
        0x29, 0xDF, //   USAGE_MAXIMUM (Reserved Reserved)		  /* 使用值最大为 */
        0x81, 0x00, //   INPUT (Data,Ary,Abs)	 /* 输入用，变量，数组，绝对值 */
        0xc0        /* END_COLLECTION */
};

/* USER CODE BEGIN PRIVATE_VARIABLES */

/* USER CODE END PRIVATE_VARIABLES */

/**
 * @}
 */

/** @defgroup USBD_CUSTOM_HID_Exported_Variables USBD_CUSTOM_HID_Exported_Variables
 * @brief Public variables.
 * @{
 */
extern USBD_HandleTypeDef hUsbDeviceFS;

/* USER CODE BEGIN EXPORTED_VARIABLES */

/* USER CODE END EXPORTED_VARIABLES */
/**
 * @}
 */

/** @defgroup USBD_CUSTOM_HID_Private_FunctionPrototypes USBD_CUSTOM_HID_Private_FunctionPrototypes
 * @brief Private functions declaration.
 * @{
 */

static int8_t CUSTOM_HID_Init_FS(void);
static int8_t CUSTOM_HID_DeInit_FS(void);
static int8_t CUSTOM_HID_OutEvent_FS(uint8_t event_idx, uint8_t state);

/**
 * @}
 */

USBD_CUSTOM_HID_ItfTypeDef USBD_CustomHID_fops_FS =
    {
        CUSTOM_HID_ReportDesc_FS,
        CUSTOM_HID_Init_FS,
        CUSTOM_HID_DeInit_FS,
        CUSTOM_HID_OutEvent_FS};

/** @defgroup USBD_CUSTOM_HID_Private_Functions USBD_CUSTOM_HID_Private_Functions
 * @brief Private functions.
 * @{
 */

/* Private functions ---------------------------------------------------------*/

/**
 * @brief  Initializes the CUSTOM HID media low layer
 * @retval USBD_OK if all operations are OK else USBD_FAIL
 */
static int8_t CUSTOM_HID_Init_FS(void)
{
  /* USER CODE BEGIN 4 */
  return (USBD_OK);
  /* USER CODE END 4 */
}

/**
 * @brief  DeInitializes the CUSTOM HID media low layer
 * @retval USBD_OK if all operations are OK else USBD_FAIL
 */
static int8_t CUSTOM_HID_DeInit_FS(void)
{
  /* USER CODE BEGIN 5 */
  return (USBD_OK);
  /* USER CODE END 5 */
}

/**
 * @brief  Manage the CUSTOM HID class events
 * @param  event_idx: Event index
 * @param  state: Event state
 * @retval USBD_OK if all operations are OK else USBD_FAIL
 */
static int8_t CUSTOM_HID_OutEvent_FS(uint8_t event_idx, uint8_t state)
{
  /* USER CODE BEGIN 6 */

  // /*查看接收数据长度*/
  // receiveCount = USBD_GetRxCount(&hUsbDeviceFS, CUSTOM_HID_EPOUT_ADDR); //第一参数是USB句柄，第二个参数的是接收的末端地址；要获取发送的数据长度的话就把第二个参数改为发送末端地址即可
  // // printf("USB_Received_Count = %d \r\n",USB_Received_Count);

  // USBD_CUSTOM_HID_HandleTypeDef *hhid;                             //定义一个指向USBD_CUSTOM_HID_HandleTypeDef结构体的指针
  // hhid = (USBD_CUSTOM_HID_HandleTypeDef *)hUsbDeviceFS.pClassData; //得到USB接收数据的储存地址

  // for (uint8_t i = 0; i < receiveCount; i++)
  // {
  //   receiveBuffer[i] = hhid->Report_buf[i]; //把接收到的数据送到自定义的缓存区保存（Report_buf[i]为USB的接收缓存区）
  // }

    if (event_idx == 0x00)
    {
      HAL_GPIO_WritePin(Lycoris_LED_NumberLock_Port, Lycoris_LED_NumberLock_Pin, GPIO_PIN_SET);
      HAL_GPIO_WritePin(Lycoris_LED_CapsLock_Port, Lycoris_LED_CapsLock_Pin, GPIO_PIN_SET);
      HAL_GPIO_WritePin(Lycoris_LED_ScrollLock_Port, Lycoris_LED_ScrollLock_Pin, GPIO_PIN_SET);
    }
    else if (event_idx == 0x01)
    {
      HAL_GPIO_WritePin(Lycoris_LED_NumberLock_Port, Lycoris_LED_NumberLock_Pin, GPIO_PIN_RESET);
      HAL_GPIO_WritePin(Lycoris_LED_CapsLock_Port, Lycoris_LED_CapsLock_Pin, GPIO_PIN_SET);
      HAL_GPIO_WritePin(Lycoris_LED_ScrollLock_Port, Lycoris_LED_ScrollLock_Pin, GPIO_PIN_SET);
    }
    else if (event_idx == 0x02)
    {
      HAL_GPIO_WritePin(Lycoris_LED_NumberLock_Port, Lycoris_LED_NumberLock_Pin, GPIO_PIN_SET);
      HAL_GPIO_WritePin(Lycoris_LED_CapsLock_Port, Lycoris_LED_CapsLock_Pin, GPIO_PIN_RESET);
      HAL_GPIO_WritePin(Lycoris_LED_ScrollLock_Port, Lycoris_LED_ScrollLock_Pin, GPIO_PIN_SET);
    }
    else if (event_idx == 0x03)
    {
      HAL_GPIO_WritePin(Lycoris_LED_NumberLock_Port, Lycoris_LED_NumberLock_Pin, GPIO_PIN_RESET);
      HAL_GPIO_WritePin(Lycoris_LED_CapsLock_Port, Lycoris_LED_CapsLock_Pin, GPIO_PIN_RESET);
      HAL_GPIO_WritePin(Lycoris_LED_ScrollLock_Port, Lycoris_LED_ScrollLock_Pin, GPIO_PIN_SET);
    }
    else if (event_idx == 0x04)
    {
      HAL_GPIO_WritePin(Lycoris_LED_NumberLock_Port, Lycoris_LED_NumberLock_Pin, GPIO_PIN_SET);
      HAL_GPIO_WritePin(Lycoris_LED_CapsLock_Port, Lycoris_LED_CapsLock_Pin, GPIO_PIN_SET);
      HAL_GPIO_WritePin(Lycoris_LED_ScrollLock_Port, Lycoris_LED_ScrollLock_Pin, GPIO_PIN_RESET);
    }
    else if (event_idx == 0x05)
    {
      HAL_GPIO_WritePin(Lycoris_LED_NumberLock_Port, Lycoris_LED_NumberLock_Pin, GPIO_PIN_RESET);
      HAL_GPIO_WritePin(Lycoris_LED_CapsLock_Port, Lycoris_LED_CapsLock_Pin, GPIO_PIN_SET);
      HAL_GPIO_WritePin(Lycoris_LED_ScrollLock_Port, Lycoris_LED_ScrollLock_Pin, GPIO_PIN_RESET);
    }
    else if (event_idx == 0x06)
    {
      HAL_GPIO_WritePin(Lycoris_LED_NumberLock_Port, Lycoris_LED_NumberLock_Pin, GPIO_PIN_SET);
      HAL_GPIO_WritePin(Lycoris_LED_CapsLock_Port, Lycoris_LED_CapsLock_Pin, GPIO_PIN_RESET);
      HAL_GPIO_WritePin(Lycoris_LED_ScrollLock_Port, Lycoris_LED_ScrollLock_Pin, GPIO_PIN_RESET);
    }
    else if (event_idx == 0x07)
    {
      HAL_GPIO_WritePin(Lycoris_LED_NumberLock_Port, Lycoris_LED_NumberLock_Pin, GPIO_PIN_RESET);
      HAL_GPIO_WritePin(Lycoris_LED_CapsLock_Port, Lycoris_LED_CapsLock_Pin, GPIO_PIN_RESET);
      HAL_GPIO_WritePin(Lycoris_LED_ScrollLock_Port, Lycoris_LED_ScrollLock_Pin, GPIO_PIN_RESET);
    }

  return USBD_OK;
}

/* USER CODE BEGIN 7 */
/**
 * @brief  Send the report to the Host
 * @param  report: The report to be sent
 * @param  len: The report length
 * @retval USBD_OK if all operations are OK else USBD_FAIL
 */
/*
static int8_t USBD_CUSTOM_HID_SendReport_FS(uint8_t *report, uint16_t len)
{
  return USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS, report, len);
}
*/
/* USER CODE END 7 */

/* USER CODE BEGIN PRIVATE_FUNCTIONS_IMPLEMENTATION */

/* USER CODE END PRIVATE_FUNCTIONS_IMPLEMENTATION */
/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */

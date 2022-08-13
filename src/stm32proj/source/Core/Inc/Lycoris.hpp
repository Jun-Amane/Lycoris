#pragma once

#include "stm32f1xx_hal.h"

#include <stdbool.h>


#ifdef __cplusplus
extern "C"
{
#endif

    void Error_Handler(void);   // 以C语言定义

#ifdef __cplusplus
}
#endif

extern bool keyChangedFlag;     // 按键更新标志位
extern bool repoartFlag;        // 上传标志位
//按键状态
typedef enum
{
    Pressed = 1,
    Unpressed = 0
} Lycoris_KeyStatusTypedef;

extern uint8_t FKEYByte; //状态控制键字节 如Shift Ctrl键等
extern uint8_t Lycoris_Report[8];

typedef struct{
    uint8_t keyCode;
    uint8_t x;
    uint8_t y;
}keyBufferTypedef;


// 定义

#define FKEY 0x00

#define Lycoris_Key_X_0_Port GPIOB
#define Lycoris_Key_X_1_Port GPIOB
#define Lycoris_Key_X_2_Port GPIOB
#define Lycoris_Key_X_3_Port GPIOB
#define Lycoris_Key_X_4_Port GPIOB
#define Lycoris_Key_X_5_Port GPIOB
#define Lycoris_Key_Y_0_Port GPIOB
#define Lycoris_Key_Y_1_Port GPIOA
#define Lycoris_Key_Y_2_Port GPIOB
#define Lycoris_Key_Y_3_Port GPIOB
#define Lycoris_Key_Y_4_Port GPIOA
#define Lycoris_Key_Y_5_Port GPIOA
#define Lycoris_Key_Y_6_Port GPIOA
#define Lycoris_Key_Y_7_Port GPIOB
#define Lycoris_Key_Y_8_Port GPIOB
#define Lycoris_Key_Y_9_Port GPIOB
#define Lycoris_Key_Y_10_Port GPIOB
#define Lycoris_Key_Y_11_Port GPIOC
#define Lycoris_Key_Y_12_Port GPIOC
#define Lycoris_Key_Y_13_Port GPIOC
#define Lycoris_Key_Y_14_Port GPIOA
#define Lycoris_Key_Y_15_Port GPIOA
#define Lycoris_Key_Y_16_Port GPIOA
#define Lycoris_Key_Y_17_Port GPIOA
#define Lycoris_Key_Y_18_Port GPIOA
#define Lycoris_LED_NumberLock_Port GPIOA
#define Lycoris_LED_CapsLock_Port GPIOB
#define Lycoris_LED_ScrollLock_Port GPIOB

#define Lycoris_Key_X_0_Pin GPIO_PIN_9
#define Lycoris_Key_X_1_Pin GPIO_PIN_8
#define Lycoris_Key_X_2_Pin GPIO_PIN_7
#define Lycoris_Key_X_3_Pin GPIO_PIN_6
#define Lycoris_Key_X_4_Pin GPIO_PIN_5
#define Lycoris_Key_X_5_Pin GPIO_PIN_4
#define Lycoris_Key_Y_0_Pin GPIO_PIN_3
#define Lycoris_Key_Y_1_Pin GPIO_PIN_15
#define Lycoris_Key_Y_2_Pin GPIO_PIN_11
#define Lycoris_Key_Y_3_Pin GPIO_PIN_10
#define Lycoris_Key_Y_4_Pin GPIO_PIN_10
#define Lycoris_Key_Y_5_Pin GPIO_PIN_9
#define Lycoris_Key_Y_6_Pin GPIO_PIN_8
#define Lycoris_Key_Y_7_Pin GPIO_PIN_15
#define Lycoris_Key_Y_8_Pin GPIO_PIN_14
#define Lycoris_Key_Y_9_Pin GPIO_PIN_13
#define Lycoris_Key_Y_10_Pin GPIO_PIN_12
#define Lycoris_Key_Y_11_Pin GPIO_PIN_13
#define Lycoris_Key_Y_12_Pin GPIO_PIN_14
#define Lycoris_Key_Y_13_Pin GPIO_PIN_15
#define Lycoris_Key_Y_14_Pin GPIO_PIN_0
#define Lycoris_Key_Y_15_Pin GPIO_PIN_1
#define Lycoris_Key_Y_16_Pin GPIO_PIN_4
#define Lycoris_Key_Y_17_Pin GPIO_PIN_5
#define Lycoris_Key_Y_18_Pin GPIO_PIN_6
#define Lycoris_LED_NumberLock_Pin GPIO_PIN_7
#define Lycoris_LED_CapsLock_Pin GPIO_PIN_0
#define Lycoris_LED_ScrollLock_Pin GPIO_PIN_1

//函数

// Init用函数
void Lycoris_GPIOInit();

//void Lycoris_TIMInit(uint16_t arr, uint16_t psc);

// Lycoris主要函数
void Lycoris_Update();
void Lycoris_Key_Y_Scan();
void Lycoris_Key_X_Scan(GPIO_TypeDef *Key_Y_Port, uint8_t index, const uint16_t *Key_Y_Pin);
void Lycoris_ifKeyStatusChanged();
void Lycoris_updateKeyBuffer();
void Lycoris_FKeys(uint8_t x, uint8_t y);
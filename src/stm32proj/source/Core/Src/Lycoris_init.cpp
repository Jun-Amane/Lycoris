#include "Lycoris.hpp"

void Lycoris_GPIOInit()
{

    // GPIO_InitTypeDef Lycoris_initStructure = {0};
    // //时钟
    // __HAL_RCC_GPIOC_CLK_ENABLE();
    // __HAL_RCC_GPIOD_CLK_ENABLE();
    // __HAL_RCC_GPIOA_CLK_ENABLE();
    // __HAL_RCC_GPIOB_CLK_ENABLE();

    __HAL_RCC_AFIO_CLK_ENABLE();
    __HAL_AFIO_REMAP_SWJ_NOJTAG(); //禁用JTAG

    // // Key_X 下拉输入
    // Lycoris_initStructure.Pin = Lycoris_Key_X_0_Pin |
    //                             Lycoris_Key_X_1_Pin |
    //                             Lycoris_Key_X_2_Pin |
    //                             Lycoris_Key_X_3_Pin |
    //                             Lycoris_Key_X_4_Pin |
    //                             Lycoris_Key_X_5_Pin;

    // Lycoris_initStructure.Mode = GPIO_MODE_INPUT;
    // Lycoris_initStructure.Pull = GPIO_PULLDOWN;
    // HAL_GPIO_Init(GPIOB, &Lycoris_initStructure);

    // // Key_Y GPIOB
    // Lycoris_initStructure.Pin = Lycoris_Key_Y_0_Pin |
    //                             Lycoris_Key_Y_2_Pin |
    //                             Lycoris_Key_Y_3_Pin |
    //                             Lycoris_Key_Y_7_Pin |
    //                             Lycoris_Key_Y_8_Pin |
    //                             Lycoris_Key_Y_9_Pin |
    //                             Lycoris_Key_Y_10_Pin;

    // Lycoris_initStructure.Speed = GPIO_SPEED_FREQ_MEDIUM;
    // Lycoris_initStructure.Pull = GPIO_NOPULL;
    // Lycoris_initStructure.Mode = GPIO_MODE_OUTPUT_PP;
    // HAL_GPIO_Init(GPIOB, &Lycoris_initStructure);

    // // Key_Y GPIOA
    // Lycoris_initStructure.Pin = Lycoris_Key_Y_1_Pin |
    //                             Lycoris_Key_Y_4_Pin |
    //                             Lycoris_Key_Y_5_Pin |
    //                             Lycoris_Key_Y_6_Pin |
    //                             Lycoris_Key_Y_14_Pin |
    //                             Lycoris_Key_Y_15_Pin |
    //                             Lycoris_Key_Y_16_Pin |
    //                             Lycoris_Key_Y_17_Pin |
    //                             Lycoris_Key_Y_18_Pin;

    // Lycoris_initStructure.Speed = GPIO_SPEED_FREQ_MEDIUM;
    // Lycoris_initStructure.Pull = GPIO_NOPULL;
    // Lycoris_initStructure.Mode = GPIO_MODE_OUTPUT_PP;
    // HAL_GPIO_Init(GPIOB, &Lycoris_initStructure);

    // // Key_Y GPIOC
    // Lycoris_initStructure.Pin = Lycoris_Key_Y_11_Pin |
    //                             Lycoris_Key_Y_12_Pin |
    //                             Lycoris_Key_Y_13_Pin;

    // Lycoris_initStructure.Speed = GPIO_SPEED_FREQ_MEDIUM;
    // Lycoris_initStructure.Pull = GPIO_NOPULL;
    // Lycoris_initStructure.Mode = GPIO_MODE_OUTPUT_PP;
    // HAL_GPIO_Init(GPIOC, &Lycoris_initStructure);

    // // LED GPIOA
    // Lycoris_initStructure.Pin = Lycoris_LED_NumberLock_Pin;

    // Lycoris_initStructure.Speed = GPIO_SPEED_FREQ_MEDIUM;
    // Lycoris_initStructure.Pull = GPIO_NOPULL;
    // Lycoris_initStructure.Mode = GPIO_MODE_OUTPUT_PP;
    // HAL_GPIO_Init(GPIOA, &Lycoris_initStructure);

    // // LED GPIOB
    // Lycoris_initStructure.Pin = Lycoris_LED_CapsLock_Pin | Lycoris_LED_ScrollLock_Pin;

    // Lycoris_initStructure.Speed = GPIO_SPEED_FREQ_MEDIUM;
    // Lycoris_initStructure.Pull = GPIO_NOPULL;
    // Lycoris_initStructure.Mode = GPIO_MODE_OUTPUT_PP;
    // HAL_GPIO_Init(GPIOB, &Lycoris_initStructure);

    GPIO_InitTypeDef GPIO_InitStruct = {0};

    /* GPIO Ports Clock Enable */
    __HAL_RCC_GPIOC_CLK_ENABLE();
    __HAL_RCC_GPIOD_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();

    // 默认状态为低电平
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_15, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10 | GPIO_PIN_11 | GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15 | GPIO_PIN_3, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0 | GPIO_PIN_1, GPIO_PIN_SET);

    // GPIOC初始化
    GPIO_InitStruct.Pin = GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

    // GPIOA初始化
    GPIO_InitStruct.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_15;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    // GPIOB初始化
    GPIO_InitStruct.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_10 | GPIO_PIN_11 | GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15 | GPIO_PIN_3;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    // 键盘阵列X初始化
    GPIO_InitStruct.Pin = GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_9;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_PULLDOWN;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    return;
}

// void Lycoris_TIMInit(uint16_t arr, uint16_t psc)
// {
//     TIM_Base_InitTypeDef Lycoris_TIMStructure;
// }
#include "Lycoris.hpp"
#include <string>

bool isFKey = true;

bool keyChangedFlag = false;
bool repoartFlag = false;

uint8_t Lycoris_Report[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};   // 上传报文

Lycoris_KeyStatusTypedef KeyStatus[6][19] = {Unpressed};
Lycoris_KeyStatusTypedef lastKeyStatus[6][19] = {Unpressed};

keyBufferTypedef keyBuffer[6];      // 上传报文中普通按键字节

unsigned char FKEYByte = 0x00; //状态控制键字节 如Shift Ctrl键等

uint8_t receiveBuffer[64];
uint8_t receiveCount = 0;

const std::string Lycoris_keyNameArray[6][19] = {
    {"Esc", "F1", "F2", "F3", "F4", "F5", "F6", "F7", "F8", "F9", "F10", "F11", "F12", "PrtScr", "ScLk", "Pause", "NumLK", "NPSlash", "NPAster"},
    {"H/F", "Num1", "Num2", "Num3", "Num4", "Num5", "Num6", "Num7", "Num8", "Num9", "Num0", "Hyp", "Caret", "En", "BkSpc", "Ins", "Home", "PgUp", "NPHyp"},
    {"Tab", "Q", "W", "E", "R", "T", "Y", "U", "I", "O", "P", "At", "LSqBrc", "Enter", "Del", "End", "PgDown", "NP9", "NPPlus"},
    {"Eisu", "A", "S", "D", "F", "G", "H", "J", "K", "L", "Semicol", "Colon", "RSqBrc", "NP4", "NP5", "NP6", "NP7", "NP8", ""},
    {"LShift", "Z", "X", "C", "V", "B", "N", "M", "LsThan", "GrtrThan", "Slash", "BkSlash", "RShift", "Up", "NP1", "NP2", "NP3", "NPEnter", ""},
    {"LCtrl", "LOpt", "LAlt", "MuHenkan", "Spc", "Henkan", "Kata/Hira", "AltGr", "ROpt", "Menu", "RCtrl", "Left", "Down", "Right", "NP0", "NPDot", "", "", ""}

};

// 按键USB Usage ID
const uint8_t Lycoris_usageIdArray[6][19] =
    {
        {0x29, 0x3A, 0x3B, 0x3C, 0x3D, 0x3E, 0x3F, 0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x53, 0x54, 0x55},
        {0x35, 0x1E, 0x1F, 0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x2D, 0x2E, 0x89, 0x2A, 0x49, 0x4A, 0x4B, 0x56},
        {0x2B, 0x14, 0x1A, 0x08, 0x15, 0x17, 0x1C, 0x18, 0x0C, 0x12, 0x13, 0x2F, 0x30, 0x28, 0x4C, 0x4D, 0x4E, 0x61, 0x57},
        {0x39, 0x04, 0x16, 0x07, 0x09, 0x0A, 0x0B, 0x0D, 0x0E, 0x0F, 0x33, 0x34, 0x31, 0x5C, 0x5D, 0x5E, 0x5F, 0x60, 0x00},
        {FKEY, 0x1D, 0x1B, 0x06, 0x19, 0x05, 0x11, 0x10, 0x36, 0x37, 0x38, 0x87, FKEY, 0x52, 0x59, 0x5A, 0x5B, 0x58, 0x00},
        {FKEY, FKEY, FKEY, 0x8B, 0x2C, 0x8A, 0x88, FKEY, FKEY, 0x65, FKEY, 0x50, 0x51, 0x4F, 0x62, 0x63, 0x00, 0x00, 0x00}

};

void Lycoris_Update()
{

    Lycoris_Key_Y_Scan();
    Lycoris_ifKeyStatusChanged();

    if (keyChangedFlag)
    {
        Lycoris_updateKeyBuffer();
        keyChangedFlag = false;
        repoartFlag = true;
    }
    return;
}

void Lycoris_Key_X_Scan(GPIO_TypeDef *Key_Y_Port, uint8_t index, const uint16_t Key_Y_Pin)
{
    HAL_GPIO_WritePin(Key_Y_Port, Key_Y_Pin, GPIO_PIN_SET);
    HAL_Delay(1);
    if (HAL_GPIO_ReadPin(Lycoris_Key_X_0_Port, Lycoris_Key_X_0_Pin) == GPIO_PIN_SET)
    {
        KeyStatus[0][index] = Pressed;
    }
    else
    {
        KeyStatus[0][index] = Unpressed;
    }
    //HAL_Delay(1);
    if (HAL_GPIO_ReadPin(Lycoris_Key_X_1_Port, Lycoris_Key_X_1_Pin) == GPIO_PIN_SET)
    {
        KeyStatus[1][index] = Pressed;
    }
    else
    {
        KeyStatus[1][index] = Unpressed;
    }
    //HAL_Delay(1);
    if (HAL_GPIO_ReadPin(Lycoris_Key_X_2_Port, Lycoris_Key_X_2_Pin) == GPIO_PIN_SET)
    {
        KeyStatus[2][index] = Pressed;
    }
    else
    {
        KeyStatus[2][index] = Unpressed;
    }
    //HAL_Delay(1);
    if (HAL_GPIO_ReadPin(Lycoris_Key_X_3_Port, Lycoris_Key_X_3_Pin) == GPIO_PIN_SET)
    {
        KeyStatus[3][index] = Pressed;
    }
    else
    {
        KeyStatus[3][index] = Unpressed;
    }
    //HAL_Delay(1);
    if (HAL_GPIO_ReadPin(Lycoris_Key_X_4_Port, Lycoris_Key_X_4_Pin) == GPIO_PIN_SET)
    {
        KeyStatus[4][index] = Pressed;
    }
    else
    {
        KeyStatus[4][index] = Unpressed;
    }
    //HAL_Delay(1);
    if (HAL_GPIO_ReadPin(Lycoris_Key_X_5_Port, Lycoris_Key_X_5_Pin) == GPIO_PIN_SET)
    {
        KeyStatus[5][index] = Pressed;
    }
    else
    {
        KeyStatus[5][index] = Unpressed;
    }
    //HAL_Delay(1);
    HAL_GPIO_WritePin(Key_Y_Port, Key_Y_Pin, GPIO_PIN_RESET);

    return;
}

//
void Lycoris_Key_Y_Scan()
{

    Lycoris_Key_X_Scan(Lycoris_Key_Y_0_Port, 0, Lycoris_Key_Y_0_Pin);
    Lycoris_Key_X_Scan(Lycoris_Key_Y_1_Port, 1, Lycoris_Key_Y_1_Pin);
    Lycoris_Key_X_Scan(Lycoris_Key_Y_2_Port, 2, Lycoris_Key_Y_2_Pin);
    Lycoris_Key_X_Scan(Lycoris_Key_Y_3_Port, 3, Lycoris_Key_Y_3_Pin);
    Lycoris_Key_X_Scan(Lycoris_Key_Y_4_Port, 4, Lycoris_Key_Y_4_Pin);
    Lycoris_Key_X_Scan(Lycoris_Key_Y_5_Port, 5, Lycoris_Key_Y_5_Pin);
    Lycoris_Key_X_Scan(Lycoris_Key_Y_6_Port, 6, Lycoris_Key_Y_6_Pin);
    Lycoris_Key_X_Scan(Lycoris_Key_Y_7_Port, 7, Lycoris_Key_Y_7_Pin);
    Lycoris_Key_X_Scan(Lycoris_Key_Y_8_Port, 8, Lycoris_Key_Y_8_Pin);
    Lycoris_Key_X_Scan(Lycoris_Key_Y_9_Port, 9, Lycoris_Key_Y_9_Pin);
    Lycoris_Key_X_Scan(Lycoris_Key_Y_10_Port, 10, Lycoris_Key_Y_10_Pin);
    Lycoris_Key_X_Scan(Lycoris_Key_Y_11_Port, 11, Lycoris_Key_Y_11_Pin);
    Lycoris_Key_X_Scan(Lycoris_Key_Y_12_Port, 12, Lycoris_Key_Y_12_Pin);
    Lycoris_Key_X_Scan(Lycoris_Key_Y_13_Port, 13, Lycoris_Key_Y_13_Pin);
    Lycoris_Key_X_Scan(Lycoris_Key_Y_14_Port, 14, Lycoris_Key_Y_14_Pin);
    Lycoris_Key_X_Scan(Lycoris_Key_Y_15_Port, 15, Lycoris_Key_Y_15_Pin);
    Lycoris_Key_X_Scan(Lycoris_Key_Y_16_Port, 16, Lycoris_Key_Y_16_Pin);
    Lycoris_Key_X_Scan(Lycoris_Key_Y_17_Port, 17, Lycoris_Key_Y_17_Pin);
    Lycoris_Key_X_Scan(Lycoris_Key_Y_18_Port, 18, Lycoris_Key_Y_18_Pin);

    return;
}

void Lycoris_ifKeyStatusChanged()
{
    for (uint8_t x = 0; x < 6; x++)
    {
        for (uint8_t y = 0; y < 19; y++)
        {
            if (lastKeyStatus[x][y] != KeyStatus[x][y])
            {
                keyChangedFlag = true;
                break;
            }
        }
        if (keyChangedFlag)
        {
            break;
        }
    }

    for (uint8_t x = 0; x < 6; x++)
    {
        for (uint8_t y = 0; y < 19; y++)
        {
            lastKeyStatus[x][y] = KeyStatus[x][y];
        }
    }

    return;
}

void Lycoris_updateKeyBuffer()
{

    bool ifUsageIdExist = false;

    FKEYByte = 0x00;
    for (uint8_t i = 0; i < 6; i++)
    {
        if (keyBuffer[i].keyCode != 0x00)
        {
            if (KeyStatus[keyBuffer[i].x][keyBuffer[i].y] == Unpressed)
            {
                keyBuffer[i].keyCode = 0x00;
            }
        }
    }

    for (uint8_t x = 0; x < 6; x++)
    {
        for (uint8_t y = 0; y < 19; y++)
        {
            if (KeyStatus[x][y] == Pressed)
            {
                Lycoris_FKeys(x,y);
                if (!isFKey)
                {
                    for (uint8_t i = 0; i < 6; i++)
                    {
                        if (keyBuffer[i].keyCode == Lycoris_usageIdArray[x][y])
                        {
                            ifUsageIdExist = true;
                            break;
                        }
                    }
                    if (!ifUsageIdExist)
                    {
                        for (uint8_t i = 0; i < 6; i++)
                        {
                            if (keyBuffer[i].keyCode == 0x00)
                            {
                                keyBuffer[i].keyCode = Lycoris_usageIdArray[x][y];
                                keyBuffer[i].x = x;
                                keyBuffer[i].y = y;
                                break;
                            }
                        }
                    }
                    else
                    {
                        ifUsageIdExist = false;
                    }
                    isFKey = true; // 优先判定控制功能键
                }
            }
        }
    }

    for (uint8_t i = 0; i < 6; i++)
    {
        Lycoris_Report[2 + i] = keyBuffer[i].keyCode;
    }
    Lycoris_Report[0] = FKEYByte;

    return;
}

void Lycoris_FKeys(uint8_t x, uint8_t y)
{
    if (Lycoris_keyNameArray[x][y] == "LCtrl")
    {
        FKEYByte = FKEYByte | (0x01 << 0);
    }
    else if (Lycoris_keyNameArray[x][y] == "LShift")
    {
        FKEYByte = FKEYByte | (0x01 << 1);
    }
    else if (Lycoris_keyNameArray[x][y] == "LAlt")
    {
        FKEYByte = FKEYByte | (0x01 << 2);
    }
    else if (Lycoris_keyNameArray[x][y] == "LOpt")
    {
        FKEYByte = FKEYByte | (0x01 << 3);
    }
    else if (Lycoris_keyNameArray[x][y] == "RCtrl")
    {
        FKEYByte = FKEYByte | (0x01 << 4);
    }
    else if (Lycoris_keyNameArray[x][y] == "RShift")
    {
        FKEYByte = FKEYByte | (0x01 << 5);
    }
    else if (Lycoris_keyNameArray[x][y] == "AltGr")
    {
        FKEYByte = FKEYByte | (0x01 << 6);
    }
    else if (Lycoris_keyNameArray[x][y] == "ROpt")
    {
        FKEYByte = FKEYByte | (0x01 << 7);
    }else{
        isFKey = false;
    }
    return;
}
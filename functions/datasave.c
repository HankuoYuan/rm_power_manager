//
// Created by Lao·Zhu on 2021/4/6.
//

#include "main.h"

unsigned char Reset_Number = 0;

void vApplicationStackOverflowHook(TaskHandle_t xTask, char *pcTaskName) {
    DataSave_To_Flash(StackOverflow_Reset);
}

void DataSave_To_Flash(Saving_Reason_e reason) {
    unsigned char Buffer[16];
    Buffer[0] = (reason & 0x07) << 5;
    Buffer[0] |= (FSM_Status.Charge_Mode & 0x07) << 2;
    Buffer[0] |= FSM_Status.Typology_Mode & 0x03;
    Buffer[1] = (FSM_Status.Expect_Mode & 0x07) << 5;
    Buffer[1] |= (FSM_Status.FSM_Mode & 0x07) << 2;
    Buffer[1] |= Reset_Number & 0x03;
    Buffer[2] = FloatToInt16(I_Capacitor) >> 8;
    Buffer[3] = FloatToInt16(I_Capacitor) & 0x00ff;
    Buffer[4] = FloatToInt16(I_Chassis) >> 8;
    Buffer[5] = FloatToInt16(I_Chassis) & 0x00ff;
    Buffer[6] = FloatToInt16(V_Capacitor) >> 8;
    Buffer[7] = FloatToInt16(V_Capacitor) & 0x00ff;
    Buffer[8] = FloatToInt16(V_Chassis) >> 8;
    Buffer[9] = FloatToInt16(V_Chassis) & 0x00ff;
    Buffer[10] = FloatToInt16(V_Baterry) >> 8;
    Buffer[11] = FloatToInt16(V_Baterry) & 0x00ff;
    Buffer[12] = referee_data_.game_robot_status_.chassis_power_limit;
    Buffer[13] = FloatToInt16(referee_data_.power_heat_data_.chassis_power) >> 8;
    Buffer[14] = FloatToInt16(referee_data_.power_heat_data_.chassis_power) & 0x00ff;
    Buffer[15] = ((HAL_GPIO_ReadPin(EN_NMOS_GPIO_Port, EN_NMOS_Pin) & 0x01) << 7)
        | ((HAL_GPIO_ReadPin(CHG_EN_GPIO_Port, CHG_EN_Pin) & 0x01) << 6)
        | ((HAL_GPIO_ReadPin(BOOST_EN_GPIO_Port, BOOST_EN_Pin) & 0x01) << 5);
    for (unsigned char counter = 0; counter < 16; counter++)
        CurrentFile_Structure->ResetInfo[counter] = Buffer[counter];
    FileSystem_WriteIntoFlash();
    GUI_Clear(C_WHITE);
    switch (reason) {
        case RePowerOn_Reset:GUI_Printf(4, 4, C_BLACK, C_WHITE, "Repoweron Reset");
            break;
        case Watchdog_Reset:GUI_Printf(4, 4, C_BLACK, C_WHITE, "WatchDog Reset");
            break;
        case Hardfault_Reset:GUI_Printf(4, 4, C_BLACK, C_WHITE, "HardFault Reset");
            break;
        case UsageFault_Reset:GUI_Printf(4, 4, C_BLACK, C_WHITE, "UsageFault Reset");
            break;
        case BusFault_Reset:GUI_Printf(4, 4, C_BLACK, C_WHITE, "BusFault Reset");
            break;
        case NMI_Reset:GUI_Printf(4, 4, C_BLACK, C_WHITE, "NMI Reset");
            break;
        case StackOverflow_Reset:GUI_Printf(4, 4, C_BLACK, C_WHITE, "Stack Overflow Reset");
            break;
        default:break;
    }
    for (unsigned char counter = 0; counter < 50; counter++) {
        HAL_Delay(20);
        HAL_WWDG_Refresh(&hwwdg1);
    }
}

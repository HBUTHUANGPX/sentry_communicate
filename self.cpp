#include "crc8.h"
#include "crc16.h"
#include "self.h"

left_c_board_euler_data_t left_c_board_euler_data;
right_c_board_euler_data_t right_c_board_euler_data;
PC_auto_aim_control_data_t PC_auto_aim_control_data;
PC_nav_control_data_t PC_nav_control_data;
PC_nav_zero_OPS_data_t PC_nav_zero_OPS_data;
A_board_OPS_data_t A_board_OPS_data;



uint8_t get_Datalength_By_CmdId(uint8_t cmd_id)
{
    switch (cmd_id)
    {
    case 0x01:
        return (uint8_t)13;
    case 0x02:
        return (uint8_t)100;//待定
    case 0x03:
        return (uint8_t)12;
    case 0x04:
        return (uint8_t)12;
    case 0x05:
        return (uint8_t)1;
    case 0x21:
        return (uint8_t)12;
    case 0x31:
        return (uint8_t)12;
    default:
        return (uint8_t)0;
    }
}

uint8_t *getDataPointerById(uint8_t cmd_id)
{
    switch (cmd_id)
    {
    case 0x01:
        return (uint8_t *)&PC_auto_aim_control_data;
    case 0x02:
        return (uint8_t *)NULL;//待定
    case 0x03:
        return (uint8_t *)&PC_nav_control_data;
    case 0x04:
        return (uint8_t *)&A_board_OPS_data;
    case 0x05:
        return (uint8_t *)&PC_nav_zero_OPS_data;
    case 0x21:
        return (uint8_t *)&left_c_board_euler_data;
    case 0x31:
        return (uint8_t *)&right_c_board_euler_data;
    default:
        return NULL;
    }
}
void parse(uint8_t *head, int size)
{
    uint8_t *pos = head;
    int step = 0;

    while (step < size)
    {
        if (*pos != 0xA5)
        {
            pos++;
            step++;
            continue;
        }
        if (*(pos + 3) == Get_CRC8_Check_Sum_UI(pos, 3, 0xFF))
        {
            uint16_t cmd_id = *(uint16_t *)(pos + 2);
            uint16_t data_length = get_Datalength_By_CmdId(cmd_id);
            if (size - step >= data_length && *(uint16_t *)(pos + 4 + data_length) == Get_CRC16_Check_Sum_UI(pos, 4 + data_length, 0xFFFF))
            {
                memcpy(getDataPointerById(cmd_id), pos + 7, data_length);
                pos += 7 + data_length;
                step += 7 + data_length;
                continue;
            }
        }
        step++;
        pos++;
    }

}
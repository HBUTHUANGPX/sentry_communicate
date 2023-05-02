#ifndef __SELF_H
#define __SELF_H
#pragma pack(1)
#include "stdint.h"
#include <string.h>
typedef struct _frame_Head //帧头 4字节
{
    uint8_t 	SOF;                        //SOF码0xA5
    uint8_t 	Data_Length;               	//数据包长度 
    uint8_t 	cmd_id;                     //cmd_id命令码ID
    uint8_t 	CRC8;                   	//CRC8校验码
} frame_Head_t;
#pragma pack()


#pragma pack(1)
typedef struct _left_c_board_euler_data // 12字节
{
    float euler[3];
}left_c_board_euler_data_t;
#pragma pack()

#pragma pack(1)
typedef struct _right_c_board_euler_data // 12字节
{
    float euler[3];
}right_c_board_euler_data_t;
#pragma pack()

#pragma pack(1)
typedef struct _PC_auto_aim_control_data // 12字节
{
    float first_yaw;
    float second_yaw;
    float pitch;
    uint8_t shoot;
}PC_auto_aim_control_data_t;
#pragma pack()

#pragma pack(1)
typedef struct _PC_nav_control_data // 12字节
{
    float v_x;
    float v_y;
    float w_z;
}PC_nav_control_data_t;
#pragma pack()

#pragma pack(1)
typedef struct _PC_nav_zero_OPS_data // 12字节
{
    uint8_t flag;
}PC_nav_zero_OPS_data_t;
#pragma pack()

#pragma pack(1)
typedef struct _A_board_OPS_data // 12字节
{
    float move_x;
    float move_y;
    float angle_z;
}A_board_OPS_data_t;
#pragma pack()


#pragma pack(1)
typedef struct _self_data // 30字节
{

}self_data_t;
#pragma pack()

#pragma pack(1)
typedef struct _communicate //自定义数据             6+n字节
{
    frame_Head_t frame_Head; // 帧头                   4字节
    self_data_t self_data;   // 自定义数据             n字节
    uint16_t CRC16;        // CRC16校验码            2字节
}communicate_t;
#pragma pack()
#pragma pack(1)
union CP_send_data
{
  communicate_t communicate;
  uint8_t c[39];
};
#pragma pack()
#endif
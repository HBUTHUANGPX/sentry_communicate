# sentry_communicate
哨兵多设备通讯方案：
C板、A板、PC_导航、PC_自瞄 使用串口通讯，电气标准为RS485
使用总线通讯的方式，无主从机。
通信协议模仿裁判系统，但不一样，示例见附件。

串口配置：
配置波特率4000000，8 位数据位，1 位停止位，无硬件流控，无校验位。
接口协议说明：

通信协议格式
||||
| ----  | ----  | ---- | 
|frame_header(字节)|data(n-byte)|frame_tail(2-byte,CRC16)

Frame_header格式
|SOF|Data_length|Cmd_id|CRC-8|
| ----  | ----  | ---- | ---- |
|0XA5,1-byte|n,1-byte|命令码,1-byte|CRC-8,1-byte|

cmd_id 命令码 ID 说明
|Cmd_id|Data_length|功能||
| ----  | ----  | ---- | ---- |
|0x21|12|左C板imu发出的欧拉角|PC_自瞄收|
|0x31|12|右C板imu发出的欧拉角|PC_自瞄收|
|0x01|13|PC_自瞄 控制一级yaw、二级yaw、pitch、发射使能|C_板收|
|0x02|待定|A板发出关于裁判系统的信息，PC_自瞄、PC_导航收|PC_自瞄、PC_导航收|
|0x03|12|PC_导航 控制底盘的运动，v_x,v_y,w_z|A板收|
|0x04|12|A板发出关于OPS的信息|PC_导航收|
|0x05|1|PC_导航 向A板发送一个标志，用于对ops清零|A板收|
			

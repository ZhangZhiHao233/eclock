/********************************************************************************** 
    功能:         包含必要头文件，宏定义，位定义，以及变量和函数的声明 
***********************************************************************************/  
#include"STC15W4K.h"  
#define uint unsigned int  
#define uchar unsigned char  
  
//on_off的状态值，表示电子密码的状态  
#define FLAG_OFF              0           //关闭  
#define FLAG_ON               1                     //打开  
#define FLAG_SETTING        2                       //设置  
  
//nset状态值，表示是否处于重置状态  
#define FLAG_RESET_ON   1                       //重置  
#define FLAG_RESET_OFF  0                       //非重置  
  
//key的几个特殊值  
#define KEY_BORDER          0x0a        //键值边界，密码数字不超过9  
#define KEY_ENSURE          0x0c                //关闭  
#define KEY_RESET       0x0d                //重置  
  
  
//按键的位定义  
sbit L1 = P1^0;                                           
sbit L2 = P1^1;  
sbit L3 = P1^2;  
sbit L4 = P1^3;  
  
//led以及蜂鸣器定义,test用作测试  
sbit LED_ON  = P3^2;  
sbit LED_OFF = P3^3;  
sbit LED_SET = P3^4;  
sbit test    = P3^5;  
sbit fmq     = P3^6;   
sbit led         = P5^5;  
  
  
//全局声明变量  
extern uchar key_times;  
extern uchar nset;  
extern uchar on_off;  
extern uchar i,j,temp;  
extern uchar key;  
extern uchar key_delay;  
  
//函数声明  
void delayms(uint xms);  
void scankey();  
void led_change(uchar option);  
bit judge();  
void init();  
void scomm();  
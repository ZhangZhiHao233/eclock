/********************************************************************************** 
    ����:         ������Ҫͷ�ļ����궨�壬λ���壬�Լ������ͺ��������� 
***********************************************************************************/  
#include"STC15W4K.h"  
#define uint unsigned int  
#define uchar unsigned char  
  
//on_off��״ֵ̬����ʾ���������״̬  
#define FLAG_OFF              0           //�ر�  
#define FLAG_ON               1                     //��  
#define FLAG_SETTING        2                       //����  
  
//nset״ֵ̬����ʾ�Ƿ�������״̬  
#define FLAG_RESET_ON   1                       //����  
#define FLAG_RESET_OFF  0                       //������  
  
//key�ļ�������ֵ  
#define KEY_BORDER          0x0a        //��ֵ�߽磬�������ֲ�����9  
#define KEY_ENSURE          0x0c                //�ر�  
#define KEY_RESET       0x0d                //����  
  
  
//������λ����  
sbit L1 = P1^0;                                           
sbit L2 = P1^1;  
sbit L3 = P1^2;  
sbit L4 = P1^3;  
  
//led�Լ�����������,test��������  
sbit LED_ON  = P3^2;  
sbit LED_OFF = P3^3;  
sbit LED_SET = P3^4;  
sbit test    = P3^5;  
sbit fmq     = P3^6;   
sbit led         = P5^5;  
  
  
//ȫ����������  
extern uchar key_times;  
extern uchar nset;  
extern uchar on_off;  
extern uchar i,j,temp;  
extern uchar key;  
extern uchar key_delay;  
  
//��������  
void delayms(uint xms);  
void scankey();  
void led_change(uchar option);  
bit judge();  
void init();  
void scomm();  
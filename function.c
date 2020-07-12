#include "function.h"  
  
//保存当前密码，输入密码  
uchar password[] = {0x01,0x01,0x01,0x01,0x01,0x01};  
uchar input[] = {0xff,0xff,0xff,0xff,0xff,0xff};  
  
  
/********************************************************************************** 
    功能:         延时，最小单位为ms(晶振为11.0592 
    计算方法：一个for循环 = 8个指令周期 = 8*12个机器周期 = 8*12*1/11.0592 = 0.0086ms 
                        xms = 0.0086 * 110 = 0.946 ms 
***********************************************************************************/  
void delayms(uint xms)  
{  
    uint i,j;  
    for(i=xms;i>0;i--)             
        for(j=110;j>0;j--);  
}  
  
  
/********************************************************************************** 
    功能:         改变几个led的状态 
***********************************************************************************/  
void led_change(uchar option)  
{  
    if(option == 0)      //关闭状态  
    {   
        LED_ON = 1;  
        LED_OFF = 0;  
        LED_SET = 1;  
    }  
    else if(option == 1) //打开状态  
    {  
        LED_ON = 0;  
        LED_OFF = 1;  
        LED_SET = 1;  
    }  
    else if(option == 2) //设置状态  
    {  
        LED_ON = 1;  
        LED_OFF = 1;  
        LED_SET = 0;  
    }  
}  
  
  
/********************************************************************************** 
    功能:         扫描按键得出键值 
    方法：     先扫行，再扫列 
***********************************************************************************/  
void scankey()  
{  
        P1  = 0xef;  
      //key = 0xff;  
        for(i=0;i<4;i++)  
      {   
        if(L1==0)  
            {  
                delayms(key_delay);  
                if(L1==0)  
                    key = i*4+0;   
                if(key < KEY_BORDER && on_off != FLAG_ON)//开锁后按键不计数  
                    key_times = key_times+1;  
            }  
            if(L2==0)  
            {     
                delayms(key_delay);  
                if(L2==0)  
                    key = i*4+1;    
                if(key < KEY_BORDER && on_off != FLAG_ON)  
                    key_times = key_times+1;  
            }  
            if(L3==0 && on_off != FLAG_ON)  
            {  
                delayms(key_delay);  
                if(L3==0)  
                    key = i*4+2;  
                if(key < KEY_BORDER)  
                    key_times = key_times+1;  
            }  
            if(L4==0 && on_off != FLAG_ON)  
            {  
                 delayms(key_delay);  
                 if(L4==0)  
                     key = i*4+3;   
                 if(key < KEY_BORDER)  
                    key_times = key_times+1;  
            }  
              
            delayms(5);                 //准备下一次扫描的时间间隔  
            temp=P1;  
            temp=temp|0x0f;  
            temp=temp<<1;  
            temp=temp|0x0f;  
            P1=temp;   
      }  
          
        //扫描后判断键值  
        switch(key)  
        {  
            case    KEY_ENSURE:  
            {  
                led_change(0);      //改变灯的状态  
                key_times = 0;  
                on_off = FLAG_OFF;//定义宏  
            }  
            break;  
            case  KEY_RESET:  
            {  
                if(on_off == FLAG_ON)  
                {  
                    led_change(2);  
                    key_times = 0;  
                    on_off = FLAG_SETTING;  
                    nset = FLAG_RESET_ON;  
                }  
                else if(on_off == FLAG_OFF)  
                {  
                    fmq = 0;  
                    delayms(10);  
                    fmq = 1;  
                    key = 0x00;         //防止在此处循环  
                }  
            }  
            break;  
            default:break;  
        }  
}  
  
  
/********************************************************************************** 
    功能:         判断密码是否符合设置密码，以及重置新密码 
***********************************************************************************/  
bit judge()  
{  
     if(nset == FLAG_RESET_OFF)  //默认状态下  
     {  
         //test密码输入后可以进入  
         switch(key_times)  
         {  
            case 1:input[0] = key;break;  
            case 2:input[1] = key;break;  
            case 3:input[2] = key;break;  
            case 4:input[3] = key;break;  
            case 5:input[4] = key;break;  
            case 6:input[5] = key;break;  
            default:break;  
         }  
           
     }  
     if(nset == FLAG_RESET_ON) //重置状态下，替换旧密码同时打开锁  
     {  
            switch(key_times)  
          {  
            case 1:password[0] = key;input[0] = key;break;  
            case 2:password[1] = key;input[1] = key;break;  
            case 3:password[2] = key;input[2] = key;break;  
            case 4:password[3] = key;input[3] = key;break;  
            case 5:password[4] = key;input[4] = key;break;  
            case 6:password[5] = key;input[5] = key;break;  
            default:break;  
          }  
     }  
       
       
       
    if(key_times == 6)  
    {  
        if(nset == FLAG_RESET_ON )  
            nset = FLAG_RESET_OFF;  
        key_times = 0;  
        for(j=0;j<6;j++)  
        {  
            if(password[j] != input[j]) //报警  
            {  
                LED_ON = 1;  
                fmq = 0;  
                delayms(30);  
                LED_OFF = ~LED_OFF;  
                delayms(30);  
                LED_OFF = ~LED_OFF;  
                delayms(30);  
                LED_OFF = ~LED_OFF;  
                delayms(30);  
                LED_OFF = ~LED_OFF;  
                fmq = 1;  
                return 0;  
            }  
        }  
        on_off = FLAG_ON;  
        scomm();  
        return 1;  
    }  
    return 0;  
}  
  
  
/********************************************************************************** 
    功能:         初始化，包括对led，定时器,串口的初始化 
***********************************************************************************/  
void init()  
{  
    led_change(0);  
    fmq = 0;  
    delayms(20);  
    fmq = 1;  
      
    P1M0 = 0;P1M1 = 0;        
    SCON = 0x40;                      
    T2L = 0xe0;         //定时器2作为波特率发生器  
    T2H = 0xfe;  
    AUXR = 0x14;  
    AUXR |= 0x01;  
    TI = 1;  
}  
  
  
/********************************************************************************** 
    功能:         发送单片机信息，一次七个字节,其中首字节为状态，其余六字节为当前密码 
***********************************************************************************/  
void scomm()  
{  
    uchar i;  
    SBUF = on_off;   
    while(TI == 0);  
    TI = 0;  
      
    for(i=0;i<6;i++)  
    {  
		delayms(1000);
        while(TI == 0);  
        {  
            TI = 0;  
            SBUF = password[i];  
        }  
    }  
}  
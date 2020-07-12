#include "function.h"  
  
//���浱ǰ���룬��������  
uchar password[] = {0x01,0x01,0x01,0x01,0x01,0x01};  
uchar input[] = {0xff,0xff,0xff,0xff,0xff,0xff};  
  
  
/********************************************************************************** 
    ����:         ��ʱ����С��λΪms(����Ϊ11.0592 
    ���㷽����һ��forѭ�� = 8��ָ������ = 8*12���������� = 8*12*1/11.0592 = 0.0086ms 
                        xms = 0.0086 * 110 = 0.946 ms 
***********************************************************************************/  
void delayms(uint xms)  
{  
    uint i,j;  
    for(i=xms;i>0;i--)             
        for(j=110;j>0;j--);  
}  
  
  
/********************************************************************************** 
    ����:         �ı伸��led��״̬ 
***********************************************************************************/  
void led_change(uchar option)  
{  
    if(option == 0)      //�ر�״̬  
    {   
        LED_ON = 1;  
        LED_OFF = 0;  
        LED_SET = 1;  
    }  
    else if(option == 1) //��״̬  
    {  
        LED_ON = 0;  
        LED_OFF = 1;  
        LED_SET = 1;  
    }  
    else if(option == 2) //����״̬  
    {  
        LED_ON = 1;  
        LED_OFF = 1;  
        LED_SET = 0;  
    }  
}  
  
  
/********************************************************************************** 
    ����:         ɨ�谴���ó���ֵ 
    ������     ��ɨ�У���ɨ�� 
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
                if(key < KEY_BORDER && on_off != FLAG_ON)//�����󰴼�������  
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
              
            delayms(5);                 //׼����һ��ɨ���ʱ����  
            temp=P1;  
            temp=temp|0x0f;  
            temp=temp<<1;  
            temp=temp|0x0f;  
            P1=temp;   
      }  
          
        //ɨ����жϼ�ֵ  
        switch(key)  
        {  
            case    KEY_ENSURE:  
            {  
                led_change(0);      //�ı�Ƶ�״̬  
                key_times = 0;  
                on_off = FLAG_OFF;//�����  
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
                    key = 0x00;         //��ֹ�ڴ˴�ѭ��  
                }  
            }  
            break;  
            default:break;  
        }  
}  
  
  
/********************************************************************************** 
    ����:         �ж������Ƿ�����������룬�Լ����������� 
***********************************************************************************/  
bit judge()  
{  
     if(nset == FLAG_RESET_OFF)  //Ĭ��״̬��  
     {  
         //test�����������Խ���  
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
     if(nset == FLAG_RESET_ON) //����״̬�£��滻������ͬʱ����  
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
            if(password[j] != input[j]) //����  
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
    ����:         ��ʼ����������led����ʱ��,���ڵĳ�ʼ�� 
***********************************************************************************/  
void init()  
{  
    led_change(0);  
    fmq = 0;  
    delayms(20);  
    fmq = 1;  
      
    P1M0 = 0;P1M1 = 0;        
    SCON = 0x40;                      
    T2L = 0xe0;         //��ʱ��2��Ϊ�����ʷ�����  
    T2H = 0xfe;  
    AUXR = 0x14;  
    AUXR |= 0x01;  
    TI = 1;  
}  
  
  
/********************************************************************************** 
    ����:         ���͵�Ƭ����Ϣ��һ���߸��ֽ�,�������ֽ�Ϊ״̬���������ֽ�Ϊ��ǰ���� 
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
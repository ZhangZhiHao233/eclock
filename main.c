/******************************************************************************************** 
    File name:              ���������� 
    Main fouction:          ��λ���뿪�������������ù��ܣ�����ʵʱ��Ϣ���͵���λ�� 
    Last modified Date:     2017-10-22 
    Created by:             zzh 
	Steps for test          1 ����ԭʼ����111111�����Ƿ�� 
                            2 �����������Ƿ�ر� 
                            3 ��ʱ����������룬���Ƿ񱨾� 
                            4 ��ʱ���裬��δ�������Ƿ񱨾� 
                            5 ������ȷ���룬��ʱ���裬���������룬��ʱӦ���ֽ���״̬ 
                            6 ���������������� 
                            7 �ظ�2~6 
*********************************************************************************************/  
#include "function.h"  
  
//������ʼ��  
uchar key_times = 0;  
uchar nset = FLAG_RESET_OFF;  
uchar on_off = FLAG_OFF;  
uchar i,j,temp;  
uchar key = 0xff;  
uchar key_delay = 5;  
  
void main()  
{  
  init();  
      
    while(1)  
    {  
        scankey();  
          
        if(judge() == 1)  
        {  
            led_change(1);  
            on_off = FLAG_ON;  
        }  
        if(key_times > 6)   
            key_times = 0;  
    }  
}  
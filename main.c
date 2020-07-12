/******************************************************************************************** 
    File name:              电子密码锁 
    Main fouction:          六位密码开解锁，包含重置功能，并将实时信息发送到上位机 
    Last modified Date:     2017-10-22 
    Created by:             zzh 
	Steps for test          1 输入原始密码111111，看是否打开 
                            2 再锁定，看是否关闭 
                            3 此时输入错误密码，看是否报警 
                            4 此时重设，因未解锁看是否报警 
                            5 输入正确密码，此时重设，输入新密码，此时应保持解锁状态 
                            6 关锁，输入新密码 
                            7 重复2~6 
*********************************************************************************************/  
#include "function.h"  
  
//变量初始化  
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
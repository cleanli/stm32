#include "common.h"  
#include "usb_lib.h"
#include "hw_config.h"
#include "usb_pwr.h"
#include "usb_bot.h"  
#include "mass_mal.h"

u8 Data_Buffer[BULK_MAX_PACKET_SIZE*2*4];	//为USB数据缓存区申请内存
u8 Bulk_Data_Buff[BULK_MAX_PACKET_SIZE];	//申请内存
int usb_main_init(void)
{ 
	u8 offline_cnt=0;
	u8 tct=0;
	u8 USB_STA;
	u8 Divece_STA; 
    memset(Data_Buffer, 0, BULK_MAX_PACKET_SIZE*2*4);
    memset(Bulk_Data_Buff, 0, BULK_MAX_PACKET_SIZE);
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//中断分组设置	 
    SD_Init();
    Mass_Memory_Size[0]=(long long)SD_GetSectorCount()*512;
    Mass_Block_Size[0] =512;
    Mass_Block_Count[0]=Mass_Memory_Size[0]/Mass_Block_Size[0];
	
 	USB_Port_Set(0); 	//USB先断开
	delay_ms(300);
   	USB_Port_Set(1);	//USB再次连接   
 	//USB配置
 	USB_Interrupts_Config();    
 	Set_USBClock();   
 	USB_Init();	    
	delay_ms(1800);	   	    
#if 0
	while(1)
	{	
		delay_ms(1);				  
		if(USB_STA!=USB_STATUS_REG)//状态改变了 
		{	 						   
			LCD_Fill(60,190,240,190+16,WHITE);//清除显示			  	   
			if(USB_STATUS_REG&0x01)//正在写		  
			{
				LCD_ShowString(60,190,200,16,16,"USB Writing...");//提示USB正在写入数据	 
			}
			if(USB_STATUS_REG&0x02)//正在读
			{
				LCD_ShowString(60,190,200,16,16,"USB Reading...");//提示USB正在读出数据  		 
			}	 										  
			if(USB_STATUS_REG&0x04)LCD_ShowString(60,210,200,16,16,"USB Write Err ");//提示写入错误
			else LCD_Fill(60,210,240,210+16,WHITE);//清除显示	  
			if(USB_STATUS_REG&0x08)LCD_ShowString(60,230,200,16,16,"USB Read  Err ");//提示读出错误
			else LCD_Fill(60,230,240,230+16,WHITE);//清除显示    
			USB_STA=USB_STATUS_REG;//记录最后的状态
		}
		if(Divece_STA!=bDeviceState) 
		{
			if(bDeviceState==CONFIGURED)LCD_ShowString(60,170,200,16,16,"USB Connected    ");//提示USB连接已经建立
			else LCD_ShowString(60,170,200,16,16,"USB DisConnected ");//提示USB被拔出了
			Divece_STA=bDeviceState;
		}
		tct++;
		if(tct==200)
		{
			tct=0;
			LED0=!LED0;//提示系统在运行
			if(USB_STATUS_REG&0x10)
			{
				offline_cnt=0;//USB连接了,则清除offline计数器
				bDeviceState=CONFIGURED;
			}else//没有得到轮询 
			{
				offline_cnt++;  
				if(offline_cnt>10)bDeviceState=UNCONNECTED;//2s内没收到在线标记,代表USB被拔出了
			}
			USB_STATUS_REG=0;
		}
	};  										    			    
#endif
}








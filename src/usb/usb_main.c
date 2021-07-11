#include "common.h"  
#include "usb_lib.h"
#include "hw_config.h"
#include "usb_pwr.h"
#include "usb_bot.h"  
#include "mass_mal.h"

//uint32_t usb_writable = 0;
u8 Data_Buffer[BULK_MAX_PACKET_SIZE*2*4];	//ΪUSB���ݻ����������ڴ�
extern u8 Bulk_Data_Buff[BULK_MAX_PACKET_SIZE];	//�����ڴ�
void usb_main_init(uint32_t flag)
{ 
	u8 offline_cnt=0;
	u8 tct=0, retry = 3;
	u8 USB_STA;
	u8 Divece_STA; 
    SD_Error sd_ret = SD_RESPONSE_FAILURE;
    //usb_writable = flag;
    if(usb_writable==0){
        lprintf("usb readonly\n");
    }
    else{
        lprintf("usb writable\n");
    }
    memset(Data_Buffer, 0, BULK_MAX_PACKET_SIZE*2*4);
    memset(Bulk_Data_Buff, 0, BULK_MAX_PACKET_SIZE);
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�жϷ�������	 
    while(SD_RESPONSE_NO_ERROR!=sd_ret && retry--){
        sd_ret = SD_Init();
        lprintf("sd init return %d retry %d\n", sd_ret, retry);
    }
    if(SD_RESPONSE_NO_ERROR!=sd_ret){
        lprintf("SD card init error: usb storage init fail!\n");
        return;
    }
    Mass_Block_Count[0]=SD_GetSectorCount();
    if(0 == Mass_Block_Count[0]){
        lprintf("SD card secotr count error: usb storage init fail!\n");
        return;
    }
    Mass_Block_Size[0] =512;
    Mass_Memory_Size[0]=(uint64_t)Mass_Block_Count[0]*Mass_Block_Size[0];
    lprintf("SD: total %U Bytes, %d sectors, %d bytes/sector\n",
            Mass_Memory_Size[0], Mass_Block_Count[0], Mass_Block_Size[0]);
    lprintf("HEX result:total 0x%W Bytes, 0x%x sectors, 0x%x bytes/sector\n",
            Mass_Memory_Size[0], Mass_Block_Count[0], Mass_Block_Size[0]);
	
 	USB_Port_Set(0); 	//USB�ȶϿ�
	delay_ms(300);
   	USB_Port_Set(1);	//USB�ٴ�����   
 	//USB����
 	USB_Interrupts_Config();    
 	Set_USBClock();   
 	USB_Init();	    
	delay_ms(1800);	   	    
    return;
#if 0
	while(1)
	{	
		delay_ms(1);				  
		if(USB_STA!=USB_STATUS_REG)//״̬�ı��� 
		{	 						   
			LCD_Fill(60,190,240,190+16,WHITE);//�����ʾ			  	   
			if(USB_STATUS_REG&0x01)//����д		  
			{
				LCD_ShowString(60,190,200,16,16,"USB Writing...");//��ʾUSB����д������	 
			}
			if(USB_STATUS_REG&0x02)//���ڶ�
			{
				LCD_ShowString(60,190,200,16,16,"USB Reading...");//��ʾUSB���ڶ�������  		 
			}	 										  
			if(USB_STATUS_REG&0x04)LCD_ShowString(60,210,200,16,16,"USB Write Err ");//��ʾд�����
			else LCD_Fill(60,210,240,210+16,WHITE);//�����ʾ	  
			if(USB_STATUS_REG&0x08)LCD_ShowString(60,230,200,16,16,"USB Read  Err ");//��ʾ��������
			else LCD_Fill(60,230,240,230+16,WHITE);//�����ʾ    
			USB_STA=USB_STATUS_REG;//��¼����״̬
		}
		if(Divece_STA!=bDeviceState) 
		{
			if(bDeviceState==CONFIGURED)LCD_ShowString(60,170,200,16,16,"USB Connected    ");//��ʾUSB�����Ѿ�����
			else LCD_ShowString(60,170,200,16,16,"USB DisConnected ");//��ʾUSB���γ���
			Divece_STA=bDeviceState;
		}
		tct++;
		if(tct==200)
		{
			tct=0;
			LED0=!LED0;//��ʾϵͳ������
			if(USB_STATUS_REG&0x10)
			{
				offline_cnt=0;//USB������,�����offline������
				bDeviceState=CONFIGURED;
			}else//û�еõ���ѯ 
			{
				offline_cnt++;  
				if(offline_cnt>10)bDeviceState=UNCONNECTED;//2s��û�յ����߱��,����USB���γ���
			}
			USB_STATUS_REG=0;
		}
	};  										    			    
#endif
}








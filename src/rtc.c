#include "common.h"
#include "rtc.h"

#define uchar unsigned char

uchar g8563_Store[6]; /*ʱ�佻����,ȫ�ֱ�������*/
uchar c8563_Store[6]={0x13,0x09,0x22,0x10,0x40,0x00}; /*д��ʱ���ֵ������һ 07:59:00*/

void SDA_set_input(uint8_t en);
/********************************************
  �ڲ���������ʱ1
 ********************************************/
void Delay()
{
    delay_us(10);
}
/********************************************
  �ڲ�������I2C��ʼ
 ********************************************/
void Start()
{ 
    SDA_HIGH;
    SCL_HIGH;
    Delay();
    SDA_LOW;
    Delay();
    SCL_LOW;
}
/********************************************
  �ڲ�������I2C����
 ********************************************/
void Stop()
{
    SDA_LOW;
    SCL_LOW;
    Delay();
    SCL_HIGH;
    Delay();
    SDA_HIGH;
    Delay();
}
/********************************************
  �ڲ����������ACK ,ÿ���ֽڴ�����ɣ����ack=0,��������ݣ�ack=1;
 ********************************************/
void WriteACK(uchar ack)
{
    if(ack)SDA_HIGH;
    else SDA_LOW;
    Delay();
    SCL_HIGH;
    Delay();
    SCL_LOW;
}
/********************************************
  �ڲ��������ȴ�ACK
 ********************************************/
void WaitACK()
{  
    uchar errtime=20;
    SDA_HIGH;
    Delay(); /*��ACK*/
    SCL_HIGH;
    Delay();
    SDA_set_input(1);
    while(GET_SDA)
    {  
        errtime--;
        if(!errtime){
            lprintf("wait ack timeout\n");
            Stop();
        }
    }
    SCL_LOW;
    Delay();
    SDA_set_input(0);
}
/********************************************
  �ڲ�����.��������ֽ�
  ���:B=����
 ********************************************/
void writebyte(uchar wdata)
{
    uchar i;
    lprintf("i2c write=%x\n", wdata);
    for(i=0;i<8;i++)
    {
        if(wdata&0x80) 
            SDA_HIGH;
        else 
            SDA_LOW;
        wdata<<=1;
        SCL_HIGH;
        Delay();
        SCL_LOW;
    }
    WaitACK();     //I2C������ͨѶ���������˳�I2CͨѶ
}
/********************************************
  �ڲ�����.��������
  ����:B
 ********************************************/
uchar Readbyte()
{
    uchar i,bytedata;
    SDA_HIGH;
    SDA_set_input(1);
    for(i=0;i<8;i++)
    {
        SCL_HIGH; 
        bytedata<<=1;
        bytedata|=GET_SDA;
        SCL_LOW;
        Delay();
    }
    SDA_set_input(0);
    lprintf("i2c read=%x\n", bytedata);
    return(bytedata);
}
/********************************************
  �������->pcf8563
 ********************************************/
void writeData(uchar address,uchar mdata)
{
    Start();
    writebyte(0xa2); /*д����*/
    writebyte(address); /*д��ַ*/
    writebyte(mdata); /*д����*/
    Stop();
}
/********************************************
  ��������<-pcf8563
 ********************************************/
/*uchar ReadData(uchar address) //���ֽ�
  {  
  uchar rdata;
  Start();
  writebyte(0xa2); //д����
  writebyte(address); //д��ַ
  Start();
  writebyte(0xa3); //������
  rdata=Readbyte();
  WriteACK(1);
  Stop();
  return(rdata);
  }	*/
void ReadData1(uchar address,uchar count,uchar * buff) /*���ֽ�*/
{  
    uchar i;
    Start();
    writebyte(0xa2); /*д����*/
    writebyte(address); /*д��ַ*/
    Start();
    writebyte(0xa3); /*������*/
    for(i=0;i<count;i++)
    {
        buff[i]=Readbyte();
        if(i<count-1) 
            WriteACK(0);
    }
    WriteACK(1);
    Stop();
}  
/********************************************
  �ڲ�����,����ʱ�䵽�ڲ�������
 ********************************************/
void P8563_Read(uint8_t*ip)
{   
    uchar time[7];
    uchar ict=7;
    ReadData1(0x02,0x07,time);
    ip[0]=time[0]&0x7f; /*�� */
    ip[1]=time[1]&0x7f; /*�� */
    ip[2]=time[2]&0x3f; /*Сʱ */
    ip[3]=time[3]&0x3f; /*�� */
    ip[4]=time[4]&0x07; /*week */
    ip[5]=time[5]&0x9f; /*�� */
    ip[6]=time[6]; /*��  */

    while(ict--){
        lprintf("ip[%d]=%x\n", ict, ip[ict]);
    }
}
/********************************************
  ����ʱ�䵽�ڲ�������----�ⲿ���� 
 ********************************************/
void P8563_gettime(uint8_t*ip)
{
    P8563_Read(ip);
    if(ip[0]==0)
        P8563_Read(ip); /*���Ϊ��=0��Ϊ��ֹʱ��仯���ٶ�һ��*/
}	
/********************************************
  дʱ���޸�ֵ
 ********************************************/
void P8563_settime(uint8_t*ip)
{
    //uchar i;
    writeData(8,ip[0]); //�� 
    writeData(7,ip[1]); //�� 
    writeData(5,ip[2]); //�� 
    writeData(4,ip[3]); //ʱ 
    writeData(3,ip[4]); //��  
    writeData(2,ip[5]); //�� 
    delay_ms(1000);
    //P8563_gettime(g8563_Store);
}

void SDA_set_input(uint8_t en)
{
    GPIO_InitTypeDef GPIO_InitStructure;	//GPIO

    GPIO_InitStructure.GPIO_Pin = SDA_PIN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        if(en){
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU ;  //��������
            GPIO_Init(SDA_GG, &GPIO_InitStructure);
        }
        else{
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  //������� 
            GPIO_Init(SDA_GG, &GPIO_InitStructure);
        }
    GPIO_SetBits(SDA_GG, SDA_PIN);	
}

/********************************************
  P8563�ĳ�ʼ��-----�ⲿ����
 ********************************************/
void P8563_init()
{
    //uchar i;


    GPIO_InitTypeDef GPIO_InitStructure;	//GPIO
    
        //ע��,ʱ��ʹ��֮��,��GPIO�Ĳ�������Ч
        //��������֮ǰ,����ʹ��ʱ��.����ʵ���������������
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
        
        GPIO_InitStructure.GPIO_Pin = SDA_PIN|SCL_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  //������� 
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_Init(GPIOB, &GPIO_InitStructure);
    GPIO_SetBits(GPIOB,SDA_PIN|SCL_PIN);
    
        // P8563_settime();
#if 0
        for(i=0;i<=5;i++) g8563_Store[i]=c8563_Store[i]; /*��ʼ��ʱ��*/
    P8563_settime();  
#endif
    // if((ReadData(0x0a)&0x3f)!=0x08) /*����Ƿ��һ�������������ʼ��ʱ��*/
    // {
    //	    P3_4 = 0;
    //       for(i=0;i<=3;i++) g8563_Store[i]=c8563_Store[i]; /*��ʼ��ʱ��*/
    //       P8563_settime();
    //       writeData(0x0,0x00);
    //       writeData(0xa,0x8); /*8:00����*/
    //       writeData(0x1,0x12); /*������Ч*/
    //      writeData(0xd,0xf0);  //������32.768K��Ƶ��
    //  }
}
void rtc_write(uint8_t*ip)
{
    P8563_init();
    P8563_settime(ip);
}
void rtc_read(uint8_t*ip)
{
    P8563_init();
    P8563_gettime(ip);
}
static char t_d[24];
char* get_rtc_time()
{
    uint8_t time_date[7];
    rtc_read(time_date);
    memset(t_d, 0, 24);
    if(time_date[5] & 0x80){
        t_d[0] = '1';
        t_d[1] = '9';
    }
    else{
        t_d[0] = '2';
        t_d[1] = '0';
    }
    slprintf(&t_d[2], "%b.%b.%b W%x %b:%b:%b",
            time_date[6], time_date[5]&0x1f, time_date[3],
            time_date[4], time_date[2],
            time_date[1], time_date[0]);
    lprintf("%s\n", t_d);
    return t_d;
}
uint8_t rtc_read_reg(uint8_t addr)
{
    uint8_t ret;
    ReadData1(addr,1,&ret);
    return ret;
}

void rtc_write_reg(uint8_t addr, uint8_t data)
{
    writeData(addr,data);
}

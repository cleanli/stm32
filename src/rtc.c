#include "common.h"
#include "rtc.h"

#define uchar unsigned char

uchar g8563_Store[6]; /*时间交换区,全局变量声明*/
uchar c8563_Store[6]={0x13,0x09,0x22,0x10,0x40,0x00}; /*写入时间初值：星期一 07:59:00*/

/********************************************
  内部函数，延时1
 ********************************************/
void Delay()
{
    delay_us(10);
}
/********************************************
  内部函数，I2C开始
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
  内部函数，I2C结束
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
  内部函数，输出ACK ,每个字节传输完成，输出ack=0,结束读书据，ack=1;
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
  内部函数，等待ACK
 ********************************************/
void WaitACK()
{  
    uchar errtime=20;
    SDA_HIGH;
    Delay(); /*读ACK*/
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
  内部函数.输出数据字节
  入口:B=数据
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
    WaitACK();     //I2C器件或通讯出错，将会退出I2C通讯
}
/********************************************
  内部函数.输入数据
  出口:B
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
  输出数据->pcf8563
 ********************************************/
void writeData(uchar address,uchar mdata)
{
    Start();
    writebyte(0xa2); /*写命令*/
    writebyte(address); /*写地址*/
    writebyte(mdata); /*写数据*/
    Stop();
}
/********************************************
  输入数据<-pcf8563
 ********************************************/
/*uchar ReadData(uchar address) //单字节
  {  
  uchar rdata;
  Start();
  writebyte(0xa2); //写命令
  writebyte(address); //写地址
  Start();
  writebyte(0xa3); //读命令
  rdata=Readbyte();
  WriteACK(1);
  Stop();
  return(rdata);
  }	*/
void ReadData1(uchar address,uchar count,uchar * buff) /*多字节*/
{  
    uchar i;
    Start();
    writebyte(0xa2); /*写命令*/
    writebyte(address); /*写地址*/
    Start();
    writebyte(0xa3); /*读命令*/
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
  内部函数,读入时间到内部缓冲区
 ********************************************/
void P8563_Read()
{   
    uchar time[7];
    uchar ict=6;
    ReadData1(0x02,0x07,time);
    g8563_Store[0]=time[0]&0x7f; /*秒 */
    g8563_Store[1]=time[1]&0x7f; /*分 */
    g8563_Store[2]=time[2]&0x3f; /*小时 */
    g8563_Store[3]=time[3]&0x3f; /*日 */
    g8563_Store[4]=time[5]&0x1f; /*月 */
    g8563_Store[5]=time[6]; /*年  */

    while(ict--){
        lprintf("g8563_Store[%d]=%x\n", ict, g8563_Store[ict]);
    }
}
/********************************************
  读入时间到内部缓冲区----外部调用 
 ********************************************/
void P8563_gettime()
{
    P8563_Read();
    if(g8563_Store[0]==0)
        P8563_Read(); /*如果为秒=0，为防止时间变化，再读一次*/
}	
/********************************************
  写时间修改值
 ********************************************/
void P8563_settime()
{
    //uchar i;
    writeData(8,g8563_Store[0]); //年 
    writeData(7,g8563_Store[1]); //月 
    writeData(5,g8563_Store[2]); //日 
    writeData(4,g8563_Store[3]); //时 
    writeData(3,g8563_Store[4]); //分  
    writeData(2,g8563_Store[5]); //秒 
}

void SDA_set_input(uint32_t en)
{
    GPIO_InitTypeDef GPIO_InitStructure;	//GPIO

    GPIO_InitStructure.GPIO_Pin = SDA_PIN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        if(en){
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU ;  //上拉输入
            GPIO_Init(SDA_GG, &GPIO_InitStructure);
        }
        else{
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  //推挽输出 
            GPIO_Init(SDA_GG, &GPIO_InitStructure);
        }
    GPIO_SetBits(SDA_GG, SDA_PIN);	
}

/********************************************
  P8563的初始化-----外部调用
 ********************************************/
void P8563_init()
{
    uchar i;


    GPIO_InitTypeDef GPIO_InitStructure;	//GPIO
    
        //注意,时钟使能之后,对GPIO的操作才有效
        //所以上拉之前,必须使能时钟.才能实现真正的上拉输出
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
        
        GPIO_InitStructure.GPIO_Pin = SDA_PIN|SCL_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  //推挽输出 
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_Init(GPIOB, &GPIO_InitStructure);
    GPIO_SetBits(GPIOB,SDA_PIN|SCL_PIN);
    
        // P8563_settime();
#if 0
        for(i=0;i<=5;i++) g8563_Store[i]=c8563_Store[i]; /*初始化时间*/
    P8563_settime();  
#endif
    // if((ReadData(0x0a)&0x3f)!=0x08) /*检查是否第一次启动，是则初始化时间*/
    // {
    //	    P3_4 = 0;
    //       for(i=0;i<=3;i++) g8563_Store[i]=c8563_Store[i]; /*初始化时间*/
    //       P8563_settime();
    //       writeData(0x0,0x00);
    //       writeData(0xa,0x8); /*8:00报警*/
    //       writeData(0x1,0x12); /*报警有效*/
    //      writeData(0xd,0xf0);  //编程输出32.768K的频率
    //  }
}
void rtc_test()
{
    P8563_init();
    P8563_gettime();
}

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
uint8_t WaitACK()
{  
    uint8_t ret = 1;
    uchar errtime=20;
    SDA_HIGH;
    Delay(); /*��ACK*/
    SDA_set_input(1);
    SCL_HIGH;
    Delay();
    while(GET_SDA)
    {  
        errtime--;
        if(!errtime){
            lprintf("wait ack timeout\n");
            ret = 0;
            break;
        }
    }
    SCL_LOW;
    Delay();
    SDA_set_input(0);
    return ret;
}
/********************************************
  �ڲ�����.��������ֽ�
  ���:B=����
 ********************************************/
uint8_t writebyte(uchar wdata)
{
    uchar i;
    //lprintf("i2c write=%x\n", wdata);
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
    return WaitACK();     //I2C������ͨѶ���������˳�I2CͨѶ
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
    //lprintf("i2c read=%x\n", bytedata);
    return(bytedata);
}
/********************************************
  �������->pcf8563
 ********************************************/
uint8_t writeData(uchar address,uchar mdata)
{
    uint8_t ret;
    Start();
    ret=writebyte(0xa2); /*д����*/
    if(ret==0)goto err;
    ret=writebyte(address); /*д��ַ*/
    if(ret==0)goto err;
    ret=writebyte(mdata); /*д����*/
    Stop();
    return ret;
err:
    Stop();
    lprintf("writeData addr %b data %b error\n", address, mdata);
    return ret;
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
uint8_t ReadData1(uchar address,uchar count,uchar * buff) /*���ֽ�*/
{  
    uint8_t ret;
    uchar i;
    Start();
    ret=writebyte(0xa2); /*д����*/
    if(ret==0)goto err;
    ret=writebyte(address); /*д��ַ*/
    if(ret==0)goto err;
    Start();
    ret=writebyte(0xa3); /*������*/
    if(ret==0)goto err;
    for(i=0;i<count;i++)
    {
        buff[i]=Readbyte();
        if(i<count-1) 
            WriteACK(0);
    }
    WriteACK(1);
err:
    Stop();
    return ret;
}  
/********************************************
  �ڲ�����,����ʱ�䵽�ڲ�������
 ********************************************/
uint8_t P8563_Read(uint8_t*ip)
{   
    uint8_t ret = 0, maxtry = 3;
    uchar time[7];
    //uchar ict=7;
    while(maxtry--){
        ret = ReadData1(0x02,0x07,time);
        if(ret)break;
    }
    if(!ret){
        lprintf("RTC read error\n");
        return ret;
    }
    ip[0]=time[0]&0x7f; /*�� */
    ip[1]=time[1]&0x7f; /*�� */
    ip[2]=time[2]&0x3f; /*Сʱ */
    ip[3]=time[3]&0x3f; /*�� */
    ip[4]=time[4]&0x07; /*week */
    ip[5]=time[5]&0x9f; /*�� */
    ip[6]=time[6]; /*��  */

#if 0
    while(ict--){
        lprintf("ip[%d]=%x\n", ict, ip[ict]);
    }
#endif
    return ret;
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
    rtc_write_reg(8,ip[0]); //�� 
    rtc_write_reg(7,ip[1]); //�� 
    rtc_write_reg(5,ip[2]); //�� 
    rtc_write_reg(4,ip[3]); //ʱ 
    rtc_write_reg(3,ip[4]); //��  
    rtc_write_reg(2,ip[5]); //�� 
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
    static int rtc_inited = 0;
    //uchar i;

    if(rtc_inited)return;

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
    lprintf("rtc reg0=%b\n", rtc_read_reg(0));
    lprintf("rtc reg1=%b\n", rtc_read_reg(1));
    rtc_write_reg(0x0,0x00);
    //       writeData(0xa,0x8); /*8:00����*/
    rtc_write_reg(0x1,0x12|rtc_read_reg(0x1)); /*������Ч*/
    //      writeData(0xd,0xf0);  //������32.768K��Ƶ��
    //  }
    rtc_inited = 1;
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
uint8_t hex2bcd(uint8_t ipt)
{
    return (ipt/10)*0x10 + (ipt%10);
}
uint8_t bcd2hex(uint8_t ipt)
{
    return ((ipt&0xf0)>>4)*10 + (ipt&0xf);
}
char* get_rtc_time(date_info_t*dit)
{
    uint8_t time_date[7];
    rtc_read(time_date);
    memset(t_d, 0, 24);
    if(time_date[5] & 0x80){
        t_d[0] = '1';
        t_d[1] = '9';
        if(dit!=0){
            dit->year = 1900 + bcd2hex(time_date[6]);
        }
    }
    else{
        t_d[0] = '2';
        t_d[1] = '0';
        if(dit!=0){
            dit->year = 2000 + bcd2hex(time_date[6]);
        }
    }
    slprintf(&t_d[2], "%b.%b.%b W%x %b:%b:%b",
            time_date[6], time_date[5]&0x1f, time_date[3],
            time_date[4], time_date[2],
            time_date[1], time_date[0]);
    if(dit!=0){
        dit->month = bcd2hex(time_date[5]&0x1f);
        dit->day = bcd2hex(time_date[3]);
        dit->weekday = time_date[4];
        dit->hour = bcd2hex(time_date[2]);
        dit->minute = bcd2hex(time_date[1]);
        dit->second = bcd2hex(time_date[0]);
#if 0
        lprintf("dit:%d.%d.%d %d:%d:%d week%d\n",
                (uint32_t)dit->year, (uint32_t)dit->month, (uint32_t)dit->day,
                (uint32_t)dit->hour, (uint32_t)dit->minute, (uint32_t)dit->second, (uint32_t)dit->weekday);
#endif
    }
    //lprintf("%s\n", t_d);
    return t_d;
}
uint8_t rtc_read_reg(uint8_t addr)
{
    uint8_t ret;
    ReadData1(addr,1,&ret);
    return ret;
}

uint8_t rtc_write_reg(uint8_t addr, uint8_t data)
{
    uint8_t ret = 0, maxtry = 3;
    while(maxtry--){
        ret = writeData(addr,data);
        if(ret)break;
    }
    return ret;
}

uint32_t diff_with_inc_step(uint32_t f, uint32_t b, uint32_t inc_step)
{
    return (f>=b)?f-b:f+inc_step-b;
}
uint8_t add_with_back_limit(uint8_t * iptp, uint32_t diff, uint8_t limit)
{
    uint8_t ret = 0;
    //lprintf("&&in %d %d %d\n", *iptp, diff, limit);
    uint32_t t = *iptp + diff;
    while(t>=limit){
        ret++;
        t-=limit;
    }
    *iptp = t;
    //lprintf("&&out %d %d\n", *iptp, ret);
    return ret;
}
uint32_t time_diff_seconds(date_info_t* dtp_f, date_info_t * dtp)
{
    uint32_t ret, h = dtp_f->hour, m  = dtp_f->minute;
    //lprintf("%d %d - %d %d\n", dtp_f->hour, dtp_f->minute,
    //        dtp->hour, dtp->minute);
    ret = diff_with_inc_step(dtp_f->second, dtp->second, 60);
    if(dtp_f->second < dtp->second){
        m = diff_with_inc_step(m, 1, 60);
    }
    ret += diff_with_inc_step(m, dtp->minute, 60)*60;
    if(dtp_f->minute < dtp->minute){
        h = diff_with_inc_step(h, 1, 24);
    }
    ret += diff_with_inc_step(h, dtp->hour, 24)*3600;
    //lprintf("ret %d\n", ret);
    return ret;
}
uint32_t time_diff_minutes(date_info_t* dtp_f, date_info_t * dtp)
{
    uint32_t ret, h = dtp_f->hour;
    //lprintf("%d %d - %d %d\n", dtp_f->hour, dtp_f->minute,
    //        dtp->hour, dtp->minute);
    ret = diff_with_inc_step(dtp_f->minute, dtp->minute, 60);
    if(dtp_f->minute < dtp->minute){
        h = diff_with_inc_step(h, 1, 24);
    }
    ret += diff_with_inc_step(h, dtp->hour, 24)*60;
    //lprintf("ret %d\n", ret);
    return ret;
}

void add_time_diff_minutes(date_info_t*dtp, uint32_t tsms)
{
    add_with_back_limit(&dtp->hour, add_with_back_limit(&dtp->minute, tsms, 60), 24);
}

void auto_time_alert_set(uint32_t time_step_minutes)
{
    date_info_t dt, dt_alt;
    uint32_t h, m;

    get_rtc_time(&dt);
    dt_alt.hour = bcd2hex(rtc_read_reg(0x0a));
    h = dt_alt.hour;
    dt_alt.minute = bcd2hex(rtc_read_reg(0x09));
    m = dt_alt.minute;
    while(time_diff_minutes(&dt_alt, &dt)>time_step_minutes)
    {
        add_time_diff_minutes(&dt_alt, time_step_minutes);
    }
    if(h != dt_alt.hour){
        rtc_write_reg(0x0a, hex2bcd(dt_alt.hour));
    }
    if(m != dt_alt.minute){
        rtc_write_reg(0x09, hex2bcd(dt_alt.minute));
    }
    lcd_lprintf(190, 150, "Next auto power on: %b:%b", hex2bcd(dt_alt.hour), hex2bcd(dt_alt.minute));
}

uint8_t check_rtc_alert_and_clear()
{
    uint8_t ret = 0, reg;
    reg = rtc_read_reg(1);
    lprintf("rtcreg1=%x\n", reg);
    ret = reg&0x08;
    if(ret){
        lprintf("rtc flag set found!!!!!!!!!\n");
        rtc_write_reg(1,0x12);//clear rtc int pin
    }
    return ret;
}

uint adjust_1min(uint faster_1min)
{
    uint8_t min = rtc_read_reg(MINUTE_REG);
    if(rtc_read_reg(SECOND_REG)>=58){
        return RTC_FAIL;
    }
    if((faster_1min && min == 59) ||
            (!faster_1min && min == 0)){
        return RTC_FAIL;
    }
    faster_1min?min++:min--;
    return rtc_write_reg(MINUTE_REG, min);
}

void clear_second()
{
    rtc_write_reg(SECOND_REG, 0);
}

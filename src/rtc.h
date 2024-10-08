#ifndef _RTC_H
#define _RTC_H
#include "date.h"

extern int use_SCL_1;

#define SDA_HIGH GPIO_WriteBit(SDA_GG, SDA_PIN, 1)
#define SCL_HIGH GPIO_WriteBit(SCL_GG, SCL_PIN, 1)
#define SDA_LOW GPIO_WriteBit(SDA_GG, SDA_PIN, 0)
#define SCL_LOW GPIO_WriteBit(SCL_GG, SCL_PIN, 0)
#define GET_SDA GPIO_ReadInputDataBit(SDA_GG, SDA_PIN)

#define AUTO_TIME_ALERT_INC_MINS (60*6)

#define MINUTE_REG 3
#define SECOND_REG 2

#define RTC_FAIL 0
#define RTC_OK 1

void P8563_init();
void rtc_read(uint8_t*);
void rtc_write(uint8_t*);
char* get_rtc_time(date_info_t*);
uint8_t rtc_read_reg(uint8_t addr);
uint8_t rtc_write_reg(uint8_t addr, uint8_t data);
void auto_time_alert_set(uint32_t time_step_minutes, int show_x, int show_y);
int32_t get_t_t_n_c();
uint8_t check_rtc_alert_and_clear();
uint adjust_1min(uint faster_1min);
void clear_second();
uint8_t hex2bcd(uint8_t ipt);
uint8_t bcd2hex(uint8_t ipt);
uint32_t bcd2hex_32(uint32_t ipt);
void get_date(date_info_t*dit);
void rtc_dump_regs();
void do_time_correct();

#endif

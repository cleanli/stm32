#ifndef __LPRINTF_H
#define __LPRINTF_H
#include<stdint.h>
#include "task.h"

int __io_putchar(int ch);
uint16_t __io_getchar();
int __io_char_received();

extern uint16_t LCD_PRINT_BACK_COLOR;
extern uint16_t LCD_PRINT_FRONT_COLOR;
void lprintf(const char *fmt, ...);
void lprintf_time(const char *fmt, ...);
void lprintf_to(const char *fmt, ...);
void slprintf(char*buf, const char *fmt, ...);
void lcd_lprintf(uint32_t x, uint32_t y, const char *fmt, ...);
void lcd_lprintf_win(uint32_t x, uint32_t y, uint32_t w, uint32_t h, const char *fmt, ...);
void mem_print(const char*buf, uint32_t ct_start, uint32_t len);
void task_log(struct task*vp);
void foce_save_log_func();
void puthexch(char c);
void reset_time_offset();
void syshour_init();

#endif

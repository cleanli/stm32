#include "lprintf.h"
#include <stdint.h>
#include <stdarg.h>
#include <string.h>
#include "common.h"
#include "os_task.h"

#define LOG_BUF_SIZE 1024
char log_buf[LOG_BUF_SIZE];
static u32 write_index = 0;
static u32 read_index = 0;
char buf_printf_buf[64];
char debug_log_buf[DEBUG_LOG_BUF_SIZE+1];
char lprintf_buf[256];
char lcdprintf_buf[256];
DECLARE_OS_LOCK(oslk_timebuf, LPRINTF_TIMEBUF_LOCK);
DECLARE_OS_LOCK(oslk_lprintf, LPRINTF_LOCK);
DECLARE_OS_LOCK(oslk_mempt, MEM_PRINT_LOCK);
DECLARE_OS_LOCK(oslk_log, LOG_LOCK_NO);
DECLARE_OS_LOCK(oslk_lcdpt, LCD_PRINT_LOCK_NO);
char halfbyte2char(char c)
{
        return ((c & 0x0f) < 0x0a)?(0x30 + c):('A' + c - 0x0a);
}

void puthexch(char c)
{
    __io_putchar(halfbyte2char(c>>4));
    __io_putchar(halfbyte2char(c&0xf));
}

void put_hex_uint(uint32_t i)
{
    int c = 8;
    while(c--){
        __io_putchar(halfbyte2char((char)((i&0xf0000000)>>28)));
        i<<=4;
    }
}

int sput_hex_uint8(char*s, uint32_t i)
{
    int c = 2;
    char* p = s;
    while(c--){
        *p++ = (halfbyte2char((char)((i&0xf0)>>4)));
        i<<=4;
    }
    return 2;
}

int sput_hex_uint(char*s, uint32_t i)
{
    int c = 8;
    char* p = s;
    while(c--){
        *p++ = (halfbyte2char((char)((i&0xf0000000)>>28)));
        i<<=4;
    }
    return 8;
}

int sput_hex_uint64(char*s, uint64_t i)
{
    int c = 16;
    char* p = s;
    while(c--){
        *p++ = (halfbyte2char((char)((i&0xf000000000000000)>>60)));
        i<<=4;
    }
    return 16;
}

void puthexchars(char *pt)
{
    while(*pt){
        puthexch(*pt++);
        __io_putchar(' ');
    }
}

void putchars(const char *pt)
{
    while(*pt)
        __io_putchar(*pt++);
}

char * num2str(uint64_t jt, char * s, char n)
{
        char * st, k = 1, j;
        uint64_t tmp;

        st = s;
        if(n > 16 || n < 2){
                *st++ = 0x30;
                *st = 0;
                return s;
        }
        tmp = 1;
        while(jt/tmp >= n){
                k++;
                tmp *= n;
        }

        while(k--){
                j = jt/tmp;
                *st++ = halfbyte2char(j);
                jt -= tmp * j;
                tmp = tmp/n;
        }
        *st = 0;
        return s;
}

void print_uint(uint32_t num)
{
        char nc[11];
        num2str(num, nc, 10);
        putchars(nc);
}

int sprint_uint64(char*s, uint64_t num)
{
    char nc[21];
    memset(nc, 0, 21);
    num2str(num, nc, 10);
    strcpy(s, nc);
    return strlen(nc);
}

int sprint_uint(char*s, uint32_t num)
{
    char nc[11];
    num2str(num, nc, 10);
    strcpy(s, nc);
    return strlen(nc);
}

int sprint_uint_0n(char*s, uint32_t num, uint32_t num_len)
{
    char nc[22];
    uint32_t raw_len;
    memset(nc,'0', 22);
    raw_len = sprint_uint(nc+11, num);
    strcpy(s, nc+11+raw_len-num_len);
    return strlen(nc+11+raw_len-num_len);
}

void print_hex(uint32_t num)
{
        char nc[9];
        num2str(num, nc, 16);
        putchars(nc);
}

int sprint_hex(char*s, uint32_t num)
{
    char nc[9];
    num2str(num, nc, 16);
    strcpy(s, nc);
    return strlen(nc);
}

void print_binary(uint32_t num)
{
        char nc[33];
        num2str(num, nc, 2);
        putchars(nc);
}
char sys_hour[14];
static u32 date_hour_offset = 0xffffffff;
void reset_time_offset()
{
    date_hour_offset = 0xffffffff;
}
char*get_sys_hour()
{
    u32 ms_time;
    u32 t;//tmp variable
    if(date_hour_offset == 0xffffffff){
        date_info_t cur_date = {0};
        get_date(&cur_date);
        ms_time = (u32)(get_system_us()/1000);
        date_hour_offset = cur_date.second;
        date_hour_offset += cur_date.minute*60;
        date_hour_offset += cur_date.hour*3600;
        date_hour_offset *= 1000;
        date_hour_offset -= ms_time;
    }
    ms_time = (u32)(get_system_us()/1000);
    if(date_hour_offset != 0xffffffff){
        ms_time+=date_hour_offset;
    }
    t = ms_time/3600/1000;
    t %= 24;
    sprint_uint_0n(&sys_hour[0], t, 2);
    sys_hour[2]=':';
    t = ms_time/60/1000;
    t %= 60;
    sprint_uint_0n(&sys_hour[3], t, 2);
    sys_hour[5]=':';
    t = ms_time/1000;
    t %= 60;
    sprint_uint_0n(&sys_hour[6], t, 2);
    sys_hour[8]='.';
    t = ms_time%1000;
    sprint_uint_0n(&sys_hour[9], t, 3);
    sys_hour[12]=' ';
    sys_hour[13]=0;//last byte
    return sys_hour;
}

char*vslprintf(int print_with_time, char*s_buf, const char *fmt, va_list args)
{
    const char *s;
    uint32_t d;
    int32_t di;
    uint64_t u;
    va_list ap;
    char*sp = s_buf;

    if(print_with_time){
        s = get_sys_hour();
        strcpy(sp, s);
        sp += strlen(s);
    }
    va_copy(ap, args);
    while (*fmt) {
        if (*fmt != '%') {
            *sp++ = *fmt++;
            continue;
        }
        switch (*++fmt) {
	    case '%':
	        *sp++ = (*fmt);
		break;
            case 's':
                s = va_arg(ap, const char *);
                strcpy(sp, s);
                sp += strlen(s);
                break;
            case 'u':
                d = va_arg(ap, uint32_t);
                sp += sprint_uint(sp, d);
                break;
            case 'd':
                di = va_arg(ap, int32_t);
                if(di<0){
                    d=-di;
                    *sp++='-';
                }
                else{
                    d=di;
                }
                sp += sprint_uint(sp, d);
                break;
            case 'U':
                u = va_arg(ap, uint64_t);
                sp += sprint_uint64(sp, u);
                break;
	    case 'c':
                d = va_arg(ap, uint32_t);
                *sp++ = d&0xff;
                break;
	    case 'x':
                d = va_arg(ap, uint32_t);
                sp += sprint_hex(sp, d);
                break;
	    case 'W':
                u = va_arg(ap, uint64_t);
                sp += sput_hex_uint64(sp, u);
                break;
	    case 'X':
                d = va_arg(ap, uint32_t);
                sp += sput_hex_uint(sp, d);
                break;
	    case 'b':
                d = va_arg(ap, uint32_t);
                sp += sput_hex_uint8(sp, d);
                break;
            /* Add other specifiers here... */             
            default: 
                *sp++ = (*(fmt-1));
                *sp++ = (*fmt);
                break;
        }
        fmt++;
    }
    *sp = 0;
    va_end(ap);
    return sp;
}

#define SIZE_OF_START_WRITE_FLASH 128
u32 get_log_size()
{
    u32 ret;
    os_lock(&oslk_log);
    if(read_index<=write_index){
        ret = write_index - read_index;
    }
    else{
        ret = LOG_BUF_SIZE - read_index + write_index;
    }
    os_unlock(&oslk_log);
    return ret;
}
static int force_save_log = 0;
void set_save_log_flag()
{
    force_save_log = 1;
}

void foce_save_log_func()
{
    u32 log_size, wi;
    log_size = get_log_size();
    wi = write_index;
    log_to_flash(log_buf, read_index, log_size, LOG_BUF_SIZE);
    os_lock(&oslk_log);
    read_index =  wi;
    os_unlock(&oslk_log);
}

os_task_st * log_wait_task = NULL;
void os_task_log(void*p)
{
    u32 log_size=0, wi, irqsv;
    (void)p;

    while(1){
        while(1){
            log_size = get_log_size();
            if(0 == log_size){
                dis_irq_save(irqsv);
                log_wait_task = cur_os_task;
                cur_os_task->task_status = TASK_STATUS_SLEEPING_IDLE;
                irq_restore(irqsv);
                os_switch_trigger();
            }
            else{
                break;
            }
        }
        wi = write_index;
        log_to_flash(log_buf, read_index, log_size, LOG_BUF_SIZE);
        os_lock(&oslk_log);
        read_index =  wi;
        os_unlock(&oslk_log);
    }
}

void task_log(struct task*vp)
{
    u32 log_size, wi;
    (void)vp;

    log_size = get_log_size();
    if(0 == log_size){
        return;
    }
    wi = write_index;
    log_to_flash(log_buf, read_index, log_size, LOG_BUF_SIZE);
    read_index =  wi;
}

#define HINT_LOG_LOST "#LOST#\n"
#define HINT_LOG_LOST_LEN (strlen(HINT_LOG_LOST))
void log_to_buf(char* log)
{
    u32 free_log_size, len, log_to_end_size, w_len;
    if(LOG_BUF_SIZE-1 == get_log_size()){
        lprintf("log buf full, log lost\n");
        return;
    }
    len = strlen(log);
    free_log_size = LOG_BUF_SIZE - 1 - get_log_size() - HINT_LOG_LOST_LEN;
    if(free_log_size<len){
        lprintf("err:%d bytes log lost\n", len-free_log_size);
        slprintf(log+free_log_size, HINT_LOG_LOST);
        len = free_log_size+HINT_LOG_LOST_LEN;
    }
    //if(free_log_size>len)
    {
        log_to_end_size = LOG_BUF_SIZE - write_index;
        while(1){
            if(log_to_end_size < len){
                w_len = log_to_end_size;
            }
            else{
                w_len = len;
            }
            memcpy(&log_buf[write_index], log, w_len);
            os_lock(&oslk_log);
            write_index = add_with_limit(write_index, w_len, LOG_BUF_SIZE);
            os_unlock(&oslk_log);
            log+=w_len;
            len-=w_len;
            if(0==len){
                return;
            }
        }
    }
}

void buf_log(const char* log)
{
    static u32 w_p = 0;
    u32 len, w_len, buf_left;
    len = strlen(log);
    while(len){
        buf_left=DEBUG_LOG_BUF_SIZE-w_p;
        if(buf_left>=len){
            w_len=len;
        }
        else{
            w_len=buf_left;
        }
        memcpy(&debug_log_buf[w_p], log, w_len);
        w_p= add_with_limit(w_p, w_len, DEBUG_LOG_BUF_SIZE);
        len-=w_len;
        log+=w_len;
    }
}

void lprintf_time_buf(u32 time, const char *fmt, ...)
{
    va_list ap;
    u32 flag;
    char*sp=buf_printf_buf;
    if(debug_mode)return;
    dis_irq_save(flag);
    u32 us = get_system_us();

    //os_lock(&oslk_timebuf);
    va_start(ap,fmt);

    if(time){
        sp += sprint_uint(sp, us/1000000);
        *sp++ = '.';
        sp += sprint_uint_0n(sp, us%1000000, 6);
        *sp++ = ':';
    }
    vslprintf(0, sp,fmt,ap);
    buf_log(buf_printf_buf);
    va_end(ap);
    irq_restore(flag);
    //os_unlock(&oslk_timebuf);
}

void putchars_buf(const char *s)
{
    u32 flag;
    if(debug_mode)return;
    dis_irq_save(flag);
    buf_log(s);
    irq_restore(flag);
}

#if 1
void lprintf_time(const char *fmt, ...)
{
    va_list ap;

    os_lock(&oslk_lprintf);
    va_start(ap,fmt);
#ifdef NO_PRINT_WITH_TIME
    vslprintf(0, lprintf_buf,fmt,ap);
#else
    vslprintf(1, lprintf_buf,fmt,ap);
#endif
    putchars(lprintf_buf);
    log_to_buf(lprintf_buf);
    va_end(ap);
}
#endif

void lprintf(const char *fmt, ...)
{
#if 1
    va_list ap;

    os_lock(&oslk_lprintf);
    va_start(ap,fmt);
    vslprintf(0, lprintf_buf,fmt,ap);
    putchars(lprintf_buf);
    va_end(ap);
    putchars_buf(fmt);
    os_unlock(&oslk_lprintf);
#else
    putchars(fmt);
#endif
}

void slprintf(char*buf, const char *fmt, ...)
{
    va_list ap;
    va_start(ap,fmt);
    vslprintf(0, buf,fmt,ap);
    va_end(ap);
}
uint16_t LCD_PRINT_BACK_COLOR = WHITE;
uint16_t LCD_PRINT_FRONT_COLOR = BLACK;
void lcd_lprintf_win(uint32_t chscale, uint32_t x, uint32_t y, uint32_t w, uint32_t h, const char *fmt, ...)
{
    va_list ap;
    os_lock(&oslk_lcdpt);
    memset(lcdprintf_buf, 0, sizeof(lcdprintf_buf));
    va_start(ap,fmt);
    vslprintf(0, lcdprintf_buf,fmt,ap);
    va_end(ap);
    os_unlock(&oslk_lcdpt);
    Show_Str_win(x, y,LCD_PRINT_FRONT_COLOR,LCD_PRINT_BACK_COLOR,lcdprintf_buf,16,0, w, h, chscale);
}
void lcd_lprintf(uint32_t chscale, uint32_t x, uint32_t y, const char *fmt, ...)
{
    va_list ap;
    os_lock(&oslk_lcdpt);
    memset(lcdprintf_buf, 0, sizeof(lcdprintf_buf));
    va_start(ap,fmt);
    vslprintf(0, lcdprintf_buf,fmt,ap);
    va_end(ap);
    Show_Str(x, y,LCD_PRINT_FRONT_COLOR,LCD_PRINT_BACK_COLOR,lcdprintf_buf,16,0, chscale);
    os_unlock(&oslk_lcdpt);
}

void mem_print(const char*buf, uint32_t ct_start, uint32_t len)
{
    const char*line_stt = buf;
    uint32_t left=len, line_len;

    os_lock(&oslk_mempt);
    putchars("\nMemShow Start:");
    while(left){
        int j, li;
        line_len = left>16?16:left;
        li=line_len;
        __io_putchar('\n');
        print_hex(ct_start);
        __io_putchar(':');
        __io_putchar(' ');
        j=0;
        while(li--){
            puthexch(line_stt[j]);
            __io_putchar(j == 7 ? '-':' ');
            j++;
        }
        li=line_len;
        j=0;
        __io_putchar(' ');
        while(li--){
            if(line_stt[j]>=0x20 && line_stt[j]<0x7f){
                __io_putchar(line_stt[j]);
            }
            else{
                __io_putchar('_');
            }
            j++;
        }
        left-=line_len;
        line_stt+=line_len;
        ct_start+=line_len;
    }
    lprintf("\nMemShow End:\n");
    os_unlock(&oslk_mempt);
}

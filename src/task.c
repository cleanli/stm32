#include <stdio.h>
#include <string.h>
#include "type.h"
#include "music.h"
#include "common.h"
#include "ui.h"
#include "task.h"

uint last_count_1s = 0;
uint last_count_10ms = 0;
uint count_1s=0;
uint count_10ms=0;
uint g_flag_1s ;
uint g_flag_10ms ;
bool music_flash = false;
bool cur_task_timer_started = false;
date_info_t g_cur_date = {0};
uint16_t touch_x;
uint16_t touch_y;
uint16_t cached_touch_x = 0;
uint16_t cached_touch_y = 0;
uint16_t draw_x = 0;
uint16_t draw_y = 0;
uint16_t touch_status = 0;
uint16_t last_touch_status = 0;
uint no_touch_down_ct = 0;
uint32_t cur_task_event_flag;
uint cur_task_timeout_ct;
uint default_music_note_period = DEFAULT_MUSIC_NOTE_PERIOD;
struct delay_work_info delayed_works[]={
    {
        NULL,
        0,
        NULL
    },
    {
        NULL,
        0,
        NULL
    }
};
#define NUMBER_OF_DELAYED_WORKS \
    (sizeof(delayed_works)/sizeof(struct delay_work_info))

#if 0
void local_float_sprintf(struct s_lfs_data* lfsd)
{
    if(lfsd->fv > 65535){
        strcpy(lfsd->buf, "oo");
        return;
    }
    uint tmp_int = lfsd->fv;
    sprintf(lfsd->buf, "%u", tmp_int);
    uint8 tmp=strlen(lfsd->buf);
    if(tmp<lfsd->number_int){
        memset(lfsd->buf, '0', lfsd->number_int);
        sprintf(lfsd->buf+lfsd->number_int-tmp, "%u", tmp_int);
    }
    float decimal = lfsd->fv - tmp_int + 1;
    uint8 n_dec=lfsd->number_decimal;
    while(n_dec--)decimal*=10;
    tmp_int=decimal;
    tmp=strlen(lfsd->buf);
    sprintf(lfsd->buf+tmp, "%u", tmp_int);
    lfsd->buf[tmp]='.';
    if(lfsd->follows){
        strcat(lfsd->buf, lfsd->follows);
    }
}

void time_hms(char*buf, uint t)
{
    uint h, m, tm, s;

    h = t / 3600;
    tm = t - h * 3600;
    m = tm / 60;
    s = tm - m * 60;
    sprintf(buf, "%02u:%02u:%02u", h, m, s);
}
#endif

void task_key_status(struct task*vp)
{
    vp;//fix unused variable warning
}

void task_lcd_bklight(struct task*vp)
{
    vp;//fix unused variable warning
}

void delayed_close_led(void*p)
{
    uint led_cmd = (uint)p;
    led_raw_set(led_cmd);
}

void flash_led(uint8 led_cmd, uint mss)
{
    led_raw_set(led_cmd);
    set_delayed_work(mss, delayed_close_led, (void*)(led_cmd&(LED_Y_C|LED_R_C)));
}

void task_power(struct task*vp)
{
    vp;
    if(g_flag_1s){
        adc_test();
        flash_led(LED_Y_C|LED_Y_1, 20);
    }
}

void task_timer(struct task*vp)
{
    vp;//fix unused variable warning
    g_flag_1s = false;
    g_flag_10ms = false;
    uint64_t systime = get_system_us();
    count_1s = systime/1000000;
    count_10ms = (systime - 1000000*count_1s)/10000;
    if(count_10ms != last_count_10ms){
        g_flag_10ms = true;
    }
    if(count_1s != last_count_1s){
        char*date = get_rtc_time(&g_cur_date);
        g_flag_1s = true;
        lcd_lprintf(0,0,date);
        //lprintf("task timect %u\r\n", cur_task_timeout_ct);
        if(cur_task_timeout_ct > 0 && (current_ui->time_disp_mode & TIME_OUT_EN)){
            if(cur_task_timer_started){
                cur_task_timeout_ct--;
                if(cur_task_timeout_ct == 0){
                    cur_task_event_flag |= 1<<EVENT_UI_TIMEOUT;
                }
            }
#if 0
            if(current_ui->time_disp_mode & TIME_DISP_EN){
                uint tmp_ct;
                if(current_ui->time_disp_mode & TIME_DISP_LEFT){
                    tmp_ct = cur_task_timeout_ct;
                }
                else{
                    tmp_ct = current_ui->timeout - cur_task_timeout_ct;
                }
                if(current_ui->time_disp_mode & TIME_DISP_SECOND){
                    sprintf(disp_mem+current_ui->time_position_of_dispmem,
                            "%u", tmp_ct);
                }
                else{
                    time_hms(disp_mem+current_ui->time_position_of_dispmem, tmp_ct);
                }
                disp_mem_update = true;
            }
#endif
        }
    }
    last_count_1s = count_1s;
    last_count_10ms = count_10ms;
}

void task_disp(struct task*vp)
{
    vp;//fix unused variable warning
}
void reset_music_note()
{
    music_note_task_play_info.music_note = 0;
    music_note_task_play_info.note_start_timerct = 0;
    music_note_task_play_info.period_ms_ct = 0;
}

bool is_music_idle()
{
    return (music_note_task_play_info.period_ms_ct == 0);
}

bool play_music_note(int8 note, uint period)
{
    if(music_note_task_play_info.period_ms_ct == 0){
        music_note_task_play_info.music_note = note;
        music_note_task_play_info.note_start_timerct = 0;
        music_note_task_play_info.period_ms_ct = period;
        return true;
    }
    return false;
}

void set_music_note_period(uint p)
{
    default_music_note_period = p;
}

bool is_playing_music()
{
    return (music_task_play_info.music_status == MUSIC_PLAYING);
}

void pause_music()
{
    if(music_task_play_info.music_status == MUSIC_PLAYING){
        beep_by_timer_100(0);
        music_task_play_info.music_status = MUSIC_PAUSE;
    }
}

void continue_music()
{
    if(music_task_play_info.music_status == MUSIC_PAUSE){
        music_task_play_info.music_status = MUSIC_PLAYING;
    }
}

void play_music( const signed char* pu, uint note_period)
{
    music_task_play_info.pu = pu;
    music_task_play_info.pu_index = 0;
    music_task_play_info.music_status = MUSIC_PLAYING;
    music_task_play_info.divert_index = NO_DIVERT;
    music_task_play_info.restart_index = 0;
    if(note_period == 0){
        note_period = DEFAULT_MUSIC_NOTE_PERIOD;
    }
    set_music_note_period(note_period);
}

void set_delayed_work(uint tct, func_p f, void*pa)
{
    for(uint i = 0; i<NUMBER_OF_DELAYED_WORKS; i++){
        if(delayed_works[i].function == NULL){
            delayed_works[i].function = f;
            delayed_works[i].ct_10ms = tct;
            delayed_works[i].para = pa;
            break;
        }
    }
}


void task_music(struct task*vp)
{
    vp;//fix unused variable warning
    int8 music_note;
    uint music_register_value;
    uint32_t timer_ct;
    if(music_task_play_info.pu != NULL &&
            music_task_play_info.music_status == MUSIC_PLAYING &&
            is_music_idle()){
        music_flash = !music_flash;
        //set_led1(music_flash);
        //set_led2(!music_flash);
        //lprintf("pu_index %u status %x\r\n", music_task_play_info.pu_index, music_task_play_info.music_status);
        music_note = music_task_play_info.pu[music_task_play_info.pu_index++];
        if(music_note==SCORE_END){
            music_task_play_info.music_status = MUSIC_END;
            cur_task_event_flag |= 1<<EVENT_MUSIC_PLAY_END;
            //set_led1(false);
            //set_led2(false);
            lprintf("play end\r\n");
            beep_by_timer_100(0);
            set_music_note_period(DEFAULT_MUSIC_NOTE_PERIOD);//recover default note period
        }
        else if(music_note==HALF_PERIOD){
            default_music_note_period /= 2;
        }
        else if(music_note==DOUBLE_PERIOD){
            default_music_note_period *= 2;
        }
        else if(music_note==DIVERT){
            if(music_task_play_info.divert_index != NO_DIVERT){
                music_task_play_info.pu_index = music_task_play_info.divert_index;
                music_task_play_info.divert_index = NO_DIVERT;
            }
        }
        else if(music_note==GOSTART){
                music_task_play_info.divert_index = music_task_play_info.pu_index;
                music_task_play_info.pu_index = music_task_play_info.restart_index;
        }
        else if(music_note==FLAGSTART){
            music_task_play_info.restart_index = music_task_play_info.pu_index;
        }
        else{
            play_music_note(music_note, default_music_note_period);
        }

    }

    if(music_note_task_play_info.period_ms_ct){
        timer_ct = get_system_us()/1000;//ms
        if(music_note_task_play_info.note_start_timerct == 0){
            music_note_task_play_info.note_start_timerct = timer_ct;
            if(music_note_task_play_info.music_note == 0){
                beep_by_timer_100(0);
            }
            else{
                music_register_value =
                    musical_scale_freq_100[get_note_index(music_note_task_play_info.music_note)];
                beep_by_timer_100(music_register_value);
            }
        }
        else if((timer_ct - music_note_task_play_info.note_start_timerct) >=
                (ulong)music_note_task_play_info.period_ms_ct){
            music_note_task_play_info.period_ms_ct = 0;
            if(!is_playing_music()){
                beep_by_timer_100(0);
            }
        }
    }
    else{
        beep_by_timer_100(0);
    }
}
void task_misc(struct task*vp)
{
    vp;//fix unused variable warning
    if(con_is_recved() && (con_recv() == 'c')){
        LCD_Clear(BLACK);	//fill all screen with some color
        lcd_lprintf(0,0,"CMD mode");
        run_cmd_interface();
        ui_start();
    }
#if 0
    if(!stop_feed_wtd){
        feed_watch_dog();
    }
#endif
    if(g_flag_10ms){
        for(uint8 i = 0; i<NUMBER_OF_DELAYED_WORKS; i++){
            if(delayed_works[i].ct_10ms > 0){
                delayed_works[i].ct_10ms--;
                if(delayed_works[i].ct_10ms==0 && delayed_works[i].function != NULL){
                    delayed_works[i].function(delayed_works[i].para);
                    delayed_works[i].function = NULL;
                }
            }
        }
    }
    //touch screen
    cached_touch_x = touch_x;
    cached_touch_y = touch_y;
    last_touch_status = touch_status;
    if(get_TP_point(&touch_x, &touch_y)){
        touch_status = 1;
        cur_task_event_flag |= 1<<EVENT_TOUCH_DOWN;
    }
    else{
        touch_status = 0;
        if(last_touch_status == 1){
            cur_task_event_flag |= 1<<EVENT_TOUCH_UP;
            TP_Draw_Big_Point(draw_x,draw_y,WHITE);
            TP_Draw_Big_Point(cached_touch_x,cached_touch_y,BLACK);
            draw_x = cached_touch_x;
            draw_y = cached_touch_y;
        }
    }
}
#include "display.h"
#include "common.h"
#include "ring_buf.h"

u16 PROXY_POINT_COLOR = 0x0000;
DECLARE_OS_LOCK(oslk_disp_para, DISP_RB_LOCK);
DECLARE_RB_DATA(disp_func_para, rb_disp_para, 2)

void draw_sq(int x1, int y1, int x2, int y2, int color);
void Proxy_draw_sq(int x1, int y1, int x2, int y2, int color)
{
    disp_func_para*rbdpp;

    os_lock(&oslk_disp_para);
    rbdpp=RB_W_GET_wait(disp_func_para, rb_disp_para);
    rbdpp->type = DISPFUNC_DRAW_SQ;
    rbdpp->draw_sq_para.color=color;
    rbdpp->draw_sq_para.x1=x1;
    rbdpp->draw_sq_para.y1=y1;
    rbdpp->draw_sq_para.x2=x2;
    rbdpp->draw_sq_para.y2=y2;
    RB_W_SET(disp_func_para, rb_disp_para);
    os_unlock(&oslk_disp_para);
}

void Proxy_LCD_DrawPoint(u16 x,u16 y)
{
    disp_func_para*rbdpp;

    os_lock(&oslk_disp_para);
    rbdpp=RB_W_GET_wait(disp_func_para, rb_disp_para);
    rbdpp->type = DISPFUNC_DRAW_POINT;
    rbdpp->draw_point_para.color=PROXY_POINT_COLOR;
    rbdpp->draw_point_para.x=x;
    rbdpp->draw_point_para.y=y;
    RB_W_SET(disp_func_para, rb_disp_para);
    os_unlock(&oslk_disp_para);
}

void Proxy_lcd_clr_window(u16 color, u16 xs, u16 ys, u16 xe, u16 ye)
{
    disp_func_para*rbdpp;

    os_lock(&oslk_disp_para);
    rbdpp=RB_W_GET_wait(disp_func_para, rb_disp_para);
    rbdpp->type = DISPFUNC_WIN_CLR;
    rbdpp->win_clr_para.color=color;
    rbdpp->win_clr_para.xs=xs;
    rbdpp->win_clr_para.ys=ys;
    rbdpp->win_clr_para.xe=xe;
    rbdpp->win_clr_para.ye=ye;
    RB_W_SET(disp_func_para, rb_disp_para);
    os_unlock(&oslk_disp_para);
}

const char* Proxy_Show_Str_win_raw(u32 *xp, u32 *yp, u32 fc, u32 bc, const char *str, u32 size, u32 mode, win_pt wd, int is_dummy)
{
    u32 xbak, ybak;
    const char* ret;
    disp_func_para*rbdpp;

    xbak = *xp;
    ybak = *yp;
    ret = Show_Str_win_raw(xp, yp, fc, bc, str, size, mode, wd, 1);
    if(is_dummy){
        return ret;
    }
    //do real display
    os_lock(&oslk_disp_para);
    rbdpp=RB_W_GET_wait(disp_func_para, rb_disp_para);
    rbdpp->type = DISPFUNC_WIN_STR;
    rbdpp->win_str_para.p_x=xbak;
    rbdpp->win_str_para.p_y=ybak;
    rbdpp->win_str_para.fc=fc;
    rbdpp->win_str_para.bc=bc;
    rbdpp->win_str_para.str=str;
    rbdpp->win_str_para.size=size;
    rbdpp->win_str_para.mode=mode;
    rbdpp->win_str_para.df_win=*wd;
    /*
    rbdpp->win_str_para->df_win.x=wd->x;
    rbdpp->win_str_para->df_win.y=wd->y;
    rbdpp->win_str_para->df_win.w=wd->w;
    rbdpp->win_str_para->df_win.h=wd->h;
    rbdpp->win_str_para->df_win.dx=wd->dx;
    rbdpp->win_str_para->df_win.dy=wd->dy;
    */
    RB_W_SET(disp_func_para, rb_disp_para);
    os_unlock(&oslk_disp_para);
    return ret;
}

void os_task_display(void*p)
{
    (void)p;
    disp_func_para*rbdpp;
    u32 *xp, *yp, fc, bc, size, mode;
    const char *str;
    win_pt wd;
    u16 color, xs, ys, xe, ye;
    while(1){
        rbdpp=RB_R_GET_wait(disp_func_para, rb_disp_para);
        switch(rbdpp->type){
            case DISPFUNC_WIN_STR:
                xp=&rbdpp->win_str_para.p_x;
                yp=&rbdpp->win_str_para.p_y;
                fc=rbdpp->win_str_para.fc;
                bc=rbdpp->win_str_para.bc;
                str=rbdpp->win_str_para.str;
                size=rbdpp->win_str_para.size;
                mode=rbdpp->win_str_para.mode;
                wd=&rbdpp->win_str_para.df_win;
                Show_Str_win_raw(xp, yp, fc, bc, str, size, mode, wd, 0);
                break;
            case DISPFUNC_WIN_CLR:
                color=rbdpp->win_clr_para.color=color;
                xs=rbdpp->win_clr_para.xs;
                ys=rbdpp->win_clr_para.ys;
                xe=rbdpp->win_clr_para.xe;
                ye=rbdpp->win_clr_para.ye;
                lcd_clr_window(color, xs, ys, xe, ye);
                break;
            case DISPFUNC_DRAW_POINT:
                POINT_COLOR=rbdpp->draw_point_para.color;
                xs=rbdpp->draw_point_para.x;
                ys=rbdpp->draw_point_para.y;
                LCD_DrawPoint(xs,ys);
                break;
            case DISPFUNC_DRAW_SQ:
                color=rbdpp->draw_sq_para.color;
                xs=rbdpp->draw_sq_para.x1;
                ys=rbdpp->draw_sq_para.y1;
                xe=rbdpp->draw_sq_para.x2;
                ye=rbdpp->draw_sq_para.y2;
                draw_sq(xs, ys, xe, ye, color);
                break;
            default:
                lprintf("unknow dispfunc type %d\n", rbdpp->type);
        };
        RB_R_SET(disp_func_para, rb_disp_para);
    }
}

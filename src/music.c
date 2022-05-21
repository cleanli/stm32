#include <stdio.h>
#include <string.h>
#include <limits.h>
#include "type.h"
#include "common.h"
#include "music.h"

struct music_note_play_info music_note_task_play_info={
    0,
    0,
    0
};

struct music_play_info music_task_play_info={
    NULL,
    0,
    0,
    MUSIC_IDLE,
    0
};

uint32_t musical_scale_freq_100[]=
{
    //1-    1-#     2-      2-#     3-      4-      4-#     5-      5-#     6-      6-#     7-
    13081, 13859, 14683, 15556, 16481, 17461, 18500, 19600, 20765, 22000, 23308, 24694,
    //1
    26163, 27718, 29366, 31113, 32963, 34923, 36999, 39200, 41530, 44000, 46616, 49388,
    //1+
    52325, 55437, 58733, 62225, 65926, 69846, 73999, 78399, 83061, 88000, 93233, 98777,
    //1++
    10465, 11087, 11747, 12445, 13185, 13969, 14800, 15680, 16612, 17600, 18647, 197553,
    //1+++
    20930, 22175, 23493, 24890, 26370, 27938, 29600, 31360, 33224, 35200, 37293, 395105,
};

const uint musical_scale_regv[]=
{
    //1-   1-#    2-     2-#    3-     4-     4-#    5-     5-#    6-    6-#   7-
    //15926, 15032, 14189, 13392, 12641, 11931, 11261, 10629, 10033, 9470, 8938, 8437,
    7963,  7516,  7094,  6696,  6320,  5966,  5631,  5315,  5016,  4735, 4469, 4218,
    3982,  3758,  3547,  3348,  3160,  2983,  2815,  2657,  2508,  2367, 2235, 2109,
    1991,  1879,  1774,  1674,  1580,  1491,  1408,  1329,  1254,  1184, 1117, 1055,
    995,   939,   887,   837,   790,   746,   704,   664,   627,   592,  559,  527,
};

uint8 get_note_index(signed char value)
{
    uint8 ret;
    bool half_note = false;
    //printf("input %d\r\n", value);
    if(value < 0){//half note: #1 #2...
        value = 0 - value;
        half_note = true;
    }
    if(value == 8)value=12;
    if(value == 9)value=22;
    if(value<8){
        value=value*10+1;
    }
    ret = (value%10) * 12;//base
    value /= 10;
    ret += value*2-2;
    if(value>=4)ret--;
    if(half_note)ret++;
    //printf("output %u\r\n", ret);
    return ret;
}

const signed char fu[200] = {5,5,6,6,5,5,8,8,7,7,0,0,5,5,6,6,5,5,9,9,8,8,0,0,
                5,5,52,52,32,32,8,8,7,7,6,6,0,0,42,42,32,32,8,8,9,9,8,8,0,0,0,0,SCORE_END};
const signed char shaolshi[] = {
    5,6,
    FLAGSTART,
    8,8,8,6,8,8,8,8,8,8,3,8,  7,7,7,6,  7,7,7,7,7,7,6,3,2,2,2,3,  5,5,5,5,6,2,2,60,
    1,1,3,5,6,3,5,5,  3,5,6,3,5,5,50,60,  1,1,1,5,3,3,3,2,  3,3,3,3,3,3,50,60,  1,1,1,5,2,2,2,1,
    2,2,2,2,3,5,  6,6,6,6,6,6,3,5,  1,1,1,3,2,70,60,60,  0,2,2,3,2,2,70,60,  50,50,50,50,50,50,5,6,
    12,12,12,6,   12,12,12,12,12,12,32,12,  7,7,7,6,  7,7,7,7,7,7,6,3,  2,2,2,3,7,7,7,6,  5,5,5,5,5,5,5,6,
    12,12,12,6,   12,12,12,12,12,12,32,12,  7,7,7,6,  7,7,7,7,7,7,6,3,  2,2,2,3,  5,5,5,5,0,2,2,60,
    DIVERT,
    1,1,1,1,1,1,5,6,
    GOSTART,
    1,1,1,1,1,1,6,3,  2,2,2,3,  5,5,5,5,0,2,2,60,  1,1,1,1,1,1,1,1,  0,0,2,2,2,2,60,60,  1,1,1,1,1,1,1,1,  1,1,0,0,0,0,0,0,
    SCORE_END
};
const signed char xianglian[] = {
    FLAGSTART,
    3,5,5,8,32,32,22,12,  6,6,6,6,6,6,6,6,  2,4,4,5,7,7,6,5,  3,3,3,3,3,3,3,3,
    5,6,6,8,42,42,32,8,   22,22,22,22,22,22,22,22,  6,6,22,22,8,7,6,5,  8,8,8,8,8,8,8,8,  8,8,8,8,8,8,8,8,
    3,5,5,8,32,32,22,12,  6,6,6,6,6,6,6,6,  2,4,4,5,7,7,6,5,  3,3,3,3,3,3,3,3,
    5,6,6,8,42,42,32,8,   22,22,22,22,22,22,22,22,  6,22,22,8,7,HP,8,7,DP,6,7,  5,5,5,5,5,5,5,5,
    3,5,5,8,32,32,22,8,  6,6,6,6,6,6,6,6,  2,4,4,5,7,7,6,5,  3,3,3,3,3,3,3,3,3,
    5,6,6,8,42,42,32,8,  9,9,9,9,9,9,6,6,  7,9,9,8,7,HP,8,7,DP,6,7,  5,5,5,5,5,5,5,5, 3,5,5,8,32,32,9,8,
    6,6,6,6,6,6,6,6,  2,4,4,5,7,7,6,5,  3,3,3,3,3,3,3,3,3,  5,6,6,8,42,42,32,8,
    DIVERT,
    9,9,9,9,9,9,6,6,  7,9,9,8,7,HP,8,7,DP,6,5,  8,8,8,8,8,8,8,8,
    GOSTART,
    9,9,9,9,9,9,9,9,  9,6,6,7,6,6,5,5,
    8,8,8,8,8,8,8,8,  8,8,0,0,0,0,0,0,  3,5,5,8,32,32,22,12,  6,6,6,6,6,6,6,6,  2,4,4,5,7,7,6,5,  3,3,3,3,3,3,3,3,
    5,6,6,8,42,42,32,8,  9,9,9,9,9,9,9,9,  6,9,9,8,7,7,6,5,  8,8,8,8,8,8,8,8,  8,8,8,8,8,8,8,8,
    SCORE_END
};
const signed char notice_music[] = {
    //1,1,4,4,5,5,8,8,8,8,0
    1,1,4,4,5,5,8,8,SCORE_END
};
const signed char xiyouji1[] = {
    HP,
    50,50,60,60,
    FLAGSTART,
    1,1,1,1,1,1,2,2,  3,3,3,70,60,70,50,50,  60,60,60,60,60,60,60,60,  60,60,60,60,1,1,2,2,  3,3,3,3,3,3,5,5,  6,6,1,1,2,3,4,4,  3,3,3,3,3,3,3,3,  3,3,3,3,3,3,5,5,
    6,6,6,6,6,6,5,5,  6,6,6,6,60,60,3,3,  2,2,2,2,2,2,1,1,  2,2,2,2,3,3,3,3,  50,50,50,50,50,50,60,60,  70,70,3,3,3,3,60,60,  60,60,1,1,1,1,1,1,  1,1,1,1,1,1,1,1,  0,0,5,5,5,5,6,6,  8,8,7,7,7,7,6,5,
    6,6,6,6,6,6,6,6,  6,6,6,6,6,6,6,6,  0,0,5,5,5,5,6,6,  8,8,7,7,7,7,6,5,  3,3,3,3,3,3,3,3,  3,3,3,3,50,50,60,60,  1,1,1,1,1,1,2,2,  3,3,3,70,60,70,50,50,  60,60,60,60,60,60,60,60,
    60,60,60,60,1,1,2,2,  3,3,3,3,3,3,5,5,  6,6,1,1,2,3,4,4,  3,3,3,3,3,3,3,3,  3,3,3,3,3,3,5,5,  6,6,6,6,6,6,5,5,  6,6,6,6,60,60,3,3,  2,2,2,2,2,2,1,1,  2,2,2,2,3,3,3,3,  50,50,50,50,50,50,60,60,
    70,70,3,3,3,3,60,60,
    DIVERT,
    60,60,1,1,1,1,1,1,  1,1,1,1,1,1,1,1,  1,1,1,1,50,50,60,60,
    GOSTART,
    60,60,1,1,1,1,1,1,  1,1,1,1,1,1,1,1,  1,1,1,1,3,3,3,3,  50,50,50,50,50,50,60,60,  70,70,3,3,3,3,60,60,  60,60,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,  70,70,70,70,70,70,70,70,  3,3,3,3,60,60,60,60,  60,60,1,1,1,1,1,1,  1,1,1,1,1,1,1,1,  1,1,1,1,1,1,1,1,  1,1,1,1,0,0,0,0,
    DP,
    SCORE_END
};
const signed char warning[] = {
    //1,1,4,4,5,5,8,8,8,8,0
    //1,2,3,4,5,6,7,8,  7,1,7,1,7,1,7,1,SCORE_END
    8,7,8,7,8,7,8,7,SCORE_END
};

const signed char pwroff_music[] = {
    HP,
    8,7,6,5,4,3,2,1,
    DP,
    SCORE_END
};

const signed char count_down_music[] = {
    8,0,0,0,8,0,0,0,  8,0,0,0,8,0,0,0,  8,0,0,0,8,0,0,0,
    8,0,0,0,8,0,0,0,  8,0,0,0,8,0,0,0,  8,0,0,0,8,0,0,0,
    8,0,0,0,8,0,0,0,SCORE_END
};

const signed char YouJianChuiYan[] = {
    HP,
    60,70,1,2,3,4,5,
    DP,
    FLAGSTART,
    6,6,6,6,  5,5,3,2,  1,1,2,4,  3,3,3,3,  0,2,3,1,  60,60,50,60,  1,1,1,1,  1,1,1,1,
    5,5,5,3,  6,5,3,2,  1,1,60,1, 50,50,50,50,  60,60,60,60,  50,50,1,2,  3,3,3,3,  3,3,3,3,
    5,5,5,3,  6,5,3,2,  1,1,60,1,  50,50,50,50,  5,5,5,HP,5,6,DP,  5,3,2,HP,3,2,DP,  1,1,1,1,  1,1,1,1,
    2,2,2,1,  3,3,2,2,  1,1,2,3,  5,5,5,5,  6,6,6,6,  3,3,5,6,  5,5,5,5, 5,5,5,5,
    6,6,6,6,  5,5,3,2,  0,1,2,4,  3,3,1,1,  0,2,3,1,  60,60,50,60,
    DIVERT,
    1,1,1,1,  1,HP,60,70,1,2,3,4,5,DP,
    GOSTART,
    1,1,1,1,  1,1,1,1,  5,5,5,3,  6,5,3,2,  1,1,60,1, 50,50,50,50,  60,60,60,60,  50,50,1,2,  3,3,3,3,  3,3,3,3,
    5,5,5,3,  6,5,3,2,  1,1,60,1,  50,50,50,50,  5,5,5,6,  5,5,3,2,  1,1,1,1,  1,1,1,1,
    GOSTART,
    1,1,1,1,  6,6,6,6,  5,5,3,2,  0,1,2,4,  3,3,1,1,  0,2,3,1,  60,60,50,60,
    1,1,1,1,  1,1,1,1,  1,1,0,0,  50,50,50,50,  5,5,5,6,  5,5,3,2,  1,1,1,1,  1,1,1,1, 1,1,
    SCORE_END
};

const signed char * music_lst[]={
    YouJianChuiYan,
    xiyouji1,
    shaolshi,
    xianglian
};

int get_music_lst_size(){
    return sizeof(music_lst)/sizeof(const signed char*);
}

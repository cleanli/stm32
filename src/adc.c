#include "common.h"
#include "adc.h"

#define ADC_INITED 0x11d0
#ifdef ADC_DEBUG
#define Debug_LOG_ADC(...) lprintf(__VA_ARGS__)
#else
#define Debug_LOG_ADC(...)
#endif
uint32_t v_bat = 0;
int adc_test()
{
    int ret = 0;
#ifdef POWER_MONITOR
    static int adc_inited = 0;
    GPIO_InitTypeDef GPIO_InitStructure;
    ADC_InitTypeDef ADC_InitStructure;
    uint32_t v_core, v_ref, v_currt;
    char in_charge;

    if(ADC_INITED!=adc_inited){
        lprintf("performing adc init\n");
        RCC_ADCCLKConfig(RCC_PCLK2_Div4);
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1|RCC_APB2Periph_GPIOA, ENABLE);

        /* Configure analog inputs */
        GPIO_InitStructure.GPIO_Pin = GPIO_ADC_VREF_PIN | GPIO_ADC_V4_2_PIN | GPIO_ADC_IBAT_PIN;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
        GPIO_Init(GPIOA, &GPIO_InitStructure);

        /* ADC1 configuration ------------------------------------------------------*/
        ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
        ADC_InitStructure.ADC_ScanConvMode = DISABLE;
        ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;
        ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
        ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
        ADC_InitStructure.ADC_NbrOfChannel = 1;
        ADC_Init(ADC1, &ADC_InitStructure);
        /* ADC1 regular channels configuration */
        lprintf("config adc1 using VREF\n");
        ADC_RegularChannelConfig(ADC1, ADC_Channel_VREF, 1, ADC_SampleTime_28Cycles5);

        lprintf("enable adc1\n");
        ADC_Cmd(ADC1, ENABLE);
        /* Enable ADC1 reset calibration register */
        ADC_ResetCalibration(ADC1);
        /* Check the end of ADC1 reset calibration register */
        lprintf("wait adc1 calibration\n");
        while(ADC_GetResetCalibrationStatus(ADC1));

        /* Start ADC1 calibration */
        ADC_StartCalibration(ADC1);
        /* Check the end of ADC1 calibration */
        while(ADC_GetCalibrationStatus(ADC1));
        lprintf("adc1 calibration done\n");
        adc_inited = ADC_INITED;
    }
    else{
        Debug_LOG_ADC("adc already inited\n");
    }

    Debug_LOG_ADC("start adc1 VREF convertion\n");
    ADC_RegularChannelConfig(ADC1, ADC_Channel_VREF, 1, ADC_SampleTime_28Cycles5);
    ADC_SoftwareStartConvCmd(ADC1, ENABLE);
    do
    {
        delay_us(5);
        Debug_LOG_ADC("waiting convertion done...\n");
    }while(ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC)==RESET);
    v_ref=ADC_GetConversionValue(ADC1);
    Debug_LOG_ADC("vref = %x\n", v_ref);
    v_core = 2500 * 4096 / v_ref;
    Debug_LOG_ADC("real vcore = %dmv\n", v_core);

    Debug_LOG_ADC("start adc1 V4_2 convertion\n");
    ADC_RegularChannelConfig(ADC1, ADC_Channel_V4_2, 1, ADC_SampleTime_28Cycles5);
    ADC_SoftwareStartConvCmd(ADC1, ENABLE);
    do
    {
        delay_us(5);
        Debug_LOG_ADC("waiting convertion done...\n");
    }while(ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC)==RESET);
    v_bat=ADC_GetConversionValue(ADC1);
    v_bat = 2500 * v_bat / v_ref;
    v_bat = v_bat * V4_2_RATIO;
    Debug_LOG_ADC("real vbat = %dmv\n", v_bat);

    Debug_LOG_ADC("start adc1 IBAT convertion\n");
    ADC_RegularChannelConfig(ADC1, ADC_Channel_IBAT, 1, ADC_SampleTime_28Cycles5);
    ADC_SoftwareStartConvCmd(ADC1, ENABLE);
    do
    {
        delay_us(5);
        Debug_LOG_ADC("waiting convertion done...\n");
    }while(ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC)==RESET);
    v_currt=ADC_GetConversionValue(ADC1);
    Debug_LOG_ADC("vcur = %x\n", v_currt);
    if(v_currt>v_ref){
        in_charge = '+';
        v_currt = v_currt - v_ref;
    }
    else{
        in_charge = '-';
        v_currt = v_ref - v_currt;
    }
    //mA/mv
    v_currt = 2500 * v_currt / v_ref;
    Debug_LOG_ADC("real v_currt = %dmv\n", v_currt);
    v_currt = v_currt * CURRENT_MEASUREMENT_CALIBRATION;
    Debug_LOG_ADC("real I = %dmA\n", v_currt);
    Debug_LOG_ADC("----%dmv %dmv %c%dmA\n", v_core, v_bat, in_charge, v_currt);
#ifdef LARGE_SCREEN
    lcd_lprintf(240, 0, "%dmv %dmv %c%dmA", v_core, v_bat, in_charge, v_currt);
#else
    lcd_lprintf(180, 30, "%dmv %dmv %c%dmA", v_core, v_bat, in_charge, v_currt);
#endif
    if(500000 > (get_system_us()%(1000*1000*200))){//200s
        lprintf_time("v_core %dmv v_bat %dmv in_charge %c I %dmA\n", v_core, v_bat, in_charge, v_currt);
    }
    if(v_bat < BATT_LOW_LIMIT){
        lprintf("battery is low\n");
        ret = 1;
    }
#endif
    return ret;
}

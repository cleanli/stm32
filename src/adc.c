#include "common.h"
#include "adc.h"

#define ADC_INITED 0x11d0
void adc_test()
{
    static int adc_inited = 0;
    GPIO_InitTypeDef GPIO_InitStructure;
    ADC_InitTypeDef ADC_InitStructure;
    char lcd_print_buf[32];
    uint32_t v_core, v_bat, v_ref;

    if(ADC_INITED!=adc_inited){
        lprintf("performing adc init\n");
        RCC_ADCCLKConfig(RCC_PCLK2_Div4);
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1|RCC_APB2Periph_GPIOA, ENABLE);

        /* Configure PA.03, PA.04 (ADC Channel3, ADC Channel4 as analog inputs */
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_4;
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
        lprintf("config adc1 using PA3\n");
        ADC_RegularChannelConfig(ADC1, ADC_Channel_3, 1, ADC_SampleTime_28Cycles5);

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
        lprintf("adc already inited\n");
    }

    lprintf("start adc1 PA3 convertion\n");
    ADC_RegularChannelConfig(ADC1, ADC_Channel_3, 1, ADC_SampleTime_28Cycles5);
    ADC_SoftwareStartConvCmd(ADC1, ENABLE);
    do
    {
        delay_us(50);
        lprintf("waiting convertion done...\n");
    }while(ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC)==RESET);
    lprintf("raw ref result = %x\n", v_ref=ADC_GetConversionValue(ADC1));
    v_core = 250 * 4096 / v_ref;
    lprintf("real vcore = %d0mv\n", v_core);
    memset(lcd_print_buf, 0, 32);
    slprintf(lcd_print_buf, "real vcore = %d0mv\n", v_core);
    Show_Str(30, 30,0,0xff,lcd_print_buf,24,1);

    lprintf("start adc1 PA4 convertion\n");
    ADC_RegularChannelConfig(ADC1, ADC_Channel_4, 1, ADC_SampleTime_28Cycles5);
    ADC_SoftwareStartConvCmd(ADC1, ENABLE);
    do
    {
        delay_us(50);
        lprintf("waiting convertion done...\n");
    }while(ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC)==RESET);
    lprintf("raw vbat result = %x\n", v_bat=ADC_GetConversionValue(ADC1));
    v_bat = 250 * v_bat / v_ref;
    v_bat = v_bat * (330 + 680) / 330;
    lprintf("real vbat = %d0mv\n", v_bat);
    memset(lcd_print_buf, 0, 32);
    slprintf(lcd_print_buf, "real vbat = %d0mv\n", v_bat);
    Show_Str(30, 90,0,0xff,lcd_print_buf,24,1);
}

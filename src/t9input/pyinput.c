#include "pyinput.h"
#include "string.h"
//////////////////////////////////////////////////////////////////////////////////	 
//本程序参考自网络并加以修改
//ALIENTEK战舰STM32开发板
//拼音输入法 驱动代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2012/9/22
//版本：V1.0			    
//广州市星翼电子科技有限公司  	 												    								  
//////////////////////////////////////////////////////////////////////////////////

//拼音输入法
pyinput t9=
{
	get_pymb,
    {0},
};

//比较两个字符串的匹配情况
//返回值:0xff,表示完全匹配.
//		 其他,匹配的字符数
unsigned char str_match(unsigned char*str1,unsigned char*str2)
{
	unsigned char i=0;
	while(1)
	{
		if(*str1=='\0'){
			return i;
		}
		if(*str1!=*str2){
			return 0;
		}
		i++;
		str1++;
		str2++;
	}
}

//获取匹配的拼音码表
//*strin,输入的字符串,形如:"726"
//**matchlist,输出的匹配表.
//返回值:[7],0,表示完全匹配；1，表示部分匹配（仅在没有完全匹配的时候才会出现）
//		 [6:0],完全匹配的时候，表示完全匹配的拼音个数
//			   部分匹配的时候，表示有效匹配的位数				    	 
unsigned char get_matched_pymb(unsigned char *strin,py_index **matchlist)
{
	int pyindex_len;
	int i;
	unsigned char temp,mcnt=0;
	pyindex_len=size_of_pyindex();//得到py索引表的大小.
	for(i=0;i<pyindex_len;i++)
	{
		temp=str_match(strin,(unsigned char*)py_index3[i].py_input);
		if(temp)
		{
			matchlist[mcnt++]=(py_index*)&py_index3[i];
		}
	}
	return mcnt;//返回匹配的个数
}

//得到拼音码表.
//str:输入字符串
//返回值:匹配个数.
unsigned char get_pymb(unsigned char* str)
{
	return get_matched_pymb(str,t9.pymb);
}

void test_py(unsigned char *inputstr)
{
	unsigned char t=0;
	unsigned char i=0;
	t=t9.getpymb(inputstr);
	if(t&0X80)
	{
		//printf("\r\n输入数字为:%s\r\n",inputstr);
		//printf("部分匹配位数:%d\r\n",t&0X7F);
		//printf("部分匹配结果:%s,%s\r\n",t9.pymb[0]->py,t9.pymb[0]->pymb);
	}else if(t)
	{
		//printf("\r\n输入数字为:%s\r\n",inputstr);
		//printf("完全匹配个数:%d\r\n",t);
		//printf("完全匹配的结果:\r\n");
		for(i=0;i<t;i++)
		{
			//printf("%s,%s\r\n",t9.pymb[i]->py,t9.pymb[i]->pymb);
		}
	}
    //else printf("没有任何匹配结果！\r\n");
}

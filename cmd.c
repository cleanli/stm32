#include "cmd.h"
#include "lcd.h"
#include <stdint.h>
#define uint uint16_t
#define lprint lprintf

static unsigned char cmd_buf[COM_MAX_LEN] = "";
static uint cmd_buf_p = COM_MAX_LEN;

uint get_howmany_para(unsigned char *s);
unsigned char * str_to_hex(unsigned char *s, uint * result);
/*
void con_send(unsigned char X)
{
    __io_putchar(X);
    if(X == '\n'){
        __io_putchar('\r');
    }
}
*/

void dispcchar(unsigned char *p)
{
    uint x = 0, y=0, offset = 0, tmp, i;
    unsigned char *cp;

    tmp = get_howmany_para(p);
    if( tmp < 2)
        goto error;
    p = str_to_hex(p, &x);
    p = str_to_hex(p, &y);
    if(tmp > 2)
        str_to_hex(p, &offset);
    if(tmp == 2)
        Display_Chinese(x,y,jiong1);
    else
        Display_Chinese2(x,y,ziku+offset);
    con_send('\n');

    return;

error:
    lprint("Err!\ndispcchar [x] [y]\n");
}

static const struct command cmd_list[]=
{
    {"dispcchar",dispcchar},
    {"go",go},
    {"help",print_help},
    {"pm",print_mem},
    {"r",read_mem},
    {"w",write_mem},
    {NULL, NULL},
};
static uint * mrw_addr;

void go(unsigned char *para)
{
	(*((void (*)())mrw_addr))();
}

void print_help(unsigned char *para)
{
    uint i = 0;
    lprint("Cmd:\n");
    while(1){
            if(cmd_list[i].cmd_name == NULL)
                    break;
	    lprint("--%s\n", cmd_list[i].cmd_name);
            i++;
    }
}

uint asc_to_hex(unsigned char c)
{
	uint v;

	if(c >= '0' && c <= '9')
		return c - '0';	
	if(c >= 'A' && c <= 'F')
		return c - 'A' + 10;
	if(c >= 'a' && c <= 'f')
		return c - 'a' + 10;
	return 0;
}

uint get_howmany_para(unsigned char *s)
{
	uint tmp = 0;
	while(1){
		while(*s == ' ')
			s++;
		if(*s)
			tmp++;
		while(*s != ' ' && *s)
			s++;
		if(!*s)
			return tmp;
	}
}

unsigned char * str_to_hex(unsigned char *s, uint * result)
{
	uint  i = 0;

	*result = 0;
	while(*s == ' ')s++;
	for(i=0;i<8;i++){
		if(*s == ' ' || *s == 0)
			break;
		*result = *result*16 + asc_to_hex(*s++);
	}
	while(*s == ' ')s++;
	return s;
}

void print_mem(unsigned char *p)
{
    uint length = 0x80, tmp, i;
    unsigned char *cp;

    tmp = get_howmany_para(p);
    if( tmp > 1)
        goto error;
    if(tmp == 0)
        goto print;
    str_to_hex(p, &length);
print:
    cp = (unsigned char *)mrw_addr;
    while(length){
	lprint("\n%x: ", (uint)cp);
	for(i=0;i<16;i++){
		length--;
		con_send(*cp++);
		con_send(i == 7 ? '-':' ');
	}
    }
    con_send('\n');

    return;

error:
    lprint("Err!\npm [length](0x80 default)\n");

}

void write_mem(unsigned char *p)
{
    uint value, tmp;

    tmp = get_howmany_para(p);
    if(tmp == 0 || tmp > 2)
	goto error;
    p = str_to_hex(p, &value);
    if(tmp == 1)
        goto write;
    str_to_hex(p, (uint*)&mrw_addr);
    mrw_addr = (uint*)((uint)mrw_addr & 0xfffffffc);
write:
    *(uint*)mrw_addr = value;
    lprint("Write 0x%x@0x%x\n",value,mrw_addr);
    return;

error:
    lprint("Err!\nw (hexaddr) [(hexaddr)](last addr default)\n");

}


void read_mem(unsigned char *p)
{
    uint value, tmp;

    tmp = get_howmany_para(p);
    if( tmp > 1)
	goto error;
    if(tmp == 0)
    	goto read;
    str_to_hex(p, (uint*)&mrw_addr);
    mrw_addr = (uint*)((uint)mrw_addr & 0xfffffffc);
read:
    value = *(uint*)mrw_addr;
    lprint("Read 0x%x at memory 0x%x\n",value,mrw_addr);

    return;

error:
    lprint("Err!\nr [(hexaddr)](last addr default)\n");

}

void lmemset(unsigned char *d,unsigned char v,unsigned int n)
{
	while(n--)*d++=v;
}

void handle_cmd()
{
    unsigned char i = 0, *p_cmd, *p_buf;

    lprint("\n");
    if(!cmd_buf[0])
	return;
    while(1){
	    if(cmd_list[i].cmd_name == NULL)
		    break;
	    p_cmd=cmd_list[i].cmd_name;
	    p_buf=cmd_buf;
	    while(*p_cmd){
		    if(*p_buf != *p_cmd)
			    break;
		    p_buf++;
		    p_cmd++;
	    }
	    if(!(*p_cmd) && (*p_buf == ' ' || !(*p_buf))){
            	    cmd_list[i].cmd_fun(p_buf);
            	    return;
       	    }
	    i++;
    }
    lprint("Unknow cmd:%s\n",cmd_buf);
}

uint time_limit_recv_byte(uint limit, unsigned char * c);
void run_cmd_interface()
{
	unsigned char c;
	
	mrw_addr = (uint*)0x30000000;
	lprint("\n\nclean_cmd. \nAnykey stop auto load file\n");
	lmemset(cmd_buf, 0, COM_MAX_LEN);
	cmd_buf_p = 0;
	lprint("\nCleanCMD>");
	
	while(1){
		c = con_recv();
		if(c == ENTER_CHAR || c == 0x1b || c== 0x03){
			if(c == ENTER_CHAR)
				handle_cmd();
			lmemset(cmd_buf, 0, COM_MAX_LEN);
			cmd_buf_p = 0;
			lprint("\nCleanCMD>");
		}
		else if(c == 0x08){
			if(!cmd_buf_p)
				continue;
                        cmd_buf[--cmd_buf_p] = 0;
                        lprintf("\b \b");
		}
		else{
			if(cmd_buf_p < (COM_MAX_LEN - 1)){
				cmd_buf[cmd_buf_p++] = c;
				con_send(c);
			}
		}
	}
}

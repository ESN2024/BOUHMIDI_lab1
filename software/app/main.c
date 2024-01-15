#include<stdio.h>
#include<stdint.h>
#include "system.h"
#include "altera_avalon_pio_regs.h"
#include "sys/alt_stdio.h"
#include <unistd.h>

int main()
{
	int data=0x01;

	while(1)
	{
		data=0x01;
		IOWR_ALTERA_AVALON_PIO_DATA(LEDS_BASE,0x01);
		usleep(50000);
		while(data != 0x80)
		{
			data= data<<1;
			IOWR_ALTERA_AVALON_PIO_DATA(LEDS_BASE,data);
			usleep(50000);	
		}	
	}
	return 0;
}
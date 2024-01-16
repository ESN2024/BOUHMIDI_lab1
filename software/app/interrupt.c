#include<stdio.h>
#include<stdint.h>
#include "system.h"
#include <io.h>
#include "altera_avalon_pio_regs.h"
#include "sys/alt_stdio.h"
#include <unistd.h>
#include <sys/alt_irq.h>

static void init_interrupt_pio();
static void chenillard(int temps);
static void arret_chenillard();
static void irqhandler_bp_sw(void *context, alt_u32 id);

volatile int edge_capture;
int temps = 100000;			//valeur de vitesse par defaut au debut du programme

static void init_interrupt_pio()
{
    void* edge_capture_ptr = (void*)&edge_capture;
	//autoriser l interruption de 2bp et 4 swicths
    IOWR_ALTERA_AVALON_PIO_IRQ_MASK(BP_SW_BASE,0x3F);

    //Reset le registre edge capture
    IOWR_ALTERA_AVALON_PIO_EDGE_CAP(BP_SW_BASE,0x3F);

	
}

static void chenillard(int t)
{
        int led_data = 0x01;
        IOWR_ALTERA_AVALON_PIO_DATA(LEDS_BASE, 0x01);
        usleep(t);

        while (led_data != 0x80)
        {
            led_data = led_data << 1;
            IOWR_ALTERA_AVALON_PIO_DATA(LEDS_BASE, led_data);
            usleep(t);
        }
		while(led_data != 0x01)
		{
			led_data= led_data>>1;
			IOWR_ALTERA_AVALON_PIO_DATA(LEDS_BASE,led_data);
			usleep(t);	
		}
}

static void arret_chenillard()
{
    IOWR_ALTERA_AVALON_PIO_DATA(LEDS_BASE, 0x00);
}

static void irqhandler_bp_sw (void * context, alt_u32 id)
{
	alt_u32 val = IORD_ALTERA_AVALON_PIO_EDGE_CAP(BP_SW_BASE);
	switch (val) 
	{
		case 0x04:
			//Vitesse +
			temps = 80000;
		break;
		case 0x08:
			//Vitesse ++
			temps = 60000;
		break;
		case 0x10:
			//Vitesse +++
			temps = 40000;
		break;
		case 0x20:
			//Vitesse ++++
			temps = 20000;
		break;
	}
	
	if (val == 0x01)
	{
		chenillard(temps);
		//temps = 100000;         //decommenter si l'on souhaite toujours avoir une vitesse par défaut 
	}
	else if (val == 0x02)
		arret_chenillard();
		
    IOWR_ALTERA_AVALON_PIO_EDGE_CAP(BP_SW_BASE,0x3F);

}



int main()
{
	init_interrupt_pio();
	alt_ic_isr_register(BP_SW_IRQ_INTERRUPT_CONTROLLER_ID,BP_SW_IRQ, irqhandler_bp_sw, NULL, NULL);

	while (1)
	{
		
	}
	return 0;
}
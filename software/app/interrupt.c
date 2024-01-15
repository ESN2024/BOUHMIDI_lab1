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

static void init_interrupt_pio()
{
    void* edge_capture_ptr = (void*)&edge_capture;
	//autoriser l interruption de 2bp et 4 swicths
    IOWR_ALTERA_AVALON_PIO_IRQ_MASK(BP_SW_BASE,0x3F);

    //Reset the edge capture register
    IOWR_ALTERA_AVALON_PIO_EDGE_CAP(BP_SW_BASE,0x3F);

    //Register the interrupt handler in the system  	
	
}

static void chenillard(int temps)
{
    // int led_data;
    // while (1)
    // {
        int led_data = 0x01;
        IOWR_ALTERA_AVALON_PIO_DATA(LEDS_BASE, 0x01);
        usleep(temps);

        while (led_data != 0x80)
        {
            led_data = led_data << 1;
            IOWR_ALTERA_AVALON_PIO_DATA(LEDS_BASE, led_data);
            usleep(temps);
        }
/*     } */
}

static void arret_chenillard()
{
    IOWR_ALTERA_AVALON_PIO_DATA(LEDS_BASE, 0x00);
}

static void irqhandler_bp_sw (void * context, alt_u32 id)
{
	alt_u32 interrupt = IORD_ALTERA_AVALON_PIO_IRQ_MASK(BP_SW_BASE);
	alt_u32 val = IORD_ALTERA_AVALON_PIO_EDGE_CAP(BP_SW_BASE);
    volatile int* edge_capture_ptr = (volatile int*) context;
    *edge_capture_ptr = IORD_ALTERA_AVALON_PIO_EDGE_CAP(BP_SW_IRQ);
	switch (val) 
	{
		case 0x01:
			//lancement chenillard
			chenillard(100000);
		break;
		case 0x02:
			//arret
			arret_chenillard();
		break;
		case 0x04:
			//lancement chenillard Vitesse +
			chenillard(80000);
		break;
		case 0x08:
			//lancement chenillard Vitesse ++
			chenillard(60000);
		break;
		case 0x10:
			//lancement chenillard Vitesse +++
			chenillard(40000);
		break;
		case 0x20:
			//lancement chenillard Vitesse ++++
			chenillard(20000);
		break;
		default :
			IOWR_ALTERA_AVALON_PIO_DATA(LEDS_BASE, 0x0F);
		break;
	}		
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
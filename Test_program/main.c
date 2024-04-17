#include "io.h"


void RGB_LED_init(void){
	
	SYSCTL_RCGCGPIO_R|=PF_mask;
	while((SYSCTL_PRGPIO_R&PF_mask)==0);
	
			GPIO_PORTF_LOCK_R=GPIO_LOCK_KEY;
			GPIO_PORTF_CR_R |=PF123_mask;
			GPIO_PORTF_AMSEL_R&=~PF123_mask;
			GPIO_PORTF_AFSEL_R&=~PF123_mask;
			GPIO_PORTF_PCTL_R&=~0x0000FFF0;
			GPIO_PORTF_DIR_R|=PF123_mask;
			GPIO_PORTF_DEN_R|=PF123_mask;
			GPIO_PORTF_DATA_R&=~PF123_mask;
	}
		void SW12_init(void)
			{
				GPIO_PORTF_LOCK_R=GPIO_LOCK_KEY;
				GPIO_PORTF_CR_R |=PF04_mask;
				GPIO_PORTF_AMSEL_R&=~PF04_mask;
				GPIO_PORTF_AFSEL_R&=~PF04_mask;
				GPIO_PORTF_PCTL_R&=~0x000F000F;
				GPIO_PORTF_DIR_R&=~PF04_mask;
				GPIO_PORTF_DEN_R|=PF04_mask;
				GPIO_PORTF_PUR_R|=PF04_mask;
		}
unsigned char SW12_input(void){
return GPIO_PORTF_DATA_R&PF04_mask;
}
void LED_output(unsigned char data){
GPIO_PORTF_DATA_R&=~0x1F;
GPIO_PORTF_DATA_R|=data;
}
unsigned char button_in;



int main()
{
		RGB_LED_init();
		SW12_init();
		while(1)
			{
				button_in=SW12_input();
				switch (button_in)
					{
				case 0X10:
				LED_output(0x08);   //green
				break;
				case 0x01:
				LED_output(0x04);   //blue
				break;
				case 0x00:
				LED_output(0x02);   //red
				break;
				}
		}

		
}

#include "gpio.h"

int main()
{

    GPIO_init((unsigned long)GPIOF, 0x11, 0xE);
    //GPIO_write_pin((unsigned long)GPIOF, 3, 1);

    //GPIOF_default_init();
    while (1)
    {
        if (!GPIO_read_pin(GPIOF, 4) && !GPIO_read_pin(GPIOF, 0))
        {
            GPIO_write_pin((unsigned long)GPIOF, 3, 0);
            GPIO_write_pin((unsigned long)GPIOF, 2, 0);
            GPIO_write_pin((unsigned long)GPIOF, 1, 1);
        }
        else if (GPIO_read_pin(GPIOF, 4) && !GPIO_read_pin(GPIOF, 0))
        {
            GPIO_write_pin((unsigned long)GPIOF, 3, 0);
            GPIO_write_pin((unsigned long)GPIOF, 1, 0);
            GPIO_write_pin((unsigned long)GPIOF, 2, 1);
        }
        else if (!GPIO_read_pin(GPIOF, 4) && GPIO_read_pin(GPIOF, 0))
        {
            GPIO_write_pin((unsigned long)GPIOF, 1, 0);
            GPIO_write_pin((unsigned long)GPIOF, 2, 0);
            GPIO_write_pin((unsigned long)GPIOF, 3, 1);
        }
    } 
}

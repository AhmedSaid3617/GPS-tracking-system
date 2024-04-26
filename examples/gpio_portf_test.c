#include "gpio.h"
#include "tm4c123gh6pm.h"
int main()
{
    GPIOF_default_init();
    while (1)
    {
        if (read_sw1() && read_sw2())
        {
            write_green_led(0);
            write_blue_led(0);
            write_red_led(1);
        }
        else if (!read_sw1() && read_sw2())
        {
            write_green_led(0);
            write_red_led(0);
            write_blue_led(1);
        }
        else if (read_sw1() && !read_sw2())
        {
            write_red_led(0);
            write_blue_led(0);
            write_green_led(1);
        }
    } 
}

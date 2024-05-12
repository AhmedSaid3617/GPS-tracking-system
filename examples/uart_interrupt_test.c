#include "main.h"

enum State
{
    IDLE = 1,
    RECORDING
};

gps_data_t data_point;
char mode_string[10] = "IDLE";
char latitude_string[10] = " ";
char longitude_string[10] = " ";
char gps_status_string[] = "Not valid";
// char satelites_string[10] = "0";
char distance[10] = "0.0";

char gps_input_buffer[500] = "1";
float coordinates[RAM_MAX_COORDINATES][2] = {1};
unsigned long coordinates_num = 1;
int mode = IDLE;

int led = 1;

int main()
{
    UART0_Init(9600);
    UART0_interrupt_init();
    GPIOF_default_init();
    Systick_Init();
    led = 0;

    while (1)
    {
        UART_printf("========", UART0);
        write_blue_led(led);
        Systic_Delay_ms(1000);
    }
    

}


void UART0_IRQHandler(void){
    led = 1;
}

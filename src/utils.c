#include "utils.h"

void float_to_string(float num, char *buffer)
{
    int first = (int)num;
    int second = (num - first) * 1000000;
    sprintf(buffer, "%d.%06d", first, second);
}

float calculate_distance(const float x[2], const float y[2])
{
    double sum = 0;
    sum += 2 * 6371 * 1000 * asin(sqrt(pow(sin((x[0] - y[0]) * (M_PI / 360)), 2) + cos(x[0] * (M_PI / 180)) * cos(y[0] * (M_PI / 180)) * pow(sin((y[1] - x[1]) * (M_PI / 360)), 2)));

#ifdef DEBUG
    UART_printf("\n++Change in distance\n", UART0);
    UART0_print_float(x[0]);
    UART0_print_float(x[1]);
    UART0_print_float(y[0]);
    UART0_print_float(y[1]);
    UART0_print_float(sum);
    UART_printf("\n++End Change in distance\n", UART0);
#endif

    return sum;
}

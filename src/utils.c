#include "utils.h"

void float_to_string(float num, char *buffer)
{
    int first = (int)num;
    int second = (num - first) * 1000000;
    sprintf(buffer, "%d.%06d", first, second);
}
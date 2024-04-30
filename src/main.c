#include "main.h"

int main() {
    I2C_Init();

    while (1)
    {
        I2C_Start(0x1e);
        I2C_Send('A');

        
        
    }
    

}
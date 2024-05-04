#ifndef GPS_TRACKING_SYSTEM_I2C_H
#define GPS_TRACKING_SYSTEM_I2C_H

void I2C_Init();
void I2C_Start(char address);
void I2C_Send(char data);
void I2C_End();
void I2C0_Write_Multiple(int slave_address, char* ptr, int bytes_count);

#endif //GPS_TRACKING_SYSTEM_I2C_H

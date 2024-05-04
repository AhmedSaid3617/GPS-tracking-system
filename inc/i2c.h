#ifndef GPS_TRACKING_SYSTEM_I2C_H
#define GPS_TRACKING_SYSTEM_I2C_H

void I2C_Init();
void I2C0_Write_Multiple(int slave_address, char* ptr, int bytes_count);
void I2C0_Write_In_Sequence(char slave_address, char data);
void I2C0_Write_First_In_Sequence(int slave_address, char data);
void I2C0_Write_Single(int slave_address, char data);
void I2C0_Write_Last_In_Sequence(int slave_address, char data);

#endif //GPS_TRACKING_SYSTEM_I2C_H

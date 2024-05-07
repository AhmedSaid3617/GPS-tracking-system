#ifndef _Systic_H_

#define _Systic_H_

void Systick_Init();
void Systick_Interrupt_Init();

void Systic_Delay_ms(unsigned int time_ms);

void Systick_Delay_cycles(unsigned int delay);

#endif
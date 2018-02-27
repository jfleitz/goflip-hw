
#ifndef _LAMPDRIVER_H_
#define _LAMPDRIVER_H_


void lampISR(void);
void blinkISR(void);

void processMessage(unsigned char, long);
#endif
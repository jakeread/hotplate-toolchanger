#ifndef SYSERROR_H_
#define SYSERROR_H_

#include <Arduino.h>

void sysError(String msg);
void logPacket(uint8_t* pck, uint16_t len);
//void sysError(uint8_t* bytes, uint16_t len);

void sysErrLightFlash(uint8_t level);
void sysErrLightCheck(void);

#define ERROR(level, msg) sysErrLightFlash(level); sysError(msg)

#endif

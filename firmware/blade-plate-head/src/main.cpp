#include <Arduino.h>
#include "indicators.h"
#include "config.h"
#include "drivers/servo.h"

#include "osape-d21/osape/osap/osap.h"
#include "osape-d21/vertices/vt_usbSerial.h"
#include "osape-d21/vertices/ucbus/ucBusDrop.h"
#include "osape-d21/vertices/ucbus/vt_ucBusDrop.h"

// servo_pwm is on PA08, TCC0-0 

EP_ONDATA_RESPONSES onServoPositionData(uint8_t* data, uint16_t len){
  chunk_uint32 microseconds = { .bytes = { data[0], data[1], data[2], data[3] } };
  servo_writeMicroseconds(microseconds.u);
  INDLIGHT_TOGGLE;
  return EP_ONDATA_ACCEPT;
}

vertex_t* servoPositionEP = osapBuildEndpoint("servo current", onServoPositionData, nullptr);

void setup() {
  CLKLIGHT_SETUP;
  BUSLIGHT_SETUP;
  INDLIGHT_SETUP;
  // the servo driver  
  servo_setup();
  // osap setup...
  osapSetup();
  vt_usbSerial_setup();
  osapAddVertex(vt_usbSerial);
  vt_ucBusDrop_setup(false, 5);
  osapAddVertex(vt_ucBusDrop);
  // demo endpoint (?) 
  osapAddVertex(servoPositionEP);
}

#define CLK_TICK 125
unsigned long last_tick = 0;

void loop() {
  // the osap main bb 
  osapLoop(); 
  // blink 
  if(millis() > last_tick + CLK_TICK){
    BUSLIGHT_TOGGLE;
    last_tick = millis();
  }
}

void ucBusDrop_onPacketARx(uint8_t* inBufferA, volatile uint16_t len){}

void ucBusDrop_onRxISR(void){}
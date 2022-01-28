/*
drivers/a4950.cpp

generic A4950 h-bridge

Jake Read at the Center for Bits and Atoms
(c) Massachusetts Institute of Technology 2021

This work may be reproduced, modified, distributed, performed, and
displayed for any purpose, but must acknowledge the squidworks and ponyo
projects. Copyright is retained and must be preserved. The work is provided as
is; no warranty is provided, and users accept all liability.
*/

#include "servo.h"
#include "../indicators.h"

#define SERVO_PIN 8
#define SERVO_PORT 0 

void servo_setup(void){
    // D21 pin setup 
    PIN_SETUP_OUTPUT(SERVO_PORT, SERVO_PIN);
    // mux le pin -> le perip 
    PORT_WRCONFIG_Type wrconfig;
    wrconfig.bit.WRPMUX = 1;
    wrconfig.bit.WRPINCFG = 1;
    wrconfig.bit.PMUX = MUX_PA08E_TCC0_WO0;
    wrconfig.bit.PMUXEN = 1;
    wrconfig.bit.HWSEL = 0;
    wrconfig.bit.PINMASK = (uint16_t)(1 << SERVO_PIN);
    PORT->Group[SERVO_PORT].WRCONFIG.reg = wrconfig.reg;
    // now we... setup a clk 
    PM->APBCMASK.reg |= PM_APBCMASK_TCC0;
    GCLK->CLKCTRL.reg = GCLK_CLKCTRL_CLKEN | GCLK_CLKCTRL_GEN_GCLK0 | 
                        GCLK_CLKCTRL_ID_TCC0_TCC1;
    while (GCLK->STATUS.bit.SYNCBUSY);
    // then the timer ...
    // we have (I think) a 48mHz clock, if we / 16, we get 3mHz: 
    // 1 microsecond is 3 ticks
    TCC0->CTRLA.reg |= TCC_CTRLA_PRESCALER_DIV16;
    TCC0->WAVE.reg = TCC_WAVE_WAVEGEN_NPWM;
    while(TCC0->SYNCBUSY.bit.WAVE);
    // period: we want 20ms total, so 20 000 us, 60 000
    // also this is near the top of the 16bit res, nice 
    TCC0->PER.reg = 60000; 
    while(TCC0->SYNCBUSY.bit.PER);
    // startup @ 1ms, though later maybe we want to only startup on config 
    TCC0->CCB[0].reg = 0;
    TCC0->CTRLA.reg |= TCC_CTRLA_ENABLE;
}

void servo_writeMicroseconds(uint32_t microseconds){
    // constrain to top of PWM res, 
    if(microseconds > 20000){
        microseconds = 20000;
    }
    TCC0->CCB[0].reg = microseconds * 3;
}
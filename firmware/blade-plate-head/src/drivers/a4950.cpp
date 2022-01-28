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

#include "a4950.h"
#include "../indicators.h"

#define IN1_PIN 4
#define IN1_PORT 0 
#define IN2_PIN 5
#define IN2_PORT 0 

#define DEADBAND 0.01f

#define BRIDGE_OFF PIN_LO(IN1_PORT, IN1_PIN); PIN_LO(IN2_PORT, IN2_PIN)
#define BRIDGE_UP PIN_HI(IN1_PORT, IN1_PIN); PIN_LO(IN2_PORT, IN2_PIN)
#define BRIDGE_DOWN PIN_LO(IN1_PORT, IN1_PIN); PIN_HI(IN2_PORT, IN2_PIN)

void a4950_setup(void){
    // D21 pin setup 
    PIN_SETUP_OUTPUT(IN1_PORT, IN1_PIN);
    PIN_SETUP_OUTPUT(IN2_PORT, IN2_PIN);
    BRIDGE_OFF;
    // thx 2 arduino 4 the DAC, I think there is no setup for it... 
    // lol, that's it 
}

void a4950_drive(float val){
    // constrain 
    if(val > 1.0f){
        val = 1.0f;
    } else if (val < -1.0f){
        val = -1.0f;
    }
    // dir vals or deadband 
    if(val >= DEADBAND){ // UP 
        BRIDGE_UP;
    } else if (val <= -DEADBAND){ // DOWN 
        BRIDGE_DOWN;
    } else { // inside deadband, off: 
        BRIDGE_OFF;
    }    
    // looks like DAC is 10-bits, so we do 
    uint32_t dacval = 1024.0f * abs(val);
    analogWrite(A0, dacval);
    // dac 
}
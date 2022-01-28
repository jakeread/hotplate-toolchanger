/*
drivers/servo.h

basic servo signal on ATSAMD21 

Jake Read at the Center for Bits and Atoms
(c) Massachusetts Institute of Technology 2021

This work may be reproduced, modified, distributed, performed, and
displayed for any purpose, but must acknowledge the squidworks and ponyo
projects. Copyright is retained and must be preserved. The work is provided as
is; no warranty is provided, and users accept all liability.
*/

#include <Arduino.h>

// init 
void servo_setup(void);

// -1 -> 1, 
void servo_writeMicroseconds(uint32_t microseconds);
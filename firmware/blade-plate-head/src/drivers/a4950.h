/*
drivers/a4950.h

generic A4950 h-bridge 

Jake Read at the Center for Bits and Atoms
(c) Massachusetts Institute of Technology 2021

This work may be reproduced, modified, distributed, performed, and
displayed for any purpose, but must acknowledge the squidworks and ponyo
projects. Copyright is retained and must be preserved. The work is provided as
is; no warranty is provided, and users accept all liability.
*/

#include <Arduino.h>

// init 
void a4950_setup(void);

// -1 -> 1, 
void a4950_drive(float val);
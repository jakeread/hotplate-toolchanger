// compile-time configur8or 
#ifndef CONFIG_H_
#define CONFIG_H_

// for the bus: head, or drop? 
//#define UCBUS_IS_HEAD
// *genuine* max is 63 ! 
#define UCBUS_MAX_DROPS 32
#define UCBUS_IS_DROP
// and D21 or D51?
//#define UCBUS_IS_D51
#define UCBUS_IS_D21 

// 3, 2, or 1 MBaud: 
#define UCBUS_BAUD 2

// if you're using the 'module board' https://gitlab.cba.mit.edu/jakeread/ucbus-module
// the first (og) revision has an SMT header, and some of the RS485 pins are varied, 
// set this flag. otherwise, if you have thru-hole JTAG header, comment it out 
//#define IS_OG_MODULE 

#endif 
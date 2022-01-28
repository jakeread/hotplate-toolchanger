// circuit specific indicators: D21 blade-plate-head, w/ ucbus interface 
// we should have a gd pin class, ffs, could probably share between D21 and D51 

// pin helper macros 
#define PIN_BM(pin) (uint32_t)(1 << pin)
#define PIN_HI(port, pin) PORT->Group[port].OUTSET.reg = PIN_BM(pin) 
#define PIN_LO(port, pin) PORT->Group[port].OUTCLR.reg = PIN_BM(pin) 
#define PIN_TGL(port, pin) PORT->Group[port].OUTTGL.reg = PIN_BM(pin)
#define PIN_SETUP_OUTPUT(port, pin) PORT->Group[port].DIRSET.reg = PIN_BM(pin) 

// PA23: clock 
#define CLKLIGHT_ON PIN_HI(0, 23)
#define CLKLIGHT_OFF PIN_LO(0, 23)
#define CLKLIGHT_TOGGLE PIN_TGL(0, 23)
#define CLKLIGHT_SETUP PIN_SETUP_OUTPUT(0, 23); CLKLIGHT_OFF

// PA22: bus light 
#define BUSLIGHT_ON PIN_HI(0, 22)
#define BUSLIGHT_OFF PIN_LO(0, 22)
#define BUSLIGHT_TOGGLE PIN_TGL(0, 22)
#define BUSLIGHT_SETUP PIN_SETUP_OUTPUT(0, 22); BUSLIGHT_OFF

// PA15: spare
#define INDLIGHT_ON PIN_HI(0, 15)
#define INDLIGHT_OFF PIN_LO(0, 15)
#define INDLIGHT_TOGGLE PIN_TGL(0, 15)
#define INDLIGHT_SETUP PIN_SETUP_OUTPUT(0, 15); INDLIGHT_OFF

#define ERRLIGHT_ON 
#define ERRLIGHT_OFF 

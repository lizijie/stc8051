
#ifdef __SDCC

#define SFR(reg, addr) __sfr __at(addr) reg
#define SBIT(reg, addr) __sbit __at(addr) reg

#define reentrant __reentrant
// #define compact
#define small __near
#define large __far

#define data __data
#define bdata
#define idata __idata
#define pdata __pdata
#define xdata __xdata
#define code __code

#define interrupt __interrupt
#define using __using
#define _at_ __at
#define _priority_
#define _task_

#endif //End of __SDCC


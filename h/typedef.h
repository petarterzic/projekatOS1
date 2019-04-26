#ifndef TYPEDEF_H_
#define TYPEDEF_H_

typedef unsigned int Reg;
typedef unsigned int Time;
typedef unsigned long StackSize;
typedef int IVTNo;
typedef void interrupt (*fnptr)(...);

extern volatile int lockFlag;
//#define lock asm pushf;asm cli;
//#define unlock asm popf;

#define lock lockFlag = 1;
#define unlock lockFlag = 0;
/*
#define IVTPENTRYSIZE 0x4

typedef void interrupt (*PrekidnaRutina)();

#define FP_SEG( fp )( (unsigned )( void _seg * )( void far * )( fp ))
#define FP_OFF( fp )( (unsigned )( fp ))
*/
#endif /* TYPEDEF_H_ */

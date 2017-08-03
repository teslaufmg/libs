/****************************************************************/
/**					Team Formula Tesla UFMG - 2017				*/
/** PIC: 24FJ64GA004 Family										*/
/** Compiler: XC16 v1.3											*/
/** Author: Francisco Gomes Soares Sanches Manso				*/
/** License: Free - Open Source									*/
/** 															*/
/****************************************************************/

/****************************************************************/
/** 															*/
/**Requirements to use this lib: 								*/
/** 															*/
/**-"system.h" library											*/
/** 															*/
/**-Set "#define FOSC " at "system.h" with the current osc value*/
/**Ex: #define FOSC 32000000 //When using a 32MHz crystal		*/
/** 															*/
/**-Set the peripheral pin by PPS() function					*/
/**Ex: PPS(20, input, _SDI1); 									*/
/** 															*/
/**-Faith 														*/
/** 															*/
/****************************************************************/

#include "system.h"
#include <string.h>

#define Master true
#define Slave false

#define master true
#define slave false

//Set the prescaler1 as 1, 2, 3, 4, 8, 16 or 64 and prescaler2 as 1, 2, 3, 4, 5, 6, 7 or 8
//So the total prescaler is (prescaler1*prescaler2):1
//Retunrs true if any prescaler isn't in the range
unsigned char SPI2_set(int prescaler1, int prescaler2, unsigned char mode, unsigned char bits_num);

//Send data by SPI channel
void SPI2_Send(char *data, char *Buf2Receive);

unsigned int SPI2_Send_Char(unsigned int data);

//Not implemented
void SPI2_Start();

//Not implemented
void SPI2_Stop();
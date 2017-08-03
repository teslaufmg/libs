/****************************************************************/
/**					Team Formula Tesla UFMG - 2017				*/
/** PIC: 24FJ64GA004 Family										*/
/** Compiler: XC16 v1.3											*/
/** Author: Francisco Gomes Soares Sanches Manso				*/
/** License: Free - Open Source									*/
/** 															*/
/****************************************************************/

#include "spi2.h"

extern void SPI2_ISR();

void __attribute__((__interrupt__, auto_psv)) _SPI2Interrupt(void){
    SPI2_ISR();
    IFS2bits.SPI2IF = 0;
}

unsigned char SPI2_set(int prescaler1, int prescaler2, unsigned char mode, unsigned char bits_num){

	//Mode set - There are 2 prescalers
    switch(prescaler1){				//Switch the first prescaler
            case 1:
                SPI2CON1bits.PPRE = 0b11;	//Prescaler register value for 1:1 prescaler
                break;
            case 4:
                SPI2CON1bits.PPRE = 0b10;	//Prescaler register value for 4:1 prescaler
                break;
            case 16:
                SPI2CON1bits.PPRE = 0b01;	//Prescaler register value for 16:1 prescaler
                break;
            case 64:
                SPI2CON1bits.PPRE = 0b00;	//Prescaler register value for 64:1 prescaler
                break;
            default:
                return (1);				//If none of these prescalers was sent as parameter, returns an error
    }

    switch(prescaler2){			//Switch the second prescaler
            case 1:
                SPI2CON1bits.SPRE = 0b111;	//Prescaler register value for 1:1 prescaler
                break;
            case 2:
                SPI2CON1bits.SPRE = 0b110;	//Prescaler register value for 2:1 prescaler
                break;
            case 3:
                SPI2CON1bits.SPRE = 0b101;	//Prescaler register value for 3:1 prescaler
                break;
            case 4:
                SPI2CON1bits.SPRE = 0b100;	//Prescaler register value for 4:1 prescaler
                break;
            case 5:
                SPI2CON1bits.SPRE = 0b011;	//Prescaler register value for 5:1 prescaler
                break;
            case 6:
                SPI2CON1bits.SPRE = 0b010;	//Prescaler register value for 6:1 prescaler
                break;
            case 7:
                SPI2CON1bits.SPRE = 0b001;	//Prescaler register value for 7:1 prescaler
                break;
            case 8:
                SPI2CON1bits.SPRE = 0b000;	//Prescaler register value for 8:1 prescaler
                break;
            default:
                return (1);				//If none of these prescalers was sent as parameter, returns an error
    }

    if(mode == Master)
    {
        SPI2CON1bits.MSTEN = mode;
        SPI2CON1bits.MODE16 = bits_num;
        SPI2CON1bits.SMP = false;
        SPI2CON1bits.CKE = false;
        SPI2STATbits.SPIROV = false;
        SPI2STATbits.SPIEN = true;
    }
    
	else
    {
        SPI2BUF = 0;
        IFS2bits.SPI2IF = false;
        IEC2bits.SPI2IE = true;
        IPC8bits.SPI2IP = 7;
        SPI2CON2 = 0;
        SPI2CON1bits.SMP = 0;
        SPI2CON1bits.CKE = 0;
        SPI2STATbits.SPIROV = 0;
        SPI2STATbits.SPIEN = 1;	
    }
	
    SPI2CON2bits.SPIBEN = true;
	
	return (0);						//Returns no errors
}

void SPI2_Start(){			//Not implemented yet
    SPI2STATbits.SPIEN = true;
}

void SPI2_Stop(){			//Not implemented yet
	SPI2STATbits.SPIEN = false;
}

void SPI2_Send(char *data, char *Buf2Receive){
	unsigned int numBytes = 0; //Counter
    int writebufferLen = strlen((char *) data); //Get the size of the message
	
	while (numBytes < writebufferLen) { //While the counter is smaller than the size of the message
    
		while(SPI2STATbits.SPITBF);	//Wait for any current transmission
		
		SPI2BUF = data[numBytes];				//Write the byte in the register
		while(SPI2STATbits.SPITBF);	//Wait it to send
		
		while(!SPI2STATbits.SPIRBF);	//Wait for receive the data
		
		Buf2Receive[numBytes] = SPI2BUF & 0xFF;
		numBytes++;
	}
}

unsigned int SPI2_Send_Char(unsigned int data){
    
    while(SPI2STATbits.SPITBF);	//Wait for any current transmission
    
	SPI2BUF = data;				//Write the byte in the register
	while(SPI2STATbits.SPITBF);	//Wait it to send
    
    while(!SPI2STATbits.SPIRBF);	//Wait for receive the data
    return (SPI2BUF & 0xFF);
}

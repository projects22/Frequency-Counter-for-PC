//USB-SERIAL FREQUENCY COUNTER PIC16F628A
//MPLAB X v3.10 xc8 v1.45
//moty22.co.uk

#include <htc.h>

#pragma config FOSC=HS, CP=OFF, CPD=OFF, WDTE=OFF, LVP=OFF, MCLRE=OFF, BOREN=OFF

#define _XTAL_FREQ 16000000

// prototypes
void send(unsigned char bytex);

void main(void) {
    int freq, msec;
    
	CMCON = 0b00000111;		//comparator off
	T2CON = 0b111010;		//TMR2 prescale=16, postscale=1:8, TMR OFF
	T1CON = 0b110;        //TMR1 prescale 1:1, osc=off
	RCSTA = 0b10010000;		//rx enable 
	PR2 = 249;				//TMR2 period 4ms
	TXSTA = 0b00100000;		//tx status 
	SPBRG = 207;				//baud rate 1200bps
 	TRISB = 0b11100110;		 //RB 1,5,6,7 inputs

    while (1) {
 
    freq = 0;
	msec = 0;
	TMR2 = 0;
	TMR1L = 0;
	TMR1H = 0;
	TMR1IF = 0;
	TMR2IF = 0;
	TMR1ON = 1;		// open gate
	TMR2ON = 1;		// start count
	
	while (msec < 125 ){		//loop for 1 second
		if (TMR1IF){
			TMR1IF = 0;
			freq++;
			}
		if (TMR2IF){
			TMR2IF = 0;
			msec++;
			}
	}
	
	TMR1ON = 0;		//close gate 
	TMR2ON = 0;		//stop count
	send(TMR1L);	//transmit bytes
	__delay_ms(20);
	send(TMR1H);
	__delay_ms(20);
	send(freq);
	}
}

void send(unsigned char bytex){
	TXREG = bytex;
	while (!TXIF){}		//wait for UART to finish
}	



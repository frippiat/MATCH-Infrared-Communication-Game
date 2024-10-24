//Libraries
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <time.h>
#include <stdlib.h>
#include <dwenguinoBoard.h>
#include <dwenguinoLCD.h>
#include "InfraredCommunication.h"
#include "MessageOperations.h"


//Global Variables

//Indicates that the microcontroller is receiving an infrared signal. (1: signal, 0: no signal)
volatile unsigned char receivingInfraredSignal = 0;
//Represents the time span in which an infrared signal is received.
volatile unsigned int lengthSignal = 0;

//Global array in which the received message is saved.
unsigned char messageReceived[9];
//Indicates how much bits are received yet.
unsigned int indexMessageReceived;
//Global array in which the message to be send is saved.
unsigned char messageToBeSend[8] = {1, 1, 0, 1, 0, 0, 1, 0};
//Indicates how much bits are build to be send yet.
unsigned int indexMessageToBeSend;

//Flag that indicates if a message will be send.
volatile unsigned char flagSendMessage = 0;


//Interrupts and timer interrupts.

//INT0 will be called on falling and rising edge of PD0 (the infrared receiver). In the interrupt, the global variable 'ReceivingInfraredSignal' is switched from 1 to 0 or from 0 to 1.
ISR(INT0_vect)
{
    if (receivingInfraredSignal)
    {
        receivingInfraredSignal = 0;
        unsigned char bit = defineBit(lengthSignal);
        saveSignal(messageReceived, bit, &indexMessageReceived);
    }
    else
    {
        receivingInfraredSignal = 1;
        lengthSignal = 0;
    }
}

//INT5 will be called on falling edge of PE5 (South Button). In the interrupt, a flag is set so that an infrared message will be send.
ISR(INT5_vect)
{
    _delay_ms(10);
    flagSendMessage = 1;
}

//TIMER_INT1 will be called each time the timer reaches the COMPARE_VALUE. This happens (62 500 / COMPARE_VALUE) times a second. In the timer interrupt, the value of the global variable 'lengthSignal' will be incremented by 1 of the microcontroller is receiving an infrared signal.
ISR(TIMER1_COMPA_vect)
{
    if (receivingInfraredSignal) {lengthSignal += 1; }

}



int main()
{
    initBoard();
    initLCD();
    clearLCD();
    backlightOn();

    DDRA |= 0xFF;                                               //Set led's (PA0 t.e.m. PA7) as output by setting all bits of the DDRA register to 1.
    DDRB |= _BV(PB1);                                           //Set infrared led (PB1) as output by setting the second bit of the DDRB register to 1.
    DDRD &= ~(_BV(PD0));                                        //Set infrared receiver (PD0) as input by clearing the first bit of the DDRD register to 0.
    DDRE &= ~(_BV(PE4) | _BV(PE5) | _BV(PE6) | _BV(PE7));       //Set buttons (PE4 t.e.m. PE7) as input by clearing the last 4 bits of the DDRE register to 0.

    PORTA |= 0x00;                                               //Initialize led's (PA0 t.e.m. PA7) to 0. (off)
    PORTB &= ~(_BV(PB1));                                        //Initialize Infrared led pin (PB1) to 0. (off)
    PORTD |= _BV(PD0);                                           //Initialize Infrared receiver pin (PD0) to 1. (no infrared signal)
    PORTE |= (_BV(PE4) | _BV(PE5) | _BV(PE6) | _BV(PE7));        //Activate the pull-up resistance of the 4 buttons (PE4 t.e.m. PE7).

    SREG |= _BV(SREG_I);                                        //Interrupts enabled.

    EIMSK |= _BV(INT0);                                         //Enable INT0. (Connected to the infrared receiver PD0).
    EICRA &= ~(_BV(ISC01));                                     //INT0 will be called by any edge by setting the ISC01-bit of the EICRA register to 0.
    EICRA |= _BV(ISC00);                                        //INT0 will be called by any edge by setting the ISC00-bit of the EICRA register to 1.

    EIMSK |= _BV(INT5);                                         //Enable INT5. (Connected to the South button PE5).
    EICRA |= _BV(ISC51);                                        //INT5 will be called on falling edge by setting the ISC51-bit of the EICRA register to 1.
    EICRA &= ~(_BV(ISC50));                                     //INT5 will be called on falling edge by setting the ISC50-bit of the EICRA register to 0.

    TIMSK1 = _BV(OCIE1A);                                       //Setup Timer1 on Compare Match A.

    TCCR1A = 0;                                                 //Set Timer1 to CTC mode. In this way, the timer will be immidiately set to zero when the COMPARE_VALUE is reached.
    TCCR1B |= _BV(WGM12);
    TCCR1B &= ~_BV(WGM13);

    TCCR1B &= ~_BV(CS10);                                       //Set prescaler equal to 256. The timer will be counting at a rate of 62 500 ticks each second.
    TCCR1B &= ~_BV(CS11);
    TCCR1B |= _BV(CS12);

    OCR1A = COMPARE_VALUE;                                      //Set the compare value equal to COMPARE_VALUE.    


    while(1)
    {

        if (flagSendMessage){
            sendMessage(messageToBeSend);
            flagSendMessage = 0;
        }


        unsigned int i = 0;
        for (i=0; i<8; i++){ printIntToLCD(messageReceived[i], 0, i); }

    }
}
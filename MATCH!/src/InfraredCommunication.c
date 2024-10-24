/*
 * InfraredCommunication.c
 *
 *  Created on: Mai 8, 2022
 *      Author: Wannes Baes
 */


#include "InfraredCommunication.h"

void sendSignal(int bit)
{
    unsigned int i;
    unsigned int iMax;

    if (bit) {iMax = PULSES_ONE; }
    else {iMax = PULSES_ZERO; }

    for (i = 0; i < iMax ; ++i) 
    {
        PORTB ^= _BV(PB1);
        _delay_us(PERIOD);
    }

    PORTB &= ~(_BV(PB1));
    _delay_ms(1);

}

void sendMessage(unsigned char *messageToBeSend)
{
    unsigned int i;
    for (i=0; i<8; i++)
    {
        sendSignal(messageToBeSend[i]);
    }
}

char defineBit(int lengthSignal)
{
    unsigned char bit;
    unsigned int averageSignalLength = (LENGTH_SIGNAL_ONE + LENGHT_SIGNAL_ZERO)/2;

    if (lengthSignal < averageSignalLength) {bit = 0;}
    else {bit = 1;}

    return bit;
}

void saveSignal(unsigned char* messageReceived, unsigned char bit, unsigned int *indexMessageReceived)
{
    messageReceived[*indexMessageReceived] = bit;
    *indexMessageReceived = (*indexMessageReceived + 1) % 8;
}
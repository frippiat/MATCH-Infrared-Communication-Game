/*
 * MessageOperations.c
 *
 *  Created on: Mai 8, 2022
 *      Author: Wannes Baes
 */

#include "MessageOperations.h"

int decimalToBinary(int decimalNumber)
{
    unsigned int binaryNumber = 0;
    unsigned char newBit = 0;
    unsigned int digitWeight = 1;

    while (decimalNumber != 0)
    {
        newBit = decimalNumber % 2;
        binaryNumber += newBit * digitWeight;
        digitWeight *= 10;
        decimalNumber /= 2;
    }

    return binaryNumber;
}

int binaryToDecimal(int binaryNumber)
{
    unsigned int decimalNumber = 0;
    unsigned char lastBit = 0;
    unsigned int bitWeight = 1;

    while (binaryNumber !=0)
    {
        lastBit = binaryNumber % 10;
        decimalNumber += lastBit * bitWeight;
        bitWeight *= 2;
        binaryNumber /= 10;
    }

    return decimalNumber;
}

int addParityBit(int originalMessage)
{
    unsigned int newMessage = originalMessage;
    unsigned int parity = 0;
    unsigned int parityBit = 0;
    
    while (originalMessage != 0)
    {
        parity += (originalMessage % 10);
        originalMessage /= 10;
    }

    parityBit = parity % 2;
    newMessage = newMessage*10 + parityBit;

    return newMessage;
}

int addRepititionBits(int originalMessage, int repitions)
{
    unsigned int originalMessageCopie = originalMessage;
    unsigned int messageSize = 1;
    while (originalMessageCopie != 0 || originalMessageCopie != 1)
    {   
        messageSize++;
        originalMessageCopie /= 10;
    }

    unsigned int newMessage = originalMessage;
    while (repitions != 0)
    {
        newMessage = (newMessage * pow(10, messageSize)) + originalMessage;
        repitions--;
    }

    return newMessage;
}

char checkParityBit(int receivedMessage)
{
    unsigned int parity = 0;
    unsigned char lastBit = 0;

    while (receivedMessage != 0)
    {
        lastBit = receivedMessage % 10;
        receivedMessage /= 10;
        parity += lastBit;
    }

    return ((parity + 1) % 2);
}

int checkRepititionBits(int receivedMessage, int repitions)
{
    unsigned int reliableMessage = 0;
    unsigned int matches = 0;
    unsigned int messageSize = 1;
    while (receivedMessage != 0 || receivedMessage != 1)
    {   
        messageSize++;
        receivedMessage /= 10;
    }
    unsigned int i = 0;
    for (i = 0; i <= repitions; i++)
    {
        //work in progress
    }

    return 1;
}
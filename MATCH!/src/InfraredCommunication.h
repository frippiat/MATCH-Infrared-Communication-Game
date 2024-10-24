/*
 * InfraredCommunication.h
 *
 *  Created on: Mai 8, 2022
 *      Author: Wannes Baes
 */


#ifndef INFRARED_COMMUNICATION_H_
#define INFRARED_COMMUNICATION_H_

//Libraries
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <time.h>
#include <stdlib.h>
#include <dwenguinoBoard.h>
#include <dwenguinoLCD.h>
#include "MessageOperations.h"

//Macro's
#define PULSES_ONE 240
#define PULSES_ZERO 80
#define PERIOD 11
#define COMPARE_VALUE 5
#define LENGTH_SIGNAL_ONE (PULSES_ONE*PERIOD)/(16*COMPARE_VALUE)
#define LENGHT_SIGNAL_ZERO (PULSES_ZERO*PERIOD)/(16*COMPARE_VALUE)

//Functions

/*
    @brief Sends infrared signal at 38 KHz, later decoded as a binairy value.
    @param bit The binairy value (1 or 0) to be send.
    @return Void.
*/
void sendSignal(int bit);

/*
    @brief Sends the complete message that is saved in the global array 'messageToBeSend' as an infrared signal at 38 KHz.
    @param *messageToBeSend The global array that represents the message to be send.
    @return Void.
*/
void sendMessage(unsigned char *messageToBeSend);

/*
    @brief Decodes the received infrared signal to a binairy value.
    @param lengthSignal The length of the infrared signal that is received. Necessary for decoding the signal. (char pointer)
    @return The decoded binary value. (char)
*/
char defineBit(int lengthSignal);

/*
    @brief Saves the decoded signal into an global array.
    @param *messageReceived The global array that represents the received message. (char pointer)
    @param bit The decoded signal (binary value) that must be saved. (char)
    @param *indexMessageReceived Indicates how much bits are received yet. (int pointer)
    @return Void.
*/
void saveSignal(unsigned char *messageReceived, unsigned char bit, unsigned int *indexMessageReceived);


#endif
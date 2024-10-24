/*
 * MessageOperations.h
 *
 *  Created on: Mai 8, 2022
 *      Author: Wannes Baes
 */


#ifndef MESSAGE_OPERATIONS_H_
#define MESSAGE_OPERATIONS_H_

//Libraries
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <time.h>
#include <stdlib.h>
#include <dwenguinoBoard.h>
#include <dwenguinoLCD.h>
#include "InfraredCommunication.h"

//Functions

/*
    @brief Convert an decimal number into the equal binary number.
    @param decimalNumber The decimal number to be converted.
    @return The equal binary number (Int).
*/
int decimalToBinary(int decimalNumber);

/*
    @brief Convert an binary number into the equal decimal number.
    @param binaryNumber The binary number to be converted.
    @return The equal decimal number (Int).
*/
int binaryToDecimal(int binaryNumber);

/*
    @brief Adds a parity bit to an binary number. Necessary fot fault detection.
    @param originalMessage The original message (binary number) to which the parity bit must be added.
    @return The new message (binary number) with a parity bit at the end.
*/
int addParityBit(int originalMessage);

/*
    @brief Adds certain quantity of copies of the message to the original message. Necessary for fault detection and correction.
    @param originalMessage The original message (binary number) to which the message copies must be added. (int)
    @param repititions The quantity of copies to be added. (int)
    @return The new message (binary number) with repition. (int)
*/
int addRepititionBits(int originalMessage, int repitions);

/*
    @brief Checks if the pariry bit is correct. This is a way of fault detection.
    @param receivedMessage The received message as an binary number that has to be checked. (int)
    @return 1 if the parity bit check is correct, 0 if the parity bit check is incorrect. (char)
*/
char checkParityBit(int receivedMessage);

/*
    @brief Checks if the repition in the received message is correct. This is a way of fault detection. Furthermore, it searches for the most reliable repition. This is a way of fault correction.
    @param receivedMessage The received message as a binary number that has to be checked. (int) ?? int groot genoeg ??
    @param repitions The quantity of copies that are added. (int)
    @return the most reliable repition of the received message.
*/
int checkRepititionBits(int receivedMessage, int repitions);

#endif
/*
 * Converter.h
 *
 *  Created on: 2018/01/27
 *      Author: Reiji
 */

#ifndef CONVERTER_H_
#define CONVERTER_H_

#include "platform.h"

typedef union _Bytes4
{
	uint8_t bytes[4];
	uint32_t uint32;
} Bytes4;

uint32_t BytesToUInt32(uint8_t* source, uint32_t startIndex);

#endif /* CONVERTER_H_ */

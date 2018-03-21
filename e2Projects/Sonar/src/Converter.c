/*
 * Converter.c
 *
 *  Created on: 2018/01/27
 *      Author: Reiji
 */

#include "Converter.h"


uint32_t BytesToUInt32(uint8_t* source, uint32_t startIndex)
{
	Bytes4 data;
	data.bytes[0] = source[startIndex];
	data.bytes[1] = source[startIndex + 1];
	data.bytes[2] = source[startIndex + 2];
	data.bytes[3] = source[startIndex + 3];

	return data.uint32;
}

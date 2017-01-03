/*
 * Utils.cpp
 *
 *  Created on: Mar 15, 2012
 *      Author: vshakya
 */

#include <FBase.h>
#include <FTextEncoding.h>
#include <FTextAsciiEncoding.h>

#include "TizenUtils.h"

using namespace Tizen::Text;


#include <cstring>
#include <memory>

#include <FText.h>

// GetCString converts Bada string to standard C++ string type.
//callers must delete this string
std::string* Utils::GetCString(const String& sBadaStr) {
    if (sBadaStr.GetLength() == 0)
    	return null;

    AsciiEncoding ascii;
    int byteCount = 0;
    string* cString = null;
    ByteBuffer* pBuffer = ascii.GetBytesN(sBadaStr);
    if (pBuffer != null){
        byteCount = pBuffer->GetLimit();
        char* chPtrBuf = new char[byteCount + 1];
        if (chPtrBuf != null){
            pBuffer->GetArray((byte*)chPtrBuf, 0, byteCount);
            cString = new string(chPtrBuf);
            if (chPtrBuf != null)
            	delete [] chPtrBuf;
        }
        if (pBuffer != null)
        	delete pBuffer;
    }
    if (cString != null)
    	return cString;
    return null;
}


int Utils::GetRandomNumber() {
	int r = Tizen::Base::Utility::Math::Rand();
	return r;
}

/**
	 * C++ version 0.4 char* style "itoa":
	 * Written by Lukás Chmela
	 * Released under GPLv3.
	 */
	char* Utils::my_itoa(int value, char* result, int base) {
		// check that the base if valid
		if (base < 2 || base > 36) { *result = '\0'; return result; }

		char* ptr = result, *ptr1 = result, tmp_char;
		int tmp_value;

		do {
			tmp_value = value;
			value /= base;
			*ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz" [35 + (tmp_value - value * base)];
		} while ( value );

		// Apply negative sign
		if (tmp_value < 0) *ptr++ = '-';
		*ptr-- = '\0';
		while(ptr1 < ptr) {
			tmp_char = *ptr;
			*ptr--= *ptr1;
			*ptr1++ = tmp_char;
		}
		return result;
	}

const char* Utils::GenerateStrName(const char* aStr, int aRandomNum) {
	std::string s(aStr);
	char buffer[34] = {0};
	my_itoa(aRandomNum,buffer,10);

	s.append("-");
	s.append(buffer);
	return s.c_str();
}



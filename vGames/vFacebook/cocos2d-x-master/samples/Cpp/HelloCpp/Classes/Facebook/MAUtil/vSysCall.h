//
//  vSysCall.h
//  HelloCpp
//
//  Created by Virendra Shakya on 11/2/13.
//
//

#ifndef __HelloCpp__vSysCall__
#define __HelloCpp__vSysCall__

#include "MAUtil/vConstants.h"

MAHandle maCreatePlaceholder();

int maGetDataSize(MAHandle data);

void maReadData(MAHandle data, void* dst, int offset, int size);

void maWriteData(MAHandle data, const void* src, int offset, int size);

void maDestroyObject(MAHandle handle);

int maCreateImageFromData(MAHandle placeholder, MAHandle data, int offset, int size);

int maCreateData(MAHandle placeholder, int size);

void maDestroyPlaceholder(MAHandle handle);


//connection


MAHandle maConnect(const char* url);
void maConnClose(MAHandle conn);
int maConnGetAddr(MAHandle conn, MAConnAddr* addr);
void maConnRead(MAHandle conn, void* dst, int size);
void maConnReadFrom(MAHandle conn, void* dst, int size, MAConnAddr* src);
void maConnWrite(MAHandle conn, const void* src, int size);
void maConnWriteTo(MAHandle conn, const void* src, int size, const MAConnAddr* dst);
void maConnReadToData(MAHandle conn, MAHandle data, int offset, int size);
void maConnWriteFromData(MAHandle conn, MAHandle data, int offset, int size);
MAHandle maHttpCreate(const char* url, int method);
void maHttpSetRequestHeader(MAHandle conn, const char* key, const char* value) ;
int maHttpGetResponseHeader(MAHandle conn, const char* key, char* buffer, int bufSize) ;
void maHttpFinish(MAHandle conn);


#endif /* defined(__HelloCpp__vSysCall__) */

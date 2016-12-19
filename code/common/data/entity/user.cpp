//
//  user.cpp
//  test-chat-lmdb
//
//  Created by Virendra Shakya on 1/16/16.
//  Copyright © 2016 Virendra Shakya. All rights reserved.
//

#include <strstream>
#include "user.hpp"
#include "packer.hpp"
#include "unpacker.hpp"
#include "primary_key.hpp"
#include "ez_reader.hpp"
#include "trace.h"

vsModelBase* vsUser::copy()
    {
    vsModelBase* obj = new vsUser("");
    return obj;
    }


const string& vsUser::primaryKey() const
	{ TRACE
	return iUserName;
	}

const vs_int32_t vsUser::recordSize() const
	{ TRACE
	vs_int32_t flatRecordSize = (vs_int32_t)(
									iUserName.length()	+ sizeof(vs_uint32_t) +
									iFullName.length()	+ sizeof(vs_uint32_t) +
									iEMail.length()			+ sizeof(vs_uint32_t) +
									iPassword.length()	+ sizeof(vs_uint32_t) +
									iSecurity.length()	+ sizeof(vs_uint32_t) +
									sizeof(iCreationDate) +
									sizeof(iModificationDate));
	
	return flatRecordSize;
	}

bool vsUser::pack(TPacker& aPacker)
	{ TRACE
	bool ret = false;
	while (true)
		{
		if ( !(aPacker.writeUint32((vs_uint32_t)iUserName.length())) ) {break;}
		if ( !(aPacker.writeChars((const vs_int8_t*)iUserName.c_str(), (vs_uint32_t)iUserName.length())) ) {break;}
		
		if ( !(aPacker.writeUint32((vs_uint32_t)iFullName.length())) ) {break;}
		if ( !(aPacker.writeChars((const vs_int8_t*)iFullName.c_str(), (vs_uint32_t)iFullName.length())) ) {break;}
		
		if ( !(aPacker.writeUint32((vs_uint32_t)iEMail.length())) ) {break;}
		if ( !(aPacker.writeChars((const vs_int8_t*)iEMail.c_str(), (vs_uint32_t)iEMail.length())) ) {break;}
		
		if ( !(aPacker.writeUint32((vs_uint32_t)iPassword.length())) ) {break;}
		if ( !(aPacker.writeChars((const vs_int8_t*)iPassword.c_str(), (vs_uint32_t)iPassword.length())) ) {break;}
		
		if ( !(aPacker.writeUint32((vs_uint32_t)iSecurity.length())) ) {break;}
		if ( !(aPacker.writeChars((const vs_int8_t*)iSecurity.c_str(), (vs_uint32_t)iSecurity.length())) ) {break;}
		
		if ( !(aPacker.writeUint64((vs_uint64_t)iCreationDate)) ) {break;}
		if ( !(aPacker.writeUint64((vs_uint64_t)iModificationDate)) ) {break;}
		
		ret = true;
		break;
		} //while
	return ret;
	}


bool vsUser::unPack(TUnPacker& aUnPacker)
	{ TRACE
	bool ret = false;
	while (true)
		{
			//userName
		if (!extractString(aUnPacker, iUserName)) break;
			//iFullName
		if (!extractString(aUnPacker, iFullName)) break;
			//iEMail
		if (!extractString(aUnPacker, iEMail)) break;
			//iPassword
		if (!extractString(aUnPacker, iPassword)) break;
			//iSecurity
		if (!extractString(aUnPacker, iSecurity)) break;
			//iCreationDate
		if (!extractInt64(aUnPacker, iCreationDate)) break;
			//iModificationDate
		if (!extractInt64(aUnPacker, iModificationDate)) break;
		
		ret = true;
		break;
		}
	return ret;
	}

vsUser::vsUser( const string& aUserName,
					const string& aFullName,
					const string& aEMail,
					const string& aPassword,
					const string& aSecurity,
					const long& aCreationDate,
					const long& aModificationDate)
	: iUserName(aUserName)
	, iFullName(aFullName)
	, iEMail(aEMail)
	, iPassword(aPassword)
	, iSecurity(aSecurity)
	, iCreationDate(aCreationDate)
	, iModificationDate(aModificationDate)
	{ TRACE
	}
vsUser::vsUser(const string& aUserName)
	: iUserName(aUserName)
	, iFullName("")
	, iEMail("")
	, iPassword("")
	, iSecurity("")
	, iCreationDate(0)
	, iModificationDate(0)
	{ TRACE
	}
vsUser::~vsUser()
	{ TRACE
	}

#if 0
void vsUser::debugDump() const
	{
	strstream s;
	s << " UserName:[" << iUserName << "], FullName:[" << iFullName << "], Email:[" << iEMail << "], Password:[" << iPassword << "], Security:[" << iSecurity << "], CreationDate:[" << iCreationDate << "], ModififcationDate:[" << iModificationDate << "]";
	string user = s.str();
	LOG("\t User = {%s} \n", user.c_str());
	}
#endif


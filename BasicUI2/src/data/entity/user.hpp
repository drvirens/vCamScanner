//
//  user.hpp
//  test-chat-lmdb
//
//  Created by Virendra Shakya on 1/16/16.
//  Copyright © 2016 Virendra Shakya. All rights reserved.
//

#ifndef user_hpp
#define user_hpp

#include <string>
#include "base_model.hpp"

using namespace std;

class vsUser : public vsModelBase
	{
public:
	vsUser( const string& aUserName,
					const string& aFullName,
					const string& aEMail,
					const string& aPassword,
					const string& aSecurity,
					const long& aCreationDate,
					const long& aModificationDate);
	vsUser(const string& aUserName);
	virtual ~vsUser();
	
	//vsModelBase
	virtual const string& primaryKey() const;
	virtual const vs_int32_t recordSize() const;
	virtual bool pack(TPacker& aPacker);
	virtual bool unPack(TUnPacker& aPacker);
	
	const string& userName() const { return iUserName; }
	const string& fullName() const { return iFullName; }
	const string& email() const { return iEMail; }
	const string& password() const { return iPassword; }
	const string& security() const { return iSecurity; }
	vs_uint64_t creationDate() const { return iCreationDate; }
	vs_uint64_t modificationDate() const { return iModificationDate; }
	
	//TUID uid() const;
	
#if defined DEBUG
	void debugDump() const;
#endif
	
private:
	string iUserName;
	string iFullName;
	string iEMail;
	string iPassword;
	string iSecurity;
	vs_uint64_t iCreationDate;
	vs_uint64_t iModificationDate;
	};

#endif /* user_hpp */

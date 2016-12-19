//
//  document.cpp
//  vsopencvios
//
//  Created by Virendra Shakya on 12/3/16.
//  Copyright © 2016 Virendra Shakya. All rights reserved.
//

#include <strstream>
#include <sstream>
#include "document.hpp"
#include "packer.hpp"
#include "unpacker.hpp"
#include "primary_key.hpp"
#include "ez_reader.hpp"
#include "trace.h"
#include "document_id.hpp"

const string& vsDocument::primaryKey() const
    { TRACE
    return iDocID;
    }

const vs_int32_t vsDocument::recordSize() const
    { TRACE
    vs_int32_t flatRecordSize = (vs_int32_t)(
                                             iDocID.length()	+ sizeof(vs_uint32_t) +
                                             iTitle.length()	+ sizeof(vs_uint32_t) +
                                             sizeof(iDateCreated)  +
                                             sizeof(iDateUpdated)  +
                                             sizeof(iSize)         +
                                             iOriginalPhotoHref.length() + sizeof(vs_uint32_t) +
                                             iModifiedLargePhotoHref.length() + sizeof(vs_uint32_t) +
                                             iCategoryName.length()	         + sizeof(vs_uint32_t));
    
    return flatRecordSize;
    }

bool vsDocument::pack(TPacker& aPacker)
    { TRACE
    bool ret = false;
    while (true)
    {
        if ( !(aPacker.writeUint32((vs_uint32_t)iDocID.length())) ) {break;}
        if ( !(aPacker.writeChars((const vs_int8_t*)iDocID.c_str(), (vs_uint32_t)iDocID.length())) ) {break;}

        if ( !(aPacker.writeUint32((vs_uint32_t)iTitle.length())) ) {break;}
        if ( !(aPacker.writeChars((const vs_int8_t*)iTitle.c_str(), (vs_uint32_t)iTitle.length())) ) {break;}
        
        if ( !(aPacker.writeUint64((vs_uint64_t)iDateCreated)) ) {break;}
        if ( !(aPacker.writeUint64((vs_uint64_t)iDateUpdated)) ) {break;}
        if ( !(aPacker.writeUint64((vs_uint64_t)iSize)) ) {break;}
        
        if ( !(aPacker.writeUint32((vs_uint32_t)iOriginalPhotoHref.length())) ) {break;}
        if ( !(aPacker.writeChars((const vs_int8_t*)iOriginalPhotoHref.c_str(), (vs_uint32_t)iOriginalPhotoHref.length())) ) {break;}
        
        if ( !(aPacker.writeUint32((vs_uint32_t)iModifiedLargePhotoHref.length())) ) {break;}
        if ( !(aPacker.writeChars((const vs_int8_t*)iModifiedLargePhotoHref.c_str(), (vs_uint32_t)iModifiedLargePhotoHref.length())) ) {break;}
        
        if ( !(aPacker.writeUint32((vs_uint32_t)iCategoryName.length())) ) {break;}
        if ( !(aPacker.writeChars((const vs_int8_t*)iCategoryName.c_str(), (vs_uint32_t)iCategoryName.length())) ) {break;}
        
        ret = true;
        break;
    } //while
    return ret;
    }

bool vsDocument::unPack(TUnPacker& aUnPacker)
    { TRACE
    bool ret = false;
    while (true)
        {
        if (!extractString(aUnPacker,   iDocID)) break;
        if (!extractString(aUnPacker,   iTitle)) break;
        if (!extractInt64(aUnPacker,    iDateCreated)) break;
        if (!extractInt64(aUnPacker,    iDateUpdated)) break;
        if (!extractInt64(aUnPacker,    iSize)) break;
        if (!extractString(aUnPacker,   iOriginalPhotoHref)) break;
        if (!extractString(aUnPacker,   iModifiedLargePhotoHref)) break;
        if (!extractString(aUnPacker,   iCategoryName)) break;
        ret = true;
        break;
        }
    return ret;
    }

vsDocument::vsDocument(const string& aTitle,
                       const vs_uint64_t& aDateCreated,
                       const vs_uint64_t& aDateUpdated,
                       const vs_uint64_t& aSize,
                       const string& aOriginalPhotoHref,
                       const string& aModifiedLargePhotoHref,
                       const string& aCategoryName)
: iTitle(aTitle)
, iDateCreated(aDateCreated)
, iDateUpdated(aDateUpdated)
, iSize(aSize)
, iOriginalPhotoHref(aOriginalPhotoHref)
, iModifiedLargePhotoHref(aModifiedLargePhotoHref)
, iCategoryName(aCategoryName)
    { TRACE
    retrieveLastDocID(iDocID);
    }
    
vsDocument::vsDocument(const vsDocument& rhs)
    { TRACE
    if (this != &rhs)
        {
        iDocID = rhs.iDocID;
        iTitle = rhs.iTitle;
        iDateCreated = rhs.iDateCreated;
        iDateUpdated = rhs.iDateUpdated;
        iSize = rhs.iSize;
        iOriginalPhotoHref = rhs.iOriginalPhotoHref;
        iModifiedLargePhotoHref = rhs.iModifiedLargePhotoHref;
        iCategoryName = rhs.iCategoryName;
        }
    }

vsDocument::vsDocument()
: iDocID()
, iTitle("")
, iDateCreated(0)
, iDateUpdated(0)
, iSize(0)
, iOriginalPhotoHref("")
, iModifiedLargePhotoHref("")
, iCategoryName("")
    { TRACE
    }

vsModelBase* vsDocument::copy()
    { TRACE
    vsDocument* obj = new vsDocument(*this);
    return obj;
    }

vsDocument::~vsDocument()
    { TRACE
    }

#if 0
void vsDocument::debugDump() const
    {
    strstream s;
    s << " iTitle:[" << iTitle << "], iDateCreated:[" << iDateCreated << "], iDateUpdated:[" << iDateUpdated << "], iSize:[" << iSize << "], iOriginalPhotoHref:[" << iOriginalPhotoHref << "], iModifiedLargePhotoHref:[" << iModifiedLargePhotoHref << "], iCategoryName:[" << iCategoryName << "]";
    string user = s.str();
    LOG("\t User = {%s} \n", user.c_str());
    }
#endif

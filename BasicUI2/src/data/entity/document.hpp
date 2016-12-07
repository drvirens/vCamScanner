//
//  document.hpp
//  vsopencvios
//
//  Created by Virendra Shakya on 12/3/16.
//  Copyright © 2016 Virendra Shakya. All rights reserved.
//

#ifndef document_hpp
#define document_hpp

#include <string>
#include "base_model.hpp"

using namespace std;

/**
 Document
    - docID				   // Primary key
	- title                // User supplied or app-generated name of this document. Is displayed to user //
	- dateCreated          // When was this doc first created? //
	- dateUpdated          // When was this doc last updated? //
	- size                 // size in bytes //
	- originalPhotoHref    // local or cloud based file path to original pic - cloud-path is not for phase1 //
	- modifiedLargePhotoHref // local or cloud based file path to opencv processed file //
	- fileType             // this is needed for generating pdf etc later using ocr //
 ------:: Phase II ::-----
	- modifiedMediumPhotoHref       // phase 2 - local or cloud based file path to opencv processed file //
	- modifiedThumbnailPhotoHref    // phase 2 - local or cloud based file path to opencv processed file //
	- uploadDate           // phase 2 - when was this doc uploaded to our backend? //
	- latitude             // phase 2 - where was this document scanned?  //
	- longitude            // phase 2 - where was this document scanned? //
	- ocrTextHref          // phase 2 - cache the ocr contents for faster processing //
 
 related to:
 -Credentials (cred)
 -User (owner)
 -Category (category)
 
 */
class vsDocument : public vsModelBase
{
public:
    vsDocument(const string& aTitle,
               const vs_uint64_t& aDateCreated,
               const vs_uint64_t& aDateUpdated,
               const vs_uint64_t& aSize,
               const string& aOriginalPhotoHref,
               const string& aModifiedLargePhotoHref,
               const string& aFileType);
    virtual ~vsDocument();
    
    //vsModelBase
    virtual const string& primaryKey() const;
    virtual const vs_int32_t recordSize() const;
    virtual bool pack(TPacker& aPacker);
    virtual bool unPack(TUnPacker& aPacker);
    
    const string& docID() const { return iDocID; }
    const string& title() const { return iTitle; }
    
    const string& originalPhotoHref() const { return iOriginalPhotoHref; }
    const string& modifiedLargePhotoHref() const { return iModifiedLargePhotoHref; }
    const string& fileType() const { return iFileType; }
    
    vs_uint64_t dateCreated() const { return iDateCreated; }
    vs_uint64_t dateUpdated() const { return iDateUpdated; }
    vs_uint64_t size() const { return iSize; }
#if defined DEBUG
    void debugDump() const;
#endif
    
private:
    string iDocID; //primary key
    string iTitle;
    vs_uint64_t iDateCreated;
    vs_uint64_t iDateUpdated;
    vs_uint64_t iSize;
    string iOriginalPhotoHref;
    string iModifiedLargePhotoHref;
    string iFileType;
};

#endif /* document_hpp */

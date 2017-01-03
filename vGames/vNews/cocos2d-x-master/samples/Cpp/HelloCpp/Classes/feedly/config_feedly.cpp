//
//  config_feedly.cpp
//  HelloCpp
//
//  Created by Virendra Shakya on 11/29/13.
//
//

#include "feedly/config.h"

const  std::string FeedlyAuth          () { std::string baseUrl(FeedlyBase); baseUrl.append("/auth/auth"); return baseUrl; }
const   std::string FeedlyAuthToken     () { std::string baseUrl(FeedlyBase); baseUrl.append("/auth/token"); return baseUrl; }
const   std::string FeedlyPreferences   () { std::string baseUrl(FeedlyBase); baseUrl.append("/preferences"); return baseUrl; }
const   std::string FeedlyProfile       () { std::string baseUrl(FeedlyBase); baseUrl.append("/profile"); return baseUrl; }
const    std::string FeedlyCategories    () { std::string baseUrl(FeedlyBase); baseUrl.append("/categories"); return baseUrl; }
const   std::string FeedlySubscriptions () { std::string baseUrl(FeedlyBase); baseUrl.append("/subscriptions"); return baseUrl; }
const   std::string FeedlyMarkers       () { std::string baseUrl(FeedlyBase); baseUrl.append("/markers/counts"); return baseUrl; }
const   std::string FeedlyFeeds		     () { std::string baseUrl(FeedlyBase); baseUrl.append("/feeds/:feedId"); return baseUrl; }

  //const std::string FeedlyStream        () { std::string baseUrl(FeedlyBase); baseUrl.append("/streams/"); return baseUrl; }
const   std::string FeedlyStream        () { std::string baseUrl(FeedlyBase); baseUrl.append("/streams/ids?streamId="); return baseUrl; }
const   std::string FeedlyStreamContent () { std::string baseUrl(FeedlyBase); baseUrl.append("/streams/contents?streamId="); return baseUrl; }
const   std::string FeedlyEntriesMget   () { std::string baseUrl(FeedlyBase); baseUrl.append("/entries/.mget"); return baseUrl; }
const   std::string FeedlyMarkEntryRead () { std::string baseUrl(FeedlyBase); baseUrl.append("/markers"); return baseUrl; }
const   std::string FeedlyMarkFeedRead  () { std::string baseUrl(FeedlyBase); baseUrl.append("/markers"); return baseUrl; }


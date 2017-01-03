#ifndef __FEEDLY_API_CONFIG_H__
#define __FEEDLY_API_CONFIG_H__


#include "feedly/feedly_apikey.h" // client_id and client_secret hidden here, ignored by git

#include <string>

using namespace std;

//viren added 1
#define RELEASEBUILD 1


const std::string RedirectURL = "http://localhost";
//const CCString RedirectURL = "urn:ietf:wg:oauth:2.0:oob";
const std::string Scope = "https://cloud.feedly.com/subscriptions";

#ifdef RELEASEBUILD
const std::string ClientId = FeedlyClientId;
const std::string ClientSecret = FeedlyClientSecret;
const std::string FeedlyBase = "http://cloud.feedly.com/v3";
#else
const CCString ClientId = FeedlyClientIdDev;
const CCString ClientSecret = FeedlyClientSecretDev;
const std::string FeedlyBase = "http://sandbox.feedly.com/v3";
#endif

// ***************  methods consts *************************

const  std::string FeedlyAuth          () ;
const   std::string FeedlyAuthToken     () ;
const   std::string FeedlyPreferences   () ;
const   std::string FeedlyProfile       () ;
const    std::string FeedlyCategories    () ;
const   std::string FeedlySubscriptions () ;
const   std::string FeedlyMarkers       () ;
const   std::string FeedlyFeeds		     () ;
  //const std::string FeedlyStream        () { std::string baseUrl(FeedlyBase); baseUrl.append("/streams/"); return baseUrl; }
const   std::string FeedlyStream        () ;
const   std::string FeedlyStreamContent () ;
const   std::string FeedlyEntriesMget   () ;
const   std::string FeedlyMarkEntryRead () ;
const   std::string FeedlyMarkFeedRead  () ;


#endif // __FEEDLY_API_CONFIG_H__

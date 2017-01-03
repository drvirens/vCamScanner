//#include <QDebug>
//#include <QSettings>
//#include <QDateTime>

#include "feedly/feedlyapi.h"
#include "feedly/config.h"
//#include "libs/logger.h"
#include "cocos2d.h"

#include "feedly/models/feedsmodel.h"
#include "feedly/models/profilemodel.h"
#include "feedly/models/entriesmodel.h"
#include "feedly/models/bk/categorymodel.h"

//viren+
void FeedlyApi::setUrl(std::string& aUrl) {
  
}
//viren-

FeedlyApi::FeedlyApi()
{
//    logger = Logger::instance();
    //connect(&parser, SIGNAL(gotAccesstoken(const std::string&)),this, SLOT(gotAccessToken(const std::string &)));
}

bool FeedlyApi::beginAuth()
{
    std::string url;
    url = FeedlyAuth();

    std::string args;
//    args = std::string("?response_type=code&client_id=%1&redirect_uri=%2").arg(ClientId).arg(RedirectURL);
//    args.append(std::string("&scope=%1").arg(Scope)  );
//    //args = args.toHtmlEscaped();
    url.append(args);

    //CCLOG( std::string("Url: %1").arg(url));
    setUrl(url);


    CCLOG("******************* beginAuth **************************");
    CCLOG("******************* ********* **************************");
//    startRequest(Get, GetString);
//
//    if(getError()) {
//        //TODO::handle error
//        return false;
//    }
//    /* emit */ loadAuthorizationPage(getResult(), FeedlyBase);
    return true;
}

bool FeedlyApi::getProfile()
{
    std::string url;
    url = FeedlyProfile();
    setUrl(url);

    CCLOG("******************* getProfile **************************");
    CCLOG("******************* ********** **************************");
//    startRequest(Get, GetString);
//
//    if(getError()) {
//        handleError();
//        return false;
//    }
//    parser.parseResponse(getResult(), FeedlyParser::Profile);
    return true;
}

bool FeedlyApi::getPreferences()
{
    std::string url;
    url = FeedlyPreferences();
    setUrl(url);

    CCLOG("******************* getPreferences **************************");
    CCLOG("******************* ************** **************************");
//    startRequest(Get, GetString);
//
//    if(getError()) {
//        handleError();
//        return false;
//    }
//    parser.parseResponse(getResult(), FeedlyParser::Preferences);
    return true;
}

bool FeedlyApi::getCategories()
{
    std::string url;
    url = FeedlyCategories();
    setUrl(url);

    CCLOG("******************* getCategories **************************");
    CCLOG("******************* ************* **************************");
//    startRequest(Get, GetString);
//
//    if(getError()) {
//        parser.parseResponse(getResult(), FeedlyParser::Categories);
//        handleError();
//        return false;
//    }
//    parser.parseResponse(getResult(), FeedlyParser::Categories);
    return true;
}

bool FeedlyApi::getSubscriptions()
{
    std::string url;
    url = FeedlySubscriptions();
    setUrl(url);

    CCLOG("******************* getSubscriptions **************************");
    CCLOG("******************* **************** **************************");
//    startRequest(Get, GetString);
//
//    if(getError()) {
//        handleError();
//        return false;
//    }
//    //printResult();
//    parser.parseResponse(getResult(), FeedlyParser::Subscriptions);


    return true;
}

bool FeedlyApi::getMarkers()
{
    std::string url;
    url = FeedlyMarkers();
    setUrl(url);

    CCLOG("******************* getMarkers **************************");
    CCLOG("******************* ********** **************************");
//    startRequest(Get, GetString);
//
//    if(getError()) {
//        handleError();
//        return false;
//    }
//    //printResult();
//    parser.parseResponse(getResult(), FeedlyParser::Markers);
    return true;
}

bool FeedlyApi::getStream(const std::string &id)
{
    std::string url;
    url = FeedlyStream();

    url.append(id);
    setUrl(url);

    CCLOG("******************* getStream **************************");
    CCLOG("******************* ********** **************************");
//    startRequest(Get, GetString);
//
//    if(getError()) {
//        handleError();
//        return false;
//    }
//    printResult();
//    CCLOG("******************* ********** **************************");
//    CCLOG("******************* ********** **************************");
//    CCLOG("******************* ********** **************************");
//    //parser.parseResponse(getResult(), FeedlyParser::Markers);
    return true;
}

bool FeedlyApi::getEntriesMgetFromFeedId(const std::string &feedId)
{
    std::string url;
    url = FeedlyStream();
//    url.append(QUrl::toPercentEncoding(feedId));
    setUrl(url);

    //qDebug() << "feedId: " << feedId;
    CCLOG("******************* getStream **************************");
    CCLOG("******************* ********** **************************");
//    startRequest(Get, GetString);
//
//    if(getError()) {
//        handleError();
//        return false;
//    }
//    //qDebug() << "results: " << getResult();
//
//    url = FeedlyEntriesMget();
//    setUrl(url);
//    setContent(getResult());
//
//    CCLOG("******************* getEntriesMget **************************");
//    CCLOG("******************* ************** **************************");
//    startRequest(Post, GetString);
//
//    if(getError()) {
//        handleError();
//        return false;
//    }
//    //printResult();
//    parser.parseResponse(getResult(), FeedlyParser::EntriesMget);
    return true;
}

bool FeedlyApi::markEntryAsRead(const std::string &id)
{
    std::string url;
    url = FeedlyMarkEntryRead();

    setUrl(url);
    //TODO:: need to get to work on a json generator
//    std::string jsonString = std::string("{ \"action\": \"markAsRead\", \"type\": \"entries\", \"entryIds\": [\"%1\"]}").arg(id);

//    qDebug() << "jsonString: " << jsonString;
//
//
//    setContent(jsonString);
//    CCLOG("******************* MarkEntryAsRead **************************");
//    CCLOG("******************* *************** **************************");
//    startRequest(Post, GetString);
//
//    if(getError()) {
//        handleError();
//        return false;
//    }
//    printResult();
    return true;
}

bool FeedlyApi::markFeedAsRead(const std::string &id)
{
    std::string url;
    url = FeedlyMarkFeedRead();

    setUrl(url);

    //TODO:: need to get to work on a json generator
    //std::string jsonString = std::string("{ \"action\": \"markAsRead\", \"type\": \"feeds\", \"feedIds\": [\"%1\"], \"lastReadEntryId\": \"%2\" }").arg(id);
//    std::string jsonString = std::string("{ \"action\": \"markAsRead\", \"type\": \"feeds\", \"feedIds\": [\"%1\"], \"asOf\": \"%2\" }").arg(id).arg(QDateTime::currentMSecsSinceEpoch());
//    /*
//    {
//      "action": "markAsRead",
//      "type": "feeds",
//      "feedIds": [
//        "feed/http://feeds.feedburner.com/design-milk"
//      ],
//      "lastReadEntryId": "c805fcbf-3acf-4302-a97e-d82f9d7c897f"
//    }
//    */
//
//    qDebug() << "jsonString: " << jsonString;
//
//
//    setContent(jsonString);
//    CCLOG("******************* MarkFeedAsRead **************************");
//    CCLOG("******************* *************** **************************");
//    startRequest(Post, GetString);
//
//    if(getError()) {
//        handleError();
//        return false;
//    }
//    printResult();
    return true;
}


/* QNetworkReply::NetworkError */ int FeedlyApi::getFeedlyError() const
{
    //return getReply()->error();
  int err = 0;
  return err;
}

FeedModel* FeedlyApi::getFeedsModel() const
{
    //return parser.getFeedsModel();
	return 0;
}

EntriesModel* FeedlyApi::getEntriesModel() const
{
    //return parser.getEntriesModel();
	return 0;
}


void FeedlyApi::parseAuthorizationResponse(const std::string &response)
{
    CCLOG( "parseAuthorizationResponse : entered");
    std::string code;
    std::string state;
    std::string tmp = response;
//    tmp.remove("http://localhost/?");
//    QStringList parms = tmp.split("&");
//
//    foreach(std::string parm, parms) {
//        if(parm.contains("code"))
//            code = parm;
//        else if(parm.contains("state"))
//            state = parm;
//    }
//    code.remove("code=");
//    state.remove("state=");
//
//    //CCLOG( std::string("code: %1").arg(code));
//    //CCLOG( std::string("state: %1").arg(state));
//    getAuthorizationToken(code, state);
}

// setters
void FeedlyApi::setAccessToken(const std::string &token)
{
    mAccessToken = token;
}

// slots
void FeedlyApi::gotAccessToken(const std::string &accessToken)
{
    CCLOG( accessToken.c_str() );
    mAccessToken = accessToken;
//    QSettings settings;
//    settings.setValue("access_token", accessToken);
//    /* emit */ authCompleted();
}

// private
void FeedlyApi::getAuthorizationToken(const std::string &code, const std::string &state)
{
    CCLOG( "entered");
    std::string url;
//    url = FeedlyAuthToken;
//    url = url.replace("http", "https");
//
//    std::string args;
//    args = std::string("?code=%1&client_id=%2").arg(code).arg(ClientId);
//    args.append(std::string("&client_secret=%1&redirect_uri=%3").arg(ClientSecret).arg(RedirectURL));
//
//    if(!state.isEmpty())
//        args.append(std::string("&state=%1").arg(state));
//    args.append("&grant_type=authorization_code");
//    url.append(args);
//
//    setUrl(url);
//
//    startRequest(Post);
//    //printResult();
//
//    if(!getError())
//        parser.parseResponse(getResult(), FeedlyParser::AuthToken);
//    /* emit */ authCompleted();
}

void FeedlyApi::setRequestHeader()
{
//    getRequest()->setRawHeader("Content-Type", "application/json");
//    getRequest()->setRawHeader("Accept", "application/json");
//    getRequest()->setRawHeader(std::string("Content-Length").toLatin1(), QByteArray::number(getContent().size()));
//    if(!mAccessToken.isEmpty()) {
//        getRequest()->setRawHeader(QByteArray("Authorization:"), mAccessToken.toLatin1());
//    }
}

void FeedlyApi::handleError()
{
//    switch(getReply()->error()) {
//    case QNetworkReply::AuthenticationRequiredError:
//        CCLOG( "auth error, begin new auth");
//        //beginAuth();
//        break;
//    default:
//        CCLOG( std::string("unhandled error: %1").arg(getReply()->errorString()));
//        break;
//    }

}

























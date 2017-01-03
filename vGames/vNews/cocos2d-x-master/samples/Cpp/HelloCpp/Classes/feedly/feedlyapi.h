#ifndef FEEDLYAPI_H
#define FEEDLYAPI_H

//#include <QObject>

//#include "networkaccessmanager.h"
#include "feedly/feedlyparser.h"
//#include "jsonparser.h"

#include <string>
#include <vector>

#include "talk/base/sigslot.h"
using namespace std;

//class Logger;
class CategoryModel;
class FeedModel;
class EntriesModel;

#define Q_INVOKABLE

class FeedlyApi : public sigslot::has_slots<> //: public NetworkAccessManager
{
//    Q_OBJECT
public:
    explicit FeedlyApi();

    // methods
    bool beginAuth();
    bool getProfile();
    bool getPreferences();
    bool getCategories();
    bool getSubscriptions();
    bool getMarkers();
    bool getStream(const std::string &id);
    bool getEntriesMgetFromFeedId(const std::string &feedId);
    bool markEntryAsRead(const std::string &id);
    bool markFeedAsRead(const std::string &id);

    /* QNetworkReply::NetworkError */ int getFeedlyError() const;
    FeedModel* getFeedsModel() const;
    EntriesModel* getEntriesModel() const;

    Q_INVOKABLE void parseAuthorizationResponse(const std::string &response);
    // setters
    void setAccessToken(const std::string &token);
  
//signals:
//    void loadAuthorizationPage(const std::string &html, const std::string &url);
//    void authCompleted();
  sigslot::signal2<const std::string &, const std::string &> loadAuthorizationPage;
  sigslot::signal0<> authCompleted;
  
//public slots:
    void gotAccessToken(const std::string &accessToken);

private:
    void setRequestHeader();
    void getAuthorizationToken(const std::string &code, const std::string &state = "");
    void handleError();
  
    //viren+
  void setUrl(std::string& aUrl);
  //viren-

//    Logger *logger;
    FeedlyParser parser;
    std::string mAccessToken;


};

#endif // FEEDLYAPI_H


/*
feed/http://aseigo.blogspot.com/feeds/posts/default
*/

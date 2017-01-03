#ifndef FEEDLYPARSER_H
#define FEEDLYPARSER_H

//#include <QObject>
//#include <QSettings>
//
//#include "jsonparser.h"
#include "feedly/models/feedsmodel.h"
#include "feedly/models/entriesmodel.h"

#include <string>
#include <vector>

#include "talk/base/sigslot.h"
using namespace std;

//#define DEBUG

class ProfileModel;
class PreferencesModel;
class Feed;
class Entry;

class FeedlyParser //: public JsonParser
{
//    Q_OBJECT
public:
    enum Method {
        AuthToken,
        Profile,
        Preferences,
        Categories,
        Subscriptions,
        Markers,
        EntriesMget,
        None
    };
    enum EntryObjects {
        EntryCategories,
        EntryTags,
        EntryKeywords,
        EntryContent,
        EntryOrigin,
        EntryAlternative,
        EntryString,
        EntryNone
    };

     FeedlyParser() {}
    ~FeedlyParser() {}

    bool parseResponse(std::string &jsonResponse, Method method = None);
    FeedModel* getFeedsModel() const {
    	return 0;
    }
    EntriesModel* getEntriesModel() const {
    	return 0;
    }

//signals:
//    void gotAccesstoken();
    sigslot::signal0<> gotAccesstoken;
  
private:
    void initModels();
    void cleanupModels();

//    QVariant parseJsonObject(const QJsonObject &object);
//    QVariant parseJsonValue(const QJsonValue &value, const QString &keyName);
//    void parseString(const QString &value, const QString &keyName);
//    void parseDouble(const double &value, const QString &keyName);
//    void parseBool(const bool &value, const QString &keyName);
//
//    void parseSubscriptionCategories(const QVariantList &subscriptionList);
//    void parseCategories(const QVariantList &categoryList);
//    void parseMarkers(const QVariantList &markerList);
//    void parseEntries(const QJsonObject &object);


    Method apiMethod;
//    QSettings settings;

    ProfileModel *profileModel;
    PreferencesModel *preferencesModel;

    FeedModel *categoryModel;
    Feed *category;
    Feed *subscription;

    EntriesModel *entriesModel;
    Entry *entry;
    EntryObjects entryObject;

//    QStringList *subscriptionCategoryIds;
    std::string *subscriptionCategoryIds;
    int objectCounter;
};

#endif // FEEDLYPARSER_H





/*

"{"unreadcounts":[{"id":"feed/http://aseigo.blogspot.com/feeds/posts/default","count":0,"updated":1370465340002},
{"id":"feed/http://appleinsider.com.feedsportal.com/c/33975/f/616168/index.rss","count":159,"updated":1381344110176},
{"id":"feed/http://feeds.arstechnica.com/arstechnica/everything","count":241,"updated":1381520314854},
{"id":"feed/http://www.phoronix.com/rss.php","count":161,"updated":1381522168232},
{"id":"feed/http://tigraphics.blogspot.com/feeds/posts/default","count":1,"updated":1381455225439},
{"id":"feed/http://zchydem.enume.net/feed/","count":0,"updated":1359971465000},
{"id":"feed/https://tbe.taleo.net/NA5/ats/servlet/Rss?org=MTVNETWORKS&cws=1&WebPage=SRCHR&WebVersion=0&_rss_version=2","count":38,"updated":1381334291925},
{"id":"feed/http://theoatmeal.com/feed/rss","count":6,"updated":1380654214395},{"id":"feed/http://feeds.feedburner.com/CrackedRSS","count":89,"updated":1381494803082},
{"id":"feed/http://planetkde.org/rss20.xml","count":29,"updated":1381340489182}
{"id":"user/d5f1c6f6-a7fe-4e81-9333-3aa95f0ffb18/category/global.all","count":724,"updated":1381522168232},
{"id":"user/d5f1c6f6-a7fe-4e81-9333-3aa95f0ffb18/category/testing","count":0,"updated":1370465340002},
{"id":"user/d5f1c6f6-a7fe-4e81-9333-3aa95f0ffb18/category/News","count":561,"updated":1381522168232},
{"id":"user/d5f1c6f6-a7fe-4e81-9333-3aa95f0ffb18/category/Qt","count":1,"updated":1381455225439},
{"id":"user/d5f1c6f6-a7fe-4e81-9333-3aa95f0ffb18/category/X-misc","count":133,"updated":1381494803082},
{"id":"user/d5f1c6f6-a7fe-4e81-9333-3aa95f0ffb18/category/global.uncategorized","count":29,"updated":1381340489182}]}"

*/





















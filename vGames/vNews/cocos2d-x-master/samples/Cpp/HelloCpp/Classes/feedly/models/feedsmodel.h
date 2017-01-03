#ifndef FEEDSMODEL_H
#define FEEDSMODEL_H

//#include <QObject>
//#include <QAbstractListModel>
//#include <std::string>
//#include <QList>

#include <string>
#include <vector>

#include "talk/base/sigslot.h"
using namespace std;


class FeedModel;

class Feed //: public QObject
{
//    Q_OBJECT
//    //Q_PROPERTY(bool isOpened READ isOpened WRITE setIsOpened NOTIFY isOpenedChanged)
//    Q_PROPERTY(bool hasUnread READ hasUnread NOTIFY hasUnreadChanged)
//    Q_PROPERTY(bool unreadCount READ unreadCount WRITE setUnreadCount NOTIFY isUnreadChanged)
public:
    Feed();
    ~Feed();
    bool isEmpty() const;
    inline bool hasChildren() const;
    bool hasUnread();
    void adjustLevels();
    void addUnreadCount();
    void subtractUnreadCount(const int &count = 1);

    // setters
    void setId(const std::string &id);
    void setLabel(const std::string &label);
    void setSortId(const std::string &id);
    void setWebsite(const std::string &website);
    void setUnreadCount(const double &count);
    void setUpdated(const double &updated);
    void setIsOpened(const bool &opened);
    void setIsSubscription(const bool &trueFalse);
    void setIsCategory(const bool &trueFalse);
    void setLevel(const int &level);
    //void setFeedModel(FeedModel *model);
    void appendFeedModel(Feed *feed);
    // getters
    std::string id() const;
    std::string label() const;
    std::string sortId() const;
    std::string webSite() const;
    double unreadCount() const;
    double updated() const;
    bool isOpened() const;
    bool isSubscription() const;
    bool isCategory() const;
    int level() const;
    FeedModel* feedModel() const;
    //FeedModel& feedModel() const;

//signals:
  sigslot::signal0<> isOpenedChanged;
  sigslot::signal0<> isUnreadChanged;
  sigslot::signal0<> hasUnreadChanged;
//    void isOpenedChanged();
//    void isUnreadChanged();
//    void hasUnreadChanged();
private:
//    Q_DISABLE_COPY(Feed)

    std::string mId;
    std::string mLabel;
    std::string mSortId;
    std::string mWebsite;
    double mUnreadCount;
    double mUpdated;
    bool mIsOpened;
    bool mIsSubscription;
    bool misCategory;
    int mLevel;
    FeedModel *mFeedModel;
    //FeedModel mFeedModel;
};


class FeedModel //: public QAbstractListModel
{
//    Q_OBJECT
//    Q_PROPERTY(double globalUnreadItems READ globalUnreadItems WRITE setGlobalUnreadItem NOTIFY globaleUnreadItemsChanged)
public:
//    enum Roles {
//        Id = Qt::UserRole + 1,
//        Label,
//        UnreadCount,
//        Level,
//        OpenRow,
//        CloseRow,
//        IsOpened,
//        IsSubscription,
//        IsCategory,
//        HasUnread,
//        HasChildren
//    };
    FeedModel();
    ~FeedModel();

     void openRow(const int &index);
     void closeRow(const int &index);
     void markFeedAsRead(const int &index);
     void markFeedsAsRead(const int &index, const int &count);


    void subtractGlobalUnreadItems(const int &count);
    int currentIndex() const;
    void doLeveling();
    void setGlobalUnreadItem(const double &count);
    double globalUnreadItems() const;

    bool isEmpty() const;
    void clear();

    vector<Feed* > feeds() const;
    Feed* findFeedById(const std::string &id);
    void updateUnreadById(const std::string &id, const double &count,
                            const double &updated);
    Feed* at(const int &index);
    void insert(int row, Feed *feed);
    void removeAt(int row);
    void append(Feed *feed);
    int rowCount() const;
//    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
//signals:
//    void globaleUnreadItemsChanged();
    sigslot::signal0<>  globaleUnreadItemsChanged;
protected:
//    QHash<int, QByteArray> roleNames() const;
private:
//    Q_DISABLE_COPY(FeedModel)
//    QModelIndex indexFromFeed(const Feed *feed);
    vector<Feed* > mFeeds;
//    QHash<int, QByteArray> mRoleNames;
    double mGlobalUnreadItems;
    mutable int mCurrentIndex;
};

#endif // FEEDSMODEL_H












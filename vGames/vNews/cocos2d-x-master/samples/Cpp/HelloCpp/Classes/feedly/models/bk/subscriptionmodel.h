#ifndef SUBSCRIPTIONMODEL_H
#define SUBSCRIPTIONMODEL_H

//#include <QObject>
//#include <QAbstractListModel>
//#include <std::string>
//#include <QList>

#include <string>
#include <vector>
using namespace std;


class Subscription
{
public:
    Subscription();
    ~Subscription();
    inline bool hasChildren() { return false; }
    bool isEmpty() const;

    void setId(const std::string &id);
    void setTitle(const std::string &title);
    void setSortId(const std::string &sortId);
    void setUpdated(const double &updated);
    void setWebsite(const std::string &website);
    void setUnreadCount(const double &count);

    std::string id() const;
    std::string title() const;
    std::string sortId() const;
    double updated() const;
    std::string website() const;
    double unreadCount() const;
private:
    //Q_DISABLE_COPY(Subscription)
    //Subscription(const Subscription&); //no copy ctor
  
    std::string mId;
    std::string mTitle;
    std::string mSortId;
    double mUpdated;
    std::string mWebsite;
    double mUnreadCount;
};



// ****************************************
class SubscriptionModel //: public QAbstractListModel
{
    //Q_OBJECT
public:
//    enum Roles {
//        Id = Qt::UserRole + 1,
//        Title,
//        SortId,
//        Updated,
//        WebSite
//    };

    SubscriptionModel();
    ~SubscriptionModel();

    vector<Subscription* > subscriptions() const;
    bool isEmpty() const;
    void clear();
//    map<int, QByteArray> roleNames() const;
    Subscription* at(const int index);
    void updateUnreadCountsById(const std::string &id,
                                const double &count,
                                const double &updated);
    void updateSubscritionById(const Subscription &subscription);
//    int getIndexById(const std::string &id);
//    void updateSubscriptionById(const std::string &id);

    void appendRow(Subscription *subscription);
    int rowCount() const;
    //QVariant data(const QModelIndex &index, int role) const;
private:
    //Q_DISABLE_COPY(SubscriptionModel)
//    map<int, QByteArray> mRoleNames;
    vector<Subscription* > mSubscriptions;
};

#endif // SUBSCRIPTIONMODEL_H























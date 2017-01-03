//#include <QDebug>
//#include <QStringList>

#include "subscriptionmodel.h"

Subscription::Subscription()
{
    mUpdated = 0;
    mUnreadCount = 0;
}

Subscription::~Subscription()
{
}

bool Subscription::isEmpty() const
{
    return (mId.empty() && mTitle.empty() && mSortId.empty() && mWebsite.empty());
}

// setters
void Subscription::setId(const std::string &id)
{
    mId = id;
}

void Subscription::setTitle(const std::string &title)
{
    mTitle = title;
}

void Subscription::setSortId(const std::string &sortId)
{
    mSortId = sortId;
}

void Subscription::setUpdated(const double &updated)
{
    mUpdated = updated;
}

void Subscription::setWebsite(const std::string &website)
{
    mWebsite = website;
}

void Subscription::setUnreadCount(const double &count)
{
    mUnreadCount = count;
}

// getters
std::string Subscription::id() const
{
    return mId;
}

std::string Subscription::title() const
{
    return mTitle;
}

std::string Subscription::sortId() const
{
    return mSortId;
}

double Subscription::updated() const
{
    return mUpdated;
}

std::string Subscription::website() const
{
    return mWebsite;
}

double Subscription::unreadCount() const
{
    return mUnreadCount;
}



// ************* model *****************88


SubscriptionModel::SubscriptionModel() //: QAbstractListModel()
{
//    mRoleNames = roleNames();
}

SubscriptionModel::~SubscriptionModel()
{
//    foreach(Subscription *sub, mSubscriptions) {
//        delete sub;
//        mSubscriptions.clear();
//    }
}

vector<Subscription* > SubscriptionModel::subscriptions() const
{
    return mSubscriptions;
}

bool SubscriptionModel::isEmpty() const
{
    return mSubscriptions.empty();
}

void SubscriptionModel::clear()
{
    if(!mSubscriptions.empty())
        mSubscriptions.clear();
}

//map<int, QByteArray> SubscriptionModel::roleNames() const
//{
//    QHash<int, QByteArray> roles;
//    roles[Id] = "id";
//    roles[Title] = "title";
//    roles[SortId] = "sortid";
//    roles[Updated] = "updated";
//    roles[WebSite] = "website";
//    return roles;
//}

Subscription* SubscriptionModel::at(const int index)
{
    Subscription *sub = mSubscriptions.at(index);
    return sub;
}

void SubscriptionModel::updateUnreadCountsById(const std::string &id, const double &count, const double &updated)
{
    int i;
    if(id.empty())
        return;

    for(i = 0; i < mSubscriptions.size(); i++) {
        if(mSubscriptions[i]->id() == id) {
            mSubscriptions[i]->setUnreadCount(count);
            mSubscriptions[i]->setUpdated(updated);
            return;
        }
    }
}

void SubscriptionModel::updateSubscritionById(const Subscription &subscription)
{
    int i = 0;

    for(i = 0; i < mSubscriptions.size(); i++) {
        if(mSubscriptions[i]->id() == subscription.id()) {
            mSubscriptions[i]->setUnreadCount(subscription.unreadCount());
            mSubscriptions[i]->setUpdated(subscription.updated());
        }

    }
}

void SubscriptionModel::appendRow(Subscription *subscription)
{
    mSubscriptions.push_back(subscription);
}

int SubscriptionModel::rowCount() const
{
   // Q_UNUSED(parent);
    return mSubscriptions.size();
}

//QVariant SubscriptionModel::data(const QModelIndex &index, int role) const
//{
//    if(!index.isValid())
//        return QVariant();
//    if(index.row() < 0 || index.row() > mSubscriptions.count())
//        return QVariant();
//
//    if(role == Id)
//        return mSubscriptions.at(index.row())->id();
//    else if(role == Title)
//        return mSubscriptions.at(index.row())->title();
//    else if(role == Qt::DisplayRole)
//        qDebug() << "display role";
//
//    return QVariant();
//}


























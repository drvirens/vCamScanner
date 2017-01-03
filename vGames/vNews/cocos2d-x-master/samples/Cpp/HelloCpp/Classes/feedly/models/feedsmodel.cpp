//#include <QDebug>
//#include <QHash>
//#include <QByteArray>
//#include <QStringList>

#include <algorithm>
#include "feedsmodel.h"


Feed::Feed()
{
    mFeedModel = NULL;
    mUnreadCount = 0;
    mUpdated = 0;
    mIsOpened = false;
    mIsSubscription = false;
    misCategory = false;
    mLevel = 0;
}

Feed::~Feed()
{
    //FIXME:: leaking memory, but causes a crash on refresh
    // need to figure this out, might be issue with qml
    if(mFeedModel != NULL)
        delete mFeedModel;

}

bool Feed::isEmpty() const
{
     return (mId.empty() && mLabel.empty());
}

bool Feed::hasChildren() const
{
    if(mFeedModel == NULL)
        return false;
    return !mFeedModel->isEmpty();
}

bool Feed::hasUnread()
{
    bool result;
    if(mUnreadCount > 0)
        result = true;
    else
        result = false;
    /* emit */ hasUnreadChanged();
    return result;
}

void Feed::adjustLevels()
{
    if(mFeedModel == NULL)
        return;
    //foreach(Feed *feed, mFeedModel) {
    for(int i = 0; i < mFeedModel->rowCount(); i++) {
        Feed *feed = mFeedModel->at(i);
        feed->setLevel(mLevel +1);
        feed->adjustLevels();
    }
}

void Feed::addUnreadCount()
{
    mUnreadCount++;
    isUnreadChanged();
}

void Feed::subtractUnreadCount(const int &count)
{
    if(count == 1)
        mUnreadCount--;
    else
        mUnreadCount -= count;
    isUnreadChanged();
}

// setters
void Feed::setId(const std::string &id)
{
    mId = id;
}

void Feed::setLabel(const std::string &label)
{
    mLabel = label;
}

void Feed::setSortId(const std::string &id)
{
    mSortId = id;
}

void Feed::setWebsite(const std::string &website)
{
    mWebsite = website;
}

void Feed::setUnreadCount(const double &count)
{
    mUnreadCount = count;
    /* emit */ isUnreadChanged();
}

void Feed::setUpdated(const double &updated)
{
    mUpdated = updated;
}

void Feed::setIsOpened(const bool &opened)
{
    mIsOpened = opened;
    /* emit */ isOpenedChanged();
}

void Feed::setIsSubscription(const bool &trueFalse)
{
    mIsSubscription = trueFalse;
}

void Feed::setIsCategory(const bool &trueFalse)
{
    misCategory = trueFalse;
}

void Feed::setLevel(const int &level)
{
    mLevel = level;
}

/*
void Feed::setFeedModel(FeedModel *model)
{
    mFeedModel = model;
}
*/

void Feed::appendFeedModel(Feed *feed)
{
    if(mFeedModel == NULL)
        mFeedModel = new FeedModel();
    mFeedModel->append(feed);
}

// getters

std::string Feed::id() const
{
    return mId;
}

std::string Feed::label() const
{
    return mLabel;
}

std::string Feed::sortId() const
{
    return mSortId;
}

std::string Feed::webSite() const
{
    return mWebsite;
}

double Feed::unreadCount() const
{
    return mUnreadCount;
}

double Feed::updated() const
{
    return mUpdated;
}

bool Feed::isOpened() const
{
    return mIsOpened;
}

bool Feed::isSubscription() const
{
    return mIsSubscription;
}

bool Feed::isCategory() const
{
    return misCategory;
}

int Feed::level() const
{
    return mLevel;
}

FeedModel* Feed::feedModel() const
{
    return mFeedModel;
}


// *************************** model ***********************
// *********************************************************
FeedModel::FeedModel() //: QAbstractListModel()
{
//    mRoleNames = roleNames();
    mGlobalUnreadItems = 0;
    mCurrentIndex = -1;
}

FeedModel::~FeedModel()
{
    clear();
}


//void FeedModel::openRow(const int &index)
//{
//    //FIXME:: doLeveling.. need better soltuion
//    doLeveling();
//
//    if(index > (mFeeds.count() -1))
//        return;
//    if(mFeeds.at(index)->isOpened())
//        return;
//    mFeeds.at(index)->setIsOpened(true);
//
//    QModelIndex modelIndex = indexFromFeed(mFeeds.at(index));
//    emit dataChanged(modelIndex, modelIndex);
//    int i = index + 1;
//
//
//    int rowCount = 0;
//    for(int j = 0; j < mFeeds.at(index)->feedModel()->rowCount(); j++ ) {
//        Feed *feed = mFeeds.at(index)->feedModel()->at(j);
//        if(feed->hasUnread())
//            rowCount++;
//    }
//
//    //beginInsertRows(QModelIndex(), i, i + mFeeds.at(index)->feedModel()->rowCount() - 1);
//    beginInsertRows(QModelIndex(), i, i + rowCount - 1);
//
//    for(int j = 0; j < mFeeds.at(index)->feedModel()->rowCount(); j++ ) {
//        Feed *feed = mFeeds.at(index)->feedModel()->at(j);
//        if(feed->hasUnread())
//            mFeeds.insert(i++, feed);
//        //qDebug() << "feed label: " << feed->label();
//    }
//    endInsertRows();
//    emit dataChanged(QModelIndex(), QModelIndex());
//}
//
//void FeedModel::closeRow(const int &index)
//{
//    if(index > (mFeeds.count() -1))
//        return;
//    if(!mFeeds.at(index)->isOpened())
//        return;
//
//    mFeeds.at(index)->setIsOpened(false);
//    QModelIndex modelIndex = indexFromFeed(mFeeds.at(index));
//    emit dataChanged(modelIndex, modelIndex);
//
//    int i = index + 1;
//
//    //for(; i < mFeeds.size() && (mFeeds.at(i)->level() > mFeeds.at(index)->level()); ++i) {  }
//    for(; i < mFeeds.size() && (mFeeds.at(i)->level() > mFeeds.at(index)->level() && mFeeds.at(index)->hasUnread()); ++i) {  }
//    --i;
//
//    beginRemoveRows(QModelIndex(), index + 1, i);
//    while(i > index) {
//        mFeeds.at(i)->setIsOpened(false);
//        mFeeds.removeAt(i);
//        i--;
//    }
//    endRemoveRows();
//}

void FeedModel::markFeedAsRead(const int &index)
{
    markFeedsAsRead(index, 1);
}

void FeedModel::markFeedsAsRead(const int &index, const int &count)
{
//    //qDebug() << "FeedModel::markFeedsAsRead called";
//    //qDebug() << "index: " << index;
//    //qDebug() << "count: " << count;
//
//    if(index > (mFeeds.size() -1))
//        return;
//    mFeeds.at(index)->subtractUnreadCount(count);
//  
//    QModelIndex modelIndex = indexFromFeed(mFeeds.at(index));
//    /* emit */ dataChanged(modelIndex, modelIndex);
}

void FeedModel::subtractGlobalUnreadItems(const int &count)
{
    mGlobalUnreadItems -= count;
    /* emit */ globaleUnreadItemsChanged();
}

int FeedModel::currentIndex() const
{
    return mCurrentIndex;
}

void FeedModel::doLeveling()
{
    for(int i = 0; i < mFeeds.size(); i++) {
        mFeeds.at(i)->adjustLevels();
    }
}

void FeedModel::setGlobalUnreadItem(const double &count)
{
    mGlobalUnreadItems = count;
    /* emit */ globaleUnreadItemsChanged();
}

double FeedModel::globalUnreadItems() const
{
    return mGlobalUnreadItems;
}

bool FeedModel::isEmpty() const
{
    return mFeeds.empty();
}

void FeedModel::clear()
{
    //beginRemoveRows(QModelIndex(), 0, mFeeds.size());
    //if(!mFeeds.isEmpty())
    //qDeleteAll(mFeeds.begin(), mFeeds.end());
//    qDeleteAll(mFeeds);

  for (vector<Feed*>::iterator it = mFeeds.begin(); it < mFeeds.end(); it++) {
    Feed* f = *it;
    delete f;
  }
    mFeeds.clear();
    //endRemoveRows();
}

vector<Feed* > FeedModel::feeds() const
{
    return mFeeds;
}

Feed* FeedModel::findFeedById(const std::string &id)
{
//    foreach(Feed *feed, mFeeds) {
//        if(feed->id() == id)
//            return feed;
//    }
//    return NULL;
  for (vector<Feed*>::iterator it = mFeeds.begin(); it < mFeeds.end(); it++) {
    Feed* f = *it;
    if (f) {
      if (f->id() == id) {
        return f;
      }
    }
  }//end for
  
  return 0;//null
}

void FeedModel::updateUnreadById(const std::string &id, const double &count, const double &updated)
{
    int i;
    if(id.empty())
        return;
    if(mFeeds.empty())
        return;
    for(i = 0; i < mFeeds.size(); i++) {
        if(mFeeds[i]->id() == id) {
            mFeeds[i]->setUnreadCount(count);
            mFeeds[i]->setUpdated(updated);
            return;
        }
    }
}


// *************
Feed* FeedModel::at(const int &index)
{
    Feed *feed = mFeeds.at(index);
    return feed;
}

void FeedModel::insert(int row, Feed *feed)
{
//    beginInsertRows(QModelIndex(), row, row);
    //connect(feed, SIGNAL(dataChanged()), SLOT(handleItemChange()));
    mFeeds.push_back(/*row,*/ feed);
//    endInsertRows();
}

void FeedModel::removeAt(int row)
{
//    beginRemoveRows(QModelIndex(), row, row);
//    mFeeds.removeAt(row);
  //O(1) solution to delete from vector
  std::swap(mFeeds[row], mFeeds.back());
  mFeeds.pop_back();
  
//    endRemoveRows();
}

void FeedModel::append(Feed *feed)
{
    mFeeds.push_back(feed);
}

int FeedModel::rowCount() const
{
//    Q_UNUSED(parent);
    return mFeeds.size();
}

//QVariant FeedModel::data(const QModelIndex &index, int role) const
//{
//    //qDebug() << "FeedModel::data entered";
//    //qDebug() << "FeedModel::date " << "role: " <<  role << " index " << index.row();
//
//    if(!index.isValid())
//        return QVariant();
//    if(index.row() < 0 || index.row() > (mFeeds.count() - 1))
//        return QVariant();
//
//    //mCurrentIndex = index.row();
//
//    switch(role) {
//    case Id:
//        mCurrentIndex = index.row();
//        return mFeeds.at(index.row())->id();
//        break;
//    case Label:
//        return mFeeds.at(index.row())->label();
//        break;
//    case UnreadCount:
//        return mFeeds.at(index.row())->unreadCount();
//        break;
//    case Level:
//        return mFeeds.at(index.row())->level();
//        break;
//    case IsOpened:
//        return mFeeds.at(index.row())->isOpened();
//        break;
//    case IsSubscription:
//        return mFeeds.at(index.row())->isSubscription();
//        break;
//    case IsCategory:
//        return mFeeds.at(index.row())->isCategory();
//        break;
//    case HasUnread:
//        return mFeeds.at(index.row())->hasUnread();
//        break;
//    case HasChildren:
//        return mFeeds.at(index.row())->hasChildren();
//        break;
//    default:
//        //mCurrentIndex = -1;
//        break;
//    };
//    return QVariant();
//}
//
//
//// protected
//QHash<int, QByteArray> FeedModel::roleNames() const
//{
//    QHash<int, QByteArray> roles;
//    roles[Id] = "id";
//    roles[Label] = "label";
//    roles[UnreadCount] = "unreadCount";
//    roles[OpenRow] = "openRow";
//    roles[CloseRow] = "closeRow";
//    roles[Level] = "level";
//    roles[IsOpened] = "isOpened";
//    roles[IsSubscription] = "isSubscription";
//    roles[IsCategory] = "isCategory";
//    roles[HasUnread] = "hasUnread";
//    roles[HasChildren] = "hasChildren";
//    return roles;
//}
//
//// private
//QModelIndex FeedModel::indexFromFeed(const Feed *feed)
//{
//    for(int row = 0; row < mFeeds.size(); ++row) {
//        if(mFeeds.at(row) == feed)
//            return index(row);
//    }
//    return QModelIndex();
//}


































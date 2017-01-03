//#include <QDebug>
//#include <QHash>
//#include <QByteArray>
//#include <QStringList>

#include <algorithm>
#include "entriesmodel.h"

Entry::Entry()
{
    mPublished = 0;
    mUpdated = 0;
    mCrawled = 0;
    mEngagement = 0;
    mUnread = true;
}

Entry::~Entry()
{
}

//viren+
void Entry::setContentSummary(const std::string &summary) {
  mContentSummary = summary;
}
void Entry::setMediaLink(const std::string &mediaLink) {
  mMediaLink = mediaLink;
}

std::string Entry::contentSummary() const
{
  return mContentSummary;
}
std::string Entry::mediaLink() const
{
  return mMediaLink;
}

  //test+
EntriesModel* EntriesModel::createTestEntriesModel() {
  EntriesModel* em = new EntriesModel();
  
  Entry* e = new Entry();
  e->setTitle("Entry 1 Title");
  e->setContentSummary("Entry 1 summary here");
  e->setMediaLink("not done yet");
  em->append(e);
  
  e = new Entry();
  e->setTitle("Entry 2 Title");
  e->setContentSummary("Entry 2 summary here");
  e->setMediaLink("not done yet");
  em->append(e);
  
  e = new Entry();
  e->setTitle("Entry 3 Title");
  e->setContentSummary("Entry 3 summary here");
  e->setMediaLink("not done yet");
  em->append(e);
  
  e = new Entry();
  e->setTitle("Entry 4 Title");
  e->setContentSummary("Entry 4 summary here");
  e->setMediaLink("not done yet");
  em->append(e);
  
  e = new Entry();
  e->setTitle("Entry 5 Title");
  e->setContentSummary("Entry 5 summary here");
  e->setMediaLink("not done yet");
  em->append(e);
  
  e = new Entry();
  e->setTitle("Entry 6 Title");
  e->setContentSummary("Entry 6 summary here");
  e->setMediaLink("not done yet");
  em->append(e);
  
  return em;
}
  //test-

//viren-

// setters
void Entry::setEntryId(const std::string &entryId)
{
    mEntryId = entryId;
}

void Entry::setCategoryId(const std::string &id)
{
    mCategoryId = id;
}

void Entry::setOriginId(const std::string &id)
{
    mOriginId = id;
}

void Entry::setStreamId(const std::string &id)
{
    mStreamId = id;
}

void Entry::setTitle(const std::string &title)
{
    mTitle= title;
}

void Entry::setAuthor(const std::string &author)
{
    mAuthor = author;
}

void Entry::setContent(const std::string &content)
{
    mContent.setHtml(content);
//    mContent = content;
}

void Entry::setContentDirection(const std::string &direction)
{
    mContentDirection = direction;
}

void Entry::setAlternativeLink(const std::string &link)
{
    mAlternativeLink = link;
}

void Entry::setCanonicalLink(const std::string &link)
{
    mCanonicalLink = link;
}

void Entry::setFingerprint(const std::string &value)
{
    mFingerprint = value;
}

void Entry::setPulished(const double &timestamp)
{
    mPublished = timestamp;
}

void Entry::setUpdated(const double &timestamp)
{
    mUpdated = timestamp;
}

void Entry::setCrawled(const double &timestamp)
{
    mCrawled = timestamp;
}

void Entry::setEngagement(const int &value)
{
    mEngagement = value;
}

void Entry::setUnread(const bool &trueFalse)
{
    mUnread = trueFalse;
}


// getters
std::string Entry::entryId() const
{
    return mEntryId;
}

std::string Entry::categoryId() const
{
    return mCategoryId;
}

std::string Entry::originId() const
{
    return mOriginId;
}

std::string Entry::streamId() const
{
    return mStreamId;
}

std::string Entry::title() const
{
    return mTitle;
}

std::string Entry::author() const
{
    return mAuthor;
}

std::string Entry::content() const
{
    //return mContent.toHtml();
    return mContent.toPlainText();
}

std::string Entry::contentDirection() const
{
    return mContentDirection;
}

std::string Entry::alternativeLink() const
{
    return mAlternativeLink;
}

std::string Entry::canonicalLink() const
{
    return mCanonicalLink;
}

std::string Entry::fingerprint() const
{
    return mFingerprint;
}

double Entry::published() const
{
    return mPublished;
}

double Entry::updated() const
{
    return mUpdated;
}

double Entry::crawled() const
{
    return mCrawled;
}

int Entry::engagement() const
{
    return mEngagement;
}

bool Entry::unread() const
{
    return mUnread;
}


// **************** model ******************



EntriesModel::EntriesModel() //: QAbstractListModel()
{
//    mRoleNames = roleNames();
    mCurrentIndex = -1;
}

EntriesModel::~EntriesModel()
{
    clear();
}


void EntriesModel::markEntryAsRead(const int &index)
{
//    qDebug() << "EntriesModel::markEntryAsRead called";
//    if(index > (mEntries.count() -1))
//        return;
//    mEntries.at(index)->setUnread(false);
//
//    QModelIndex modelIndex = indexFromFeed(mEntries.at(index));
//    emit dataChanged(modelIndex, modelIndex);
}

int EntriesModel::markAllEntriesRead()
{
//    qDebug() << "EntriesModel::markAllEntriesRead called";
    int count = 0;
//    foreach(Entry *ent, mEntries) {
//        if(ent->unread() == true) {
//            ent->setUnread(false);
//            count++;
//        }
//    }
//    emit dataChanged(index(0), index(mEntries.size() - 1));
    return count;
}

std::string EntriesModel::getEntryUrlAtIndex(const int &index)
{
    return mEntries.at(index)->alternativeLink();
}

int EntriesModel::currentIndex() const
{
    return mCurrentIndex;
}

bool EntriesModel::isEmpty() const
{
    return mEntries.size() == 0;
}

void EntriesModel::clear()
{
//    qDeleteAll(mEntries.begin(), mEntries.end());

  for (vector<Entry*>::iterator it = mEntries.begin(); it < mEntries.end(); it++) {
    Entry* e = *it;
    delete e;
  }
    mEntries.clear();
}

Entry* EntriesModel::at(const int &index)
{
    Entry *entry = mEntries.at(index);
    return entry;
}

void EntriesModel::insert(int row, Entry *entry)
{
//    beginInsertRows(QModelIndex(), row, row);
//    //connect(feed, SIGNAL(dataChanged()), SLOT(handleItemChange()));
//    mEntries.insert(row, entry);
//    QModelIndex modelIndex = indexFromFeed(mEntries.last());
//    emit dataChanged(modelIndex, modelIndex);
//    endInsertRows();
mEntries.push_back(entry);
}

void EntriesModel::append(Entry *entry)
{
//    mEntries.append(entry);
//    QModelIndex modelIndex = indexFromFeed(mEntries.last());
//    emit dataChanged(modelIndex, modelIndex);

  mEntries.push_back(entry);
}

int EntriesModel::rowCount() const
{
//    Q_UNUSED(parent);
    return mEntries.size();
}

//QVariant EntriesModel::data(const QModelIndex &index, int role) const
//{
//    if(!index.isValid())
//        return QVariant();
//    if(index.row() < 0 || index.row() > (mEntries.count() - 1))
//        return QVariant();
//
//    //qDebug() << "EntriesModel::data entered";
//    //qDebug() << "EntriesModel::date " << "role: " <<  role << " index " << index.row();
//
//    //mCurrentIndex = index.row();
//
//    switch(role) {
//    case Content:
//        return mEntries.at(index.row())->content();
//        break;
//    case Title:
//        return mEntries.at(index.row())->title();
//        break;
//    case EntryId:
//        mCurrentIndex = index.row();
//        return mEntries.at(index.row())->entryId();
//        break;
//    case Unread:
//        return mEntries.at(index.row())->unread();
//        break;
//    default:
//        //mCurrentIndex = -1;
//        break;
//    };
//    return QVariant();
//}
//
//// protected
//QHash<int, QByteArray> EntriesModel::roleNames() const
//{
//    QHash<int, QByteArray> roles;
//    roles[Content] = "content";
//    roles[Title] = "title";
//    roles[EntryId] = "entryId";
//    roles[Unread] = "unread";
//
//    return roles;
//}
//
//// private
//QModelIndex EntriesModel::indexFromFeed(const Entry *entry)
//{
//    for(int row = 0; row < mEntries.size(); ++row) {
//        if(mEntries.at(row) == entry)
//            return index(row);
//    }
//    return QModelIndex();
//}
//



















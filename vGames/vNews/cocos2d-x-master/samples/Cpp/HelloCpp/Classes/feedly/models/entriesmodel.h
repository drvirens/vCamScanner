#ifndef ENTRIESMODEL_H
#define ENTRIESMODEL_H

//#include <QObject>
//#include <QAbstractListModel>
//#include <QTextDocument>
//#include <std::string>
//#include <QList>

#include "TextDocument.h"

#include <string>
#include <vector>

using namespace std;

class EntriesModel;

class Entry //: public QObject
{
//    Q_OBJECT
public:
    Entry();
    ~Entry();
  
    //viren+
    void setContentSummary(const std::string &summary);
    void setMediaLink(const std::string &mediaLink);
  std::string mediaLink() const;
  std::string contentSummary() const;
    //viren-

    // setters
    void setEntryId(const std::string &id);
    void setCategoryId(const std::string &id);
    void setOriginId(const std::string &id);
    void setStreamId(const std::string &id);
    void setTitle(const std::string &title);
    void setAuthor(const std::string &author);
    void setContent(const std::string &content);
    void setContentDirection(const std::string &direction);
    void setAlternativeLink(const std::string &link);
    void setCanonicalLink(const std::string &link);
    void setFingerprint(const std::string &value);
    void setPulished(const double &timestamp);
    void setUpdated(const double &timestamp);
    void setCrawled(const double &timestamp);
    void setEngagement(const int &value);
    void setUnread(const bool &trueFalse);
    // getters
    std::string entryId() const;
    std::string categoryId() const;
    std::string originId() const;
    std::string streamId() const;
    std::string title() const;
    std::string author() const;
    std::string content() const;
    std::string contentDirection() const;
    std::string alternativeLink() const;
    std::string canonicalLink() const;
    std::string fingerprint() const;
    double published() const;
    double updated() const;
    double crawled() const;
    int engagement() const;
    bool unread() const;
private:
//    Q_DISABLE_COPY(Entry)
//viren+
      std::string mContentSummary;
      std::string mMediaLink; //can be local file path
//viren-

    std::string mEntryId;
    std::string mCategoryId;
    std::string mOriginId;
    std::string mStreamId;
    std::string mTitle;
    std::string mAuthor;
    //std::string mContent;
    TextDocument mContent;

    std::string mContentDirection;
    std::string mAlternativeLink;
    std::string mCanonicalLink;
    std::string mFingerprint;
    double mPublished;
    double mUpdated;
    double mCrawled;
    int mEngagement;
    bool mUnread;

};

#define Q_INVOKABLE

class EntriesModel //: public QAbstractListModel
{
//    Q_OBJECT
public:
//    enum Roles {
//        Content = Qt::UserRole + 1,
//        Title,
//        EntryId,
//        Unread
//    };

    //test+
  static EntriesModel* createTestEntriesModel();
    //test-


    EntriesModel();
    ~EntriesModel();

    Q_INVOKABLE void markEntryAsRead(const int &index);
    Q_INVOKABLE int markAllEntriesRead();
    Q_INVOKABLE std::string getEntryUrlAtIndex(const int &index);

    int currentIndex() const;
    bool isEmpty() const;
    void clear();

    Entry* at(const int &index);
    void insert(int row, Entry *entry);
    void append(Entry *entry);
    int rowCount() const;
//    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
protected:
//    QHash<int, QByteArray> roleNames() const;
private:
//    Q_DISABLE_COPY(EntriesModel)
//    QModelIndex indexFromFeed(const Entry *entry);

    vector<Entry* > mEntries;
//    QHash<int, QByteArray> mRoleNames;
    mutable int mCurrentIndex;
};


#endif // ENTRIESMODEL_H

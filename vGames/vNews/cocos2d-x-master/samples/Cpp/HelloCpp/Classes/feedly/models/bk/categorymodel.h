#ifndef CATEGORYMODEL_H
#define CATEGORYMODEL_H

//#include <QObject>
//#include <QAbstractListModel>
//#include <std::string>
//#include <vector>

#include <string>
#include <vector>
using namespace std;

#include "subscriptionmodel.h"

class Category
{
public:
    Category();
    ~Category();
    bool isEmpty() const;
    inline bool hasChildren() const { return !mSubscriptionModel->isEmpty(); }

    // setters
    void setId(const std::string &id);
    void setLabel(const std::string &label);
    void setUnreadCount(const double &count);
    void setUpdated(const double &updated);
    void setIsOpened(const bool &opened);
    void setSubscriptionModel(SubscriptionModel *model);
    void appendSubscriptionModel(Subscription *subscription);

    // getterkis
    std::string id() const;
    std::string label() const;
    double unreadCount() const;
    double updated() const;
    bool isOpened() const;
    SubscriptionModel* subscriptionModel() const;
private:
   // Q_DISABLE_COPY(Category)
    std::string mId;
    std::string mLabel;
    double mUnreadCount;
    double mUpdated;
    bool mIsOpened;
    SubscriptionModel *mSubscriptionModel;

};


// *************** model *******************
class CategoryModel //: public QAbstractListModel
{
    //Q_OBJECT
public:
//    enum Roles {
//        Id = Qt::UserRole + 1,
//        Label,
//        Level,
//
//        OpenRow,
//        CloseRow,
//        IsOpened,
//        HasChildren
//    };
    CategoryModel();
    ~CategoryModel();
  
    //test+
  static CategoryModel* createTestCategoryModel();
  //test-

     void openRow(const int index);
     void closeRow(const int index);

    vector<Category* > categories() const;
    bool isEmpty() const;
    void clear();
    //QHash<int, QByteArray> roleNames() const;

    Category* at(const int index);
    Category* findCategoryById(const std::string &id);
    void updateCategoryById(const std::string &id, const double &count,
                            const double &updated);

    void insertRow(int row, Category *category);
    void appendRow(Category *category);
    int rowCount() const;
    //QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
//public slots:
//    void openRow(int index);
//    void closeRow(int index);
private:
    //Q_DISABLE_COPY(CategoryModel)
    //QHash<int, QByteArray> mRoleNames;
    vector<Category* > mCategories;

};






//Category(const Category &category);
//Category& operator = (const Category &category);
//bool operator == (const Category &category);

/*
Category::Category(const Category &category)
{
    mId = category.id();
    mLabel = category.label();
    mUnreadCount = category.unreadCount();
    mUpdated = category.updated();
    mIsOpened = false;
}

Category& Category::operator= (const Category &category)
{
    //if(this == category)
    //    return *this;
    mId = category.id();
    mLabel = category.label();
    mUnreadCount = category.unreadCount();
    mUpdated = category.updated();
    return *this;
}

bool Category::operator== (const Category &category)
{
    return (mId == category.id());
}
*/



//CategoryModel(const CategoryModel &model);
//CategoryModel& operator =(const CategoryModel &model);
/*
CategoryModel::CategoryModel(const CategoryModel &model) :
    QAbstractListModel()
{
    mCategories = model.categories();
}

CategoryModel& CategoryModel::operator = (const CategoryModel &model)
{
    mCategories = model.categories();
    return *this;
}
*/

#endif // CATEGORYMODEL_H

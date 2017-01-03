//#include <QDebug>
//#include <QHash>
//#include <QByteArray>
//#include <QStringList>

#include "categorymodel.h"
#include "subscriptionmodel.h"

//test+
CategoryModel* CategoryModel::createTestCategoryModel()
{
  CategoryModel* cm = new CategoryModel();
  
  //1
  Category* c = new Category();
  c->setId("Category_id_1");
  c->setLabel("Category_Label_1");
  c->setIsOpened(false);
  c->setUnreadCount(1);
  c->setUpdated(true);
  cm->appendRow(c);
  //2
  c = new Category();
  c->setId("Category_id_2");
  c->setLabel("Category_Label_2");
  c->setIsOpened(false);
  c->setUnreadCount(2);
  c->setUpdated(true);
  cm->appendRow(c);
  //3
  c = new Category();
  c->setId("Category_id_3");
  c->setLabel("Category_Label_3");
  c->setIsOpened(false);
  c->setUnreadCount(3);
  c->setUpdated(true);
  cm->appendRow(c);
  //4
  c = new Category();
  c->setId("Category_id_4");
  c->setLabel("Category_Label_4");
  c->setIsOpened(false);
  c->setUnreadCount(4);
  c->setUpdated(true);
  cm->appendRow(c);
  //5
  c = new Category();
  c->setId("Category_id_5");
  c->setLabel("Category_Label_5");
  c->setIsOpened(false);
  c->setUnreadCount(5);
  c->setUpdated(true);
  
  cm->appendRow(c);
  return cm;
}
//test-

Category::Category()
{
    mUnreadCount = 0;
    mUpdated = 0;
    mIsOpened = false;
    mSubscriptionModel = NULL;
}

Category::~Category()
{
    if(mSubscriptionModel)
        delete mSubscriptionModel;
}

bool Category::isEmpty() const
{
    return (mId.empty() && mLabel.empty());
}

// setters
void Category::setId(const std::string &id)
{
    mId = id;
}

void Category::setLabel(const std::string &label)
{
    mLabel = label;
}

void Category::setUnreadCount(const double &count)
{
    mUnreadCount = count;
}

void Category::setUpdated(const double &updated)
{
    mUpdated = updated;
}

void Category::setIsOpened(const bool &opened)
{
    mIsOpened = opened;
}

void Category::setSubscriptionModel(SubscriptionModel *model)
{
    mSubscriptionModel = model;
}

void Category::appendSubscriptionModel(Subscription *subscription)
{
    if(mSubscriptionModel == NULL)
        mSubscriptionModel = new SubscriptionModel();

    mSubscriptionModel->appendRow(subscription);
}

// getters
std::string Category::id() const
{
    return mId;
}

std::string Category::label() const
{
    return mLabel;
}

double Category::unreadCount() const
{
    return mUnreadCount;
}

double Category::updated() const
{
    return mUpdated;
}

bool Category::isOpened() const
{
    return mIsOpened;
}

SubscriptionModel* Category::subscriptionModel() const
{
    return mSubscriptionModel;
}




// ************** model *********************
CategoryModel::CategoryModel() //: QAbstractListModel()
{
//    mRoleNames = roleNames();
}

CategoryModel::~CategoryModel()
{
//    foreach(Category *cat, mCategories) {
//        delete cat;
//        mCategories.clear();
//    }
}

vector<Category* > CategoryModel::categories() const
{
    return mCategories;
}

bool CategoryModel::isEmpty() const
{
    return mCategories.empty();
}

void CategoryModel::clear()
{
    if(!mCategories.empty())
        mCategories.clear();
}

//QHash<int, QByteArray> CategoryModel::roleNames() const
//{
//    QHash<int, QByteArray> roles;
//    roles[Id] = "id";
//    roles[Label] = "label";
//    roles[OpenRow] = "openRow";
//    roles[CloseRow] = "closeRow";
//    roles[IsOpened] = "isOpened";
//    roles[HasChildren] = "hasChildren";
//    return roles;
//}

Category* CategoryModel::at(const int index)
{
    Category *cat = mCategories.at(index);
    return cat;
}

Category* CategoryModel::findCategoryById(const std::string &id)
{
//    foreach(Category *cat, mCategories) {
//        if(cat->id() == id)
//            return cat;
//    }
//    return NULL;
  
  for (vector<Category*>::iterator it = mCategories.begin(); it < mCategories.end(); it++) {
    Category* cat = *it;
    if (cat) {
      if (cat->id() == id) {
        return cat;
      }
    }
  }//end for
  
  return 0;//null
}

void CategoryModel::updateCategoryById(const std::string &id, const double &count, const double &updated)
{
    int i;
    if(id.empty())
        return;

    for(i = 0; i < mCategories.size(); i++) {
        if(mCategories[i]->id() == id) {
            mCategories[i]->setUnreadCount(count);
            mCategories[i]->setUpdated(updated);
            return;
        }
    }
}

void CategoryModel::insertRow(int row, Category *category)
{
//    beginInsertRows(QModelIndex(), row, row);
    //connect(item, SIGNAL(dataChanged()), SLOT(handleItemChange()));
//    mCategories.insert(row, category);
//    endInsertRows();

vector<Category*>::iterator it = mCategories.end();
  mCategories.insert(it, category);
}

void CategoryModel::appendRow(Category *category)
{
    mCategories.push_back(category);
}

int CategoryModel::rowCount() const
{
//    Q_UNUSED(parent);
    return mCategories.size();
}

//QVariant CategoryModel::data(const QModelIndex &index, int role) const
//{
//    if(!index.isValid())
//        return QVariant();
//    if(index.row() < 0 || index.row() > (mCategories.count() - 1))
//        return QVariant();
//
//    switch(role) {
//    case Id:
//        return mCategories.at(index.row())->id();
//        break;
//    case Label:
//        return mCategories.at(index.row())->label();
//        break;
//    //case OpenRow:
//        //openRow(index.row());
//    //    test();
//    //    break;
//    //case CloseRow:
//    //    test();
//        //closeRow(index.row());
//    //    break;
//    case IsOpened:
//        return mCategories.at(index.row())->isOpened();
//        break;
//    case HasChildren:
//        return mCategories.at(index.row())->hasChildren();
//        break;
//    default:
//        return QVariant();
//
//    };
//}

//// public slots
//void CategoryModel::openRow(int index)
//{
//    qDebug() << "openRow called: " << index;
//
//    if(index > (mCategories.size() -1))
//        return;
//    if(mCategories[index]->isOpened())
//        return;
//    mCategories.at(index)->setIsOpened(true);
////    emit dataChanged(modelIndex, modelIndex);
//    //int i = index + 1;
//
//    //foreach(Subscription *sub, mCategories.at(index)->subscriptionModel()) {
//    for(int j = 0; j < mCategories.at(index)->subscriptionModel()->rowCount(); j++ ) {
//        //Subscription *sub = mCategories.at(index)->subscriptionModel()->at(j);
//        //mCategories.insert(i++, sub);
//        //qDebug() << "sub title: " << sub->title();
//    }
//}
//
//void CategoryModel::closeRow(int index)
//{
//    qDebug() << "closeRow called: " << index;
//    if(index > (mCategories.count() -1))
//        return;
//
//}























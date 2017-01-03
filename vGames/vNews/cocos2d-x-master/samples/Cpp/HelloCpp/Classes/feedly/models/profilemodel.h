#ifndef PROFILEMODEL_H
#define PROFILEMODEL_H

//#include <QObject>
//#include <std::string>

#include <string>
#include <vector>

#include "talk/base/sigslot.h"
using namespace std;

class ProfileModel //: public QObject
{
//    Q_OBJECT
//    Q_PROPERTY(std::string id READ id WRITE setId NOTIFY idChanged)
//    Q_PROPERTY(std::string email READ email WRITE setEmail NOTIFY emailChanged)
//    Q_PROPERTY(std::string givenName READ givenName WRITE setGivenName NOTIFY givenNameChanged)
//    Q_PROPERTY(std::string familyName READ familyName WRITE setFamilyName NOTIFY familyNameChanged)
//    Q_PROPERTY(std::string picture READ picture WRITE setPicture NOTIFY pictureChanged)
//    Q_PROPERTY(std::string gender READ gender WRITE setGender NOTIFY genderChanged)
//    Q_PROPERTY(std::string locale READ locale WRITE setLocale NOTIFY localeChanged)
//    Q_PROPERTY(std::string google READ google WRITE setGoogle NOTIFY googleChanged)
//    Q_PROPERTY(std::string twitter READ twitter WRITE setTwitter NOTIFY twitterChanged)
//    Q_PROPERTY(std::string facebook READ facebook WRITE setFacebook NOTIFY facebookChanged)
//    Q_PROPERTY(std::string wave READ wave WRITE setWave NOTIFY waveChanged)
//    Q_PROPERTY(std::string client READ client WRITE setClient NOTIFY clientChanged)
//    Q_PROPERTY(bool evernoteConnected READ evernoteConnected WRITE setEvernoteConnected NOTIFY evernoteConnectedChanged)
//    Q_PROPERTY(bool pocketConnected READ pocketConnected WRITE setPocketConnected NOTIFY pocketConnectedChanged)
public:
    ProfileModel();

    void setId(const std::string &id);
    void setEmail(const std::string &email);
    void setGivenName(const std::string &givenName);
    void setFamilyName(const std::string &familyName);
    void setPicture(const std::string &picture);
    void setGender(const std::string &gender);
    void setLocale(const std::string &locale);
    void setGoogle(const std::string &google);
    void setTwitter(const std::string &twitter);
    void setFacebook(const std::string &facebook);
    void setWave(const std::string &wave);
    void setClient(const std::string &client);
    void setEvernoteConnected(const bool &isConnected);
    void setPocketConnected(const bool & isConnected);

    const std::string& id() const;
    const std::string& email() const;
    const std::string& givenName() const;
    const std::string& familyName() const;
    const std::string& picture() const;
    const std::string& gender() const;
    const std::string& locale() const;
    const std::string& google() const;
    const std::string& twitter() const;
    const std::string& facebook() const;
    const std::string& wave() const;
    const std::string& client() const;
    const bool& evernoteConnected() const;
    const bool& pocketConnected() const;

//signals:
//    void idChanged();
//    void emailChanged();
//    void givenNameChanged();
//    void familyNameChanged();
//    void pictureChanged();
//    void genderChanged();
//    void localeChanged();
//    void googleChanged();
//    void twitterChanged();
//    void facebookChanged();
//    void waveChanged();
//    void clientChanged();
//    void evernoteConnectedChanged();
//    void pocketConnectedChanged();
  sigslot::signal0<> idChanged;
  sigslot::signal0<> emailChanged;
  sigslot::signal0<> givenNameChanged;
  sigslot::signal0<> familyNameChanged;
  sigslot::signal0<> pictureChanged;
  sigslot::signal0<> genderChanged;
  sigslot::signal0<> localeChanged;
  sigslot::signal0<> googleChanged;
  sigslot::signal0<> twitterChanged;
  sigslot::signal0<> facebookChanged;
  sigslot::signal0<> waveChanged;
  sigslot::signal0<> clientChanged;
  sigslot::signal0<> evernoteConnectedChanged;
  sigslot::signal0<> pocketConnectedChanged;


private:
    std::string mId;
    std::string mEmail;
    std::string mGivenName;
    std::string mFamilyName;
    std::string mPicture;
    std::string mGender;
    std::string mLocale;
    std::string mGoogle;
    std::string mTwitter;
    std::string mFacebook;
    std::string mWave;
    std::string mClient;
    bool mEvernoteConnected;
    bool mPocketConnected;
};

#endif // PROFILEMODEL_H






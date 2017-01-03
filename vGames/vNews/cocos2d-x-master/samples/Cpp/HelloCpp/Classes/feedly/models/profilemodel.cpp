#include "profilemodel.h"

ProfileModel::ProfileModel()
{
}

// setters
void ProfileModel::setId(const std::string &id)
{
    mId = id;
    /* emit */ idChanged();
}

void ProfileModel::setEmail(const std::string &email)
{
    mEmail = email;
    /* emit */ emailChanged();
}

void ProfileModel::setGivenName(const std::string &givenName)
{
    mGivenName = givenName;
    /* emit */ givenNameChanged();
}

void ProfileModel::setFamilyName(const std::string &familyName)
{
    mFamilyName = familyName;
    /* emit */ familyNameChanged();
}

void ProfileModel::setPicture(const std::string &picture)
{
    mPicture = picture;
    /* emit */ pictureChanged();
}

void ProfileModel::setGender(const std::string &gender)
{
    mGender = gender;
    /* emit */ genderChanged();
}

void ProfileModel::setLocale(const std::string &locale)
{
    mLocale = locale;
    /* emit */ localeChanged();
}

void ProfileModel::setGoogle(const std::string &google)
{
    mGoogle = google;
    /* emit */ googleChanged();
}

void ProfileModel::setTwitter(const std::string &twitter)
{
    mTwitter = twitter;
    /* emit */ twitterChanged();
}

void ProfileModel::setFacebook(const std::string &facebook)
{
    mFacebook = facebook;
    /* emit */ facebookChanged();
}

void ProfileModel::setWave(const std::string &wave)
{
    mWave = wave;
    /* emit */ waveChanged();
}

void ProfileModel::setClient(const std::string &client)
{
    mClient = client;
    /* emit */ clientChanged();
}

void ProfileModel::setEvernoteConnected(const bool &isConnected)
{
    mEvernoteConnected = isConnected;
    /* emit */ evernoteConnectedChanged();
}

void ProfileModel::setPocketConnected(const bool &isConnected)
{
    mPocketConnected = isConnected;
    /* emit */ pocketConnectedChanged();
}


// getters
const std::string& ProfileModel::id() const
{
    return mId;
}

const std::string& ProfileModel::email() const
{
    return mEmail;
}

const std::string& ProfileModel::givenName() const
{
    return mGivenName;
}

const std::string& ProfileModel::familyName() const
{
    return mFamilyName;
}

const std::string& ProfileModel::picture() const
{
    return mPicture;
}

const std::string& ProfileModel::gender() const
{
    return mGender;
}

const std::string& ProfileModel::locale() const
{
    return mLocale;
}

const std::string& ProfileModel::google() const
{
    return mGoogle;
}

const std::string& ProfileModel::twitter() const
{
    return mTwitter;
}

const std::string& ProfileModel::facebook() const
{
    return mFacebook;
}

const std::string& ProfileModel::wave() const
{
    return mWave;
}

const std::string& ProfileModel::client() const
{
    return mClient;
}

const bool& ProfileModel::evernoteConnected() const
{
    return mEvernoteConnected;
}

const bool& ProfileModel::pocketConnected() const
{
    return mPocketConnected;
}
















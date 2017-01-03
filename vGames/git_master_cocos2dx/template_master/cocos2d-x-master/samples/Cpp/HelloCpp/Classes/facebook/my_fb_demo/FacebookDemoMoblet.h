
#ifndef FACEBOOKDEMOMOBLET_H_
#define FACEBOOKDEMOMOBLET_H_

#include "ma.h"
#include "MAUtil/VirenString.h"
#include "Facebook/FacebookManager.h"
#include "GUI/FacebookLoginScreen.h"
#include "webview/WebViewListener.h"

#include "cocos2d.h"
using namespace cocos2d;

class FacebookDemoMoblet: public NativeUI::WebViewListener {
public:
	FacebookDemoMoblet(const MAUtil::String &appId);

	virtual void webViewHookInvoked(NativeUI::WebView* webView, int hookType,
			MAHandle urlData);

	virtual void webViewContentLoading(NativeUI::WebView* webView,
			const int webViewState) {
		CCLOG( "FacebookDemoMoblet::webViewContentLoading");
	}
	~FacebookDemoMoblet();
	/**
	 * This method is called when the application is closed.
	 */
	void closeEvent(); // GCCATTRIB(noreturn);
private:
	void login();
	void initializeFacebook(const MAUtil::String &appId);
	void createGUI();

	MAUtil::String extractAccessToken(const char *newurl);

private:
	bool hasAccessToken(char* aUrl);

	void addLinkOnWall();
	void addPostOnWall();

//  void addLinkOnWall(FacebookDemoGUI::FacebookDemoScreen *menu);
//	void addPostOnWall(FacebookDemoGUI::FacebookDemoScreen *menu);
//	void addStatusMessageOnWall(FacebookDemoGUI::FacebookDemoScreen *menu);
//
//	/**
//	 * Creates a button and adds it to the main menu
//	 * Adds on the button a command that sends the connection request to Facebook
//	 */
//	void addActivitiesButton(FacebookDemoGUI::FacebookDemoScreen *menu);
//	void addAlbumsButton(FacebookDemoGUI::FacebookDemoScreen *menu);
//	void addBooksButton(FacebookDemoGUI::FacebookDemoScreen *menu);
//	void addCheckinsButton(FacebookDemoGUI::FacebookDemoScreen *menu);
//	void addFeedButton(FacebookDemoGUI::FacebookDemoScreen *menu);
//	void addHomeButton(FacebookDemoGUI::FacebookDemoScreen *menu);
//	void addInterestsButton(FacebookDemoGUI::FacebookDemoScreen *menu);
//	void addLikesButton(FacebookDemoGUI::FacebookDemoScreen *menu);
//	void addLinksButton(FacebookDemoGUI::FacebookDemoScreen *menu);
//	void addMusicButton(FacebookDemoGUI::FacebookDemoScreen *menu);
//	void addPhotosButton(FacebookDemoGUI::FacebookDemoScreen *menu);
//	void addPictureButton(FacebookDemoGUI::FacebookDemoScreen *menu);
//	void addPostsButton(FacebookDemoGUI::FacebookDemoScreen *menu);
//	void addTelevisionButton(FacebookDemoGUI::FacebookDemoScreen *menu);
//	void addEventsButton(FacebookDemoGUI::FacebookDemoScreen *menu);
//	void addFriendsButton(FacebookDemoGUI::FacebookDemoScreen *menu);
//	void addFriendListsButton(FacebookDemoGUI::FacebookDemoScreen *menu);
//	void addNotesButton(FacebookDemoGUI::FacebookDemoScreen *menu);
//	void addStatusMessagesButton(FacebookDemoGUI::FacebookDemoScreen *menu);
//
private:
	FacebookManager *mFacebookManager;
	FacebookDemoGUI::FacebookLoginScreen *mLoginScreen;
};

#endif /* FACEBOOKDEMOMOBLET_H_ */

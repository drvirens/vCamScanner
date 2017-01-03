

#include <string.h>
#include <time.h>

#include "Facebook/MAUtil/vConstants.h"
#include "MAUtil/Set.h"
#include "FacebookDemoMoblet.h"
#include "Facebook/GetPermissions.h"
#include "Facebook/GraphAPI/GetConnections/Connections.h"
#include "Facebook/GraphAPI/GetFacebookObjects/FacebookObjects/Link.h"
#include "Facebook/GraphAPI/GetFacebookObjects/FacebookObjects/Post.h"
#include "Facebook/GraphAPI/GetFacebookObjects/FacebookObjects/StatusMessage.h"
#include "Application/ConnectionRequestCommand.h"
#include "Application/PublishRequestCommand.h"
#include "Facebook/config.h"
#include "vSysCall.h"

using namespace FacebookDemoGUI;

FacebookDemoMoblet::FacebookDemoMoblet(const MAUtil::String &appId) {
	if (appId.size() == 0) {
		maPanic(1, "This application requires an application id. Please see file config.h");
	}

	initializeFacebook(appId);
	createGUI();
	login();
}

void FacebookDemoMoblet::login() {
	MAUtil::String oAuthUrl = mFacebookManager->getOAuthUrl();
	VIREN_LOG("\t\tOAuthUrl = %s", oAuthUrl.c_str());

	mLoginScreen->setUrl(oAuthUrl);
	mLoginScreen->setListener(this);
	mLoginScreen->show();
}

void FacebookDemoMoblet::webViewHookInvoked(NativeUI::WebView* webView,
		int hookType, MAHandle urlData) {
	CCLOG( "FacebookDemoMoblet::webViewHookInvoked");

	char* theUrl = (char*) urlData;
	CCAssert( theUrl != 0, "");
	if (!theUrl) {
		return;
	}

	if (!hasAccessToken(theUrl)) {
		CCLOG( "Not the access-token link so ignore this url");
//		delete[] theUrl;
//		theUrl = 0;
		return;
	}

	CCLOG( "extracting token from: url = %s ", theUrl);
	MAUtil::String access_token = extractAccessToken(theUrl);
	if (access_token.size() > 0) {
		mFacebookManager->setAccessToken(access_token);
		CCLOG( "received access_token: %s ", access_token.c_str());
	}

//	delete[] theUrl;
//	theUrl = 0;

	//viren+
	//testing: this must be notified to this class and then we should call below function
	this->addLinkOnWall();
	//viren-
}

bool FacebookDemoMoblet::hasAccessToken(char* aUrl) {
	const char* tmp = strstr(aUrl, "access_token");
	return (tmp == 0) ? false : true;
}

MAUtil::String FacebookDemoMoblet::extractAccessToken(const char *newurl) {
	CCLOG( "FacebookDemoMoblet::extractAccessToken");
	MAUtil::String access_token;
	CCLOG("CONFIG_REDIRECT_URL_BARE : %s", CONFIG_REDIRECT_URL_BARE);
	CCLOG("newurl : %s", newurl);
	const char* redirectedUrl = strstr(newurl, CONFIG_REDIRECT_URL_BARE);
	if (redirectedUrl != 0) {
		const char *accessToken = (char*) strstr(newurl, "access_token=")
				+ strlen("access_token=");
		const char *expiresIn = strstr(newurl, "&expires_in=");

		if (accessToken == 0) {
			CCLOG( "access_token not found in the redirected url");
			return access_token;
		}
		if (expiresIn == 0) {
			CCLOG( "expires_in not found in the redirected url");
			return access_token;
		}
		//int theLen = expiresIn - accessToken;

		int allocLen = strlen(accessToken);
		char* theAccessToekn = new char[allocLen + 1];
		strcpy(theAccessToekn, accessToken);

//			accessToken[expiresIn - accessToken] = 0;
//			access_token.append(accessToken, strlen(accessToken));
		theAccessToekn[expiresIn - accessToken] = 0;
		access_token.append(theAccessToekn, strlen(theAccessToekn));
	}
	return access_token;

#if 0
	MAUtil::String access_token;

	if (strstr(newurl, "fbconnect://") == newurl)
	{
//		Environment::getEnvironment().removeCustomEventListener(this);
		char *accessToken = strstr(newurl, "access_token=") + strlen("access_token=");
		char *expiresIn = strstr(newurl, "&expires_in=");
		accessToken[expiresIn - accessToken] = 0;
		access_token.append(accessToken, strlen(accessToken));
	}

	return access_token;
#endif
}


void FacebookDemoMoblet::closeEvent() {
	// Exit the app.
//	close();
	return;
}

FacebookDemoMoblet::~FacebookDemoMoblet() {
	delete mFacebookManager;
	delete mLoginScreen;
}

void FacebookDemoMoblet::initializeFacebook(const MAUtil::String &appId) {
	MAUtil::Set<MAUtil::String> permissions;
	//ask for a access_token
	permissions.insert("offline_access");

	/**
	 * add to the "permissions" set the permission that we need for retrieving connections for
	 * a User and publishing on a User's wall
	 */
	GetPermissionsFor<User>::Retrieve::onlyConnections(permissions);
	GetPermissionsFor<User>::publishingData(permissions);

//#if 0 //viren: we dont need below for now
	/**
	 * add to the "permissions" set, the permissions that we need for retrieving an object, the connections for
	 * that object and for publishing a object
	 */
	GetPermissionsFor<Album>::allPosibleRequests(permissions);
	GetPermissionsFor<Checkin>::allPosibleRequests(permissions);
	GetPermissionsFor<Comment>::allPosibleRequests(permissions);
	GetPermissionsFor<Event>::allPosibleRequests(permissions);
	GetPermissionsFor<FriendList>::allPosibleRequests(permissions);
	GetPermissionsFor<Link>::allPosibleRequests(permissions);
	GetPermissionsFor<Note>::allPosibleRequests(permissions);
	GetPermissionsFor<Photo>::allPosibleRequests(permissions);
	GetPermissionsFor<Post>::allPosibleRequests(permissions);
	GetPermissionsFor<StatusMessage>::allPosibleRequests(permissions);
//#endif

	mFacebookManager = new FacebookManager(appId, permissions);
}

void FacebookDemoMoblet::createGUI() {
	mLoginScreen = new FacebookLoginScreen();

	//publish
//	addLinkOnWall();
//	addPostOnWall();

//	addStatusMessageOnWall();
//
//	//connections
//	addActivitiesButton(0);
//	addAlbumsButton(0);
//	addBooksButton(0);
//	addCheckinsButton(0);
//	addFeedButton(0);
//	addHomeButton(0);
//	addInterestsButton(0);
//	addLikesButton(0);
//	addLinksButton(0);
//	addMusicButton(0);
//	addPhotosButton(0);
////	addPictureButton(0);
//
//	addPostsButton(0);
//	addTelevisionButton(0);
//	addEventsButton(0);
//	addFriendsButton(0);
//	addFriendListsButton(0);
//	addNotesButton(0);
//	addStatusMessagesButton(0);
}

/*
 Viren: we get access token using URL fragments:
 2013-11-05 20:22:00.708 HelloCpp[10306:60b] URL = http://innopathmobie.appspot.com/#access_token=CAADIdW6M8GwBAMQxV6VzHfLEFRfsf34kQzZBx7qY7vHCSCkOCx4RKJ38vcYwhUkkcMiOl1Go4PvbB4hgOZBaZCdYWOwtw8ZBZAiUAFWI0oE0MPlU4jhTnjwbzygBfDF8gbmwTZCLU35INOrPMy1cs9T75wdUAZAEDS2U4OHBHffbrXwycgqCVvt&expires_in=5173702
 no fbconnect
 */


/**
 * creates a button and adds it to the main menu
 * adds on the button a command that sends the upload picture request to Facebook
 */
void FacebookDemoMoblet::addLinkOnWall() {

	FacebookDemoApplication::PostOnWallCommand<Link> *postLinkCommand =
			new FacebookDemoApplication::PostOnWallCommand<Link>(
					mFacebookManager, 0, "me");
	postLinkCommand->setLinkParams("http://www.engadget.com/2013/09/09/tizen-3-0-ui/",
			"Link posted via my Facebook SDK in CPP");

	//viren+
	postLinkCommand->execute();
	//viren-

//	FacebookDemoGUI::ListItem *postLinkButton = new FacebookDemoGUI::ListItem(postLinkCommand, "post a link on wall");
//	menu->add(postLinkButton);
}

/**
 * creates a button and adds it to the main menu
 * adds on the button a command that sends the upload picture request to Facebook
 */
void FacebookDemoMoblet::addPostOnWall() {
	FacebookDemoApplication::PostOnWallCommand<Post> *addLinkCommand =
			new FacebookDemoApplication::PostOnWallCommand<Post>(
					mFacebookManager, 0, "me");
	addLinkCommand->setPostParams("Post added with MOSYN SDK", //message
			"http://www.youtube.com/watch?v=9-A5q54b5J4", //link
			"New post", //name
			"Link from You Tube", //caption
			"Testing adding a post on wall with MOSYNC_SDK"); //description

//	FacebookDemoGUI::ListItem *linkButton = new FacebookDemoGUI::ListItem(addLinkCommand, "add a post on wall (video)");
//	menu->add(linkButton);

	FacebookDemoApplication::PostOnWallCommand<Post> *addPictureCommand =
			new FacebookDemoApplication::PostOnWallCommand<Post>(
					mFacebookManager, 0, "me");
	addPictureCommand->setPostParams(
			"Post added with MOSYN SDK", //message
			"http://a1.sphotos.ak.fbcdn.net/hphotos-ak-ash4/s720x720/314847_10150297818876545_69819861544_8095955_1938447479_n.jpg", //link
			"New post", //name
			"MoSync developers", //caption
			"Testing adding a post on wall with MOSYNC_SDK"); //description

//	FacebookDemoGUI::ListItem *pictureButton = new FacebookDemoGUI::ListItem(addPictureCommand, "add a post on wall (picture)");
//	menu->add(pictureButton);
}

///**
// * creates a button and adds it to the main menu
// * adds on the button a command that sends the upload picture request to Facebook
// */
//void FacebookDemoMoblet::addStatusMessageOnWall(FacebookDemoGUI::FacebookDemoScreen *menu)
//{
//	FacebookDemoApplication::PostOnWallCommand<StatusMessage> *postStatusMessageCmd = new FacebookDemoApplication::PostOnWallCommand<StatusMessage>(mFacebookManager,
//			menu, "me");
//	postStatusMessageCmd->setMessage("Status message added with MOSYNC_SDK");
//
//	FacebookDemoGUI::ListItem *addStatusMessagButton = new FacebookDemoGUI::ListItem(postStatusMessageCmd, "add a status message on wall");
//	menu->add(addStatusMessagButton);
//}
//
///**
// * Creates a button and adds it to the main menu
// * Adds on the button a command that sends the connection request to Facebook
// */
//void FacebookDemoMoblet::addActivitiesButton(FacebookDemoGUI::FacebookDemoScreen *menu)
//{
//	using namespace FacebookDemoGUI;
//	using namespace FacebookDemoApplication;
//
//	ConnectionRequestCommand *activitiesCmd = new ConnectionRequestCommand( mFacebookManager, menu,
//		Connections<User>::activities(), "me");
//
//	ListItem *button = new ListItem(activitiesCmd, "activities");
//	menu->add(button);
//}
//
///**
// * Creates a button and adds it to the main menu
// * Adds on the button a command that sends the connection request to Facebook
// */
//void FacebookDemoMoblet::addAlbumsButton(FacebookDemoGUI::FacebookDemoScreen *menu)
//{
//	using namespace FacebookDemoGUI;
//	using namespace FacebookDemoApplication;
//
//	OpenMenuCommand *albumsButtonCmd = new OpenMenuCommand(menu);
//
//	/**
//	 * We only want to retrieve from Facebook the "name", "id", "description" and "count" fields from an Album object
//	 */
//	MAUtil::Vector<MAUtil::String> fields;
//	fields.add("name");
//	fields.add("id");
////	fields.add("description");
////	fields.add("count");
//	ConnectionRequestCommand *displayAlbumsCmd = new ConnectionRequestCommand(  mFacebookManager,
//			albumsButtonCmd->getMenuScreen(),
//			Connections<User>::albums(), fields, "me");
//
//	ListItem *displayAlbums = new ListItem(displayAlbumsCmd, "display albums");
//	albumsButtonCmd->addMenuItem(displayAlbums);
//
//	//create new album
//	AddCommand<Album> *createAlbumCmd = new AddCommand<Album>( mFacebookManager,
//			albumsButtonCmd->getMenuScreen());
//	createAlbumCmd->setAlbumName("New album created with MOSYNC_SDK");
//
//	ListItem *createAlbum = new ListItem(createAlbumCmd, "create album");
//	albumsButtonCmd->addMenuItem(createAlbum);
//
//	ListItem *albumsButton = new ListItem(albumsButtonCmd, "albums");
//	menu->add(albumsButton);
//}
//
///**
// * Creates a button and adds it to the main menu
// * Adds on the button a command that sends the connection request to Facebook
// */
//void FacebookDemoMoblet::addBooksButton(FacebookDemoGUI::FacebookDemoScreen *menu)
//{
//	using namespace FacebookDemoGUI;
//	using namespace FacebookDemoApplication;
//
//	ConnectionRequestCommand *displayActivitiesCmd = new ConnectionRequestCommand( mFacebookManager, menu,
//			Connections<User>::books(), "me");
//
//	ListItem *button = new ListItem(displayActivitiesCmd, "books");
//	menu->add(button);
//}
//
///**
// * Creates a button and adds it to the main menu
// * Adds on the button a command that sends the connection request to Facebook
// */
//void FacebookDemoMoblet::addCheckinsButton(FacebookDemoGUI::FacebookDemoScreen *menu)
//{
//	using namespace FacebookDemoGUI;
//	using namespace FacebookDemoApplication;
//
//	OpenMenuCommand *checkinsButtonCmd = new OpenMenuCommand(menu);
//
//	/**
//	 * We only want to retrieve from Facebook the "place" and "id" fields from an Checkin object
//	 */
//	MAUtil::Vector<MAUtil::String> fields;
//	fields.add("id");
//	fields.add("place");
//	//fields.add("application");
//	ConnectionRequestCommand *displayCheckinsCmd = new ConnectionRequestCommand( mFacebookManager,
//			checkinsButtonCmd->getMenuScreen(), Connections<User>::checkins(), fields, "me");
//
//	ListItem *displayCheckins = new ListItem(displayCheckinsCmd, "display checkins");
//	checkinsButtonCmd->addMenuItem(displayCheckins);
//
//	//create new checkin
//	AddCommand<Checkin> *createCheckinCmd = new AddCommand<Checkin>( mFacebookManager,
//			checkinsButtonCmd->getMenuScreen());
//	MAUtil::String placeIdMoSync = "126381597427662";
//	Coordinate coordMoSync;
//	coordMoSync.mLatitude = "59.339451";
//	coordMoSync.mLongitude = "18.05798";
//	createCheckinCmd->setCheckinParams(placeIdMoSync, coordMoSync);
//
//	ListItem *createCheckin = new ListItem(createCheckinCmd, "create checkin");
//	checkinsButtonCmd->addMenuItem(createCheckin);
//
//	ListItem *checkinsButton = new ListItem(checkinsButtonCmd, "checkins");
//	menu->add(checkinsButton);
//}
//
///**
// * Creates a button and adds it to the main menu
// * Adds on the button a command that sends the connection request to Facebook
// */
//void FacebookDemoMoblet::addFeedButton(FacebookDemoGUI::FacebookDemoScreen *menu)
//{
//	using namespace FacebookDemoGUI;
//	using namespace FacebookDemoApplication;
//
//	/**
//	 * We only want to retrieve from Facebook the "from", "id", "name" and "caption" fields from an Album object
//	 */
//	MAUtil::Vector<MAUtil::String> fields;
//	fields.add("id");
//	fields.add("from");
//	fields.add("name");
////	fields.add("caption");
//	fields.add("message");
//	fields.add("application");
//	fields.add("type");
//	ConnectionRequestCommand *displayFeedCmd = new ConnectionRequestCommand( mFacebookManager, menu,
//			Connections<User>::feed(), fields, "me");
//
//	ListItem *feedButton = new ListItem(displayFeedCmd, "feed");
//	menu->add(feedButton);
//}
//
///**
// * Creates a button and adds it to the main menu
// * Adds on the button a command that sends the connection request to Facebook
// */
//void FacebookDemoMoblet::addHomeButton(FacebookDemoGUI::FacebookDemoScreen *menu)
//{
//	using namespace FacebookDemoGUI;
//	using namespace FacebookDemoApplication;
//
//	/**
//	 * We only want to retrieve from Facebook the "id", "name", and "caption"  fields from an Album object
//	 */
//	MAUtil::Vector<MAUtil::String> fields;
//	fields.add("id");
//	fields.add("from");
//	fields.add("name");
////	fields.add("caption");
//	fields.add("message");
//	fields.add("application");
//	fields.add("type");
//	ConnectionRequestCommand *displayHomeCmd = new ConnectionRequestCommand( mFacebookManager, menu,
//			Connections<User>::home(), fields, "me");
//
//	ListItem *homeButton = new ListItem(displayHomeCmd, "home");
//	menu->add(homeButton);
//}
//
///**
// * Creates a button and adds it to the main menu
// * Adds on the button a command that sends the connection request to Facebook
// */
//void FacebookDemoMoblet::addInterestsButton(FacebookDemoGUI::FacebookDemoScreen *menu)
//{
//	using namespace FacebookDemoGUI;
//	using namespace FacebookDemoApplication;
//
//	ConnectionRequestCommand *displayInterestsCmd = new ConnectionRequestCommand( mFacebookManager, menu,
//			Connections<User>::interests(), "me");
//
//	ListItem *button = new ListItem(displayInterestsCmd, "interests");
//	menu->add(button);
//}
//
///**
// * Creates a button and adds it to the main menu
// * Adds on the button a command that sends the connection request to Facebook
// */
//void FacebookDemoMoblet::addLikesButton(FacebookDemoGUI::FacebookDemoScreen *menu)
//{
//	using namespace FacebookDemoGUI;
//	using namespace FacebookDemoApplication;
//
//	ConnectionRequestCommand *displayLikesCmd = new ConnectionRequestCommand( mFacebookManager, menu,
//			Connections<User>::likes(), "me");
//
//	ListItem *button = new ListItem(displayLikesCmd, "likes");
//	menu->add(button);
//}
//
///**
// * Creates a button and adds it to the main menu
// * Adds on the button a command that sends the connection request to Facebook
// */
//void FacebookDemoMoblet::addLinksButton(FacebookDemoGUI::FacebookDemoScreen *menu)
//{
//	using namespace FacebookDemoGUI;
//	using namespace FacebookDemoApplication;
//
//	MAUtil::Vector<MAUtil::String> fields;
//	fields.add("id");
//	fields.add("name");
////	fields.add("message");
//	ConnectionRequestCommand *displayLinksCmd = new ConnectionRequestCommand( mFacebookManager, menu,
//			Connections<User>::links(), fields, "me");
//
//	ListItem *button = new ListItem(displayLinksCmd, "links");
//	menu->add(button);
//}
//
///**
// * Creates a button and adds it to the main menu
// * Adds on the button a command that sends the connection request to Facebook
// */
//void FacebookDemoMoblet::addMusicButton(FacebookDemoGUI::FacebookDemoScreen *menu)
//{
//	using namespace FacebookDemoGUI;
//	using namespace FacebookDemoApplication;
//
//	ConnectionRequestCommand *displayMusicCmd = new ConnectionRequestCommand( mFacebookManager, menu,
//			Connections<User>::music(), "me");
//
//	ListItem *button = new ListItem(displayMusicCmd, "music");
//	menu->add(button);
//}
//
///**
// * Creates a button and adds it to the main menu
// * Adds on the button a command that sends the connection request to Facebook
// */
//void FacebookDemoMoblet::addPhotosButton(FacebookDemoGUI::FacebookDemoScreen *menu)
//{
//	using namespace FacebookDemoGUI;
//	using namespace FacebookDemoApplication;
//
//	/**
//	 * We only want to retrieve from Facebook the "from", "name" and "id" fields from an Photo object
//	 */
//	MAUtil::Vector<MAUtil::String> fields;
//	fields.add("from");
////	fields.add("name");
//	fields.add("id");
//	ConnectionRequestCommand *displayPhotosCmd = new ConnectionRequestCommand( mFacebookManager, menu,
//			Connections<User>::photos(), fields, "me");
//
//	ListItem *button = new ListItem(displayPhotosCmd, "photos");
//	menu->add(button);
//}
//
///**
// * Creates a button and adds it to the main menu
// * Adds on the button a command that sends the connection request to Facebook
// */
//void FacebookDemoMoblet::addPictureButton(FacebookDemoGUI::FacebookDemoScreen *menu)
//{
//	using namespace FacebookDemoGUI;
//	using namespace FacebookDemoApplication;
//
//	ConnectionRequestCommand *displayPictureCmd = new ConnectionRequestCommand( mFacebookManager, menu,
//			Connections<User>::picture(), "me");
//
//	ListItem *button = new ListItem(displayPictureCmd, "picture");
//	menu->add(button);
//}
//
///**
// * Creates a button and adds it to the main menu
// * Adds on the button a command that sends the connection request to Facebook
// */
//void FacebookDemoMoblet::addPostsButton(FacebookDemoGUI::FacebookDemoScreen *menu)
//{
//	using namespace FacebookDemoGUI;
//	using namespace FacebookDemoApplication;
//
//	/**
//	 * We only want to retrieve from Facebook the "id", "from", "name" and "caption" fields from an Album object
//	 */
//	MAUtil::Vector<MAUtil::String> fields;
//	fields.add("id");
//	fields.add("from");
//	fields.add("name");
////	fields.add("caption");
//	fields.add("message");
//	fields.add("application");
//	fields.add("type");
//	ConnectionRequestCommand *displayPostsCmd = new ConnectionRequestCommand( mFacebookManager, menu,
//			Connections<User>::posts(), fields, "me");
//
//	ListItem *button = new ListItem(displayPostsCmd, "posts");
//	menu->add(button);
//}
//
///**
// * Creates a button and adds it to the main menu
// * Adds on the button a command that sends the connection request to Facebook
// */
//void FacebookDemoMoblet::addTelevisionButton(FacebookDemoGUI::FacebookDemoScreen *menu)
//{
//	using namespace FacebookDemoGUI;
//	using namespace FacebookDemoApplication;
//
//	ConnectionRequestCommand *displayTelevisionCmd = new ConnectionRequestCommand( mFacebookManager, menu,
//		Connections<User>::television(), "me");
//
//	ListItem *button = new ListItem(displayTelevisionCmd, "television");
//	menu->add(button);
//}
//
///**
// * Creates a button and adds it to the main menu
// * Adds on the button a command that sends the connection request to Facebook
// */
//void FacebookDemoMoblet::addEventsButton(FacebookDemoGUI::FacebookDemoScreen *menu)
//{
//	using namespace FacebookDemoGUI;
//	using namespace FacebookDemoApplication;
//
//	OpenMenuCommand *eventsButtonCmd = new OpenMenuCommand(menu);
//
//	/**
//	 * We only want to retrieve from Facebook the "name", "id", "name" and "start_time" and "location" fields from an Event object
//	 */
//	MAUtil::Vector<MAUtil::String> fields;
//	fields.add("id");
//	fields.add("name");
////	fields.add("start_time");
//	fields.add("location");
//	ConnectionRequestCommand *displayEventsCmd = new ConnectionRequestCommand( mFacebookManager,
//			eventsButtonCmd->getMenuScreen(), Connections<User>::events(), fields, "me");
//
//	ListItem *displayEvents = new ListItem(displayEventsCmd, "Display events");
//	eventsButtonCmd->addMenuItem(displayEvents);
//
//	//create new event
//	AddCommand<Event> *createEventCmd = new AddCommand<Event>( mFacebookManager,
//			eventsButtonCmd->getMenuScreen());
//
//	//event
//	UnixTimeStamp startTimeStamp(Date("2012", "10", "6"), Time("4","15","30"));
//	UnixTimeStamp endTimeStamp(Date("2012", "10", "6"), Time("5", "20","00"));
//
//	createEventCmd->setEventParams("New event created with MOSYNC_SDK", startTimeStamp, endTimeStamp,
//			"Testing creating an event", "Stockholm");
//
//	ListItem *createEvent = new ListItem(createEventCmd, "Create event");
//	eventsButtonCmd->addMenuItem(createEvent);
//
//	ListItem *eventsButton = new ListItem(eventsButtonCmd, "events");
//	menu->add(eventsButton);
//}
//
///**
// * Creates a button and adds it to the main menu
// * Adds on the button a command that sends the connection request to Facebook
// */
//void FacebookDemoMoblet::addFriendsButton(FacebookDemoGUI::FacebookDemoScreen *menu)
//{
//	using namespace FacebookDemoGUI;
//	using namespace FacebookDemoApplication;
//
//	//display the friends
//	ConnectionRequestCommand *displayFriendsCmd = new ConnectionRequestCommand( mFacebookManager, menu,
//			Connections<User>::friends(), "me");
//
//	ListItem *listsButton = new ListItem(displayFriendsCmd, "friends");
//	menu->add(listsButton);
//}
//
///**
// * Creates a button and adds it to the main menu
// * Adds on the button a command that sends the connection request to Facebook
// */
//void FacebookDemoMoblet::addFriendListsButton(FacebookDemoGUI::FacebookDemoScreen *menu)
//{
//	using namespace FacebookDemoGUI;
//	using namespace FacebookDemoApplication;
//
//	OpenMenuCommand *listsButtonCmd = new OpenMenuCommand(menu);
//
//	//display the friend lists
//	ConnectionRequestCommand *displayListsCmd = new ConnectionRequestCommand( mFacebookManager,
//			listsButtonCmd->getMenuScreen(),
//			Connections<User>::friendlists(), "me");
//	ListItem *displayLists = new ListItem(displayListsCmd, "Display friend lists");
//	listsButtonCmd->addMenuItem(displayLists);
//
//	//create new friend list
//	tm tmTimeStamp;
//	split_time(maLocalTime(), &tmTimeStamp);
//	MAUtil::String strTimeStamp;
//	strTimeStamp = MAUtil::integerToString(tmTimeStamp.tm_year + 1900);
//	strTimeStamp += "/";
//	strTimeStamp += MAUtil::integerToString(tmTimeStamp.tm_mon);
//	strTimeStamp += "/";
//	strTimeStamp += MAUtil::integerToString(tmTimeStamp.tm_mday);
//	strTimeStamp += "_";
//	strTimeStamp += MAUtil::integerToString(tmTimeStamp.tm_hour);
//	strTimeStamp += ":";
//	strTimeStamp += MAUtil::integerToString(tmTimeStamp.tm_min);
//	strTimeStamp += ":";
//	strTimeStamp += MAUtil::integerToString(tmTimeStamp.tm_sec);
//
////	strTimeStamp += MAUtil::integerToString(tmTimeStamp.tm_sec + rand());
//
//	AddCommand<FriendList> *createListCmd = new AddCommand<FriendList>( mFacebookManager,
//			listsButtonCmd->getMenuScreen() );
//	createListCmd->setFriendlistName(strTimeStamp);
//
//	ListItem *createList = new ListItem(createListCmd, "Create friend list");
//	listsButtonCmd->addMenuItem(createList);
//
//	ListItem *listsButton = new ListItem(listsButtonCmd, "friendLists");
//	menu->add(listsButton);
//}
//
///**
// * Creates a button and adds it to the main menu
// * Adds on the button a command that sends the connection request to Facebook
// */
//void FacebookDemoMoblet::addNotesButton(FacebookDemoGUI::FacebookDemoScreen *menu)
//{
//	using namespace FacebookDemoGUI;
//	using namespace FacebookDemoApplication;
//
//	OpenMenuCommand *notesButtonCmd = new OpenMenuCommand(menu);
//
//	/**
//	 * We only want to retrieve from Facebook the "id", "subject" and "from" fields from an Album object
//	 */
//	MAUtil::Vector<MAUtil::String> fields;
//	fields.add("id");
//	fields.add("subject");
////	fields.add("from");
//	ConnectionRequestCommand *displayNotesCmd = new ConnectionRequestCommand( mFacebookManager,
//			notesButtonCmd->getMenuScreen(),
//			Connections<User>::notes(), fields, "me");
//	ListItem *displayNotes = new ListItem(displayNotesCmd, "Display notes");
//	notesButtonCmd->addMenuItem(displayNotes);
//
//	//create new friend list
//	AddCommand<Note> *createNoteCmd = new AddCommand<Note>( mFacebookManager,
//			notesButtonCmd->getMenuScreen());
//	createNoteCmd->setNoteParams("New note created with MOSYNC_SDK", "Testing creating a note with Facebook library");
//	ListItem *createNote = new ListItem(createNoteCmd, "Create Note");
//	notesButtonCmd->addMenuItem(createNote);
//
//	ListItem *listsButton = new ListItem(notesButtonCmd, "notes");
//	menu->add(listsButton);
//}
//
///**
// * Creates a button and adds it to the main menu
// * Adds on the button a command that sends the connection request to Facebook
// */
//void FacebookDemoMoblet::addStatusMessagesButton(FacebookDemoGUI::FacebookDemoScreen *menu)
//{
//	using namespace FacebookDemoGUI;
//	using namespace FacebookDemoApplication;
//
//	OpenMenuCommand *statusButtonCmd = new OpenMenuCommand(menu);
//
//	/**
//	 * We only want to retrieve from Facebook the "name", "id", "message" fields from an StatusMessage object
//	 */
//	MAUtil::Vector<MAUtil::String> fields;
//	fields.add("id");
//	fields.add("message");
//	ConnectionRequestCommand *displayStatusesCmd = new ConnectionRequestCommand( mFacebookManager,
//			menu, Connections<User>::statuses(), fields, "me");
//	ListItem *displayStatuses = new ListItem(displayStatusesCmd, "Display status messages");
//	statusButtonCmd->addMenuItem(displayStatuses);
//
//	//create new status message
//	AddCommand<StatusMessage> *createStatusMsgCmd = new AddCommand<StatusMessage>( mFacebookManager, menu);
//	createStatusMsgCmd->setMessage("New status message created with MOSYNC_SDK");
//	ListItem *createStatusMsg = new ListItem(createStatusMsgCmd, "Create StatusMessage");
//	statusButtonCmd->addMenuItem(createStatusMsg);
//
//	ListItem *statusButton = new ListItem(statusButtonCmd, "status messages");
//	menu->add(statusButton);
//}

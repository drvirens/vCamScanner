
#ifndef _VIREN_FACEBOOK_CONFIG_H__
#define _VIREN_FACEBOOK_CONFIG_H__

/*
 * The Graph API allows you to access all public information about an object. To get more information about a user,
 * your application must first get their permission.
 * The user has to authorize your application (log in and grant permissions). After that, your application can
 * get an access_token for the Facebook user. With that, you can your app. can perform authorized requests on behalf of that user.
 * (The access_token is included in the Graph API requests).
 *
 * The Graph API uses OAuth 2.0 for authorization.
 *
 * The Facebook implementation of the OAuth 2.0 involves three different steps:
 * 		1) user authentication: ensures that the user is who they say they are (use GUI/LoginScreen for this)
 * 		2) app. authorization: ensures that the user knows exactly what data and capabilities they are providing to your app (grants permissions)
 * 		3) app. authentication: ensures that the user is giving their information to your application and not someone else (application id)
 * 	Once these steps are complete, your application retrieves an user access token that you enables you to access the user's information
 *  and take actions on their behalf.
 *  For an example on how to handle all these steps see: FacebookDemoMoblet::login()
 *
 *  User authentication and application authorization are handled at the same time by redirecting the user to the Facebook's OAuth Dialog.
 *  When invoking this dialog, we must pass in the application id ("https://www.facebook.com/dialog/oauth?client_id=YOUR_APP_ID&response_type=token").
 *  The application id is generated when you create your application in the Facebook's Developer App (https://developers.facebook.com/apps).
 *  In order to create an application go to: https://developers.facebook.com/apps and click "Create new App".
 *  After filling all the necessary fields, your application will get an application id (App ID).
 *
 *	Assign to the CONFIG_APPLICATION_ID this application id.
 *
 *	For the official Facebook documentation on authentication see: http://developers.facebook.com/docs/authentication/
 *
*/

#define CONFIG_APPLICATION_ID "220406691459180"
#define CONFIG_SECRET_ID "f3f7f8d31a7bbc510bcfbc66413e5504"

#define CONFIG_REDIRECT_URL "redirect_uri=http%3A%2F%2Finnopathmobie.appspot.com&"
#define CONFIG_REDIRECT_URL_BARE "innopathmobie.appspot.com"

#endif


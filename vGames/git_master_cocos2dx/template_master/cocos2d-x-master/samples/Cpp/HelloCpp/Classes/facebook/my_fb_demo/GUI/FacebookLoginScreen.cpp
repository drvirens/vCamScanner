


#include "FacebookLoginScreen.h"
//#include <IX_WIDGET.h>

namespace FacebookDemoGUI{

FacebookLoginScreen::FacebookLoginScreen()
{
	using namespace NativeUI;

	mWebView = new FacebookDemoGUI::FacebookWebView();

//	mWebView->fillSpaceHorizontally();
//	mWebView->fillSpaceVertically();
//
//	mScreen.setMainWidget(mWebView);

	mWebView->setSoftHook(".*"); // Hook all urls.
}

void FacebookLoginScreen::setSize(int width, int height)
{
//	mScreen.setSize(width, height);
}

void FacebookLoginScreen::setUrl(const MAUtil::String &url)
{
	mWebView->openURL(url);
}

MAUtil::String FacebookLoginScreen::getRedirectUrl() const
{
	return mWebView->getNewURL();
}

void FacebookLoginScreen::setListener(NativeUI::WebViewListener *listener)
{
	mWebView->addWebViewListener(listener);
}

void FacebookLoginScreen::show()
{
//	mScreen.show();
}

FacebookLoginScreen::~FacebookLoginScreen()
{

}

}//namespace FacebookDemoGUI

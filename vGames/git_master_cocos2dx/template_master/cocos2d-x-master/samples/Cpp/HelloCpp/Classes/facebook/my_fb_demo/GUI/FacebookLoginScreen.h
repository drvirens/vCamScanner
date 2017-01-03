

#ifndef FACEBOOKLOGINSCREEN_H_
#define FACEBOOKLOGINSCREEN_H_


#include "MAUtil/VirenString.h"
#include "FacebookWebView.h"
//#include <NativeUI/Screen.h>

namespace FacebookDemoGUI{

class FacebookLoginScreen
{
public:
	FacebookLoginScreen();
	void setSize(int width, int height);

	void setUrl(const MAUtil::String &url);
	MAUtil::String getRedirectUrl() const;

	void setListener(NativeUI::WebViewListener *listener);

	void show();
	~FacebookLoginScreen();

private:
	//NativeUI::Screen					mScreen;
	FacebookDemoGUI::FacebookWebView	*mWebView;
};

}//namespace FacebookDemoGUI

#endif /* FACEBOOKLOGINSCREEN_H_ */

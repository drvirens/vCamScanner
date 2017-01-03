

#ifndef FACEBOOKWEBVIEW_H_
#define FACEBOOKWEBVIEW_H_

#include "MAUtil/VirenString.h"
#include "WebView/WebView.h"

namespace FacebookDemoGUI
{

class FacebookWebView: public NativeUI::WebView
{
public:
	FacebookWebView();
	void setStringPropertySize(int bufferSize);

	 /**
	 * Widget override.
	 * Get a widget property as a string, setting also the result code.
	 */
	virtual MAUtil::String getPropertyString( const MAUtil::String& property) const;

private:
		int BUFFER_SIZE;
};


}//namespace FacebookDemoGUI


#endif /* FACEBOOKWEBVIEW_H_ */

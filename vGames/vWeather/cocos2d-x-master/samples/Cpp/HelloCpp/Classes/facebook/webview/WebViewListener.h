

#ifndef NATIVEUI_WEB_VIEW_LISTENER_H_
#define NATIVEUI_WEB_VIEW_LISTENER_H_

//#include "MAUtil/VirenString.h""
#include "Facebook/MAUtil/vConstants.h"
#include "cocos2d.h"

namespace NativeUI
{
	// Forward declaration.
	class WebView;

	/**
	* \brief Listener for WebView events.
	*/
	class WebViewListener
	{
	public:
		/**
		 * Constructor.
		 */
		WebViewListener()
		{
    CCLOG ( "WebViewListener::WebViewListener" );
		}

		/**
		 * We need to define an virtual destructor for
		 * the library to build in Debug mode.
		 */
		virtual ~WebViewListener()
		{
    CCLOG (  "WebViewListener::~WebViewListener" );
		}

		/**
		* This method is called when MAW_EVENT_WEB_VIEW_HOOK_INVOKED is received.
		* @param webView The web view object that generated the event.
		* @param hookType The type of hook that has been invoked.
		* One of:
		*  -#MAW_CONSTANT_SOFT
		*  -#MAW_CONSTANT_HARD
		*
		* @param urlData The handle to url data. This is string data,
		* there is NO null terminating character. The encoding
		* of the data is determined by the application. The data
		* object is only valid during the duration of this call.
		*/
		virtual void webViewHookInvoked(
			WebView* webView,
			int hookType,
			MAHandle urlData)
		{
    CCLOG ( "WebViewListener::webViewHookInvoked" );
		}

		/**
		* This method is called when the web view content is loading.
		* @param webView The web view object that generated the event.
		* @param webViewState  Any of the following constants:
		* - #MAW_CONSTANT_STARTED
		* - #MAW_CONSTANT_DONE
		* - #MAW_CONSTANT_STOPPED
		* - #MAW_CONSTANT_ERROR
		*/
		virtual void webViewContentLoading(
			WebView* webView,
			const int webViewState)
		{
    CCLOG ( "WebViewListener::webViewContentLoading" );
    
    /*
     // TODO: Micke says: Here we could add a string parameter for
     // "WebViewHookInvoked" events to be able to pass data to
     // the main (hidden) WebView using mosync.bridge.sendRaw.
     sprintf(buffer,
     "try{mosync.nativeui.event(%d, \"%s\", %d, %d, %d)}catch(e){}",
     widget,
     eventType.c_str(),
     firstParameter,
     secondParameter,
     thirdParameter);
     mWebView->callJS(buffer);
     */
		}
	};

} // namespace NativeUI

#endif /* NATIVEUI_WEB_VIEW_LISTENER_H_ */

/*! @} */

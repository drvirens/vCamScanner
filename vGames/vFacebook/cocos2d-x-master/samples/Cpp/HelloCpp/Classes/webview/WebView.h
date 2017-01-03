

#ifndef NATIVEUI_WEBVIEW_H_
#define NATIVEUI_WEBVIEW_H_

#include "MAUtil/VirenString.h""

#include "cocos2d.h"
#include "webview_plugin/ZYWebView.h"

USING_NS_CC;



namespace NativeUI
{
  class WebViewListener;
  
	class WebView //: public cocos2d::webview_plugin::CCWebViewDelegate
  /*: public Widget */
	{
  public:
  
//    void showResult(std::string* str1, std::string* str2);
//    //CCWebViewDelegate
//    virtual void callbackFromJS(CCWebView *webview, CCString *message);

		WebView();
		virtual ~WebView();
		virtual void openURL(const MAUtil::String& url);

		/*
		 * Get the currently displayed url in the web view.
		 * @return The displayed url.
		 */
		virtual MAUtil::String getURL();

		/**
		 * Set the currently displayed HTML data in the web view.
		 * @param html A valid html data.
		 */
		virtual void setHtml(const MAUtil::String& html);

		/**
		 * Set the base URL used by the web-view when loading relative paths.
		 * The value of this URL is used when setting the #MAW_WEB_VIEW_URL and
		 * #MAW_WEB_VIEW_HTML properties. The default value for this property
		 * points to the Assets folder in the local file system
		 * ("file://pathToLocalFileSystem/Assets/").
		 *
		 * @note Use: #maGetSystemProperty ("mosync.path.local.url") to find
		 * the baseURL for the local file system.
		 * @param baseUrl Any valid URL schema.
		 *
		 */
		virtual void setBaseUrl(const MAUtil::String& baseUrl);

		/**
		 * Get the base URL used by the web-view when loading relative paths.
		 * The value of this URL is used when setting the #MAW_WEB_VIEW_URL and
		 * #MAW_WEB_VIEW_HTML properties. The default value for this property
		 * points to the Assets folder in the local file system
		 * ("file://pathToLocalFileSystem/Assets/").
		 *
		 * @return The url.
		 *
		 */
		virtual MAUtil::String getBaseUrl();

		/**
		* Set the pattern used to "soft hook" urls, to get notified
		* when pages are being loaded.
		*
		* When this pattern matches a url that is being requested
		* to load in the WebView, event #MAW_EVENT_WEB_VIEW_HOOK_INVOKED
		* is sent, and the page loads NORMALLY.
		*
		* Note that when receiving event #MAW_EVENT_WEB_VIEW_HOOK_INVOKED
		* you MUST deallocate the urlData handle of the event by calling
		* maDestroyPlaceholder on the handle. Destroy the handle when you are
		* done reading the url data, to avoid that memory will get used up.
		*
		* The pattern is a url pattern specified using regular expression
		* syntax, according to the ICU regular expression standard, using
		* complete match. For example, the ".*" matching expression is used
		* to match any url string. To match all HTTP requests, use the
		* pattern "http://.*". To match all requests for a specific domain,
		* use a pattern like ".*google.com.*". For further infomation, see:
		* http://userguide.icu-project.org/strings/regexp
		* When typing a C-string with a pattern that contains a matching
		* expression with a backslash, make sure to escape the backslash,
		* for example "\B" should be "\\B".
		*
		* By setting the pattern to an empty string, the soft hook mechanism
		* is turned off, and #MAW_EVENT_WEB_VIEW_HOOK_INVOKED is not sent.
		*
		* Both "soft" hooks and "hard" hooks can be enabled simultaneously,
		* but only one hook pattern can be used for each type of hook. When
		* setting a new hook pattern, the old hook is replaced.
		*
		* Note that urls opened using openURL method are NOT hooked.
		* This way of loading a page is excluded from the hook mechanism to
		* prevent "loops" when loading pages.
		*
		* @param url A string with a url pattern.
		* Example:
		*   // Hook all urls.
		*	setSoftHook(".*");
		*
		*   // Hook no urls.
		*	setSoftHook("");
		*
		*   // Hook urls that start with "mosync:".
		*	setSoftHook("mosync://.*");
		*/
		virtual void setSoftHook(const MAUtil::String& url);

		/**
		* Set the pattern used to "hard hook" urls, to get notified
		* and prevent loading of pages.
		*
		* Hard hooks are useful for communicating events from a WebView,
		* for example by setting document.location to a url string in
		* JavaScript. Example: document.location = 'mosync://ExitApp'
		* The application can then examine the url data and take action
		* depending on the url content.
		*
		* When this pattern matches a url that is being requested
		* to load in the WebView, event #MAW_EVENT_WEB_VIEW_HOOK_INVOKED
		* is sent, and page loading is ABORTED.
		*
		* Note that when receiving event #MAW_EVENT_WEB_VIEW_HOOK_INVOKED
		* you MUST deallocate the urlData handle of the event by calling
		* maDestroyPlaceholder on the handle. Destory the handle when you are
		* done reading the url data, to avoid that memory will get used up.
		*
		* The pattern is a url pattern specified using regular expression
		* syntax, according to the ICU regular expression standard, using
		* complete match. For example, the ".*" matching expression is used
		* to match any url string. To match all HTTP requests, use the
		* pattern "http://.*". To match all requests for a specific domain,
		* use a pattern like ".*google.com.*". For further infomation, see:
		* http://userguide.icu-project.org/strings/regexp
		* When typing a C-string with a pattern that contains a matching
		* expression with a backslash, make sure to escape the backslash,
		* for example "\B" should be "\\B".
		*
		* By setting the pattern to an empty string, the soft hook mechanism
		* is turned off, and #MAW_EVENT_WEB_VIEW_HOOK_INVOKED is not sent.
		*
		* Both "soft" hooks and "hard" hooks can be enabled simultaneously,
		* but only one hook pattern can be used for each type of hook. When
		* setting a new hook pattern, the old hook is replaced.
		*
		* The "hard" hook property takes precedence over the "soft" hook
		* property. When both properties are set,
		* #MAW_EVENT_WEB_VIEW_HOOK_INVOKED is sent once, for the
		* "hard" hook type.
		*
		* Note that urls opened using openURL method are NOT hooked.
		* This way of loading a page is excluded from the hook mechanism to
		* prevent "loops" when loading pages.
		*
		* @param url A string with a url pattern.
		* Example:
		*   // Hook urls that start with "mosync:".
		*	setHardHook("mosync://.*");
		*/
		virtual void setHardHook(const MAUtil::String& url);

		/**
		* Enable the zoom controls of the web view.
		* Note that this is not available on Windows Phone 7
		*/
		virtual void enableZoom();

		/**
		* Disable the zoom controls of the web view.
		* Note that this is not available on Windows Phone 7
		*/
		virtual void disableZoom();

		/*
		 * Navigate back the browsing history.
		 */
		virtual void navigateBack();

		/*
		 * Navigate forward the browsing history.
		 */
		virtual void navigateForward();

		/*
		 * Get whether the webview can navigate back
		 * in the browsing history.
		 * @return true if the webview can navigate back, false otherwise.
		 */
		virtual bool canNavigateBack();

		/*
		 * Get whether the webview can navigate forward
		 * in the browsing history.
		 * @return true if the webview can navigate forward, false otherwise.
		 */
		virtual bool canNavigateForward();

		/**
		 * Set the horizontal scroll bar to be painted.
		 * Available only on Android for the moment.
		 */
		virtual void enableHorizontalScrollBar();

		/**
		 * Set the horizontal scroll bar not to be painted.
		 * Available only on Android for the moment.
		 */
		virtual void disableHorizontalScrollbar();

		/*
		 * get whether the horizontal scrollbar should be drawn.
		 * @return True if the horizontal scroll bar is enabled, false otherwise.
		 * Available only on Android for the moment.
		 */
		virtual bool isHorizontalScrollbarEnabled();

		/*
		 * Set the vertical scroll bar to be painted.
		 * Available only on Android for the moment.
		 */
		virtual void enableVerticalScrollBar();

		/**
		 * Set the vertical scroll bar not to be painted.
		 * Available only on Android for the moment.
		 */
		virtual void disableVerticalScrollbar();

		/*
		 * Gets whether the vertical scrollbar should be drawn.
		 * @return True if the vertical scroll bar is enabled, false otherwise.
		 * Available only on Android for the moment.
		 */
		virtual bool isVerticalScrollBarEnabled();

		/**
		 * Get the new URL whenever the web view changes it.
		 * @return The new URL.
		 */
		virtual MAUtil::String getNewURL();

        /**
         * Add an web view event listener.
         * @param listener The listener that will receive web view events.
         */
        virtual void addWebViewListener(WebViewListener* listener);

        /**
         * Remove the web view listener.
         * @param listener The listener that receives web view events.
         */
        virtual void removeWebViewListener(WebViewListener* listener);

		/**
		 * Register this web view to receive messages from JavaScript.
		 * This will set a hook for urls with the "mosync://"
		 * scheme. Messages will arrive in in the
		 * WebViewListener::webViewHookInvoked() method. Use class
		 * WebViewMessage to inspect and parse messages.
		 */
		virtual void enableWebViewMessages();

		/**
		 * Unregister this web view from receiving messages sent
		 * from JavaScript. This will clear the web view url hook.
		 */
		virtual void disableWebViewMessages();

		/**
		 * Run JavaScript code in the web view.
		 * @param script The JavaScript code to run.
		 * @return #MAW_RES_OK on success, <0 on error.
		 */
		virtual int callJS(const MAUtil::String& script);

    protected:
		/**
		 * This method is called when there is an event for this widget.
		 * It passes on the event to all widget's listeners.
		 *
		 * If the event is #MAW_EVENT_WEB_VIEW_HOOK_INVOKED the data
		 * parameter "urlData" gets deleted automatically after the
		 * event is processed.
		 *
		 * @param widgetEventData The data for the widget event.
		 */
 //viren for now       virtual void handleWidgetEvent(MAWidgetEventData* widgetEventData);

    private:
        /**
         * Array with date picker listeners.
         */
        //MAUtil::Vector<WebViewListener*> mWebViewListeners;
    
    WebViewListener* mWebViewListener;
    ZYWebView* m_webView;
	};

} // namespace NativeUI

#endif

/*! @} */

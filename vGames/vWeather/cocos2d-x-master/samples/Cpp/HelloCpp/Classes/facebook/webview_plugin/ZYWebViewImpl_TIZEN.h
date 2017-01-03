

#ifndef __TIZEN_WEBVIEW_IMPL_H__
#define __TIZEN_WEBVIEW_IMPL_H__

#include <FBase.h>
#include <FUi.h>
#include <FWeb.h>

#include "CCOspApplication.h"
#include "CCOspForm.h"
#include "webview/WebViewListener.h"


class ZYWebViewImpl_TIZEN 
			: public Tizen::Base::Object
			, public Tizen::Web::Controls::ILoadingListener
			, public Tizen::Web::Controls::IWebKeypadEventListener
			, public Tizen::Web::Controls::IWebUiEventListener
{
public:
	ZYWebViewImpl_TIZEN(Tizen::Web::Controls::Web* aWeb = 0);
	virtual ~ZYWebViewImpl_TIZEN();
	
	void showWebView(float x, float y, float width, float height);
	void updateURL (const char* url);
	void removeWebView();

	void  addWebViewListener (NativeUI::WebViewListener* listener );
	void  removeWebViewListener (NativeUI::WebViewListener* listener);

private:
	void CreateWebControl();
	void SetWeb(Tizen::Web::Controls::Web* aWeb);


private:
	    static const int EDIT_LINE_HEIGHT = 106;
		static const int EDIT_LINE_LEFT_RIGHT_MARGIN = 7;
		static const int EDIT_LINE_BOTTOM_MARGIN = 5;

//		void SetITizenWebViewListener(ITizenWebViewListener* aITizenWebViewListener);
		void LoadUrl(Tizen::Base::String url) ;
		Tizen::Base::String GetValidUrl(Tizen::Base::String& url);

	//ILoadingListener
		virtual bool OnHttpAuthenticationRequestedN(const Tizen::Base::String& host, const Tizen::Base::String& realm, const Tizen::Web::Controls::AuthenticationChallenge& authentication);
		virtual void OnHttpAuthenticationCanceled(void);
		virtual void OnLoadingStarted(void);
		virtual void OnLoadingCanceled(void);
		virtual void OnLoadingErrorOccurred(Tizen::Web::Controls::LoadingErrorType error, const Tizen::Base::String& reason);
		virtual void OnLoadingCompleted(void);
		virtual void OnEstimatedProgress(int progress);
		virtual void OnPageTitleReceived(const Tizen::Base::String& title);
		virtual bool OnLoadingRequested(const Tizen::Base::String& url, Tizen::Web::Controls::WebNavigationType type);
		virtual Tizen::Web::Controls::DecisionPolicy OnWebDataReceived(const Tizen::Base::String& mime, const Tizen::Net::Http::HttpHeader& header);
	//IWebKeypadEventListener
		virtual void OnWebKeypadWillOpen(Tizen::Web::Controls::Web& source);
		virtual void OnWebKeypadOpened(Tizen::Web::Controls::Web& source);
		virtual void OnWebKeypadClosed(Tizen::Web::Controls::Web& source);
	//IWebUiEventListener
		virtual void OnWebPageBlockSelected(Tizen::Web::Controls::Web &source, Tizen::Graphics::Point &startPoint, Tizen::Graphics::Point &endPoint);
		virtual void OnWebPageShowRequested(Tizen::Web::Controls::Web &source);
		virtual void OnWebWindowCloseRequested(Tizen::Web::Controls::Web &source);
		virtual Tizen::Web::Controls::Web* OnWebWindowCreateRequested(void);

private:

	    CCOspForm* __pCCOspForm;
	    Tizen::Web::Controls::Web *__pWeb;
//	    ITizenWebViewListener* __pITizenWebViewListener;
	    NativeUI::WebViewListener* mWebViewListener;
};


#if 0
@interface ZYWebView_iOS : NSObject <UIWebViewDelegate>
{
    UIWebView* m_webview;
}

- (void)showWebView_x:(float)x y:(float)y width:(float) widht height:(float)height;

- (void)updateURL:(const char*)url;

- (void)removeWebView;

- (void) addWebViewListener:(NativeUI::WebViewListener*)listener;
- (void) removeWebViewListener:(NativeUI::WebViewListener*) listener;

@end
#endif

#endif //__TIZEN_WEBVIEW_IMPL_H__

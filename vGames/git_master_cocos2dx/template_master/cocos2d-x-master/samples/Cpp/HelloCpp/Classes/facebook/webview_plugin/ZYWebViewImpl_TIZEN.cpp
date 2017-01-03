

#include "ZYWebViewImpl_TIZEN.h"
#include "TizenUtils.h"

//#import "EAGLView.h"
#include "cocos2d.h"
#include <string.h>
#include <FBase.h>
#include <FText.h>

#include <FApp.h>
#include <FSystem.h>
#include <FUi.h>
#include <FUiIme.h>
#include <FGraphics.h>

USING_NS_CC;
using namespace Tizen::Base;
using namespace Tizen::Text;
using namespace Tizen::Ui;
using namespace Tizen::Ui::Controls;
using namespace Tizen::Graphics;
using namespace Tizen::App;

using namespace Tizen::Base::Utility;
using namespace Tizen::Locales;
using namespace Tizen::System;
using namespace Tizen::Web::Controls;
using namespace cocos2d;

ZYWebViewImpl_TIZEN::ZYWebViewImpl_TIZEN(Tizen::Web::Controls::Web* aWeb)
			:  __pCCOspForm(0)
			, __pWeb(aWeb)
			, mWebViewListener(0)
{
}

ZYWebViewImpl_TIZEN::~ZYWebViewImpl_TIZEN()
{
}

void ZYWebViewImpl_TIZEN::showWebView(float x, float y, float width, float height) {
	if (!__pWeb ) {
		CreateWebControl();
	}
}

void ZYWebViewImpl_TIZEN::updateURL (const char* url) {
//	CCOspForm* mainFOrm = (CCOspForm *)CCOspApplication::GetInstance()->getCCOspForm();
//	mainFOrm->SetITizenWebViewListener(0);
//	mainFOrm->LoadUrl(url);
	this->LoadUrl(url);
}

void
ZYWebViewImpl_TIZEN::OnLoadingCompleted(void)
{
//	SetUrl(__pWeb->GetUrl());
//	SetButtonGotoImage();

	CCLOG ("ZYWebViewImpl_TIZEN::OnLoadingCompleted");

	Tizen::Base::String tizenUrl = __pWeb->GetUrl();
	AppLogDebug("ZYWebViewImpl_TIZEN::OnLoadingCompleted : Url = %S", tizenUrl.GetPointer());


	std::string* tmp = Utils::GetCString(tizenUrl);
	const char* theCUrl = tmp->c_str();


	  int hookType = 0;//widgetEventData->hookType;
	  MAHandle url = (MAHandle)theCUrl;//widgetEventData->urlData;
	  NativeUI::WebView *theWebView = 0;

	  CCAssert( mWebViewListener != 0, "" );
	  if (mWebViewListener)
	  {
		  mWebViewListener->webViewHookInvoked(theWebView, hookType, url);
	  }
}


void ZYWebViewImpl_TIZEN::removeWebView() {
}

void ZYWebViewImpl_TIZEN::addWebViewListener (NativeUI::WebViewListener* listener ) {
	mWebViewListener = listener;
}

void ZYWebViewImpl_TIZEN::removeWebViewListener (NativeUI::WebViewListener* listener) {
	if (mWebViewListener == listener) {
		mWebViewListener = 0;
	}
}

void ZYWebViewImpl_TIZEN::SetWeb(Tizen::Web::Controls::Web* aWeb) {
	__pWeb = aWeb;
}

//void ZYWebViewImpl_TIZEN::SetITizenWebViewListener(ITizenWebViewListener* aITizenWebViewListener) {
//	__pITizenWebViewListener = aITizenWebViewListener;
//}

void ZYWebViewImpl_TIZEN::CreateWebControl()
{
	result r = E_SUCCESS;
	Rectangle bound;
	WebSetting setting;

	if (!__pCCOspForm) {
		__pCCOspForm = (CCOspForm *)CCOspApplication::GetInstance()->getCCOspForm();
	}
	//Web
	__pWeb = new (std::nothrow) Web();

	bound = __pCCOspForm->GetClientAreaBounds();
	r = __pWeb->Construct(Rectangle(0, EDIT_LINE_HEIGHT + EDIT_LINE_BOTTOM_MARGIN, bound.width, bound.height - EDIT_LINE_HEIGHT - EDIT_LINE_BOTTOM_MARGIN));
	if(r != E_SUCCESS) {
		AppLogDebug( "Web Construct() has failed. %s", GetErrorMessage(r) );
		return;
	}

	r = __pCCOspForm->AddControl(__pWeb);
	if(r != E_SUCCESS) {
		AppLogDebug( "Addcontrol() has failed. %s", GetErrorMessage(r) );
		return;
	}

	setting.SetInputStyle(INPUT_STYLE_OVERLAY);
	r = __pWeb->SetSetting(setting);
	if(r != E_SUCCESS) {
		AppLogDebug( " SetSetting() has failed. %s", GetErrorMessage(r) );
		return;
	}

	__pWeb->SetLoadingListener(this);
	__pWeb->SetWebKeypadEventListener(this);
	__pWeb->SetWebUiEventListener(this);

	__pWeb->SetFocus();
	__pWeb->SetShowState(false);
}

Tizen::Base::String
ZYWebViewImpl_TIZEN::GetValidUrl(Tizen::Base::String& url)
{
	String absoluteUrl = url;
	Uri uri;

	uri.SetUri(url);
	if (uri.GetScheme() == L"")
	{
		//absoluteUrl.Insert(WEB_URL_PREFIX_HTTP, 0);
	}
	return absoluteUrl;
}


void ZYWebViewImpl_TIZEN::LoadUrl(Tizen::Base::String url) {
	if (url.IsEmpty())
	{
		return;
	}
	__pWeb->LoadUrl(GetValidUrl(url));
	__pWeb->SetShowState(true);
	__pCCOspForm->RequestRedraw(true);
}


bool
ZYWebViewImpl_TIZEN::OnHttpAuthenticationRequestedN(const Tizen::Base::String& host, const Tizen::Base::String& realm, const Tizen::Web::Controls::AuthenticationChallenge& authentication)
{
	AppLogDebug("OnHttpAuthenticationRequestedN.");
	return false;
}

void
ZYWebViewImpl_TIZEN::OnHttpAuthenticationCanceled(void)
{
	AppLogDebug("OnHttpAuthenticationCanceled.");
}

void
ZYWebViewImpl_TIZEN::OnLoadingStarted(void)
{
//	SetButtonCancelImage();
	AppLogDebug("OnLoadingStarted.");
}

void
ZYWebViewImpl_TIZEN::OnLoadingCanceled(void)
{
//	SetButtonGotoImage();
	AppLogDebug("OnLoadingCanceled.");
}

void
ZYWebViewImpl_TIZEN::OnLoadingErrorOccurred(LoadingErrorType error, const String& reason)
{
//	Tizen::Ui::Controls::MessageBox msgBox;
//	int modalresult = 0;
	Tizen::Base::String errReason;

	switch (error)
	{
	case WEB_REQUEST_TIMEOUT:
	{
		errReason = Tizen::Base::String(L"Request timeout");
	}
	break;

	case WEB_NO_CONNECTION:
	{
		errReason = Tizen::Base::String(L"Network is not in service");
	}
	break;

	case WEB_MIME_NOT_SUPPORTED:
	{
		errReason = Tizen::Base::String(L"The content type is not supported");
	}
	break;

	case WEB_BAD_URL:
	{
		errReason = Tizen::Base::String(L"The url is invalid");
	}
	break;

	case WEB_HTTP_RESPONSE:
	{
		errReason = Tizen::Base::String(L"HTTP response");
	}
	break;

	case WEB_OUT_OF_MEMORY:
	{
		errReason = Tizen::Base::String(L"Page Too Large");
	}
	break;

	case WEB_REQUEST_MAX_EXCEEDED:
	{
		errReason = Tizen::Base::String(L"Request Max Exceeded");
	}
	break;

	case WEB_ERROR_UNKNOWN:
	default:
	{
		errReason = Tizen::Base::String(L"An Unknown error");
	}
	break;
	}

//	msgBox.Construct(L"LOADING ERROR TYPE", errReason, MSGBOX_STYLE_NONE, 3000);
//	msgBox.ShowAndWait(modalresult);
//	SetButtonGotoImage();
	AppLogDebug("ZYWebViewImpl_TIZEN::OnLoadingErrorOccurred = %S", errReason.GetPointer());
}

void
ZYWebViewImpl_TIZEN::OnEstimatedProgress(int progress)
{
	AppLogDebug("PROGRESS = %d", progress);
}

void
ZYWebViewImpl_TIZEN::OnPageTitleReceived(const Tizen::Base::String& title)
{
	AppLogDebug("ZYWebViewImpl_TIZEN::OnPageTitleReceived", title.GetPointer());
}

bool
ZYWebViewImpl_TIZEN::OnLoadingRequested(const Tizen::Base::String& url, WebNavigationType type)
{
	AppLogDebug("ZYWebViewImpl_TIZEN::OnLoadingRequested : url : %S",url.GetPointer());
	//SetUrl(url);
	return false;
}


DecisionPolicy
ZYWebViewImpl_TIZEN::OnWebDataReceived(const Tizen::Base::String& mime, const Tizen::Net::Http::HttpHeader& header)
{
	AppLogDebug("ZYWebViewImpl_TIZEN::OnWebDataReceived");
	return WEB_DECISION_CONTINUE;
}

void
ZYWebViewImpl_TIZEN::OnWebKeypadWillOpen(Tizen::Web::Controls::Web& source)
{
	AppLogDebug("ZYWebViewImpl_TIZEN::OnWebKeypadWillOpen");
	Rectangle bound = __pCCOspForm->GetClientAreaBounds();

	if (source.IsVisible())
	{
		source.SetSize(bound.width, bound.height - EDIT_LINE_HEIGHT - EDIT_LINE_BOTTOM_MARGIN);
	}
}

void
ZYWebViewImpl_TIZEN::OnWebKeypadOpened(Tizen::Web::Controls::Web& source)
{
	AppLogDebug("OnWebKeypadOpened.");
}

void
ZYWebViewImpl_TIZEN::OnWebKeypadClosed(Tizen::Web::Controls::Web& source)
{
	AppLogDebug("OnWebKeypadClosed.");
	Rectangle bound = __pCCOspForm->GetClientAreaBounds();
	source.SetSize(bound.width, bound.height - EDIT_LINE_HEIGHT - EDIT_LINE_BOTTOM_MARGIN);
}

void
ZYWebViewImpl_TIZEN::OnWebPageBlockSelected(Tizen::Web::Controls::Web &source, Tizen::Graphics::Point &startPoint, Tizen::Graphics::Point &endPoint)
{
	AppLogDebug("OnWebPageBlockSelected.");
}

void
ZYWebViewImpl_TIZEN::OnWebPageShowRequested(Tizen::Web::Controls::Web &source)
{
	AppLogDebug("OnWebPageShowRequested.");
}

void
ZYWebViewImpl_TIZEN::OnWebWindowCloseRequested(Tizen::Web::Controls::Web &source)
{
	AppLogDebug("OnWebWindowCloseRequested.");
}

Tizen::Web::Controls::Web*
ZYWebViewImpl_TIZEN::OnWebWindowCreateRequested(void)
{
	AppLogDebug("OnWebWindowCreateRequested. : WebViewer doesn't include new window creation.");
//	MessageBox messageBox;
//	messageBox.Construct(L"", L"WebViewer doesn't include new window creation.", MSGBOX_STYLE_NONE, 3000);
//
//	int modalResult = 0;
//	messageBox.ShowAndWait(modalResult);

	return null;
}




#if 0
static NativeUI::WebViewListener* gWebViewListener = 0;

@implementation ZYWebView_iOS


- (void) addWebViewListener:(NativeUI::WebViewListener*)listener
{
  gWebViewListener = listener;
}
- (void) removeWebViewListener:(NativeUI::WebViewListener*) listener
{
  gWebViewListener = 0;
}

- (void)showWebView_x:(float)x y:(float)y width:(float) widht height:(float)height
{
    if (!m_webview)
    {
        m_webview = [[UIWebView alloc] initWithFrame:CGRectMake(x, y, widht , height)];
        [m_webview setDelegate:self];

        [[EAGLView sharedEGLView] addSubview:m_webview];
        [m_webview release];
        
        m_webview.backgroundColor = [UIColor clearColor];
        m_webview.opaque = NO;
        
        for (UIView *aView in [m_webview subviews])  
        { 
            if ([aView isKindOfClass:[UIScrollView class]])  
            { 
                UIScrollView* scView = (UIScrollView *)aView;
                
//                [(UIScrollView *)aView setShowsVerticalScrollIndicator:NO]; //右侧的滚动条 （水平的类似）
                [scView setShowsHorizontalScrollIndicator:NO];
//                scView.bounces = NO;
                
                for (UIView *shadowView in aView.subviews)  
                {
                    if ([shadowView isKindOfClass:[UIImageView class]]) 
                    { 
                        shadowView.hidden = YES;  //上下滚动出边界时的黑色的图片 也就是拖拽后的上下阴影
                    } 
                } 
            } 
        }  
    }
}

- (void)updateURL:(const char*)url
{
    NSString *request = [NSString stringWithUTF8String:url];
    [m_webview loadRequest:[NSURLRequest requestWithURL:[NSURL URLWithString:request] 
                                            cachePolicy:NSURLRequestReloadIgnoringLocalCacheData 
                                        timeoutInterval:60]];
}

- (void)removeWebView
{
    [m_webview removeFromSuperview];
    m_webview = NULL;
}

#pragma mark - WebView
- (BOOL)webView:(UIWebView *)webView shouldStartLoadWithRequest:(NSURLRequest *)request navigationType:(UIWebViewNavigationType)navigationType
{
  CCLOG ( "UIWebView delegate : shouldStartLoadWithRequest" );
    return YES;
}

- (void)webViewDidStartLoad:(UIWebView *)webView
{
    CCLOG ( "UIWebView delegate : webViewDidStartLoad" );
}

- (void)webViewDidFinishLoad:(UIWebView *)webView
{
  CCLOG ( "UIWebView delegate : webViewDidFinishLoad" );
  
  char* theCUrl = 0;
  NSURLRequest* request = [webView request];
  NSLog(@"webView:URL = %@", [request URL]);
  
  NSString* theStringUrl = [[request URL] absoluteString];
  if (theStringUrl)
  {
    const char *theCStr = [theStringUrl UTF8String];
    theCUrl = new char[strlen(theCStr) + 1];
    strcpy(theCUrl, theCStr);
  }
  
  int hookType = 0;//widgetEventData->hookType;
  MAHandle url = (MAHandle)theCUrl;//widgetEventData->urlData;
  NativeUI::WebView *theWebView = 0;
  
  CCAssert( gWebViewListener != 0, "" );
  if (gWebViewListener)
  {
    gWebViewListener->webViewHookInvoked(theWebView, hookType, url);
  }
}

- (void)webView:(UIWebView *)webView didFailLoadWithError:(NSError *)error
{
    CCLOG ( "UIWebView delegate : didFailLoadWithError" );
  
  NSDictionary *userInfo = [error userInfo];
  NSString *e = [[userInfo objectForKey:NSUnderlyingErrorKey] localizedDescription];
  NSLog(@"ERROR: %@", e);
  
  #if 0
    // 102 == WebKitErrorFrameLoadInterruptedByPolicyChange
    // -999 == "Operation could not be completed", note -999 occurs when the user clicks away before
    // the page has completely loaded, if we find cases where we want this to result in dialog failure
    // (usually this just means quick-user), then we should add something more robust here to account
    // for differences in application needs
  if (!(([error.domain isEqualToString:@"NSURLErrorDomain"] && error.code == -999) ||
        ([error.domain isEqualToString:@"WebKitErrorDomain"] && error.code == 102))) {
    [self dismissWithError:error animated:YES];
  }
  #endif
}



@end
#endif

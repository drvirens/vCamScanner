

#include "webview_plugin/ZYWebView.h"
#import "ZYWebView_iOS.h"

static ZYWebView_iOS* m_webViewiOS;

ZYWebView::ZYWebView()
{
    
}

ZYWebView::~ZYWebView()
{
    [m_webViewiOS release];
    m_webViewiOS = NULL;
}

bool ZYWebView::init()
{
	return true;
}

void ZYWebView::showWebView(const char* url, float x, float y, float width, float height)
{
    m_webViewiOS = [[ZYWebView_iOS alloc] init];
    [m_webViewiOS showWebView_x:x y:y width:width height:height];
    
    this->updateURL(url);
}

void ZYWebView::updateURL(const char* url)
{
    [m_webViewiOS updateURL:url];
}

void ZYWebView::removeWebView()
{
    [m_webViewiOS removeWebView];
}

void ZYWebView::addWebViewListener(NativeUI::WebViewListener* listener)
{
  [m_webViewiOS addWebViewListener:listener];
}
void ZYWebView::removeWebViewListener(NativeUI::WebViewListener* listener)
{
  [m_webViewiOS removeWebViewListener:listener];
}

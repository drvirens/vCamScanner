

#include "webview_plugin/ZYWebView.h"
#include "webview_plugin/ZYWebViewImpl_TIZEN.h"
#include "CCOspApplication.h"
#include "CCOspForm.h"

static ZYWebViewImpl_TIZEN* gZYWebViewImpl_TIZEN = 0;

ZYWebView::ZYWebView()
{
	gZYWebViewImpl_TIZEN = 0;
}

ZYWebView::~ZYWebView()
{
	delete gZYWebViewImpl_TIZEN;
	gZYWebViewImpl_TIZEN = 0;
}

bool ZYWebView::init()
{
	return true;
}

void ZYWebView::showWebView(const char* url, float x, float y, float width, float height)
{
	if (!gZYWebViewImpl_TIZEN ) {
		gZYWebViewImpl_TIZEN = new ZYWebViewImpl_TIZEN();
		gZYWebViewImpl_TIZEN->showWebView(x, y, width, height);
	}
	this->updateURL(url);
}

void ZYWebView::updateURL(const char* url)
{
	if (gZYWebViewImpl_TIZEN) {
		gZYWebViewImpl_TIZEN->updateURL(url);
	}
}

void ZYWebView::removeWebView()
{
	gZYWebViewImpl_TIZEN->removeWebView();
}

void ZYWebView::addWebViewListener(NativeUI::WebViewListener* listener)
{
	gZYWebViewImpl_TIZEN->addWebViewListener(listener);
}
void ZYWebView::removeWebViewListener(NativeUI::WebViewListener* listener)
{
	gZYWebViewImpl_TIZEN->removeWebViewListener(listener);
}

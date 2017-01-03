

#import <Foundation/Foundation.h>

#include "WebViewListener.h"

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

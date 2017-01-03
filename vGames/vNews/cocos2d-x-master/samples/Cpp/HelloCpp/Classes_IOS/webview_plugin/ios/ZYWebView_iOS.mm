

#import "ZYWebView_iOS.h"
#import "EAGLView.h"
#include "cocos2d.h"
//#include "talk/base/common.h"
#include <string.h>

using namespace cocos2d;

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

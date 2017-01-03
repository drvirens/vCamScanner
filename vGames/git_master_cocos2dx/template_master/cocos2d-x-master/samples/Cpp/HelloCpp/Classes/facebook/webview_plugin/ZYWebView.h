//
//  based on BlackFire BFWebView.h
//

#ifndef NewPuzzle_BFWebView_h
#define NewPuzzle_BFWebView_h

#include "cocos2d.h"
#include "webview/WebViewListener.h"

USING_NS_CC;
using namespace NativeUI;


class ZYWebView : public CCObject
{
public:
    ZYWebView();
    ~ZYWebView();
    
    CREATE_FUNC(ZYWebView);
	bool init();
    
     void showWebView(const char* url, float x, float y, float width, float height);

    
    void updateURL(const char* url);
        
    void removeWebView();
  
  /**
   * Add an web view event listener.
   * @param listener The listener that will receive web view events.
   */
   void addWebViewListener(WebViewListener* listener);
  
  /**
   * Remove the web view listener.
   * @param listener The listener that receives web view events.
   */
   void removeWebViewListener(WebViewListener* listener);
  
private:

};

#endif

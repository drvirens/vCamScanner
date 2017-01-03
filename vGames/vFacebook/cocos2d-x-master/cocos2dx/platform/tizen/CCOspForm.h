/****************************************************************************
Copyright (c) 2013 cocos2d-x.org
Copyright (c) 2013 Lee, Jae-Hong

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/

#ifndef _CCOSPFORM_H_
#define _CCOSPFORM_H_

#include <FBase.h>
#include <FUi.h>
#include <FWeb.h>

//viren+
//#define SUPPORT_WEB_VIEW 1
#ifdef SUPPORT_WEB_VIEW
class ITizenWebViewListener {
public:
	virtual ~ITizenWebViewListener() = 0;
	virtual void WebViewDidFinishLoad(const char* aUrl) = 0;
};
#endif
//viren-

typedef void (*EditTextCallback)(const char* pText, void* ctx);

class CCOspForm
    : public Tizen::Ui::Controls::Form
    , public Tizen::Ui::ITouchEventListener
    , public Tizen::Ui::ITextEventListener
    , public Tizen::Ui::Controls::IFormBackEventListener
#ifdef SUPPORT_WEB_VIEW
	, public Tizen::Web::Controls::ILoadingListener
	, public Tizen::Web::Controls::IWebKeypadEventListener
	, public Tizen::Web::Controls::IWebUiEventListener
#endif
{
public:
    CCOspForm();
    ~CCOspForm();

    virtual result OnInitializing(void);
    virtual result OnTerminating(void);
    virtual void  OnTouchDoublePressed(const Tizen::Ui::Control& source, const Tizen::Graphics::Point& currentPosition, const Tizen::Ui::TouchEventInfo& touchInfo);
    virtual void  OnTouchFocusIn(const Tizen::Ui::Control& source, const Tizen::Graphics::Point& currentPosition, const Tizen::Ui::TouchEventInfo& touchInfo);
    virtual void  OnTouchFocusOut(const Tizen::Ui::Control& source, const Tizen::Graphics::Point& currentPosition, const Tizen::Ui::TouchEventInfo& touchInfo);
    virtual void  OnTouchLongPressed (const Tizen::Ui::Control& source, const Tizen::Graphics::Point& currentPosition, const Tizen::Ui::TouchEventInfo& touchInfo);
    virtual void  OnTouchMoved(const Tizen::Ui::Control& source, const Tizen::Graphics::Point& currentPosition, const Tizen::Ui::TouchEventInfo& touchInfo);
    virtual void  OnTouchPressed(const Tizen::Ui::Control& source, const Tizen::Graphics::Point& currentPosition, const Tizen::Ui::TouchEventInfo& touchInfo);
    virtual void  OnTouchReleased(const Tizen::Ui::Control& source, const Tizen::Graphics::Point& currentPosition, const Tizen::Ui::TouchEventInfo& touchInfo);

    // ITextEventListener
    virtual void OnTextValueChanged(const Tizen::Ui::Control& source);
    virtual void OnTextValueChangeCanceled(const Tizen::Ui::Control& source);

    //IFormBackEventListener
    virtual void OnFormBackRequested(Tizen::Ui::Controls::Form& source);

#ifdef SUPPORT_WEB_VIEW
    static const int EDIT_LINE_HEIGHT = 106;
	static const int EDIT_LINE_LEFT_RIGHT_MARGIN = 7;
	static const int EDIT_LINE_BOTTOM_MARGIN = 5;

	void SetITizenWebViewListener(ITizenWebViewListener* aITizenWebViewListener);
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


    void CreateWebControl();
    Tizen::Web::Controls::Web *__pWeb;
    ITizenWebViewListener* __pITizenWebViewListener;
#endif

    void ShowKeypad(const char* pMessage, Tizen::Ui::Controls::KeypadStyle keypadStyle, Tizen::Ui::Controls::KeypadInputModeCategory keypadCategory, bool bSingleLineEnabled, bool bTextPrediction, int nMaxLength, EditTextCallback pfEditTextCallback, void* pCtx);
    void ShowKeypad();
    void CloseKeypad();
private:
    Tizen::Ui::Controls::Keypad*__pKeypad;
    EditTextCallback m_pfEditTextCallback;
    void* m_pCtx;


};

#endif  // _CCOSPFORM_H_

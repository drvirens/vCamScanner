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
#include "cocos2d.h"

//#include <CCEventKeyboard.h>

#include "CCOspForm.h"
#include "CCDirector.h"
#include "CCEGLView.h"
#include "text_input_node/CCIMEDispatcher.h"
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

CCOspForm::CCOspForm()
    : __pKeypad(null)
    , m_pfEditTextCallback(null)
#ifdef SUPPORT_WEB_VIEW
	, __pWeb(0)
#endif
    , m_pCtx(null)
{
}

CCOspForm::~CCOspForm()
{
}

#ifdef SUPPORT_WEB_VIEW
void CCOspForm::SetITizenWebViewListener(ITizenWebViewListener* aITizenWebViewListener) {
	__pITizenWebViewListener = aITizenWebViewListener;
}

void CCOspForm::CreateWebControl()
{
	result r = E_SUCCESS;
	Rectangle bound;
	WebSetting setting;

	//Web
	__pWeb = new (std::nothrow) Web();

	bound = this->GetClientAreaBounds();
	r = __pWeb->Construct(Rectangle(0, EDIT_LINE_HEIGHT + EDIT_LINE_BOTTOM_MARGIN, bound.width, bound.height - EDIT_LINE_HEIGHT - EDIT_LINE_BOTTOM_MARGIN));
	if(r != E_SUCCESS) {
		AppLogDebug( "Web Construct() has failed. %s", GetErrorMessage(r) );
		return;
	}

	r = this->AddControl(__pWeb);
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
CCOspForm::GetValidUrl(Tizen::Base::String& url)
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


void CCOspForm::LoadUrl(Tizen::Base::String url) {
	if (url.IsEmpty())
	{
		return;
	}
	__pWeb->LoadUrl(GetValidUrl(url));
	__pWeb->SetShowState(true);
	this->RequestRedraw(true);
}


bool
CCOspForm::OnHttpAuthenticationRequestedN(const Tizen::Base::String& host, const Tizen::Base::String& realm, const Tizen::Web::Controls::AuthenticationChallenge& authentication)
{
	AppLogDebug("OnHttpAuthenticationRequestedN.");
	return false;
}

void
CCOspForm::OnHttpAuthenticationCanceled(void)
{
	AppLogDebug("OnHttpAuthenticationCanceled.");
}

void
CCOspForm::OnLoadingStarted(void)
{
//	SetButtonCancelImage();
	AppLogDebug("OnLoadingStarted.");
}

void
CCOspForm::OnLoadingCanceled(void)
{
//	SetButtonGotoImage();
	AppLogDebug("OnLoadingCanceled.");
}

void
CCOspForm::OnLoadingErrorOccurred(LoadingErrorType error, const String& reason)
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
	AppLogDebug("CCOspForm::OnLoadingErrorOccurred = %S", errReason.GetPointer());
}

void
CCOspForm::OnLoadingCompleted(void)
{
//	SetUrl(__pWeb->GetUrl());
//	SetButtonGotoImage();
	Tizen::Base::String url = __pWeb->GetUrl();
	AppLogDebug("CCOspForm::OnLoadingCompleted : Url = %S", url.GetPointer());

	const char* theUrl = virenPutUrlHere ;
	__pITizenWebViewListener->WebViewDidFinishLoad(theUrl);
}

void
CCOspForm::OnEstimatedProgress(int progress)
{
	AppLogDebug("PROGRESS = %d", progress);
}

void
CCOspForm::OnPageTitleReceived(const Tizen::Base::String& title)
{
	AppLogDebug("CCOspForm::OnPageTitleReceived", title.GetPointer());
}

bool
CCOspForm::OnLoadingRequested(const Tizen::Base::String& url, WebNavigationType type)
{
	AppLogDebug("CCOspForm::OnLoadingRequested : url : %S",url.GetPointer());
	//SetUrl(url);
	return false;
}


DecisionPolicy
CCOspForm::OnWebDataReceived(const Tizen::Base::String& mime, const Tizen::Net::Http::HttpHeader& header)
{
	AppLogDebug("CCOspForm::OnWebDataReceived");
	return WEB_DECISION_CONTINUE;
}

void
CCOspForm::OnWebKeypadWillOpen(Tizen::Web::Controls::Web& source)
{
	AppLogDebug("CCOspForm::OnWebKeypadWillOpen");
	Rectangle bound = this->GetClientAreaBounds();

	if (source.IsVisible())
	{
		source.SetSize(bound.width, bound.height - EDIT_LINE_HEIGHT - EDIT_LINE_BOTTOM_MARGIN);
	}
}

void
CCOspForm::OnWebKeypadOpened(Tizen::Web::Controls::Web& source)
{
	AppLogDebug("OnWebKeypadOpened.");
}

void
CCOspForm::OnWebKeypadClosed(Tizen::Web::Controls::Web& source)
{
	AppLogDebug("OnWebKeypadClosed.");
	Rectangle bound = this->GetClientAreaBounds();
	source.SetSize(bound.width, bound.height - EDIT_LINE_HEIGHT - EDIT_LINE_BOTTOM_MARGIN);
}

void
CCOspForm::OnWebPageBlockSelected(Tizen::Web::Controls::Web &source, Tizen::Graphics::Point &startPoint, Tizen::Graphics::Point &endPoint)
{
	AppLogDebug("OnWebPageBlockSelected.");
}

void
CCOspForm::OnWebPageShowRequested(Tizen::Web::Controls::Web &source)
{
	AppLogDebug("OnWebPageShowRequested.");
}

void
CCOspForm::OnWebWindowCloseRequested(Tizen::Web::Controls::Web &source)
{
	AppLogDebug("OnWebWindowCloseRequested.");
}

Tizen::Web::Controls::Web*
CCOspForm::OnWebWindowCreateRequested(void)
{
	AppLogDebug("OnWebWindowCreateRequested. : WebViewer doesn't include new window creation.");
//	MessageBox messageBox;
//	messageBox.Construct(L"", L"WebViewer doesn't include new window creation.", MSGBOX_STYLE_NONE, 3000);
//
//	int modalResult = 0;
//	messageBox.ShowAndWait(modalResult);

	return null;
}


#endif

result
CCOspForm::OnInitializing(void)
{
	// Setup back event listener
	SetFormBackEventListener(this);

    AddTouchEventListener(*this);
    SetMultipointTouchEnabled(true);
#ifdef SUPPORT_WEB_VIEW
    CreateWebControl();
#endif
    return E_SUCCESS;
}

result
CCOspForm::OnTerminating(void)
{
    result r = E_SUCCESS;

    if (__pKeypad)
        __pKeypad->Destroy();

    return r;
}

void
CCOspForm:: OnTouchDoublePressed(const Control& source, const Point& currentPosition, const TouchEventInfo& touchInfo)
{
}

void
CCOspForm:: OnTouchFocusIn(const Control& source, const Point& currentPosition, const TouchEventInfo& touchInfo)
{
}

void
CCOspForm::OnTouchFocusOut(const Control& source, const Point& currentPosition, const TouchEventInfo& touchInfo)
{
}

void
CCOspForm::OnTouchLongPressed(const Control& source, const Point& currentPosition, const TouchEventInfo& touchInfo)
{
}

void
CCOspForm::OnTouchMoved(const Control& source, const Point& currentPosition, const TouchEventInfo& touchInfo)
{
    int id = touchInfo.GetPointId();
    float x = currentPosition.x;
    float y = currentPosition.y;
    CCDirector::sharedDirector()->getOpenGLView()->handleTouchesMove(1, &id, &x, &y);
}

void
CCOspForm::OnTouchPressed(const Control& source, const Point& currentPosition, const TouchEventInfo& touchInfo)
{
    int id = touchInfo.GetPointId();
    float x = currentPosition.x;
    float y = currentPosition.y;
    CCDirector::sharedDirector()->getOpenGLView()->handleTouchesBegin(1, &id, &x, &y);
}

void
CCOspForm::OnTouchReleased(const Control& source, const Point& currentPosition, const TouchEventInfo& touchInfo)
{
    int id = touchInfo.GetPointId();
    float x = currentPosition.x;
    float y = currentPosition.y;
    CCDirector::sharedDirector()->getOpenGLView()->handleTouchesEnd(1, &id, &x, &y);
}

void CCOspForm::OnTextValueChanged(const Tizen::Ui::Control& source)
{
    String text = __pKeypad->GetText();
    Utf8Encoding utf8;
    ByteBuffer* buffer = utf8.GetBytesN(text);
    const char* pText = "";
    if (buffer)
        pText = (const char *)buffer->GetPointer();

    if (m_pfEditTextCallback)
    {
        m_pfEditTextCallback(pText, m_pCtx);
    }
    else
    {
        const char* pContentText = CCIMEDispatcher::sharedDispatcher()->getContentText();

        for (unsigned int i = strlen(pContentText); i > 0; i--)
        {
            CCIMEDispatcher::sharedDispatcher()->dispatchDeleteBackward();
        }

        std::string text("");
        if (pText != null)
        {
            text = pText;
            if (text.compare("") == 0)
            {
                text = "\n";
            }

            if (text.at(text.length() - 1) != '\n')
            {
                text += '\n';
            }
        }

        CCIMEDispatcher::sharedDispatcher()->dispatchInsertText(text.c_str(), text.length());
    }

    if (buffer)
        delete buffer;
}

void CCOspForm::OnTextValueChangeCanceled(const Tizen::Ui::Control& source)
{
    if (m_pfEditTextCallback)
    {
        m_pfEditTextCallback("", m_pCtx);
    }
    else
    {
        const char* pContentText = CCIMEDispatcher::sharedDispatcher()->getContentText();

        for (unsigned int i = strlen(pContentText); i > 0; i--)
        {
            CCIMEDispatcher::sharedDispatcher()->dispatchDeleteBackward();
        }
    }
}

void
CCOspForm::ShowKeypad(const char* pMessage, KeypadStyle keypadStyle, KeypadInputModeCategory keypadCategory, bool bSingleLineEnabled, bool bTextPrediction, int nMaxLength, EditTextCallback pfEditTextCallback, void* pCtx)
{
    m_pfEditTextCallback = pfEditTextCallback;
    m_pCtx = pCtx;

    if (__pKeypad)
    {
        __pKeypad->RemoveTextEventListener(*this);
        __pKeypad->Destroy();
        __pKeypad = null;
    }

    if (nMaxLength > 100)
        nMaxLength = 100;
    else if (nMaxLength == -1)
        nMaxLength = 100;

    __pKeypad = new Keypad();
    __pKeypad->Construct(keypadStyle, keypadCategory, nMaxLength);
    __pKeypad->AddTextEventListener(*this);

    __pKeypad->SetTextPredictionEnabled(bTextPrediction);
    __pKeypad->SetSingleLineEnabled(bSingleLineEnabled);
    __pKeypad->SetText(String(pMessage));
    __pKeypad->SetShowState(true);
    __pKeypad->Show();
}

void
CCOspForm::ShowKeypad()
{
    ShowKeypad(
        CCIMEDispatcher::sharedDispatcher()->getContentText(),
        KEYPAD_STYLE_NORMAL,
        KEYPAD_MODE_ALPHA,
        true,
        true,
        100,
        null,
        null);
}

void
CCOspForm::CloseKeypad()
{
    __pKeypad->SetShowState(false);
    Invalidate(true);
}

void
CCOspForm::OnFormBackRequested(Tizen::Ui::Controls::Form& source)
{
//	CCDirector* d = CCDirector::sharedDirector();
//	if (d) {
//		d->end();
//		d = 0;
//	}
//
//	UiApp* pApp = UiApp::GetInstance();
//	AppAssert(pApp);
//	pApp->Terminate();


	CCKeypadDispatcher* kd = CCDirector::sharedDirector()->getKeypadDispatcher();
	kd->dispatchKeypadMSG(kTypeBackClicked);
}


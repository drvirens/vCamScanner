
#include "CCOspApplication.h"
#include "CCOspForm.h"
#include "cocos2d.h"
//#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace Tizen::App;
using namespace Tizen::System;
using namespace Tizen::Ui;
using namespace Tizen::Ui::Controls;
using namespace Tizen::Base::Runtime;
using namespace Tizen::Base;

CCOspApplication * CCOspApplication::sm_pSharedCCOspApplication = 0;
CCOspApplicationInitialized CCOspApplication::sm_pApplicationInitialized = 0;
Orientation CCOspApplication::sm_eScreenOrientation = ORIENTATION_NONE;

CCOspApplication::CCOspApplication()
    : __pForm(null)
	, __isAlarmLaunchedAutomatically(false)
	, __pAutoLaunchArguments(0)
	, __isAppInitialized(false)
{
	AppLogDebug("CCOspApplication::CCOspApplication ctor ");
    CCAssert(! sm_pSharedCCOspApplication, "sm_pSharedCCOspApplication is null");
    sm_pSharedCCOspApplication = this;
    //viren+
//	CCApplication* sharedApp = CCApplication::sharedApplication();
//	if (sharedApp) {
//		AppLogDebug("set __pAutoLaunchArguments here in ctor");
//		sharedApp->SetAutoLaunch(__isAlarmLaunchedAutomatically);
//		sharedApp->SetAutoLaunchParams(__pAutoLaunchArguments);
//	} else {
//    	AppLogDebug("CCApplication still NULL in ctor");
//    }
	//viren-
}

CCOspApplication::~CCOspApplication()
{
	AppLogDebug("CCOspApplication::~CCOspApplication destructor ");
    CCAssert(this == sm_pSharedCCOspApplication, "");
    sm_pSharedCCOspApplication = NULL;
}

Application* CCOspApplication::CreateInstance(void)
{
	AppLogDebug("CCOspApplication::CreateInstance  ");
    return new (std::nothrow) CCOspApplication();
}

void CCOspApplication::SetApplicationInitializedCallback(CCOspApplicationInitialized p)
{
	AppLogDebug("CCOspApplication::SetApplicationInitializedCallback  ");
    sm_pApplicationInitialized = p;
}

void CCOspApplication::SetScreenOrientation(Orientation orientation)
{
    sm_eScreenOrientation = orientation;
}

CCOspApplication* CCOspApplication::GetInstance(void)
{
	AppLogDebug("CCOspApplication::GetInstance ");
    CCAssert(sm_pSharedCCOspApplication, "CCOspApplication::GetInstance is NULL");

    //viren+
    CCApplication* sharedApp = CCApplication::sharedApplication();
    if (sharedApp) {
    	AppLogDebug("set __pAutoLaunchArguments here in GetInstance as well");
    	sharedApp->SetAutoLaunch(sm_pSharedCCOspApplication->__isAlarmLaunchedAutomatically);
    	sharedApp->SetAutoLaunchParams(sm_pSharedCCOspApplication->__pAutoLaunchArguments);
    } else {
    	AppLogDebug("CCApplication still NULL in GetInstance");
    }
    //viren-
    return sm_pSharedCCOspApplication;
}

Tizen::Ui::Controls::Form* CCOspApplication::getCCOspForm()
{
    return __pForm;
}

bool CCOspApplication::OnAppInitializing(AppRegistry& appRegistry)
{
	AppLogDebug("CCOspApplication::OnAppInitializing");

    AppManager::GetInstance()->SetAppLaunchConditionEventListener(this);

    result r = E_SUCCESS;

    __pFrame = new (std::nothrow) Frame();
    TryReturn(__pFrame != null, E_FAILURE, "[CCOspApplication] Generating a frame failed.");

    r = __pFrame->Construct();
    TryReturn(!IsFailed(r), E_FAILURE, "[CCOspApplication] pAppFrame->Construct() failed.");

    this->AddFrame(*__pFrame);

    __pForm = new (std::nothrow) CCOspForm;
    TryCatch(__pForm != null, , "[CCOspApplication] Allocation of CCOspForm failed.");

    r = __pForm->Construct(FORM_STYLE_NORMAL);
    TryCatch(!IsFailed(r), , "[CCOspApplication] __pForm->Construct(FORM_STYLE_NORMAL) failed.");

    r = GetAppFrame()->GetFrame()->AddControl(*__pForm);
    TryCatch(!IsFailed(r), , "[CCOspApplication] GetAppFrame()->GetFrame()->AddControl(*__pForm) failed.");

    return true;

CATCH:
    delete __pForm;
    __pForm = null;

    return false;
}

bool CCOspApplication::OnAppInitialized(void)
{
	AppLogDebug("CCOspApplication::OnAppInitialized");
    sm_pApplicationInitialized();
    __pFrame->SetOrientation(sm_eScreenOrientation);

    __isAppInitialized = true;

    return true;
}

bool CCOspApplication::OnAppTerminating(AppRegistry& appRegistry, bool forcedTermination)
{
	AppLogDebug("CCOspApplication::OnAppTerminating");
    CCEGLView::sharedOpenGLView()->cleanup();

    __isAppInitialized = false;
    return true;
}

void CCOspApplication::OnForeground(void)
{
	AppLogDebug("CCOspApplication::OnForeground");
	//CocosDenshion::SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
	cocos2d::CCDirector::sharedDirector()->resume();

    Timer* timer = CCEGLView::sharedOpenGLView()->getTimer();
    if (timer != null)
    {
        timer->Start(CCApplication::sharedApplication()->getAnimationInterval());
    }
    if (CCDirector::sharedDirector()->getOpenGLView())
    {
        CCApplication::sharedApplication()->applicationWillEnterForeground();
    }
}

void CCOspApplication::OnBackground(void)
{
	//AppLogDebug("CCOspApplication::OnBackground");
	//CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
	cocos2d::CCDirector::sharedDirector()->pause();

    Timer* timer = CCEGLView::sharedOpenGLView()->getTimer();
    if (timer != null)
    {
        timer->Cancel();
    }

    CCApplication::sharedApplication()->applicationDidEnterBackground();
}

void CCOspApplication::OnLowMemory(void)
{
	AppLogDebug("CCOspApplication::OnLowMemory");
}

void CCOspApplication::OnBatteryLevelChanged(BatteryLevel batteryLevel)
{
	AppLogDebug("CCOspApplication::OnBatteryLevelChanged");
}

void CCOspApplication::OnScreenOn(void)
{
	AppLogDebug("CCOspApplication::OnScreenOn");
}

void CCOspApplication::OnScreenOff(void)
{
	AppLogDebug("CCOspApplication::OnScreenOff");
}


void CCOspApplication::OnAppLaunchConditionMetN(const Tizen::Base::String& condition,
					Tizen::Base::Object* pExtraData,
					Tizen::Base::Collection::IList* pArguments)
{
	AppLogDebug("CCOspApplication::OnAppLaunchConditionMetN = ENTER");

	if (pArguments == 0) {
		AppLogDebug("CCOspApplication::OnAppLaunchConditionMetN : pArguments is NULL, so return");
		__isAlarmLaunchedAutomatically = false;
		return;
	}

	if (pArguments->GetCount() == 0) {
		AppLogDebug("CCOspApplication::OnAppLaunchConditionMetN : pArguments count is ZERO, so return");
		__isAlarmLaunchedAutomatically = false;
		return;
	}

	AppLogDebug("condition MET is = %S", condition.GetPointer());

	AppLogDebug("arguments list size = %d", pArguments->GetCount());

	result r = PowerManager::TurnScreenOn();
	if (r != E_SUCCESS) {
		AppLogDebug("TurnScreenOn failed. Error = %S", GetErrorMessage(r));
	}
	r = PowerManager::KeepScreenOnState(true,false);
	if (r != E_SUCCESS) {
		AppLogDebug("TurnScreenOn failed. Error = %S", GetErrorMessage(r));
	}
//
//	CCApplication* sharedApp = CCApplication::sharedApplication();
//	if (sharedApp == 0) {
//		AppLogDebug("CCOspApplication::OnAppLaunchConditionMetN : sharedApplication() is NULL so return");
//		__isAlarmLaunchedAutomatically = false;
//		return;
//	}

	__isAlarmLaunchedAutomatically = true;
	__pAutoLaunchArguments = pArguments; //TODO: Create a COPY???

	AppLogDebug("Set tag and launchParams and exit...__pAutoLaunchArguments = %x", __pAutoLaunchArguments);


	//
	// If app is in background, and not killed, then we must call below
	//
	if (__isAppInitialized == false) {
		AppLogDebug("__isAppInitialized is FALSEE so no need to call below code");
		return;
	}
	CCApplication* sharedApp = CCApplication::sharedApplication();
	if (sharedApp == 0) {
		AppLogDebug("CCOspApplication::OnAppLaunchConditionMetN : sharedApplication() is NULL so return");
		return; //dont do anything
	}
	else {
		AppLogDebug("Calling sharedApp->applicationDidLaunchOnConditionMet");
		sharedApp->applicationDidLaunchOnConditionMet(pArguments);
	}


	//TODO: Delete the arguments pArguments object here??
	AppLogDebug("CCOspApplication::OnAppLaunchConditionMetN = EXIT");
}

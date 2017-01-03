
#ifndef _CCOSPAPPLICATION_H_
#define _CCOSPAPPLICATION_H_

#include <FApp.h>
#include <FUi.h>
#include <FSystem.h>

typedef void (*CCOspApplicationInitialized)(void);

class CCOspApplication
    : public Tizen::App::Application
      , public Tizen::System::IScreenEventListener
      , public Tizen::App::IAppLaunchConditionEventListener
{
public:
    /**
     * [OspApplication] application must have a factory method that creates an instance of itself.
     */
    static Tizen::App::Application* CreateInstance(void);
    static CCOspApplication* GetInstance(void);
    static void SetApplicationInitializedCallback(CCOspApplicationInitialized p);
    static void SetScreenOrientation(Tizen::Ui::Orientation orientation);

public:
    CCOspApplication();
    ~CCOspApplication();

    Tizen::Ui::Controls::Form* getCCOspForm();

    virtual bool OnAppInitializing(Tizen::App::AppRegistry& appRegistry);
    virtual bool OnAppInitialized(void);
    virtual bool OnAppTerminating(Tizen::App::AppRegistry& appRegistry, bool forcedTermination = false);
    virtual void OnForeground(void);
    virtual void OnBackground(void);
    virtual void OnLowMemory(void);
    virtual void OnBatteryLevelChanged(Tizen::System::BatteryLevel batteryLevel);

	virtual void OnScreenOn(void);
	virtual void OnScreenOff(void);
	virtual void OnAppLaunchConditionMetN(const Tizen::Base::String& condition,
				Tizen::Base::Object* pExtraData,
				Tizen::Base::Collection::IList* pArguments);

protected:
    static CCOspApplication* sm_pSharedCCOspApplication;
    static CCOspApplicationInitialized sm_pApplicationInitialized;
    static Tizen::Ui::Orientation sm_eScreenOrientation;
#if 0
private:
    void DoLaunchApplication();
#endif
private:
    Tizen::Ui::Controls::Frame* __pFrame;
    Tizen::Ui::Controls::Form* __pForm;

private:
	bool __isAlarmLaunchedAutomatically;
	Tizen::Base::Collection::IList* __pAutoLaunchArguments;
	bool __isAppInitialized;
};

#endif // _CCOSPAPPLICATION_H_

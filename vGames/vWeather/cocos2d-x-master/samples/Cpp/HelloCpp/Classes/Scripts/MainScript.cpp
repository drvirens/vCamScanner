#include "MainScript.h"
#include "Widgets/JokesWidget.h"
#include "Widgets/TimeWidget.h"
#include "Widgets/TurnOnAlarmWidget.h"
#include "Widgets/TurnOnAlarmMenuWidget.h"
#include "Widgets/AlarmTimeChooser.h"
#include "Widgets/StartFlowGameWidget.h"
#include "Widgets/FlowHelperWidget.h"
#include "Widgets/WeatherWidget.h"
#include "Logic/System.h"
#include "Logic/PrefetchAction.h"
#include "Logic/TimeGuess.h"

#include "SlidingMenu.h"

using namespace cocos2d;
MainScript::MainScript()
    : _menu_select(0), _alarm_menu(0), _alarm_time_chooser(0),
      _clock_widget(0), _jokes_widget(0)
{
}

class MainScript::AlarmSetCallback : public AlarmTimeChooser::Delegate
{
public:
    AlarmSetCallback(MainScript* parent)
        : _parent(parent)
    {}

    void onWakeUpTimeChoosen(const Time t)
    {
        _parent->step3_OnWakeUpTimeChoosen(t);
    }

    void onWakeUpAndGoOutChoosen(const Time wake_up, const Time go_out)
    {
        _parent->step3_OnWakeUpAndGoOutTimeChoosen(wake_up, go_out);
    }

    void onCancel()
    {
        _parent->step3_OnCancel();
    }

private:
    MainScript* _parent;
};

class MainScript::FlowDelegate : public FlowHelperWidget::Delegate
{
public:
    FlowDelegate(MainScript* parent)
        : _parent(parent)
    {

    }
    void onWin()
    {
        _parent->getApi()->runScript(ScriptPtr(new MainScript));
    }

private:
    MainScript* _parent;
};

/*
void MainScript::onInit()
{


    getApi()->addBackCallback(this,
                              callfunc_selector(MainScript::onLastBack));
#if 0
    _clock_widget = addWidget<TimeWidget>(getApi());
#endif

    TurnOnAlarmWidget::Mode mode = TurnOnAlarmWidget::NormalMode;
#ifdef SHOW_MORNING_STUFF
    if(System::getAlarm().isMorning())
    {
#endif
        showMorningStuff();
        mode = TurnOnAlarmWidget::MorningMode;
#ifdef SHOW_MORNING_STUFF
    }
#endif

#if 0
    _menu_select = addWidget<TurnOnAlarmWidget>(
                getApi(),
                delegate<TurnOnAlarmDelegate>(
                    this,
                    callfunc_selector(MainScript::step1_AlarmMenu),
                    this,
                    callfunc_selector(MainScript::step1_TurnOffAlarm)
                    ),
                mode);
#endif

    PrefetchAction::performPrefetch();

}
*/

void MainScript::onInit()
{
  getApi()->addBackCallback(this, callfunc_selector(MainScript::onLastBack));
  
  //showMorningStuff();
  createCitiesWeather();
  
  PrefetchAction::performPrefetch();
}

void MainScript::createCitiesWeather()
{
  std::string backgrounds[] = {"bing.jpg", "bing2.jpg", "bing.jpg", "bing2.jpg",
      "bing.jpg", "bing2.jpg"};
  
  /*
  CCArray *items = CCArray::create();
  //for (int i = 0; i < 42; i++) {
  for (int i = 0; i < 6; i++) {
    //CCSprite *sprite = CCSprite::create("bing.jpg");
    CCSprite *sprite = CCSprite::create(backgrounds[i].c_str());
    CCMenuItemSprite *item = CCMenuItemSprite::create(sprite, sprite, this, 0);
    items->addObject(item);
    item->setTag(i);
  }

//  CCSlidingGridMenu *gridMenu = CCSlidingGridMenu::create(items,
//                    5, 4, CCSizeMake(60, 50), true, ccp(240, 160), 120);

  CCSize fullScreenSize(320, 480);
  SlidingMenuGrid *gridMenu = SlidingMenuGrid::create(items,
                          1, 1, CCSizeMake(320, 480), true,
                          ccp(160,240), 10);
  getApi()->addChild(gridMenu);
  //addChild(gridMenu);
  gridMenu->setShowIndicator(true);
  gridMenu->setIndicatorSprite(CCSprite::create("pages-indicator.png"));
  CCEdgeInsets capsInset = {50, 100, 50, 100};
  gridMenu->setTouchAreaWithCapInsets(capsInset);
  */
  
  int iMaxLevels = 6;
  
  CCArray* allItems = CCArray::create();
  for (int i = 1; i <= iMaxLevels; ++i)
  {
//    CCSprite* normalSprite = CCSprite::create("LevelButton.png");
//    CCSprite* selectedSprite = CCSprite::create("LevelButton.png");
CCSprite *normalSprite = CCSprite::create(backgrounds[i].c_str());
//CCSprite *selectedSprite = CCSprite::create(backgrounds[i].c_str());

    CCMenuItemSprite* item = CCMenuItemSprite::create(normalSprite, normalSprite);
    allItems->addObject(item);
  }
  CCSize s = CCDirector::sharedDirector()->getWinSize();  
  SlidingMenuGrid* m_pSlidingMenu = SlidingMenuGrid::menuWithArray(allItems, 1, 1, ccp(s.width/2,s.height/2), CCPointMake(90, 80));
  
  getApi()->addChild(m_pSlidingMenu);

}


void MainScript::showMorningStuff()
{
#if 0
    _jokes_widget = addWidget<JokesWidget>(getApi());
    _start_flow_widget = addWidget<StartFlowGameWidget>(
                getApi(),
                delegate<StartFlowGameWidget::Delegate>(
                    this,
                    callfunc_selector(MainScript::stepX_startFlow)));
#endif
    _weather_widget = addWidget<WeatherWidget>(getApi());
  
    //viren+ : this needs to be added at the bottom
    //_weather_widget = addWidget<WeatherWidget>(getApi());
    //viren-
}

void MainScript::hideMorningStuff()
{
    if(_jokes_widget)
        getApi()->hideWidget(_jokes_widget);
    if(_start_flow_widget)
        getApi()->hideWidget(_start_flow_widget);
    if(_weather_widget)
        getApi()->hideWidget(_weather_widget);
}

void MainScript::stepX_startFlow()
{
    getApi()->addBackBarrier();
    hideMorningStuff();
    getApi()->hideWidget(_menu_select);
    getApi()->hideWidget(_clock_widget);

    addWidget<FlowHelperWidget>(
                getApi(),
                FlowHelperWidget::DelegatePtr(new FlowDelegate(this)),
                FlowHelperWidget::FreePlay);
}

void MainScript::onLastBack()
{
    CCDirector::sharedDirector()->end();
}
void MainScript::step1_TurnOffAlarm()
{
    Alarm& a = System::getAlarm();
    a.cancelAlarm();

    getApi()->runScript(ScriptPtr(new MainScript));
}

void MainScript::step1_AlarmMenu()
{
    assert(_menu_select);
    getApi()->addBackBarrier();

    hideMorningStuff();
    getApi()->hideWidget(_menu_select);

    _alarm_menu = addWidget<TurnOnAlarmMenuWidget>(
                getApi(),
                delegate<TurnOnAlarmMenuDelegate>(
                    this, callfunc_selector(MainScript::step2_WakeUpSettings),
                    this, callfunc_selector(MainScript::step2_GoOutSettings)));

}

void MainScript::step2_WakeUpSettings()
{
    assert(_alarm_menu && _clock_widget);
    getApi()->addBackBarrier();

    getApi()->hideWidget(_alarm_menu);
    getApi()->hideWidget(_clock_widget);


    _alarm_time_chooser = addWidget<AlarmTimeChooser>(
                getApi(), AlarmTimeChooser::WakeUp,
                AlarmTimeChooser::DelegatePtr(new AlarmSetCallback(this)),
                TimeGuess::getInstance().getValue(TimeGuess::WakeUp, Time(8,30))
                );
}

void MainScript::step2_GoOutSettings()
{
    assert(_alarm_menu && _clock_widget);

    getApi()->addBackBarrier();

    getApi()->hideWidget(_alarm_menu);
    getApi()->hideWidget(_clock_widget);

    _alarm_time_chooser = addWidget<AlarmTimeChooser>(
                getApi(), AlarmTimeChooser::WakeUpAndGoOut,
                AlarmTimeChooser::DelegatePtr(new AlarmSetCallback(this)),
                TimeGuess::getInstance().getValue(TimeGuess::WakeUp, Time(8,30)),
                TimeGuess::getInstance().getValue(TimeGuess::TimeToPrepare, Time(0,40)));
}

void MainScript::step3_OnWakeUpTimeChoosen(const Time t)
{
    System::getAlarm().setAlarm(t);
    getApi()->runScript(ScriptPtr(new MainScript));
}

void MainScript::step3_OnWakeUpAndGoOutTimeChoosen(const Time wake,
                                                   const Time go_out)
{
  CCLOG("MainScript::step3_OnWakeUpAndGoOutTimeChoosen");
    System::getAlarm().setAlarm(wake, go_out);

    getApi()->runScript(ScriptPtr(new MainScript));
}

void MainScript::step3_OnCancel()
{
    getApi()->runScript(ScriptPtr(new MainScript));
}

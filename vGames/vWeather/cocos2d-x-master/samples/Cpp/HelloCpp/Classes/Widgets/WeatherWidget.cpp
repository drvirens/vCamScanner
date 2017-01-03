#include "WeatherWidget.h"
#include "ContentProvider/Weather/WeatherHolder.h"
#include <sstream>
#include "Logic/Time.h"

#include "Tiles/CurrentTimeTile.h"

#include "FlexNode.h"
#include "Util/LayoutLayer.h"

USING_NS_CC_UTIL;
using namespace Weather;
using namespace cocos2d;

bool isNight(); //util function

class WeatherWidget::WeatherDelegate : public WeatherHolder::Delegate
{
public:
    WeatherDelegate(WeatherWidget* parent)
        : _parent(parent), _cancel(false)
    {}

    void onForecastArrived(const Forecast & f)
    {
        CCLog("Forecast arrived");
        if(!_cancel)
        {
            _parent->_forecast = f;
            _parent->_forecast_arrived = true;
            _parent->showWidget();
            _parent->_delegate = 0;
        }
    }

    void cancel()
    {
        _cancel = true;
    }

private:
    WeatherWidget* _parent;
    bool _cancel;
};

WeatherWidget::WeatherWidget()
    : _drawn(false), _forecast_arrived(false), _ready(false), _delegate(0)
{
    _delegate = new WeatherDelegate(this);
    WeatherHolder::getInstance().getForecast(
                WeatherHolder::DelegatePtr(_delegate));
}

  //viren+
void WeatherWidget::init() {
  CCLOG("WeatherWidget::init");
}
  //viren-


void WeatherWidget::onInit()
{
    _ready = true;
    if(_forecast_arrived)
        showWidget();
}

void temperatureToString(std::ostream& os, const Temperature t)
{
//viren+
//#ifdef SHOW_POSITIVE_SIGN
    if(t > 0)
        os << '+';
//#endif
  
    os << t;
  
    //add ° symbol
  os << "°";
    //viren-

}

std::string cloudsToString(const CloudState state)
{
    switch(state)
    {
    case Sunny: return R::tr(R::Weather_Sunny);
    case PartialyCloud: return R::tr(R::Weather_PartialyCloud);
    case Cloudy: return R::tr(R::Weather_Cloudy);
    case HeavyCloudy: return R::tr(R::Weather_HeavyCloudy);
    case ShortRain: return R::tr(R::Weather_ShortRain);
    case Rain: return R::tr(R::Weather_Rain);
    case Lightning: return R::tr(R::Weather_Lightning);
    case Hail: return R::tr(R::Weather_Hail);
    case RainSnow: return R::tr(R::Weather_RainSnow);
    case Snow: return R::tr(R::Weather_Snow);
    case HeavySnow: return R::tr(R::Weather_HeavySnow);
    }
    return "";
}

bool isNight() {
  Time now = Time::now();
  Hour nowHour = now.getHour();
  if (nowHour >= 8 && nowHour <= 18) {
    return false;
  }
  return true;
}

CCSprite* cloudsToImage(const CloudState state)
{
#if 0
    std::stringstream ss;
    ss << "weather/_" << int(state) << "_w.png";
    return CCSprite::create(ss.str().c_str());
#endif

  std::stringstream ss;
  if (isNight()) {
    ss << "weather/night/_" << int(state) << "_w.png";
  }
  else { //day
    ss << "weather/day/_" << int(state) << "_w.png";
  }
  return CCSprite::create(ss.str().c_str());
  
}
void WeatherWidget::onSuspend()
{
    _ready = false;
    if(_delegate)
    {
        _delegate->cancel();
    }
}

std::string WeatherWidget::weatherText()
{
    //bool today = true;
    std::string fr = _forecast.getForecastDate();
    if(fr.size() < 2)
        return "";

    unsigned int d1 = fr[fr.size()-2] - '0';
    unsigned int d2 = fr[fr.size()-1] - '0';

    unsigned int day = d1*10 + d2;

    time_t cur_time = time(0);
    tm* tm_val = localtime(&cur_time);
    unsigned int cur_day = tm_val->tm_mday;

    //TODO: save parsed date in forecast
    if(day == cur_day)
        return R::tr(R::Weather_Today);
    else
        return R::tr(R::Weather_Tomorrow);
}

void WeatherWidget::showWidget()
{

    if(_ready && _forecast_arrived )
    {
        time_t cur = time(0);
        time_t diff = cur - _forecast.getLastUpdate();

        if(diff < 3600 * 24 && _forecast.getCity().getID())
        {
        //viren+
          CCSize padding = CCSizeMake(2, 12);
          LayoutLayer *outer = hll()
          ->setWidthSizingPolicy(LAYOUT_SIZING_EQUAL)
          ->setPadding(padding);
          
          for (int i = 1; i < 6; ++i)
          {
            LayoutLayer *row = vll()->setPadding(padding);
            
            row->addChild(CCSprite::create("Icon.png"));
            row->addChild(FlexNode::create());
            
            std::string tmmpStr = toString(2345 * i);
            CCLOG("tmmpStr = %s", tmmpStr.c_str());
            CCLabelTTF *label = CCLabelTTF::create(
                                                   tmmpStr.c_str(),
                                                   "Thonburi",
                                                   15
                                                   );
            row->addChild(label);
              //    addLabelToTile(row, tmmpStr.c_str());
            
            outer->addChild(row);
          }
          
          outer->fitToContents();
//          this->addChild(outer);
          getApi()->addChild(outer);
          
          alignNodeToParent(outer, ALIGNMENT_BOTTOM);
        //viren-
            //If the forecast is new
            MTileBlock wb = getApi()->reserveSpace(Anchor::HMiddle, //viren: was Anchor::Right,
                                                   Anchor::Top, //viren: was Anchor::Top,
                                                   //MTileSize(6,3)); //viren: for tizen bigger tile
                                                   MTileSize(10,10)); //viren: was 6,5
                                                   //MTileSize(6,6)); //viren: added min size
            //TODO: Make it grey and transparent
            MTile* weather = MTile::create("blue.png", wb.getPosition(), wb.getSize());
          
            //viren+
          {
            //this will show it override but need to adjust size
//          CurrentTimeTile* tile = CurrentTimeTile::create(wb.getPosition(), wb.getSize());
//          getApi()->addTile(tile);
          
            MTileBlock _rs = wb; //getApi()->reserveSpace(Anchor::HMiddle, Anchor::Top,
                                 //                 MTileSize(3,3)); //viren: was (6,3));
          CurrentTimeTile* tile = CurrentTimeTile::create(_rs.getPosition(), MTileSize(3,3));
          getApi()->addTile(tile);
          }

            //viren-
          
            Forecast f = _forecast;
            std::stringstream ss;
          
            //viren: add symbol first
            //add max symbol = ↑
            //ss << "˅";
            temperatureToString(ss, f.getMinTemperature());
            //ss << " .. ";
            ss << "     ";
          
            //add max symbol = ↑
            //ss << "^";
            temperatureToString(ss, f.getMaxTemperature());



            CCLabelTTF* title = LF::label(cloudsToString(f.getCloudState()).c_str(),
                                          LF::MEDIUM_FONT);
//viren: improve the ui for tizen
//#ifdef SHOW_WEATHER_SUMMARY
//#if (CC_TARGET_PLATFORM != CC_PLATFORM_TIZEN)
            weather->addChild(title, Aligment::Left, Aligment::Top);
//#endif
            CCSprite* icon = cloudsToImage(f.getCloudState());
            //icon->setScale(1.15f);
            icon->setScale(0.80f);

            float center_margin = icon->getContentSize().width*0.2f;
            float top_margin = icon->getContentSize().width*0.15f;//was 0.3
          
            weather->addChild(icon,
            Aligment::HCenter, //viren : original was : Aligment::Right,
            //Aligment::VCenter, //viren make it top
            Aligment::Top,
            0,
            -top_margin); // viren - original was : center_margin);


            float temp_size = LF::BIG_FONT*1.25f;
            CCLabelTTF* temperature = LF::label(ss.str().c_str(),temp_size);
          
            //viren+
#if 0 //original
            weather->addChild(temperature,
                              Aligment::Left,
                              Aligment::VCenter,
                              0,
                              center_margin+LF::vfix(temp_size)/2);
#endif
          weather->addChild(temperature,
                            Aligment::HCenter,
                            Aligment::Bottom,
                            0,
                            0);//top_margin+LF::vfix(temp_size)/2);
                            //viren-
            std::stringstream sub_tit;
            sub_tit << f.getCity().getName() << weatherText();

            CCLabelTTF* city = LF::label(sub_tit.str().c_str(), LF::SMALL_FONT);
//viren: improve the UI
//#ifdef SHOW_CITY_NAME
            weather->addChild(city, Aligment::Left, Aligment::Bottom);
//#endif
            getApi()->addTile(weather);

            //if(isUmbrellaNeeded(f))
            //  showUmbrellaAlarm();
        }
    }
}

void WeatherWidget::showUmbrellaAlarm()
{
    //If the forecast is new
    MTileBlock wb = getApi()->reserveSpace(Anchor::Right,
                                           Anchor::Top,
                                           MTileSize(1,1));
                                           //viren: original = was crashing cuz width==0, height == 0 MTileSize(6,2));
 //viren+
  assert( wb.getSize().width() != 0);
  assert( wb.getSize().height() != 0);
  //viren-
  
    MTile* umbr = MTile::create("red.png", wb.getPosition(),
                                   wb.getSize());

    addImageAndLabelToTile(umbr, R::tr(R::Waether_DoNotForgetUmbrella), "umbrella.png");
    getApi()->addTile(umbr);

}

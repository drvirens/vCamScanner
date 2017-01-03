#include "WeatherPanel.h"
#include "ContentProvider/Weather/WeatherHolder.h"
#include <sstream>
#include "Logic/Time.h"

#include "Tiles/CurrentTimeTile.h"
#include "Core/LabelFactory.h"

#include "news_app/homeUI/Global.h"

class WeatherPanel::WeatherDelegate : public WeatherHolder::Delegate
{
public:
    WeatherDelegate(WeatherPanel* parent)
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
    WeatherPanel* _parent;
    bool _cancel;
};

WeatherPanel::WeatherPanel(CCNode* row, CCNode* parent)
    : _drawn(false), _forecast_arrived(false), _ready(false), _delegate(0),
      mRow(row), mParent(parent)
{
    _delegate = new WeatherDelegate(this);
    WeatherHolder::getInstance().getForecast(
                WeatherHolder::DelegatePtr(_delegate));
}

bool WeatherPanel::init() {
  if ( !CCLayer::init() )
  {
    return false;
  }
  onInit();

  return true;
}

void WeatherPanel::showPlaceholderWeatherWidgets() {
  const CCSize& windowSize = CCDirector::sharedDirector()->getWinSize();
  
    //Current location icon
  iLocationIcon = CCSprite::create("current_location.png");
  iLocationIcon->setScale(0.45f);
  this->addChild(iLocationIcon);
  
    //Current city name
  iCurrentCityNameLabel = CCLabelTTF::create("New York", DEFAULT_FONT,
                                             DEFAULT_SETTINGS_LABEL_SIZE * SCREEN_SCALE() * 1.0f );
  iCurrentCityNameLabel->setColor(ccWHITE);
  //this->addChild(iCurrentCityNameLabel);

    //Textual forecast for next hour
  iForecastSummaryLabel = CCLabelTTF::create("Clear sky", DEFAULT_FONT,
                                               DEFAULT_SETTINGS_LABEL_SIZE * SCREEN_SCALE() * 1.0f );
  iForecastSummaryLabel->setColor(ccWHITE);
  this->addChild(iForecastSummaryLabel);
  
    //Weather icon
  iForecastSummaryIcon = cloudsToImage(Undefined);
  iForecastSummaryIcon->setScale(0.30f);
  this->addChild(iForecastSummaryIcon);
  
    //Temperature
  iTemperatureLabel = CCLabelTTF::create("4 deg C", DEFAULT_FONT,
                                                     DEFAULT_SETTINGS_LABEL_SIZE * SCREEN_SCALE() * 1.0f );
  iForecastSummaryLabel->setColor(ccWHITE);
  this->addChild(iTemperatureLabel);
  
  if (this->m_pChildren) {
    doAlignItemsHorizontallyWithPadding(10.0f);
  }
  
  mParent->addChild(this);
  const CCPoint thePoint = ccp(windowSize.width * 0.50f, windowSize.height * 0.85f);
  this->setPosition(thePoint);
}

void WeatherPanel::showWidget()
{
  if(_ready && _forecast_arrived )
  {
    time_t cur = time(0);
    time_t diff = cur - _forecast.getLastUpdate();
    
    if(diff < 3600 * 24 && _forecast.getCity().getID())
    {
      // CurrentTimeTile* tile = CurrentTimeTile::create(_rs.getPosition(), MTileSize(3,3));
      Forecast f = _forecast;
      std::stringstream ss;
      
      temperatureToString(ss, f.getMinTemperature());
      ss << "..";
      temperatureToString(ss, f.getMaxTemperature());
      
      const char* labelForecastSummary = cloudsToString(f.getCloudState()).c_str();
      iForecastSummaryLabel->setString(labelForecastSummary);
      
      std::string path = getWeatherImagePath(f.getCloudState());
      iForecastSummaryIcon->setTexture(CCTextureCache::sharedTextureCache()->addImage(path.c_str()));
      
      const char* labelTemperature = ss.str().c_str();
      iTemperatureLabel->setString(labelTemperature);

      std::stringstream sub_tit;
      sub_tit << f.getCity().getName() << weatherText();
      const char* labelCityName = sub_tit.str().c_str();
    }
  }
}


void WeatherPanel::onInit()
{
    _ready = true;
  
  showPlaceholderWeatherWidgets();
    if(_forecast_arrived)
        showWidget();
}

void WeatherPanel::temperatureToString(std::ostream& os, const Temperature t)
{
    if(t > 0)
        os << '+';
    os << t;
    os << "°";
}

std::string WeatherPanel::cloudsToString(const CloudState state)
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

bool WeatherPanel::isNight() {
  Time now = Time::now();
  Hour nowHour = now.getHour();
  if (nowHour >= 8 && nowHour <= 18) {
    return false;
  }
  return true;
}

std::string WeatherPanel::getWeatherImagePath(const CloudState state)
{
  std::stringstream ss;
  if (isNight()) {
    ss << "weather/night/_" << int(state) << "_w.png";
    }
    else { //day
      ss << "weather/day/_" << int(state) << "_w.png";
    }
  std::string path = ss.str();
  return path;
}

CCSprite* WeatherPanel::cloudsToImage(const CloudState state)
{
  std::string path = getWeatherImagePath(state);
  return CCSprite::create(path.c_str());
}


void WeatherPanel::onSuspend()
{
    _ready = false;
    if(_delegate)
    {
        _delegate->cancel();
    }
}

std::string WeatherPanel::weatherText()
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

void WeatherPanel::showUmbrellaAlarm()
{
//    //If the forecast is new
//    MTileBlock wb = getApi()->reserveSpace(Anchor::Right,
//                                           Anchor::Top,
//                                           MTileSize(1,1));
//                                           //viren: original = was crashing cuz width==0, height == 0 MTileSize(6,2));
// //viren+
//  assert( wb.getSize().width() != 0);
//  assert( wb.getSize().height() != 0);
//  //viren-
//  
//    MTile* umbr = MTile::create("red.png", wb.getPosition(),
//                                   wb.getSize());
//
//    addImageAndLabelToTile(umbr, R::tr(R::Waether_DoNotForgetUmbrella), "umbrella.png");
//    getApi()->addTile(umbr);

}

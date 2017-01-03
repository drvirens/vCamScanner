

#ifndef WEATHERWIDGET_PANEL_H
#define WEATHERWIDGET_PANEL_H


#include "ContentProvider/Weather/Forecast.h"
#include "cocos2d.h"

#include "VirenBaseLayer.h"

using namespace Weather;
USING_NS_CC;

class WeatherPanel : public VirenBaseLayer //CCLayer //VirenBaseLayer
{
public:
    WeatherPanel(CCNode* row, CCNode* parent);
    virtual bool init();

private:
  void temperatureToString(std::ostream& os, const Temperature t);
  std::string cloudsToString(const CloudState state);
  bool isNight();
  CCSprite* cloudsToImage(const CloudState state);
  
  
  class WeatherDelegate;
    void onInit();
    void onSuspend();
    void showWidget();
    void showUmbrellaAlarm();
    std::string weatherText();
    bool _forecast_arrived;
    bool _drawn;
    bool _ready;
    Weather::Forecast _forecast;
    WeatherDelegate* _delegate;
  
  void showPlaceholderWeatherWidgets();
  std::string getWeatherImagePath(const CloudState state);
  
    //Current location icon
  CCSprite* iLocationIcon;
    //Current city name
  CCLabelTTF* iCurrentCityNameLabel;
    //Textual forecast for next hour
  CCLabelTTF* iForecastSummaryLabel;
    //Weather icon
  CCSprite* iForecastSummaryIcon;
    //Temperature
  CCLabelTTF* iTemperatureLabel;
  
  CCNode* mRow;
  CCNode* mParent;
};

#endif // WEATHERWIDGET_PANEL_H

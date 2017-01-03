#ifndef FORECAST_H
#define FORECAST_H
#include "City.h"
#include <ctime>
#include <string>
namespace Weather
{

typedef int Temperature;
typedef unsigned int RainProbability;
enum CloudState
{
    Sunny = 0, //Sunny
    PartialyCloud = 1, //Cloudy with rain
    Cloudy = 2,
    HeavyCloudy = 3,
    ShortRain = 4,
    Rain = 5,
    Lightning = 6, //storm
    Hail = 7,
    RainSnow =8, //Rain and snow
    Snow = 9,
    HeavySnow = 10, //Heavy Snow
    Undefined

};

class Forecast
{
public:
    Forecast();
  
    //viren+
    void doCopy(const Forecast& aRhs);
    Forecast(const Forecast& aRhs);
    Forecast& operator=(const Forecast& aRhs);
    //viren-

    void setLastUpdate(const time_t last_update);
    const time_t getLastUpdate() const;

    void setCity(const City& city);
    const City& getCity() const;

    void setMinTemperature(const Temperature t);
    const Temperature getMinTemperature() const;

    void setMaxTemperature(const Temperature t);
    const Temperature getMaxTemperature() const;

    void setCloudState(const CloudState st);
    const CloudState getCloudState() const;

    void setRainProbability(const RainProbability prob);
    RainProbability getRainProbability() const;
    bool isRainProbabilityDefined() const;

    void setForecastDate(const std::string& date);
    const std::string& getForecastDate() const;
private:
    City _city;
    Temperature _min;
    Temperature _max;
    CloudState _state;
    RainProbability _rain_probability;
    bool _is_pobability_defined;

    time_t _last_update;
    std::string _forecast_date;
};

bool isUmbrellaNeeded(const Forecast& f);

}

#endif // FORECAST_H

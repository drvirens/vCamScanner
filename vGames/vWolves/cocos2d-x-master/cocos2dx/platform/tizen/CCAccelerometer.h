

//viren+

#ifndef __PLATFORM_TIZEN_CCACCELEROMETER_H__
#define __PLATFORM_TIZEN_CCACCELEROMETER_H__

#include "platform/CCCommon.h"
#include "platform/CCAccelerometerDelegate.h"
#include <FUix.h>

NS_CC_BEGIN

class CC_DLL CCAccelerometer : public Tizen::Uix::Sensor::ISensorEventListener
{
public:
    CCAccelerometer();
    ~CCAccelerometer();

    void setDelegate(CCAccelerometerDelegate* pDelegate);
    void setAccelerometerInterval(float interval);
    void startSensor();
    void stopSensor();

    virtual void OnDataReceived(Tizen::Uix::Sensor::SensorType sensorType, Tizen::Uix::Sensor::SensorData& sensorData , result r);

private:
    CCAccelerometerDelegate* _accelDelegate;
    CCAcceleration _accelerationValue;
    Tizen::Uix::Sensor::SensorManager* __sensorMgr;
};

NS_CC_END

#endif



#if 0 //viren: original

#ifndef __PLATFORM_TIZEN_CCACCELEROMETER_H__
#define __PLATFORM_TIZEN_CCACCELEROMETER_H__

#include "platform/CCCommon.h"
#include "platform/CCAccelerometerDelegate.h"

NS_CC_BEGIN

class CC_DLL CCAccelerometer
{
public:
    CCAccelerometer();
    ~CCAccelerometer();

    void setDelegate(CCAccelerometerDelegate* pDelegate);
    void setAccelerometerInterval(float interval);
    void update(float x, float y, float z, long sensorTimeStamp);

private:
    CCAccelerometerDelegate* m_pAccelDelegate;
    CCAcceleration m_obAccelerationValue;
};

NS_CC_END

#endif

#endif
//viren-

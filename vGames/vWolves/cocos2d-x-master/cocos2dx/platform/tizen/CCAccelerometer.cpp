
#if 0 //original

#include "CCAccelerometer.h"
#include <stdio.h>

NS_CC_BEGIN

CCAccelerometer::CCAccelerometer() : m_pAccelDelegate(NULL)
{
}

CCAccelerometer::~CCAccelerometer()
{

}

void CCAccelerometer::setDelegate(CCAccelerometerDelegate* pDelegate)
{
    m_pAccelDelegate = pDelegate;

    if (pDelegate)
    {
    }
    else
    {
    }
}

void CCAccelerometer::setAccelerometerInterval(float interval)
{
}


void CCAccelerometer::update(float x, float y, float z, long sensorTimeStamp)
{
    if (m_pAccelDelegate)
    {
    }
}
NS_CC_END

#endif

#include "CCAccelerometer.h"
#include "CCOspApplication.h"

using namespace Tizen::Uix::Sensor;

NS_CC_BEGIN

CCAccelerometer::CCAccelerometer()
    : _accelDelegate(NULL)
    , __sensorMgr(NULL)
{
}

CCAccelerometer::~CCAccelerometer()
{

}

void CCAccelerometer::setDelegate(CCAccelerometerDelegate* pDelegate)
{
    _accelDelegate = pDelegate;

    if (pDelegate)
    {
        startSensor();
    }
    else
    {
        stopSensor();
    }
}

void CCAccelerometer::setAccelerometerInterval(float interval)
{
    if (__sensorMgr)
    {
        __sensorMgr->SetInterval(SENSOR_TYPE_ACCELERATION, interval * 1000);
    }
}

void CCAccelerometer::startSensor()
{
    long interval = 0L;

    if (__sensorMgr)
    {
        __sensorMgr->RemoveSensorListener(*this);
        delete __sensorMgr;
        __sensorMgr = null;
    }

    __sensorMgr = new SensorManager();
    __sensorMgr->Construct();
    __sensorMgr->GetMinInterval(SENSOR_TYPE_ACCELERATION, interval);

    if (interval < 50)
    {
        interval = 50;
    }
    __sensorMgr->AddSensorListener(*this, SENSOR_TYPE_ACCELERATION, interval, true);

}

void CCAccelerometer::stopSensor()
{
    if (__sensorMgr)
    {
        __sensorMgr->RemoveSensorListener(*this);
        delete __sensorMgr;
        __sensorMgr = null;
    }
}

#if 0
- (void)accelerometer:(UIAccelerometer *)accelerometer didAccelerate:(UIAcceleration *)acceleration
{
    if (! delegate_)
    {
        return;
    }

    acceleration_->x = acceleration.x;
    acceleration_->y = acceleration.y;
    acceleration_->z = acceleration.z;
    acceleration_->timestamp = acceleration.timestamp;

    double tmp = acceleration_->x;

    switch ([[UIApplication sharedApplication] statusBarOrientation])
    {
    case UIInterfaceOrientationLandscapeRight:
        acceleration_->x = -acceleration_->y;
        acceleration_->y = tmp;
        break;

    case UIInterfaceOrientationLandscapeLeft:
        acceleration_->x = acceleration_->y;
        acceleration_->y = -tmp;
        break;

    case UIInterfaceOrientationPortraitUpsideDown:
        acceleration_->x = -acceleration_->y;
        acceleration_->y = -tmp;
        break;

    case UIInterfaceOrientationPortrait:
        break;
    }

    delegate_->didAccelerate(acceleration_);
}

#endif

void CCAccelerometer::OnDataReceived(SensorType sensorType, SensorData& sensorData , result r)
{
	//viren+
#if 0
    if (_accelDelegate)
    {
        AccelerationSensorData& data = static_cast<AccelerationSensorData&>(sensorData);
        AppLog("AccelerationSensorData    x = %5.4f , y = %5.4f,  z = %5.4f ", data.x,data.y,data.z);

        _accelerationValue.x = -data.x;
        _accelerationValue.y = -data.y;
        _accelerationValue.z = -data.z;
        _accelerationValue.timestamp = data.timestamp;

        _accelDelegate->didAccelerate(&_accelerationValue);
    }
#endif
    if (!_accelDelegate)
    {
    	return;
    }
        AccelerationSensorData& data = static_cast<AccelerationSensorData&>(sensorData);
        //AppLogDebug("AccelerationSensorData    x = %5.4f , y = %5.4f,  z = %5.4f ", data.x,data.y,data.z);

        Tizen::Ui::Orientation currOrientation = CCOspApplication::GetScreenOrientation();

        _accelerationValue.x = data.x;
        _accelerationValue.y = data.y;
         _accelerationValue.z = data.z;
         _accelerationValue.timestamp = data.timestamp;

        double tmp = data.x;

        switch(currOrientation) {
			case Tizen::Ui::ORIENTATION_NONE:                       /**< The control has no orientation style */
			{
				break;
			}
			case Tizen::Ui::ORIENTATION_PORTRAIT:                   /**< The control has vertical orientation style */
			{
				_accelerationValue.x = -data.y;
				_accelerationValue.y = -tmp;
				break;
			}
			case Tizen::Ui::ORIENTATION_LANDSCAPE:                  /**< The control has horizontal orientation style */
			{
				//below 2 lines will make object away from tilted side, away from gravity. it should move towards gravity
//				_accelerationValue.x = -data.y;
//				_accelerationValue.y = tmp;

				_accelerationValue.x = data.y;
				_accelerationValue.y = -tmp;
				break;
			}
			case Tizen::Ui::ORIENTATION_PORTRAIT_REVERSE:       /**< The control has vertical upside-down orientation style */
			{
				break;
			}
			case Tizen::Ui::ORIENTATION_LANDSCAPE_REVERSE:          /**< The control has horizontal reverse orientation style */
			{
				break;
			}
			case Tizen::Ui::ORIENTATION_AUTOMATIC:                  /**< The control has vertical, horizontal, and horizontal reverse orientation styles */
			{
				break;
			}
			case Tizen::Ui::ORIENTATION_AUTOMATIC_FOUR_DIRECTION:   /**< The control has four-directional orientation style */
			{
				break;
			}
        } //switch

        _accelDelegate->didAccelerate(&_accelerationValue);

    //viren-
}

NS_CC_END


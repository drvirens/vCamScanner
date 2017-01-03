

#include <new>
#include <FGraphics.h>
#include <FLocales.h>
#include <FLocCoordinates.h>
#include <FSysSettingInfo.h>
#include <FSysSystemTime.h>
#include "LocationManagerMainForm.h"
#include "LocationManagerThread.h"

using namespace std;
using namespace Tizen::App;
using namespace Tizen::Base;
using namespace Tizen::Base::Collection;
using namespace Tizen::Base::Utility;
using namespace Tizen::Graphics;
using namespace Tizen::Locales;
using namespace Tizen::Locations;
using namespace Tizen::Ui;
using namespace Tizen::Ui::Controls;
using namespace Tizen::Ui::Scenes;

LocationManagerMainForm::LocationManagerMainForm(void)
	: __viewType(VIEW_TYPE_NONE)
	, __pLocProvider(null)
	, __pLocationManagerThread(null)
	, __regionId(-1)
	, __isUpdateInProgress(false)
{
}

LocationManagerMainForm::~LocationManagerMainForm(void)
{
}

bool
LocationManagerMainForm::Initialize(void)
{
	OnInitializing();
	return true;
}

result
LocationManagerMainForm::OnInitializing(void)
{
	result r = E_SUCCESS;
	__pLocationManagerThread =  new (std::nothrow) LocationManagerThread();
	r = __pLocationManagerThread->Construct(/* *this */);
	if (IsFailed(r))
	{
		AppLogDebug("Thread Construct failed.");
		return r;
	}

	LocationCriteria criteria;
	criteria.SetAccuracy(LOC_ACCURACY_HUNDRED_METERS);

	__pLocProvider = new (std::nothrow) LocationProvider();
	r = __pLocProvider->Construct(criteria, *this);
	if (r != E_SUCCESS)
	{
		AppLogDebug("Location Provider construct failed.");
	}

	return r;
}

result LocationManagerMainForm::OnTerminating(void)
{
	AppLogDebug("LocationManagerMainForm::OnTerminating");
	delete __pLocProvider;
	__pLocationManagerThread->Join();
	delete __pLocationManagerThread;

	return E_SUCCESS;
}


#if 0
		case ID_CONTEXT_UPDATE_INTERVAL:
		{
			result res = __pLocProvider->StartLocationUpdatesByInterval(3);

			if (res == E_USER_NOT_CONSENTED)
			{
				bool isSettingEnabled = CheckLocationSetting();
				if (!isSettingEnabled)
				{
					LaunchLocationSettings();
				}
				else
				{
					ShowMessageBox(L"Privacy protection", L"Please allow the application to use your location. You can change settings at Settings->Privacy.");
				}
			}
		}
		case ID_POPUP_REGION_CANCEL:
		{
			__pRegionCenterLatitude->Clear();
			__pRegionCenterLongitude->Clear();
			__pRegionRadius->Clear();
		}
#endif


void LocationManagerMainForm::CancelLocationUpdates() {
	AppLogDebug("LocationManagerMainForm::CancelLocationUpdates");
	if (__pLocationManagerThread) {
		result r = E_SUCCESS;
		if(__pLocProvider) {
			r = __pLocProvider->StopLocationUpdates();
		}
		// if thread is running
		__pLocationManagerThread->Stop();
		__pLocationManagerThread->Join();
	}

}

/*
 void GetLastKnownLocation() {
	Location location = LocationProvider::GetLastKnownLocation();
	result lastResult = GetLastResult();

	if (lastResult == E_USER_NOT_CONSENTED)
	{
		bool isSettingEnabled = CheckLocationSetting();
		if (!isSettingEnabled)
		{
			LaunchLocationSettings();
		}
		else
		{
			ShowMessageBox(L"Privacy protection", L"Please allow the application to use your location. You can change settings at Settings->Privacy.");
		}
		return;
	}
	if (location.IsValid())
	{
		AppLogDebug("The last location is obtained successfully.");
		LogLocationInfo(location);
	}
	else
	{
		AppLogDebug("Failed to fetch the last location");
	}
}
 */
double LocationManagerMainForm::GetLastKnownLongitude() {
	AppLogDebug("LocationManagerMainForm::GetLastKnownLongitude");
	double longi = 0.0;
	return longi;
}

double LocationManagerMainForm::GetLastKnownLatitude() {
	AppLogDebug("LocationManagerMainForm::GetLastKnownLatitude");
	double lati = 0.0;
	return lati;
}

void LocationManagerMainForm::GetCurrentLocation() {
	AppLogDebug("ID_CONTEXT_GET_CURRENT");
	result r = __pLocationManagerThread->Start();
	if (IsFailed(r))
	{
		AppLogDebug("Failed to fetch the current location");
	}
}


void LocationManagerMainForm::OnLocationUpdated(const Tizen::Locations::Location& location)
{
	AppLogDebug("Location update obtained for application.");
	LogLocationInfo(location);
}

void LocationManagerMainForm::OnLocationUpdateStatusChanged(LocationServiceStatus status)
{
	AppLogDebug("Service Status is (%d)", status);

	switch(status)
	{
	case LOC_SVC_STATUS_RUNNING:
		AppLogDebug("Update Status: Running");
		break;

	case LOC_SVC_STATUS_PAUSED:
		AppLogDebug("Update Status: Paused");
		break;

	case LOC_SVC_STATUS_DENIED:
		AppLogDebug("Update Status: Denied");
		break;

	case LOC_SVC_STATUS_NOT_FIXED:
		AppLogDebug("Update Status: Not Fixed");
		break;

	case LOC_SVC_STATUS_IDLE:
		AppLogDebug("Update Status: Idle");
		break;
	}
}

void LocationManagerMainForm::OnRegionEntered(RegionId regionId)
{
	AppLogDebug("Region Entered for Id (%d)", regionId);
}

void LocationManagerMainForm::OnRegionLeft(RegionId regionId)
{
	AppLogDebug("Region Left for Id (%d)", regionId);
}

void LocationManagerMainForm::OnRegionMonitoringStatusChanged(LocationServiceStatus status)
{
	AppLogDebug("Service Status is (%d)", status);
	switch(status)
	{
	case LOC_SVC_STATUS_RUNNING:
		AppLogDebug("Monitoring Status: Running");
		break;
	case LOC_SVC_STATUS_PAUSED:
		AppLogDebug("Monitoring Status: Paused");
		break;
	case LOC_SVC_STATUS_DENIED:
		AppLogDebug("Monitoring Status: Denied");
		break;
	case LOC_SVC_STATUS_NOT_FIXED:
		AppLogDebug("Monitoring Status: Not Fixed");
		break;
	case LOC_SVC_STATUS_IDLE:
		AppLogDebug("Monitoring Status: Idle");
		break;
	}
}

void
LocationManagerMainForm::OnAccuracyChanged(LocationAccuracy accuracy)
{
	AppLogDebug("Accuracy changed to (%d)", accuracy);
	switch(accuracy)
	{
	case LOC_ACCURACY_FINEST:
		AppLogDebug("Location Accuracy: Finest");
		break;
	case LOC_ACCURACY_TEN_METERS:
		AppLogDebug("Location Accuracy: Ten meters");
		break;
	case LOC_ACCURACY_HUNDRED_METERS:
		AppLogDebug("Location Accuracy: Hundred meters");
		break;
	case LOC_ACCURACY_ONE_KILOMETER:
		AppLogDebug("Location Accuracy: One Kilometer");
		break;
	case LOC_ACCURACY_ANY:
		AppLogDebug("Location Accuracy: Any");
		break;
	case LOC_ACCURACY_INVALID:
		AppLogDebug("Location Accuracy: Invalid");
		break;
	}
}

void LocationManagerMainForm::DrawLocationInformation(const Tizen::Locations::Location& location)
{
	Coordinates coord = location.GetCoordinates();

	String print = "Latitude: " + Double::ToString(coord.GetLatitude()) + L" " +
							 L"Longitude: " + Double::ToString(coord.GetLongitude()) + L"\n" +
							 L"Altitude: " + Double::ToString(coord.GetAltitude()) + L"\n";
	AppLogDebug("%S", print.GetPointer());

//	print = "Speed: "+ Double::ToString(location.GetSpeed()) ;
//	AppLogDebug("%S", print.GetPointer());
//
//	print = "Course: "+ Double::ToString(location.GetCourse());
//	AppLogDebug("%S", print.GetPointer());
//
//	print = "Vertical Accuracy: " + Double::ToString(location.GetVerticalAccuracy()) ;
//	AppLogDebug("%S", print.GetPointer());
//
//	print = "Horizontal Accuracy: " + Double::ToString(location.GetHorizontalAccuracy()) ;
//	AppLogDebug("%S", print.GetPointer());
//
//	DateTime datetime = location.GetTimestamp();
//	LocaleManager lclMgr;
//	result r = lclMgr.Construct();
//	if (r == E_SUCCESS)
//	{
//		int offset = lclMgr.GetSystemTimeZone().GetRawOffset();
//		datetime.AddMinutes(offset);
//	}
//
//	print = "Timestamp: " + datetime.ToString();
//	AppLogDebug("%S", print.GetPointer());
//
//	String satelliteInfoKey = L"satellite";
//	String methodName = L"location_method";
//
//	AppLogDebug("Location Method: ");
//	print =  location.GetExtraInfo(methodName);
//	AppLogDebug("%S", print.GetPointer());
//
//	AppLogDebug("Satellite Information: ");
//
//	String satelliteInfo = location.GetExtraInfo(satelliteInfoKey);
//	StringTokenizer satInfotoken(satelliteInfo, L";");
//	int count = satInfotoken.GetTokenCount();
//
//	for (int i = 0; i < count; i ++)
//	{
//		String element;
//		satInfotoken.GetNextToken(element);
//		StringTokenizer satElements(element, L",");
//
//		String prn;
//		String elevation;
//		String azimuth;
//		String snr;
//		satElements.GetNextToken(prn);
//		satElements.GetNextToken(elevation);
//		satElements.GetNextToken(azimuth);
//		satElements.GetNextToken(snr);
//
//		prn.Trim();
//		elevation.Trim();
//		azimuth.Trim();
//		snr.Trim();
//
//		print = Integer::ToString(i + 1) + L")" + L" Id: " + prn + L" Elevation: " + elevation + L" Azimuth: " + azimuth + L" SNR: " + snr ;
//		AppLogDebug("%S", print.GetPointer());
//	}
}

void LocationManagerMainForm::AddMonitoringRegion(void)
{
//	double latitude = 0.0;
//	double longitude = 0.0;
//	double radius = 0.0;
//	bool success = true;
//
//	AppLogDebug("Now the regions will be added.");
//
//	result r = Double::Parse(__pRegionCenterLatitude->GetText(), latitude);
//	if (r != E_SUCCESS)
//	{
//		success = false;
//	}
//
//	r = Double::Parse(__pRegionCenterLongitude->GetText(), longitude);
//	if (r != E_SUCCESS)
//	{
//		success = false;
//	}
//
//	r = Double::Parse(__pRegionRadius->GetText(), radius);
//	if (r != E_SUCCESS)
//	{
//		success = false;
//	}
//
//	if (success == false)
//	{
//		ShowMessageBox(L"Invalid input", L"The region info provided is not proper.");
//	}
//	else
//	{
//		__regionCenter.Set(latitude, longitude, 0.0);
//		__regionRadius = radius;
//
//		if (__regionId != -1)
//		{
//			__pLocProvider->RemoveMonitoringRegion(__regionId);
//			AppLogDebug("Monitoring region with region Id " + String(Integer::ToString(__regionId)) + L" removed\n");
//
//			__regionId = -1;
//
//
//			AppLogDebug("Location Accuracy: Invalid");
//
//
//
//			AppLogDebug("Monitoring Status: Idle");
//
//		}
//		result r = __pLocProvider->AddMonitoringRegion(__regionCenter, __regionRadius, __regionId);
//		if (r == E_USER_NOT_CONSENTED)
//		{
//			bool isSettingEnabled = CheckLocationSetting();
//			if (!isSettingEnabled)
//			{
//				LaunchLocationSettings();
//			}
//			else
//			{
//				ShowMessageBox(L"Privacy protection", L"Please allow the application to use your location. You can change settings at Settings->Privacy.");
//			}
//			return;
//		}
//		else if (IsFailed(r))
//		{
//			ShowMessageBox(L"Invalid input", L"The region info provided is not proper.");
//			return;
//
//		}
//		AppLogDebug("Monitoring region with region Id " + String(Integer::ToString(__regionId)) + L" added\n");
//
//
//	}
}


void
LocationManagerMainForm::ShowMessageBox(const String& title, const String& message)
{
	MessageBox messageBox;
	messageBox.Construct(title, message, MSGBOX_STYLE_OK);
	int ModalResult;
	messageBox.ShowAndWait(ModalResult);
}

void
LocationManagerMainForm::LogLocationInfo(const Tizen::Locations::Location location)
{
	String timeStamp = location.GetTimestamp().ToString();
	String extraInfo = L"satellite";

	Coordinates coord = location.GetCoordinates();
	AppLogDebug("Location Information: Latitude = %lf, Longitude = %lf, Altitude = %lf", coord.GetLatitude(), coord.GetLongitude(), coord.GetAltitude());
	AppLogDebug("Location Information: Horizontal Accuracy = %f, Vertical Accuracy = %f", location.GetHorizontalAccuracy(), location.GetVerticalAccuracy());
	AppLogDebug("Location Information: Direction = %f, Speed = %f", location.GetCourse(), location.GetSpeed());
	AppLogDebug("Location Information: SatelliteInfo = %ls", location.GetExtraInfo(extraInfo).GetPointer());
	AppLogDebug("Location Information: TimeStamp = %ls",timeStamp.GetPointer());
}

void
LocationManagerMainForm::OnUserEventReceivedN(RequestId requestId, Tizen::Base::Collection::IList* pArgs)
{
	if (requestId == LOC_MGR_DRAW_SYNC_LOC_UPDATE)
	{
		Location* pLocation = static_cast<Location*> (pArgs->GetAt(0));

		if (pLocation->IsValid())
		{
			DrawLocationInformation(*pLocation);
		}
		else
		{

			AppLogDebug("Failed to fetch the current location");

		}
	}
	else if(requestId == LOC_MGR_NOTIFY_ERROR)
	{
		bool isSettingEnabled = CheckLocationSetting();
		if (!isSettingEnabled)
		{
			LaunchLocationSettings();
		}
		else
		{
			ShowMessageBox(L"Privacy protection", L"Please allow the application to use your location. You can change settings at Settings->Privacy.");
		}
	}

	if(pArgs)
	{
		pArgs->RemoveAll(true);
		delete pArgs;
	}
}

void
LocationManagerMainForm::LaunchLocationSettings(void)
{
	int res;

	MessageBox messageBox;
	messageBox.Construct(L"Information", L"Location services are disabled. Enable them in location settings?", MSGBOX_STYLE_YESNO);
	messageBox.ShowAndWait(res);

	if (res == MSGBOX_RESULT_YES)
	{
		HashMap extraData;
		extraData.Construct();
		String categoryKey = L"category";
		String categoryVal = L"Location";
		extraData.Add(&categoryKey, &categoryVal);

		AppControl* pAc = AppManager::FindAppControlN(L"tizen.settings", L"http://tizen.org/appcontrol/operation/configure");

		if (pAc)
		{
			pAc->Start(null, null, &extraData, this);
			delete pAc;
		}
	}
	return;
}

bool
LocationManagerMainForm::CheckLocationSetting(void)
{
	bool hasPrivilege = false;
	bool gpsEnabled = true;
	bool wpsEnabled = true;

	result gps = Tizen::System::SettingInfo::GetValue(L"http://tizen.org/setting/location.gps", gpsEnabled);
	result wps = Tizen::System::SettingInfo::GetValue(L"http://tizen.org/setting/location.wps", wpsEnabled);

	hasPrivilege = gpsEnabled | wpsEnabled;
	if (gps != E_SUCCESS || wps != E_SUCCESS || hasPrivilege == false)
	{
		return false;
	}

	return true;
}

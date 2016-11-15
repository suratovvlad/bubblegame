#ifndef _ENGINE_DEVICEINFO_H_
#define _ENGINE_DEVICEINFO_H_

class DeviceInfo
{
public:

	static std::string GetConnectionType();

	// одно из ios, macos, android, windows
	static std::string GetPlatformName();

	// ios - iPad 3 (GSM+CDMA)
	// android - Nexus 5
	// mac - пока просто код Macmini6,2
	// windows - unknown
	static std::string GetModel();

	// ios, mac - Apple
	// android - Asus, Sony и т.д.
	// windows - unknown
	static std::string GetManufacturer();

	// имя, которое задает пользователь, пока только mac и ios, на остальных - unknown
	static std::string GetUserDefinedDeviceName();

	// ios - 8.3.1
	// android - 4.4.2 
	// mac - Version 10.10.3 (Build ABCDE)
	// windows - 8.1.9600
	static std::string GetDeviceOSVersion();

	// ios - iPad, iPod, iPhone
	// android - Phone/Phablet/Tablet
	// windows, mac - Desktop
	static std::string GetDeviceType();

	// размер оперативной памяти в байтах
	static uint64_t GetRamSize();

	// возвращает первый из списка языков устройства
	// не зависит от приложения
	static std::string GetFirstDeviceLang();

	// возвращает двузначный код страны
	//	en;ru не зависит от приложения
	static std::string GetCountryTag();

	// windows - определить реальное значение довольно сложно, возвращается -1
	// mac - рассчитано на базе CGDisplayScreenSize, CGDisplayPixelsWide для основного дисплея
	// ios - список значений для устройств на 05.2015, -1 на симуляторе или новом устройстве
	// android - android.util.DisplayMetrics
	static int GetMainDisplayPpi();
	
	// Проверяет устройство на JailBreak
	static bool isJailbroken();

};


#endif // _ENGINE_DEVICEINFO_H_

/****************************************************************************************************************************
  defines.h

  For RTL8720-based boards using internal RTC with RTL8720DN WiFi

  Built by Khoi Hoang https://github.com/khoih-prog/RTL8720_RTC
  Licensed under MIT license
  Version: 1.0.0

  Version Modified By   Date      Comments
  ------- -----------  ---------- -----------
  1.0.0  K Hoang      10/08/2021 Initial release to support RTL8720-based boards using internal RTC with RTL8720DN WiFi
 *****************************************************************************************************************************/

#ifndef defines_h
#define defines_h

#if !( defined(CONFIG_PLATFORM_8721D) || defined(BOARD_RTL8722D) || defined(BOARD_RTL8722DM_MINI) || defined(BOARD_RTL8720DN_BW16) )
  #error This code is designed to run on RTL8720-based platform! Please check your Tools->Board setting.
#endif

#include <RTL8720_RTC.h>

#include <WiFiWebServer_RTL8720.h>

char ssid[] = "SSID_5GHz";        // your network SSID (name)
char pass[] = "12345678";        // your network password

#endif    //defines_h

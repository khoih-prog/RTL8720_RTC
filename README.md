# RTL8720_RTC Library

[![arduino-library-badge](https://www.ardu-badge.com/badge/RTL8720_RTC.svg?)](https://www.ardu-badge.com/RTL8720_RTC)
[![GitHub release](https://img.shields.io/github/release/khoih-prog/RTL8720_RTC.svg)](https://github.com/khoih-prog/RTL8720_RTC/releases)
[![GitHub](https://img.shields.io/github/license/mashape/apistatus.svg)](https://github.com/khoih-prog/RTL8720_RTC/blob/main/LICENSE)
[![contributions welcome](https://img.shields.io/badge/contributions-welcome-brightgreen.svg?style=flat)](#Contributing)
[![GitHub issues](https://img.shields.io/github/issues/khoih-prog/RTL8720_RTC.svg)](http://github.com/khoih-prog/RTL8720_RTC/issues)

<a href="https://www.buymeacoffee.com/khoihprog6" target="_blank"><img src="https://cdn.buymeacoffee.com/buttons/v2/default-yellow.png" alt="Buy Me A Coffee" style="height: 60px !important;width: 217px !important;" ></a>

---
---

## Table of Contents

* [Why do we need this RTL8720_RTC library](#why-do-we-need-this-rtl8720_rtc-library)
  * [Features](#features)
  * [Why using ISR-based Alarm is better](#why-using-isr-based-alarm-is-better)
  * [Currently supported Boards](#currently-supported-boards)
  * [Important Notes about ISR](#important-notes-about-isr)
* [Changelog](changelog.md)
* [Prerequisites](#prerequisites)
* [Installation](#installation)
  * [Use Arduino Library Manager](#use-arduino-library-manager)
  * [Manual Install](#manual-install)
  * [VS Code & PlatformIO](#vs-code--platformio)
* [Packages' Patches](#packages-patches)
  * [1. For RTL8720DN boards using AmebaD core](#1-for-rtl8720dn-boards-using-amebad-core)
* [Usage](#usage)
  * [1. RTL8720_RTC Class](#1-rtl8720_rtc-class)
    * [1.1 Function List](#11-function-list)
  * [2. TimeSpan and DateTime](#2-timespan-and-datetime)
    * [2.1 Typedef](#21-typedef)
    * [2.2 Function List](#22-function-list)
* [Examples](#examples)
  * [ 1. RTL8720_RTC_Time_WiFi](examples/RTL8720_RTC_Time_WiFi)
* [Example RTL8720_RTC_Time_WiFi](#example-rtl8720_rtc_time_wifi)
  * [ 1. File RTL8720_RTC_Time_WiFi.ino](#1-file-rtl8720_rtc_time_wifiino)
  * [ 2. File defines.h](#2-file-definesh)
* [Debug Terminal Output Samples](#debug-terminal-output-samples)
  * [1. RTL8720_RTC_Time_WiFi on RTL8720DN_BW16](#1-rtl8720_rtc_time_wifi-on-rtl8720dn_bw16)
* [Troubleshooting](#troubleshooting)
* [Issues](#issues)
* [TO DO](#to-do)
* [DONE](#done)
* [Contributions and Thanks](#contributions-and-thanks)
* [Contributing](#contributing)
* [License](#license)
* [Copyright](#copyright)

---
---

### Why do we need this [RTL8720_RTC library](https://github.com/khoih-prog/RTL8720_RTC)

## Features

This is an Arduino library for **RTL8720-based RTC**

The examples will demonstrate how to get the UTC time from NTP server, then update the RTC to make sure the time is perfectly correct.


### Why using ISR-based Alarm is better

Imagine you have a system with a **mission-critical** function, measuring water level and control the sump pump or doing something much more important. You normally use a software timer to poll, or even place the function in loop(). But what if another function is **blocking** the loop() or setup().

So your function **might not be executed, and the result would be disastrous.**

You'd prefer to have your function called, no matter what happening with other functions (busy loop, bug, etc.).

The correct choice is to use an ISR-based Alarm with **Interrupt** to call your function.

These ISR-based Alarm, using interrupt, still work even if other functions are blocking. Moreover, they are much more **precise** (certainly depending on clock frequency accuracy) than other software timers using millis() or micros(). That's necessary if you need to measure some data requiring better accuracy.

Functions using normal software timers, relying on loop() and calling millis(), won't work if the loop() or setup() is blocked by certain operation. For example, certain function is blocking while it's connecting to WiFi or some services.

The catch is **your function is now part of an ISR (Interrupt Service Routine), and must be lean / mean, and follow certain rules.** More to read on:

[**HOWTO Attach Interrupt**](https://www.arduino.cc/reference/en/language/functions/external-interrupts/attachinterrupt/)

---

### Currently supported Boards

1. RTL8720-based boards such as **Realtek RTL8720DN, RTL8722DM and RTL8722CSM**, etc.

---

### Important Notes about ISR

1. Inside the attached function, **delay() won’t work and the value returned by millis() will not increment.** Serial data received while in the function may be lost. You should declare as **volatile any variables that you modify within the attached function.**

2. Typically global variables are used to pass data between an ISR and the main program. To make sure variables shared between an ISR and the main program are updated correctly, declare them as volatile.

3. Don't use Serial.print(ln) function inside ISR or system will hang up.

---
---

## Prerequisites

1. [`Arduino IDE 1.8.19+` for Arduino](https://github.com/arduino/Arduino). [![GitHub release](https://img.shields.io/github/release/arduino/Arduino.svg)](https://github.com/arduino/Arduino/releases/latest)
2. [`Arduino AmebaD core 3.1.2+`](https://github.com/ambiot/ambd_arduino) for Realtek RTL8720DN, RTL8722DM and RTL8722CSM. [![GitHub release](https://img.shields.io/github/release/ambiot/ambd_arduino.svg)](https://github.com/ambiot/ambd_arduino/releases/latest)
3. [`Timezone_Generic library v1.9.1+`](https://github.com/khoih-prog/Timezone_Generic) to use examples using Timezone. To install, check [![arduino-library-badge](https://www.ardu-badge.com/badge/Timezone_Generic.svg?)](https://www.ardu-badge.com/Timezone_Generic)
4. [`WiFiWebServer_RTL8720 library v1.1.1+`](https://github.com/khoih-prog/WiFiWebServer_RTL8720) WiFi to access NTP server. To install. check [![arduino-library-badge](https://www.ardu-badge.com/badge/WiFiWebServer_RTL8720.svg?)](https://www.ardu-badge.com/WiFiWebServer_RTL8720).

---
---

## Installation

### Use Arduino Library Manager

The best and easiest way is to use `Arduino Library Manager`. Search for [**RTL8720_RTC**](https://github.com/khoih-prog/RTL8720_RTC), then select / install the latest version.
You can also use this link [![arduino-library-badge](https://www.ardu-badge.com/badge/RTL8720_RTC.svg?)](https://www.ardu-badge.com/RTL8720_RTC) for more detailed instructions.

### Manual Install

Another way to install is to:

1. Navigate to [**RTL8720_RTC**](https://github.com/khoih-prog/RTL8720_RTC) page.
2. Download the latest release `RTL8720_RTC-main.zip`.
3. Extract the zip file to `RTL8720_RTC-main` directory 
4. Copy whole `RTL8720_RTC-main` folder to Arduino libraries' directory such as `~/Arduino/libraries/`.

### VS Code & PlatformIO

1. Install [VS Code](https://code.visualstudio.com/)
2. Install [PlatformIO](https://platformio.org/platformio-ide)
3. Install [**RTL8720_RTC** library](https://platformio.org/lib/show/12667/RTL8720_RTC) by using [Library Manager](https://platformio.org/lib/show/12667/RTL8720_RTC/installation). Search for **RTL8720_RTC** in [Platform.io Author's Libraries](https://platformio.org/lib/search?query=author:%22Khoi%20Hoang%22)
4. Please visit documentation for the other options and examples at [Project Configuration File](https://docs.platformio.org/page/projectconf.html)


---
---

### Packages' Patches

#### 1. For RTL8720DN boards using AmebaD core
 
 To avoid compile error relating to PROGMEM, you have to copy the file [Realtek AmebaD core pgmspace.h](Packages_Patches/realtek/hardware/AmebaD/3.1.1/cores/arduino/avr/pgmspace.h) into Realtek AmebaD directory (~/.arduino15/packages/realtek/hardware/AmebaD/3.1.1/cores/arduino/avr/pgmspace.h). 

Supposing the Realtek AmebaD core version is 3.1.1. This file must be copied into the directory:

- `~/.arduino15/packages/realtek/hardware/AmebaD/3.1.1/cores/arduino/avr/pgmspace.h`

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz
This file must be copied into the directory:

- `~/.arduino15/packages/realtek/hardware/AmebaD/x.yy.zz/cores/arduino/avr/pgmspace.h`

---
---

## Usage

### 1. RTL8720_RTC Class

### 1.1. Function List

```
void init();
bool free();
void write(time_t t);
time_t read();
void wait(float s);
void setAlarm(alarm_t *alrm, alarm_irq_handler alarmHandler);
void disableAlarm();
void restoreTimeInfo();
void backupTimeInfo();
```

---

### 2. TimeSpan and DateTime

### 2.1. Typedef

```
class TimeSpan;

class DateTime;

/** ISO 8601 Timestamp function */
enum timestampOpt 
{
  TIMESTAMP_FULL, // YYYY-MM-DDTHH:MM:SS
  TIMESTAMP_TIME, // HH:MM:SS
  TIMESTAMP_DATE  // YYYY-MM-DD
};
```

### 2.2. Function List

```
class DateTime
{
  DateTime (uint32_t t = SECONDS_FROM_1970_TO_2000);
  DateTime (const uint16_t year, const uint8_t month, const uint8_t day, const uint8_t hour = 0, const uint8_t min = 0, const uint8_t sec = 0);
  DateTime (const DateTime& copy);
  DateTime (const tmElements_t& tm);

  // To use with RTL8720 datetime_t struct
  DateTime (const datetime_t &tm);

  tmElements_t get_tmElements_t();
  void setFrom_tmElements_t(const tmElements_t& tm);
  time_t get_time_t();
  void setFrom_time_t(const time_t& timeInput);

  uint16_t year() const;
  uint8_t month() const;
  uint8_t day() const;
  uint8_t hour() const;
  uint8_t minute() const;
  uint8_t second() const;
  uint16_t yearOffset() const;
  uint8_t dayOfTheWeek() const;

  /** 32-bit times as seconds since 1/1/2000 */
  long secondstime() const;

  /** 32-bit times as seconds since 1/1/1970 */
  uint32_t unixtime() const;

  /** ISO 8601 Timestamp function */
  String timestamp(timestampOpt opt = TIMESTAMP_FULL)
}

```


---
---

### Examples 

 1. [RTL8720_RTC_Time_WiFi](examples/RTL8720_RTC_Time_WiFi)

---
---

### Example [RTL8720_RTC_Time_WiFi](examples/RTL8720_RTC_Time_WiFi)

#### 1. File [RTL8720_RTC_Time_WiFi.ino](examples/RTL8720_RTC_Time_WiFi/RTL8720_RTC_Time_WiFi.ino)

```
// Important notes: Currently, RTL8720DN-based boards RTC has no battery backup. So the time will be lost when power down
// Therefore, NTP client is necessary to get NTP time and update RTC.

#include "defines.h"

// To be included only in main(), .ino with setup() to avoid `Multiple Definitions` Linker Error
#include <Timezone_Generic.h>             // https://github.com/khoih-prog/Timezone_Generic

//////////////////////////////////////////

// US Eastern Time Zone (New York, Detroit)
TimeChangeRule myDST = {"EDT", Second, Sun, Mar, 2, -240};    //Daylight time = UTC - 4 hours
TimeChangeRule mySTD = {"EST", First, Sun, Nov, 2, -300};     //Standard time = UTC - 5 hours
Timezone *myTZ;

TimeChangeRule *tcr;        //pointer to the time change rule, use to get TZ abbrev

//////////////////////////////////////////

int status = WL_IDLE_STATUS;      // the Wifi radio's status

char timeServer[]         = "time.nist.gov";  // NTP server
unsigned int localPort    = 2390;             // local port to listen for UDP packets

const int NTP_PACKET_SIZE = 48;       // NTP timestamp is in the first 48 bytes of the message
const int UDP_TIMEOUT     = 2000;     // timeout in miliseconds to wait for an UDP packet to arrive

byte packetBuffer[NTP_PACKET_SIZE];   // buffer to hold incoming and outgoing packets

// A UDP instance to let us send and receive packets over UDP
WiFiUDP Udp;

time_t currTime;

char        datetime_buf[256];

RTL8720_RTC   myRTC;

// send an NTP request to the time server at the given address
void sendNTPpacket(char *ntpSrv)
{
  // set all bytes in the buffer to 0
  memset(packetBuffer, 0, NTP_PACKET_SIZE);
  // Initialize values needed to form NTP request
  // (see URL above for details on the packets)

  packetBuffer[0] = 0b11100011;   // LI, Version, Mode
  packetBuffer[1] = 0;     // Stratum, or type of clock
  packetBuffer[2] = 6;     // Polling Interval
  packetBuffer[3] = 0xEC;  // Peer Clock Precision
  // 8 bytes of zero for Root Delay & Root Dispersion
  packetBuffer[12]  = 49;
  packetBuffer[13]  = 0x4E;
  packetBuffer[14]  = 49;
  packetBuffer[15]  = 52;

  // all NTP fields have been given values, now
  // you can send a packet requesting a timestamp:
  Udp.beginPacket(ntpSrv, 123); //NTP requests are to port 123

  Udp.write(packetBuffer, NTP_PACKET_SIZE);

  Udp.endPacket();
}

void getNTPTime()
{
  static bool gotCurrentTime = false;

  // Just get the correct ime once
  if (!gotCurrentTime)
  {
    sendNTPpacket(timeServer); // send an NTP packet to a time server
    // wait to see if a reply is available
    delay(1000);

    if (Udp.parsePacket())
    {
      Serial.println(F("Packet received"));
      // We've received a packet, read the data from it
      Udp.read(packetBuffer, NTP_PACKET_SIZE); // read the packet into the buffer

      //the timestamp starts at byte 40 of the received packet and is four bytes,
      // or two words, long. First, esxtract the two words:

      unsigned long highWord = word(packetBuffer[40], packetBuffer[41]);
      unsigned long lowWord = word(packetBuffer[42], packetBuffer[43]);
      // combine the four bytes (two words) into a long integer
      // this is NTP time (seconds since Jan 1 1900):
      unsigned long secsSince1900 = highWord << 16 | lowWord;
      Serial.print(F("Seconds since Jan 1 1900 = "));
      Serial.println(secsSince1900);

      // now convert NTP time into everyday time:
      Serial.print(F("Unix time = "));
      // Unix time starts on Jan 1 1970. In seconds, that's 2208988800:
      const unsigned long seventyYears = 2208988800UL;
      // subtract seventy years:
      unsigned long epoch = secsSince1900 - seventyYears;

      // print Unix time:
      Serial.println(epoch);
      
      // Get the time_t from epoch
      time_t epoch_t = epoch;

      // set the system time to UTC
      // warning: assumes that compileTime() returns US EDT
      // adjust the following line accordingly if you're in another time zone
      setTime(epoch_t); 

      // Update RTC
      myRTC.write(epoch_t);
     
      // print the hour, minute and second:
      Serial.print(F("The UTC time is "));        // UTC is the time at Greenwich Meridian (GMT)
      Serial.print((epoch  % 86400L) / 3600);     // print the hour (86400 equals secs per day)
      Serial.print(':');

      if (((epoch % 3600) / 60) < 10)
      {
        // In the first 10 minutes of each hour, we'll want a leading '0'
        Serial.print('0');
      }
      
      Serial.print((epoch  % 3600) / 60); // print the minute (3600 equals secs per minute)
      Serial.print(':');

      if ((epoch % 60) < 10)
      {
        // In the first 10 seconds of each minute, we'll want a leading '0'
        Serial.print('0');
      }
      Serial.println(epoch % 60); // print the second

      gotCurrentTime = true;
    }
    else
    {
      // wait ten seconds before asking for the time again
      delay(10000);
    }
  }
}

//////////////////////////////////////////

// format and print a time_t value, with a time zone appended.
void printDateTime(time_t t, const char *tz)
{
  char buf[32];
  char m[4];    // temporary storage for month string (DateStrings.cpp uses shared buffer)
  strcpy(m, monthShortStr(month(t)));
  sprintf(buf, "%2d:%2d:%2d %s %2d %s %d %s",
          hour(t), minute(t), second(t), dayShortStr(weekday(t)), day(t), m, year(t), tz);
  Serial.println(buf);
}

void setup()
{
  Serial.begin(115200);
  while (!Serial);

  delay(200);

  Serial.print(F("\nStart RTL8720_RTC_Time_WiFi on ")); Serial.println(BOARD_NAME);
  Serial.println(RTL8720_RTC_VERSION);
  Serial.println(TIMEZONE_GENERIC_VERSION);

  if (WiFi.status() == WL_NO_SHIELD)
  {
    Serial.println(F("WiFi shield not present"));
    // don't continue
    while (true);
  }

  String fv = WiFi.firmwareVersion();

  Serial.print("Current Firmware Version = "); Serial.println(fv);
  
  if (fv != LATEST_RTL8720_FIRMWARE) 
  {
    Serial.println("Please upgrade the firmware");
  }
 
  // attempt to connect to Wifi network:
  while (status != WL_CONNECTED) 
  {
    Serial.print("Attempting to connect to SSID: "); Serial.println(ssid);
    
    // Connect to WPA/WPA2 network. 2.4G and 5G are all OK
    status = WiFi.begin(ssid, pass);

    // wait 10 seconds for connection:
    delay(10000);
  }
 
  Serial.print(F("TZ_NTP_Clock_RTL8720DN started @ IP address: "));
  Serial.println(WiFi.localIP());

  myTZ = new Timezone(myDST, mySTD);

  // Start the RTC
  myRTC.init();

  Udp.begin(localPort);
}

void displayTime()
{
  currTime = myRTC.read();
    
  // Display time from RTC
  DateTime now = DateTime(currTime);

  time_t utc = now.get_time_t();
  time_t local = myTZ->toLocal(utc, &tcr);

  printDateTime(utc, "UTC");
  printDateTime(local, tcr -> abbrev);
}

void displayRTCTime()
{
  static unsigned long displayRTCTime_timeout = 0;

#define DISPLAY_RTC_INTERVAL     60000L

  // Send status report every STATUS_REPORT_INTERVAL (60) seconds: we don't need to display frequently.
  if ((millis() > displayRTCTime_timeout) || (displayRTCTime_timeout == 0))
  {
    Serial.println("============================");
    displayTime();

    displayRTCTime_timeout = millis() + DISPLAY_RTC_INTERVAL;
  }
}

void loop()
{
  // Get time from NTP once, then update RTC
  // You certainly can make NTP check every hour/day to update RTC to have better accuracy
  getNTPTime();

  displayRTCTime();
}
```

#### 2. File [defines.h](examples/RTL8720_RTC_Time_WiFi/defines.h)

```
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
```

---
---

### Debug Terminal Output Samples

#### 1. RTL8720_RTC_Time_WiFi on RTL8720DN_BW16

The following is the sample terminal output when running example [RTL8720_RTC_Time_WiFi](examples/RTL8720_RTC_Time_WiFi) on RTL8720DN_BW16

```
Start RTL8720_RTC_Time_WiFi on RTL8720DN_BW16
RTL8720_RTC v1.0.1
Timezone_Generic v1.9.0
Current Firmware Version = 1.0.0
Attempting to connect to SSID: HueNet_5G
Attempting to connect to SSID: HueNet_5G
TZ_NTP_Clock_RTL8720DN started @ IP address: 192.168.2.111
Packet received
Seconds since Jan 1 1900 = 3851712462
Unix time = 1642723662
The UTC time is 0:07:42
============================
00:07:43 Fri 21 Jan 2022 UTC
19:07:43 Thu 20 Jan 2022 EST
```

---
---

### Troubleshooting

If you get compilation errors, more often than not, you may need to install a newer version of the core for Arduino boards.

Sometimes, the library will only work if you update the board core to the latest version because I am using newly added functions.


---
---

### Issues

Submit issues to: [RTL8720_RTC issues](https://github.com/khoih-prog/RTL8720_RTC/issues)

---

## TO DO

1. Search for bug and improvement.


---

## DONE

1. Basic RTC-wrapper library for **Realtek RTL8720DN, RTL8722DM and RTL8722CSM**, using [`Arduino AmebaD core`](https://github.com/ambiot/ambd_arduino)
2. Add Version String 
3. Add Table of Contents

---
---

### Contributions and Thanks

Many thanks for everyone for bug reporting, new feature suggesting, testing and contributing to the development of this library.

---

## Contributing

If you want to contribute to this project:

- Report bugs and errors
- Ask for enhancements
- Create issues and pull requests
- Tell other people about this library

---

### License

- The library is licensed under [MIT](https://github.com/khoih-prog/RTL8720_RTC/blob/main/LICENSE)

---

## Copyright

Copyright 2021- Khoi Hoang



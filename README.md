# RTL8720_RTC Library

[![arduino-library-badge](https://www.ardu-badge.com/badge/RTL8720_RTC.svg?)](https://www.ardu-badge.com/RTL8720_RTC)
[![GitHub release](https://img.shields.io/github/release/khoih-prog/RTL8720_RTC.svg)](https://github.com/khoih-prog/RTL8720_RTC/releases)
[![GitHub](https://img.shields.io/github/license/mashape/apistatus.svg)](https://github.com/khoih-prog/RTL8720_RTC/blob/main/LICENSE)
[![contributions welcome](https://img.shields.io/badge/contributions-welcome-brightgreen.svg?style=flat)](#Contributing)
[![GitHub issues](https://img.shields.io/github/issues/khoih-prog/RTL8720_RTC.svg)](http://github.com/khoih-prog/RTL8720_RTC/issues)

<a href="https://www.buymeacoffee.com/khoihprog6" title="Donate to my libraries using BuyMeACoffee"><img src="https://cdn.buymeacoffee.com/buttons/v2/default-yellow.png" alt="Donate to my libraries using BuyMeACoffee" style="height: 50px !important;width: 181px !important;" ></a>
<a href="https://www.buymeacoffee.com/khoihprog6" title="Donate to my libraries using BuyMeACoffee"><img src="https://img.shields.io/badge/buy%20me%20a%20coffee-donate-orange.svg?logo=buy-me-a-coffee&logoColor=FFDD00" style="height: 20px !important;width: 200px !important;" ></a>

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
3. [`Timezone_Generic library v1.10.0+`](https://github.com/khoih-prog/Timezone_Generic) to use examples using Timezone. To install, check [![arduino-library-badge](https://www.ardu-badge.com/badge/Timezone_Generic.svg?)](https://www.ardu-badge.com/Timezone_Generic)
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
3. Install [**RTL8720_RTC** library](https://registry.platformio.org/libraries/khoih-prog/RTL8720_RTC) by using [Library Manager](https://registry.platformio.org/libraries/khoih-prog/RTL8720_RTC/installation). Search for **RTL8720_RTC** in [Platform.io Author's Libraries](https://platformio.org/lib/search?query=author:%22Khoi%20Hoang%22)
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


https://github.com/khoih-prog/RTL8720_RTC/blob/92386b3e49bd8028ce108aac46a3fb13bc87fe3e/examples/RTL8720_RTC_Time_WiFi/RTL8720_RTC_Time_WiFi.ino#L15-L260



#### 2. File [defines.h](examples/RTL8720_RTC_Time_WiFi/defines.h)

https://github.com/khoih-prog/RTL8720_RTC/blob/92386b3e49bd8028ce108aac46a3fb13bc87fe3e/examples/RTL8720_RTC_Time_WiFi/defines.h#L15-L29

---
---

### Debug Terminal Output Samples

#### 1. RTL8720_RTC_Time_WiFi on RTL8720DN_BW16

The following is the sample terminal output when running example [RTL8720_RTC_Time_WiFi](examples/RTL8720_RTC_Time_WiFi) on RTL8720DN_BW16

```
Start RTL8720_RTC_Time_WiFi on RTL8720DN_BW16
RTL8720_RTC v1.0.2
Timezone_Generic v1.10.0
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



/****************************************************************************************************************************
  RTL8720_RTC.h
  For RTL8720-based boards using internal RTC with RTL8720DN WiFi

  Built by Khoi Hoang https://github.com/khoih-prog/RTL8720_RTC
  Licensed under MIT license
  Version: 1.0.0

  Version Modified By   Date      Comments
  ------- -----------  ---------- -----------
  1.0.0  K Hoang      10/08/2021 Initial release to support RTL8720-based boards using internal RTC with RTL8720DN WiFi
*****************************************************************************************************************************/

#pragma once

#ifndef RTL8720_RTC_H
#define RTL8720_RTC_H

#if ( defined(CONFIG_PLATFORM_8721D) || defined(BOARD_RTL8722D) || defined(BOARD_RTL8722DM_MINI) || defined(BOARD_RTL8720DN_BW16) )

  #if defined(BOARD_RTL8722D)
    #define BOARD_NAME      "RTL8722D"
  #elif defined(BOARD_RTL8722DM_MINI)
    #define BOARD_NAME      "RTL8722DM_MINI"
  #elif defined(BOARD_RTL8720DN_BW16)
    #define BOARD_NAME      "RTL8720DN_BW16"
  #endif

#else
  #error This code is designed to run on RTL8720-based platform! Please check your Tools->Board setting.
#endif

#define RTL8720_RTC_VERSION      "RTL8720_RTC v1.0.0"

#include <Arduino.h>

#include "rtc_api.h"
#include "timer_api.h"

#ifdef __cplusplus
  extern "C" {
#endif

  /*static*/ void rtc_restore_timeinfo(void);
  void rtc_backup_timeinfo(void);
  
#ifdef __cplusplus
  }
#endif

class RTL8720_RTC
{
  public:

    RTL8720_RTC() {};
    ~RTL8720_RTC() {};

    /**
        @brief  Initializes the RTC device, include clock, RTC registers and function.
        @param  none
        @retval  none
    */
    void init() 
    {
      rtc_init();
    }

    /**
        @brief  Deinitializes the RTC device.
        @param  none
        @retval  none
    */
    void free() 
    {
      rtc_free();
    }

    /**
        @brief  Set the specified timestamp in seconds to RTC.
        @param  t: Seconds from 1970.1.1 00:00:00 to specified data and time
                     which is to be set.
        @retval  none
    */
    void write(time_t t)
    {
      rtc_write( (time_t) t);  
    }

    /**
        @brief  Get current timestamp in seconds from RTC.
        @param  none
        @retval value: The current timestamp in seconds which is calculated from 1970.1.1 00:00:00.
    */
    time_t read()
    {
      return (rtc_read());
    }

    /**
        @brief  Wait for 1000000 us / 1s.
    */
    void wait(float s) 
    {
      DelayUs((int)(s * 1000000.0f));
    }

    /**
      * @brief  Set the specified RTC Alarm and interrupt.
      * @param  alarm: alarm object define in application software.
      * @param  alarmHandler:  alarm interrupt callback function.
      * @retval   status:
      */
      
    void setAlarm(alarm_t *alrm, alarm_irq_handler alarmHandler)
    {
	    rtc_set_alarm(alrm, alarmHandler);
    }  

    /**
      * @brief  Disable RTC Alarm and function.
      * @param  none
      * @retval   none
      */
    void disableAlarm()
    {
	    rtc_disable_alarm();
    }

    /**
      * @brief  This function is used to restore rtc_timeinfo global variable whose value is lost after system reset.
      * @param  none
      * @retval value: none
      */    
    void restoreTimeInfo()
    {
      rtc_restore_timeinfo();
    }
    
    /**
      * @brief  This function is used to backup tm_year parameter in rtc_timeinfo global variable before system reset.
      * @param  none
      * @retval value: none
      */
    void backupTimeInfo()
    {
	    rtc_backup_timeinfo();
    }

  private:
  

};

#include "DateTime_Generic.h"

#endif    // RTL8720_RTC_H

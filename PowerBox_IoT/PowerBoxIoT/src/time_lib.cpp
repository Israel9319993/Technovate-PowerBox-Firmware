#include "time_lib.h"

Time::Time() {}
void Time::Begin()
{
    sntp_set_time_sync_notification_cb(Time::TimeAvailable);
    sntp_servermode_dhcp(1); // (optional)
    configTime(gmtOffset_sec, daylightOffset_sec, ntpServer1, ntpServer2);
    configTzTime(time_zone, ntpServer1, ntpServer2);
}

void Time::TimeAvailable(struct timeval *t)
{
    Serial.println("Got time adjustment from NTP!");
    PrintLocalTime();
}

void Time::PrintLocalTime()
{
    struct tm timeinfo;
    if (!getLocalTime(&timeinfo))
    {
        Serial.println("No time available (yet)");
        return;
    }

    else
    {
        Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");
        strftime(timeHour, 3, "%H", &timeinfo);
        strftime(timeMinute, 3, "%M", &timeinfo);
        strftime(timeSecond, 3, "%S", &timeinfo);
        strftime(timeDay, 3, "%d", &timeinfo);
        strftime(timeMonth, 3, "%m", &timeinfo);
        strftime(timeYear, 5, "%Y", &timeinfo);
        strftime(timeWeek,4, "%A", &timeinfo);

        // // if ((hours != atoi(serverHour)) && (minutes != atoi(serverMinute)) && (sec != atoi(serverSecond)) && !timeCheck)
        // //         {
        //             RtcDateTime compiled = RtcDateTime(atoi(serverYear), atoi(serverMonth), atoi(serverDay), atoi(serverHour), atoi(serverMinute), atoi(serverSecond));
        //             Rtc.SetDateTime(compiled);

        //             // serverTime.PrintLocalTime();
        //             glcd.Notification("Device Time Updated", "update");
        //             timeCheck = true;
        //         // }
    }
}

void Time::ReadTime()
{
    PrintLocalTime();
    // RtcDateTime dt = Rtc.GetDateTime();
      const char* m[12] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
    const char* w[7] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
    years = atoi(timeYear);
    months = atoi(timeMonth);
    days = atoi(timeDay);
    hours = atoi(timeHour);
    hour24 = atoi(timeHour);
    minutes = atoi(timeMinute);
    sec = atoi(timeSecond);

    hourChar[0] = (hours / 10) % 10 + 48;
    hourChar[1] = hours % 10 + 48;
    minuteChar[0] = (minutes / 10) % 10 + 48;
    minuteChar[1] = minutes % 10 + 48;

    if (hour24 > 12)
    {
        hours = hour24 - 12;
        strcpy(dayTime, "pm");
    }
    else if (hour24 == 0)
    {
        hours = 12;
        strcpy(dayTime, "am");
    }
    else
    {
        hours = hour24;
        strcpy(dayTime, "am");
    }

    snprintf(timeOut, sizeof(timeOut), "%02d:%02d %s", hours, minutes, dayTime);
}

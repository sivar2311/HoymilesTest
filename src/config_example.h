// rename config-example.h to config.h and put in serial numbers / wifi credentials / ntp-server and time-zone
#pragma once

uint64_t    inv_serial = 0x001122334455UL;
uint64_t    dtu_serial = 0x99978563412UL;
const char* WIFI_SSID  = "your-wifi-ssid";
const char* WIFI_PASS  = "your-wifi-pass";
const char* NTP_SERVER = "pool.ntp.org";
const char* TIME_ZONE  = "CET-1CEST,M3.5.0,M10.5.0/3";
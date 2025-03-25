#ifndef DEFINITION_H
#define DEFINITION_H
#ifdef LOG_TAG
#undef LOG_TAG
#endif
#define LOG_TAG "SYSTEM_LOGS"

#include <log/log.h>
#include <vector>
#include <cstring>
#include <fstream>
#include <string>
#include <android/log.h>
#include <sys/system_properties.h>
#include <cutils/properties.h>
#include <sys/stat.h>   // For mkdir() and struct stat
#include <sys/types.h>  // For mkdir() on some platforms
#include <stdio.h>
#include <stdlib.h>
#include <sstream> 
#include <unistd.h>
#include <thread>
#include <iostream>
#include <unordered_map>
#include <mutex>
#include <ctime>
#define MAX_LOG_LINES 100000            // Max lines before overwriting
#define MAX_LOG_LINES_2FILES 100000
std::mutex logMutex;
using namespace std;
// Log file paths
const std::string BLUETOOTH_LOG_FILE = "/data/local/tmp/bluetooth_logs.txt";
const std::string WIFI_LOG_FILE = "/data/local/tmp/wifi_logs.txt";
const std::string LTE_LOG_FILE = "/data/local/tmp/lte_logs.txt";
const std::string DISPLAY_LOG_FILE = "/data/local/tmp/display_logs.txt";
const std::string GPS_LOG_FILE = "/data/local/tmp/gps_logs.txt";
const std::string TOUCH_LOG_FILE = "/data/local/tmp/touch_logs.txt";
const std::string DMESG_LOG_FILE = "/data/local/tmp/dmesg_logs.txt";
const std::string CRASH_LOG_FILE = "/data/local/tmp/crash_logs.txt";
const std::string ERROR_LOG_FILE = "/data/local/tmp/error.txt";
const std::string DEBUG_LOG_FILE = "/data/local/tmp/debug.txt";

const std::string ARCHIVE_DIR = "./";
const int TIME_WINDOW = 15 * 60; // 15 minutes in seconds

// Log macros for Logcat
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

// Function to convert string to lowercase
std::string toLowerCase(const std::string &str) {
    std::string lowerStr = str;
    std::transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), ::tolower);
    return lowerStr;
}

// Generic function to check for keywords (case insensitive)
bool containsKeyword(const std::string &line, const std::vector<std::string> &keywords) {
    std::string lowerLine = toLowerCase(line);
    for (const std::string &keyword : keywords) {
        if (lowerLine.find(keyword) != std::string::npos) {
            return true;
        }
    }
    return false;
}

bool isWiFiLog(const std::string &line) { 
    return containsKeyword(line, {"wifi", "wlan", "supplicant", "hostapd", "dhcp", "p2p", "iwlan", "wificond", "netd", 
                                  "802.11", "scan", "rssi", "networkinfo", "wifi_state", "wpa_supplicant", 
                                  "wifi_native", "wifi_hal", "ssid", "bssid", "auth", "eap", "roam", "handover", 
                                  "assoc", "link speed", 
                                  "wifi connectivity", "wifi status", "wifi event", "wifi monitor"}); 
}

bool isBluetoothLog(const std::string &line) { 
    return containsKeyword(line, {"bluetooth", "bt", "hci", "gatt", "a2dp", "avrcp", "hfp", "hid", "smp", "l2cap", 
                                  "rfcomm", "ble", "br/edr", "sco", "bluetooth_adapter", "btif", "bt_stack"}); 
}

bool isLTELog(const std::string &line) { 
    return containsKeyword(line, {"lte", "4g", "5g", "cellular", "mobile data", "rrc", "nr", "signal strength", 
                                  "network type", "ims", "volte", "handover", "data call", "nas", "radio", "qcril", 
                                  "modem", "ril", "telephony", "carrier", "rat", "srn", "gsm", "cdma", "umts", 
                                  "tdd", "fdd", "dss"}); 
}

bool isDisplayLog(const std::string &line) { 
    return containsKeyword(line, {"display", "brightness", "hwc", "vsync", "framebuffer", "panel", "surfaceflinger", 
                                  "overlay", "composer", "mipi", "dsi", "dpi", "oled", "lcd", "screen", "gamma", 
                                  "hdr", "refresh_rate", "color_mode", "dimming", "bl_level", "brightness_mode"}); 
}

bool isTouchLog(const std::string &line) { 
    return containsKeyword(line, {"touch", "1c40000", "atmel_mxt_ts", "input", "multitouch", "gesture", "tap", 
                                  "swipe", "touchscreen", "fingerprint", "stylus", "keyevent", "motion_event", 
                                  "haptics", "force touch", "touch driver", "hid_event", "inputflinger"}); 
}

bool isGpsLog(const std::string &line) { 
    return containsKeyword(line, {"locsvc_gnssapiclient", "gps", "latitude", "longitude", "altitude", "gprmc", 
                                  "gpgga", "gpgsv", "gpgsa", "nmea", "fix", "sbas", "glonass", "galileo", "beidou", 
                                  "ttff", "locationprovider", "geofence", "ephemeris", "agps", "l5", "carrier_phase", 
                                  "dop", "hdop", "vdop", "accuracy", "navigation"}); 
}




std::vector<std::string> readLogLines(const std::string &filePath)
{
    std::ifstream file(filePath);
    std::vector<std::string> lines;
    std::string line;
    while (std::getline(file, line))
    {
        lines.push_back(line);
    }
    return lines;
}

// Function to check if a file is non-empty
bool isNonEmptyFile(const std::string &filename)
{
    struct stat fileStat;
    return (stat(filename.c_str(), &fileStat) == 0 && fileStat.st_size > 0);
}

// Function to build the tar command dynamically
std::string getTarCommand()
{
    std::vector<std::string> logFiles = {
        "bluetooth_logs.txt",
        "display_logs.txt",
        "gps_logs.txt",
        "lte_logs.txt",
        "touch_logs.txt",
        "crash_logs.txt",
        "error.txt",
        "debug.txt",
        "dmesg_logs.txt",
        "wifi_logs.txt"};

    std::string basePath = "/data/local/tmp/";
    std::string tarCommand = "tar -czf " + basePath + "logs.tar.gz -C " + basePath;
    bool hasFiles = false;

    for (const auto &file : logFiles)
    {
        std::string fullPath = basePath + file;
        if (isNonEmptyFile(fullPath))
        {
            tarCommand += " " + file;
            hasFiles = true;
        }
    }

    return hasFiles ? tarCommand : ""; // Return empty string if no files are non-empty
}


time_t getLastModifiedTime(const std::string &filename) {
    struct stat fileStat;
    if (stat(filename.c_str(), &fileStat) == 0) {
        return fileStat.st_mtime; // Last modified time
    }
    return 0; // File doesn't exist or error
}

#endif // DEFINITION_H

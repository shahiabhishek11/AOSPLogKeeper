#include "Diagnostics.h"
#include <log/log.h>
#include <termios.h> 
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
#include <string.h>
#include <sstream> 
#include <unistd.h>
#include <thread>
#include <chrono>
#include <iostream>
#include <unordered_map>
#include <mutex>

using namespace std;

#define LOG_TAG "LOG_FILTER"
#define MAX_LOG_LINES 100000            // Max lines before overwriting
#define MAX_LOG_LINES_2FILES 100000
std::mutex logMutex;

// Log file paths
const std::string BLUETOOTH_LOG_FILE = "/data/local/tmp/bluetooth_logs.txt";
const std::string WIFI_LOG_FILE = "/data/local/tmp/wifi_logs.txt";
const std::string LTE_LOG_FILE = "/data/local/tmp/lte_logs.txt";

const std::string DISPLAY_LOG_FILE = "/data/local/tmp/display_logs.txt";
const std::string GPS_LOG_FILE = "/data/local/tmp/gps_logs.txt";
const std::string TOUCH_LOG_FILE = "/data/local/tmp/touch_logs.txt";

const std::string DMESG_LOG_FILE_1 = "/data/local/tmp/dmesg_logs_1.txt";
const std::string DMESG_LOG_FILE_2 = "/data/local/tmp/dmesg_logs_2.txt";

const std::string CRASH_LOG_FILE_1 = "/data/local/tmp/crash_logs_1.txt";
const std::string CRASH_LOG_FILE_2 = "/data/local/tmp/crash_logs_2.txt";

const std::string ERROR_LOG_FILE = "/data/local/tmp/error.txt";
const std::string INFO_LOG_FILE = "/data/local/tmp/info.txt";
const std::string DEBUG_LOG_FILE = "/data/local/tmp/debug.txt";
const std::string WARNING_LOG_FILE = "/data/local/tmp/warning.txt";
const std::string VERBOSE_LOG_FILE = "/data/local/tmp/verbose.txt";

// Log macros for Logcat
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS4__)
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)



// Constructor
Diagnostic::Diagnostic() {
    ALOGD("%s: constructor diagnostics ", __func__);
    // Initialize members if needed
}

// Destructor
Diagnostic::~Diagnostic() {
     ALOGD("%s: destructor diagnostics ", __func__);
    // Clean up resources if needed
}
// Read log file into a vector of lines
std::vector<std::string> readLogLines(const std::string &filePath) {
    std::ifstream file(filePath);
    std::vector<std::string> lines;
    std::string line;
    while (std::getline(file, line)) {
        lines.push_back(line);
    }
    return lines;
}

// Function to check if a file is non-empty
bool isNonEmptyFile(const std::string &filename) {
    struct stat fileStat;
    return (stat(filename.c_str(), &fileStat) == 0 && fileStat.st_size > 0);
}

// Function to build the tar command dynamically
std::string getTarCommand() {
    std::vector<std::string> logFiles = {
        "bluetooth_logs.txt",
        "display_logs.txt",
        "gps_logs.txt",
        "lte_logs.txt",
        "touch_logs.txt",
        "crash_logs_1.txt",
        "crash_logs_2.txt",
        "wifi_logs.txt"
    };

    std::string basePath = "/data/local/tmp/";
    std::string tarCommand = "tar -czf " + basePath + "logs.tar.gz -C " + basePath;
    bool hasFiles = false;

    for (const auto &file : logFiles) {
        std::string fullPath = basePath + file;
        if (isNonEmptyFile(fullPath)) {
            tarCommand += " " + file;
            hasFiles = true;
        }
    }

    return hasFiles ? tarCommand : "";  // Return empty string if no files are non-empty
}


void writeCircularLog(const std::string &file1, const std::string &file2, const std::string &logLine) {
    static std::unordered_map<std::string, bool> useFirstFile = {
        {CRASH_LOG_FILE_1, true}, {DMESG_LOG_FILE_1, true}
    };
    static std::unordered_map<std::string, size_t> lineCount = {
        {CRASH_LOG_FILE_1, 0}, {DMESG_LOG_FILE_1, 0}
    };

    // Determine which file to write to
    std::string activeFile = useFirstFile[file1] ? file1 : file2;
    
    // Read existing lines
    std::vector<std::string> lines = readLogLines(activeFile);
    
    // Append new log line
    lines.push_back(logLine);
    lineCount[file1]++;

    // If max lines reached
    if (lineCount[file1] >= MAX_LOG_LINES_2FILES) {
        useFirstFile[file1] = !useFirstFile[file1]; 
        activeFile = useFirstFile[file1] ? file1 : file2;
        lineCount[file1] = 0; 
    }

    // Rewrite the file with updated log content
    std::ofstream logFile(activeFile, std::ios::out | std::ios::trunc);
    if (!logFile.is_open()) {
        std::cerr << "Error: Cannot open log file " << activeFile << std::endl;
        return;
    }

    for (const std::string &line : lines) {
        logFile << line << "\n";
    }

    logFile.flush();
    logFile.close();
}

size_t getFileSize(const std::string &filePath) {
    struct stat fileStat;
    return (stat(filePath.c_str(), &fileStat) == 0) ? fileStat.st_size : 0;
}

void writeCircularLog(const std::string &filePath, const std::string &logLine) {
    std::lock_guard<std::mutex> lock(logMutex);  // Ensure thread safety

    std::deque<std::string> lines;
    std::ifstream inFile(filePath);
    std::string line;
    // Read existing log lines into a deque
    while (std::getline(inFile, line)) {
        lines.push_back(line);
    }
    inFile.close(); // Close the file after reading

    // Append the new log line
    lines.push_back(logLine);

    // Maintain circular buffer size by removing the oldest entry
    while (lines.size() > MAX_LOG_LINES) {
        lines.pop_front();
    }

    // Write the updated log back to the file
    std::ofstream outFile(filePath, std::ios::out | std::ios::trunc);
    if (!outFile.is_open()) {
        std::cerr << "Error: Cannot open log file " << filePath << std::endl;
        return;
    }

    for (const auto &entry : lines) {
        outFile << entry << "\n";
    }
    outFile.close(); // No need to flush before closing
}
// Convert a string to lowercase (for case-insensitive searching)
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
                                  "pointer", "haptics", "force touch", "touch driver", "hid_event", "inputflinger"}); 
}

bool isGpsLog(const std::string &line) { 
    return containsKeyword(line, {"locsvc_gnssapiclient", "gps", "latitude", "longitude", "altitude", "gprmc", 
                                  "gpgga", "gpgsv", "gpgsa", "nmea", "fix", "sbas", "glonass", "galileo", "beidou", 
                                  "ttff", "locationprovider", "geofence", "ephemeris", "agps", "l5", "carrier_phase", 
                                  "dop", "hdop", "vdop", "accuracy", "navigation"}); 
}
// Function to set correct file permissions
void setFilePermissions(const std::string &filePath) {
    if (access(filePath.c_str(), F_OK) != 0) {
        ALOGD("%s: Creating file: %s", __func__, filePath.c_str());
        std::ofstream file(filePath);  // Create the file if it doesn't exist
        if (!file) {
            ALOGE("%s: Failed to create file: %s", __func__, filePath.c_str());
            return;
        }
        file.close();
    }

    // Change file permissions
    if (chmod(filePath.c_str(), 0666) != 0) { // Use 0666 instead of 0777 for security
        ALOGE("%s: Failed to set permissions on %s", __func__, filePath.c_str());
    } else {
        ALOGD("%s: Set permissions to 666 on %s", __func__, filePath.c_str());
    }
    //Change ownership to root:shell (useful for ADB access)
    system(("chown root:shell " + filePath).c_str());
}

// Function to process logs with circular buffer
void processLog(const string &logLine) {
    if (logLine.find(" E/") != string::npos) {  // Error logs
        writeCircularLog(ERROR_LOG_FILE, logLine);
    } else if (logLine.find(" I/") != string::npos) {  // Info logs
        writeCircularLog(INFO_LOG_FILE, logLine);
    } else if (logLine.find(" D/") != string::npos) {  // Debug logs
        writeCircularLog(DEBUG_LOG_FILE, logLine);
    } else if (logLine.find(" W/") != string::npos) {  // Warning logs
        writeCircularLog(WARNING_LOG_FILE, logLine);
    }else if (logLine.find(" V/") != string::npos) {  // verbose logs
        writeCircularLog(VERBOSE_LOG_FILE, logLine);
    }
}
// Compress logs into tar.gz every 60 seconds
void compressLogs() {
    while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(60));  // Run every 60 sec
        std::lock_guard<std::mutex> lock(logMutex);  // Prevent race conditions

        std::string tarCommand = getTarCommand();
        if (tarCommand.empty()) {
            std::cout << "No non-empty logs to compress. Skipping..." << std::endl;
            continue;
        }

        int result = system(tarCommand.c_str());
        if (result != 0) {
            std::cerr << "Error: Failed to create TAR file! (Exit Code: " << result << ")" << std::endl;
        } else {
            std::cout << "Logs compressed successfully: /data/local/tmp/logs.tar.gz" << std::endl;
            system("chmod 666 /data/local/tmp/logs.tar.gz");
            system("chown root:shell /data/local/tmp/logs.tar.gz");
            std::cout << "Permissions set: logs.tar.gz (chmod 666, chown root:shell)" << std::endl;
        }
    }
}

void captureCrashLogs() {
    FILE *crashLogStream = popen("/system/bin/logcat -b crash -d 2>&1", "r");

    if (!crashLogStream) {
        std::cerr << "Error: Failed to capture crash logs!" << std::endl;
        return;  // Avoid infinite retries on failure
    }

    char buffer[4096];
    while(true){
    if (fgets(buffer, sizeof(buffer), crashLogStream)) {
        std::string logLine(buffer);
        writeCircularLog(CRASH_LOG_FILE_1, CRASH_LOG_FILE_2, logLine);
        }
    }

    pclose(crashLogStream);
}
#if 0
// Capture and store dmesg logs
void captureDmesgLogs() {
    while (true) {
        FILE *dmesgLogStream = popen("dmesg", "r");
        if (dmesgLogStream) {
            char buffer[4096];
            while (fgets(buffer, sizeof(buffer), dmesgLogStream)) {
                writeCircularLog(DMESG_LOG_FILE_1, DMESG_LOG_FILE_2, buffer);
            }
            pclose(dmesgLogStream);
        } else {
            std::cerr << "Error: Failed to capture dmesg logs!" << std::endl;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}
#endif


// Function to capture logs for a specific category
void captureLogs(const std::string &logFilePath, bool (*filterFunc)(const std::string &)) {
    FILE *logStream = popen("/system/bin/logcat -v time 2>&1", "r");

    if (!logStream) {
        std::cerr << "Error: Failed to open logcat stream for " << logFilePath << std::endl;
        return;
    }

    char buffer[4092];

    while (true) {
        if (fgets(buffer, sizeof(buffer), logStream)) {
            std::string logLine(buffer);
            if (filterFunc(logLine)) {
                writeCircularLog(logFilePath, logLine);
            }
        }
    }

    pclose(logStream);
}

void captureAndProcessLogs() {
    FILE *logStream = popen("/system/bin/logcat -v time 2>&1", "r");

    if (!logStream) {
        std::cerr << "Error: Failed to open logcat stream for processing logs." << std::endl;
        return;
    }

    char buffer[4092];

    while (true) {
        if (fgets(buffer, sizeof(buffer), logStream)) {
            std::string logLine(buffer);
            std::lock_guard<std::mutex> lock(logMutex);  
            processLog(logLine);
        }
    }

    pclose(logStream);
}
// Implementation of the onRequest method
bool Diagnostic::onRequest() {
     ALOGD("%s: Diagnostic::onRequest called: ", __func__);

    // Set file permissions before opening
    setFilePermissions(BLUETOOTH_LOG_FILE);
    setFilePermissions(WIFI_LOG_FILE);
    setFilePermissions(LTE_LOG_FILE);
    setFilePermissions(DISPLAY_LOG_FILE);
    setFilePermissions(TOUCH_LOG_FILE);
    setFilePermissions(GPS_LOG_FILE);
    setFilePermissions(CRASH_LOG_FILE_1);
    setFilePermissions(CRASH_LOG_FILE_2);
#if 0
    
    setFilePermissions(DMESG_LOG_FILE_1);
    setFilePermissions(DMESG_LOG_FILE_2);
    setFilePermissions(ERROR_LOG_FILE);
    setFilePermissions(INFO_LOG_FILE); 
    setFilePermissions(DEBUG_LOG_FILE);
    setFilePermissions(WARNING_LOG_FILE);
    setFilePermissions(VERBOSE_LOG_FILE);

    // Check if running as root
    if (getuid() != 0) {
        ALOGE("%s: Not running as root, attempting to restart with su", __func__);
        execlp("su", "su", "-c", "/data/local/tmp/log_filter", nullptr);
        ALOGE("%s: Failed to restart with su!", __func__);
        return 1;
    }

    ALOGD("%s: Running as root", __func__);
#endif
    // Ensure /data/local/tmp exists and is writable
    if (access("/data/local/tmp", W_OK) != 0) {
        ALOGE("%s: No write access to /data/local/tmp!", __func__);
        return 1;
    }
    // Print initial file sizes
    size_t btSize = getFileSize(BLUETOOTH_LOG_FILE);
    size_t wifiSize = getFileSize(WIFI_LOG_FILE);
    size_t lteSize = getFileSize(LTE_LOG_FILE);
    size_t DisplaySize = getFileSize(DISPLAY_LOG_FILE);
    size_t TouchSize = getFileSize(TOUCH_LOG_FILE);
    size_t GpsSize = getFileSize(GPS_LOG_FILE);
    size_t crash1Size = getFileSize(CRASH_LOG_FILE_1);
    size_t crash2Size = getFileSize(CRASH_LOG_FILE_2);
#if 0   
    
    size_t dmesg1Size = getFileSize(DMESG_LOG_FILE_1);
    size_t dmesg2Size = getFileSize(DMESG_LOG_FILE_2);
    size_t errorSize = getFileSize(ERROR_LOG_FILE);
    size_t infoSize = getFileSize(INFO_LOG_FILE);
    size_t debugSize = getFileSize(DEBUG_LOG_FILE);
    size_t warningSize = getFileSize(WARNING_LOG_FILE);
    size_t verboseSize = getFileSize(VERBOSE_LOG_FILE);
#endif
    ALOGD("Log File Sizes at Startup:");
    ALOGD("  Bluetooth Log: %zu bytes (%.2f MB)", btSize, btSize / (1024.0 * 1024));
    ALOGD("  WiFi Log: %zu bytes (%.2f MB)", wifiSize, wifiSize / (1024.0 * 1024));
    ALOGD("  LTE Log: %zu bytes (%.2f MB)", lteSize, lteSize / (1024.0 * 1024));
    ALOGD("  DISPLAY Log: %zu bytes (%.2f MB)", DisplaySize, DisplaySize / (1024.0 * 1024));
    ALOGD("  TOUCH Log: %zu bytes (%.2f MB)", TouchSize, TouchSize / (1024.0 * 1024));
    ALOGD("  GPS Log: %zu bytes (%.2f MB)", GpsSize, GpsSize / (1024.0 * 1024));
    ALOGD("  crash1 Log: %zu bytes (%.2f MB)", crash1Size, crash1Size / (1024.0 * 1024));
    ALOGD("  crash2 Log: %zu bytes (%.2f MB)", crash2Size, crash2Size / (1024.0 * 1024));
#if 0    
    
    ALOGD("  dmesg1 Log: %zu bytes (%.2f MB)", dmesg1Size, dmesg1Size / (1024.0 * 1024));
    ALOGD("  dmesg2 Log: %zu bytes (%.2f MB)", dmesg2Size, dmesg2Size / (1024.0 * 1024));
    ALOGD("  error Log: %zu bytes (%.2f MB)", errorSize, errorSize / (1024.0 * 1024));
    ALOGD("  info Log: %zu bytes (%.2f MB)", infoSize, infoSize / (1024.0 * 1024));
    ALOGD("  debug Log: %zu bytes (%.2f MB)", debugSize, debugSize / (1024.0 * 1024));
    ALOGD("  warning Log: %zu bytes (%.2f MB)", warningSize, warningSize / (1024.0 * 1024));
    ALOGD("  verbose Log: %zu bytes (%.2f MB)", verboseSize, verboseSize / (1024.0 * 1024));
#endif
   
//#if 1
    // Open log files
    std::ofstream btLogFile(BLUETOOTH_LOG_FILE, std::ios::out | std::ios::app);
    std::ofstream wifiLogFile(WIFI_LOG_FILE, std::ios::out | std::ios::app);
    std::ofstream lteLogFile(LTE_LOG_FILE, std::ios::out | std::ios::app);
    std::ofstream displayLogFile(DISPLAY_LOG_FILE, std::ios::out | std::ios::app);
    std::ofstream touchLogFile(TOUCH_LOG_FILE, std::ios::out | std::ios::app);
    std::ofstream gpsLogFile(GPS_LOG_FILE, std::ios::out | std::ios::app);
    std::ofstream crash1LogFile(CRASH_LOG_FILE_1, std::ios::out | std::ios::app);
    std::ofstream crash2LogFile(CRASH_LOG_FILE_2, std::ios::out | std::ios::app);
#if 0
    
    std::ofstream dmesgLogFile1(DMESG_LOG_FILE_1, std::ios::out | std::ios::app);
    std::ofstream dmesgLogFile2(DMESG_LOG_FILE_2, std::ios::out | std::ios::app);
    std::ofstream errorLogFile(ERROR_LOG_FILE, std::ios::out | std::ios::app);
    std::ofstream infoLogFile(INFO_LOG_FILE, std::ios::out | std::ios::app);
    std::ofstream debugLogFile(DEBUG_LOG_FILE, std::ios::out | std::ios::app);
    std::ofstream warnigLogFile(WARNING_LOG_FILE, std::ios::out | std::ios::app);
    std::ofstream verboseLogFile(VERBOSE_LOG_FILE, std::ios::out | std::ios::app);
#endif

    if (!btLogFile.is_open()) {
        ALOGE("%s: Failed to open Bluetooth log file!", __func__);
        return 1;
    }
    if (!wifiLogFile.is_open()) {
        ALOGE("%s: Failed to open WiFi log file!", __func__);
        return 1;
    }
    if (!lteLogFile.is_open()) {
        ALOGE("%s: Failed to open lte log file!", __func__);
        return 1;
    }
    if (!displayLogFile.is_open()) {
        ALOGE("%s: Failed to open display log file!", __func__);
        return 1;
    }
    if (!touchLogFile.is_open()) {
        ALOGE("%s: Failed to open touch log file!", __func__);
        return 1;
    }
    if (!gpsLogFile.is_open()) {
        ALOGE("%s: Failed to open gps log file!", __func__);
        return 1;
    }
    if (!crash1LogFile.is_open()) {
        ALOGE("%s: Failed to open crash1 log file!", __func__);
        return 1;
    }
    if (!crash2LogFile.is_open()) {
        ALOGE("%s: Failed to open crash2 log file!", __func__);
        return 1;
    }
#if 0
    
    if (!dmesgLogFile1.is_open()) {
        ALOGE("%s: Failed to open dmesg1 log file!", __func__);
        return 1;
    }
    if (!dmesgLogFile2.is_open()) {
        ALOGE("%s: Failed to open dmesg2 log file!", __func__);
        return 1;
    }
    if (!errorLogFile.is_open()) {
        ALOGE("%s: Failed to open error log file!", __func__);
        return 1;
    }
    if (!infoLogFile.is_open()) {
        ALOGE("%s: Failed to open info log file!", __func__);
        return 1;
    }
    if (!debugLogFile.is_open()) {
        ALOGE("%s: Failed to open debug log file!", __func__);
        return 1;
    }
    if (!warnigLogFile.is_open()) {
        ALOGE("%s: Failed to open warning log file!", __func__);
        return 1;
    }
    if (!verboseLogFile.is_open()) {
        ALOGE("%s: Failed to open verbose log file!", __func__);
        return 1;
    }
#endif



    ALOGD("%s: Starting log capture threads...", __func__);

    std::thread bluetoothLogThread(captureLogs, BLUETOOTH_LOG_FILE, isBluetoothLog);
    std::thread wifiLogThread(captureLogs, WIFI_LOG_FILE, isWiFiLog);
    std::thread lteLogThread(captureLogs, LTE_LOG_FILE, isLTELog);
    std::thread displayLogThread(captureLogs, DISPLAY_LOG_FILE, isDisplayLog);
    std::thread touchLogThread(captureLogs, TOUCH_LOG_FILE, isTouchLog);
    std::thread gpsLogThread(captureLogs, GPS_LOG_FILE, isGpsLog);

    //std::thread processLogThread(captureAndProcessLogs);
    std::thread crashLogThread(captureCrashLogs);
    //std::thread dmesgLogThread(captureDmesgLogs);
    std::thread compressionThread(compressLogs);

    ALOGD("%s: Threads started. Waiting for logs...", __func__);


#if 0
    FILE *logStream = popen("/system/bin/logcat -v time 2>&1", "r");

    if (!logStream) {
        ALOGE("%s: Failed to open logcat stream!", __func__);
        return 1;
    }

    char buffer[4092];

    while (true) {  // Infinite loop to continuously save logs
        if (fgets(buffer, sizeof(buffer), logStream)) {
            std::string logLine(buffer);

           // ALOGD("%s: Received log: %s", __func__, logLine.c_str());  // Debugging
           
            if (isBluetoothLog(logLine)) writeCircularLog(BLUETOOTH_LOG_FILE, logLine);
            if (isWiFiLog(logLine)) writeCircularLog(WIFI_LOG_FILE, logLine);
            if (isLTELog(logLine)) writeCircularLog(LTE_LOG_FILE, logLine);
            if (isDisplayLog(logLine)) writeCircularLog(DISPLAY_LOG_FILE, logLine);
            if (isTouchLog(logLine)) writeCircularLog(TOUCH_LOG_FILE, logLine);
            if (isGpsLog(logLine)) writeCircularLog(GPS_LOG_FILE, logLine);
            //processLog(logLine);
        }
    }

   // pclose(logStream);
#endif
    // Keep the main thread alive while the logging threads run
    bluetoothLogThread.join();
    wifiLogThread.join();
    lteLogThread.join();
    displayLogThread.join();
    touchLogThread.join();
    gpsLogThread.join();
    //processLogThread.join();
    crashLogThread.join();
    //dmesgLogThread.join();
    compressionThread.join();

    ALOGD("%s: main end", __func__);
    return 0;
}


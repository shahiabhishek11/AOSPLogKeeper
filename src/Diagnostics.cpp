#include "include/Diagnostics.h"
#include "include/Definition.h"
using namespace std;

// Constructor
Diagnostic::Diagnostic()
{
    ALOGD("%s: constructor diagnostics ", __func__);
    // Initialize members if needed
}

// Destructor
Diagnostic::~Diagnostic()
{
    ALOGD("%s: destructor diagnostics ", __func__);
}

void Diagnostic::writeCircularLogwifi(const std::string &filePath, const std::string &logLine)
{
    std::deque<std::string> lines;
    std::ifstream inFile(filePath);
    std::string line;
    // Read existing log lines into a deque
    while (std::getline(inFile, line))
    {
        lines.push_back(line);
    }
    inFile.close(); // Close the file after reading

    // Append the new log line
    lines.push_back(logLine);

    // Maintain circular buffer size by removing the oldest entry
    while (lines.size() > MAX_LOG_LINES)
    {
        lines.pop_front();
    }

    // Write the updated log back to the file
    std::ofstream outFile(filePath, std::ios::out | std::ios::trunc);
    if (!outFile.is_open())
    {
        ALOGD("Error: Cannot open log file %s", filePath.c_str());
        return;
    }

    for (const auto &entry : lines)
    {
        outFile << entry << "\n";
    }
    outFile.close(); // No need to flush before closing
}

void Diagnostic::writeCircularLogble(const std::string &filePath, const std::string &logLine)
{
    std::deque<std::string> lines;
    std::ifstream inFile(filePath);
    std::string line;
    // Read existing log lines into a deque
    while (std::getline(inFile, line))
    {
        lines.push_back(line);
    }
    inFile.close(); // Close the file after reading

    // Append the new log line
    lines.push_back(logLine);

    // Maintain circular buffer size by removing the oldest entry
    while (lines.size() > MAX_LOG_LINES)
    {
        lines.pop_front();
    }

    // Write the updated log back to the file
    std::ofstream outFile(filePath, std::ios::out | std::ios::trunc);
    if (!outFile.is_open())
    {
        ALOGD("Error: Cannot open log file %s", filePath.c_str());
        return;
    }

    for (const auto &entry : lines)
    {
        outFile << entry << "\n";
    }
    outFile.close(); // No need to flush before closing
}

void Diagnostic::writeCircularLoglte(const std::string &filePath, const std::string &logLine)
{
    std::deque<std::string> lines;
    std::ifstream inFile(filePath);
    std::string line;
    // Read existing log lines into a deque
    while (std::getline(inFile, line))
    {
        lines.push_back(line);
    }
    inFile.close(); // Close the file after reading

    // Append the new log line
    lines.push_back(logLine);

    // Maintain circular buffer size by removing the oldest entry
    while (lines.size() > MAX_LOG_LINES)
    {
        lines.pop_front();
    }

    // Write the updated log back to the file
    std::ofstream outFile(filePath, std::ios::out | std::ios::trunc);
    if (!outFile.is_open())
    {
        ALOGD("Error: Cannot open log file %s", filePath.c_str());
        return;
    }

    for (const auto &entry : lines)
    {
        outFile << entry << "\n";
    }
    outFile.close(); // No need to flush before closing
}

void Diagnostic::writeCircularLoggps(const std::string &filePath, const std::string &logLine)
{
    std::deque<std::string> lines;
    std::ifstream inFile(filePath);
    std::string line;
    // Read existing log lines into a deque
    while (std::getline(inFile, line))
    {
        lines.push_back(line);
    }
    inFile.close(); // Close the file after reading

    // Append the new log line
    lines.push_back(logLine);

    // Maintain circular buffer size by removing the oldest entry
    while (lines.size() > MAX_LOG_LINES)
    {
        lines.pop_front();
    }

    // Write the updated log back to the file
    std::ofstream outFile(filePath, std::ios::out | std::ios::trunc);
    if (!outFile.is_open())
    {
        ALOGD("Error: Cannot open log file %s", filePath.c_str());
        return;
    }

    for (const auto &entry : lines)
    {
        outFile << entry << "\n";
    }
    outFile.close(); // No need to flush before closing
}

void Diagnostic::writeCircularLogtouch(const std::string &filePath, const std::string &logLine)
{
    std::deque<std::string> lines;
    std::ifstream inFile(filePath);
    std::string line;
    // Read existing log lines into a deque
    while (std::getline(inFile, line))
    {
        lines.push_back(line);
    }
    inFile.close(); // Close the file after reading

    // Append the new log line
    lines.push_back(logLine);

    // Maintain circular buffer size by removing the oldest entry
    while (lines.size() > MAX_LOG_LINES)
    {
        lines.pop_front();
    }

    // Write the updated log back to the file
    std::ofstream outFile(filePath, std::ios::out | std::ios::trunc);
    if (!outFile.is_open())
    {
        ALOGD("Error: Cannot open log file %s", filePath.c_str());
        return;
    }

    for (const auto &entry : lines)
    {
        outFile << entry << "\n";
    }
    outFile.close(); // No need to flush before closing
}

void Diagnostic::writeCircularLogdisplay(const std::string &filePath, const std::string &logLine)
{
    std::deque<std::string> lines;
    std::ifstream inFile(filePath);
    std::string line;
    // Read existing log lines into a deque
    while (std::getline(inFile, line))
    {
        lines.push_back(line);
    }
    inFile.close(); // Close the file after reading

    // Append the new log line
    lines.push_back(logLine);

    // Maintain circular buffer size by removing the oldest entry
    while (lines.size() > MAX_LOG_LINES)
    {
        lines.pop_front();
    }

    // Write the updated log back to the file
    std::ofstream outFile(filePath, std::ios::out | std::ios::trunc);
    if (!outFile.is_open())
    {
        ALOGD("Error: Cannot open log file %s", filePath.c_str());
        return;
    }

    for (const auto &entry : lines)
    {
        outFile << entry << "\n";
    }
    outFile.close(); // No need to flush before closing
}

void Diagnostic::writeCircularLogdmesg(const std::string &filePath, const std::string &logLine)
{
    std::deque<std::string> lines;
    std::ifstream inFile(filePath);
    std::string line;
    // Read existing log lines into a deque
    while (std::getline(inFile, line))
    {
        lines.push_back(line);
    }
    inFile.close(); // Close the file after reading

    // Append the new log line
    lines.push_back(logLine);

    // Maintain circular buffer size by removing the oldest entry
    while (lines.size() > MAX_LOG_LINES)
    {
        lines.pop_front();
    }

    // Write the updated log back to the file
    std::ofstream outFile(filePath, std::ios::out | std::ios::trunc);
    if (!outFile.is_open())
    {
        ALOGD("Error: Cannot open log file %s", filePath.c_str());
        return;
    }

    for (const auto &entry : lines)
    {
        outFile << entry << "\n";
    }
    outFile.close(); // No need to flush before closing
}

void Diagnostic::writeCircularLogcrash(const std::string &filePath, const std::string &logLine)
{
    std::deque<std::string> lines;
    std::ifstream inFile(filePath);
    std::string line;
    // Read existing log lines into a deque
    while (std::getline(inFile, line))
    {
        lines.push_back(line);
    }
    inFile.close(); // Close the file after reading

    // Append the new log line
    lines.push_back(logLine);

    // Maintain circular buffer size by removing the oldest entry
    while (lines.size() > MAX_LOG_LINES)
    {
        lines.pop_front();
    }

    // Write the updated log back to the file
    std::ofstream outFile(filePath, std::ios::out | std::ios::trunc);
    if (!outFile.is_open())
    {
        ALOGD("Error: Cannot open log file %s", filePath.c_str());
        return;
    }

    for (const auto &entry : lines)
    {
        outFile << entry << "\n";
    }
    outFile.close(); // No need to flush before closing
}

// Function to set correct file permissions
void setFilePermissions(const std::string &filePath)
{
    if (access(filePath.c_str(), F_OK) != 0)
    {
        ALOGD("%s: Creating file: %s", __func__, filePath.c_str());
        std::ofstream file(filePath); // Create the file if it doesn't exist
        if (!file)
        {
            ALOGE("%s: Failed to create file: %s", __func__, filePath.c_str());
            return;
        }
        file.close();
    }

    // Change file permissions
    if (chmod(filePath.c_str(), 0666) != 0)
    { // Use 0666 instead of 0777 for security
        ALOGE("%s: Failed to set permissions on %s", __func__, filePath.c_str());
    }
    else
    {
        ALOGD("%s: Set permissions to 666 on %s", __func__, filePath.c_str());
    }
    // Change ownership to root:shell (useful for ADB access)
    system(("chown root:shell " + filePath).c_str());
}

void Diagnostic::processLog(const std::string &logLine)
{
    if (logLine.find(" E ") != string::npos)
    { // Error logs
        writeCircularLog(ERROR_LOG_FILE, logLine);
    }
    else if (logLine.find(" D ") != string::npos)
    { // Debug logs
        writeCircularLog(DEBUG_LOG_FILE, logLine);
    }
}

void Diagnostic::monitorCrashLogs()
{
    std::this_thread::sleep_for(std::chrono::seconds(15));
    time_t lastModified1 = getLastModifiedTime(CRASH_LOG_FILE);
    ALOGD("Initial Crash log 1 modified time: %ld ", lastModified1);

    while (true)
    {
        std::this_thread::sleep_for(std::chrono::seconds(1)); // Check every second

        time_t newModified1 = getLastModifiedTime(CRASH_LOG_FILE);
        // ALOGD("Previous Crash log 1 modified time: %ld ", lastModified1);
        // ALOGD("Current Crash log 1 modified time: %ld ", newModified1);

        // Detect system time reset
        if (newModified1 < lastModified1)
        {
            ALOGW("System time reset detected! Updating lastModified1.");
            lastModified1 = newModified1; // Reset to the new valid timestamp

            // Assume logs might have changed, so trigger compression
            compresscrashLogs(newModified1);
        }

        if (newModified1 > lastModified1)
        {
            ALOGD("Crash log 1 updated. Extracting relevant logs...");
            lastModified1 = newModified1;

            // Compress logs immediately
            compresscrashLogs(newModified1);
        }
    }
}

void Diagnostic::compressLogs()
{
    while (true)
    {
        std::this_thread::sleep_for(std::chrono::seconds(60)); // Run every 60 sec
        std::string tarCommand = getTarCommand();
        if (tarCommand.empty())
        {
            ALOGD("No non-empty logs to compress. Skipping...");
            continue;
        }

        int result = system(tarCommand.c_str());
        if (result != 0)
        {
            ALOGD("Error: Failed to create TAR file! (Exit Code: %d)", result);
        }
        else
        {
            ALOGD("Logs compressed successfully: /data/local/tmp/logs.tar.gz");
            system("chmod 666 /data/local/tmp/logs.tar.gz");
            system("chown root:shell /data/local/tmp/logs.tar.gz");
            ALOGD("Permissions set: logs.tar.gz (chmod 666, chown root:shell)");
        }
    }
}

void Diagnostic::captureCrashLogs()
{
    FILE *crashLogStream = popen("/system/bin/logcat -b crash", "r");

    if (!crashLogStream)
    {
        ALOGD("Error: Failed to capture crash logs!");
        return; // Avoid infinite retries on failure
    }

    char buffer[4096];
    while (true)
    {
        if (fgets(buffer, sizeof(buffer), crashLogStream))
        {
            std::string logLine(buffer);
            writeCircularLogcrash(CRASH_LOG_FILE, logLine);
        }
    }

    pclose(crashLogStream);
}

void Diagnostic::captureDmesgLogs()
{
    FILE *DmesgLogStream = popen("dmesg -w", "r");

    if (!DmesgLogStream)
    {
        ALOGD("Error: Failed to capture crash logs!");
        return; // Avoid infinite retries on failure
    }

    char buffer[4096];
    while (true)
    {
        if (fgets(buffer, sizeof(buffer), DmesgLogStream))
        {
            std::string logLine(buffer);
            writeCircularLogdmesg(DMESG_LOG_FILE, logLine);
        }
    }

    pclose(DmesgLogStream);
}

void Diagnostic::writeCircularLog(const std::string &filePath, const std::string &logLine)
{
    std::deque<std::string> lines;
    std::ifstream inFile(filePath);
    std::string line;
    // Read existing log lines into a deque
    while (std::getline(inFile, line))
    {
        lines.push_back(line);
    }
    inFile.close(); // Close the file after reading

    // Append the new log line
    lines.push_back(logLine);

    // Maintain circular buffer size by removing the oldest entry
    while (lines.size() > MAX_LOG_LINES)
    {
        lines.pop_front();
    }

    // Write the updated log back to the file
    std::ofstream outFile(filePath, std::ios::out | std::ios::trunc);
    if (!outFile.is_open())
    {
        ALOGD("Error: Cannot open log file %s", filePath.c_str());
        return;
    }

    for (const auto &entry : lines)
    {
        outFile << entry << "\n";
    }
    outFile.close(); // No need to flush before closing
}

// Function to capture logs for a specific category
void Diagnostic::captureLogswifi(const std::string &logFilePath, bool (*filterFunc)(const std::string &))
{
    FILE *logStream = popen("/system/bin/logcat", "r");

    if (!logStream)
    {
        ALOGD("Error: Failed to open logcat stream for %s", logFilePath.c_str());
        return;
    }

    char buffer[4092];

    while (true)
    {
        if (fgets(buffer, sizeof(buffer), logStream))
        {
            std::string logLine(buffer);
            if (filterFunc(logLine))
            {

                writeCircularLogwifi(logFilePath, logLine);
            }
        }
    }

    pclose(logStream);
}

void Diagnostic::captureLogsble(const std::string &logFilePath, bool (*filterFunc)(const std::string &))
{
    FILE *logStream = popen("/system/bin/logcat", "r");

    if (!logStream)
    {
        ALOGD("Error: Failed to open logcat stream for %s", logFilePath.c_str());
        return;
    }

    char buffer[4092];

    while (true)
    {
        if (fgets(buffer, sizeof(buffer), logStream))
        {
            std::string logLine(buffer);
            if (filterFunc(logLine))
            {
                writeCircularLogble(logFilePath, logLine);
            }
        }
    }

    pclose(logStream);
}

void Diagnostic::captureLogsgps(const std::string &logFilePath, bool (*filterFunc)(const std::string &))
{
    FILE *logStream = popen("/system/bin/logcat", "r");

    if (!logStream)
    {
        ALOGD("Error: Failed to open logcat stream for %s", logFilePath.c_str());
        return;
    }

    char buffer[4092];

    while (true)
    {
        if (fgets(buffer, sizeof(buffer), logStream))
        {
            std::string logLine(buffer);
            if (filterFunc(logLine))
            {
                writeCircularLoggps(logFilePath, logLine);
            }
        }
    }

    pclose(logStream);
}

void Diagnostic::captureLogslte(const std::string &logFilePath, bool (*filterFunc)(const std::string &))
{
    FILE *logStream = popen("/system/bin/logcat", "r");

    if (!logStream)
    {
        ALOGD("Error: Failed to open logcat stream for %s", logFilePath.c_str());
        return;
    }

    char buffer[4092];

    while (true)
    {
        if (fgets(buffer, sizeof(buffer), logStream))
        {
            std::string logLine(buffer);
            if (filterFunc(logLine))
            {
                writeCircularLoglte(logFilePath, logLine);
            }
        }
    }

    pclose(logStream);
}

void Diagnostic::captureLogstouch(const std::string &logFilePath, bool (*filterFunc)(const std::string &))
{
    FILE *logStream = popen("/system/bin/logcat", "r");

    if (!logStream)
    {
        ALOGD("Error: Failed to open logcat stream for %s", logFilePath.c_str());
        return;
    }

    char buffer[4092];

    while (true)
    {
        if (fgets(buffer, sizeof(buffer), logStream))
        {
            std::string logLine(buffer);
            if (filterFunc(logLine))
            {
                writeCircularLogtouch(logFilePath, logLine);
            }
        }
    }

    pclose(logStream);
}

void Diagnostic::captureLogsdisplay(const std::string &logFilePath, bool (*filterFunc)(const std::string &))
{
    FILE *logStream = popen("/system/bin/logcat", "r");

    if (!logStream)
    {
        ALOGD("Error: Failed to open logcat stream for %s", logFilePath.c_str());
        return;
    }

    char buffer[4092];

    while (true)
    {
        if (fgets(buffer, sizeof(buffer), logStream))
        {
            std::string logLine(buffer);
            if (filterFunc(logLine))
            {
                writeCircularLogdisplay(logFilePath, logLine);
            }
        }
    }

    pclose(logStream);
}

void Diagnostic::captureAndProcessLogs()
{
    FILE *logStream = popen("/system/bin/logcat", "r");

    if (!logStream)
    {
        ALOGD("Error: Failed to open logcat stream for processing logs.");
        return;
    }

    char buffer[4092];

    while (true)
    {
        if (fgets(buffer, sizeof(buffer), logStream))
        {
            std::string logLine(buffer);
            processLog(logLine);
        }
    }

    pclose(logStream);
}
// Function to get the last modified time of a file

// // Function to create a timestamp string
std::string getTimestamp(time_t timeVal)
{
    struct tm *timeinfo = localtime(&timeVal);
    char buffer[20];
    strftime(buffer, sizeof(buffer), "%Y%m%d_%H%M%S", timeinfo);
    return std::string(buffer);
}

// Function to extract logs within a 15-minute window
void extractRelevantLogs(time_t crashTime, const std::string &inputFile, const std::string &outputFile)
{
    std::ifstream inFile(inputFile);
    std::ofstream outFile(outputFile);
    std::string line;
    time_t logTime;

    while (std::getline(inFile, line))
    {
        std::istringstream iss(line);
        struct tm logTm = {};
        std::string timestampStr;
        if (!(iss >> timestampStr))
            continue; // Read timestamp

        // Convert timestamp to time_t
        strptime(timestampStr.c_str(), "%Y-%m-%d %H:%M:%S", &logTm);
        logTime = mktime(&logTm);

        // Check if log time is within ±15 minutes of the crash timestamp
        if (logTime >= (crashTime - TIME_WINDOW) && logTime <= (crashTime + TIME_WINDOW))
        {
            outFile << line << "\n";
        }
    }
}

// Function to compress logs into a .tar.gz file
void Diagnostic::compresscrashLogs(time_t crashTime)
{
    std::string basePath = "/data/local/tmp/";
    std::string timestamp = getTimestamp(crashTime);
    std::string archiveName = ARCHIVE_DIR + timestamp + "_crash_log.tar.gz";
    std::string archivePath = basePath + archiveName;

    std::vector<std::string> logFiles = {
        "crash_logs.txt", "error.txt", "debug.txt", "bluetooth_logs.txt",
        "display_logs.txt", "gps_logs.txt", "lte_logs.txt", "touch_logs.txt", "dmesg_logs.txt",
        "wifi_logs.txt"};

    time_t startTime = time(nullptr);
    ALOGD("Waiting for 5 minutes before starting compression...");

    while (difftime(time(nullptr), startTime) < 300)
    {
        sleep(1);
    }

    // Step 1: Create copies of the log files
    for (const auto &file : logFiles)
    {
        std::string copyCommand = "cp " + basePath + file + " " + basePath + file.substr(0, file.find_last_of('.')) + "_copy.txt";
        system(copyCommand.c_str());
    }

    // Step 2: Compress only the copied files
    std::string tarCommand = "tar -czf " + archivePath + " -C " + basePath;
    for (const auto &file : logFiles)
    {
        tarCommand += " " + file.substr(0, file.find_last_of('.')) + "_copy.txt";
    }

    ALOGD("Executing command: %s", tarCommand.c_str());
    int result = system(tarCommand.c_str());

    if (result == 0)
    {
        // Step 3: Set permissions and ownership
        system(("chmod 666 " + archivePath).c_str());
        system(("chown root:shell " + archivePath).c_str());

        ALOGD("Crash logs compressed successfully.");

        // Step 4: Delete the copied log files
        for (const auto &file : logFiles)
        {
            std::string deleteCommand = "rm " + basePath + file.substr(0, file.find_last_of('.')) + "_copy.txt";
            system(deleteCommand.c_str());
        }
    }
    else
    {
        ALOGD("Error: Failed to create archive!");
    }
}

// Implementation of the onRequest method
bool Diagnostic::onRequest()
{
    ALOGD("%s: Diagnostic::onRequest called: ", __func__);
    setFilePermissions(BLUETOOTH_LOG_FILE);
    setFilePermissions(WIFI_LOG_FILE);
    setFilePermissions(LTE_LOG_FILE);
    setFilePermissions(DISPLAY_LOG_FILE);
    setFilePermissions(TOUCH_LOG_FILE);
    setFilePermissions(GPS_LOG_FILE);
    setFilePermissions(CRASH_LOG_FILE);
    setFilePermissions(DEBUG_LOG_FILE);
    setFilePermissions(ERROR_LOG_FILE);
    setFilePermissions(DMESG_LOG_FILE);
 
    // Ensure /data/local/tmp exists and is writable
    if (access("/data/local/tmp", W_OK) != 0)
    {
        ALOGE("%s: No write access to /data/local/tmp!", __func__);
        return -1;
    }
 
    std::ofstream btLogFile(BLUETOOTH_LOG_FILE, std::ios::out | std::ios::app);
    std::ofstream wifiLogFile(WIFI_LOG_FILE, std::ios::out | std::ios::app);
    std::ofstream lteLogFile(LTE_LOG_FILE, std::ios::out | std::ios::app);
    std::ofstream displayLogFile(DISPLAY_LOG_FILE, std::ios::out | std::ios::app);
    std::ofstream touchLogFile(TOUCH_LOG_FILE, std::ios::out | std::ios::app);
    std::ofstream gpsLogFile(GPS_LOG_FILE, std::ios::out | std::ios::app);
    std::ofstream crashLogFile(CRASH_LOG_FILE, std::ios::out | std::ios::app);
    std::ofstream errorLogFile(ERROR_LOG_FILE, std::ios::out | std::ios::app);
    std::ofstream debugLogFile(DEBUG_LOG_FILE, std::ios::out | std::ios::app);
    std::ofstream dmesgLogFile(DMESG_LOG_FILE, std::ios::out | std::ios::app);
 
    if (!btLogFile.is_open())
    {
        ALOGE("%s: Failed to open Bluetooth log file!", __func__);
        return -1;
    }
    if (!wifiLogFile.is_open())
    {
        ALOGE("%s: Failed to open WiFi log file!", __func__);
        return -1;
    }
    if (!lteLogFile.is_open())
    {
        ALOGE("%s: Failed to open lte log file!", __func__);
        return -1;
    }
    if (!displayLogFile.is_open())
    {
        ALOGE("%s: Failed to open display log file!", __func__);
        return -1;
    }
    if (!touchLogFile.is_open())
    {
        ALOGE("%s: Failed to open touch log file!", __func__);
        return -1;
    }
    if (!gpsLogFile.is_open())
    {
        ALOGE("%s: Failed to open gps log file!", __func__);
        return -1;
    }
    if (!crashLogFile.is_open())
    {
        ALOGE("%s: Failed to open crash1 log file!", __func__);
        return -1;
    }
 
    if (!errorLogFile.is_open())
    {
        ALOGE("%s: Failed to open error log file!", __func__);
        return -1;
    }
    if (!debugLogFile.is_open())
    {
        ALOGE("%s: Failed to open debug log file!", __func__);
        return -1;
    }
    if (!dmesgLogFile.is_open())
    {
        ALOGE("%s: Failed to open dmesg log file!", __func__);
        return -1;
    } 
    return 0;    
}

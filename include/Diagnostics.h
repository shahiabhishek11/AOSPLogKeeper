#ifndef DIAGNOSTIC_H
#define DIAGNOSTIC_H

#include <utils/RefBase.h>  // Required for android::sp support
#include <android/log.h>

class Diagnostic : public android::RefBase {  // Inherit from RefBase
public:
    // Constructor
    Diagnostic();

    // Destructor
    ~Diagnostic();

    bool onRequest();
    void captureDmesgLogs();
    void captureAndProcessLogs();
    void captureCrashLogs();
    void monitorCrashLogs();
    void compressLogs();
    void compresscrashLogs(time_t crashTime);
    void processLog(const std::string &logLine);
    void captureLogsble(const std::string &logFilePath, bool (*filterFunc)(const std::string &));
    void captureLogswifi(const std::string &logFilePath, bool (*filterFunc)(const std::string &));
    void captureLogsgps(const std::string &logFilePath, bool (*filterFunc)(const std::string &));
    void captureLogslte(const std::string &logFilePath, bool (*filterFunc)(const std::string &));
    void captureLogstouch(const std::string &logFilePath, bool (*filterFunc)(const std::string &));
    void captureLogsdisplay(const std::string &logFilePath, bool (*filterFunc)(const std::string &));
    
    void writeCircularLogwifi(const std::string &filePath, const std::string &logLine);
    void writeCircularLogble(const std::string &filePath, const std::string &logLine);
    void writeCircularLoglte(const std::string &filePath, const std::string &logLine);
    void writeCircularLoggps(const std::string &filePath, const std::string &logLine);
    void writeCircularLogtouch(const std::string &filePath, const std::string &logLine);
    void writeCircularLogdisplay(const std::string &filePath, const std::string &logLine);
    void writeCircularLogdmesg(const std::string &filePath, const std::string &logLine);
    void writeCircularLogcrash(const std::string &filePath, const std::string &logLine);
    void writeCircularLog(const std::string &filePath, const std::string &logLine);

};

#endif  // DIAGNOSTIC_H

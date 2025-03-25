#include "include/Definition.h"
#include "include/Diagnostics.h"
#include <log/log.h>
#include <memory>
#include <android-base/logging.h>
#include <hidl/HidlTransportSupport.h>
#include <thread>
#include <unistd.h>

using android::hardware::configureRpcThreadpool;
using android::hardware::joinRpcThreadpool;
using android::sp;

// Function to continuously run onRequest()
void runOnRequestLoop(sp<Diagnostic> diagService) {
    usleep(20000000);  // Sleep for 20 seconds
    diagService->onRequest();
}

// Function to start log capturing
void startLogCapture(sp<Diagnostic> diagService) {
    std::thread bluetoothLogThread(&Diagnostic::captureLogsble, diagService, BLUETOOTH_LOG_FILE, isBluetoothLog);
    std::thread wifiLogThread(&Diagnostic::captureLogswifi, diagService, WIFI_LOG_FILE, isWiFiLog);
    std::thread lteLogThread(&Diagnostic::captureLogslte, diagService,LTE_LOG_FILE, isLTELog);
    std::thread displayLogThread(&Diagnostic::captureLogsdisplay,diagService, DISPLAY_LOG_FILE, isDisplayLog);
    std::thread touchLogThread(&Diagnostic::captureLogstouch,diagService, TOUCH_LOG_FILE, isTouchLog);
    std::thread gpsLogThread(&Diagnostic::captureLogsgps,diagService, GPS_LOG_FILE, isGpsLog);
    std::thread dmesgLogThread(&Diagnostic::captureDmesgLogs,diagService);
    std::thread processLogThread(&Diagnostic::captureAndProcessLogs,diagService);
    std::thread crashLogThread(&Diagnostic::captureCrashLogs,diagService);
    //std::thread compressionThread(&Diagnostic::compressLogs,diagService);
    std::thread logMonitorThread(&Diagnostic::monitorCrashLogs,diagService);


    // Detach threads so they run independently
    bluetoothLogThread.detach();
    wifiLogThread.detach();
    lteLogThread.detach();
    displayLogThread.detach();
    touchLogThread.detach();
    gpsLogThread.detach();
    dmesgLogThread.detach();
    processLogThread.detach();
    crashLogThread.detach();
    //compressionThread.detach();
    logMonitorThread.detach();
}

int main() {
    sp<Diagnostic> systemLogService = new Diagnostic();  

    configureRpcThreadpool(1, true /* callerWillJoin */);

    std::thread requestThread(runOnRequestLoop, systemLogService);

    // Start log capturing threads
    startLogCapture(systemLogService);
    // Run onRequest in a separate thread

    joinRpcThreadpool();
    requestThread.join();
    
    return 0;
}

# AOSP Logs Keeper Service

## Overview
The `aosp_logs_keeper_service` is an advanced Android HAL (Hardware Abstraction Layer) service designed to capture and store diagnostic logs from various system components. It provides comprehensive logging capabilities for critical subsystems, including Wi-Fi, Bluetooth, LTE, GPS, display, touch, crash reports, and kernel logs.

This service operates by continuously collecting logs and saving them in the `/data/local/tmp` directory. To optimize storage and improve log management, it automatically compresses all collected logs into a .tar archive every minute. This ensures efficient utilization of storage space while preserving detailed diagnostic data for analysis.

The primary objective of the aosp_logs_keeper_service is to facilitate issue `identification and debugging` in a test environment. By systematically capturing logs, it enables developers and testers to diagnose system crashes, performance issues, and anomalies efficiently. This service plays a crucial role in quality assurance by providing structured log data that aids in root cause analysis and enhances overall system stability.

Designed for seamless integration into the Android system, aosp_logs_keeper_service runs in the background with minimal overhead, ensuring uninterrupted log collection without impacting device performance. Its automated compression mechanism further streamlines the debugging process, reducing the need for manual intervention.

By leveraging this service, development teams can proactively detect and resolve issues, leading to improved software reliability and robustness in production environments..

## Features
- Implements a diagnostic service using HIDL.
- Uses `joinRpcThreadpool` to manage incoming requests.
- Spawns a separate thread for handling service requests.
- Logs system events using Android's logging framework.

## Directory Structure
- Diagnostics.h 
- Diagnostics.cpp
- main.cpp
- Android.mk
- README.md


## Dependencies
Ensure the following Android shared libraries are linked:
- `liblog`
- `libbase`
- `libhidltransport`
- `libutils`



## Build Instructions
To build the `aosp_logs_keeper_service`, use the following command:

    sh
    mm aosp_logs_keeper_service



Running the Service
After successfully building, start the service using:

    sh
    ./aosp_logs_keeper_service

## Code Structure
### main.cpp
Initializes the Diagnostic service.
Configures an RPC thread pool.
Calls onRequest() to handle incoming requests.
Uses joinRpcThreadpool() to keep the service running.
### Diagnostics.h
Declares the Diagnostic class, which defines the onRequest() function.
### Diagnostics.cpp
Implements the Diagnostic service logic.









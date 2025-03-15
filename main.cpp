#include "Diagnostics.h"
#include <log/log.h>
#include <memory>
#include <android-base/logging.h>
#include <hidl/HidlTransportSupport.h>
#include <thread>
#include <unistd.h>

using android::hardware::configureRpc::Threadpool;
using android::hardware::joinRpcThreadpool;
using android::sp;



	int main()
	{
		//Create a Diagnostic service instance
		sp<Diagnostic> systemLogService = new Diagnostic();
		
		//Configure threadpool for RPC handling
		configureRpcThreadpool(1,true);
		
		//Call onRequest()
		systemLogService->onRequest();
		
		//join the RPC threadpool to handle incoming requests
		joinRpcThreadpool();
		
		return 0;
	}

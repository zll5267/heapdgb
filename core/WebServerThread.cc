#include <unistd.h>
#include <sys/types.h>
#include <pthread.h>

#include "log.h"
#include "util.h"
#include "WebServer.hh"
#include "MallocWrapperRequestHandler.hh"
#include "WebServerThread.hh"

namespace HeapDBG {
namespace Core {
    static bool webServertStarted = WebServerThread::createWebServerThread();
	bool WebServerThread::createWebServerThread()
	{
		pthread_t thread;
		pthread_attr_t attr;
		pthread_attr_init(&attr);
		pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
		int ret = pthread_create(&thread, &attr, startWebServer, NULL);
		if (ret)
		{
			CORE_ERROR("thread create fail");
			return false;
		}
		return true;
	}

	void* WebServerThread::startWebServer(void *arg)
	{
		HeapDBG::WebServer::WebServer webServer("192.168.1.105", "7676");
		webServer.setHandler(new MallocWrapperRequestHandler());
		int ret = webServer.start();
		if (!ret)
		{
			CORE_ERROR("web server start fail");
			exit(-1);
		}
	}

} // Core
} // HeapDBG


#ifndef __HEAPDBG_CORE_WEB_SERVER_THREAD_
#define __HEAPDBG_CORE_WEB_SERVER_THREAD_

namespace HeapDBG {
namespace Core {
	class WebServerThread
	{
	public:
		// return true when success or false
		static bool createWebServerThread();
	private:
		//the thread will run this
		static void* startWebServer(void *arg);

	};
} // Core
} // HeapDBG

#endif //__HEAPDBG_CORE_WEB_SERVER_THREAD_


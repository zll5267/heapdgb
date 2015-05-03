#ifndef __HEAPDBG_CORE_MALLOC_WRAPPER_REQUESt_HANDLER
#define __HEAPDBG_CORE_MALLOC_WRAPPER_REQUESt_HANDLER

#include "WebRequestHandler.hh"

namespace HeapDBG {
namespace Core {
	class MallocWrapperRequestHandler
		: public WebServer::WebRequestHandler
	{
	public:
		virtual void generateResponse(int fd);
	};
} // Core
} // HeapDBG

#endif //__HEAPDBG_CORE_MALLOC_WRAPPER_REQUESt_HANDLER


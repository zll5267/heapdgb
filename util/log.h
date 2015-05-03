#ifndef __HEAPDBG_LOG_H
#define __HEAPDBG_LOG_H

#include <iostream>

#define HEAPDBG_WEBSERVER_DEBUG         1
#define HEAPDBG_MALLOCWRAPPER_DEBUG     1
#define HEAPDBG_CORE_DEBUG              1

#ifdef HEAPDBG_WEBSERVER_DEBUG
#define WEBSERVER_DEBUG(str) std::cout << str << std::endl;
#define WEBSERVER_ERROR(str) std::cerr << str << std::endl;
#else //HEAPDBG_WEBSERVER_DEBUG
#define WEBSERVER_DEBUG(str)
#define WEBSERVER_ERROR(str)
#endif //HEAPDBG_WEBSERVER_DEBUG

#ifdef HEAPDBG_MALLOCWRAPPER_DEBUG
#define WRAPPER_DEBUG(str) std::cout << str << std::endl;
#define WRAPPER_ERROR(str) std::cerr << str << std::endl;
#else //HEAPDBG_MALLOCWRAPPER_DEBUG
#define WRAPPER_DEBUG(str)
#define WRAPPER_ERROR(str)
#endif //HEAPDBG_MALLOCWRAPPER_DEBUG

#ifdef HEAPDBG_CORE_DEBUG
#define CORE_DEBUG(str) std::cout << str << std::endl;
#define CORE_ERROR(str) std::cerr << str << std::endl;
#else //HEAPDBG_CORE_DEBUG
#define CORE_DEBUG(str)
#define CORE_ERROR(str)
#endif //HEAPDBG_CORE_DEBUG

#endif // __HEAPDBG_LOG_H

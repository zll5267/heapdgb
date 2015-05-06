#include <pthread.h>
#include <dlfcn.h>
#include <sys/types.h>
#include <execinfo.h>
#include <stdio.h>
#include <list>

#include "log.h"
#include "util.h"
#include "MallocInfo.hh"

namespace HeapDBG {
namespace Wrapper {
    __attribute__((destructor)) static void printStatistic();
    static pthread_mutex_t wrapper_mutex = PTHREAD_MUTEX_INITIALIZER;
    static unsigned long malloc_count = 0;
    static std::list<MallocInfo> mallocList;
    static const size_t max_stacktrace_depth = 128;
    static bool useHook = true;
    typedef void* (*malloc_ptr)(size_t);
    typedef void (*free_ptr)(void*);
    static malloc_ptr sys_malloc = 0;
    static free_ptr sys_free = 0;

    static bool getSystemMalloc()
    {
        sys_malloc = (malloc_ptr)dlsym(RTLD_NEXT, "malloc");
        if(!sys_malloc)
        {
            WRAPPER_ERROR("can not find the system malloc functioin" << dlerror());
            return false;
        }

        sys_free = (free_ptr)dlsym(RTLD_NEXT, "free");
        if(!sys_free)
        {
            WRAPPER_ERROR("can not find the system free functioin" << dlerror());
            return false;
        }
        //WRAPPER_DEBUG("sysmalloc:0x"<<std::hex<<(unsigned long)sys_malloc);
        //WRAPPER_DEBUG("sysfree:0x" << (unsigned long)sys_free << std::dec);
        return true;
    }
    //guarantee the system malloc/free initialized
    static bool initialized = getSystemMalloc();

#ifdef __cplusplus
    extern "C"
    {
#endif
        void* malloc(size_t size)
        {
            //WRAPPER_DEBUG("malloc, initialized:" << initialized);
            //if not initizlized, means malloc can not perform
            if (!initialized)
                return NULL;
            void *ptr = sys_malloc(size);
            //WRAPPER_DEBUG("useHook:" << useHook << ";ptr:" << ptr);
            if (useHook&&ptr)
            {
                pid_t threadID = HeapDBG::Util::getTID();
                pthread_mutex_lock(&wrapper_mutex);
                useHook = false;
                ++malloc_count;
                //for stacktrace
                void* frames[max_stacktrace_depth] = {0};
                size_t stack_size = backtrace(frames, max_stacktrace_depth);
                char** stacktrace = backtrace_symbols(frames, stack_size);
                //WRAPPER_DEBUG("stack_size:" << stack_size);
                //create MallocInfo
                MallocInfo mallocInfo(ptr, size, stacktrace, stack_size, threadID);
                mallocList.push_back(mallocInfo);
                sys_free(stacktrace);
                useHook = true;
                pthread_mutex_unlock(&wrapper_mutex);
            }
            return ptr;
        }
        void free(void* ptr)
        {
            //if not initizlized, means malloc can not perform
            if (!initialized)
                return;
            long address = (long)ptr;
            if(useHook&&ptr)
            {
                pthread_mutex_lock(&wrapper_mutex);
                useHook = false;
                //--malloc_count;
                for(std::list<MallocInfo>::iterator it = mallocList.begin();
                    it != mallocList.end(); ++it)
                {
                    if ((*it).getAddress() == address)
                    {
                        mallocList.erase(it);
                        break;
                    }
                }
                useHook = true;
                pthread_mutex_unlock(&wrapper_mutex);
            }
        }
    void generateHTML(char body[], size_t n)
    {
		int tLen = 0;
		char *tpBody = body + tLen;
		int tnLeft = n - tLen;
		pthread_mutex_unlock(&wrapper_mutex);
		tLen = snprintf(tpBody, tnLeft, "<html><title>heapdbg</title><body>");
		tpBody += tLen;
		tnLeft -= tLen;
        if (mallocList.empty())
        {
            tLen = snprintf(tpBody, tnLeft,
                "Found no leaks, not one of the %lu allocations was not released.allocations was not released." ,
                malloc_count);

			tpBody += tLen;
			tnLeft -= tLen;
			snprintf(tpBody, tnLeft, "</body></html>");
        }
        else
        {
			//std::cout << "body1:" << body << std::endl;
            tLen = snprintf(tpBody, tnLeft,
                            " detected that %lu out of %lu allocations were not released.<p>",
                            mallocList.size(), malloc_count);
			tpBody += tLen;
			tnLeft -= tLen;
			//std::cout << "body2:" << body << std::endl;
            unsigned long i = 0;
            for(std::list<MallocInfo>::iterator it = mallocList.begin();
                it != mallocList.end(); ++it)
            {
                MallocInfo mallocInfo = *it;//mallocList[i];
				tLen = snprintf(tpBody, tnLeft,
                                "Leak %lu@threadID: %d; leaked %lu bytes as position 0x%lx",
                                ++i, mallocInfo.getThreadID(), mallocInfo.getSize(), mallocInfo.getAddress());

				tpBody += tLen;
				tnLeft -= tLen;

                const std::vector<std::string>& stacktrace = mallocInfo.getStackTrace();
                for (size_t j = 0; j < stacktrace.size(); ++j)
                {
					tLen = snprintf(tpBody, tnLeft, "<p>&nbsp;&nbsp;&nbsp;&nbsp%s<p>", stacktrace[j].c_str());
					tpBody += tLen;
					tnLeft -= tLen;
                }
            }
			snprintf(tpBody, tnLeft, "</body></html>");
        }
		pthread_mutex_unlock(&wrapper_mutex);
    }
#ifdef __cplusplus
    }
#endif
#ifdef HEAPDBG_MALLOCWRAPPER_DEBUG
    static void printStatistic()
    {
        useHook = false;
        if (mallocList.empty())
        {
            std::cout << "found no leaks, not one of the " << malloc_count;
            std::cout << " allocations was not released." << std::endl;
        }
        else
        {
            std::cout << "detected that " << mallocList.size();
            std::cout << " out of " << malloc_count << " allocations were not released." << std::endl;
            //for (int i = 0; i < mallocList.size(); ++i)
            int i = 0;
            for(std::list<MallocInfo>::iterator it = mallocList.begin();
                it != mallocList.end(); ++it)
            {
                MallocInfo mallocInfo = *it;//mallocList[i];
                std::cout << "Leak " << (++i) << "@thread id: " << mallocInfo.getThreadID();
                std::cout << "; leaked " << mallocInfo.getSize() << " bytes at position 0x";
                std::cout << std::hex << mallocInfo.getAddress() << std::dec << std::endl;

                const std::vector<std::string>& stacktrace = mallocInfo.getStackTrace();
                for (size_t j = 0; j < stacktrace.size(); ++j)
                {
                    std::cout << "\t" << stacktrace[j] << std::endl;
                }
            }
        }
    }
#endif
} // Wrapper
} // namespace HeapDBG

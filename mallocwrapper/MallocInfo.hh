#ifndef __HEAPDBG_WRAPPER_MALLOC_INFO_H
#define __HEAPDBG_WRAPPER_MALLOC_INFO_H

#include <unistd.h>
#include <vector>
#include <string>

namespace HeapDBG {
namespace Wrapper {

    class MallocInfo
    {
    public:
        MallocInfo(void* address, size_t size,
            char** stacktrace, size_t depth, pid_t tid);

        long getAddress() const;
        size_t getSize() const;
        const std::vector<std::string>& getStackTrace() const;
        pid_t getThreadID() const;
    private:
        long mAddress;
        size_t mSize;
        std::vector<std::string> mStackTrace;
        pid_t mThreadID;
    };

} // Wrapper
} // namespace HeapDBG
#endif // __HEAPDBG_WRAPPER_MALLOC_INFO_H

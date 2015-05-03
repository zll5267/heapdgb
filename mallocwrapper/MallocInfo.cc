#include <list>

#include "MallocInfo.hh"

namespace HeapDBG {
namespace Wrapper {
    MallocInfo::MallocInfo(void* address, size_t size,
        char** stacktrace, size_t depth, pid_t tid)
    {
        mAddress = (long)address;
        mSize = size;

        for (int i = 0; i < depth; ++i)
        {
            std::string frame = stacktrace[i];
            mStackTrace.push_back(frame);
        }
        mThreadID = tid;
    }

    long MallocInfo::getAddress() const
    {
        return mAddress;
    }

    size_t MallocInfo::getSize() const
    {
        return mSize;
    }

    const std::vector<std::string>& MallocInfo::getStackTrace() const
    {
        return mStackTrace;
    }

    pid_t MallocInfo::getThreadID() const
    {
        return mThreadID;
    }
} // Wrapper
} // namespace HeapDBG

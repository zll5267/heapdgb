#ifndef __HEAPDBG_UTIL_H
#define __HEAPDBG_UTIL_H

#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/syscall.h>

namespace HeapDBG {
namespace Util{
    inline pid_t getTID()
    {
        return syscall(SYS_gettid);//__NR_gettid
    }

	inline ssize_t iwrite(int fd, void *buf, size_t n)
	{
		size_t nleft = n;
		ssize_t nwritten;
		char* bufp = (char*)buf;

		while (nleft > 0)
		{
			if ((nwritten = write(fd, bufp, nleft)) <= 0)
			{
				if (errno == EINTR)
					nwritten = 0;
				else
				{
					WEBSERVER_DEBUG("write error, " << n << " need to write, but " << nleft << " still left.");
					return -1;
				}
			}
			nleft -= nwritten;
			bufp += nwritten;
		}
		//WEBSERVER_DEBUG("write " << n << " bytes!!");
		return n;
	}
} // Util
} // HeapDBG

#endif // __HEAPDBG_UTIL_H

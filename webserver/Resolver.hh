#ifndef __HEAPDBG_RESOLVER_H
#define __HEAPDBG_RESOLVER_H

#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netdb.h>

namespace HeapDBG {
namespace WebServer {
    class Resolver
    {
        public:
            Resolver(const char* hostname, const char* service = NULL, int family = AF_INET, int socktype = SOCK_STREAM);
            ~Resolver();

            /*
             * printall: true print all the avaiable addrinfo
             *           false only print the current addrinfo
             *           default: true
             */
            void printAllAvaiableAddrinfo(bool printall = true);
            void printCurrentAddrinfo();

            /*
             * try the next addrinfo in the list
             * return: not null: next operation success,
             *         null: next operation fail.
             */
            struct addrinfo *next();
            /*
             *get current usable addrinfo
             *return: null means can not resolve the hostname
             */
            struct addrinfo *current(){ return ai_current;}

        private:
            /*
             *prohibit copy and assign
             */
            Resolver(const Resolver&);
            Resolver& operator=(const Resolver&);

            struct addrinfo hint, *ai_result, *ai_current;

    };
} // WebServer
} // namespace HeapDBG
#endif // __HEAPDBG_RESOLVER_H

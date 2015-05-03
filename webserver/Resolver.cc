#include <iostream>
#include <ctime>
#include <errno.h>
#include <cstring>

#include "log.h"
#include "Resolver.hh"

namespace HeapDBG {
namespace WebServer {
    Resolver::Resolver(const char* hostname, const char* service, int family, int socktype)
        :ai_result(NULL), ai_current(NULL)
    {
        memset(&hint, 0, sizeof(hint));

        hint.ai_family = family;
        hint.ai_flags = AI_PASSIVE;
        hint.ai_socktype  = socktype;
        hint.ai_protocol = 0;

        int ret = getaddrinfo(hostname, service, &hint, &ai_result);
        if(ret)
        {
            WEBSERVER_ERROR(" get addrinfo fail, reason is: " << gai_strerror(ret));
            ai_result = NULL;

            //throw std::bad_alloc();
        }
        ai_current = ai_result;
    }

    Resolver::~Resolver()
    {
        if(ai_result)
            freeaddrinfo(ai_result);
    }

    void Resolver::printAllAvaiableAddrinfo(bool printall)
    {
        struct addrinfo *ai_temp = NULL;
        char hostname[NI_MAXHOST] = {0};
        char service[NI_MAXSERV] = {0};
        int ret = -1;
        if(!ai_result)
        {
            WEBSERVER_ERROR(" don't have any addrinfo now !!!!!!! ");
            return;
        }

        if(printall)
            ai_temp = ai_result;
        else
            ai_temp = ai_current;
        while(ai_temp)
        {
            ret = getnameinfo(((struct sockaddr*)(ai_temp->ai_addr)), ai_temp->ai_addrlen,
                    hostname, sizeof(hostname),
                    service, sizeof(service),
                    NI_NUMERICHOST|NI_NUMERICSERV
                    );
            if(ret)
            {
                WEBSERVER_ERROR(" error happens: " << gai_strerror(ret));
                ret = -1;
            }
            else
            {
                WEBSERVER_DEBUG("hostname: " << hostname << "; service : " << service);
            }
            if(printall)
                ai_temp = ai_temp->ai_next;
            else
                break; //ai_temp = NULL;
        }
    }

    void Resolver::printCurrentAddrinfo()
    {
        printAllAvaiableAddrinfo(false);
    }

    struct addrinfo *Resolver::next()
    {
        if(ai_current && ai_current->ai_next)
        {
            ai_current = ai_current->ai_next;
            return ai_current;
        }
        return NULL;
    }
} // WebServer
} // namespace HeapDBG

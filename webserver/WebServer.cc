#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>

#include "log.h"
#include "WebServer.hh"

namespace HeapDBG {
namespace WebServer {

    WebServer::WebServer(const char* hostname, const char* service, int family, int socktype)
        :mServerfd(-1), mClientfd(-1),mResolver(hostname, service, family, socktype)
    {
        memset(&mClientaddr, 0, sizeof(mClientaddr));
        mClientaddrlen = sizeof(mClientaddr);
		mHandler = new WebRequestHandler();
    }

     WebServer::~WebServer()
    {
		if (mHandler)
			delete mHandler;
		mHandler = NULL;
    }

    bool WebServer::start()
    {
        bool result = false;

        struct addrinfo *ai_current = mResolver.current();
        while(!result && ai_current)
        {
            mServerfd = socket(ai_current->ai_family, ai_current->ai_socktype, ai_current->ai_protocol);
            if(!(mServerfd < 0))
            {
                if(bind(mServerfd, ai_current->ai_addr, ai_current->ai_addrlen) == 0)
                {
                    if(listen(mServerfd, LISTEN_QUEUE) == 0)
                    {
                        result = true;
                    }
                    else
                    {
                        WEBSERVER_ERROR("listen error: " << strerror(errno));
                    }
                }
                else
                {
                    WEBSERVER_ERROR("bind error: " << strerror(errno));
                }
            }
            else
            {
                WEBSERVER_ERROR("socket error: " << strerror(errno));
            }
            if(!result)
            {
                if(mServerfd >= 0)
                    close(mServerfd);

                mServerfd = -1;
                if(!mResolver.next())
                    break;
                WEBSERVER_ERROR("try next addrinfo");
            }
        }

        if(result)
        {
#ifdef HEAPDBG_WEBSERVER_DEBUG
            mResolver.printCurrentAddrinfo();
#endif
            signal(SIGPIPE, ignoreSIGPIPE);
            while(true)
            {
                mClientfd = accept(mServerfd, (struct sockaddr *)&mClientaddr, &mClientaddrlen);
                if(mClientfd < 0)
                {
                    //perror("accept error happen: ");
                    WEBSERVER_ERROR("accept error: " << strerror(errno));
                    continue;
                }
                newRequest(mClientfd, mClientaddr, mClientaddrlen);
            }
        }

        return result;
    }

    void WebServer::ignoreSIGPIPE(int signo)
    {
        perror("signal PIPE catched ");
    }

	void WebServer::setHandler(WebRequestHandler* handler)
	{
		if (mHandler)
			delete mHandler;
		mHandler = handler;
	}

    void WebServer::newRequest(int clientfd, struct sockaddr_storage clientaddr, socklen_t clientaddrlen)
    {
        WEBSERVER_DEBUG("enter WebServer::newRequest");
#ifdef HEAPDBG_WEBSERVER_DEBUG
        char hostname[NI_MAXHOST] = {0};
        char service[NI_MAXSERV] = {0};
        int ret = -1;
        ret = getnameinfo(((struct sockaddr*)(&mClientaddr)), mClientaddrlen,
                hostname, sizeof(hostname),
                service, sizeof(service),
                NI_NUMERICHOST|NI_NUMERICSERV
                );
        if(ret)
        {
            WEBSERVER_ERROR(" getnameinfo error happen: " << gai_strerror(ret));
            ret = -1;
        }
        else
        {
            WEBSERVER_DEBUG("get connection from [hostname: " << hostname << "; service : " << service << "]");
        }
#endif
        WEBSERVER_DEBUG("try to handle the request");
		if (mHandler)
			mHandler->handle(mClientfd);
    }
} // WebServer
} // namespace HeapDBG

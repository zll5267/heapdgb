#ifndef __HEAPDBG_WEB_SERVER_H
#define __HEAPDBG_WEB_SERVER_H

#include "Resolver.hh"
#include "WebRequestHandler.hh"

namespace HeapDBG {
namespace WebServer {
    /*
        WebServer implementation
    */
    class WebServer
    {
        public:
            WebServer(const char* hostname, const char* service = NULL, int family = AF_INET, int socktype = SOCK_STREAM);
            ~WebServer();

            /**
             *start to listen on one of the result from getaddrinfo
             *return: true start successfull
             *        false start fail
             */
            bool start();

            //ignore the SIGPIPE signal
            static void ignoreSIGPIPE(int signo);
            //set the http request handler
            void setHandler(WebRequestHandler* handler);
        private:
            //prohibit copy and assign
            WebServer(const WebServer&);
            WebServer& operator=(const WebServer&);

            //private help function
            void newRequest(int clientfd, struct sockaddr_storage clientaddr, socklen_t clientaddrlen);
            //member variable
            static const int LISTEN_QUEUE = 5;
            int mServerfd, mClientfd;
            Resolver mResolver;
            struct sockaddr_storage mClientaddr;
            socklen_t mClientaddrlen;
            WebRequestHandler* mHandler;
    };

} // WebServer
} // namespace HeapDBG
#endif // __HEAPDBG_WEB_SERVER_H

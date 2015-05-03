#ifndef __HEAPDBG_WEB_SERVER_FACTORY_H
#define __HEAPDBG_WEB_SERVER_FACTORY_H

#include "WebServer.hh"

namespace HeapDBG {
namespace WebServer {
    /*
        A Factory class use to create a server
        listen on a port
    */
    class WebServerFactory
    {
    public:
        static WebServer* createWebServer();

    };

} // WebServer
} // namespace HeapDBG
#endif // __HEAPDBG_WEB_SERVER_FACTORY_H

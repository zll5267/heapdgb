#ifndef __HEAPDBG_WEB_REQUEST_HANDLER_H
#define __HEAPDBG_WEB_REQUEST_HANDLER_H

#define MAXLINE 512
#define MAXBUF 4096

namespace HeapDBG {
namespace WebServer {

    class WebRequestHandler
    {
    public:
        WebRequestHandler();
        ~WebRequestHandler();

        void handle(int clientfd);
        /*return the http response*/
        virtual void generateResponse(int fd);

    private:
        void requestError(int fd, const char *cause, const char *errnum, const char *shortmsg, const char *longmsg);
        void handleRequestHeader(char *buf);


    };

} // WebServer
} // namespace HeapDBG
#endif // __HEAPDBG_WEB_REQUEST_HANDLER_H

#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>

#include "log.h"
#include "util.h"
#include "WebRequestHandler.hh"


namespace HeapDBG {
namespace WebServer {
    WebRequestHandler::WebRequestHandler(){};
    WebRequestHandler::~WebRequestHandler(){};

    void WebRequestHandler::handle(int clientfd)
    {
        //WEBSERVER_DEBUG("enter WebRequestHandler::handle, clientfd:" << clientfd);
        char buf[MAXBUF] = {0}, method[MAXLINE] = {0}, uri[MAXLINE] = {0}, version[MAXLINE] = {0};
        read(clientfd, buf, MAXBUF);
        //WEBSERVER_DEBUG("ReadInfo: " << std::endl << buf);
        sscanf(buf, "%s %s %s", method, uri, version);
        //WEBSERVER_DEBUG("method:" << method << ";uri:" << uri << ";version:" << version);
        if (strcasecmp(method, "GET"))
        {
            requestError(clientfd, method, "501", "Not Implemented", "This method is not supported by HeapDBG WebServer");
            return;
        }
        if (!strcasecmp(uri, "/heapdbg"))
        {
            generateResponse(clientfd);
        }
        else
        {
            //WEBSERVER_ERROR("wrong access path:" << uri << "; only accept /heapdbg");
            requestError(clientfd, uri, "501", "Not Implemented", "This uri is not supported by HeapDBG WebServer, only accept /heapdbg");
        }
        close(clientfd);
    }

    void WebRequestHandler::generateResponse(int fd)
    {
        static int generateCounts = 0;
        //WEBSERVER_DEBUG("enter WebRequestHandler::generateResponse");
        char buf[MAXLINE] = {0}, body[MAXLINE] = {0}, response[MAXBUF] = {0};
        /*build the body*/
        sprintf(body, "<html><title>Welcome</title><body><p>Hello World, welcome %d to HeapDBG</body></html>", ++generateCounts);

        /*build response header*/
        sprintf(buf, "HTTP/1.0 200 OK\r\n");
        sprintf(buf, "%sServer: HeapDBG\r\n", buf);
        sprintf(buf, "%sConnection: close\r\n", buf);
        sprintf(buf, "%sContent-type: text/html\r\n", buf);
        sprintf(buf, "%sContent-length: %d\r\n", buf, (int)strlen(body));

        sprintf(response, "%s\r\n%s", buf, body);
        WEBSERVER_DEBUG("response:" << std::endl << response);
        HeapDBG::Util::iwrite(fd, response, strlen(response));
    }

    void WebRequestHandler::requestError(int fd, const char *cause, const char *errnum, const char *shortmsg, const char *longmsg)
    {
        char buf[MAXLINE] = {0}, body[MAXLINE] = {0}, response[MAXBUF] = {0};
        /*build the body*/
        sprintf(body, "<html><title>request error</title>");
        sprintf(body, "%s<body bgcolor=""ffffff"">\r\n", body);
        sprintf(body, "%s%s: %s\r\n", body, errnum, shortmsg);
        sprintf(body, "%s<p>%s: %s\r\n", body, longmsg, cause);
        sprintf(body, "%s<hr><em>HeapDGB web server</em>\r\n", body);

        /*build response header*/
        sprintf(buf, "HTTP/1.0 %s %s\r\n", errnum, shortmsg);
        sprintf(buf, "%sContent-type: text/html\r\n", buf);
        sprintf(buf, "%sContent-length: %d\r\n", buf, (int)strlen(body));
		sprintf(response, "%s\r\n%s", buf, body);
        WEBSERVER_DEBUG("response:" << std::endl << response);
        HeapDBG::Util::iwrite(fd, response, strlen(response));
    }


} // WebServer
} // namespace HeapDBG

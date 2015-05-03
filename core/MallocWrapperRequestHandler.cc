#include "log.h"
#include "util.h"
#include "MallocWrapperRequestHandler.hh"

extern "C" void generateHTML(char body[], size_t n);
namespace HeapDBG {
namespace Core {

	void MallocWrapperRequestHandler::generateResponse(int fd)
	{
        //WEBSERVER_DEBUG("enter WebRequestHandler::generateResponse");
        char buf[MAXLINE] = {0}, body[MAXBUF] = {0}, response[MAXBUF+MAXLINE] = {0};
        /*build the body*/
		generateHTML(body, MAXBUF);


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

} // Core
} // HeapDBG


#include <iostream>
#include "WebServer.hh"

void printUsage(const char *filename)
{
    std::cout << "The usage for this tool: " << filename << " [-n hostname] [-p portnum] [-v ipversion] [-t socktype] [-h help]" << std::endl;
    std::cout << "                         " << "hostname : " << "[]" << std::endl;
    std::cout << "                         " << "portnum  : " << "[]" << std::endl;
    std::cout << "                         " << "ipversion: " << "[4|6] " << std::endl;
    std::cout << "                         " << "socktype : " << "[TCP|UDP] " << std::endl;
    std::cout << "                         " << "help     : " << "[print this help info] " << std::endl;
}
void printSetting(const char *hostname, const char *portnum, const int ipversion, const int socktype)
{
    std::cout << " The setting for the server is: " << std::endl;
    std::cout << "                     hostname : " << hostname << std::endl;
    std::cout << "                     portnum  : " << portnum << std::endl;
    if(ipversion == AF_INET6)
        std::cout << "                     ipversion: " << "6" << std::endl;
    else
        std::cout << "                     ipversion: " << "4" << std::endl;
    if(socktype == SOCK_DGRAM)
        std::cout << "                     socktype : " << "UDP" << std::endl;
    else
        std::cout << "                     socktype : " << "TCP" << std::endl;
}
//const char *HOSTNAME = "localhost";
//const char *PORTNUM = "5050";
#define HOSTNAME "localhost"
#define PORTNUM "7676"
int main(int argc, char *argv[])
{
    const char *hostname = HOSTNAME;
    const char *portnum = PORTNUM;
    int ipversion = AF_INET;
    int socktype = SOCK_STREAM;

    char ch = 0;
    const char *optstring = ":hn:p:v:t:";
    while((ch = getopt(argc, argv, optstring)) != -1)
    {
        switch(ch)
        {
            case 'h':
                printUsage(argv[0]);
                return 0;
            case 'n':
                hostname = optarg;
                break;
            case 'p':
                portnum = optarg;
                break;
            case 'v':
                if(optarg[0] == '6')
                    ipversion = AF_INET6;
                break;
            case 't':
                if(optarg[0] == 'U')
                    socktype = SOCK_DGRAM;
                break;
            default:
                std::cout << "not support option: " << (char)optopt << std::endl;
                printUsage(argv[0]);
                return -1;
        }

    }
    printSetting(hostname, portnum, ipversion, socktype);

    try
    {
        HeapDBG::WebServer::WebServer webServer(hostname, portnum, ipversion, socktype);

        //server.printAllAvaiableAddrinfo();
        int ret = webServer.start();
        if (!ret)
        {
            return -1;
        }
    }
    catch(...)
    {
        std::cerr << " server create failed ! " << std::endl;
        return -1;
    }

}


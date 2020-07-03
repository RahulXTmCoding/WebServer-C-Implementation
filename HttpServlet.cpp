#include <cstdint>
#include<string.h>
#include<stdlib.h>
#include <thread> 
#include <sys/socket.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/sendfile.h>
 #include <sys/uio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include<arpa/inet.h>	
#include <netinet/in.h>
#include <netdb.h> 
#include "header.cpp"
#include <map>
#include <iostream>
#include <unistd.h>
#include <sstream>
#include <memory>
class HttpServer
{
private:
int serverSocketDescriptor;
int bindState;
struct sockaddr_in serverAddress;
struct sockaddr_in clientAddress;
int clientAddressLength;

int clientSocketDescriptor;
int clientSocketPortNumber;
struct in_addr clientIPAddress;
char *clientIP;


public:
HttpServer(char *arg)
{
serverSocketDescriptor=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
if(serverSocketDescriptor<0)
{
printf("Unable to create socket\n");

return;
}
printf("Server Socket created\n");
serverAddress.sin_family=AF_INET;
serverAddress.sin_port=htons(atoi(arg));
serverAddress.sin_addr.s_addr=htonl(INADDR_ANY);
bindState=bind(serverSocketDescriptor,(struct sockaddr *)&serverAddress,sizeof(struct sockaddr));
if(bindState<0)
{

printf("Unable to bind socket to ");
printf(arg);
printf("\n");


return;
}
}
void listenMode()
{
listen(serverSocketDescriptor,SOMAXCONN);
printf("Server is in listening mode\n");
clientAddressLength=sizeof(clientAddress);
}
int acceptClient()
{
	return accept(serverSocketDescriptor,(struct sockaddr*)&clientAddress,(socklen_t*)&clientAddressLength);
}

~HttpServer()
{

}
void closeServer()
{
	close(serverSocketDescriptor);
}
void doGet()
{


}


};
#include<stdio.h>
#include <string>
#include "httpServlet.cpp"
#include "HttpRequestProcessor.cpp"
#include <stdexcept>
using namespace std;
int main(int no,char *arg[])
{
HttpServer *server;
server=HttpServer::getInstance();
thread *t;
server.listenMode();
while(1)
{
int clientSocketDescriptor=server.acceptClient();
if(clientSocketDescriptor<0)
{
printf("Client connected, but unable to accept client\n");
continue;
}
t=new thread(HttpRequestProcessor::handleClient,clientSocketDescriptor);
}
server.closeServer();
return 0;
}
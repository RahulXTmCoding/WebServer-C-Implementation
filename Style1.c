#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<string.h>
#include "header.cpp"
int main()
{
int winsock;
WORD winsockversion;
WSADATA data;
winsockversion=MAKEWORD(1,1);
winsock=WSAStartup(winsockversion,&data);
if(winsock!=0)
{
printf("unable to initialize the driver");
return 0;
}
int serverDescriptor=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
if(serverDescriptor<0)
{
printf("unable to create socket\n");
WSACleanup();
return 0;
}
struct sockaddr_in serverAddress;
struct sockaddr_in clientAddress;
serverAddress.sin_family=AF_INET;
serverAddress.sin_port=htons(7500);
serverAddress.sin_addr.s_addr=htonl(INADDR_ANY);
int bindState=bind(serverDescriptor,(struct sockaddr*)&serverAddress,sizeof(serverAddress));
if(bindState<0)
{
printf("unable to bind\n");
WSACleanup();
return 0;
}
int clientDescriptor;
int clientAddressLength;
char request[1024];
char response[1024];
listen(serverDescriptor,SOMAXCONN);
printf("listening mode.........\n");
while(1)
{

clientDescriptor=accept(serverDescriptor,(struct sockaddr*)&clientAddress,&clientAddressLength);
if(clientDescriptor<0)
{
printf("unable to accept the client \n");
continue;
}
int readSize=recv(clientDescriptor,request,sizeof(request),0);
if(readSize<0)
{
printf("unable to read data\n");
closesocket(clientDescriptor);
continue;

}

request[readSize]='\0';



Header h;
h.setHeaderVersion("1.1");
h.setStatusCode("200");
h.setStatusMessage("OK");
h.setContent_Type("text/plane");
char *c;
itoa(strlen("Hello World"),c,10);
h.setContent_Length(c);
sprintf(response,"%s%s",h.getHeader(),"Hello World");

printf("%s\n",response);


int sendByte=send(clientDescriptor,response,strlen(response),0);
if(sendByte<=0)
{
printf("unable to send data\n");
closesocket(clientDescriptor);
continue;
}
printf("data SEnd\n");

closesocket(clientDescriptor);
}
closesocket(serverDescriptor);
return 0;
}
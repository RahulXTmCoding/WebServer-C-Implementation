#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<windows.h>
#include "header.cpp"
int main()
{
int winsockState;
WORD winsockVersion;
WSADATA winsockData;
int serverSocketDescriptor;
int bindState;
struct sockaddr_in serverAddress;
struct sockaddr_in clientAddress;
int clientAddressLength;
char requestBuffer[1024];
int bytesReceived;
char responseBuffer[1024];
int bytesSent;
int clientSocketDescriptor;
int clientSocketPortNumber;
struct in_addr clientIPAddress;
char *clientIP;
winsockVersion=MAKEWORD(1,1);
winsockState=WSAStartup(winsockVersion,&winsockData);
if(winsockState!=0)
{
printf("Unable to initialize winsock library\n");
return 0;
}
printf("Winsock Library Initialized\n");
serverSocketDescriptor=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
if(serverSocketDescriptor<0)
{
printf("Unable to create socket\n");
WSACleanup();
return 0;
}
printf("Server Socket created\n");
serverAddress.sin_family=AF_INET;
serverAddress.sin_port=htons(7500);
serverAddress.sin_addr.s_addr=htonl(INADDR_ANY);
bindState=bind(serverSocketDescriptor,(struct sockaddr *)&serverAddress,sizeof(struct sockaddr));
if(bindState<0)
{
printf("Unable to bind socket to 7500\n");

WSACleanup();
return 0;
}
while(1)
{
listen(serverSocketDescriptor,SOMAXCONN);
printf("Server is in listening mode\n");
clientAddressLength=sizeof(clientAddress);
clientSocketDescriptor=accept(serverSocketDescriptor,(struct sockaddr
*)&clientAddress,&clientAddressLength);
if(clientSocketDescriptor<0)
{
printf("Client connected, but unable to accept client\n");
continue;
}
printf("Client connected\n");
memcpy(&clientIPAddress,&clientAddress.sin_addr.s_addr,4);
clientIP=inet_ntoa(clientIPAddress);
clientSocketPortNumber=ntohs(clientAddress.sin_port);
printf("Client IP %s, connected on port %d\n",clientIP,clientSocketPortNumber);
bytesReceived=recv(clientSocketDescriptor,requestBuffer,sizeof(requestBuffer),0);
if(bytesReceived<0)
{
printf("Unable to extract request data\n");
closesocket(clientSocketDescriptor);
continue;
}
printf("Byte received %d\n",bytesReceived);
requestBuffer[bytesReceived]='\0';
printf("Request data %s\n",requestBuffer);

char requestParse[1024];
int i=0;
while(requestBuffer[i]!='\n')
{
requestParse[i]=requestBuffer[i];
i++;
}
requestParse[i]='\0';
printf(" parsed request header::%s \n",requestParse);

char *p[3];

char *token = strtok(requestParse, " "); 
 i=0;  
    // Keep printing tokens while one of the 
    // delimiters present in str[]. 
    while (token != NULL) 
    { 
     
     p[i]=token;
      i++;   
        token = strtok(NULL, " "); 
    }

for(i=0;i<3;i++)
{

printf("%s\n",p[i]);
} 



Header h;
h.setHeaderVersion("1.1");
h.setStatusCode("200");
h.setStatusMessage("OK");
h.setContent_Type("text/plane");
char c[1024];
itoa(strlen("Hello World\0"),c,10);
h.setContent_Length(c);
sprintf(responseBuffer,"%s%s",h.getHeader(),"Hello World");

printf("%s\n",responseBuffer);
bytesSent=send(clientSocketDescriptor,responseBuffer,strlen(responseBuffer),0);
printf("Response %s of %d bytes sent\n",responseBuffer,bytesSent);
closesocket(clientSocketDescriptor);
}
closesocket(serverSocketDescriptor);
WSACleanup();
return 0;
}
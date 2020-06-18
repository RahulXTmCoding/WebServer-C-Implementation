#include<stdio.h>
#include <cstdint>
#include<string.h>
#include<stdlib.h>
#include <thread> 
#include <windows.h>
#include "header.cpp"
#include <map>
#include <iostream>
#include <mysql_connection.h>
#include <mysql_driver.h>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <sstream>
#include <memory>
#include <string>

#include <stdexcept>
using namespace std;

using namespace sql;
using namespace sql::mysql;



void doPost(char *p,char *qs,char *data)
{}
void doGet(char* p,char *data)
{
map<char*,char*> requestBag;
int i;
char line[1024];
char urlPart[1024];
char qsPart[1024];
i=0;
while(i<strlen(p))
{
if(p[i]=='?'||p[i]=='\n'||p[i]=='\0')
{
break;
}
urlPart[i]=p[i];
i++;

}
urlPart[i]='\0';
printf("%s\n",urlPart);
int j=0;
if(p[i]=='?')
{
i++;
printf("%s\n",urlPart);
while(i<strlen(p))
{
if(p[i]=='\0'||p[i]=='\n')
{
break;
}
qsPart[j]=p[i];
i++;
j++;
}
}
qsPart[j]='\0';

printf("%s\n",qsPart);

if(strcmp(urlPart+(strlen(urlPart)-5),"/save")==0)
{
int l=strlen(qsPart);
for(int i=0;i<l;i++)
{
char *var;
char* val;
var=(qsPart+i);
while(i<l)
{

if(qsPart[i]=='=')
{
qsPart[i]='\0';
break;
}
i++;
}

i++;


val=(qsPart+i);


while(i<l)
{

if(qsPart[i]=='&'||qsPart[i]=='\0')
{
qsPart[i]='\0';
break;
}
if(qsPart[i]=='+')
{
qsPart[i]=' ';
}
i++;
}


requestBag.insert({var,val});
printf("%s      %s\n",var,val);


}

strcpy(data,"<!DOCTYPE html><html lang='en><head><meta charset='utf-8'><title>My first web application</title></head><body><h3>Data Saved</h3><form action='/one.com'><button type='submit'>Ok</button></form></body></html>");
}
else{
if(urlPart[strlen(urlPart)-1]=='/')
{
strcat(urlPart,"index.html");
}
else
if(strcmp(urlPart+(strlen(urlPart)-5),".html")!=0)
{
strcat(urlPart,"/index.html");
}

printf("%s\n",urlPart);
FILE *f;
f=fopen(urlPart+1,"r");
if (f == NULL)
{
printf("Unable to find file\n");
}
strcpy(data,"");
while(fgets(line,1024,f))
{

strcat(data,line);
printf("%s\n",line);
strcat(data,"\n");

}
}



}










char * processRequest(char* requestBuffer)
{
char requestParse[1024];
char *data=(char *)malloc(sizeof(char)*30000);

char *qs=(char *)malloc(sizeof(char)*1024);
int i=0;
while(requestBuffer[i]!='\n')
{
requestParse[i]=requestBuffer[i];
i++;
}
requestParse[i]='\0';
int z=0;
while(i<strlen(requestBuffer))
{
if(requestBuffer[i]=='\n')
{
qs[z]='\0';
z=0;
i++;

}
qs[z]=requestBuffer[i];
z++;
i++;
}

printf(" parsed request header::%s \n",requestParse);
printf("Query String::%s\n",qs);
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

if(strcmp(p[0],"GET")==0)
{
doGet(p[1],data);
}
else
if(strcmp(p[0],"POST")==0)
{
doPost(p[1],qs,data);
}






return data;
}
void handleClient(int clientSocketDescriptor)
{
char requestBuffer[1024];
int bytesReceived;
char responseBuffer[1024];
int bytesSent;
printf("Client connected\n");

bytesReceived=recv(clientSocketDescriptor,requestBuffer,sizeof(requestBuffer),0);
if(bytesReceived<=0)
{
printf("Unable to extract request data\n");
closesocket(clientSocketDescriptor);
return;
}
printf("Byte received %d\n",bytesReceived);
requestBuffer[bytesReceived]='\0';
printf("Request data %s\n",requestBuffer);


char *response=processRequest(requestBuffer);

Header h;
h.setHeaderVersion("1.1");
h.setStatusCode("200");
h.setStatusMessage("OK");
h.setContent_Type("text/html");
char c[1024];
itoa(strlen(response),c,10);
h.setContent_Length(c);
sprintf(responseBuffer,"%s\n%s",h.getHeader(),response);

printf("%s\n",responseBuffer);
bytesSent=send(clientSocketDescriptor,responseBuffer,strlen(responseBuffer),0);
printf("Response %s of %d bytes sent\n",responseBuffer,bytesSent);
closesocket(clientSocketDescriptor);



}





int main()
{


sql::mysql::MySQL_Driver *d;
try{
d = sql::mysql::get_driver_instance();
}catch(SQLException &e){}


int winsockState;
WORD winsockVersion;
WSADATA winsockData;
int serverSocketDescriptor;
int bindState;
struct sockaddr_in serverAddress;
struct sockaddr_in clientAddress;
int clientAddressLength;

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
thread *t;
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
t=new thread(handleClient,clientSocketDescriptor);
}
closesocket(serverSocketDescriptor);
WSACleanup();
return 0;
}
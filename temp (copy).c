#include<stdio.h>
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
#include <string>

#include <stdexcept>
using namespace std;





void doPost(char *p[],char *qs,char *data,int client)
{

	 struct stat stat_buf;
char content[90000];
map<char*,char*> requestBag;
int i;
char line[30000];
char urlPart[30000];
char qsPart[30000];
i=0;
while(i<strlen(p[1]))
{
if(p[1][i]=='?'||p[1][i]=='\n'||p[1][i]=='\0')
{
break;
}
urlPart[i]=p[1][i];
i++;

}
urlPart[i]='\0';
//printf("%s\n",urlPart);
int j=0;
if(p[1][i]=='?')
{
i++;
//printf("%s\n",urlPart);
while(i<strlen(p[1]))
{
if(p[1][i]=='\0'||p[1][i]=='\n')
{
break;
}
qsPart[j]=p[1][i];
i++;
j++;
}
}
qsPart[j]='\0';

//printf("%s\n",qsPart);




Header h;
h.setHeaderVersion("1.1");
h.setStatusCode("200");
h.setStatusMessage("OK");
char ct[1000];

strcat(ct,"");

if(strcmp(p[3],"html")==0||strcmp(p[3],"")==0)
{
strcat(ct,"text/html");
}
else
if(strcmp(p[3],"css")==0)
{
strcat(ct,"text/css");

}
else
if(strcmp(p[3],"js")==0)
{
strcat(ct,"text/javascript");
}
else
if(strcmp(p[3],"jpg")==0||strcmp(p[3],"JPG")==0)
{
strcat(ct,"image/jpeg");

}
else
if(strcmp(p[3],"gif")==0)
{
strcat(ct,"image/gif");

}
else
if(strcmp(p[3],"png")==0)
{
	strcat(ct,"image/png");
}
else
if(strcmp(p[3],"webp")==0)
{
strcat(ct,"image/webp");
}
else
{
strcat(ct,"text/plain");

}

h.setContent_Type(ct);


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
//printf("%s      %s\n",var,val);


}

//header send karo phle
strcpy(content,"<!DOCTYPE html><html lang='en><head><meta charset='utf-8'><title>My first web application</title></head><body><h3>Data Saved</h3><form action='/one.com'><button type='submit'>Ok</button></form></body></html>");
char c[1024];

sprintf(c,"%d",strlen(content));
h.setContent_Length(c);

char* header=h.getHeader();




send(client,header,strlen(header),0);
send(client,content,strlen(content),0);




}
else{
if(urlPart[strlen(urlPart)-1]=='/')
{
strcat(urlPart,"index.html");
}
else
{

if(strcmp(p[3],"")==0)
{
strcat(urlPart,"/index.html");
}

}










//printf("%s\n",urlPart);
int ff=open(urlPart+1,O_RDONLY);
FILE *f;
f=fopen(urlPart+1,"r");
if (f == NULL)
{
printf("Unable to find file\n");
}
else
{
  fseek(f, 0, 2);    /* file pointer at the end of file */

  int size = ftell(f);


char c[1024];

sprintf(c,"%d",size);
h.setContent_Length(c);

char* header=h.getHeader();

//printf("%s",header);


send(client,header,strlen(header),0);
/*
while(!feof(f))
{
fread(line, sizeof(line), 1, f); 

send(client,line,strlen(line),0);

}
*/
fstat (ff, &stat_buf);
sendfile(client,ff,NULL,stat_buf.st_size);

}



}

}
void doGet(char* p[],char *data,int client)
{
	 struct stat stat_buf;
char content[90000];
map<char*,char*> requestBag;
int i;
char line[30000];
char urlPart[30000];
char qsPart[30000];
i=0;
while(i<strlen(p[1]))
{
if(p[1][i]=='?'||p[1][i]=='\n'||p[1][i]=='\0')
{
break;
}
urlPart[i]=p[1][i];
i++;

}
urlPart[i]='\0';
//printf("%s\n",urlPart);
int j=0;
if(p[1][i]=='?')
{
i++;
//printf("%s\n",urlPart);
while(i<strlen(p[1]))
{
if(p[1][i]=='\0'||p[1][i]=='\n')
{
break;
}
qsPart[j]=p[1][i];
i++;
j++;
}
}
qsPart[j]='\0';

//printf("%s\n",qsPart);




Header h;
h.setHeaderVersion("1.1");
h.setStatusCode("200");
h.setStatusMessage("OK");
char ct[1000];

strcat(ct,"");

if(strcmp(p[3],"html")==0||strcmp(p[3],"")==0)
{
strcat(ct,"text/html");
}
else
if(strcmp(p[3],"css")==0)
{
strcat(ct,"text/css");

}
else
if(strcmp(p[3],"js")==0||strcmp(p[3],"htc")==0)
{
strcat(ct,"text/javascript");
}
else
if(strcmp(p[3],"jpg")==0||strcmp(p[3],"JPG")==0)
{
strcat(ct,"image/jpeg");

}
else
if(strcmp(p[3],"gif")==0)
{
strcat(ct,"image/gif");

}
else
if(strcmp(p[3],"png")==0)
{
	strcat(ct,"image/png");
}
else
if(strcmp(p[3],"webp")==0)
{
strcat(ct,"image/webp");
}
else
{
strcat(ct,"text/plain");

}

h.setContent_Type(ct);


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
//printf("%s      %s\n",var,val);


}

//header send karo phle
strcpy(content,"<!DOCTYPE html><html lang='en><head><meta charset='utf-8'><title>My first web application</title></head><body><h3>Data Saved</h3><form action='/one.com'><button type='submit'>Ok</button></form></body></html>");
char c[1024];

sprintf(c,"%d",strlen(content));
h.setContent_Length(c);

char* header=h.getHeader();




send(client,header,strlen(header),0);
send(client,content,strlen(content),0);




}
else{
if(urlPart[strlen(urlPart)-1]=='/')
{
strcat(urlPart,"index.html");
}
else
{

if(strcmp(p[3],"")==0)
{
strcat(urlPart,"/index.html");
}

}










//printf("%s\n",urlPart);
int ff=open(urlPart+1,O_RDONLY);
FILE *f;
f=fopen(urlPart+1,"r");
if (f == NULL)
{
return;
printf("Unable to find file\n");
printf(urlPart+1);
printf("\n");
}
else
{
  fseek(f, 0, 2);    /* file pointer at the end of file */

  int size = ftell(f);


char c[1024];

sprintf(c,"%d",size);
h.setContent_Length(c);

char* header=h.getHeader();

//printf("%s",header);


send(client,header,strlen(header),0);
/*
while(!feof(f))
{
fread(line, sizeof(line), 1, f); 

send(client,line,strlen(line),0);

}
*/
fstat (ff, &stat_buf);
sendfile(client,ff,NULL,stat_buf.st_size);

}



}


}










void processRequest(char* requestBuffer,char *data,int client)
{
char requestParse[10000];


char *qs=(char *)malloc(sizeof(char)*10000);
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

char *p[4];

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

int k=strlen(p[1])-1;
char *type=(char*)malloc(sizeof(char)*1000);
strcpy(type,"");
while(k>=0)
{
if(p[1][k]=='.')
{

strcpy(type,p[1]+k+1);
break;

}
if(p[1][k]=='//'||p[1][k]=='\\') break;
k--;
}
p[3]=type;





/*
for(i=0;i<4;i++)
{

printf("%s\n",p[i]);
} 

*/


if(strcmp(p[0],"GET")==0)
{
doGet(p,data,client);
}
else
if(strcmp(p[0],"POST")==0)
{
doPost(p,qs,data,client);
}
//finding type of request;







}
void handleClient(int clientSocketDescriptor)
{
char requestBuffer[10000];
int bytesReceived;
char responseBuffer[90000];

//(char *)malloc(4000000*sizeof(char));
int bytesSent;
//printf("Client connected\n");

bytesReceived=recv(clientSocketDescriptor,requestBuffer,sizeof(requestBuffer),0);
if(bytesReceived<=0)
{
printf("Unable to extract request data\n");
close(clientSocketDescriptor);
return;
}

requestBuffer[bytesReceived]='\0';



processRequest(requestBuffer,responseBuffer,clientSocketDescriptor);




close(clientSocketDescriptor);



}





int main(int no,char *arg[])
{




int serverSocketDescriptor;
int bindState;
struct sockaddr_in serverAddress;
struct sockaddr_in clientAddress;
int clientAddressLength;

int clientSocketDescriptor;
int clientSocketPortNumber;
struct in_addr clientIPAddress;
char *clientIP;

serverSocketDescriptor=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
if(serverSocketDescriptor<0)
{
printf("Unable to create socket\n");

return 0;
}
printf("Server Socket created\n");
serverAddress.sin_family=AF_INET;
serverAddress.sin_port=htons(atoi(arg[1]));
serverAddress.sin_addr.s_addr=htonl(INADDR_ANY);
bindState=bind(serverSocketDescriptor,(struct sockaddr *)&serverAddress,sizeof(struct sockaddr));
if(bindState<0)
{

printf("Unable to bind socket to ");
printf(arg[1]);
printf("\n");


return 0;
}
thread *t;
listen(serverSocketDescriptor,SOMAXCONN);
printf("Server is in listening mode\n");
clientAddressLength=sizeof(clientAddress);

while(1)
{

clientSocketDescriptor=accept(serverSocketDescriptor,(struct sockaddr*)&clientAddress,(socklen_t*)&clientAddressLength);
if(clientSocketDescriptor<0)
{
printf("Client connected, but unable to accept client\n");
continue;
}
t=new thread(handleClient,clientSocketDescriptor);
}
close(serverSocketDescriptor);

return 0;
}
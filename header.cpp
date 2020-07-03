#include<stdio.h>
class Header
{
private:
char *headerVersion;
char *statusCode;
char *statusMessage;
char *content_type;
char *content_length; 
char header[1024];

public:
void setHeaderVersion(char *headerVersion)
{
this->headerVersion=headerVersion;
}
void setStatusCode(char *statusCode)
{
this->statusCode=statusCode;
}
void setStatusMessage(char *statusMessage)
{
this->statusMessage=statusMessage;
}
void setContent_Type(char* content_type)
{
this->content_type=content_type;
}
void setContent_Length(char* content_length)
{
this->content_length=content_length;
}
char * getHeaderVersion()
{
return this->headerVersion;
}
char * getStatusCode()
{
return this->statusCode;
}
char * getStatusMessage()
{
return this->statusMessage;
}
char * getContent_Type()
{
return this->content_type;
}
char * getContent_Length()
{
return this->content_length;
}
char * getHeader()
{
sprintf(this->header,"HTTP/%s %s %s\r\nContent-Type: %s\r\nContent-Length: %s\r\n\r\n",headerVersion,statusCode,statusMessage,content_type,content_length);

return this->header;
}


};
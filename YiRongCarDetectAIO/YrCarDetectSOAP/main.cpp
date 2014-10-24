// webserver.cpp : Defines the entry point for the console application.
//
#include "YrElecarDetect.nsmap"
#pragma comment(lib,"wsock32.lib")


//�Ӵ˶� ��Ȼ����ʾadd.wsdl
int http_get(struct soap *soap)
{
	FILE*fd = NULL;
	fd = fopen("YrElecarDetect.wsdl", "rb"); //open WSDL file to copy
	if (!fd)
	{
		return 404; //return HTTP not found error
	}
	soap->http_content = "text/xml"; //HTTP header with text /xml content
	soap_response(soap,SOAP_FILE);
	for(;;)
	{
		size_t r = fread(soap->tmpbuf,1, sizeof(soap->tmpbuf), fd);
		if (!r)
		{
			break;
		}
		if (soap_send_raw(soap, soap->tmpbuf, r))
		{
			break; //cannot send, but little we can do about that
		}
	}
	fclose(fd);
	soap_end_send(soap);
	return SOAP_OK;
} 

int main(int argc, char **argv)
{ 
	SOAP_SOCKET m, s; /* master and slave sockets */
	
	struct soap soap;

	soap_init(&soap);

	//�Ӵ��С���Ȼ����ʾWSDL
	soap.fget = http_get;

	if (argc < 2)
	{
		//soap_serve(&soap);	/* serve as CGI application */
		fprintf(stderr, "û�д��˿�\n");
		
		//������л������ʵ��
		soap_destroy(&soap);
		
		//������л�������
		soap_end(&soap);
	}
	else
	{
		    port = atoi(argv[1]);
		   m = soap_bind(&soap, NULL, port, 100);
		if (!soap_valid_socket(m))
		{ 
			soap_print_fault(&soap, stderr);
			exit(-1);
		}
		fprintf(stderr, "Socket connection successful: master socket = %d\n", m);
		for ( ; ; )
		{ 
			s = soap_accept(&soap);
		//	fprintf(stderr, "Socket connection successful: slave socket = %d\n", s);
			fprintf(stderr,"\n�յ�������IP��ַ%d.%d.%d.%d��socket����%d!", 
				(soap.ip >>24)&0xFF, (soap.ip >> 16)&0xFF, (soap.ip >> 8)&0xFF, soap.ip&0xFF, s);

			if (!soap_valid_socket(s))
			{ 
				soap_print_fault(&soap, stderr);
				exit(-1);
			} 
			soap_serve(&soap);
			soap_end(&soap);
		}
	}
	return 0;
} 
/////////////////////////////////////////

int ns__SendMission(struct soap *soap, char *MsgXml, char *ResponseXml)
{ 
	strcpy(ResponseXml,"aaa");
	return SOAP_OK;
} 

int ns__GetServerStatus(struct soap *soap, char *MsgXml, char *ResponseXml)
{ 
	strcpy(ResponseXml,"bbb");
	return SOAP_OK;
} 

int ns__AddCamera(struct soap *soap, char *MsgXml, char *ResponseXml)
{ 

	return SOAP_OK;
} 

int ns__IfCamera(struct soap *soap, char *MsgXml, char *ResponseXml)
{ 

	return SOAP_OK;
} 
int ns__DelCamera(struct soap *soap, char *MsgXml, char *ResponseXml)
{ 

	return SOAP_OK;
} 

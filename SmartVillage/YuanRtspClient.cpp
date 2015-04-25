#include "stdafx.h"
#include "YuanRtspClient.h"



// �ַ��������󳤶�
#define YUAN_MAX_STR_LEN 1024

CYuanRtspClient::CYuanRtspClient(const string &strUrl, int nPort, const string &strIp)
{
	m_strUrl = strUrl;
	m_nPort = nPort;
	m_strIp = strIp;
	m_tcpSocket = INVALID_SOCKET;
	m_nSeq = 0;
}
CYuanRtspClient::~CYuanRtspClient()
{
	CloseSocket();
}
/*
* ��ʼ���׽���
*/
ERTSPERROR CYuanRtspClient::InitSocket(void)
{
	ERTSPERROR eRet = E_RTSP_UNKNOW_ERROR;
	WORD wVersionRequested;
	WSADATA wsaData = {0};
	int nError = 0;

	wVersionRequested = MAKEWORD( 2, 2 );
	nError = WSAStartup(wVersionRequested, &wsaData);
	if (nError != 0)
		return E_RTSP_SOCKET_START_ERROR;
	
	if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2)
	{
		// �汾��ƥ��
		WSACleanup( );
		return E_RTSP_SOCKET_VERSION_ERROR;
	}
	// �Ƿ���Ҫ��ȡip
	if (m_strIp.length() <= 0)
	{
		if (!GetIpFromUrl(m_strUrl))
			return E_RTSP_IP_ERROR;
	}
	m_sockAddr.sin_family = AF_INET;
	m_sockAddr.sin_port =htons(m_nPort);
	m_sockAddr.sin_addr.S_un.S_addr = inet_addr(m_strIp.c_str());
	// m_udpSocketDesc = socket(AF_INET,SOCK_DGRAM,0);
	// �����׽���
	m_tcpSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (INVALID_SOCKET != m_tcpSocket)
		eRet = E_RTSP_SUCCESS;
	return eRet;
}
/*
* ���ӷ����� 
*/
ERTSPERROR CYuanRtspClient::Connect(void)
{
	ERTSPERROR eRet = E_RTSP_UNKNOW_ERROR;
	if(INVALID_SOCKET == m_tcpSocket)
		return eRet;
	int nRet = 0;
	nRet = connect(m_tcpSocket,(const struct sockaddr *)&m_sockAddr,sizeof(struct sockaddr_in));
	if(SOCKET_ERROR != nRet)
		eRet = E_RTSP_SUCCESS;
	else
		eRet = E_RTSP_SOCKET_CONNECT_ERROR;
	return eRet;
}
/*
* �ж��Ƿ����������url
*/
ERTSPERROR CYuanRtspClient::JudgeCorrect(void)
{
	ERTSPERROR eRet = E_RTSP_UNKNOW_ERROR;
	eRet = Connect();
	if (eRet == E_RTSP_SUCCESS)
		eRet = RtstDescribe();
	return eRet;
}
/*
* �ж�rtsp��url�Ƿ�Ϸ���rtsp://10.142.50.239����vlc�ڲ����������˲��Ϸ�)
*/
bool CYuanRtspClient::IsValid(char *url)
{
	bool bRet = false;
	if (url != NULL)
	{
		if (GetIpFromUrl(url))
		{
			if (m_strIp.length() > 0)
			{
				char *p = strstr(url, (char *)m_strIp.c_str());
				if (p != NULL)
				{// �ж�ip�����Ƿ��и�'/'�ļ�·��
					char *q = strchr(p, '/');
					if (q != NULL && strlen(q) > 1)
						bRet = true;
				}
			}
		}
	}
	return bRet;
}
/*
* �ر��׽���
*/
void CYuanRtspClient::CloseSocket(void)
{
	if(m_tcpSocket != INVALID_SOCKET)
	{
		closesocket(m_tcpSocket);
		m_tcpSocket = INVALID_SOCKET;
	}
	WSACleanup();
}
/*
* ����ý������Ϣ 
*/
ERTSPERROR CYuanRtspClient::RtstDescribe(void)
{
	ERTSPERROR eRet = E_RTSP_UNKNOW_ERROR;
	if(INVALID_SOCKET == m_tcpSocket)
		return eRet;
	m_nSeq++;

	char szDescribeCommand[YUAN_MAX_STR_LEN] = {0};
	sprintf(szDescribeCommand, "DESCRIBE %s RTSP/1.0\r\n"
		"CSeq: %d\r\n"
		"Accept: application/sdp\r\n"
		"User-Agent: shawn\r\n"
		"\r\n", (char *)m_strUrl.c_str(), m_nSeq);
	int nRet = 0;
	nRet = send(m_tcpSocket, szDescribeCommand, strlen(szDescribeCommand)+1, 0);
	if(SOCKET_ERROR == nRet)
		return E_RTSP_SOCKET_SEND_ERROR;
	//Sleep(500);
	char szDescribeResponse[YUAN_MAX_STR_LEN] = {0};
	nRet = recv(m_tcpSocket,  szDescribeResponse, sizeof(szDescribeResponse), 0);
	if(SOCKET_ERROR != nRet)
	{
		OutputDebugStringA(szDescribeResponse);
		// �жϷ����Ƿ����
		if (IsGetDescribeCorrect(szDescribeResponse))
			eRet = E_RTSP_SUCCESS;
		else
			eRet = E_RTSP_SERVER_UNAVAILABLE;
	}
	else
		eRet = E_RTSP_SOCKET_REV_ERROR;
	return eRet;
}

/*
* ��url����ȡip 
*/
bool CYuanRtspClient::GetIpFromUrl(const string &strUrl)
{
	bool bRet = false;
	char *url = (char *)strUrl.c_str();
	do 
	{
		// Parse the URL as "rtsp://[<username>[:<password>]@]<server-address-or-name>[:<port>][/<stream-name>]"
		const char *pPrefix = "rtsp://";
		unsigned const c_uPrefixLength = 7;
		if (strUrl.length() < c_uPrefixLength)
			break; 
		char szBuf[10] = {0};
		strncpy(szBuf, (char *)strUrl.c_str(), c_uPrefixLength);
		// ת����Сд��ĸ���бȽ�
		strlwr(szBuf);
		if (strncmp(szBuf, pPrefix, c_uPrefixLength) != 0)
			break;

		const unsigned uParseBufferSize = 1024;
		char szParseBuffer[uParseBufferSize];
		char const* from = &url[c_uPrefixLength];

		// Check whether "<username>[:<password>]@" occurs next.
		// We do this by checking whether '@' appears before the end of the URL, or before the first '/'.
		char *username = NULL;
		char *password = NULL;
		const char *pColonPasswordStart = NULL;
		char const* p;
		for (p = from; *p != '\0' && *p != '/'; ++p) 
		{
			if (*p == ':' && pColonPasswordStart == NULL) 
			{
				pColonPasswordStart = p;
			} else if (*p == '@')
			{
				// We found <username> (and perhaps <password>).  Copy them into newly-allocated result strings:
				if (pColonPasswordStart == NULL)
					pColonPasswordStart = p;

				char const* usernameStart = from;
				unsigned usernameLen = pColonPasswordStart - usernameStart;
				username = new char[usernameLen + 1] ; // allow for the trailing '\0'
				for (unsigned i = 0; i < usernameLen; ++i) 
					username[i] = usernameStart[i];
				username[usernameLen] = '\0';

				char const* passwordStart = pColonPasswordStart;
				if (passwordStart < p)
					++passwordStart; // skip over the ':'
				unsigned passwordLen = p - passwordStart;
				password = new char[passwordLen + 1]; // allow for the trailing '\0'
				for (unsigned j = 0; j < passwordLen; ++j)
					password[j] = passwordStart[j];
				password[passwordLen] = '\0';

				from = p + 1; // skip over the '@'
				break;
			}
		}
		// ��������
		if (username && strlen(username) > 0)
		{
			m_strAdmin = username;
			delete username;
		}
		if (password && strlen(password) > 0)
		{
			m_strPassword = password;
			delete password;
		}
		// Next, parse <server-address-or-name>
		char* to = &szParseBuffer[0];
		unsigned i;
		for (i = 0; i < uParseBufferSize || *from=='\0'; ++i)
		{
			if (*from == '\0' || *from == ':' || *from == '/')
			{
				// We've completed parsing the address
				*to = '\0';
				break;
			}
			*to++ = *from++;
		}
		if (i == uParseBufferSize)
		{
			//	url̫����
			break;
		}
		// ����ip��ַ
		m_strIp = szParseBuffer;
		// �����˿�
		if (*from == ':')
		{// ������Ŷ˿ں�
			char szPort[128] = {0};
			int i = 0;
			while (i < 128 && *from != '/')
			{
				szPort[i] = *from++;
			}
			m_nPort = atoi(szPort);
		}
		bRet = true;
	} while (0);

	return bRet;
}
/*
* �ж�describe������Ϣ�Ƿ���ȷ
*/
bool CYuanRtspClient::IsGetDescribeCorrect(const string &str)
{
	bool bRet = false;
	if (str.length() > 0)
	{
		int nIndex = str.find_first_of('\n');
		if (nIndex > 0)
		{
			// ��ȡ��һ����Ϣ
			string strSub = str.substr(0, nIndex);
			// RTSP/1.0 200 OK
			// RTSP/1.0 503 Service Unavailable	
			// ת��Сд
			int nLen = strSub.length();
			char szTemp[512] = {0};
			if (nLen >= 512)
				return false;
			strcpy(szTemp, (char *)strSub.c_str());
			// ת����Сд��ĸ���бȽ�
			strlwr(szTemp);
			// �Ƿ��ҵ�"Service Unavailable"
			char *q = strstr(szTemp, "unavailable");
			if (q == NULL)
			{
				// �Ƿ��ҵ�"ok"
				char *q = strstr(szTemp, "ok");
				if (q != NULL)
					bRet = true;
			}
		}	
	}
	return bRet;
}
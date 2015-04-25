#ifndef __YUAN_RTSP_CLIENT_H__
#define __YUAN_RTSP_CLIENT_H__

#pragma comment(lib, "ws2_32.lib")

/*
rtsp �ͻ���
ʵ��rtsp���ӵȹ���
*/

/*
�ж�һ��rtsp�Ƿ����ͨ
// �ж�rtsp��ַ�Ƿ��������
// ʹ��urlȥ����һ��CYuanRtspClient����

CYuanRtspClient YuanRtsp("rtsp://35.33.141.131/cam/realmonitor?channel=1&subtype=0");
ERTSPERROR eRet = YuanRtsp.InitSocket();
if (eRet == E_RTSP_SUCCESS)
{
	eRet = YuanRtsp.JudgeCorrect();
	if (eRet == E_RTSP_SUCCESS)
		printf("url����ͨ\n");
	else
		printf("url������ͨ\n"); // ���������Զ�eRet��ֵ�����ж�
}
*/

#include <WinSock2.h>
#include <string>
using namespace std;

// rtsp��Ĭ�϶˿ں�
#define RTSP_PROTOCOL_PORT 554

// ����rtspʱ��һЩ��������
typedef enum tagERTSPERROR
{
	
	E_RTSP_SUCCESS = 0, // ��ȷ
	E_RTSP_SOCKET_START_ERROR, // �����׽���ʧ��
	E_RTSP_SOCKET_VERSION_ERROR, // �׽��ְ汾��ƥ��
	E_RTSP_IP_ERROR, // url�е�ip����
	E_RTSP_SOCKET_ERROR, //�����׽���ʧ��
	E_RTSP_SOCKET_CONNECT_ERROR, // ���ӷ�����ʧ��
	E_RTSP_SOCKET_SEND_ERROR, // socket ����ʧ��
	E_RTSP_SOCKET_REV_ERROR, // socket ����ʧ��
	E_RTSP_SERVER_UNAVAILABLE, // rtsp server������(�����ǵ�ַ����)
	E_RTSP_UNKNOW_ERROR // λ�ô���
}ERTSPERROR;

class CYuanRtspClient
{
public:
	/*
	* strUrl rtsp����˵���ַ
	* nPort socket�Ķ˿ں�
	* strIp ����˵�ip�����������ȥstrUrl����ȡ)
	*/
	CYuanRtspClient(const string &strUrl, int nPort = RTSP_PROTOCOL_PORT, const string &strIp = "");
	~CYuanRtspClient();
	/*
	* ��ʼ���׽���
	*/
	ERTSPERROR InitSocket(void);
	
	/*
	* �ж��Ƿ����������url
	*/
	ERTSPERROR JudgeCorrect(void);
	
private:
	///////////////////////////////////////////
	/*
	* �ر��׽���
	*/
	void CloseSocket(void);
	/*
	* ���ӷ����� 
	*/
	ERTSPERROR Connect(void);
	/*
	* ����ý������Ϣ 
	*/
	ERTSPERROR RtstDescribe(void);
	/*
	* ��url����ȡip 
	*/
	bool GetIpFromUrl(const string &strUrl);
	/*
	* �ж�rtsp��url�Ƿ�Ϸ���rtsp://10.142.50.239����vlc�ڲ����������˲��Ϸ�)
	* ��ʱ��ʹ�ô˽ӿ�
	*/
	bool IsValid(char *url);
	/*
	* �ж�describe������Ϣ�Ƿ���ȷ
	*/
	bool IsGetDescribeCorrect(const string &str);
private:
	string m_strUrl; // rtsp�������ַ
	string m_strIp; // ����˵�ip
	int m_nPort; // socket�˿ں�
	SOCKET m_tcpSocket; // tcp��socket
	struct sockaddr_in m_sockAddr;
	int m_nSeq; // rtsp��CSepֵ
	// �û�����Ϣ��
	string m_strAdmin;
	string m_strPassword;

};

#endif /* __YUAN_RTSP_CLIENT_H__ */
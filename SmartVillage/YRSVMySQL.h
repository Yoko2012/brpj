
#ifndef _YRSV_MYSQL_H_
#define _YRSV_MYSQL_H_

#include <windows.h>
#include <mysql.h>
#pragma comment(lib,"libmysql.lib")

#include <vector>
#include <list>
#include <sstream>
#include <string>

using namespace::std;


#define MAX_FACE_DB_NUM 32
#define RCT_MAX_STR_SIZE 256
//����ʡ��
#define CAR_MASK_MAX 31

//�Ա���
enum SEX_TYPE
{
	SEX_UNKNOW=0,		//δ֪
	SEX_MALE,				//����
	SEX_FEMALE,			//Ů��
};

//�����Ͷ���
enum CARD_TYPE
{
	CARD_UNKNOW=0,				//δ֪
	CARD_GENERATION_ONE,	//һ��֤
	CARD_GENERATION_TWO,	//����֤
	CARD_GAS_CARDIN,			//ʿ��֤
	CARD_STUDENT,					//ѧ��֤
	CARD_DRIVER,					//��ʻ֤
	CARD_PASSPORT,				//����
	CARD_OTHER,						//����
};

//���ᶨ��
enum NATIVE_PLACE_TYPE
{
	NATIVE_Unknow=0,			//δ֪
	NATIVE_BeiJing,				//����
	NATIVE_TianJin,				//���
	NATIVE_ChongQing,			//����
	NATIVE_GuangDong,		//�㶫
	NATIVE_HeiBei,				//�ӱ�
	NATIVE_ShanXi,				//ɽ��
	NATIVE_LiaoNing,			//����
	NATIVE_JiLin,					//����
	NATIVE_HeiLongJiang,	//������
	NATIVE_JiangSu,				//����
	NATIVE_ZheJiang,			//�㽭
	NATIVE_AnHui,					//����
	NATIVE_FuJiang,				//����
	NATIVE_JiangXi,				//����
	NATIVE_ShangDong,			//ɽ��
	NATIVE_HeNan,					//����
	NATIVE_HuBei,					//����
	NATIVE_HuNan,					//����
	NATIVE_HaiNan,				//����
	NATIVE_SiChuan,				//�Ĵ�
	NATIVE_GuiZhou,				//����
	NATIVE_YunNan,				//����
	NATIVE_ShanXi2,				//����
	NATIVE_GanSu,					//����
	NATIVE_QingHai,				//�ຣ
	NATIVE_TaiWan,				//̨��
	NATIVE_XinJiang,			//�½�
	NATIVE_GuangXi,				//����
	NATIVE_NingXia,				//����
	NATIVE_NeiMengGu,			//���ɹ�
	NATIVE_XiZang,				//����
};

//��ʱ¼�Ƽƻ���
struct SET_RECORD_DATA_ST
{
	//���ݿ��NID
	long nid;
	long ncamera;		//����ͷID 
	char area[128];	//����ͷ����
	char name[64];	//����ͷ����
	char ip[32];		//IP��ַ
	
	//�������3������false ���������Ч
	int everyday;	//ʹ��ÿ�� bool 
	int usedate;	//ʹ������ bool	 
	int useweek;	//ʹ��ÿ�� bool
	// ����״̬ ������ִ��¼�ơ������þ�ֻ�Ǳ��� bool
	int enable;
	
	int StartWeek; //0 ���� 1-6 ��һ������
	int EndWeek;	//0 ���� 1-6 ��һ������

	//��ʼʱ��
	int StartYear;	
	int StartMon;
	int StartDay;
	int StartHour;
	int StartMin;
	int StartSec;
	//����ʱ��
	int EndYear;
	int EndMon;
	int EndDay;
	int EndHour;
	int EndMin;
	int EndSec;
};

//��Ƶ¼����Ϣ��
struct HISTORY_VIDEO_ST
{
	long nid;
	long ncamera;		//����ͷID new
	char name[260];	//����ͷ����
	char ip[32];		//IP��ַ
	int venderID;		//����
	char format[8];	//��׺MP4 AVI ��ʽ
	long size;	//�ļ���С
	char path[260];

	//��ʼʱ��
	int StartYear;
	int StartMon;
	int StartDay;
	int StartHour;
	int StartMin;
	int StartSec;
	//����ʱ��
	int EndYear;
	int EndMon;
	int EndDay;
	int EndHour;
	int EndMin;
	int EndSec;
};

//ϵͳ��־��
struct HISTORY_REPORT_ST
{
	//ʱ��
	int year;
	int mon;
	int day;
	int hour;
	int min;
	int sec;

	char user[32];	//�û���
	char str[1024];	//��־��Ϣ
};

//�����
struct DEVICE_AREA_ST
{
	long nid;
	char name[128];
};

//����ͷ��Ϣ��
typedef struct
{
	HTREEITEM Parent_item;		//��ָ��
	HTREEITEM item;						//��ָ��
	long ncamera;
	long areaID;						//new
	char area[128];						//����
	char name[64];						//���������
	char ip[32];
	char user[32];
	char psw[128];
	long port;
	long venderID;			//0---����,1---��
	long channel;
	char Rtspurl[512];	//rtsp����ַ
	long RTP;						//��ý�崫��ģʽ0=RTP-RTSP��1=RTP-UDP
	long DecodeTag;			//��ý������־0=haikang��1=ga_h264
	char longitude[32]; //����
	char latitude[32];	//γ��
	long userID;					//USER��NID
}IPLIST;

struct  DEVICE_SET_CAR_LITE_ST
{
	int redrect;			//��ͼ���ƴ����
	int deskew;				//������бУ��
	int jpgquailty;		//JPGͼƬ����
	int minwidth;			//������С���
	int maxwidth;			//���������
	int left;					//�������-��
	int right;				//�������-��
	int top;					//�������-��
	int bottom;				//�������-��
	char defaultchar[32];	//Ĭ��ʡ��
	int reliability;	//�������Ŷ�NRELIABILITY
	int carlor;				//������ɫʶ��
	unsigned char mask[CAR_MASK_MAX];	//���ֽ϶��ʡ��
};

struct  DEVICE_SET_FACE_LITE_ST
{
	//FaceProcess �������ʱ��
	int minface;			//��С�����ߴ� SDK��С�ߴ� 32*32=1024
	int maxface;			//��������ߴ� SDK��С�ߴ� 240*240=57600
	float frontface_ts;		//���淧ֵ  0.5  [0-1.0]
	float sideface_ts;		//���淧ֵ  0.5  [0-1.0]

	//RecoVideo
	int time_out;			//ȥ��ʱ�� ��   30
	float scale_ratio;		//���ű�        1.0
	int video_ts;			//���ط�ֵ		50 [1-100] 
 
	//RecoFaceMng ��������� ������ⱨ���ȶ�ʱ ��
	int threshold;			//��С���ƶȷ�ֵ	50 [1-100] 
	int maxcount;			//���ƥ����		10

	int dbTotal;			//���ò�������
	long db_nid[MAX_FACE_DB_NUM];		//���ò��ؿ�ID

};

//����ͷ�������ñ�
struct DEVICE_SET_ST
{
	long nid;				//���к�
	long ncamera;		//����ͷid
	int svmode;				//���ܷ���ģʽ 0=����ʶ��1=����ʶ��
	int width;				//��Ƶͼ���
	int hight;				//��Ƶͼ���

	struct  DEVICE_SET_FACE_LITE_ST face;
	struct  DEVICE_SET_CAR_LITE_ST car;
};

//�û���
struct SET_USER_LIST_ST
{
	long nid;
	char user[128];
};

//�û���  �û���Ϣ
struct SET_USER_DATA_ST
{
	long nid;
	char user[128];
	char psw[128];
	
	//Ȩ��
	int admin;//����ԱȨ��
	int	systemset;//ϵͳ����
	int	recordset;//¼������
	int	record;//¼��
	int	ptz;//��̨
	int	preview;//Ԥ��
	int	historyvideo;//��ʷ��Ƶ��ѯ
	int	historyreport;//ϵͳ��־��ѯ
	int	historydetect;//��ʷʶ���ѯ
	int	historyalarm;//��ʷ������ѯ
	int	device;//�豸����
	int	blackset;//���ƺ���������
	int	capbmp;//ץ��
	int	Cardetect;//����ʶ�𱨾�
	int	CarDetectset;//����ʶ������
	int Facedetect;//����ʶ��
	int FaceDetectset;//����ʶ������
};

//����ʶ������ͱ�����
struct HISTORY_CarDetect_ST
{
	long nid;
	long ncamera;				//����ͷ���
	char area[64];				//��������
	char name[32];				//����ͷ����
	char ip[32];					//IP��ַ
	
	char plate[32];//���ƺ�
	char platecolor[32];//������ɫ
	char platetype[32];//��������
	char direction[32];//���Ʒ���
	char carcolor[32];//������ɫ
	int reliability;//���Ŷ�
	
	//����ʱ��DGETTIME
	int year;
	int mon;
	int day;
	int hour;
	int min;
	int sec;

	int nflag;						//��ʶ
	char path[260];				//�ļ�·��
	long picsize;					//ͼ���С
	char smallpath[260];	//������Ƭ·�� new
	long smallsize;				//������Ƭ��С new
	long blackid;				//������ID
};

//������������
struct BLACK_DATA_ST
{
	long nid;						//���к�
	char plate[32];				//���ƺ�
	char brand[32];				//Ʒ��
	char name[32];				//ʧ������
	char Phone[32];				//��ϵ�绰
	char other[1024];			//������Ϣ
};

//�������ؿ���Ϣ��
struct FACE_DB_ST
{
	long	nid;		//���к�
	char dbname[32];	//���ؿ�����
	long	RW_dbID;			//���ؿ�ID
};

//��Ա������Ϣ��
struct PERSON_BLACK_ST
{
	long	nid;					//���к�
	long	db_nid;				//�����к�
	long	RW_dbID;			//���ؿ�ID
	long	RW_personID;	//������ԱID
	char name[32];				//����

	//��������
	int year;
	int mon;
	int day;
	
	int sex;					//�Ա�  0--δ֪  1--����  2--Ů��
	char phone[32];		//�绰
	int	cardtype;			//֤������
	char cardNO[32];		//֤����
	int native;				//����
	char address[512];//��ַ
};

//����������Ϣ��
struct FACE_BLACK_ST
{
	long	nid;								//���к�
	long	person_black_nid;		//������Ա�����к�
	long	RW_faceID;					//����ID
	long	RW_personID;				//������ԱID
	char file[260];							//��Ƭ·��
	long size;									//��Ƭ��С
	char face[260];
	long facesize;
};

//��ʱ���ؿ���Ϣ��
struct FACE_TEMP_DB_ST
{
	long nid;			//���к�
	char name[64];	//���������
	long RW_tempID;	//��ʱ��ID
	long ncamera;		//�����ID
};

//����ץ�ı�
struct FACE_CAPTURE_ST
{
	long nid;			//���к�
	int sex;			//�Ա�
	int	age;				//����
	int	facetype;		//������
	int	quality;		//��Ƭ����
	char file[260];	//�ֳ���Ƭ·��
	int	size;				//�ֳ���Ƭ��С
	char face[260];	//С ����ͼƬ·��
	int	facesize;		//С ����ͼƬ��С
	int	isblack;		//������־
	long	ncamera;	//����ͷ���
	char cameraName[64];	//����ͷ����
	char sip[32];		//����ͷIP
	int	deal;				//�Ƿ��ѱȶԴ����־	
	
	//����ʱ��DGETTIME
	int year;
	int mon;
	int day;
	int hour;
	int min;
	int sec;
	
	long temp_db_nid;	//ץ�Ŀ����к�
	long RW_tempID;		//��ʱ��ID
	long RW_personID;	//��ʱ��ԱID
	long RW_faceID;		//����ID
};

//����������
struct FACE_ALARM_ST
{
	long nid;					//���к�
	long captureID;		//ץ�ı�ID
	long db_nid;		//tb_face_db��NID
	long RW_dbID;			//������ID
	long RW_personID;	//������ԱID
	long RW_faceID;		//����ID ����һ��ͼƬ
	int similarity;			//���ƶ�
	long ncamera;
	char cameraName[64];	//����ͷ����
	char sip[32];		//����ͷIP
};

//================================��ͼ===============================///
//����������ͼ��Ϣ
struct FACE_ALARM_VIEW_ST
{
	long captureID;		//ץ�ı�ID
	long db_nid;		//tb_face_db��nid
	long	person_black_nid;	
	long RW_dbID;			//������ID
	long	RW_personID;	//������ԱID
	long RW_faceID;		//����ID
	
	char dbname[32];			//���ؿ�����
	char name[32];				//����
	//��������
	int year;
	int mon;
	int day;
	int sex;						//�Ա�  0--δ֪  1--����  2--Ů��
	char phone[32];			//�绰
	int	cardtype;				//֤������
	char cardNO[32];			//֤����
	int native;					//����
	char address[512];	//��ַ	
	char file[260];		//����ԭʼͼƬ
	int size;
	char face[260];	//������Ƭ
	int facesize;		//��Ƭ��С
	int similarity;			//���ƶ�
	long	ncamera;	//����ͷ���
	char cameraName[64];	//����ͷ����
	char sip[32];		//����ͷIP
};

//ConnectionOracleDB ���ݿ����Ӻ��� ����ֵ ����
#define ReadFile_FAIL -1	//�����ļ���ʧ��
#define MySQLInit_FAIL -2	//mysql��ʼ������
#define ContOpen_FAIL -3	//���ݿ��޷�����
#define Connectd_DONE 1		//���ݿ����ӳɹ�	

class CYRSVMySQL
{
public:
	TCHAR Ip[64];
	TCHAR Port[64];
	TCHAR User[128];
	TCHAR Psw[128];
	TCHAR DataBaseName[128];

	MYSQL myConnection;		//MySQL ���Ӷ���
	MYSQL *mysql_handle;
	bool m_bConnection;		//���ӱ�־
	bool IOwriteLock;

public:
	CYRSVMySQL(void);
	~CYRSVMySQL(void);

	void DeCode(char *src,char *dst);				//����
	bool ReadFile(char* FileName);					//�����ݿ������ļ�
	void filterstring(char *str);					//ȥ���������ݿ�ʱ���ֵ�����
	int ConnectionMySQL(char* FileName);			//�������ݿ�
	void DisConnectionMySQL(void);					//�Ͽ�����
	void VarSaveString(char *dst,char *src);		//�����ֶ�Ϊ�ַ���
	long VarSaveNumber(char *src);		//�����ֶ�Ϊ����
	void StrSaveArray(char *src,long *dst);			//���ؿ��ַ���ת��������
	void ArraySaveStr(long *src,long count,char *dst);
	void UCHARSaveCHAR(unsigned char *src,long count,char *dst);
	void StrReplace(char*src, char*sub, char*dst);

	/**************************�����*******************************/
	bool DEVICE_GetAreaID(long &nid,char *AreaName);							//��ȡ����ID���������ж������Ƿ����
	bool DEVICE_AddNewArea(char *AreaName);										//��������
	bool DEVICE_DeleteArea(long areaID);										//ɾ������
	bool DEVICE_ReadAllOrgName(vector<struct DEVICE_AREA_ST>& DeviceAreaList);	//��ȡ���е�����
	bool DEVICE_UpdateAreaInfo(long areaID,char *AreaName);						//�޸���������

	/**************************�豸��*******************************/
	bool DEVICE_GetCameraID(long &nid,long areaID,char *name);					//��ȡ�豸ID���������ж��豸�Ƿ����
	bool DEVICE_AddNewCamera(long &ncamera,IPLIST CamInfo);						//�����豸
	bool DEVICE_ReadCameraInfo(long areaID,vector<IPLIST>& CameraList);			//��ĳ���������е��豸��Ϣ
	bool DEVICE_DeleteCamera(long cameraID);									//ɾ�������
	bool DEVICE_DeleteCameraWithAreaID(long AreaID);							//ɾ��ĳ����������������
	bool DEVICE_UpdateCameraInfo(IPLIST CamInfo);								//�����豸��Ϣ
	bool DEVICE_JudgeCamera(long ncamera);										//�ж��豸�Ƿ����
	bool DEVICE_GetCameraWithAreaID(long AreaID,list<long> &ncameraList);		//��ȡĳ�������µ����������ID
	bool DEVICE_ReadCameraInfoFromCamID(long ncamera,IPLIST &CamInfo);			//����nid��ȡ�������Ϣ
	bool DEVICE_ReadCameraInfoFromCarDetectID(long CarDetectID,IPLIST &CameraInfo);	//����

	/**************************�û���*******************************/
	bool USER_UserNameJudge(long &nid,char *userName);					//�ж��û����Ƿ����
	bool USER_AddNewUser(struct SET_USER_DATA_ST UserInfo);				//�����û���Ϣ
	bool USER_DeletetUser(long nid);									//ɾ���û���Ϣ
	bool USER_UpdateUserInfo(struct SET_USER_DATA_ST UserInfo);			//�༭�û���Ϣ
	bool USER_ReadUserInfoWithName(char *user,struct SET_USER_DATA_ST *UserInfo);
	bool USER_ReadUserInfoWithNid(long nid,struct SET_USER_DATA_ST *UserInfo);
	bool USER_ReadAllUserInfo(list<struct SET_USER_LIST_ST> &UserList);

	/**************************ϵͳ��־��*******************************/
	bool LOG_AddNewSystemLog(char *userName,char *logStr);				//����ϵͳ��־
	long LOG_GetSystemLogNum(char *userName,char *startTime,char *endTime,int flag,char *SQLstr);
	bool LOG_ReadSystemLog(char *SQLstr,int flag,long startNum,long endNum,list<struct HISTORY_REPORT_ST> &HistoryList);

	/**************************���������������*******************************/
	bool CAR_MatchResult_AddNewNoPicData(bool &isblack,long &nid,long &blackID,struct HISTORY_CarDetect_ST carInfo);
	bool CAR_Black_Compare(bool &isblack,long &blackID,char *carNum);//�ڲ�����
	bool CAR_AlarmResult_AddNewNoPicData(struct HISTORY_CarDetect_ST carInfo);
	long CAR_MatchResult_GetNum(char *CamName,char *sip,char *plate,char *startTime,char *endTime,
		char *direction,char *platecolor,char *platetype,char *carcolor,int flag,char *SQLstr);
	long CAR_AlarmResult_GetNum(char *CamName,char *sip,char *plate,char *startTime,char *endTime,
		char *direction,char *platecolor,char *platetype,char *carcolor,int flag,char *SQLstr);
	bool CAR_MatchResult_Read(char *SQLstr,int flag,long startNum,long endNum,list<struct HISTORY_CarDetect_ST> &HistoryList);
	bool CAR_AlarmResult_Read(char *SQLstr,int flag,long startNum,long endNum,list<struct HISTORY_CarDetect_ST> &HistoryList);
	long CAR_MatchResult_Count(long CAMID,char *startTime,char *endTime);//ͳ�Ʒ���
	bool CAR_MatchResult_ReadforListOne(long nid,struct HISTORY_CarDetect_ST &CarData);
	bool CAR_AlarmResult_ReadforListOne(long nid,struct HISTORY_CarDetect_ST &CarData);

	/**************************������������*******************************/
	bool CAR_BlackTable_AddNew(struct BLACK_DATA_ST BlackInfo);
	bool CAR_BlackTable_DeleteWithNid(long nid);
	bool CAR_BlackTable_Edit(struct BLACK_DATA_ST BlackInfo);
	long CAR_BlackTable_GetNum(void);
	bool CAR_BlackTable_Read(long startNum,long endNum,list<struct BLACK_DATA_ST> &BlackList);
	bool CAR_BlackTable_ReadOne(long Num,struct BLACK_DATA_ST &black);
	bool CAR_BlackTable_DeleteAll(void);
	bool CAR_Alarm_DeleteAll(void);
	bool CAR_Alarm_DeleteWithBlackNid(long blackid);
	bool CAR_BlackTable_ReadOneWithNid(long Nid,struct BLACK_DATA_ST &black);

	/**************************�������ؿ���Ϣ��*******************************/
	bool FACE_BlackDB_AddNew(long &nid,struct FACE_DB_ST faceDB);
	bool FACE_BlackDB_ReadAll(list<struct FACE_DB_ST> &FaceDBList);
	bool FACE_BlackDB_Edit(struct FACE_DB_ST faceDB);
	bool FACE_BlackDB_DeleteWithNid(long nid);
	bool FACE_BlackDB_GetRWID(long nid,long &RW_dbID);//��ȡ��Ϊ��ID
	
	/**************************��Ա������Ϣ��*******************************/
	long FACE_BlackPerson_GetNum(long DBID);
	bool FACE_BlackPerson_Read(long DBID,long startNum,long endNum,list<struct PERSON_BLACK_ST> &BlackList);//��ȡĳ�����ؿ��µ�������Ա
	bool FACE_BlackPerson_ReadOne(long nid,struct PERSON_BLACK_ST &black);
	bool FACE_BlackPerson_AddNew(long &personID,struct PERSON_BLACK_ST black);
	bool FACE_BlackPerson_Edit(struct PERSON_BLACK_ST black);
	bool FACE_BlackPerson_DeleteWithNid(long nid);
	bool FACE_BlackPerson_DeleteWithDBID(long dbID);
	bool FACE_BlackPerson_CmpRead(struct PERSON_BLACK_ST &black,char *name,int sex,char *sage,char *eage,int cardtype,char *cardNO,
										  char *phone,int native,char *address,int flag,long db_id,long RW_DBID,long RW_PersonID);
	
	/**************************����������Ϣ��*******************************/
	bool FACE_BlackFace_Read(long PersonID,list<struct FACE_BLACK_ST> &FaceList);//������ԱID��ȡ������Ա����������
	bool FACE_BlackFace_AddNew(struct FACE_BLACK_ST face);
	bool FACE_BlackFace_Update(struct FACE_BLACK_ST face);
	bool FACE_BlackFace_DeleteWithNid(long nid);
	bool FACE_BlackFace_DeleteWithPersonID(long personID);
	bool FACE_BlackFace_ReadWithRWfaceID(long RW_faceID,long RW_personID,struct FACE_BLACK_ST &face);
	bool FACE_Black_Read_PersonAndFace(long faceID,long personID,struct PERSON_BLACK_ST &person,struct FACE_BLACK_ST &face);
	bool FACE_Black_Read_DetailBlack(long faceID,long personID,struct FACE_ALARM_VIEW_ST &alarmInfo);

	/**************************����ͷ�������ñ�*******************************/
	bool DEVICE_SetTable_AddNew(long ncamera);//�������ͷ�������ã����������ͷ��ʱ����ô˺������Ĭ������
	bool DEVICE_SetTable_Read(long ncamera,struct DEVICE_SET_ST &CamSet);
	bool DEVICE_SetTable_Update(struct DEVICE_SET_ST CamSet);
	bool DEVICE_SetTable_DeleteWithCamID(long ncamera);

	/**************************��ʱ���ؿ���Ϣ��*******************************/
	bool TEMP_DB_AddNew(struct FACE_TEMP_DB_ST tempDB);//�������ͷ��ʱ���ؿ⣬���������ͷ��ʱ����ô˺������Ĭ������
	bool TEMP_DB_ReadAll(list<struct FACE_TEMP_DB_ST> &TempDBList);
	bool TEMP_DB_Read(long ncamera,struct FACE_TEMP_DB_ST &tempDB);
	bool TEMP_DB_UpdateWithNcamera(struct FACE_TEMP_DB_ST tempDB);
	bool TEMP_DB_DeleteWithNcamera(long ncamera);
	bool TEMP_DB_Update(struct FACE_TEMP_DB_ST tempDB);
	bool TEMP_DB_DeleteWithNid(long nid);
	bool TEMP_DB_Get_RWtempID(long ncamera,long &RWtempID);
	bool TEMP_DB_Get_RWtempID_List(list<long>&IDList);

	/**************************����ץ�ı�*******************************/
	bool FACE_Capture_AddNew(long &nid,struct FACE_CAPTURE_ST tempFace);
	long FACE_Capture_GetNum(long ncamera,int sex,int sage,int eage,char *startTime,char *endTime,int flag,char *SQLstr);
	bool FACE_Capture_Read(char *SQLstr,int flag,long startNum,long endNum,list<struct FACE_CAPTURE_ST> &faceList);
	bool FACE_Capture_ReadforListOne(long nid,struct FACE_CAPTURE_ST &tempFace);
	bool FACE_Capture_GetUndealFace(struct FACE_CAPTURE_ST &tempFace);//��ȡδ�ȶԵ�ץ�ļ�¼
	bool FACE_Capture_UpdateDealFlag(long nid);//���´����־
	bool FACE_Capture_UpdateBlackFlag(long nid);//�����Ƿ�Ϊ��������־
	long FACE_Capture_GetAlarmNum(long ncamera,int sex,int sage,int eage,char *startTime,char *endTime,int flag,char *SQLstr);
	bool FACE_Capture_ReadAlarmList(char *SQLstr,int flag,long startNum,long endNum,list<struct FACE_CAPTURE_ST> &faceList);
	bool FACE_Capture_CmpRead(struct FACE_CAPTURE_ST &tempFace,long RW_tempID,long RW_personID,long RW_faceID,
									  int sex,long ncamera,int flag,char *startTime,char *endTime);

	/**************************����������*******************************/
	bool FACE_Alarm_AddNew(struct FACE_ALARM_ST alarmFace);
	/**************************����������ͼ*******************************/
	long VS_FACE_Alarm_GetNum(long ncamera,int sex,int sage,int eage,char *startTime,char *endTime,int flag,char *SQLstr);
	bool VS_FACE_Alarm_Read(char *SQLstr,int flag,long startNum,long endNum,list<struct FACE_ALARM_VIEW_ST> &alarmList);
	long VS_FACE_Alarm_GetNum(long captureID);
	bool VS_FACE_Alarm_ReadWithCaptureID(long captureID,long startNum,long endNum,list<struct FACE_ALARM_VIEW_ST> &alarmList);
	bool VS_FACE_Alarm_ReadOne(long captureID,long personID,struct FACE_ALARM_VIEW_ST &alarmInfo);

	bool LOG_AddNewMysqlLog(char *userName,const char *logStr);//�ڲ�����
};



#endif
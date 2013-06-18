#include "stdafx.h"
#include "yirongcardetectaio.h"

#include "CarDetect.h"
//////////////////////////
//WAV����
#include "mmsystem.h"
#pragma comment(lib,"winmm.lib") 

//////////////////////
#include "YiRongCarDetectAIODlg.h"
extern CYiRongCarDetectAIODlg *DlgMain;

#include "DLGSetSystem.h"
extern CDLGSetSystem DlgSetSystem;

#include "IO.h"
extern IO OracleIO;

#include "DLGLogin.h"
extern CDLGLogin DlgLogin;

#if ALLTAB_DETECT_CAR_MODE
//����
#pragma comment(lib, "carSDK\\plate_dll.lib")

#else
//�綯��
#pragma comment(lib, "elecarSDK\\plate_dll.lib")

#endif



#if OPEN_CARDETECT_CODE


CCarDetect::CCarDetect()
{
	CarHandle=NULL;
	State=-1;

	CarTotal=0;
	PicFlag=false;
	Jpg=(unsigned char*)calloc(VIDEO_WIDTH*VIDEO_HEIGHT*3,sizeof(unsigned char));
	JpgSize=0;

	int i;
	for(i=0;i<CAR_STRUCT_MAX;i++)
	{
		//	CarInfo[i].SmallJpg=(unsigned char*)calloc(VIDEO_WIDTH*VIDEO_HEIGHT*3,sizeof(unsigned char));
		//	CarInfo[i].SmallJpgSize=0;
	}

//	ElcarDetectFlag=1;
//	CarDetectFlag=1;
	//��ͼ���ƴ���� 0=���� 1=��
	CarSet.RedRect=1;
	//������бУ��ʹ�ܱ�־ 0:��У����1:У��
	CarSet.Deskew=1;
	//JPGͼƬ���� 75
	CarSet.JPGquality=75;
	//������С��� 60
	CarSet.MinWidth=60;
	//��������� 180
	CarSet.MaxWidth=180;

	CarSet.RangeRate.x0=0;
	CarSet.RangeRate.x1=100;
	CarSet.RangeRate.y0=10;
	CarSet.RangeRate.y1=90;
	//Ĭ��ʡ���ַ�  
	//ʡ�ݺ��֣��� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� ԥ �� �� �� �� �� �� �� ³ ��
	memcpy(CarSet.DefaultChar,"��",CAR_STR_MAX);
	//31��ʡ ��־λ
	//0: �����ú���ʶ�� 1: ���θú���ʶ��
	//�� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� ԥ �� �� �� �� �� �� �� ³ �� (ʡ��)
	//1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1
	for(i=0;i<CAR_MASK_MAX;i++)
		CarSet.Mask[i]=1;
	CarSet.Mask[26]=0;

	//�������Ŷ� 75
	CarSet.Reliability=50;
	//������ɫʶ���־��0:��ʶ��1:ʶ��
	CarSet.CarColor=1;

	/////////////////////////////////////
	cam_name[0]=0;
	l_ipaddr[0]=0;	

	JumpJPG=false;
}

CCarDetect::~CCarDetect()
{
	if(1==State)
		lc_plate_analysis_destroy(CarHandle);

	free(Jpg);

	/*
	int i;
	for(i=0;i<CAR_STRUCT_MAX;i++)
	free(CarInfo[i].SmallJpg);
	*/

}


void CCarDetect::SetRange()
{
	int i;
	//	char j[32];
	if(1==State)
	{
		CarSet.Range.x0=(int16_t)(CarSet.Width*(CarSet.RangeRate.x0/100.0));
		CarSet.Range.x1=(int16_t)(CarSet.Width*(CarSet.RangeRate.x1/100.0));
		CarSet.Range.y0=(int16_t)(CarSet.Hight*(CarSet.RangeRate.y0/100.0));
		CarSet.Range.y1=(int16_t)(CarSet.Hight*(CarSet.RangeRate.y1/100.0));

		if(CarSet.Range.x0<3)
			CarSet.Range.x0=3;
		if(CarSet.Range.x1 > (CarSet.Width-3))
			CarSet.Range.x1=(CarSet.Width-3);

		if(CarSet.Range.y0<3)
			CarSet.Range.y0=3;
		if(CarSet.Range.y1 > (CarSet.Hight-3))
			CarSet.Range.y1=(CarSet.Hight-3);

		i=lc_plate_set_rect_detect(CarHandle,CarSet.Range);
		/*
		if(LC_PLATE_SUCCESS!=i)
		{
				sprintf(j,"%d",i);
			m_maindlg->SetWindowText(j);
		}
		*/
	}
}

void CCarDetect::SetRedRect()
{	
	if(1==State)
	{
		if(LC_PLATE_SUCCESS!=lc_plate_set_position_flag(CarHandle,CarSet.RedRect))
			errorprintf("ERROR set_position");
	}
}

void CCarDetect::SetDeskew()
{	
	if(1==State)
	{
		if(LC_PLATE_SUCCESS!=lc_plate_set_deskew_flag(CarHandle,CarSet.Deskew))
			errorprintf("ERROR set_deskew_flag");
	}
}
void CCarDetect::SetMinMaxWidth()
{	
	if(1==State)
	{
		if(LC_PLATE_SUCCESS!=lc_plate_set_plate_width(CarHandle,CarSet.MinWidth,CarSet.MaxWidth))
			errorprintf("ERROR set_plate");
	}
}

void CCarDetect::SetMask()
{	
	if(1==State)
	{
		if(LC_PLATE_SUCCESS!=lc_plate_set_chinese_mask(CarHandle,CarSet.Mask))
			errorprintf("ERROR set_chinese_mask");
	}
}

void CCarDetect::SetDefaultChar()
{	
	if(1==State)
	{
		if(LC_PLATE_SUCCESS!=lc_plate_set_chinese_default(CarHandle,CarSet.DefaultChar))
			errorprintf("ERROR set_chinese_default");
	}
}

void CCarDetect::SetReliability()
{	
	if(1==State)
	{
		if(LC_PLATE_SUCCESS!=lc_plate_set_chinese_trust_thresh(CarHandle,CarSet.Reliability))
			errorprintf("ERROR set_chinese_trust");
	}
}

void CCarDetect::SetJPGquality()
{	
	if(1==State)
	{
		if(LC_PLATE_SUCCESS!=lc_plate_set_image_quality(CarHandle,CarSet.JPGquality))
			errorprintf("ERROR set_image_quality");
	}
}

void CCarDetect::SetCarColor()
{	
	if(1==State)
	{
		if(LC_PLATE_SUCCESS!=lc_plate_set_car_color_enable(CarHandle,CarSet.CarColor))
			errorprintf("ERROR set_car_color");
	}
}


void CCarDetect::SetAll()
{
	//��һ��
	if(1==State)
	{
		SetRedRect();
		SetRange();
		SetDeskew();
		SetMinMaxWidth();
		SetMask();
		SetDefaultChar();
		SetReliability();
		SetJPGquality();
		SetCarColor();
	}
}
/*
pchannel->cardetect.Start(LC_VIDEO_FORMAT_I420,\
pchannel->image,pframeinfo->width,pframeinfo->height,pframeinfo->width*pframeinfo->height*3/2);

//�����߳�
pchannel->cardetect.Result();
*/

void CCarDetect::errorprintf(char *str)
{
	char tempstr[260];
	sprintf(tempstr,"���ں�=%d,����ͷ����=%s,IP��ַ=%s,%s\n",m_playhandle,cam_name,l_ipaddr,str);
	DlgMain->ShowRuntimeMessage(tempstr,0);
}

void CCarDetect::LimitMessageBox(void)
{
#if ALLTAB_DETECT_CAR_MODE

	uint32_t limit=0;
	char str[32];
	if(LC_PLATE_SUCCESS == lc_plate_get_limit_thread_num(&limit))
	{
		sprintf(str,"�����ʶ������=%d��",limit);
		errorprintf(str);
	}

#endif 

}

//��ʼ����
void CCarDetect::Start(int format,unsigned char *image,int w,int h,int size)
{
	CarSet.Width=w;
	CarSet.Hight=h;

	//��һ��
	if(-1==State)
	{
		if(LC_PLATE_SUCCESS!=lc_plate_analysis_create(&CarHandle,	\
			LC_PLATE_PROC_WAIT_VIDEO,CarSet.Width,CarSet.Hight,NULL,NULL))
		{	
			State=0;
			LimitMessageBox();
			errorprintf("��ǰ����ʶ���޷��������߳����ﵽ���");
			return ;
		}
		else
			State=1;

		errorprintf("ʶ�𴴽��ɹ�");

		if(LC_PLATE_SUCCESS!=lc_plate_set_video_format(CarHandle,format))
			return ;

		SetRedRect();
		SetRange();
		SetDeskew();
		SetMinMaxWidth();
		SetMask();
		SetDefaultChar();
		SetReliability();
		SetJPGquality();
		SetCarColor();

		if(LC_PLATE_SUCCESS!=lc_plate_analysis(&CarHandle,image,w,h,size))
			return ;
	}
	else if(1==State)//N���Ժ�
	{
		if(LC_PLATE_SUCCESS!=lc_plate_analysis(&CarHandle,image,w,h,size))
			return ;
	}

	//�������ʧ�ܾͲ����κ���
}

/*
���⳵����ɫ
����
����
����
����
����
����
����
δ֪
*/
/*
char* CCarDetect::CarColor(uint8_t i)
{
	switch(i)
	{
	case 0:return "����";
	case 1:return "����";
	case 2:return "�׵�-����";
	case 3:return "�׵�-����";
	case 4:return "����";
	case 5:return "����";
	case 6:return "����";
	case 99:return "δ֪";
	default:return "δ֪";
	}
}

char* CCarDetect::CarType(uint8_t i)
{
	switch(i)
	{
	case 1:return "������������";
	case 2:return "С����������";
	case 16:return "������������";
	case 23:return "������������";
	case 25:return "������������";
	case 26:return "������������";
	case 27:return "����������������";
	case 28:return "ũ����������";
	case 99:return "δ֪";
	default:return "δ֪";
	}
}
*/
char* CCarDetect::CarDirection(uint8_t i)
{
	switch(i)
	{
	case 0:return "δ֪����";
	case 1:return "���ϵ���";
	case 2:return "���µ���";
	default:return "δ֪����";
	}
}

//�ж�ʶ������ĳ����Ƿ��ܱ�����ļ�(�Ƿ��ļ���)
// trueΪ����ȷ����
bool ErrorPlateName(char *name)
{

	if(NULL!=strchr(name,'\\'))
		return true;
	else if(NULL!=strchr(name,'/'))
		return true;
	else if(NULL!=strchr(name,':'))
		return true;
	else if(NULL!=strchr(name,'*'))
		return true;
	else if(NULL!=strchr(name,'?'))
		return true;
	else if(NULL!=strchr(name,'\"'))
		return true;
	else if(NULL!=strchr(name,'<'))
		return true;
	else if(NULL!=strchr(name,'>'))
		return true;
	else if(NULL!=strchr(name,'|'))
		return true;

	return false;
}

//���� 0Ϊ�����Ч
//���� 1Ϊд�����ݿ�
//���� 2Ϊ��ó�����Ϣ
//���� 3Ϊ��ѯ������޷��ؽ��
int CCarDetect::Result()
{
	if(1!=State)
		return 0;

	int i,re,ge;
	int tempCartotal=0;
	//�����ڷ���
	int tempstate=3;
	char tempstr[100]={0};

	char str[260];
	char pathstr[ZOG_MAX_PATH_STR];
	char timestr[100];
	char dirstr[ZOG_MAX_PATH_STR];

	int nItem;

	int yrvm_first;
	int nid;
	char Timeformat[32];
	FILE *fp;
	bool isBlack=false;

	re=lc_plate_get_plate_number(CarHandle,&tempCartotal);

	if(LC_PLATE_SUCCESS==re && tempCartotal>0)
	{
		PicFlag=true;
		CarTotal=tempCartotal;

		for(i=0;i<CarTotal;i++)
		{
			lc_plate_get_plate_name(CarHandle,i,&CarInfo[i].Str);

			//lc_plate_get_plate_color_id(CarHandle,i,&CarInfo[i].ColorId);
			lc_plate_get_plate_color_name(CarHandle,i,&CarInfo[i].PlateColor);

			lc_plate_get_plate_reliability(CarHandle,i,&CarInfo[i].Reliability);

			lc_plate_get_car_direction(CarHandle,i,&CarInfo[i].Direction);

			lc_plate_get_plate_position(CarHandle,i,&CarInfo[i].CarRect);

			//	lc_plate_get_plate_type_id(CarHandle,i,&CarInfo[i].Type);
			lc_plate_get_plate_type_name(CarHandle,i,&CarInfo[i].PlateType);

			//������ɫ
			lc_plate_get_car_color_name(CarHandle,i,&CarInfo[i].CarColor);

			/*
			r=lc_plate_get_small_picture(CarHandle,CarInfo[i].SmallJpg,&CarInfo[i].SmallJpgSize,i);
			if(LC_PLATE_SUCCESS==r && JpgSize>0 && JpgSize< 1110400)
			{
			sprintf(str,"%s-small.jpg",CarInfo[i].Str);
			fp=fopen(str,"wb");
			if(fp)
			{
			fwrite(CarInfo[i].SmallJpg,CarInfo[i].SmallJpgSize,1,fp);
			fclose(fp);
			}
			}
			*/
		}
		tempstate=2;
	}
	//׼��ץͼ
	if(PicFlag && CarTotal>0)
	{
		ge=lc_plate_get_plate_picture(CarHandle,Jpg,&JpgSize);

		if(LC_PLATE_SUCCESS==ge && JpgSize>0 && JpgSize< 1110400 )
		{
			CTime nowtime=CTime::GetTickCount();
			sprintf(timestr,"%04d-%02d-%02d-%02d-%02d-%02d",
				nowtime.GetYear(),
				nowtime.GetMonth(),
				nowtime.GetDay(),
				nowtime.GetHour(),
				nowtime.GetMinute(),
				nowtime.GetSecond());

			sprintf(dirstr,"%s\\%04d-%02d-%02d",
				DlgSetSystem.m_path_detect.GetBuffer(0),
				nowtime.GetYear(),
				nowtime.GetMonth(),
				nowtime.GetDay());

			CreateDirectory(dirstr, NULL);

			sprintf(dirstr,"%s\\%04d-%02d-%02d\\%s",
				DlgSetSystem.m_path_detect.GetBuffer(0),
				nowtime.GetYear(),
				nowtime.GetMonth(),
				nowtime.GetDay(),
				l_ipaddr);

			CreateDirectory(dirstr, NULL);

			yrvm_first=0;

			for(i=0;i<CarTotal;i++)
			{
				if(strlen(CarInfo[i].Str) <7)
					continue;
				//�����ƺ�
				if(ErrorPlateName(CarInfo[i].Str))
					continue;

				sprintf(Timeformat,"%04d-%02d-%02d %02d:%02d:%02d",
					nowtime.GetYear(),
					nowtime.GetMonth(),
					nowtime.GetDay(),
					nowtime.GetHour(),
					nowtime.GetMinute(),
					nowtime.GetSecond());
			
#if ALLTAB_DETECT_CAR_MODE
//����
				//�����Ƭ
				sprintf(pathstr,"%s\\%s %d %s %s %d "
//					"%d %d %d %d"
					" %s %s %s %s %d .jpg",	\
					dirstr,
					timestr,camid,l_ipaddr,
					CarInfo[i].Str,
					CarInfo[i].Reliability,	
//					CarInfo[i].CarRect.x0,CarInfo[i].CarRect.x1,CarInfo[i].CarRect.y0,CarInfo[i].CarRect.y1,
					//CarColor(CarInfo[i].ColorId),CarDirection(CarInfo[i].Direction),CarType(CarInfo[i].Type),
					CarInfo[i].PlateColor,CarDirection(CarInfo[i].Direction),CarInfo[i].PlateType,
					CarInfo[i].CarColor,
					JpgSize);
	
				fp=fopen(pathstr,"wb");
				if(fp)
				{
					fwrite(Jpg,JpgSize,1,fp);
					fclose(fp);
				}
				
				bool tempadd;
				//���籣��
				if(DlgSetSystem.m_check_savenet)
				{
					//д���ݿ�
					tempadd=OracleIO.CAR_MatchResult_AddNew(
						&isBlack,
						camid,
						CarInfo[i].PlateType,
						CarInfo[i].PlateColor,	
						CarDirection(CarInfo[i].Direction),
						CarInfo[i].CarColor,
						CarInfo[i].Str,
						CarInfo[i].Reliability,	
						"null",
						JpgSize,Jpg);
				}
				else
				{
					//���ر���
					tempadd=OracleIO.CAR_MatchResult_AddNew(
						&isBlack,
						camid,
						CarInfo[i].PlateType,
						CarInfo[i].PlateColor,	
						CarDirection(CarInfo[i].Direction),
						CarInfo[i].CarColor,
						CarInfo[i].Str,
						CarInfo[i].Reliability,	
						pathstr,
						JpgSize,Jpg);
				
				}
				if(tempadd)
				{
					//�����б�
					if(DlgMain->m_ListCarTotal >=200)
					{
						CleanList();
					}
					
					(DlgMain->m_ListCarTotal)++;
					sprintf(str,"%d",DlgMain->m_ListCarTotal);
					nItem = DlgMain->m_ListCar.InsertItem(0,str);
					
					DlgMain->m_ListCar.SetItemText(nItem,1,Timeformat);
					DlgMain->m_ListCar.SetItemText(nItem,2,cam_name);
					DlgMain->m_ListCar.SetItemText(nItem,3,l_ipaddr);
					DlgMain->m_ListCar.SetItemText(nItem,4,CarInfo[i].Str);
					
					sprintf(str,"%d",CarInfo[i].Reliability);
					DlgMain->m_ListCar.SetItemText(nItem,5,str);
					
					DlgMain->m_ListCar.SetItemText(nItem,6,CarDirection(CarInfo[i].Direction));
					DlgMain->m_ListCar.SetItemText(nItem,7,	CarInfo[i].PlateColor);
					DlgMain->m_ListCar.SetItemText(nItem,8,	CarInfo[i].PlateType);
					DlgMain->m_ListCar.SetItemText(nItem,9,	CarInfo[i].CarColor);
					if(alarmflag && isBlack)
					{
						DlgMain->m_ListCar.SetItemText(nItem,10,	"��");
						if(DlgSetSystem.m_check_alarmpic)
						{
							//	ShellExecute(DlgMain->m_hWnd,NULL,pathstr,NULL,NULL,SW_NORMAL);
							JumpJPG=true;
							strcpy(JumpJPGpath,pathstr);
						}
						//��������
						if(DlgSetSystem.m_check_alarmwav)
							PlaySound(DlgSetSystem.m_path_alarmwav,NULL,SND_FILENAME | SND_ASYNC);
					}
					else
						DlgMain->m_ListCar.SetItemText(nItem,10,	"��");
					
					DlgMain->m_ListCar.SetItemText(nItem,11,	pathstr);
			
					if(DlgSetSystem.m_check_savenet)
						DlgMain->m_ListCar.SetItemText(nItem,12,	"��");
					else
						DlgMain->m_ListCar.SetItemText(nItem,12,	"��");
				}
				else
				{
					errorprintf("���ݿ����:ʶ�����������");
					DlgMain->ShowRuntimeMessage("���ݿ����:ʶ�����������",1);
				}
#else
//�綯��
				//�����Ƭ
				sprintf(pathstr,"%s\\%s %d %s %s %d %s %d .jpg",	\
					dirstr,
					timestr,camid,l_ipaddr,
					&CarInfo[i].Str[strlen(CarInfo[i].Str)-5],
					CarInfo[i].Reliability,
					CarDirection(CarInfo[i].Direction),
					JpgSize);
	
				fp=fopen(pathstr,"wb");
				if(fp)
				{
					fwrite(Jpg,JpgSize,1,fp);
					fclose(fp);
				}

				bool tempadd;
				//���籣��
				if(DlgSetSystem.m_check_savenet)
				{
					//д���ݿ�
					tempadd=OracleIO.ELECAR_MatchResult_AddNew(
						&isBlack,
						camid,
						"����",	
						CarDirection(CarInfo[i].Direction),
						&CarInfo[i].Str[strlen(CarInfo[i].Str)-5],
						CarInfo[i].Reliability,	
						"null",
						JpgSize,Jpg);
				}
				else
				{
					//���汾��
					tempadd=OracleIO.ELECAR_MatchResult_AddNew(
						&isBlack,
						camid,
						"����",
						CarDirection(CarInfo[i].Direction),
						&CarInfo[i].Str[strlen(CarInfo[i].Str)-5],
						CarInfo[i].Reliability,	
						pathstr,
						JpgSize,Jpg);
				}
				if(tempadd)
				{
					//�����б�
					if(DlgMain->m_ListCarTotal >=200)
					{
						CleanList();
					}

					(DlgMain->m_ListCarTotal)++;
					sprintf(str,"%d",DlgMain->m_ListCarTotal);
					nItem = DlgMain->m_ListCar.InsertItem(0,str);
					
					DlgMain->m_ListCar.SetItemText(nItem,1,Timeformat);
					DlgMain->m_ListCar.SetItemText(nItem,2,cam_name);
					DlgMain->m_ListCar.SetItemText(nItem,3,l_ipaddr);
					DlgMain->m_ListCar.SetItemText(nItem,4,&CarInfo[i].Str[strlen(CarInfo[i].Str)-5]);
					
					sprintf(str,"%d",CarInfo[i].Reliability);
					DlgMain->m_ListCar.SetItemText(nItem,5,str);
					
					DlgMain->m_ListCar.SetItemText(nItem,6,CarDirection(CarInfo[i].Direction));

					DlgMain->m_ListCar.SetItemText(nItem,7,"����");

					if(alarmflag && isBlack)
					{
						DlgMain->m_ListCar.SetItemText(nItem,8,	"��");
						if(DlgSetSystem.m_check_alarmpic)
						{
						//	ShellExecute(DlgMain->m_hWnd,NULL,pathstr,NULL,NULL,SW_NORMAL);
							JumpJPG=true;
							strcpy(JumpJPGpath,pathstr);
						}
						//��������
						if(DlgSetSystem.m_check_alarmwav)
							PlaySound(DlgSetSystem.m_path_alarmwav,NULL,SND_FILENAME | SND_ASYNC);
					}
					else
						DlgMain->m_ListCar.SetItemText(nItem,8,	"��");
					
					DlgMain->m_ListCar.SetItemText(nItem,9,	pathstr);
		
					if(DlgSetSystem.m_check_savenet)
						DlgMain->m_ListCar.SetItemText(nItem,10,	"��");
					else
						DlgMain->m_ListCar.SetItemText(nItem,10,	"��");
				}
				else
				{
					errorprintf("���ݿ����:ʶ�����������");
					DlgMain->ShowRuntimeMessage("���ݿ����:ʶ�����������",1);
				}
#endif
/**********************ƽ̨BEGIN*********************************/
#if YRVM_PINGTAI_MODE

#if ALLTAB_DETECT_CAR_MODE
				//����
				if(0 == yrvm_first)
				{
					//���ݿ�
					nid=OracleIO.YRVM_getCarOracleTempNid();
					//д��ʧ��
					if(! OracleIO.YRVM_writeCarTempPhotoToOracleDB(l_ipaddr,Jpg,JpgSize,nid))
					{
						errorprintf("YRVM���ݿ����:�����޴�����ͷIP����ʶ�����������");
						DlgMain->ShowRuntimeMessage("YRVM���ݿ����:�����޴�����ͷIP����ʶ�����������",1);
						break; //�˳�FORѭ��
					}
					yrvm_first=1;
				}
				
				//�����Ŷ�
				sprintf(tempstr,"%02d",CarInfo[i].Reliability);
				
				//д�ַ���
				OracleIO.YRVM_writeCarTempInfoToOracleDB(CarInfo[i].Str,	\
					CarInfo[i].PlateColor,CarInfo[i].Direction,tempstr,CarInfo[i].PlateType,
					CarInfo[i].CarColor,nid);
#else

#if YRVM_PINGTAI_ELECAR_MIX_MODE
				//�綯��д���������
				if(0==yrvm_first)
				{
					//���ݿ�
					nid=OracleIO.YRVM_getCarOracleTempNid();
					if(! OracleIO.YRVM_writeCarTempPhotoToOracleDB(l_ipaddr,Jpg,JpgSize,nid))
					{
						errorprintf("YRVM���ݿ����:�����޴�����ͷIP����ʶ�����������");
						DlgMain->ShowRuntimeMessage("YRVM���ݿ����:�����޴�����ͷIP����ʶ�����������",1);
						break; //�˳�FORѭ��
					}
					yrvm_first=1;
				}
				
				//�����Ŷ�
				sprintf(tempstr,"%02d",CarInfo[i].Reliability);
				
				//д�ַ���
				OracleIO.YRVM_writeCarTempInfoToOracleDB(&CarInfo[i].Str[strlen(CarInfo[i].Str)-5],	\
					"����",CarInfo[i].Direction,tempstr,"�綯������",
					CarInfo[i].CarColor,nid);

#else
				//�綯��д��綯����
				if(0==yrvm_first)
				{
					//���ݿ�
					nid=OracleIO.YRVM_getElectricCarOracleTempNid();
					if(! OracleIO.YRVM_writeElectricCarTempPhotoToOracleDB(l_ipaddr,Jpg,JpgSize,nid))
					{
						errorprintf("YRVM���ݿ����:�����޴�����ͷIP����ʶ�����������");
						DlgMain->ShowRuntimeMessage("YRVM���ݿ����:�����޴�����ͷIP����ʶ�����������",1);
						break; //�˳�FORѭ��
					}
					yrvm_first=1;
				}
				
				//�����Ŷ�
				sprintf(tempstr,"%02d",CarInfo[i].Reliability);
				
				//д�ַ���
				OracleIO.YRVM_writeElectricCarTempInfoToOracleDB(&CarInfo[i].Str[strlen(CarInfo[i].Str)-5],	\
				//	CarInfo[i].PlateColor,
					"����",
					CarInfo[i].Direction,tempstr,nid);
#endif
#endif

#endif
/**********************ƽ̨END*********************************/
			}//FOR END
/**********************ƽ̨BEGIN*********************************/
#if YRVM_PINGTAI_MODE
			//ִֻ��һ��
			if(yrvm_first)
#if ALLTAB_DETECT_CAR_MODE
//����
			OracleIO.YRVM_ExecuteInsertMatchCarResultProcedure(nid);
#else

#if YRVM_PINGTAI_ELECAR_MIX_MODE
			//�綯��д���������
			OracleIO.YRVM_ExecuteInsertMatchCarResultProcedure(nid);
#else
			//�綯��д��綯����
			OracleIO.YRVM_ExecuteInsertMatchVehicleResultProcedure(nid);
#endif

#endif

#endif
/**********************ƽ̨END*********************************/
//������������־
#if 0
			fp=fopen("YRCarTotalList.txt","a+");
			if(fp)
			{
				for(i=0;i<CarTotal;i++)
				{
					//if(0==strlen(CarInfo[i].Str))
					//	continue;

					fprintf(fp,"%d %d %d %d %d %d :\n\tnid=%d,���ƺ�=%s,IP=%s\n",	\
						nowtime.GetYear(),	\
						nowtime.GetMonth(),	\
						nowtime.GetDay(),	\
						nowtime.GetHour(),	\
						nowtime.GetMinute(),	\
						nowtime.GetSecond(),	\
						i,
						CarInfo[i].Str,\
						l_ipaddr);
					fprintf(fp,"\tstrlen=%d,���Ŷ�=%d,�ļ�·��=%s\n",	\
						strlen(CarInfo[i].Str),
						CarInfo[i].Reliability,	\
						pathstr);
					fprintf(fp,"\t����λ��x0=%d,x1=%d,y0=%d,y1=%d\n",
						CarInfo[i].CarRect.x0,CarInfo[i].CarRect.x1,CarInfo[i].CarRect.y0,CarInfo[i].CarRect.y1);
					fprintf(fp,"\t������ɫ=%s,����=%s,��������=%s\n",
						//CarColor(CarInfo[i].ColorId),CarDirection(CarInfo[i].Direction),CarType(CarInfo[i].Type)
						CarInfo[i].PlateColor,CarDirection(CarInfo[i].Direction),CarInfo[i].PlateType
						);
					fprintf(fp,"\t������ɫ=%s\n",CarInfo[i].CarColor);

				}
				fclose(fp);
			}
#endif

			PicFlag=false;
			CarTotal=0;
			tempstate=1;
		}
	}
	return tempstate;
}

void CCarDetect::CleanList(void)
{
	int total;
	char str[260];
	total=DlgMain->m_ListCar.GetItemCount();
	
	//���籣�� ��һ��ɾ���ļ�
	if(DlgSetSystem.m_check_savenet)
	{
		for(int i=0;i<total;i++)
		{
#if ALLTAB_DETECT_CAR_MODE
			//����
			DlgMain->m_ListCar.GetItemText(i,12,str,260);
#else
			//�綯��
			DlgMain->m_ListCar.GetItemText(i,10,str,260);
#endif	
			//����ģʽ�Ͳ���ɾ
			if(0==strcmp(str,"��"))
				continue;
			
			//ɾ���ļ�
#if ALLTAB_DETECT_CAR_MODE
			//����
			DlgMain->m_ListCar.GetItemText(i,11,str,260);
#else
			//�綯��
			DlgMain->m_ListCar.GetItemText(i,9,str,260);
#endif	
			DeleteFile(str);
			
		}	
	}

	DlgMain->m_ListCar.DeleteAllItems();
	DlgMain->m_ListCarTotal=0;
	
}


//ֹͣ����
void CCarDetect::Stop()
{
	if(1==State)
	{
		Sleep(100);
		lc_plate_analysis_destroy(CarHandle);
		//��Ϊ ~()�ͷź���ʱ���Ӵ˻����
		errorprintf("ʶ��ֹͣ�ɹ�");
		CarHandle=NULL;
	}

	State=-1;

	CarTotal=0;
	PicFlag=false;
	JpgSize=0;
}


#endif
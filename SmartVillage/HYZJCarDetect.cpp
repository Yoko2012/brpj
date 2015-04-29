#include "stdafx.h"
#include "SmartVillage.h"

#include "HYZJCarDetect.h"
//////////////////////////

#include "YUV2RGB.h"

//////////////////////
#include "SmartVillageDlg.h"
extern CSmartVillageDlg *DlgMain;

#include "DLGSetSystem.h"
extern CDLGSetSystem DlgSetSystem;

#include "YRSVMySQL.h"
extern CYRSVMySQL MySqlIO;

#include "DLGLogin.h"
extern CDLGLogin DlgLogin;

#include "JingAoUpload.h"


#if OPEN_HYZJ_CARDETECT_CODE

CHYZJCarDetect::CHYZJCarDetect()
{
	CarHandle=0;
	State=-1;

	CarTotal=0;
	JpgSize=0;
	JpgSmall=(unsigned char*)calloc(VIDEO_WIDTH*VIDEO_HEIGHT*3,sizeof(unsigned char));
	JpgSmallSize=0;


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
	memset(CarSet.DefaultChar,0,HYZJ_CAR_STR_MAX);
	memcpy(CarSet.DefaultChar,"��",HYZJ_CAR_STR_MAX);
	//31��ʡ ��־λ
	//0: �����ú���ʶ�� 1: ���θú���ʶ��
	//�� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� ԥ �� �� �� �� �� �� �� ³ �� (ʡ��)
	//1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1
	for(i=0;i<HYZJ_CAR_MASK_MAX;i++)
		CarSet.Mask[i]=1;
	CarSet.Mask[26]=0;

	//�������Ŷ� 75
	CarSet.Reliability=50;
	//������ɫʶ���־��0:��ʶ��1:ʶ��
	CarSet.CarColor=1;
CarSet.Night=0;
	/////////////////////////////////////
	cam_name[0]=0;
	l_ipaddr[0]=0;	

	JumpJPG=false;
	cam_Direction=0;
}

CHYZJCarDetect::~CHYZJCarDetect()
{
	if(1==State)
		LPR_UninitEx(CarHandle);


	if(JpgSmall)
	{
		free(JpgSmall);
		JpgSmall=NULL;
	}

}




void CHYZJCarDetect::SetRange()
{
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
	}
}
void CHYZJCarDetect::errorprintf(char *str)
{
	char tempstr[260]={0};
	sprintf(tempstr,"���ں�=%d,����ͷ����=%s,IP��ַ=%s,%s\n",m_playhandle,cam_name,l_ipaddr,str);
	DlgMain->ShowRuntimeMessage(tempstr,0);
}

void CHYZJCarDetect::LimitMessageBox(void)
{
	char str[32]={0};
	sprintf(str,"�����ʶ������=%d��",LPR_GetTotalChannelNum ());
	errorprintf(str);
}


//��ʼ����
bool CHYZJCarDetect::Start(int format,unsigned char *image,int w,int h,int size)
{
	CarSet.Width=w;
	CarSet.Hight=h;
	//��һ��
	if(-1==State)
	{
		
		CarHandle=DlgMain->DlgTabVideo.DlgScreen.HYZJCarDetect_total+1;
		
		if(0==LPR_SetImageFormat(FALSE,FALSE,format,FALSE,45,400,TRUE,FALSE,TRUE,CarHandle))
		{	
			State=0;
			errorprintf("����ʶ���ʽ��֧��");
			return false;
		}

		if(0==LPR_InitEx(CarHandle))
		{	
			State=0;
			LimitMessageBox();
			errorprintf("��ǰ����ʶ���޷��������߳����ﵽ���");
			return false;
		}
		else
			State=1;

		DlgMain->DlgTabVideo.DlgScreen.HYZJCarDetect_total++;

		errorprintf("ʶ�𴴽��ɹ�");

		struct DEVICE_SET_ST CamSet={0};

		MySqlIO.DEVICE_SetTable_Read(camid,CamSet);

		//��������ݿ��ȡ���Լ����档����ʶ��CPP�ļ�ҲҪ�Ӷ�ȡ
		CarSet.CarColor=CamSet.car.carlor;
		CarSet.Deskew=CamSet.car.deskew;
		CarSet.RedRect=CamSet.car.redrect;
		CarSet.JPGquality=CamSet.car.jpgquailty;
		CarSet.MinWidth=CamSet.car.minwidth;
		CarSet.MaxWidth=CamSet.car.maxwidth;
		CarSet.RangeRate.x0=CamSet.car.left;
		CarSet.RangeRate.x1=CamSet.car.right;
		CarSet.RangeRate.y0=CamSet.car.top;
		CarSet.RangeRate.y1=CamSet.car.bottom;
		strcpy(CarSet.DefaultChar,CamSet.car.defaultchar);
		CarSet.Reliability=CamSet.car.reliability;
		memcpy(CarSet.Mask,CamSet.car.mask,HYZJ_CAR_MASK_MAX);
		SetRange();

		CarSetrcRange.left=CarSet.Range.x0;
		CarSetrcRange.right=CarSet.Range.x1;
		CarSetrcRange.top=CarSet.Range.y0;
		CarSetrcRange.bottom=CarSet.Range.y1;
		CarSet.Night=CamSet.car.night;

		LPR_SetSpecialParameters(CarSet.Night,0,0,HYZJ_CAR_STRUCT_MAX,CarSet.DefaultChar,CarHandle);

	}
	
	if(1==State)//N���Ժ�
	{
		int nRecoNum = 0;
		TH_RECT aaaa={0,0,0,0} ;
		LPR_RGB888Ex(image, w, h, PlateResultReal, nRecoNum, &aaaa,CarHandle );
		
	}

	return true;
	//�������ʧ�ܾͲ����κ���
}
char* CHYZJCarDetect::CarType(int i)
{
	switch(i)
	{
	case 1:return "����С����";
	case 2:return "����С����";
	case 3:return "���Ż���";
	case 4:return "˫�Ż���";
	case 5:return "��������";
	case 6:return "�侯����";
	case 7:return "���Ի�����";
	case 8:return "���ž�����";
	case 9:return "˫�ž�����";
	case 10:return "ʹ�ݳ���";
	case 11:return "��۽����й���½����";
	case 12:return "ũ�ó���";
	case 13:return "��������";
	case 14:return "���Ž����й���½����";
	case 15:return "˫���侯����";
	default:return "δ֪����";
	}
}
char* CHYZJCarDetect::CarDirection(int i)
{
	switch(i)
	{
	case 1:return "������";
	case 2:return "���ҵ���";
	case 3:return "���ϵ���";
	case 4:return "���µ���";
	default:return "δ֪";
	}
}
char* CHYZJCarDetect::CarColor(int i)
{
	switch(i)
	{
	case 0:return "��ɫ";
	case 1:return "����ɫ";
	case 2:return "��ɫ";
	case 3:return "��ɫ";
	case 4:return "��ɫ";
	case 5:return "��ɫ";
	case 6:return "��ɫ";
	case 7:return "��ɫ";
	case 8:return "��ɫ";
	default:return "δ֪";
	}
}

char* CHYZJCarDetect::CarColor2JingAo(int i)
{
	switch(i)
	{
	case 0:return "0";
	case 2:return "1";
	case 6:return "2";
	case 8:return "3";
	default:return "5";
	}
}

char* CHYZJCarDetect::CarType2JingAo(int i)
{
	switch(i)
	{
	case 1:return "K00";
	case 2:return "K00";
	case 3:return "K00";
	case 4:return "H00";
	case 5:return "K00";
	case 6:return "K00";
	case 7:return "K00";
	case 8:return "K00";
	case 9:return "H00";
	case 10:return "K00";
	case 11:return "K00";
	case 12:return "K00";
	case 13:return "K00";
	case 14:return "K00";
	case 15:return "H00";
	default:return "ZZZ";
	}

}



//�ж�ʶ������ĳ����Ƿ��ܱ�����ļ�(�Ƿ��ļ���)
// trueΪ����ȷ����
bool CHYZJCarDetect::ErrorPlateName(char *name)
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
int CHYZJCarDetect::Result()
{
	if(1!=State)
		return 0;

	int i,re;
	int tempCartotal=0;
	//�����ڷ���
	int tempstate=3;
	char tempstr[100]={0};

	char str[ZOG_MAX_PATH_STR]={0};
	char pathstr[ZOG_MAX_PATH_STR]={0};
	char timestr[64]={0};
	char dirstr[ZOG_MAX_PATH_STR]={0};

	char pathSmallstr[ZOG_MAX_PATH_STR]={0};
	char dirSmallstr[ZOG_MAX_PATH_STR]={0};

	struct HISTORY_CarDetect_ST carInfo={0};
	int nItem;

	long nid,blackid;
	char Timeformat[32]={0};
	FILE *fp;
	bool isBlack=false;

	char jsonstr[2048];
	int resoap;

	 re =  LPR_GetReliableResult(CarInfo,  CarTotal, CarHandle);
	if(1==re && CarTotal>0)
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
			DlgSetSystem.path_CarDetect.GetBuffer(0),
			nowtime.GetYear(),
			nowtime.GetMonth(),
			nowtime.GetDay());

		CreateDirectory(dirstr, NULL);

		sprintf(dirstr,"%s\\%04d-%02d-%02d\\%d_%s",
			DlgSetSystem.path_CarDetect.GetBuffer(0),
			nowtime.GetYear(),
			nowtime.GetMonth(),
			nowtime.GetDay(),
			camid,cam_name);

		CreateDirectory(dirstr, NULL);
		////////////////////////
		sprintf(dirSmallstr,"%s\\%04d-%02d-%02d",
			DlgSetSystem.path_CarDetect_Small.GetBuffer(0),
			nowtime.GetYear(),
			nowtime.GetMonth(),
			nowtime.GetDay());

		CreateDirectory(dirSmallstr, NULL);

		sprintf(dirSmallstr,"%s\\%04d-%02d-%02d\\%d_%s",
			DlgSetSystem.path_CarDetect_Small.GetBuffer(0),
			nowtime.GetYear(),
			nowtime.GetMonth(),
			nowtime.GetDay(),
			camid,cam_name);

		CreateDirectory(dirSmallstr, NULL);

		for(i=0;i<CarTotal;i++)
		{
			if ( CarInfo[i].pImageRGB24 != NULL )
			{
				ErrorPlateName(CarInfo[i].license);

				sprintf(Timeformat,"%04d-%02d-%02d %02d:%02d:%02d",
					nowtime.GetYear(),
					nowtime.GetMonth(),
					nowtime.GetDay(),
					nowtime.GetHour(),
					nowtime.GetMinute(),
					nowtime.GetSecond());

				//�����Ƭ
				sprintf(pathstr,"%s\\%s %d %s %s %d "
					" %s %s %s %s .jpg",	\
					dirstr,
					timestr,camid,l_ipaddr,
					CarInfo[i].license,
					CarInfo[i].nConfidence,	
					CarInfo[i].color,CarDirection(CarInfo[i].nDirection),CarType(CarInfo[i].nType),
					CarColor(CarInfo[i].nCarColor));

				CompressRGBToJPEG(CarInfo[i].pImageRGB24, CarInfo[i].nImageWidth, CarInfo[i].nImageHeight,
					0,75,pathstr,0,0);

				fp=fopen(pathstr,"rb");
				if(fp)
				{	
					fseek(fp,0,SEEK_END);
					JpgSize = ftell(fp);
					fclose(fp);
				}
			
				//////////////////////
				//�����Ƭ
				sprintf(pathSmallstr,"%s\\%s %d %s %s %d "
					" %s %s %s %s .jpg",	\
					dirSmallstr,
					timestr,camid,l_ipaddr,
					CarInfo[i].license,
					CarInfo[i].nConfidence,	
					CarInfo[i].color,CarDirection(CarInfo[i].nDirection),CarType(CarInfo[i].nType),
					CarColor(CarInfo[i].nCarColor));
				
				int cw=0,ch=0;
				CutImage(CarInfo[i].pImageRGB24, CarInfo[i].nImageWidth, CarInfo[i].nImageHeight,
					CarInfo[i].rcLocation.left,CarInfo[i].rcLocation.top,
					CarInfo[i].rcLocation.right,CarInfo[i].rcLocation.bottom,
					JpgSmall, cw,ch, 3);

				CompressRGBToJPEG(JpgSmall,cw,ch,
					0,75,pathSmallstr,0,0);

				fp=fopen(pathSmallstr,"rb");
				if(fp)
				{	
					fseek(fp,0,SEEK_END);
					JpgSmallSize = ftell(fp);
					fclose(fp);
				}


				bool tempadd;

				memset(&carInfo,0,sizeof(struct HISTORY_CarDetect_ST ));

				carInfo.ncamera=camid;
				strcpy(carInfo.platetype,CarType(CarInfo[i].nType));
				strcpy(carInfo.platecolor,	CarInfo[i].color);
				strcpy(carInfo.direction,CarDirection(CarInfo[i].nDirection));
				strcpy(carInfo.carcolor,CarColor(CarInfo[i].nCarColor));
				strcpy(carInfo.plate,CarInfo[i].license);
				carInfo.reliability=CarInfo[i].nConfidence;
				strcpy(carInfo.path,pathstr);
				carInfo.picsize=JpgSize;
				
				strcpy(carInfo.smallpath,pathSmallstr);
				carInfo.smallsize=JpgSmallSize;
				
				carInfo.year=nowtime.GetYear();
				carInfo.mon=nowtime.GetMonth();
				carInfo.day=nowtime.GetDay();
				carInfo.hour=nowtime.GetHour();
				carInfo.min=nowtime.GetMinute();
				carInfo.sec=nowtime.GetSecond();

				nid=0;
				blackid=0;
				//���ر���
				tempadd=MySqlIO.CAR_MatchResult_AddNewNoPicData(
					isBlack,
					nid,
					blackid,
					carInfo);

				if(tempadd)
				{
					//�����б�
					if(DlgMain->DlgTabVideo.m_ListCarTotal >=HY_MAX_CAR_LIST_NUM)
					{
						CleanList();
					}

					//��ͼƬ
					DlgMain->DlgTabVideo.m_ListImg.AddImg(pathSmallstr);
					nItem =DlgMain->DlgTabVideo.m_ListImg.InsertItem(
						0, DlgMain->DlgTabVideo.m_ListCarTotal);

					DlgMain->DlgTabVideo.m_ListCar.SetItemText(nItem,1,Timeformat);
					DlgMain->DlgTabVideo.m_ListCar.SetItemText(nItem,2,cam_name);
					DlgMain->DlgTabVideo.m_ListCar.SetItemText(nItem,3,l_ipaddr);

					(DlgMain->DlgTabVideo.m_ListCarTotal)++;
					sprintf(str,"%d",DlgMain->DlgTabVideo.m_ListCarTotal);
					DlgMain->DlgTabVideo.m_ListCar.SetItemText(nItem,4,str);

					DlgMain->DlgTabVideo.m_ListCar.SetItemText(nItem,5,CarInfo[i].license);

					sprintf(str,"%d",CarInfo[i].nConfidence);
					DlgMain->DlgTabVideo.m_ListCar.SetItemText(nItem,6,str);

					DlgMain->DlgTabVideo.m_ListCar.SetItemText(nItem,7,CarDirection(CarInfo[i].nDirection));
					DlgMain->DlgTabVideo.m_ListCar.SetItemText(nItem,8,	CarInfo[i].color);
					DlgMain->DlgTabVideo.m_ListCar.SetItemText(nItem,9,CarType(CarInfo[i].nType));
					DlgMain->DlgTabVideo.m_ListCar.SetItemText(nItem,10,	CarColor(CarInfo[i].nCarColor));

					if( isBlack)
					{
						DlgMain->DlgTabVideo.m_ListCar.SetItemText(nItem,11,	"��");
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
						DlgMain->DlgTabVideo.m_ListCar.SetItemText(nItem,11,	"��");
					DlgMain->DlgTabVideo.m_ListCar.SetItemText(nItem,12,	pathstr);
					DlgMain->DlgTabVideo.m_ListCar.SetItemText(nItem,13,	"��");

					sprintf(str,"%d",nid);
					DlgMain->DlgTabVideo.m_ListCar.SetItemText(nItem,14,	str);
					sprintf(str,"%d",blackid);
					DlgMain->DlgTabVideo.m_ListCar.SetItemText(nItem,15,	str);

				}
				else
				{
					errorprintf("���ݿ����:ʶ�����������");
					DlgMain->ShowRuntimeMessage("���ݿ����:ʶ�����������",1);
				}

#if JING_AO_UPLOAD

				if(DlgSetSystem.m_c_jingao)
				{
					//С��Ƭ
					sprintf(pathSmallstr,"%d %s %d %s %d.jpg",	
						nid,
						timestr,camid,l_ipaddr,
						JpgSmallSize);

					//����Ƭ
					sprintf(pathstr,"%d %s %d %s %d.jpg",	
						nid,
						timestr,camid,l_ipaddr,
						JpgSize);

					sprintf(jsonstr,"{id:\"%d\",captureDeviceIP:\"%s\",\
									captureDeviceMAC:\"00-00-00-00-00-00\",captureTime:\"%s\",\
									licensePlateNumber:\"%s\",licensePlateColor:\"%s\",\
									vehicleType:\"%s\",throughDirection:\"%d\",geographicalPosition:\"%s\"}",
									nid,l_ipaddr,Timeformat,carInfo.plate,
									CarColor2JingAo(CarInfo[i].nColor),CarType2JingAo(CarInfo[i].nType),
									cam_Direction,cam_name);

					resoap=JingAoUpload(DlgSetSystem.m_e_jingao_ipport.GetBuffer(0),
						"/capture-data-interface/vehicle",
						"baseInfo","licensePlatePicture","panoramicPicture",
						pathSmallstr,carInfo.smallpath,
						pathstr,carInfo.path,
						jsonstr);

					if(0!=resoap)
					{
						sprintf(jsonstr,"CAR JingAoUpload error %d",resoap);
						MySqlIO.LOG_AddNewSystemLog(DlgLogin.CurrentUser.user,jsonstr);
					}
					else
					{
						char *pjsonstr=strstr(jsonstr,"result:\"0\"");
						if(NULL==pjsonstr)
						{
							MySqlIO.LOG_AddNewSystemLog(DlgLogin.CurrentUser.user,jsonstr);
						}
					}
				}
#endif
			}
		}
	
		tempstate=2;
	}

				/*
		
*/

/*
				sprintf(dirSmallstr,"d:\\%s %s %d.jpg",
					CarInfo->license,
					timestr,
					i);

				 CompressRGBToJPEG(CarInfo->pImageRGB24, CarInfo->nImageWidth, CarInfo->nImageHeight,
					0,75,dirSmallstr,0,0);
				int cw,ch;

				 CutImage(CarInfo->pImageRGB24, CarInfo->nImageWidth, CarInfo->nImageHeight,
					 CarInfo->rcLocation.left,CarInfo->rcLocation.top,
					 CarInfo->rcLocation.right,CarInfo->rcLocation.bottom,
					 JpgSmall, cw,ch, 3);

				 sprintf(dirSmallstr,"d:\\%s %s %d s.jpg",
					 CarInfo->license,
					 timestr,
					 i);

				 CompressRGBToJPEG(JpgSmall,cw,ch,
					 0,75,dirSmallstr,0,0);
					 */

	

	return tempstate;
}

void CHYZJCarDetect::CleanList(void)
{
	DlgMain->DlgTabVideo.m_ListImg.ClearImageList();
	DlgMain->DlgTabVideo.m_ListCar.DeleteAllItems();
	DlgMain->DlgTabVideo.m_ListCarTotal=0;

}


//ֹͣ����
void CHYZJCarDetect::Stop()
{
	if(1==State)
	{
		State=0;
		Sleep(100);
		LPR_UninitEx(CarHandle);
		//��Ϊ ~()�ͷź���ʱ���Ӵ˻����
		errorprintf("ʶ��ֹͣ�ɹ�");
		CarHandle=0;

		if(DlgMain->DlgTabVideo.DlgScreen.HYZJCarDetect_total>0)
			DlgMain->DlgTabVideo.DlgScreen.HYZJCarDetect_total--;
	}

	State=-1;

	CarTotal=0;

	JpgSize=0;
}


#endif
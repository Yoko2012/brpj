/******************************************************************************************
V2013-02-05 10:30:00
V2013-03-26 10:30:00 �޸�log����Ƭ�Ĵ洢·����Facecloud���ڵ�·��
******************************************************************************************/
#ifndef _FACE_CLOUD_DLL_
#define _FACE_CLOUD_DLL_

#ifdef FACE_CLOUD_API
#else
#define FACE_CLOUD_API _declspec(dllimport)
#endif

#include "include/rwfacerect.h"

/***********************************************************************
//˵������ʼ��FaceCloud
//���룺DLLpath	---- DLL���ڵ�λ��
//�������
//���أ�0		---- ��ʼ�����
        -1		---- ��ʼ��ʧ��
***********************************************************************/
extern "C" int FACE_CLOUD_API InitializeFaceCloud(char *DLLpath);

/***********************************************************************
//˵��������ʼ��FaceCloud
//���룺��
//�������
//���أ�0  ---- ����ʼ�����
        -1 ---- ����ʼ��ʧ��
***********************************************************************/
extern "C" int FACE_CLOUD_API UnInitializeFaceCloud(void);

/***********************************************************************
//˵������ȡ����
//���룺detectImage		---- ��Ƶͼ��
		size			---- ��Ƶͼ���С
		width			---- ��Ƶͼ��Ŀ�
		height			---- ��Ƶͼ���
		list_size		---- ��������
		face_rect_list	---- �������ο��б�
//�������
//���أ�0				---- ��ȡ�������
        -1				---- ��ȡ����ʧ��
***********************************************************************/
extern "C" int FACE_CLOUD_API YRDetectFace(unsigned char *detectImage, unsigned long int size, unsigned long int width, unsigned long int height, int &list_size, RwFaceRect *face_rect_list);


#endif
#ifndef RECONOVA_FACE_RECOGNITION_H__
#define RECONOVA_FACE_RECOGNITION_H__

#ifdef __linux
#define RWFACERECOG_API
#else

#ifdef RWFACERECOG_EXPORTS
#define RWFACERECOG_API __declspec(dllexport)
#else
#define RWFACERECOG_API __declspec(dllimport)
#endif

#endif


#include "rwinit.h"
#include "rwimage.h"
#include "rwfeature.h"
#include "rwfacerect.h"
#include "rwtrackdata.h"


/** ����ʶ���� */
typedef void * RwFaceRecogHandle;

/** ͼƬ�����󷵻������� */
#define MAX_DET_RESULT_COUNT 32 


/**
 * ��ʼ������ʶ��ģ��
 * @param [in] module_handle �ײ�ģ����
 * @return �����Ƿ�ɹ�
 * - 0 ��ʾ�ɹ�
 * - -1 ��ʾʧ��
 */
RWFACERECOG_API int InitializeFaceRecog(RwModuleHandle module_handle);

/**
 * ����ʼ������ʶ��ģ��
 * @return �����Ƿ�ɹ�
 * - 0 ��ʾ�ɹ�
 * - -1 ��ʾʧ��
 */
RWFACERECOG_API int UnInitializeFaceRecog(void);


/**
 * ��ȡ����ʶ����
 * @param [out] face_recog_handle ����ʶ����
 * @return �����Ƿ�ɹ�
 * - 0 ��ʾ�ɹ�
 * - -1 ��ʾʧ��
 */
RWFACERECOG_API int CreateFaceRecogHandle(
	RwFaceRecogHandle *face_recog_handle
);

/**
 * �ͷ�����ʶ����
 * @param [in] face_recog_handle ����ʶ����
 * @return �����Ƿ�ɹ�
 * - 0 ��ʾ�ɹ�
 * - -1 ��ʾʧ��
 */
RWFACERECOG_API int ReleaseFaceRecogHandle(
	RwFaceRecogHandle *face_recog_handle
	);

/**
 * ��ȡ������ͼ����
 * @param [in] face_recog_handle ����ʶ����
 * @param [out] face_width ������ͼͼ��Ŀ�
 * @param [out] face_height ������ͼͼ��ĸ�
 * @param [out] face_width_step ������ͼͼ���д�С
 * @param [out] face_data_size ������ͼͼ���С
 * @return �����Ƿ�ɹ�
 * - 0 ��ʾ�ɹ�
 * - -1 ��ʾʧ��
 */
RWFACERECOG_API int GetFaceImageParam(
	RwFaceRecogHandle face_recog_handle,
	int *face_width,
	int *face_height,
	int *face_width_step,
	int *face_data_size
);

/**
 * ��ȡ������ͼ����
 * @param [in] face_recog_handle ����ʶ����
 * @param [out] feature_size ������С
 * - ��ȡ������ʱ����Ҫ���ⲿ���������ڴ�
 * @return �����Ƿ�ɹ�
 * - 0 ��ʾ�ɹ�
 * - -1 ��ʾʧ��
 */
RWFACERECOG_API int GetFeatureParam(
	RwFaceRecogHandle face_recog_handle,
	int *feature_size
);

/**
 * ����ͼƬ������⣬��ȡ������ͼ���е�������Ϣ
 * @param [in] face_recog_handle ����ʶ����
 * @param [in] image ͼ����Ϣ
 * @param [in] scale_ratio ���ű������ڴ����ʱ�������ź���
 * - 1.0f ������
 * @param [out] list_size ͼ������������
 * @param [out] face_rect_list ͼ����������Ϣ����
 * - ͼƬ�����󷵻�������MAX_DET_RESULT_COUNT
 * @return �����Ƿ�ɹ�
 * - 0 ��ʾ�ɹ�
 * - -1 ��ʾʧ��
 */
RWFACERECOG_API int DetectFace(
	RwFaceRecogHandle face_recog_handle,
	RwImage &image,
	float scale_ratio,
	int *list_size,
	RwFaceRect *face_rect_list
);

/**
 * ��Ƶ������⣬��ȡ������ͼ���е�������Ϣ
 * @param [in] face_recog_handle ����ʶ����
 * @param [in] image ͼ����Ϣ
 * @param [in] img_time ͼ��ʱ�䣨���룩
 * @param [in] scale_ratio ���ű������ڴ����ʱ�������ź���
 * - 1.0f ������
 * @param [out] list_size ͼ������������
 * @param [out] face_rect_list ͼ����������Ϣ����
 * @param [out] track_data_list ͼ���и�����Ϣ������������Ϣ��Ӧ
 * @return �����Ƿ�ɹ�
 * - 0 ��ʾ�ɹ�
 * - -1 ��ʾʧ��
 */
RWFACERECOG_API int DetectFaceV(
	RwFaceRecogHandle face_recog_handle,
	RwImage &image,
	long img_time,
	float scale_ratio,
	int *list_size,
	RwFaceRect *face_rect_list,
	RwTrackData *track_data_list
);

/**
 * ��ȡ����ͼƬ�е�����
 * @param [in] face_recog_handle ����ʶ����
 * @param [in] image ͼ����Ϣ
 * @param [in] scale_ratio ���ű������ڴ����ʱ�������ź���
 * - 1.0f ������
 * @param [in&out] facerect ͼ���е���������Ϣ
 * - ����ʱ��д����ٺ�
 * @param [out] feature ������Ϣ
 * @param [out] face_image ����ͼ���ͼ��Ϣ
 * @return �����Ƿ�ɹ�
 * - 0 ��ʾ�ɹ�
 * - -1 ��ʾʧ��
 */
RWFACERECOG_API int ExtractFeature(
	RwFaceRecogHandle face_recog_handle,
	RwImage &image,
	float scale_ratio,
	RwFaceRect *facerect,
	RwFeature *feature,
	RwImage *face_image
	);

/**
 * ��ȡ��ƵͼƬ�е�����
 * @param [in] face_recog_handle ����ʶ����
 * @param [in] image ͼ����Ϣ
 * @param [in] scale_ratio ���ű������ڴ����ʱ�������ź���
 * - 1.0f ������
 * @param [in&out] facerect ͼ���е���������Ϣ
 * - ����ʱ��д����ٺ�
 * @param [in&out] track_data ������Ϣ
 * @param [out] feature ������Ϣ
 * @param [out] face_image ����ͼ���ͼ��Ϣ
 * @return �����Ƿ�ɹ�
 * - 0 ��ʾ�ɹ�
 * - -1 ��ʾʧ��
 */
RWFACERECOG_API int ExtractFeatureV(
	RwFaceRecogHandle face_recog_handle,
	RwImage &image,
	float scale_ratio,
	RwFaceRect *facerect,
	RwTrackData *track_data,
	RwFeature *feature,
	RwImage *face_image
);

#endif
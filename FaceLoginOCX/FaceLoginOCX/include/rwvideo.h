#ifndef RECONOVA_VIDEO_H__
#define RECONOVA_VIDEO_H__

#ifdef __linux
#define RWVIDEO_API
#else

#ifdef RWVIDEO_EXPORTS
#define RWVIDEO_API __declspec(dllexport)
#else
#define RWVIDEO_API __declspec(dllimport)
#endif

#endif


#include "rwinit.h"
#include "rwimage.h"
#include "rwfeature.h"
#include "rwtrackdata.h"
#include "rwvideoevent.h"


/** ��Ƶ�ӿڷ����б���󳤶� */
#define MAX_FEATURE_COUNT 20


/** ��Ƶ��� */
typedef void * RwVideoHandle;


/**
 * ��ȡ��Ƶ���
 * @param [in] video_handle ��Ƶ���
 * @return �����Ƿ�ɹ�
 * - 0 ��ʾ�ɹ�
 * - -1 ��ʾʧ��
 */
RWVIDEO_API int CreateVideoHandle(
	RwModuleHandle module_handle,
	RwVideoHandle *video_handle
);

/**
 * �ͷ���Ƶ���
 * @param [in] video_handle ��Ƶ���
 * @return �����Ƿ�ɹ�
 * - 0 ��ʾ�ɹ�
 * - -1 ��ʾʧ��
 */
RWVIDEO_API int ReleaseVideoHandle(RwVideoHandle *video_handle);

/**
 * ������Ƶ���
 * ���µ�һ����Ƶʶ�����ע��ǰ��Ҫ������Ƶ���
 * @param [in] video_handle ��Ƶ���
 * @return �����Ƿ�ɹ�
 * - 0 ��ʾ�ɹ�
 * - -1 ��ʾʧ��
 */
RWVIDEO_API int ResetVideoHandle(RwVideoHandle video_handle);

/**
 * �������Ƶʶ����Ҫ���������뵽��ʷ������
 * @param [in] video_handle ��Ƶ���
 * @param [in] cur_time ��Ƶʱ��
 * @param [in] similarity ������ƶ�
 * - һ���˵����������������������ƶ�
 * @param [in] list_size �б��С
 * @param [in] feature_list �����б�
 * @param [in] image_list ������ͼ�б�
 * @param [in] trackdata_list ����������Ϣ�б�
 * @param [out] event_count �¼�����
 * @return �����Ƿ�ɹ�
 * - 0 ��ʾ�ɹ�
 * - -1 ��ʾʧ��
 */
RWVIDEO_API int AddToDetect(
	RwVideoHandle video_handle,
	long cur_time,
	double similarity,
	int list_size,
	RwFeature *feature_list,
	RwImage *image_list,
	RwTrackData *trackdata_list,
	int *event_count
);

/**
 * ��ȡ��Ƶ���еĽ��
 * @param [in] video_handle ��Ƶ���
 * @param [out] feature_event_list ��Ƶ�¼��б�
 * - ��󳤶�MAX_FEATURE_COUNT
 * @return �����Ƿ�ɹ�
 * - 0 ��ʾ�ɹ�
 * - -1 ��ʾʧ��
 */
RWVIDEO_API int GetDetectResult(
	RwVideoHandle video_handle,
	RwVideoEvent *det_event_list
);


/**
 * �������Ƶע�ᣬ��Ҫ���������뵽��ʷ�����У��ܹ�ֱ�ӷ��ؽ��
 * @param [in] video_handle ��Ƶ���
 * @param [in] similarity ������ƶ�
 * - ע���������������С��������ƶ�
 * @param [in] feature ������Ϣ
 * @param [in] image ����ͼ����Ϣ
 * @param [in] trackdata ����������Ϣ
 * @param [out] list_size �����б���
 * - ��󳤶�MAX_FEATURE_COUNT
 * @return �����Ƿ�ɹ�
 * - 0 ��ʾ�ɹ�
 * - -1 ��ʾʧ��
 */
RWVIDEO_API int AddToRegister(
	RwVideoHandle video_handle,
	double similarity,
	RwFeature feature,
	RwImage image,
	RwTrackData trackdata,
	int *list_size
);

/**
 * ��ȡע��Ľ��
 * @param [in] video_handle ��Ƶ���
 * @param [out] feature_event_list ע���¼�
 * - ��󳤶�MAX_FEATURE_COUNT
 * @return �����Ƿ�ɹ�
 * - 0 ��ʾ�ɹ�
 * - -1 ��ʾʧ��
 */
RWVIDEO_API int GetRegisterResult(
	RwVideoHandle video_handle,
	RwVideoEvent *reg_event
	);

#endif
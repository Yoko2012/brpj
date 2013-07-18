#ifndef RECONOVA_RW_FEATURE_LIST_EVENT_H__
#define RECONOVA_RW_FEATURE_LIST_EVENT_H__


/**
 * @brief ��Ƶ�¼�����
 */
enum RwVideoEventType{
	/** ���� */
	FL_EVENT_TYPE_ENTER,
	/** � */
	FL_EVENT_TYPE_ACTIVITY,
	/** �뿪 */
	FL_EVENT_TYPE_LEAVE,
};


/**
 * @brief ��Ƶ�¼�
 */
typedef struct tagRwVideoEvent
{
	/** �¼����� */
	RwVideoEventType event_type;
	/** �¼�ʱ�� */
	long time;
	/** ���ٺ� */
	int track_no;
	/** �������к�ͼƬ���еĳ��� */
	int list_size;
	/** �������� */
	RwFeature **feature_list;
	/** ͼƬ���� */
	RwImage **image_list;
}RwVideoEvent;


#endif
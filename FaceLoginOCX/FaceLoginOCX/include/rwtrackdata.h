#ifndef RECONOVA_RW_TRACK_DATA_H__
#define RECONOVA_RW_TRACK_DATA_H__


/**
 * @brief ������Ϣ
 */
typedef struct tagRwTrackData
{
	/** ������Ϣ1 */
	int data1;
	/** ������Ϣ2 */
	int data2;
	/** ������Ϣ3 */
	int data3;
	/** ������Ϣ4 */
	int data4;
	/** Ԥ����Ϣ��С */
	int buff_size;
	/** Ԥ����Ϣָ�� */
	void* pri_buff;
}RwTrackData;

#endif
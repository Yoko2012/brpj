#ifndef RECONOVA_RW_FEATURE_H__
#define RECONOVA_RW_FEATURE_H__


/**
 * @brief ����������Ϣ
 */
typedef struct tagRwFeature
{
	/** ��������ָ�� */
	void *feature;
	/** ������С,ͨ��ReleaseFaceRecogInstance�ӿڷ��� */
	int feature_size;
}RwFeature;

#endif
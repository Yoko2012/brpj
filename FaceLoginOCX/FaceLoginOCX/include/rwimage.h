#ifndef RECONOVA_RW_IMAGE_H__
#define RECONOVA_RW_IMAGE_H__

/**
 * @brief ͼ����Ϣ
 */
typedef struct tagRwImage
{
	/** ͼ������ */
	unsigned char *imagedata;
	/** ͼ�����ݴ�С */
	int image_size;
	/** ͼ��� */
	int width;
	/** ͼ��� */
	int height;
	/** ͼ���д�С */
	int widthStep;
}RwImage;

#endif
#ifndef RECONOVA_RW_FACE_RECT_H__
#define RECONOVA_RW_FACE_RECT_H__

/**
 * @brief ������Ϣ
 */
typedef struct tagRwFaceRect
{
	/** �����ĸ��ٺ� */
	int track_no;

	/** �������ο����Ͻǵ�x���� */
	int left;
	/** �������ο����Ͻǵ�y���� */
	int top;
	/** �������ο����½ǵ�x���� */
	int right;
	/** �������ο����½ǵ�y���� */
	int bottom;

	/** �������۵�x���� */
	int lefteye_x;
	/** �������۵�y���� */
	int lefteye_y;
	/** �������۵�x���� */
	int righteye_x;
	/** �������۵�y���� */
	int righteye_y;
	/** �������ӵ�x���� */
	int nose_x;
	/** �������ӵ�y���� */
	int nose_y;
	/** ������͵�x���� */
	int centermouth_x;
	/** ������͵�y���� */
	int centermouth_y;
}RwFaceRect;

#endif
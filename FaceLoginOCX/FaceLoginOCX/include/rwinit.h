#ifndef RECONOVA_INITIALIZATION_H__
#define RECONOVA_INITIALIZATION_H__


#ifdef __linux
#define RWINIT_API
#else

#ifdef RWINIT_EXPORTS
#define RWINIT_API __declspec(dllexport)
#else
#define RWINIT_API __declspec(dllimport)
#endif

#endif


/** ģ���� */
typedef void * RwModuleHandle;

/**
 * ��ʼ��ģ�飬��Ҫ���õ�ǰ����Ŀ¼��exe����Ŀ¼
 * @param [in] path ����Ŀ¼
 * ..//Relesae
 * @return �����Ƿ�ɹ�
 * - 0 ��ʾ�ɹ�
 * - -1 ��ʾʧ��
 */
RWINIT_API int InitializeModule(
	const char *path,
	RwModuleHandle *module_handle
);

/**
 * ����ʼ������ģ��
 * @return �����Ƿ�ɹ�
 * - 0 ��ʾ�ɹ�
 * - -1 ��ʾʧ��
 */
RWINIT_API int UnInitializeModule(void);


#endif
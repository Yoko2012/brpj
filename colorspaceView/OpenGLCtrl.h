#pragma once

#include <GL/gl.h>
#include <GL/glu.h>

#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")

//////////////////////////////////////////////////////////////////////
//-	�궨��

#define		CTRL_CLASS_NAME		_T("COpenGLCtrl")

// COpenGLCtrl

class COpenGLCtrl : public CWnd
{
	DECLARE_DYNAMIC(COpenGLCtrl)

	CDC*		m_pDC;
	HGLRC		m_hRC;

	GLfloat		m_glfViewPosX, m_glfViewPosY, m_glfViewPosZ,				//�ӵ�����
				m_glfTargetPosX, m_glfTargetPosY, m_glfTargetPosZ,			//�۲�Ŀ�������
				m_glfCamDirectX, m_glfCamDirectY, m_glfCamDirectZ,			//�������
				m_glfGridUnit;
	COLORREF	m_clrBackgroud, m_clrGridAxse, m_clrGridLine;				//�����������ɫ
	int			m_nLines;

public:

	enum { MS_LBBTN = 0, MS_MBBTN, MS_RBBTN };

public:
	COpenGLCtrl();
	virtual ~COpenGLCtrl();

	void		RegisterCtrlClass();
	void		SetSceneSize(GLsizei glsWidth, GLsizei glsHeight);
	void		InitOpenGL();
	void		RenderScene();
	COLORREF	GetBkgColor(){return m_clrBackgroud;}
	void		SetBkgColor(COLORREF clrBkg){m_clrBackgroud = clrBkg;}

protected:
	virtual void PreSubclassWindow();
 
public:
	afx_msg void OnPaint();
	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);

	DECLARE_MESSAGE_MAP()
};
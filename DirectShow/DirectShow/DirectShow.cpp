// DirectShow.cpp : Defines the exported functions for the DLL application.
//


#include "stdafx.h"
#include "DirectShow.h"

#ifdef _MANAGED
#pragma managed(push, off)
#endif

#pragma   data_seg   ("m_pGraph")  
	CComPtr<IGraphBuilder> m_pGraph = NULL;//��������  
#pragma   data_seg()
	#pragma   data_seg   ("m_pDeviceFilter")  
	CComPtr<IBaseFilter> m_pDeviceFilter = NULL;//��������  
#pragma   data_seg()
	#pragma   data_seg   ("m_pMediaControl")  
	CComPtr<IMediaControl> m_pMediaControl = NULL;//��������  
#pragma   data_seg()
	#pragma   data_seg   ("m_pSampleGrabberFilter")  
	CComPtr<IBaseFilter> m_pSampleGrabberFilter = NULL;//��������  
#pragma   data_seg()
	#pragma   data_seg   ("m_pSampleGrabber")  
	CComPtr<ISampleGrabber> m_pSampleGrabber = NULL;//��������  
#pragma   data_seg()
	#pragma   data_seg   ("m_pSampleGrabberInput")  
	CComPtr<IPin> m_pSampleGrabberInput = NULL;//��������  
#pragma   data_seg()
	#pragma   data_seg   ("m_pSampleGrabberOutput")  
	CComPtr<IPin> m_pSampleGrabberOutput = NULL;//��������  
#pragma   data_seg()
	#pragma   data_seg   ("m_pCameraOutput")  
	CComPtr<IPin> m_pCameraOutput = NULL;//��������  
#pragma   data_seg()
	#pragma   data_seg   ("m_pMediaEvent")  
	CComPtr<IMediaEvent> m_pMediaEvent = NULL;//��������  
#pragma   data_seg()
	#pragma   data_seg   ("m_pNullFilter")  
	CComPtr<IBaseFilter> m_pNullFilter = NULL;//��������  
#pragma   data_seg()
	#pragma   data_seg   ("m_pNullInputPin")  
	CComPtr<IPin> m_pNullInputPin = NULL;//��������  
#pragma   data_seg()
	#pragma   data_seg   ("m_pNullInputPin")  
	CComPtr<ICaptureGraphBuilder2> g_pCapture = NULL;//��������  
#pragma   data_seg()

#pragma   data_seg   ("m_nBufferSize")  
	long m_nBufferSize = 0;//��������  
#pragma   data_seg()

#pragma   data_seg   ("m_bConnected")  
	bool m_bConnected = false;//��������  
#pragma   data_seg()

#pragma   data_seg   ("m_bConnected2")  
	bool m_bConnected2 = false;//��������  
#pragma   data_seg()

	
//	#pragma   data_seg   ("pGraphBuilder")  
//	IGraphBuilder *pGraphBuilder;//��������  
//#pragma   data_seg()
//		#pragma   data_seg   ("pMediaControl")  
//	IMediaControl *pMediaControl;//��������  
//#pragma   data_seg()
//		#pragma   data_seg   ("pBasicVideo")  
//	IBasicVideo *pBasicVideo;//��������  
//#pragma   data_seg()
	//#pragma   data_seg()
		#pragma   data_seg   ("m_pBasicVideo")  
	CComPtr<IBasicVideo> m_pBasicVideo = NULL;//��������  
#pragma   data_seg()
			#pragma   data_seg   ("m_pVideoWindow")  
	CComPtr<IVideoWindow> m_pVideoWindow = NULL;//��������  
#pragma   data_seg()
		
bool BindFilter(int nCamID, IBaseFilter **pFilter);
BYTE * pBuffer1; 
long lBufferSize1;

#ifdef _MANAGED
#pragma managed(pop)
#endif

class CSampleGrabberCB : public ISampleGrabberCB 
{
public:
	long lWidth;
	long lHeight;
	TCHAR m_szFileName[MAX_PATH];// λͼ�ļ�����
	CSampleGrabberCB()
	{
	} 
	STDMETHODIMP_(ULONG) AddRef() { return 2; }
	STDMETHODIMP_(ULONG) Release() { return 1; }
	STDMETHODIMP QueryInterface(REFIID riid, void ** ppv)
	{
		if( riid == IID_ISampleGrabberCB || riid == IID_IUnknown )
		{ 
			*ppv = (void *) static_cast<ISampleGrabberCB*> ( this );
			return NOERROR;
		} 
		return E_NOINTERFACE;
	}
	STDMETHODIMP SampleCB( double SampleTime, IMediaSample * pSample )
	{
		return 0;
	}
	STDMETHODIMP BufferCB( double dblSampleTime, BYTE * pBuffer, long lBufferSize )
	{
		lBufferSize1 = lBufferSize;
		pBuffer1 = pBuffer;
		return 0;
	}
};
CSampleGrabberCB mCB;

//////////////////////////////////////////////////////////////////////////////////
bool BindFilter(int nCamID, IBaseFilter **pFilter)
{
	if (nCamID < 0)
		return false;
	
	// enumerate all video capture devices
	CComPtr<ICreateDevEnum> pCreateDevEnum;
	HRESULT hr = CoCreateInstance(CLSID_SystemDeviceEnum, NULL, CLSCTX_INPROC_SERVER,
		IID_ICreateDevEnum, (void**)&pCreateDevEnum);
	if (hr != NOERROR)
	{
		return false;
	}
	
	CComPtr<IEnumMoniker> pEm;
	hr = pCreateDevEnum->CreateClassEnumerator(CLSID_VideoInputDeviceCategory,
		&pEm, 0);
	if (hr != NOERROR) 
	{
		return false;
	}
	
	pEm->Reset();
	ULONG cFetched;
	IMoniker *pM;
	int index = 0;
	while(hr = pEm->Next(1, &pM, &cFetched), hr==S_OK, index <= nCamID)
	{
		IPropertyBag *pBag;
		hr = pM->BindToStorage(0, 0, IID_IPropertyBag, (void **)&pBag);
		if(SUCCEEDED(hr)) 
		{
			VARIANT var;
			var.vt = VT_BSTR;
			hr = pBag->Read(L"FriendlyName", &var, NULL);
			if (hr == NOERROR) 
			{
				if (index == nCamID)
				{
					pM->BindToObject(0, 0, IID_IBaseFilter, (void**)pFilter);
				}
				SysFreeString(var.bstrVal);
			}
			pBag->Release();
		}
		pM->Release();
		index++;
	}
	
	pCreateDevEnum = NULL;
	return true;
}
//////////////////////////////////////////////////////////////////////////////////

extern "C" {
	//��ȡ�豸����
	DIRECTSHOW_API int GetCameraCount(void)
	{
		int count = 0;
 		CoInitialize(NULL);

	   // enumerate all video capture devices
		CComPtr<ICreateDevEnum> pCreateDevEnum;
		HRESULT hr = CoCreateInstance(CLSID_SystemDeviceEnum, NULL, CLSCTX_INPROC_SERVER,
										IID_ICreateDevEnum, (void**)&pCreateDevEnum);

		CComPtr<IEnumMoniker> pEm;
		hr = pCreateDevEnum->CreateClassEnumerator(CLSID_VideoInputDeviceCategory,
			&pEm, 0);
		if (hr != NOERROR) 
		{
			return count;
		}

		pEm->Reset();
		ULONG cFetched;
		IMoniker *pM;
		while(hr = pEm->Next(1, &pM, &cFetched), hr==S_OK)
		{
			count++;
		}

		pCreateDevEnum = NULL;
		pEm = NULL;
		return count;
	}

	//��ȡ����ͷ����
	DIRECTSHOW_API int GetCameraName(int nCamID, char* sName, int nBufferSize)
	{
		int count = 0;
 		CoInitialize(NULL);

	   // enumerate all video capture devices
		CComPtr<ICreateDevEnum> pCreateDevEnum;
		HRESULT hr = CoCreateInstance(CLSID_SystemDeviceEnum, NULL, CLSCTX_INPROC_SERVER,
										IID_ICreateDevEnum, (void**)&pCreateDevEnum);

		CComPtr<IEnumMoniker> pEm;
		hr = pCreateDevEnum->CreateClassEnumerator(CLSID_VideoInputDeviceCategory,
			&pEm, 0);
		if (hr != NOERROR) return 0;


		pEm->Reset();
		ULONG cFetched;
		IMoniker *pM;
		while(hr = pEm->Next(1, &pM, &cFetched), hr==S_OK)
		{
			if (count == nCamID)
			{
				IPropertyBag *pBag=0;
				hr = pM->BindToStorage(0, 0, IID_IPropertyBag, (void **)&pBag);
				if(SUCCEEDED(hr))
				{
					VARIANT var;
					var.vt = VT_BSTR;
					hr = pBag->Read(L"FriendlyName", &var, NULL); //������������,��������Ϣ�ȵ�...
					if(hr == NOERROR)
					{
						//��ȡ�豸����			
						WideCharToMultiByte(CP_ACP,0,var.bstrVal,-1,sName, nBufferSize ,"",NULL);

						SysFreeString(var.bstrVal);				
					}
					pBag->Release();
				}
				pM->Release();

				break;
			}
			count++;
		}

		pCreateDevEnum = NULL;
		pEm = NULL;

		return 1;
	}

	//�ر�����ͷ
	DIRECTSHOW_API void CloseCamera()
	{	
		if(m_bConnected2)
		{
			m_pVideoWindow->put_Visible(OAFALSE);
			m_pVideoWindow->put_Owner(NULL);
		}
		if(m_bConnected)
			m_pMediaControl->Stop();

		m_pGraph = NULL;
		m_pDeviceFilter = NULL;
		m_pMediaControl = NULL;
		m_pSampleGrabberFilter = NULL;
		m_pSampleGrabber = NULL;
		m_pSampleGrabberInput = NULL;
		m_pSampleGrabberOutput = NULL;
		m_pCameraOutput = NULL;
		m_pMediaEvent = NULL;
		m_pNullFilter = NULL;
		m_pNullInputPin = NULL;
		m_pVideoWindow = NULL;
		g_pCapture = NULL;
		m_nBufferSize = 0;
		m_pBasicVideo = NULL;
		pBuffer1 = NULL;
		lBufferSize1 = 0;
		if(m_bConnected)
			CoUninitialize();
		m_bConnected = false;

	}

	//������ͷ
	DIRECTSHOW_API bool OpenCameraCB(int nCamID, bool bDisplayProperties, LONG * nWidth, LONG * nHeight)
	{		
		HRESULT hr = S_OK;
		CoInitialize(NULL);

		hr = CoCreateInstance(CLSID_FilterGraph, NULL, CLSCTX_INPROC,
								IID_IGraphBuilder, (void **)&m_pGraph);

		hr = CoCreateInstance(CLSID_SampleGrabber, NULL, CLSCTX_INPROC_SERVER, 
								IID_IBaseFilter, (LPVOID *)&m_pSampleGrabberFilter);

		// Create the capture graph builder
		hr = CoCreateInstance (CLSID_CaptureGraphBuilder2 , NULL, CLSCTX_INPROC,
                           IID_ICaptureGraphBuilder2, (void **) &g_pCapture);
		if (FAILED(hr))
			return false;

		hr = m_pGraph->QueryInterface(IID_IMediaControl, (void **) &m_pMediaControl);

		hr   =   m_pGraph-> QueryInterface(IID_IVideoWindow,(void**)&m_pVideoWindow);

		hr = m_pSampleGrabberFilter->QueryInterface(IID_ISampleGrabber, (void**)&m_pSampleGrabber);
		// Attach the filter graph to the capture graph
		hr = g_pCapture->SetFiltergraph(m_pGraph);
		// Bind Device Filter.  We know the device because the id was passed in
		BindFilter(nCamID, &m_pDeviceFilter);

		hr = m_pGraph->AddFilter(m_pDeviceFilter, L"Capture Filter");
		if( !m_pSampleGrabber )
		{
			//AfxMessageBox("Fail to create SampleGrabber, maybe qedit.dll is not registered?");
			return FALSE;
		}

		//������Ƶ��ʽ
		AM_MEDIA_TYPE mt; 
		ZeroMemory(&mt, sizeof(AM_MEDIA_TYPE));
		mt.majortype = MEDIATYPE_Video;
		mt.subtype = MEDIASUBTYPE_RGB24;
		hr = m_pSampleGrabber->SetMediaType(&mt);

		if( FAILED( hr ) )
		{
			//AfxMessageBox("Fail to set media type!");
			return FALSE;
		}
		hr = m_pGraph->AddFilter( m_pSampleGrabberFilter, L"Grabber" );
		if( FAILED( hr ) )
		{
			//AfxMessageBox("Fail to put sample grabber in graph");
			return FALSE;
		}

		// try to render preview/capture pin
		hr = g_pCapture->RenderStream(&PIN_CATEGORY_PREVIEW, &MEDIATYPE_Video,m_pDeviceFilter,m_pSampleGrabberFilter,NULL);
		if( FAILED( hr ) )
		hr = g_pCapture->RenderStream(&PIN_CATEGORY_CAPTURE, &MEDIATYPE_Video,m_pDeviceFilter,m_pSampleGrabberFilter,NULL);

		if( FAILED( hr ) )
		{
			//AfxMessageBox("Can��t build the graph");
			return FALSE;
		}

		hr = m_pSampleGrabber->GetConnectedMediaType( &mt );
		if ( FAILED( hr) )
		{
			//AfxMessageBox("Failt to read the connected media type");
			return FALSE;
		}

		VIDEOINFOHEADER * vih = (VIDEOINFOHEADER*) mt.pbFormat;
		mCB.lWidth = vih->bmiHeader.biWidth;
		mCB.lHeight = vih->bmiHeader.biHeight;
		*nWidth =  vih->bmiHeader.biWidth;
		*nHeight = vih->bmiHeader.biHeight;

		if (mt.cbFormat != 0) 
		{
			CoTaskMemFree((PVOID)mt.pbFormat);
			// Strictly unnecessary but tidier
			mt.cbFormat = 0;
			mt.pbFormat = NULL;
		}
		if (mt.pUnk != NULL) 
		{
			mt.pUnk->Release();
			mt.pUnk = NULL;
		}		
		hr = m_pSampleGrabber->SetBufferSamples( FALSE );
		hr = m_pSampleGrabber->SetOneShot( FALSE );
		hr = m_pSampleGrabber->SetCallback( &mCB, 1 );

		//������Ƶ��׽����
		//m_hWnd = hWnd ; 
		//SetupVideoWindow();
		m_pVideoWindow-> put_Visible(OAFALSE);//
		m_pVideoWindow->put_AutoShow(OAFALSE);//activemovie window ����ʾ
		m_pVideoWindow-> put_Owner(NULL); 
		hr = m_pMediaControl->Run();//��ʼ��Ƶ��׽
				

		if(FAILED(hr))
		{
			//AfxMessageBox("Couldn��t run the graph!");
			return FALSE;
		}
		m_bConnected = true;

		return TRUE;
	}

	//��ȡ����ͷ֡����
	DIRECTSHOW_API int QueryFrameCB(long * bufferSize, char ** buffer)
	{
		if(lBufferSize1 > 0 && pBuffer1 != NULL)
		{
			*bufferSize = lBufferSize1;
			//char * pBuffer = (char *)malloc(lBufferSize1);
			//memcpy(pBuffer,pBuffer1,lBufferSize1);


			*buffer = (char*)pBuffer1;
			return 1;

		}
		else
		{
			*buffer = NULL;
			*bufferSize = 0;
			return 0;
		}
	}
}



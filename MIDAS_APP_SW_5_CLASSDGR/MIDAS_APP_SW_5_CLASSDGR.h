
// MIDAS_APP_SW_5_CLASSDGR.h : MIDAS_APP_SW_5_CLASSDGR ���� ���α׷��� ���� �� ��� ����
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"       // �� ��ȣ�Դϴ�.
#include "Brushs.h"

// CMIDAS_APP_SW_5_CLASSDGRApp:
// �� Ŭ������ ������ ���ؼ��� MIDAS_APP_SW_5_CLASSDGR.cpp�� �����Ͻʽÿ�.
//

class CMIDAS_APP_SW_5_CLASSDGRApp : public CWinApp
{
public:
	CMIDAS_APP_SW_5_CLASSDGRApp();
	Brushs* viewBrushPtr;

// �������Դϴ�.
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// �����Դϴ�.
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMIDAS_APP_SW_5_CLASSDGRApp theApp;

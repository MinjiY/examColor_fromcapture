
// ExamColor.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CExamColorApp:
// �� Ŭ������ ������ ���ؼ��� ExamColor.cpp�� �����Ͻʽÿ�.
//

class CExamColorApp : public CWinApp
{
public:
	CExamColorApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CExamColorApp theApp;
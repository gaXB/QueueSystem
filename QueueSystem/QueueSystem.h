
// QueueSystem.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������



// CQueueSystemApp:
// �йش����ʵ�֣������ QueueSystem.cpp
//


//typedef  teamType[10][]  TeamAType;


class CQueueSystemApp : public CWinApp
{
public:
	CQueueSystemApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()

};

extern CQueueSystemApp theApp;
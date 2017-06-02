
// KZLib.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//
#include "ReaderInfo.h"
#include "BookInfo.h"

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CKZLibApp:
// �йش����ʵ�֣������ KZLib.cpp
//

class CKZLibApp : public CWinApp
{
public:
	CKZLibApp();

	CList<ReaderInfo, ReaderInfo&> readerList;
	CList<BookInfo, BookInfo&> bookList;

	BOOL RemoveReader(int position);
	BOOL RemoveBookInfo(int position);

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()

	
};

extern CKZLibApp theApp;
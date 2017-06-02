
// KZLib.h : PROJECT_NAME 应用程序的主头文件
//
#include "ReaderInfo.h"
#include "BookInfo.h"

#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"		// 主符号


// CKZLibApp:
// 有关此类的实现，请参阅 KZLib.cpp
//

class CKZLibApp : public CWinApp
{
public:
	CKZLibApp();

	CList<ReaderInfo, ReaderInfo&> readerList;
	CList<BookInfo, BookInfo&> bookList;

	BOOL RemoveReader(int position);
	BOOL RemoveBookInfo(int position);

// 重写
public:
	virtual BOOL InitInstance();

// 实现

	DECLARE_MESSAGE_MAP()

	
};

extern CKZLibApp theApp;
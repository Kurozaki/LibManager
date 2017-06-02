#include "BookInfo.h"

#pragma once


// CBookMgr 对话框

class CBookMgr : public CDialogEx
{
	DECLARE_DYNAMIC(CBookMgr)

public:
	CBookMgr(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CBookMgr();

// 对话框数据
	enum { IDD = IDD_BOOKMGR };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonDelBook();
	afx_msg void OnBnClickedButtonAddbook();
	int AddBookInfo(BookInfo bInfo);
	afx_msg void OnDblclkLcBookinfo(NMHDR *pNMHDR, LRESULT *pResult);

	CListCtrl* mBookListCtrl;
	CString saveFilePath;
//	virtual BOOL DestroyWindow();
	virtual void PostNcDestroy();
	void RefreshBookInfo(void);
};

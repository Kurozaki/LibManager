#include "BookInfo.h"

#pragma once


// CBookMgr �Ի���

class CBookMgr : public CDialogEx
{
	DECLARE_DYNAMIC(CBookMgr)

public:
	CBookMgr(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CBookMgr();

// �Ի�������
	enum { IDD = IDD_BOOKMGR };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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

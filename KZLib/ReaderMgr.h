#include "ReaderInfoInputDlg.h"
#include "ReaderInfo.h"

#pragma once


// CReaderMgr 对话框

class CReaderMgr : public CDialogEx
{
	DECLARE_DYNAMIC(CReaderMgr)

public:
	CReaderMgr(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CReaderMgr();
	
	int AddReader(ReaderInfo info);

// 对话框数据
	enum { IDD = IDD_READERMGR };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	
	afx_msg void OnBnClickedButtonAddreader();

private:
	CListCtrl* mReaderListCtrl;
	CString saveFilePath;

public:
	afx_msg void OnBnClickedButtonDelReader();
	afx_msg void OnDblclkLcReader(NMHDR *pNMHDR, LRESULT *pResult);
	virtual void PostNcDestroy();
};

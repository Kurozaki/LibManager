#include "LendRec.h"

#pragma once


// CLendMgr �Ի���

class CLendMgr : public CDialogEx
{
	DECLARE_DYNAMIC(CLendMgr)

public:
	CLendMgr(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CLendMgr();

// �Ի�������
	enum { IDD = IDD_LENDMGR };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

private:
	CListCtrl* mLendListCtrl;
	CString saveFilePath;
	CList<LendRec, LendRec&> mLendRecList;

public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonAddrec();
	afx_msg void OnBnClickedButtonDelrec();
	int AddLendRec(LendRec recInfo);
	virtual void PostNcDestroy();
	afx_msg void OnDblclkLcLendinfo(NMHDR *pNMHDR, LRESULT *pResult);
};

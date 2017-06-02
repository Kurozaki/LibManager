
// KZLibDlg.h : ͷ�ļ�
//
#include "BookMgr.h"
#include "ReaderMgr.h"
#include "LendMgr.h"

#pragma once


// CKZLibDlg �Ի���
class CKZLibDlg : public CDialogEx
{
// ����
public:
	CKZLibDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_KZLIB_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

private:
	CBookMgr mBookMgr;
	CReaderMgr mReaderMgr;
	CLendMgr mLendInfoMgr;

	CTabCtrl* mMainTabCtrl;
	

// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnSelchangeMainTab(NMHDR *pNMHDR, LRESULT *pResult);
};

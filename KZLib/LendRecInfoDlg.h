#include "LendRec.h"

#pragma once


// LendRecInfoDlg �Ի���

class LendRecInfoDlg : public CDialog
{
	DECLARE_DYNAMIC(LendRecInfoDlg)

public:
	LendRecInfoDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~LendRecInfoDlg();

	LendRec mLendRec;
	BOOL isExp;

// �Ի�������
	enum { IDD = IDD_LENDRECINFODLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonRecinfoClose();
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};

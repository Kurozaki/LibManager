#include "LendRec.h"

#pragma once


// LendRecInputDlg �Ի���

class LendRecInputDlg : public CDialogEx
{
	DECLARE_DYNAMIC(LendRecInputDlg)

public:
	LendRecInputDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~LendRecInputDlg();
	LendRec recInfo;


// �Ի�������
	enum { IDD = IDD_LENDRECINPUTDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	DECLARE_MESSAGE_MAP()


public:
	afx_msg void OnBnClickedButtionRecdlgAdd();
	afx_msg void OnBnClickedButtonRecdlgCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeComboLendbookname();
};

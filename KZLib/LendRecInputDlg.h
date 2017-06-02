#include "LendRec.h"

#pragma once


// LendRecInputDlg 对话框

class LendRecInputDlg : public CDialogEx
{
	DECLARE_DYNAMIC(LendRecInputDlg)

public:
	LendRecInputDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~LendRecInputDlg();
	LendRec recInfo;


// 对话框数据
	enum { IDD = IDD_LENDRECINPUTDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	DECLARE_MESSAGE_MAP()


public:
	afx_msg void OnBnClickedButtionRecdlgAdd();
	afx_msg void OnBnClickedButtonRecdlgCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeComboLendbookname();
};

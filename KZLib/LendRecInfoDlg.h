#include "LendRec.h"

#pragma once


// LendRecInfoDlg 对话框

class LendRecInfoDlg : public CDialog
{
	DECLARE_DYNAMIC(LendRecInfoDlg)

public:
	LendRecInfoDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~LendRecInfoDlg();

	LendRec mLendRec;
	BOOL isExp;

// 对话框数据
	enum { IDD = IDD_LENDRECINFODLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonRecinfoClose();
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};

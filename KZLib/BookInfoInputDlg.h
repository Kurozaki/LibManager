#include "BookInfo.h"

#pragma once


// BookInfoInputDlg 对话框

class BookInfoInputDlg : public CDialog
{
	DECLARE_DYNAMIC(BookInfoInputDlg)

public:
	BookInfoInputDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~BookInfoInputDlg();

	BookInfo mInfo;
	BOOL isEditMode;

// 对话框数据
	enum { IDD = IDD_BOOKINFOINPUTDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonBookinfoAdd();
	afx_msg void OnBnClickedButtonBookinfoCancel();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL OnInitDialog();
};

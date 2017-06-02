#include "ReaderInfo.h"

#pragma once


// ReaderInfoInputDlg 对话框

class ReaderInfoInputDlg : public CDialog
{
	DECLARE_DYNAMIC(ReaderInfoInputDlg)

public:
	ReaderInfoInputDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~ReaderInfoInputDlg();

	CString inputName;
	CString inputIDNumber;
	BOOL isEditMode;

// 对话框数据
	enum { IDD = IDD_READERINFOINPUTDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonAddreaderAdd();
	afx_msg void OnBnClickedButtonAddreaderCancel();

	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL OnInitDialog();
};

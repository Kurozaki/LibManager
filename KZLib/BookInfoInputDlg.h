#include "BookInfo.h"

#pragma once


// BookInfoInputDlg �Ի���

class BookInfoInputDlg : public CDialog
{
	DECLARE_DYNAMIC(BookInfoInputDlg)

public:
	BookInfoInputDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~BookInfoInputDlg();

	BookInfo mInfo;
	BOOL isEditMode;

// �Ի�������
	enum { IDD = IDD_BOOKINFOINPUTDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonBookinfoAdd();
	afx_msg void OnBnClickedButtonBookinfoCancel();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL OnInitDialog();
};

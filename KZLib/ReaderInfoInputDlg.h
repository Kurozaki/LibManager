#include "ReaderInfo.h"

#pragma once


// ReaderInfoInputDlg �Ի���

class ReaderInfoInputDlg : public CDialog
{
	DECLARE_DYNAMIC(ReaderInfoInputDlg)

public:
	ReaderInfoInputDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~ReaderInfoInputDlg();

	CString inputName;
	CString inputIDNumber;
	BOOL isEditMode;

// �Ի�������
	enum { IDD = IDD_READERINFOINPUTDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonAddreaderAdd();
	afx_msg void OnBnClickedButtonAddreaderCancel();

	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL OnInitDialog();
};

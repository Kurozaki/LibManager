// ReaderInfoInputDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "KZLib.h"
#include "ReaderInfoInputDlg.h"
#include "afxdialogex.h"
#include "ReaderInfo.h"


// ReaderInfoInputDlg �Ի���

IMPLEMENT_DYNAMIC(ReaderInfoInputDlg, CDialog)

ReaderInfoInputDlg::ReaderInfoInputDlg(CWnd* pParent /*=NULL*/)
	: CDialog(ReaderInfoInputDlg::IDD, pParent)
{
	isEditMode = FALSE;
}

ReaderInfoInputDlg::~ReaderInfoInputDlg()
{
}

void ReaderInfoInputDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(ReaderInfoInputDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_ADDREADER_ADD, &ReaderInfoInputDlg::OnBnClickedButtonAddreaderAdd)
	ON_BN_CLICKED(IDC_BUTTON_ADDREADER_CANCEL, &ReaderInfoInputDlg::OnBnClickedButtonAddreaderCancel)
//	ON_WM_KEYDOWN()
//ON_WM_KEYDOWN()
END_MESSAGE_MAP()


// ReaderInfoInputDlg ��Ϣ�������


void ReaderInfoInputDlg::OnBnClickedButtonAddreaderAdd()
{
	CEdit* mNameEidt;
	CEdit* mIDNEdit;

	mNameEidt = (CEdit *)GetDlgItem(IDC_EDIT_ADDREADER_NAME);
	mIDNEdit = (CEdit *)GetDlgItem(IDC_EDIT_ADDREADER_IDN);
	
	mNameEidt->GetWindowText(inputName);
	mIDNEdit->GetWindowText(inputIDNumber);

	if(inputName.GetLength() == 0 || inputIDNumber.GetLength() == 0)
	{
		MessageBox(_T("������Ϣ����Ϊ�գ�"), _T("��ʾ"), MB_OK);
		return;
	}	

	ReaderInfoInputDlg::OnOK();
}


void ReaderInfoInputDlg::OnBnClickedButtonAddreaderCancel()
{
	ReaderInfoInputDlg::OnCancel();
}


BOOL ReaderInfoInputDlg::PreTranslateMessage(MSG* pMsg)
{
	if(pMsg->message == WM_KEYDOWN){
		if(pMsg->wParam == VK_RETURN){
			return TRUE; 
		}
	}

	return CDialog::PreTranslateMessage(pMsg);
}


BOOL ReaderInfoInputDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	if(isEditMode){
		SetDlgItemText(IDC_EDIT_ADDREADER_NAME, inputName);
		SetDlgItemText(IDC_EDIT_ADDREADER_IDN, inputIDNumber);
		
		SetDlgItemText(IDC_BUTTON_ADDREADER_ADD, _T("ȷ���޸�"));
		SetWindowText(_T("�༭������Ϣ"));
	}

	return TRUE;  
}

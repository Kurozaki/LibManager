// BookInfoInputDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "KZLib.h"
#include "BookInfoInputDlg.h"
#include "afxdialogex.h"


// BookInfoInputDlg �Ի���

IMPLEMENT_DYNAMIC(BookInfoInputDlg, CDialog)

BookInfoInputDlg::BookInfoInputDlg(CWnd* pParent /*=NULL*/)
	: CDialog(BookInfoInputDlg::IDD, pParent)
{
	isEditMode = FALSE;
}

BookInfoInputDlg::~BookInfoInputDlg()
{
}

void BookInfoInputDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(BookInfoInputDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_BOOKINFO_ADD, &BookInfoInputDlg::OnBnClickedButtonBookinfoAdd)
	ON_BN_CLICKED(IDC_BUTTON_BOOKINFO_CANCEL, &BookInfoInputDlg::OnBnClickedButtonBookinfoCancel)
END_MESSAGE_MAP()


// BookInfoInputDlg ��Ϣ�������


void BookInfoInputDlg::OnBnClickedButtonBookinfoAdd()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	bool nullFlag = false;

	GetDlgItemText(IDC_EDIT_BOOKINFO_CODE, mInfo.mCode);
	GetDlgItemText(IDC_EDIT_BOOKINFO_NAME, mInfo.mName);
	GetDlgItemText(IDC_EDIT_BOOKINFO_AUTHOR, mInfo.mAuthor);
	GetDlgItemText(IDC_EDIT_BOOKINFO_PUBLISH, mInfo.mPublish);
	CString countStr;
	GetDlgItemText(IDC_EDIT_BOOKINFO_COUNT, countStr);
	mInfo.mKeepCount = _ttoi(countStr);

	nullFlag = mInfo.mCode.GetLength() == 0;
	nullFlag = mInfo.mName.GetLength() == 0;
	nullFlag = mInfo.mAuthor.GetLength() == 0;
	nullFlag = mInfo.mPublish.GetLength() == 0;
	nullFlag = countStr.GetLength() == 0;

	if(nullFlag){
		MessageBox(_T("������Ϣ����Ϊ��"), _T("��ʾ"), MB_OK);
		return;
	}

	CDialog::OnOK();
}


void BookInfoInputDlg::OnBnClickedButtonBookinfoCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialog::OnCancel();
}


BOOL BookInfoInputDlg::PreTranslateMessage(MSG* pMsg)
{
	if(pMsg->message == WM_KEYDOWN){
		if(pMsg->wParam == VK_RETURN){
			return TRUE; 
		}
	}
	return CDialog::PreTranslateMessage(pMsg);
}


BOOL BookInfoInputDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	if(isEditMode){
		SetDlgItemText(IDC_EDIT_BOOKINFO_CODE, mInfo.mCode);
		SetDlgItemText(IDC_EDIT_BOOKINFO_NAME, mInfo.mName);
		SetDlgItemText(IDC_EDIT_BOOKINFO_PUBLISH, mInfo.mPublish);
		SetDlgItemText(IDC_EDIT_BOOKINFO_AUTHOR, mInfo.mAuthor);
		SetDlgItemInt(IDC_EDIT_BOOKINFO_COUNT, mInfo.mKeepCount);	

		SetWindowText(_T("�༭ͼ����Ϣ"));
		SetDlgItemText(IDC_BUTTON_BOOKINFO_ADD, _T("�޸�ͼ����Ϣ"));
	}

	return TRUE; 
}

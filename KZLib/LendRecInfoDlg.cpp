// LendRecInfoDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "KZLib.h"
#include "LendRecInfoDlg.h"
#include "afxdialogex.h"


// LendRecInfoDlg �Ի���

IMPLEMENT_DYNAMIC(LendRecInfoDlg, CDialog)

LendRecInfoDlg::LendRecInfoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(LendRecInfoDlg::IDD, pParent)
{
	isExp = FALSE;
}

LendRecInfoDlg::~LendRecInfoDlg()
{
}

void LendRecInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(LendRecInfoDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_RECINFO_CLOSE, &LendRecInfoDlg::OnBnClickedButtonRecinfoClose)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// LendRecInfoDlg ��Ϣ�������


void LendRecInfoDlg::OnBnClickedButtonRecinfoClose()
{
	CDialog::OnCancel();
}


BOOL LendRecInfoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	SetDlgItemText(IDC_STATIC_LENDER, _T("�����ˣ�") + mLendRec.mLenderName);
	SetDlgItemText(IDC_STATIC_BOOKNAME, _T("ͼ������") + mLendRec.mBookName);
	SetDlgItemText(IDC_STATIC_BOOKAUTHOR, _T("ͼ�����ߣ�") + mLendRec.mBookAuthor);
	SetDlgItemText(IDC_STATIC_LENDDATE, _T("�������ڣ�") + mLendRec.mDate);

	CTime expTime(mLendRec.mDateInt + 30*24*3600);
	CTime now = CTime::GetCurrentTime();
	CString statusString;
	int temp = now.GetTime() - expTime.GetTime();
	if(temp > 0){
		isExp = TRUE;
		statusString = _T(" (�ѹ���)");
	}else{
		statusString = _T(" (δ����)");
		isExp = FALSE;
	}
	SetDlgItemText(IDC_STATIC_LEND_STATUS,_T("�������ڣ�") + expTime.Format(_T("%Y-%m-%d %H:%M")) + statusString);

	return TRUE;  
}


HBRUSH LendRecInfoDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	if(pWnd->GetDlgCtrlID() == IDC_STATIC_LEND_STATUS){
		pDC->SetTextColor(isExp? RGB(255, 0, 0) : RGB(34, 177, 76));
	}
	return hbr;
}

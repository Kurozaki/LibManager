// LendRecInfoDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "KZLib.h"
#include "LendRecInfoDlg.h"
#include "afxdialogex.h"


// LendRecInfoDlg 对话框

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


// LendRecInfoDlg 消息处理程序


void LendRecInfoDlg::OnBnClickedButtonRecinfoClose()
{
	CDialog::OnCancel();
}


BOOL LendRecInfoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	SetDlgItemText(IDC_STATIC_LENDER, _T("借阅人：") + mLendRec.mLenderName);
	SetDlgItemText(IDC_STATIC_BOOKNAME, _T("图书名：") + mLendRec.mBookName);
	SetDlgItemText(IDC_STATIC_BOOKAUTHOR, _T("图书作者：") + mLendRec.mBookAuthor);
	SetDlgItemText(IDC_STATIC_LENDDATE, _T("借阅日期：") + mLendRec.mDate);

	CTime expTime(mLendRec.mDateInt + 30*24*3600);
	CTime now = CTime::GetCurrentTime();
	CString statusString;
	int temp = now.GetTime() - expTime.GetTime();
	if(temp > 0){
		isExp = TRUE;
		int fine = temp / (24 * 3600);
		statusString.Format(_T(" (已过期，罚款 %d.%d 元)"), fine/10, fine%10);
	}else{
		statusString = _T(" (未过期)");
		isExp = FALSE;
	}
	SetDlgItemText(IDC_STATIC_LEND_STATUS,_T("还书日期：") + expTime.Format(_T("%Y-%m-%d %H:%M")) + statusString);

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

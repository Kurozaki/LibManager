// LendMgr.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "KZLib.h"
#include "LendMgr.h"
#include "LendRec.h"
#include "LendRecInputDlg.h"
#include "afxdialogex.h"
#include "LendRecInfoDlg.h"
#include <locale>


// CLendMgr �Ի���

IMPLEMENT_DYNAMIC(CLendMgr, CDialogEx)

CLendMgr::CLendMgr(CWnd* pParent /*=NULL*/)
	: CDialogEx(CLendMgr::IDD, pParent)
{
	saveFilePath = _T("lend.cdb");
}

CLendMgr::~CLendMgr()
{
}

void CLendMgr::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CLendMgr, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_ADDREC, &CLendMgr::OnBnClickedButtonAddrec)
	ON_BN_CLICKED(IDC_BUTTON_DELREC, &CLendMgr::OnBnClickedButtonDelrec)
	ON_NOTIFY(NM_DBLCLK, IDC_LC_LENDINFO, &CLendMgr::OnDblclkLcLendinfo)
END_MESSAGE_MAP()


// CLendMgr ��Ϣ�������


BOOL CLendMgr::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	mLendListCtrl = (CListCtrl *)GetDlgItem(IDC_LC_LENDINFO);
	LONG styles=GetWindowLong(mLendListCtrl->m_hWnd, GWL_STYLE); 
    SetWindowLong(mLendListCtrl->m_hWnd, GWL_STYLE, styles|LVS_REPORT);
	mLendListCtrl->SetExtendedStyle(LVS_EX_FULLROWSELECT);

	CRect rs;
	GetClientRect(&rs);
	int colWidth = rs.Width()/4;

	mLendListCtrl->InsertColumn(0, _T("������"), LVCFMT_LEFT, colWidth, 0);
	mLendListCtrl->InsertColumn(1, _T("����"), LVCFMT_LEFT, colWidth, 1);
	mLendListCtrl->InsertColumn(2, _T("ͼ������"), LVCFMT_LEFT, colWidth, 2);
	mLendListCtrl->InsertColumn(3, _T("��������"), LVCFMT_LEFT, colWidth, 3);

	CStdioFile file;
	char* old_locale = _strdup( setlocale(LC_CTYPE,NULL));

	BOOL openFlag = file.Open(saveFilePath, CFile::modeNoTruncate|CFile::modeRead);
	if(openFlag){
		setlocale(LC_CTYPE, ("chs"));
		BOOL readFlag = TRUE;
		CString buf;

		while(readFlag){
			file.ReadString(buf);
			if(buf.GetLength() == 0){
				readFlag = FALSE;
				break;
			}
			LendRec rec;
			rec.mLenderName = buf;
			file.ReadString(rec.mBookName);
			file.ReadString(rec.mBookAuthor);
			file.ReadString(rec.mDate);
			file.ReadString(buf);
			rec.mDateInt = _ttoi(buf);
			AddLendRec(rec);
		}
		
		setlocale(LC_CTYPE, old_locale); 
		free(old_locale); 
	}

	return TRUE;  
}


void CLendMgr::OnBnClickedButtonAddrec()
{
	LendRecInputDlg inputDlg;
	int result = inputDlg.DoModal();
	if(result == IDOK){
		AddLendRec(inputDlg.recInfo);
	}
}


void CLendMgr::OnBnClickedButtonDelrec()
{
	int selMark = mLendListCtrl->GetSelectionMark();
	if(selMark == -1) {
		MessageBox(_T("����ѡ��Ҫɾ����Ŀ"), _T("��ʾ"), MB_OKCANCEL);
		return;
	}
	int clkMark = MessageBox(_T("ȷ��Ҫɾ����"), _T("��ʾ"));
	if(clkMark == IDOK) {
		CString bookName = mLendListCtrl->GetItemText(selMark, 1);

		POSITION bookP = ((CKZLibApp *)AfxGetApp())->bookList.GetHeadPosition();
		while(bookP){
			BookInfo &info = ((CKZLibApp *)AfxGetApp())->bookList.GetNext(bookP);
			if(info.mName == bookName){
				info.mKeepCount++;
				break;
			}	
		}	

		mLendListCtrl->DeleteItem(selMark);
		POSITION p = mLendRecList.GetHeadPosition();
		for(int i=0; i<selMark; i++){
			mLendRecList.GetNext(p);
		}
		mLendRecList.RemoveAt(p);
	}
}


int CLendMgr::AddLendRec(LendRec recInfo)
{
	int addMark = mLendListCtrl->GetItemCount();
	addMark = mLendListCtrl->InsertItem(addMark, _T(""));
	if(addMark != -1){
		mLendRecList.AddTail(recInfo);
		mLendListCtrl->SetItemText(addMark, 0, recInfo.mLenderName);
		mLendListCtrl->SetItemText(addMark, 1, recInfo.mBookName);
		mLendListCtrl->SetItemText(addMark, 2, recInfo.mBookAuthor);
		mLendListCtrl->SetItemText(addMark, 3, recInfo.mDate);
	}
	return addMark;
}


void CLendMgr::PostNcDestroy()
{
	// TODO: �ڴ����ר�ô����/����û���
	CStdioFile file;
	BOOL openFlag = file.Open(saveFilePath, CFile::modeCreate|CFile::modeWrite);
	if(openFlag){
		POSITION p = mLendRecList.GetHeadPosition();
		while(p){
			LendRec rec = mLendRecList.GetNext(p);
			file.WriteString(rec.mLenderName + "\n");
			file.WriteString(rec.mBookName + "\n");
			file.WriteString(rec.mBookAuthor + "\n");
			file.WriteString(rec.mDate + "\n");
			CString temp;
			temp.Format(_T("%d"), rec.mDateInt);
			file.WriteString(temp + "\n");
		}
		file.Close();
	}
	CDialogEx::PostNcDestroy();
}


void CLendMgr::OnDblclkLcLendinfo(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	
	int selMark = mLendListCtrl->GetSelectionMark();
	if(selMark == -1){
		return;
	}
	POSITION p = mLendRecList.GetHeadPosition();
	for(int i=0; i<selMark; i++){
		mLendRecList.GetNext(p);
	}
	LendRec rec = mLendRecList.GetAt(p);
	LendRecInfoDlg infoDlg;
	infoDlg.mLendRec = rec;
	infoDlg.DoModal();

	*pResult = 0;
}

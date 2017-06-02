// ReaderMgr.cpp : 实现文件
//

#include "stdafx.h"
#include "KZLib.h"
#include "ReaderMgr.h"
#include "ReaderInfo.h"
#include "afxdialogex.h"
#include <locale>

#include "ReaderInfoInputDlg.h"


// CReaderMgr 对话框

IMPLEMENT_DYNAMIC(CReaderMgr, CDialogEx)

CReaderMgr::CReaderMgr(CWnd* pParent /*=NULL*/)
	: CDialogEx(CReaderMgr::IDD, pParent)
{
	saveFilePath = _T("reader.cdb");
}

CReaderMgr::~CReaderMgr()
{
}

void CReaderMgr::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CReaderMgr, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_ADDREADER, &CReaderMgr::OnBnClickedButtonAddreader)
	ON_BN_CLICKED(IDC_BUTTON_DEL_READER, &CReaderMgr::OnBnClickedButtonDelReader)
	ON_NOTIFY(NM_DBLCLK, IDC_LC_READER, &CReaderMgr::OnDblclkLcReader)
END_MESSAGE_MAP()


// CReaderMgr 消息处理程序


void CReaderMgr::OnBnClickedButtonAddreader()
{
	ReaderInfoInputDlg inputDlg;
	int result = inputDlg.DoModal();
	if(result == IDOK){
		ReaderInfo info = ReaderInfo(inputDlg.inputName, inputDlg.inputIDNumber);
		AddReader(info);
	}
}


void CReaderMgr::OnBnClickedButtonDelReader()
{
	// TODO: 在此添加控件通知处理程序代码
	int result = MessageBox(_T("确定要删除吗"), _T("提示"), MB_OKCANCEL);
	if(result == IDOK){
		int selMark = mReaderListCtrl->GetSelectionMark();
		if(selMark == -1){
			MessageBox(_T("请先选中要删除的条目！"), _T("提示"), MB_OK);
			return;
		}
		mReaderListCtrl->DeleteItem(selMark);
		((CKZLibApp *)AfxGetApp())->RemoveReader(selMark);
	}
}

BOOL CReaderMgr::OnInitDialog()
{
	mReaderListCtrl = (CListCtrl *)GetDlgItem(IDC_LC_READER);

	LONG styles=GetWindowLong(mReaderListCtrl->m_hWnd, GWL_STYLE); 
    SetWindowLong(mReaderListCtrl->m_hWnd, GWL_STYLE, styles|LVS_REPORT);
	mReaderListCtrl->SetExtendedStyle(LVS_EX_FULLROWSELECT);

	CRect rs;
	mReaderListCtrl->GetClientRect(&rs);
	UINT colWidth = rs.Width();
	mReaderListCtrl->InsertColumn(0, _T("姓名"), LVCFMT_LEFT, colWidth/2, 1);
	mReaderListCtrl->InsertColumn(1, _T("学号"), LVCFMT_LEFT, colWidth/2, 2);
	
	/*test 
	for(int i=0; i<5;i++){
		ReaderInfo info;
		info.mName.Format(_T("%d"), i);
		info.mIdNumber.Format(_T("%d"), i);
		AddReader(info);
	}	*/
	CStdioFile file;
	char* old_locale = _strdup( setlocale(LC_CTYPE,NULL)); 

	BOOL openFlag = file.Open(saveFilePath, CFile::modeNoTruncate|CFile::modeRead);
	if(openFlag){
		setlocale( LC_CTYPE, ("chs"));

		BOOL readFlag = TRUE;
		CString buf;
		while(readFlag){
			file.ReadString(buf);
			if(buf.GetLength() == 0){
				readFlag = FALSE;
				break;
			}
			ReaderInfo info;
			info.mIdNumber = buf;
			file.ReadString(info.mName);
			AddReader(info);
		}

		setlocale(LC_CTYPE, old_locale); 
		free(old_locale); 
		file.Close();
	}

	return TRUE;
}

int CReaderMgr::AddReader(ReaderInfo info){
	int index = mReaderListCtrl->GetItemCount();
	int addRes = mReaderListCtrl->InsertItem(index, _T(""));
	mReaderListCtrl->SetItemText(addRes, 0, info.mName);
	mReaderListCtrl->SetItemText(addRes, 1, info.mIdNumber);

	((CKZLibApp *)AfxGetApp())->readerList.AddTail(info);

	return addRes;
}


void CReaderMgr::OnDblclkLcReader(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	
	NMLISTVIEW* p = (NMLISTVIEW *)pNMHDR;
	int itemRow = p->iItem;		//get selected row

	CString editName = mReaderListCtrl->GetItemText(itemRow, 0);
	CString editIDN = mReaderListCtrl->GetItemText(itemRow, 1);

	ReaderInfoInputDlg editDlg;
	editDlg.isEditMode = TRUE;
	editDlg.inputName = editName;
	editDlg.inputIDNumber = editIDN;
	int editRes = editDlg.DoModal();

	if(editRes == IDOK){
		mReaderListCtrl->SetItemText(itemRow, 0, editDlg.inputName);
		mReaderListCtrl->SetItemText(itemRow, 1, editDlg.inputIDNumber);

		POSITION p = ((CKZLibApp *)AfxGetApp())->readerList.GetHeadPosition();
		for(int i=0;i <itemRow; i++){
			((CKZLibApp *)AfxGetApp)->readerList.GetNext(p);
		}
		((CKZLibApp *)AfxGetApp)->readerList.SetAt(p, ReaderInfo(editDlg.inputName, editDlg.inputIDNumber));
	}
	
	*pResult = 0;
}


void CReaderMgr::PostNcDestroy()
{
	// TODO: 在此添加专用代码和/或调用基类
	CStdioFile file;
	file.Open(saveFilePath, CFile::modeCreate|CFile::modeWrite);
	setlocale(LC_CTYPE, ("chs"));
	
	POSITION p = ((CKZLibApp *)AfxGetApp())->readerList.GetHeadPosition();
	while(p){
		ReaderInfo info = ((CKZLibApp *)AfxGetApp())->readerList.GetNext(p);
		file.WriteString(info.mIdNumber + "\n");
		file.WriteString(info.mName + "\n");
	}
	file.Close();

	CDialogEx::PostNcDestroy();
}

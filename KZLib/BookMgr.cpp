// BookMgr.cpp : 实现文件
//

#include "stdafx.h"
#include "KZLib.h"
#include "BookMgr.h"
#include "afxdialogex.h"
#include "BookInfoInputDlg.h"
#include <locale>


// CBookMgr 对话框

IMPLEMENT_DYNAMIC(CBookMgr, CDialogEx)

CBookMgr::CBookMgr(CWnd* pParent /*=NULL*/)
	: CDialogEx(CBookMgr::IDD, pParent)
{
	saveFilePath = _T("bookinfo.cdb");
}

CBookMgr::~CBookMgr()
{
}

void CBookMgr::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CBookMgr, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_DEL_BOOK, &CBookMgr::OnBnClickedButtonDelBook)
	ON_BN_CLICKED(IDC_BUTTON_ADDBOOK, &CBookMgr::OnBnClickedButtonAddbook)
	ON_NOTIFY(NM_DBLCLK, IDC_LC_BOOKINFO, &CBookMgr::OnDblclkLcBookinfo)
END_MESSAGE_MAP()


// CBookMgr 消息处理程序


BOOL CBookMgr::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	mBookListCtrl = (CListCtrl *)GetDlgItem(IDC_LC_BOOKINFO);

	LONG styles=GetWindowLong(mBookListCtrl->m_hWnd, GWL_STYLE); 
    SetWindowLong(mBookListCtrl->m_hWnd, GWL_STYLE, styles|LVS_REPORT);
	mBookListCtrl->SetExtendedStyle(LVS_EX_FULLROWSELECT);

	CRect rs;
	GetClientRect(&rs);
	int colWidth = rs.Width()/8;	//get col width

	mBookListCtrl->InsertColumn(0, _T("编号"), LVCFMT_LEFT, colWidth, 0);
	mBookListCtrl->InsertColumn(1, _T("书名"), LVCFMT_CENTER, colWidth*2, 1);
	mBookListCtrl->InsertColumn(2, _T("作者"), LVCFMT_CENTER, colWidth*2, 2);
	mBookListCtrl->InsertColumn(3, _T("出版社"), LVCFMT_CENTER, colWidth*2, 3);
	mBookListCtrl->InsertColumn(4, _T("持有"), LVCFMT_LEFT, colWidth, 4);

	CStdioFile file;	//read info from file

	char* old_locale = _strdup( setlocale(LC_CTYPE,NULL)); 
	BOOL open = file.Open(saveFilePath, CFile::modeRead);
	if(open){
		setlocale( LC_CTYPE, ("chs")); 
		BOOL flag = TRUE;
		CString buf;
		int index = 0;
		while(flag){
			file.ReadString(buf);
			if(buf.GetLength() == 0){
				flag = FALSE;
				break;
			}
			BookInfo info;
			info.mCode = buf;
			file.ReadString(info.mName);
			file.ReadString(info.mAuthor);
			file.ReadString(info.mPublish);
			file.ReadString(buf);
			info.mKeepCount = _ttoi(buf);
			AddBookInfo(info);
		}
		setlocale(LC_CTYPE, old_locale); 
		free(old_locale); 
		file.Close();
	}
	
	return TRUE; 
}


void CBookMgr::OnBnClickedButtonDelBook()
{
	int clkMark = MessageBox(_T("确定要删除吗"), _T("提示"));
	if(clkMark == IDOK) {
		int selMark = mBookListCtrl->GetSelectionMark();
		if(selMark == -1){
			MessageBox(_T("请先选中要删除的条目！"), _T("提示"), MB_OK);
			return;
		}
		mBookListCtrl->DeleteItem(selMark);


		POSITION p = ((CKZLibApp *)AfxGetApp())->bookList.GetHeadPosition();
		for(int i=0; i<selMark; i++){
			((CKZLibApp *)AfxGetApp())->bookList.GetNext(p);
		}
		((CKZLibApp *)AfxGetApp())->bookList.RemoveAt(p);
	}
}


void CBookMgr::OnBnClickedButtonAddbook()
{
	// TODO: 在此添加控件通知处理程序代码
	BookInfoInputDlg inputDlg;
	int addRes = inputDlg.DoModal();
	if(addRes == IDOK){
		AddBookInfo(inputDlg.mInfo);
	}
}


int CBookMgr::AddBookInfo(BookInfo bInfo)
{
	int index = mBookListCtrl->GetItemCount();
	int addRow = mBookListCtrl->InsertItem(index, _T(""));

	mBookListCtrl->SetItemText(addRow, 0, bInfo.mCode);
	mBookListCtrl->SetItemText(addRow, 1, bInfo.mName);
	mBookListCtrl->SetItemText(addRow, 2, bInfo.mAuthor);
	mBookListCtrl->SetItemText(addRow, 3, bInfo.mPublish);
	CString countStr;
	countStr.Format(_T("%d"), bInfo.mKeepCount);
	mBookListCtrl->SetItemText(addRow, 4, countStr);

	((CKZLibApp *)AfxGetApp())->bookList.AddTail(bInfo);

	return addRow;
}


void CBookMgr::OnDblclkLcBookinfo(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	
	NMLISTVIEW* p = (NMLISTVIEW *)pNMHDR;
	int itemRow = p->iItem;		//get selected row
	if(itemRow == -1){
		return;
	}

	BookInfoInputDlg editDlg;
	//set edit info
	editDlg.isEditMode = TRUE;
	editDlg.mInfo.mCode = mBookListCtrl->GetItemText(itemRow, 0);
	editDlg.mInfo.mName = mBookListCtrl->GetItemText(itemRow, 1);
	editDlg.mInfo.mAuthor = mBookListCtrl->GetItemText(itemRow, 2);
	editDlg.mInfo.mPublish = mBookListCtrl->GetItemText(itemRow, 3);
	editDlg.mInfo.mKeepCount = _ttoi( mBookListCtrl->GetItemText(itemRow, 4));

	int editRes = editDlg.DoModal();

	if(editRes == IDOK) {
		mBookListCtrl->SetItemText(itemRow, 0, editDlg.mInfo.mCode);
		mBookListCtrl->SetItemText(itemRow, 1, editDlg.mInfo.mName);
		mBookListCtrl->SetItemText(itemRow, 2, editDlg.mInfo.mAuthor);
		mBookListCtrl->SetItemText(itemRow, 3, editDlg.mInfo.mPublish);
		CString countStr;
		countStr.Format(_T("%d"), editDlg.mInfo.mKeepCount);
		mBookListCtrl->SetItemText(itemRow, 4, countStr);
		

		POSITION p = ((CKZLibApp *)AfxGetApp())->bookList.GetHeadPosition();
		for(int i=0; i<itemRow; i++){
			((CKZLibApp *)AfxGetApp())->bookList.GetNext(p);
		}
		((CKZLibApp *)AfxGetApp())->bookList.SetAt(p, editDlg.mInfo);
	}
	*pResult = 0;
}



void CBookMgr::PostNcDestroy()
{
	//write to file
	CStdioFile file;
	file.Open(saveFilePath, CFile::modeCreate|CFile::modeWrite);
	setlocale(LC_CTYPE, ("chs"));

	POSITION p = ((CKZLibApp *)AfxGetApp())->bookList.GetHeadPosition();
	while(p){
		BookInfo info = ((CKZLibApp *)AfxGetApp())->bookList.GetNext(p);
		file.WriteString(info.mCode + "\n");
		file.WriteString(info.mName + "\n");
		file.WriteString(info.mAuthor + "\n");
		file.WriteString(info.mPublish + "\n");
		CString keepCount;
		keepCount.Format(_T("%d\n"), info.mKeepCount);
		file.WriteString(keepCount);
	}	
	file.Close();

	CDialogEx::PostNcDestroy();
}


void CBookMgr::RefreshBookInfo(void)
{
	POSITION p = ((CKZLibApp *)AfxGetApp())->bookList.GetHeadPosition();
	mBookListCtrl->DeleteAllItems();
	while(p){
		BookInfo &bInfo = ((CKZLibApp *)AfxGetApp())->bookList.GetNext(p);
		int index = mBookListCtrl->GetItemCount();
		int addRow = mBookListCtrl->InsertItem(index, _T(""));

		mBookListCtrl->SetItemText(addRow, 0, bInfo.mCode);
		mBookListCtrl->SetItemText(addRow, 1, bInfo.mName);
		mBookListCtrl->SetItemText(addRow, 2, bInfo.mAuthor);
		mBookListCtrl->SetItemText(addRow, 3, bInfo.mPublish);
		CString countStr;
		countStr.Format(_T("%d"), bInfo.mKeepCount);
		mBookListCtrl->SetItemText(addRow, 4, countStr);
	}
}

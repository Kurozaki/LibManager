
// KZLibDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "KZLib.h"
#include "KZLibDlg.h"
#include "afxdialogex.h"

#include "BookMgr.h"
#include "ReaderMgr.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CKZLibDlg 对话框




CKZLibDlg::CKZLibDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CKZLibDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CKZLibDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CKZLibDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(TCN_SELCHANGE, IDC_MAIN_TAB, &CKZLibDlg::OnSelchangeMainTab)
END_MESSAGE_MAP()


// CKZLibDlg 消息处理程序

BOOL CKZLibDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	mMainTabCtrl = (CTabCtrl *)GetDlgItem(IDC_MAIN_TAB);

	mMainTabCtrl->InsertItem(0, _T("图书管理"));
	mMainTabCtrl->InsertItem(1, _T("读者管理"));
	mMainTabCtrl->InsertItem(2, _T("借阅管理"));

	CRect rs;
	mMainTabCtrl->GetClientRect(&rs);
	rs.top += 34;
	rs.bottom += 10;
	rs.left += 13;
	rs.right += 9;

	mBookMgr.Create(IDD_BOOKMGR, GetDlgItem(IDD_KZLIB_DIALOG));
	mReaderMgr.Create(IDD_READERMGR, GetDlgItem(IDD_KZLIB_DIALOG));
	mLendInfoMgr.Create(IDD_LENDMGR, GetDlgItem(IDD_KZLIB_DIALOG));

	mBookMgr.MoveWindow(&rs);
	mReaderMgr.MoveWindow(&rs);
	mLendInfoMgr.MoveWindow(&rs);

	mBookMgr.ShowWindow(true);
	mReaderMgr.ShowWindow(false);
	mLendInfoMgr.ShowWindow(false);

	mMainTabCtrl->SetCurSel(0);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CKZLibDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CKZLibDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CKZLibDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CKZLibDlg::OnSelchangeMainTab(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	int sel = mMainTabCtrl->GetCurSel();
	switch(sel)
	{
		case 0:
			mBookMgr.ShowWindow(true);
			mBookMgr.RefreshBookInfo();

			mReaderMgr.ShowWindow(false);
			mLendInfoMgr.ShowWindow(false);
			break;

		case 1:
			mBookMgr.ShowWindow(false);
			mReaderMgr.ShowWindow(true);
			mLendInfoMgr.ShowWindow(false);
			break;
		
		case 2:
			mBookMgr.ShowWindow(false);
			mReaderMgr.ShowWindow(false);
			mLendInfoMgr.ShowWindow(true);
			break;
	}
	*pResult = 0;
}

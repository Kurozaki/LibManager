
// KZLibDlg.cpp : ʵ���ļ�
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


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CKZLibDlg �Ի���




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


// CKZLibDlg ��Ϣ�������

BOOL CKZLibDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	mMainTabCtrl = (CTabCtrl *)GetDlgItem(IDC_MAIN_TAB);

	mMainTabCtrl->InsertItem(0, _T("ͼ�����"));
	mMainTabCtrl->InsertItem(1, _T("���߹���"));
	mMainTabCtrl->InsertItem(2, _T("���Ĺ���"));

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

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CKZLibDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CKZLibDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CKZLibDlg::OnSelchangeMainTab(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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

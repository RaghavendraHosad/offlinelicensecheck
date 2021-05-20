
// OfflineLicenseMgmntToolDlg.cpp : implementation file
//

#include "Header.h"
#include "pch.h"
#include "framework.h"
#include "OfflineLicenseMgmntTool.h"
#include "OfflineLicenseMgmntToolDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
	
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CAboutDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// COfflineLicenseMgmntToolDlg dialog



COfflineLicenseMgmntToolDlg::COfflineLicenseMgmntToolDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_OFFLINELICENSEMGMNTTOOL_DIALOG, pParent)
	, m_LicenseFileName(_T(""))
	, m_ExpiryDate(_T(""))
	, m_Message(_T(""))
	, m_HashTypeName(_T(""))
	, m_EncryptionType(_T(""))
	, m_EncryptedFileName(_T(""))
	, m_DateSelected(COleDateTime::GetCurrentTime())
	, m_Result(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void COfflineLicenseMgmntToolDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_LICENSE_FILE, m_LicenseFileName);
	//DDX_Text(pDX, IDC_EDIT_EXP_DT, m_ExpiryDate);
	DDX_Text(pDX, IDC_EDIT_MSG, m_Message);
	DDX_CBString(pDX, IDC_COMBO_HASH, m_HashTypeName);
	DDX_CBString(pDX, IDC_COMBO_ENCRYPTION_TYPE, m_EncryptionType);
	DDX_Text(pDX, IDC_EDIT_ENC_FILE_NAME, m_EncryptedFileName);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, m_DateSelected);
	DDX_Control(pDX, IDC_COMBO_HASH, m_CtrlHashType);
	DDX_Control(pDX, IDC_COMBO_ENCRYPTION_TYPE, m_CtrlEncType);
	DDX_Control(pDX, IDC_EDIT_LICENSE_FILE, m_CtrlLicenseFileName);
	DDX_Control(pDX, IDC_EDIT_MSG, m_CtrlMessage);
	DDX_Control(pDX, IDC_EDIT_ENC_FILE_NAME, m_EncFileName);
	DDX_Control(pDX, IDC_STATIC_GROUP1, m_CtrlGroup1);
	DDX_Control(pDX, IDC_STATIC_GROUP2, m_CtrlGroup2);
	DDX_Text(pDX, IDC_EDIT_RESULT, m_Result);
	DDX_Control(pDX, IDC_EDIT_RESULT, m_CtrlResult);
}

BEGIN_MESSAGE_MAP(COfflineLicenseMgmntToolDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_OK, &COfflineLicenseMgmntToolDlg::OnBtnClickedOk)
	ON_BN_CLICKED(IDCLOSE, &COfflineLicenseMgmntToolDlg::OnBnClickedClose)
END_MESSAGE_MAP()


// COfflineLicenseMgmntToolDlg message handlers

BOOL COfflineLicenseMgmntToolDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	m_CtrlHashType.AddString(L"Hash type 1");
	m_CtrlHashType.AddString(L"Hash type 2");
	m_CtrlHashType.AddString(L"Hash type 3");
	m_CtrlHashType.SetCurSel(0);

	m_CtrlEncType.AddString(L"AES");
	m_CtrlEncType.AddString(L"DES");	

	m_CtrlEncType.SetCurSel(1);

	m_CtrlLicenseFileName.SetWindowTextW(L"license.txt");
	m_CtrlMessage.SetWindowTextW(L"Your license period is expired! Please renew license.");

	m_EncFileName.SetWindowTextW(L"one_year_license.enc");
	m_CtrlResult.EnableWindow(0);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void COfflineLicenseMgmntToolDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void COfflineLicenseMgmntToolDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR COfflineLicenseMgmntToolDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


/// <summary>
/// This function called when OK button Clicked
/// Responsible to create license.txt file and <>.enc file
/// with all necessory info
/// </summary>
void COfflineLicenseMgmntToolDlg::OnBtnClickedOk()
{
	// TODO: Add your control notification handler code here
	CString strLicenseFileName;
	CString strMessage;
	CString strSelectHasgType;
	CString strSelectEncyptionType;

	Hash *pobjHash = new Hash();	

	UpdateData();

	strLicenseFileName = m_LicenseFileName;
	UDATE uDt;
	m_DateSelected.GetAsUDATE(uDt);
	strMessage = m_Message;
	strSelectHasgType = m_HashTypeName;
	char tmpDt[11] = { 0 };

	WORD wDay = uDt.st.wDay;
	WORD wMonth = uDt.st.wMonth;
	WORD wYear = uDt.st.wYear;

	char tmpsD[3];
	char tmpsM[3];
	char tmpsY[5];

	_itoa_s(wDay, tmpsD, 10);
	_itoa_s(wMonth, tmpsM, 10);
	_itoa_s(wYear, tmpsY, 10);

	sprintf_s(tmpDt, "%s-%s-%s", tmpsY, tmpsM, tmpsD );
	pobjHash->HashFunction1(tmpDt);
	CString result = pobjHash->GetHashString();

	strSelectEncyptionType = m_EncryptedFileName;
	CT2A asci1(strLicenseFileName);
	CT2A asci2(strSelectEncyptionType);
	CT2A asci3(m_Message);
	CT2A asci4(m_HashTypeName);
	LicenseMgmnt obj((char*)asci1.m_psz, (char*)asci2.m_psz, (char*)asci3.m_psz, (char*)asci4.m_psz);
	CT2A asci5(result);
	obj.CreateLicenseFile((char*)asci5);
	/// <summary>
	/// 
	/// </summary>
	obj.EncryptLicenseFile();

	//check latest .enc file generated if true. success
	m_CtrlResult.EnableWindow(1);
	m_Result = "Success";

	//CDC* pDC = m_CtrlResult.GetDC();
	//pDC->SetBkColor(RGB(255, 0, 255));

	UpdateData(FALSE);

	
}


void CAboutDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	//CDialogEx::OnOK();
	AfxMessageBox(L"V1.0 Year 2021\nFree Copy Rights\n Author prasadhosd@gmail.com");
}


void COfflineLicenseMgmntToolDlg::OnBnClickedClose()
{
	// TODO: Add your control notification handler code here
	PostQuitMessage(0);
}

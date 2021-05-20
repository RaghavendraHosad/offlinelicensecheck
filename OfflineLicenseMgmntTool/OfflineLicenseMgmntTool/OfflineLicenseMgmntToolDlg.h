//Author prasadhosad@gmail.com, date: 18-05-2021
// OfflineLicenseMgmntToolDlg.h : header file
//

#pragma once


// COfflineLicenseMgmntToolDlg dialog
class COfflineLicenseMgmntToolDlg : public CDialogEx
{
// Construction
public:
	COfflineLicenseMgmntToolDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_OFFLINELICENSEMGMNTTOOL_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
private:
	// This is the license file name
	CString m_LicenseFileName;
	// Enter Expiry Date
	CString m_ExpiryDate;
	// On validity expiry show this message
	CString m_Message;
	// Select one hash algorithm among many listed.
	CString m_HashTypeName;
	// Select encryption type listed.
	CString m_EncryptionType;
	// Enter encrypted file name.
	CString m_EncryptedFileName;
public:
	afx_msg void OnBtnClickedOk();
private:
	// Selected Date
	COleDateTime m_DateSelected;
public:
	afx_msg void OnBnClickedClose();
private:
	// Control var for Hash Type Name
	CComboBox m_CtrlHashType;
	// Control Encryption Type
	CComboBox m_CtrlEncType;
	// Ctrl License File Name
	CEdit m_CtrlLicenseFileName;
	// Ctrl Message Edit
	CEdit m_CtrlMessage;
	// Ctrl Edit - Encrypted file name
	CEdit m_EncFileName;
	CStatic m_CtrlGroup1;
	CStatic m_CtrlGroup2;
	// Final Result Display
	CString m_Result;
	// Ctrl Result Edit
	CEdit m_CtrlResult;
};

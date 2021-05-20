//Author prasadhosad@gmail.com, date: 18-05-2021
// OfflineLicenseMgmntTool.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// COfflineLicenseMgmntToolApp:
// See OfflineLicenseMgmntTool.cpp for the implementation of this class
//

class COfflineLicenseMgmntToolApp : public CWinApp
{
public:
	COfflineLicenseMgmntToolApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern COfflineLicenseMgmntToolApp theApp;

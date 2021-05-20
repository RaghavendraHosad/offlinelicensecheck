// OfflineLicenseValidityChecker.cpp : Implementation of COfflineLicenseValidityChecker
//Author prasadhosad@gmail.com, date: 18-05-2021

#include "pch.h"
#include <direct.h>
#include <string>
#include <time.h>
#include <ShlObj.h>
#include "OfflineLicenseValidityChecker.h"

// COfflineLicenseValidityChecker
///
/// Hash a char array or undo (choice 0/1)
/// 
STDMETHODIMP GetStringHash(char* strForHash, char* resHash, int choice)
{
	char* tmp = _strdup(strForHash);
	int len = strlen(strForHash);
	if (choice == 0)
	{
		if (tmp != NULL)
		{
			for (int i = 0; i < len; i++) {
				tmp[i] = strForHash[i] + (len - i);
			}

			tmp[len / 2] += 31;
		}
	}
	else if (choice == 1)
	{
		if (tmp != NULL)
		{
			for (int i = 0; i < len; i++) {
				tmp[i] = strForHash[i] - (len - i);
			}

			tmp[len / 2] -= 31;
		}
	}

	for (int i = 0; i < len; i++) {
		resHash[i] = tmp[i];
	}
	
	return S_OK;
}

/// <summary>
/// 
/// This function is the main to be called to confirm validty from other apps
/// </summary>
/// <returns></returns>
STDMETHODIMP COfflineLicenseValidityChecker::CheckSWValidity()
{
	// TODO: Add your implementation code here

	//get current dir path
	char curdir[_MAX_PATH];
	if (_getcwd(curdir, _MAX_PATH) == NULL)
	{
		//MessageBox(0, L"failure to get current directory.", L"Offline Validity ChecK", 0);
		return E_FAIL;
	}

	char licenseFilePath[_MAX_PATH];
	sprintf_s(licenseFilePath, "%s%s", curdir, "\\one_year_license.enc");

	if (INVALID_FILE_ATTRIBUTES == GetFileAttributes((LPCWSTR)licenseFilePath) && GetLastError() == ERROR_FILE_NOT_FOUND)
	{
		MessageBox(0, L"failure to find the .enc file.", L"Offline Validity ChecK", 0);
		return E_FAIL;
	}

	const UINT max_sz = 1024;
	std::string decryptionkey =																								"c0mPl3xKEy!23";  //confidential password

	//App folder path
	//std::string appdata = getenv("APPDATA");
	std::string appdata;
	char* pappdata;
	size_t len;
	_dupenv_s(&pappdata, &len, "APPDATA");
	
	appdata.assign(pappdata, strlen(pappdata));
	int i = appdata.find("Roaming");
	appdata.replace(i, 7, "Local");
	std::string tempDir = appdata;
	tempDir.append("\\OffValidityCheck");
	//create a folder OffValidityCheck
	std::wstring crdir = std::wstring(tempDir.begin(), tempDir.end());
	LPCWSTR dirApp = crdir.c_str();
	DWORD cwCheck = GetFileAttributesA(tempDir.c_str());
	if(cwCheck != FILE_ATTRIBUTE_DIRECTORY)
	{
		if (CreateDirectory(dirApp, NULL) == false)
		{
			MessageBox(0, L"unable to create dir", L"Offline Validity ChecK", 0);
			return E_FAIL;
		}
	}	

	std::string loc = "\\OffValidityCheck\\license.txt";
	appdata.append(loc);

	const char* appdatpathforlicense = appdata.c_str();

	//Don't want to open license.txt by others during this task
	HANDLE file_lock_mtx = CreateMutex(NULL, false, NULL);
	WaitForSingleObject(file_lock_mtx, INFINITE);

	//.enc from current directory to encrypted txt file to AppData\OffValidityCheck folder

	//decrypt secured encrypted license.txt
	char cmd[1024];
	memset(cmd, 0, 1024);
	sprintf_s(cmd, 1024, "support\\openssl enc -d -aes-256-cbc -in %s%s%s -out %s%s%s -pass pass:%s", "\"", licenseFilePath, "\"", "\"", appdatpathforlicense, "\"", decryptionkey.c_str() );

	//std::string sTemps(cmd);
	//std::wstring stemp = std::wstring(sTemps.begin(), sTemps.end());
	//LPCWSTR sw = stemp.c_str();
	//MessageBox(0, sw, L"Offline Validity ChecK", 0);

	size_t siz = strlen(cmd) + 1;
	wchar_t* wcStr_cmd = new wchar_t[siz];
	size_t sz_out;
	mbstowcs_s(&sz_out, wcStr_cmd, siz, cmd, siz - 1);

	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));

	// Start the child process.
	if (!CreateProcess(
		0, wcStr_cmd, NULL, NULL, TRUE, NORMAL_PRIORITY_CLASS | CREATE_NO_WINDOW, NULL, NULL, &si, &pi))
		MessageBox(0, L"ERROR: %s : CreateProcess faild!.", L"Offline Validity ChecK", 0);
	//else
	//	MessageBox(0, L"nWell, CreateProcess() looks OK.\n\n", L"Offline Validity ChecK", 0);

	// Wait until child process exits (in milliseconds). If INFINITE, the functions time-out interval never elapses except with user or other intervention.
	WaitForSingleObject(pi.hProcess, INFINITE);

	// Close process and thread handles.
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);

	//Read content to a buffer
	char* path;
	char line[80] = { 0 };
	unsigned int line_count = 0;
		
	FILE* file;
	fopen_s(&file, appdatpathforlicense, "r");

	if (!file)
	{
		MessageBox(0, L"license.txt - unable to open.", L"Offline Validity ChecK", 1);
		return E_FAIL;
	}
	//else
	//	MessageBox(0, L"license.txt - open is fine.", L"Offline Validity ChecK", 1);

	/* Get each line until there are none left */
	char to_find[1024] = "ExpiryDate";
	char last_run_datetime[1024] = "LastRunDateTime";

	char to_new[2048];
	memset(to_new, 0, sizeof(to_new));
	char line_buf[128];
	memset(line_buf, 0, sizeof(line_buf));
	int count = 0;
	while (fgets(line, sizeof(line), file))
	{
		if (strstr(line, "ExpiryDate")) {
			strcpy_s(to_find, line);
			strncpy_s(line_buf, &line[11], sizeof(line_buf) - 1);
		}

		if (strstr(line, "LastRunDateTime"))
			strcpy_s(last_run_datetime, line);

		if (strstr(line, "Message:")) {
			memset(line_buf, 0, sizeof(line_buf));
			strncpy_s(line_buf, &line[8], sizeof(line_buf) - 1);
			printf("%s", line_buf);
		}

		strcat_s(to_new, line);
	}

	if (fclose(file))
	{
		return E_FAIL;
		perror(path);
	}

	//ExpieryDate line read
	char delm[2] = ":";
	char* token;
	char* next_token_line1 = NULL;
	token = strtok_s(to_find, delm, &next_token_line1);

	char resHash[11];
	memset(resHash, 0, sizeof(resHash));
	char strForHash[11];
	memset(strForHash, 0, sizeof(strForHash));

	strncpy_s(strForHash, next_token_line1, 10);
	GetStringHash(strForHash, resHash, 1);                             
	strcpy_s(next_token_line1, sizeof(resHash), resHash);       

	char cYearExp[5] = { '\0' };
	char cMonthExp[3] = { '\0' };
	char cDayExp[3] = { '\0' };

	strncpy_s(cYearExp, &next_token_line1[0], 4);
	int nyE = atoi(cYearExp);
	strncpy_s(cMonthExp, &next_token_line1[5], 2);
	int nmE = atoi(cMonthExp);
	strncpy_s(cDayExp, &next_token_line1[8], 2);
	int ndE = atoi(cDayExp);

	//char buffer1[256];
	//sprintf_s(buffer1, "Exp %d-%d-%d", nyE, nmE, ndE);	
	//std::string sTemps1(next_token_line1);
	//std::wstring stemp1 = std::wstring(sTemps1.begin(), sTemps1.end());
	//LPCWSTR sw1 = stemp1.c_str();
	//MessageBox(0, sw1, L"Offline Validity ChecK", 0);

	//LastRunDateTime line read
	char* next_token_line2 = NULL;
	token = strtok_s(last_run_datetime, delm, &next_token_line2);

	strncpy_s(strForHash, next_token_line2, 10);
	//reverse hash value
	GetStringHash(strForHash, resHash, 1);    
	strcpy_s(next_token_line2, sizeof(resHash), resHash);      

	char cYearLstrun[5] = { '\0' };
	char cMonthLstrun[3] = { '\0' };
	char cDayLstrun[3] = { '\0' };

	strncpy_s(cYearLstrun, &next_token_line2[0], 4);
	int nlY = atoi(cYearLstrun);
	strncpy_s(cMonthLstrun, &next_token_line2[5], 2);
	int nlM = atoi(cMonthLstrun);
	strncpy_s(cDayLstrun, &next_token_line2[8], 2);
	int nlD = atoi(cDayLstrun);

	//Ex: 2021-04-06 15:38:37
	char delm_spc[2] = " ";
	char* next_token_line2_tmp = NULL;
	token = strtok_s(next_token_line2, delm_spc, &next_token_line2_tmp);

	char tpm[9] = { '\0' };
	strncpy_s(tpm, next_token_line2 + 11, 8);

	GetStringHash(tpm, resHash, 1);      
	strcpy_s(next_token_line2_tmp, sizeof(resHash), resHash);

	//to int 01.01.01
	char cHur[3] = { '\0' };
	char cMin[3] = { '\0' };
	char cSec[3] = { '\0' };

	strncpy_s(cHur, &next_token_line2_tmp[0], 2);
	int nH = atoi(cHur);
	strncpy_s(cMin, &next_token_line2_tmp[3], 2);
	int nMin = atoi(cMin);
	strncpy_s(cSec, &next_token_line2_tmp[6], 2);
	int nSec = atoi(cSec);

	//Compare lastrundatetime vs curr time
	time_t now;
	struct tm lastrundttm;
	double sec;
	time(&now);
	localtime_s(&lastrundttm, &now);

	lastrundttm.tm_year = nlY -1900; //as tm_year is from 1900
	lastrundttm.tm_mon = nlM;
	lastrundttm.tm_mday = nlD;

	lastrundttm.tm_hour = nH;
	lastrundttm.tm_min = nMin;
	lastrundttm.tm_sec = nSec;

	SYSTEMTIME LocalTime;
	GetLocalTime(&LocalTime);

	struct tm currsystm;
	time(&now);
	localtime_s(&currsystm, &now);
	currsystm.tm_year = LocalTime.wYear -1900; //as tm_year is from 1900
	currsystm.tm_mon = LocalTime.wMonth;
	currsystm.tm_mday = LocalTime.wDay;

	currsystm.tm_hour = LocalTime.wHour;
	currsystm.tm_min = LocalTime.wMinute;
	currsystm.tm_sec = LocalTime.wSecond;

	//Compare current system dt, time Vs Last run dt, time
	//current time is always greater than the stored time
	//sec = difftime(mktime(&currsystm), mktime(&lastrundttm));
	time_t start_Tm, end_tm;
	start_Tm = mktime(&lastrundttm);
	end_tm = mktime(&currsystm);
	sec = difftime(end_tm, start_Tm);

	char tempValChk[256];
	sprintf_s(tempValChk, "%s%s", "ERROR: License security key expired!\nExpiry date is:", next_token_line1);
	std::string tStrChk(tempValChk);
	std::wstring stemp1 = std::wstring(tStrChk.begin(), tStrChk.end());
	LPCWSTR swchkVal = stemp1.c_str();

	if (sec <= 0)
	{
		MessageBox(0, swchkVal, L"Offline Validity Check", 0);
		ReleaseMutex(file_lock_mtx);
		return E_FAIL;
	}

	//Check Expiery date
	struct tm expDtTim;
	double sec_tmp;
	time(&now);
	localtime_s(&expDtTim, &now);
	expDtTim.tm_year = nyE -1900;
	expDtTim.tm_mon = nmE;
	expDtTim.tm_mday = ndE;

	sec_tmp = difftime(mktime(&expDtTim), mktime(&currsystm));
	sprintf_s(tempValChk, "%d %d\n%s%s", expDtTim.tm_year, currsystm.tm_year, "ERROR: License security key expired!\nExpiry date is:", next_token_line1);
	std::string tStrChk1(tempValChk);
	std::wstring stemp2 = std::wstring(tStrChk1.begin(), tStrChk1.end());
	swchkVal = stemp2.c_str();
	
	if (sec_tmp <= 0)
	{
		MessageBox(0, swchkVal, L"Offline Validity Check", 0);
		ReleaseMutex(file_lock_mtx);
		return E_FAIL;
	}

	//check if expiry year is just a difference of 1 year than its current system year
	double diffYear = expDtTim.tm_year - currsystm.tm_year;
	if (diffYear > 1)
	{
		MessageBox(0, L"ERROR: License security key expired!", L"Offline Validity ChecK", 0);
		return E_FAIL;
	}

	//update current date into lincense file and encrypt 
	char tmp[37];
	memset(tmp, 0, sizeof(tmp));

	char buffer[20];
	memset(buffer, 0, sizeof(buffer));
	struct tm timeinfo;
	time_t rawtime = time(0);
	localtime_s(&timeinfo, &rawtime);
	strftime(buffer, 19, "%F %T", &timeinfo);
	buffer[19] = '\0';
	char tmpF[11];  //yyyy-mm-dd
	memset(tmpF, 0, sizeof(tmpF));
	char tmpS[9];   //hh:mm:ss
	memset(tmpS, 0, sizeof(tmpS));
	char resStgF[11]; //yyyy-mm-dd  hashed ver
	memset(resStgF, 0, sizeof(resStgF));
	char resStgS[9];  //hh-mm-ss  hashed ver
	memset(resStgS, 0, sizeof(resStgS));
	sprintf_s(tmpF, "%4d-%02d-%02d", LocalTime.wYear, LocalTime.wMonth, LocalTime.wDay);
	GetStringHash(tmpF, resStgF, 0);
	sprintf_s(tmpS, "%02d:%02d:%02d", LocalTime.wHour, LocalTime.wMinute, LocalTime.wSecond);
	GetStringHash(tmpS, resStgS, 0);

	//update license.txt with hased ver of LastRunDateTime
	sprintf_s(tmp, "LastRunDateTime:%s %s\n", resStgF, resStgS);

	std::string st(to_new);
	int n = st.find("LastRunDateTime:");
	st.replace(n, sizeof(tmp) - 1, tmp);

	FILE* fp_write;
	fopen_s(&fp_write, appdatpathforlicense, "w");
	fprintf(fp_write, "%s", st.c_str());
	fclose(fp_write);

	//create latest .enc file
	char cmd_new[1024];
	memset(cmd_new, 0, sizeof(cmd_new));
	sprintf_s(cmd_new, sizeof(cmd_new), "support\\openssl enc -aes-256-cbc -salt -in %s -out %s -pass pass:%s", appdatpathforlicense, "one_year_license.enc", decryptionkey.c_str());

	size_t sz = strlen(cmd_new) + 1;
	wchar_t* cmd_wcStr = new wchar_t[sz];
	size_t out_sz;
	mbstowcs_s(&out_sz, cmd_wcStr, sz, cmd_new, sz - 1);

	STARTUPINFO si_new;
	PROCESS_INFORMATION pi_new;
	ZeroMemory(&si_new, sizeof(si_new));
	si_new.cb = sizeof(si_new);
	ZeroMemory(&pi_new, sizeof(pi_new));

	//0,cmd,0,0,TRUE, NORMAL_PRIORITY_CLASS|CREATE_NO_WINDOW,0,0,&sInfo,&pInfo
	// Start the child process.
	if (!CreateProcess(
		0, cmd_wcStr, NULL, NULL, TRUE, NORMAL_PRIORITY_CLASS | CREATE_NO_WINDOW, NULL, NULL, &si_new, &pi_new))
		MessageBox(0, L"ERROR: CreateProcess faild!", L"Offline Validity Check", 0);
	//else
	//	essageBox(0, L"CreateProcess is success!", L"Offline Validity ChecK", 0);

	// Wait until child process exits (in milliseconds). If INFINITE, the functions time-out interval never elapses except with user or other intervention.
	WaitForSingleObject(pi_new.hProcess, INFINITE);

	// Close process and thread handles.
	CloseHandle(pi_new.hProcess);
	CloseHandle(pi_new.hThread);

	ReleaseMutex(file_lock_mtx);
	//delete license file
	remove(appdatpathforlicense);

    return S_OK;
}

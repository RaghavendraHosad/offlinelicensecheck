#include "pch.h"
#include "Header.h"
#include <fstream>
Hash::Hash()
{
}

Hash::~Hash()
{
	m_strDateHash = L"";
}

void Hash::HashFunction1(char* cStr)
{
	char* cTmp = _strdup(cStr);
	int len = strlen(cStr);

	if (cTmp != NULL)
	{
		for (int i = 0; i < len; i++) {
			cTmp[i] = cStr[i] + (len - i);
		}

		cTmp[len / 2] += 31;
	}

	m_strDateHash = CString(cTmp);
}

void Hash::HashFunction2(char* cStr)
{
	char* cTmp = _strdup(cStr);
	int len = strlen(cStr);

	for (int i = 0; i < len; i++) {
		cTmp[i] = cStr[i] + (len - i);
	}

	m_strDateHash = CString(cTmp);
}

void Hash::HashFunction3(char* cStr)
{
	char* cTmp = _strdup(cStr);
	int len = strlen(cStr);

	for (int i = 0; i < len; i++) {
		cTmp[i] = cStr[i] + (len - i);
	}

	m_strDateHash = CString(cTmp);

}

CString Hash::GetHashString()
{
	return m_strDateHash;
}

///////////////////////////////////////////////////////////

LicenseMgmnt::LicenseMgmnt()
{
}

LicenseMgmnt::~LicenseMgmnt()
{

}

LicenseMgmnt::LicenseMgmnt(char* license_file_path, char* encrypted_file_path, char* message, char* hashtype)
{
	//get current dir path
	TCHAR curdir[_MAX_PATH];
	GetCurrentDirectory(_MAX_PATH, curdir);
	char ccurdir[_MAX_PATH];
	size_t charsconverted = 0;

	char temp_path_1[_MAX_PATH];
	char temp_path_2[_MAX_PATH];

	wcstombs_s(&charsconverted, ccurdir, _MAX_PATH, curdir, _MAX_PATH);
	sprintf_s(temp_path_1, "%s\\%s", ccurdir, license_file_path);
	m_LicenseFilePath = license_file_path;
	sprintf_s(temp_path_2, "%s\\%s", ccurdir, encrypted_file_path);
	m_EncryptedFilePath = encrypted_file_path;

	m_Message = message;
	m_HashFuncType = hashtype;

	m_currentDirectory = ccurdir;
}

bool LicenseMgmnt::CreateLicenseFile(char* strhash)
{
	//m_LicenseFilePath 
	SYSTEMTIME LocalTime;
	GetLocalTime(&LocalTime);

	time_t now;
	time(&now);
	struct tm lastrundttm;
	localtime_s(&lastrundttm, &now);

	char tempSysTime[21];

	char strYear[11];
	char strHour[9];
	
	sprintf_s(strYear, "%.4ld-%.2ld-%.2ld", lastrundttm.tm_year + 1900, lastrundttm.tm_mon, lastrundttm.tm_mday);
	sprintf_s(strHour, "%.2ld-%.2ld-%.2ld", lastrundttm.tm_hour, lastrundttm.tm_min, lastrundttm.tm_sec);

	Hash* phObj = new Hash();
	phObj->HashFunction1(strYear);
	CString strY = phObj->GetHashString();
	CT2A asci6(strY);
	phObj->HashFunction1(strHour);
	CString strH = phObj->GetHashString();
	CT2A asci7(strH);

	delete phObj;

	sprintf_s(tempSysTime, "%s %s", (char*)asci6, (char*)asci7);
	std::ofstream file(m_LicenseFilePath);
	file << "ExpiryDate:" << strhash << "\n" << "LastRunDateTime:" << tempSysTime << "\n" << "Message:" << m_Message << "\n" << m_HashFuncType;
	file.close();
	return true;
}

bool LicenseMgmnt::EncryptLicenseFile()
{
	if (m_LicenseFilePath != "")
	{
		//create latest .enc file
		char cmd_new[1024];
		memset(cmd_new, 0, sizeof(cmd_new));
		sprintf_s(cmd_new, sizeof(cmd_new), "support\\openssl enc -aes-256-cbc -salt -in %s -out %s -pass pass:%s", m_LicenseFilePath, m_EncryptedFilePath, "c0mPl3xKEy!23");  

		STARTUPINFO si_new;
		PROCESS_INFORMATION pi_new;
		ZeroMemory(&si_new, sizeof(si_new));
		si_new.cb = sizeof(si_new);
		ZeroMemory(&pi_new, sizeof(pi_new));

		wchar_t wtext[1024];

		size_t ln = 0;
		mbstowcs_s(&ln, wtext, strlen(cmd_new) + 1, cmd_new, strlen(cmd_new) + 1);

		//0,cmd,0,0,TRUE, NORMAL_PRIORITY_CLASS|CREATE_NO_WINDOW,0,0,&sInfo,&pInfo
		// Start the child process.
		if (!CreateProcess(
			0, wtext, NULL, NULL, TRUE, NORMAL_PRIORITY_CLASS | CREATE_NO_WINDOW, NULL, NULL, &si_new, &pi_new))
		{
			//MessageBox(0, L"Error", L"Test", 0);
		}
		//else
			//MessageBox(0, L"OK", L"Test", 0);

		// Wait until child process exits (in milliseconds). If INFINITE, the functions time-out interval never elapses except with user or other intervention.
		WaitForSingleObject(pi_new.hProcess, INFINITE);

		// Close process and thread handles.
		CloseHandle(pi_new.hProcess);
		CloseHandle(pi_new.hThread);
	}
	return true;
}
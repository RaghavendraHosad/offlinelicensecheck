#pragma once
#include <afx.h>

class LicenseMgmnt {

public:
	LicenseMgmnt();
	LicenseMgmnt(char* license_file, char* encrypted_file, char* msg, char* htype);
	~LicenseMgmnt();

	bool CreateLicenseFile(char* strhash);
	bool EncryptLicenseFile();

private:
	char *m_CurrentFolderPath;
	char* m_LicenseFilePath;
	char *m_EncryptedFilePath;

	char* m_Message;
	char* m_HashFuncType;

	char* m_currentDirectory;
};

class Hash {

public:
	Hash();
	~Hash();

	void HashFunction1(char*);
	void  HashFunction2(char*);
	void  HashFunction3(char*);

	CString GetHashString();

private:
	CString m_strDateHash;
};


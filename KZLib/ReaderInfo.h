#pragma once
class ReaderInfo
{
public:
	ReaderInfo(void);
	ReaderInfo(CString name, CString idn);
	~ReaderInfo(void);

	UINT mReaderID;
	CString mName;
	CString mIdNumber;
};


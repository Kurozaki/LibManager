#pragma once
class BookInfo
{
public:
	BookInfo(void);
	~BookInfo(void);

	CString mCode;
	CString mName;
	CString mAuthor;
	CString mPublish;
	UINT mKeepCount;
};


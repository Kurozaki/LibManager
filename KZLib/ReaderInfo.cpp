#include "StdAfx.h"
#include "ReaderInfo.h"


ReaderInfo::ReaderInfo(void)
{
}

ReaderInfo::ReaderInfo(CString name, CString idn){
	mName = name;
	mIdNumber = idn;
}

ReaderInfo::~ReaderInfo(void)
{
}

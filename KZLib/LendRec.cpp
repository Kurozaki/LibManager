#include "StdAfx.h"
#include "LendRec.h"


LendRec::LendRec(void)
{
}


LendRec::~LendRec(void)
{
}

void LendRec::SetDateString(CString year, CString month, CString day, CString hour){
	mDate.Format(_T("%s-%s-%s %s:00"), year, month, day, hour);
}
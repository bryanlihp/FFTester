#include "stdafx.h"
#include "GlobalUtil.h"


GlobalUtil::GlobalUtil()
{
}


GlobalUtil::~GlobalUtil()
{
}



void CreateMemLeak(LPCSTR pszDescription)
{
	if (pszDescription == NULL || strlen(pszDescription) == 0)
	{
		char *pMemLeak = new char[20];
		strcpy_s(pMemLeak, 20, "No name memory leak");
	}
	else
	{
		int size = strlen(pszDescription);
		char *pMemLeak = new char[size + 1];
		strcpy_s(pMemLeak, size + 1, pszDescription);
	}
}

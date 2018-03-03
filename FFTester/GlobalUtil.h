#pragma once

void CreateMemLeak(LPCSTR pszDescription);
//#define MEMLEAK_WRAPPER(v) CreateMemLeak(v)
#define MEMLEAK_WRAPPER(v)


class GlobalUtil
{
public:
	GlobalUtil();
	~GlobalUtil();
};


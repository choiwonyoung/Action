// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

// �̸������������ �ֻ����� ���Խ�ų �����...

#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#ifndef _CRT_NON_CONFORMING_SWPRINTFS
#define  _CRT_NON_CONFORMING_SWPRINTFS
#endif

#if !defined(_DEBUG) && !defined(_SECURE_SCL)
#define _SECURE_SCL 0						// Release Mode������ �׻� ���� �ִ� Checked Iterator�� ����.
#endif


#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers

#include <vector>
#include <windows.h>
#include <cstdio>

using namespace std;

#include "../Base/Base.h"



// TODO: reference additional headers your program requires here

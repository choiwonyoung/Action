// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers



#include <windows.h>
#include <cassert>
#include <vector>
#include <cstdio>
#include <string>
#include <map>
#include <hash_map>
#include <vector>
#include <algorithm>
#include <malloc.h>
#include <memory>

#include <d3d11.h>
#include <DirectXMath.h>

using namespace std;
using namespace stdext;
using namespace DirectX;

#include "../Base/Base.h"

#include "../Base/Crc32Static.h"
#include "../Base/C9File.h"

#include "../RXML/RXML.h"

// TODO: reference additional headers your program requires here

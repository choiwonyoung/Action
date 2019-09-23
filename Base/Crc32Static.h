#pragma once

#include <wtypes.h>
#include <windns.h>
//#include "C9Base.h"
#include "Crc32Common.h"



class CCrc32Static
{
public:
	CCrc32Static();
	virtual ~CCrc32Static();

	static DWORD StringCrc32( const char * pszString );
	static DWORD WStringCrc32( const wchar_t * pwszString );
	static DWORD FileCrc32Win32( LPCTSTR szFilename , DWORD &dwCrc32 );
#ifndef _WIN64
	static DWORD FileCrc32Filemap( LPCTSTR szFilename , DWORD &dwCrc32 );
	static DWORD FileCrc32Assembly( LPCTSTR szFilename , DWORD &dwCrc32 );
	static DWORD FileCrc32Assembly( char *pBuffer , DWORD dwSize , DWORD &dwCrc32 );
#endif //#ifndef _WIN64

	static UINT64 StringCrc64( const char * pszString );


protected:
	static bool GetFileSizeQW( const HANDLE hFile , QWORD &qwSize );
	static void CalcCrc32( const BYTE byte , DWORD &dwCrc32 );

	static DWORD s_arrdwCrc32Table[256];
};

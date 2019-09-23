#include "stdafx.h"
#include "Base.h"


CAnsiToUni2::CAnsiToUni2( const char *pStrAnsi )
{
	int iLen = ( int )strlen( pStrAnsi ) + 1;
	m_pString = new wchar_t[iLen];
	MultiByteToWideChar( CP_ACP , 0 , pStrAnsi , -1 , m_pString , iLen );
}

CAnsiToUni2::~CAnsiToUni2()
{
	RSAFE_DELETE_ARRAY( m_pString );
}

CAnsiToUni2::operator wchar_t*( )
{
	return( m_pString );
}

CUniToAnsi2::CUniToAnsi2( const wchar_t *pStrUni )
{
	int iLen = ( int )wcslen( pStrUni ) * 2 + 1;
	m_pString = new char[iLen];
	WideCharToMultiByte( CP_ACP , 0 , pStrUni , -1 , m_pString , iLen , NULL , NULL );
}

CUniToAnsi2::~CUniToAnsi2()
{
	RSAFE_DELETE_ARRAY( m_pString );
}

CUniToAnsi2::operator char*( )
{
	return( m_pString );
}

CUTF8ToUni2::CUTF8ToUni2( const char *pStrAnsi )
{
	int iLen = ( int )strlen( pStrAnsi ) + 1;
	m_pString = new wchar_t[iLen];
	MultiByteToWideChar( CP_UTF8 , 0 , pStrAnsi , -1 , m_pString , iLen );
}

CUTF8ToUni2::~CUTF8ToUni2()
{
	RSAFE_DELETE_ARRAY( m_pString );
}

CUTF8ToUni2::operator wchar_t*( )
{
	return( m_pString );
}


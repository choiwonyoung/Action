#include "stdafx.h"	
//#include "C9Error.h"
#include "C9File.h"
#include "Crc32Static.h"
//#include "C9LogManager.h"


//-----------------------------------------------------------------------------
// Name: Open()
// Desc: 파일 열기 
//-----------------------------------------------------------------------------
bool C9File::Open( const char *pSzFileName )
{
	m_strFileName = pSzFileName;

	m_hFile = CreateFileA( pSzFileName , GENERIC_READ , FILE_SHARE_READ , NULL , OPEN_EXISTING , FILE_FLAG_SEQUENTIAL_SCAN , NULL );

	if( m_hFile == INVALID_HANDLE_VALUE )
	{
		wchar_t strError[256];
		wsprintf( strError , L"Error: Failed to open file (%s)" , pSzFileName );
		MessageBox( NULL , strError , L"Failed Open file" , 0 );
		return false;
	}

	m_dwSize = GetFileSize( m_hFile , NULL );
	m_bSave = false;

	return true;
}

//-----------------------------------------------------------------------------
// Name: Save()
// Desc: 파일 저장
//-----------------------------------------------------------------------------
bool C9File::Save( const char *pSzFileName )
{
	m_hFile = CreateFileA( pSzFileName , GENERIC_WRITE , 0 , NULL , CREATE_ALWAYS , FILE_ATTRIBUTE_NORMAL , NULL );

	if( m_hFile == INVALID_HANDLE_VALUE )
	{
		wchar_t strError[256];
		wsprintf( strError , L"Error: Failed to save file (%s)" , pSzFileName  );
		MessageBox( NULL , strError , L"Failed Save file" , 0 );			
		return false;
	}

	m_strFileName = pSzFileName;
	m_bSave = true;
	return true;
}


//-----------------------------------------------------------------------------
// Name: WriteData()
// Desc: 
//-----------------------------------------------------------------------------
void C9File::WriteData( const char *pSzString )
{
	assert( IsSave() );
	int iLength = static_cast< int >( strlen( pSzString ) );
	if( iLength > 0 )
	{
		iLength++;
		WriteData( iLength );
		WriteData( pSzString , sizeof( char ) * iLength );
	}
	else
	{
		WriteData( 0 );
	}
}

void C9File::WriteData( const string & strData )
{
	assert( IsSave() );
	return WriteData( strData.c_str() );
}

void C9File::WriteData( const wchar_t *pSzString )
{
	assert( IsSave() );
	int iLength = static_cast< int >( wcslen( pSzString ) );
	if( iLength > 0 )
	{
		iLength++;
		WriteData( iLength );
		WriteData( pSzString , sizeof( wchar_t ) * iLength );
	}
	else
	{
		WriteData( 0 );
	}
}

void C9File::WriteData( int iData )
{
	assert( IsSave() );
	WriteFile( m_hFile , &iData , sizeof( int ) , &m_dwTemp , NULL );
}

void C9File::WriteData( float fData )
{
	assert( IsSave() );
	WriteFile( m_hFile , &fData , sizeof( float ) , &m_dwTemp , NULL );
}

void C9File::WriteData( double dData )
{
	assert( IsSave() );
	WriteFile( m_hFile , &dData , sizeof( double ) , &m_dwTemp , NULL );
}

void C9File::WriteData( UINT uiData )
{
	assert( IsSave() );
	WriteFile( m_hFile , &uiData , sizeof( UINT ) , &m_dwTemp , NULL );
}

void C9File::WriteData( char cData )
{
	assert( IsSave() );
	WriteFile( m_hFile , &cData , sizeof( char ) , &m_dwTemp , NULL );
}

void C9File::WriteData( unsigned char ucData )
{
	assert( IsSave() );
	WriteFile( m_hFile , &ucData , sizeof( unsigned char ) , &m_dwTemp , NULL );
}

void C9File::WriteData( UINT16 usData )
{
	assert( IsSave() );
	WriteFile( m_hFile , &usData , sizeof( UINT16 ) , &m_dwTemp , NULL );
}

void C9File::WriteData( DWORD dwData )
{
	assert( IsSave() );
	WriteFile( m_hFile , &dwData , sizeof( DWORD ) , &m_dwTemp , NULL );
}

void C9File::WriteData( UINT64 dwData )
{
	assert( IsSave() );
	WriteFile( m_hFile , &dwData , sizeof( UINT64 ) , &m_dwTemp , NULL );
}

void C9File::WriteData( INT64 dwData )
{
	assert( IsSave() );
	WriteFile( m_hFile , &dwData , sizeof( INT64 ) , &m_dwTemp , NULL );
}

#ifdef _WIN64
void C9File::WriteData_SizeT( size_t dwData )
{
	UINT tempData = ( UINT )dwData;
	assert( IsSave() );
	WriteFile( m_hFile , &tempData , sizeof( UINT ) , &m_dwTemp , NULL );
}

void C9File::WriteData_SizeT( const void *pData , size_t size )
{
	DWORD dwSize = ( DWORD )size;
	assert( dwSize > 0 );
	assert( IsSave() );
	WriteFile( m_hFile , pData , dwSize , &m_dwTemp , NULL );
}

#endif //#ifdef _WIN64

void C9File::WriteData( bool bData )
{
	assert( IsSave() );
	WriteFile( m_hFile , &bData , sizeof( bool ) , &m_dwTemp , NULL );
}

void C9File::WriteData( const void *pData , DWORD dwSize )
{
	assert( dwSize > 0 );
	assert( IsSave() );
	WriteFile( m_hFile , pData , dwSize , &m_dwTemp , NULL );
}



void C9File::WriteData( const wstring & wstrData )
{
	assert( IsSave() );
	WriteData( wstrData.c_str() );
}

void C9File::WriteData( const CBitArray & bitArray )
{
	assert( IsSave() );
	const int iBitLength = bitArray.GetBitLength();
	WriteFile( m_hFile , &iBitLength , sizeof( int ) , &m_dwTemp , NULL );
	if( iBitLength > 0 )
		WriteFile( m_hFile , bitArray.GetBuffer() , sizeof( BYTE ) * bitArray.GetAllocSize() , &m_dwTemp , NULL );
}

void C9File::Close()
{
	CloseHandle( m_hFile ); m_hFile = NULL;
}

C9File::~C9File()
{
	Close();
}

void C9File::SetPos( LONG lPos )
{
	SetFilePointer( m_hFile , lPos , NULL , FILE_BEGIN );
}

bool C9File::IsEnd() const
{
	return false;
}

C9File::C9File()
{
	m_hFile = NULL;
	m_dwSize = 0;
	m_bSave = false;
	m_typeData = 0;
}

void C9File::LoadStringTable( wchar_t* pFileBuffer , vector< wstring >	&textString , hash_map<DWORD , int> &mapStringTable )
{

	wchar_t buffer1[256];
	wchar_t buffer2[4096];

	const wchar_t* strSep = L"\n\r\0";
	wchar_t* pNextToken = NULL;

	wchar_t* pToken = wcstok_s( &( pFileBuffer[1] ) , strSep , &pNextToken );
	if( NULL != pToken )
	{
		if( L';' != pToken[0] )
		{
			if( 2 == ::swscanf( pToken , L"%s %[^\0]" , buffer1 , buffer2 ) )
			{
				DWORD dwKey = CCrc32Static::WStringCrc32( buffer1 );
				mapStringTable.insert( hash_map<DWORD , int>::value_type( dwKey , ( int )textString.size() ) );
			}
		}
		textString.push_back( pToken );
	}

	while( true )
	{
		pToken = ::wcstok_s( NULL , strSep , &pNextToken );
		if( NULL == pToken || 0 == wcsncmp( pToken , L"[EOF]" , 5 ) )
			break;
		else
		{
			if( L';' != pToken[0] )
			{
				if( 2 == ::swscanf( pToken , L"%s %[^\0]" , buffer1 , buffer2 ) )
				{
					DWORD dwKey = CCrc32Static::WStringCrc32( buffer1 );
					mapStringTable.insert( hash_map<DWORD , int>::value_type( dwKey , ( int )textString.size() ) );
				}
			}
			textString.push_back( pToken );
		}
	}
}

void C9File::ConvertStringTable( wchar_t* pFileBuffer , vector< wstring >	&textString , hash_map<DWORD , int> &mapStringTable )
{
	wchar_t buffer1[256];
	wchar_t buffer2[4096];

	const wchar_t* strSep = L"\n\r\0";
	wchar_t* pNextToken = NULL;

	wchar_t* pToken = wcstok_s( &( pFileBuffer[1] ) , strSep , &pNextToken );
	if( NULL != pToken )
	{
		if( L';' != pToken[0] )
		{
			if( 2 == ::swscanf( pToken , L"%s %[^\0]" , buffer1 , buffer2 ) )
			{
				DWORD dwKey = CCrc32Static::WStringCrc32( buffer1 );

				hash_map<DWORD , int>::iterator pos = mapStringTable.find( dwKey );
				if( pos != mapStringTable.end() )
				{
					int iIndex = pos->second;

					textString[iIndex] = pToken;
				}
			}
		}
	}

	while( true )
	{
		pToken = ::wcstok_s( NULL , strSep , &pNextToken );
		if( NULL == pToken || 0 == wcsncmp( pToken , L"[EOF]" , 5 ) )
			break;
		else
		{
			if( L';' != pToken[0] )
			{
				if( 2 == ::swscanf( pToken , L"%s %[^\0]" , buffer1 , buffer2 ) )
				{
					DWORD dwKey = CCrc32Static::WStringCrc32( buffer1 );

					hash_map<DWORD , int>::iterator pos = mapStringTable.find( dwKey );
					if( pos != mapStringTable.end() )
					{
						int iIndex = pos->second;

						textString[iIndex] = pToken;
					}
				}
			}
		}
	}
}

void C9File::SaveStringTable( const wchar_t *pwszOutFileName , vector< wstring >	&textString )
{
	FILE *fp;
	fp = _wfopen( pwszOutFileName , L"wt, ccs=UNICODE" );

	for( UINT i = 0; i < textString.size(); ++i )
	{
		wstring &strTextString = textString[i];
		if( strTextString != L"<Delete string>" )
		{
			strTextString += L"\n";
			fwrite( strTextString.c_str() , sizeof( wchar_t ) , strTextString.size() , fp );
		}
	}

	if( fp )
	{
		fwprintf( fp , L"[EOF]" );
		fclose( fp );
	}
}

// C9ReadBuffer ////////////////////////////////////////////////////////////////////////

void C9ReadBuffer::ReadAllBuffer()
{
	assert( m_bSave == false );
	assert( m_pBuffer == NULL );

	m_pBuffer = new char[m_dwSize];

	ReadFile( m_hFile , m_pBuffer , m_dwSize , &m_dwTemp , NULL );

	m_pBufferPos = m_pBuffer;
	m_bMemSet = false;
}

void C9ReadBuffer::SetReadBuffer( const char *pSzFileName , char *pBuffer , DWORD dwSize , bool bMemSet )
{
	UNUSED_ARG( bMemSet );

	m_strFileName = pSzFileName;

	{
		m_pBuffer = new char[dwSize + 2];
		memcpy( m_pBuffer , pBuffer , dwSize );
		// 버퍼 끝처리
		m_pBuffer[dwSize] = 0;
		m_pBuffer[dwSize + 1] = 0;
	}
	m_pBufferPos = m_pBuffer;
	m_dwSize = dwSize;
	m_bSave = false;
}

void C9ReadBuffer::SetReadBuffer( const char *pSzFileName , BufferPtr spBuffer , DWORD dwSize )
{
	m_strFileName = pSzFileName;

	m_spBuffer = spBuffer;			// 스마트 포인터가 소멸되지 않도록 저장한다. (객체 소멸시 메모리 삭제되도록)
	m_pBuffer = spBuffer.get();

	m_pBufferPos = m_pBuffer;
	m_dwSize = dwSize;
	m_bSave = false;
}

C9ReadBuffer::C9ReadBuffer()
{
	m_pBuffer = NULL;
	m_pBufferPos = NULL;
	m_bMemSet = false;
	m_typeData = 1;
}

C9ReadBuffer::~C9ReadBuffer()
{
	Close();
}

void C9ReadBuffer::Close()
{
	if( m_bMemSet )
		m_pBuffer = NULL;
	else if( m_spBuffer )
	{
		// 스마트 포인터를 들고 있었던 경우는 메모리가 자동 소멸되므로 m_pBuffer를 그냥 NULL로 셋팅
		m_pBuffer = NULL;
	}
	else
		RSAFE_DELETE_ARRAY( m_pBuffer );
	m_pBufferPos = NULL;
}

void C9ReadBuffer::SetPos( LONG lPos )
{
	m_pBufferPos = m_pBuffer + lPos;
}

bool C9ReadBuffer::IsEnd() const
{
	return ( m_pBufferPos >= ( m_pBuffer + m_dwSize ) ) ? true : false;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////

bool C9File::ReadData( void *pData , DWORD dwSize )
{
	assert( dwSize > 0 );
	if( m_typeData )
		return ( ( C9ReadBuffer* )( this ) )->C9ReadBuffer::ReadDataImpl( pData , dwSize );
	else
		return C9File::ReadDataImpl( pData , dwSize );
}
#ifdef _WIN64
bool C9File::ReadData_SizeT( size_t& data )
{
	bool bRet = false;
	UINT tempData = 0;

	if( m_typeData )
	{
		bRet = ( ( C9ReadBuffer* )( this ) )->C9ReadBuffer::ReadDataImpl( tempData );
		data = tempData;
		return bRet;
	}
	else
	{
		bRet = C9File::ReadDataImpl( tempData );
		data = tempData;
		return bRet;
	}
}

bool C9File::ReadData_SizeT( void *pData , size_t size )
{
	assert( size > 0 );
	if( m_typeData )
		return ( ( C9ReadBuffer* )( this ) )->C9ReadBuffer::ReadDataImpl( pData , ( DWORD )size );
	else
		return C9File::ReadDataImpl( pData , ( DWORD )size );
}
#endif //#ifdef _WIN64

void* C9File::allocateStringBuffer( size_t size )
{
	if( stringBuffer.size() < size )
		stringBuffer.resize( size );
	return &stringBuffer[0];
}


bool C9File::ReadDataImpl( void *pData , DWORD dwSize )
{
	assert( dwSize > 0 );
	assert( IsSave() == false );
	return ( TRUE == ReadFile( m_hFile , pData , dwSize , &m_dwTemp , NULL ) ) ? true : false;
}


bool C9ReadBuffer::ReadDataImpl( void *pData , DWORD dwSize )
{
	if( ( m_pBufferPos + dwSize ) > ( m_pBuffer + m_dwSize ) )
		return FALSE;

	memcpy( pData , m_pBufferPos , dwSize );
	m_pBufferPos += dwSize;
	return TRUE;
}

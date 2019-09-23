#pragma once

#define	C9_SIZE_OF_BETWEEN_VALUE( _front, _back )			size_t( size_t( &_back ) - size_t( &_front ) + sizeof( _back ) )

#pragma warning(push)
#pragma warning(disable:4127)
#pragma warning(disable:4244)
#pragma warning(disable:4512)
#pragma warning(disable:4819)
#include <boost/type_traits/is_pod.hpp>
#pragma warning(pop)

#include "BitArray.h"


class C9File
{
public:
	C9File();
	virtual ~C9File();

	virtual bool	Open( const char *pSzFileName );
	virtual bool	Save( const char *pSzFileName );
	virtual void	Close();

	virtual void	WriteData( int iData );
	virtual void	WriteData( float fData );
	virtual void	WriteData( double dData );
	virtual void	WriteData( UINT uiData );
	virtual void	WriteData( char cData );
	virtual void	WriteData( unsigned char ucData );
	virtual void	WriteData( UINT16 usData );
	virtual void	WriteData( DWORD dwData );
	virtual void	WriteData( UINT64 dwData );
	virtual void	WriteData( INT64 dwData );
	virtual void 	WriteData( bool bData );
	virtual void	WriteData( const char *pSzString );
	virtual void	WriteData( const string & strData );
	virtual void	WriteData( const wchar_t *pSzString );
	virtual void	WriteData( const void *pData , DWORD dwSize );
#ifdef _WIN64
	virtual void	WriteData_SizeT( const void *pData , size_t size );
	virtual void	WriteData_SizeT( size_t dwData );	//64비트 서버에서 size_t 저장 된것 사용하기 UINT로 바꿔서 저장
#else //#ifdef _WIN64
#define	WriteData_SizeT WriteData
#endif //#ifdef _WIN64
	virtual void	WriteData( const wstring & wstrData );
	virtual void	WriteData( const CBitArray & bitArray );


	template<typename DataType>	bool ReadData( DataType& data );
	bool			ReadData( void *pData , DWORD dwSize );
#ifdef _WIN64
	bool ReadData_SizeT( size_t& data );
	bool			ReadData_SizeT( void *pData , size_t size );
#else //#ifdef _WIN64
#define ReadData_SizeT ReadData
#endif //#ifdef _WIN64

	virtual void	SetPos( LONG lPos );

	bool			IsSave() const { return m_bSave; }
	DWORD			GetSize() const { return m_dwSize; }
	const char*		GetFileName() const { return m_strFileName.c_str(); }
	virtual bool	IsEnd() const;

	static void		LoadStringTable( wchar_t* pFileBuffer , vector< wstring >	&textString , hash_map<DWORD , int> &mapStringTable );
	static void		SaveStringTable( const wchar_t *pwszOutFileName , vector< wstring >	&textString );
	static void		ConvertStringTable( wchar_t* pFileBuffer , vector< wstring >	&textString , hash_map<DWORD , int> &mapStringTable );

protected:
	void*			allocateStringBuffer( size_t size );

private:
	template<typename StringType>	bool ReadDataStringImpl( StringType& strData );
	template<typename DataType>		bool ReadDataImpl( DataType &bData );
	template<> 						bool ReadDataImpl( string &strData );
	template<> 						bool ReadDataImpl( wstring &strData );
	template<> 						bool ReadDataImpl( CBitArray & bitArray );
	bool ReadDataImpl( void *pData , DWORD dwSize );

protected:
	vector<BYTE>	stringBuffer;
	HANDLE			m_hFile;
	DWORD			m_dwTemp;
	string			m_strFileName;
	DWORD			m_dwSize;
	bool			m_bSave;

	int				m_typeData;	// 0: C9File, 1:C9ReadBuffer
};


// C9PackFile ///////////////////////////////////////////////////////////////////////

class C9ReadBuffer : public C9File
{
public:
	friend C9File; // hack. see implementation of ' template<typename DataType> bool C9File::ReadData(DataType& data) '

	C9ReadBuffer();
	virtual ~C9ReadBuffer();
	
	typedef				std::shared_ptr< char > BufferPtr;

	void				ReadAllBuffer();
	void				SetReadBuffer( const char *pSzFileName , char *pBuffer , DWORD dwSize , bool bMemSet = false );
	void				SetReadBuffer( const char *pSzFileName , BufferPtr spBuffer , DWORD dwSize );
	virtual void		Close();

	virtual void		SetPos( LONG lPos );
	virtual bool		IsEnd() const;

	char*				GetBuffer() { return m_pBuffer; }

private:
	bool				ReadDataImpl( void *pData , DWORD dwSize );

	template<typename DataType>		bool	ReadDataImpl( DataType& bData );
	template<> 						bool 	ReadDataImpl( string& strData );
	template<> 						bool 	ReadDataImpl( wstring& strData );
	template<> 						bool 	ReadDataImpl( CBitArray& bitArray );

	template<typename StringType>	bool	ReadDataStringImpl( StringType& strData );

private:
	char*	m_pBuffer;
	char*	m_pBufferPos;
	bool	m_bMemSet;
	BufferPtr m_spBuffer;
};

template<typename DataType>
bool C9File::ReadData( DataType& data )
{
	if( m_typeData )
		return ( ( C9ReadBuffer* )( this ) )->C9ReadBuffer::ReadDataImpl( data );
	else
		return C9File::ReadDataImpl( data );
}

template<typename StringType>
bool C9File::ReadDataStringImpl( StringType& strData )
{
	assert( IsSave() == false );
	int iSize;
	C9File::ReadDataImpl( iSize );
	strData.resize( 0 );

	if( iSize > 0 )
	{
		StringType::value_type *pSzBuf = static_cast< StringType::value_type * >( allocateStringBuffer( iSize * sizeof( StringType::value_type ) ) );
		if( ReadFile( m_hFile , pSzBuf , sizeof( StringType::value_type ) * iSize , &m_dwTemp , NULL ) == FALSE )
			return FALSE;

		strData = pSzBuf;
	}
	return TRUE;
}

template<typename DataType>
bool C9ReadBuffer::ReadDataImpl( DataType &bData )
{
	_STATIC_ASSERT( __has_trivial_copy( DataType ) || boost::is_pod<DataType>::value ); // 컴파일 타임 memcpy 가능 여부 체크 (여기서 이상한 에러나면 잘못된 객체임) ; 모든 경우를 다 막을 순 없음

	if( ( m_pBufferPos + sizeof( DataType ) ) > ( m_pBuffer + m_dwSize ) )
		return FALSE;

	bData = *( DataType* )m_pBufferPos;
	m_pBufferPos += sizeof( DataType );
	return TRUE;
}

// 기본 구현은 memcpy 가 가능한 것에 대해서만 수행한다.
template<typename DataType>
bool C9File::ReadDataImpl( DataType &bData )
{
	_STATIC_ASSERT( __has_trivial_copy( DataType ) || boost::is_pod<DataType>::value ); // 컴파일 타임 memcpy 가능 여부 체크 (여기서 이상한 에러나면 잘못된 객체임) ; 모든 경우를 다 막을 순 없음
	assert( IsSave() == false );
	return ( TRUE == ReadFile( m_hFile , &bData , sizeof( DataType ) , &m_dwTemp , NULL ) ) ? true : false;
}

template<typename StringType>
bool C9ReadBuffer::ReadDataStringImpl( StringType& strData )
{
	int iSize;
	C9ReadBuffer::ReadDataImpl( iSize );
	strData.resize( 0 );

	if( iSize > 0 )
	{
		int ReadSize = iSize * sizeof( StringType::value_type );
		StringType::value_type *pSzBuf = static_cast< StringType::value_type * >( allocateStringBuffer( ReadSize ) );
		ReadDataImpl( pSzBuf , ReadSize );
		strData = pSzBuf;
	}
	return TRUE;
}


template<>
bool C9File::ReadDataImpl( CBitArray & bitArray )
{
	assert( IsSave() == false );

	int iBitLength = 0;
	C9File::ReadDataImpl( iBitLength );

	if( iBitLength > 0 )
	{
		bitArray.SetBitLength( iBitLength );
		return C9File::ReadDataImpl( bitArray.GetBuffer() , sizeof( BYTE ) * bitArray.GetAllocSize() );
	}

	return TRUE;
}

template<>
bool C9File::ReadDataImpl( wstring &strData )
{
	return C9File::ReadDataStringImpl<wstring>( strData );
}
template<>
bool C9File::ReadDataImpl( string &strData )
{
	return C9File::ReadDataStringImpl<string>( strData );
}

template<>
bool C9ReadBuffer::ReadDataImpl( CBitArray & bitArray )
{
	int iBitLength = 0;
	C9ReadBuffer::ReadDataImpl( iBitLength );

	if( iBitLength > 0 )
	{
		bitArray.SetBitLength( iBitLength );
		return C9ReadBuffer::ReadDataImpl( bitArray.GetBuffer() , sizeof( BYTE ) * bitArray.GetAllocSize() );
	}

	return TRUE;
}

template<>
bool C9ReadBuffer::ReadDataImpl( wstring &strData )
{
	return C9ReadBuffer::ReadDataStringImpl<wstring>( strData );
}

template<>
bool C9ReadBuffer::ReadDataImpl( string &strData )
{
	return C9ReadBuffer::ReadDataStringImpl<string>( strData );
}

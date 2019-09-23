#include "stdafx.h"
#include "BitArray.h"

#define 	SEG_COUNT		10240

//////////////////////////////////////////////////////////////////////////
// Constructer / Destructer
CBitArray::CBitArray()
	: m_pBuffer( NULL )
	, m_iBitLength( 0 )
	, m_iAllocSize( 0 )
{
}

CBitArray::CBitArray( const CBitArray &src )
	: m_pBuffer( NULL )
	, m_iBitLength( 0 )
	, m_iAllocSize( 0 )
{
	*this = src;
}

CBitArray::CBitArray( BYTE * pBuffer , int iSize )
	: m_pBuffer( NULL )
	, m_iBitLength( 0 )
	, m_iAllocSize( 0 )
{
	Init( pBuffer , iSize << 3 );
}

CBitArray::CBitArray( int iBitLenght )
	: m_pBuffer( NULL )
	, m_iBitLength( 0 )
	, m_iAllocSize( 0 )
{
	UNUSED_ARG( iBitLenght );

	Init( NULL , m_iBitLength );
}

CBitArray::~CBitArray()
{
	RSAFE_DELETE_ARRAY( m_pBuffer );
}

//////////////////////////////////////////////////////////////////////////
// Utility function
int			CBitArray::GetOnBitCount() const
{
	int nBitOnCount = 0;

	for( int iBit = 0; iBit < m_iBitLength; ++iBit )
	{
		if( GetBit( m_pBuffer , iBit ) )
			++nBitOnCount;
	}

	return nBitOnCount;
}

void		CBitArray::ResetAt( const CBitArray & src )
{
	int iBitLength = min( m_iBitLength , src.m_iBitLength );
	for( int iBit = 0; iBit < iBitLength; ++iBit )
	{
		if( src.IsBit( iBit ) )
			ResetBit( m_pBuffer , iBit );
	}
}

bool		CBitArray::IsBit( int iBit ) const
{
	if( m_pBuffer == NULL || iBit >= m_iBitLength )
		return false;

	return GetBit( m_pBuffer , iBit );
}

bool		CBitArray::IsBit( const CBitArray & src ) const
{
	int iSize = min( m_iAllocSize , src.m_iAllocSize );

	for( int nByte = 0; nByte < iSize; ++nByte )
		if( ( m_pBuffer[nByte] & src.m_pBuffer[nByte] ) != 0 )
			return true;

	return false;
}

void		CBitArray::Set( int iBit )
{
	if( iBit >= m_iBitLength )
		SetBitLength( iBit + 1 );

	SetBit( m_pBuffer , iBit );
}

void		CBitArray::Set( const CBitArray & src )
{
	if( m_iBitLength < src.m_iBitLength )
		SetBitLength( src.m_iBitLength );
	for( int nByte = 0; nByte < src.m_iAllocSize; ++nByte )
		m_pBuffer[nByte] |= src.m_pBuffer[nByte];
}

void		CBitArray::Reset( int iBit )
{
	if( iBit < m_iBitLength )
		ResetBit( m_pBuffer , iBit );
}

void		CBitArray::Reset( const CBitArray & src )
{
	if( m_iBitLength < src.m_iBitLength )
		SetBitLength( src.m_iBitLength );

	for( int nByte = 0; nByte < src.m_iAllocSize; ++nByte )
		m_pBuffer[nByte] &= ~src.m_pBuffer[nByte];
}

void		CBitArray::SetBitLength( int iBitLength )
{
	int iNewAllocSize = ( iBitLength + 7 ) >> 3;

	if( iNewAllocSize == 0 )
	{
		RSAFE_DELETE_ARRAY( m_pBuffer );

		m_pBuffer = NULL;
		m_iBitLength = 0;
		m_iAllocSize = 0;
	}
	else if( iNewAllocSize > m_iAllocSize )
	{
		if( m_pBuffer == NULL )
		{
			m_pBuffer = new BYTE[iNewAllocSize];
			memset( m_pBuffer , 0x00 , iNewAllocSize );
		}
		else
		{
			BYTE *pOldData = m_pBuffer;
			m_pBuffer = new BYTE[iNewAllocSize];
			memcpy( m_pBuffer , pOldData , m_iAllocSize );
			RSAFE_DELETE_ARRAY( pOldData );

			memset( ( BYTE * )m_pBuffer + m_iAllocSize , 0 , iNewAllocSize - m_iAllocSize );
		}
	}

	m_iBitLength = iBitLength;
	m_iAllocSize = iNewAllocSize;
}


//////////////////////////////////////////////////////////////////////////
// operator
void CBitArray::operator&=( const CBitArray & src )
{
	int iAllocSize = min( m_iAllocSize , src.m_iAllocSize );

	for( int nByte = 0; nByte < iAllocSize; ++nByte )
		m_pBuffer[nByte] &= src.m_pBuffer[nByte];
}

void CBitArray::operator^=( const CBitArray& src )
{
	if( m_iBitLength < src.m_iBitLength )
		SetBitLength( src.m_iBitLength );

	for( int nByte = 0; nByte < m_iAllocSize; ++nByte )
		m_pBuffer[nByte] ^= src.m_pBuffer[nByte];
}

CBitArray CBitArray::operator&( const CBitArray& src )
{
	CBitArray bitArray = *this;
	bitArray &= src;

	return bitArray;
}

CBitArray CBitArray::operator|( const CBitArray& src )
{
	CBitArray bitArray = *this;
	bitArray |= src;

	return bitArray;
}

CBitArray CBitArray::operator^( const CBitArray& src )
{
	CBitArray bitArray = *this;
	bitArray ^= src;

	return bitArray;
}

//////////////////////////////////////////////////////////////////////////
// private function
void		CBitArray::Init( BYTE * pBuffer , int iBitLength )
{
	m_iBitLength = iBitLength;
	m_iAllocSize = ( iBitLength + 7 ) >> 3;
	if( m_iAllocSize > 0 )
	{
		m_pBuffer = new BYTE[m_iAllocSize];
		if( pBuffer == NULL )
			ZeroMemory( m_pBuffer , m_iAllocSize );
		else
			memcpy( m_pBuffer , pBuffer , m_iAllocSize );
	}
}

int CBitArray::GetBitLength() const
{
	return m_iBitLength;
}

int CBitArray::GetAllocSize() const
{
	return m_iAllocSize;
}

void CBitArray::SetAll()
{
	memset( m_pBuffer , 0xff , m_iAllocSize );
}

void CBitArray::ResetAll()
{
	memset( m_pBuffer , 0 , m_iAllocSize );
}

const BYTE * CBitArray::GetBuffer() const
{
	return m_pBuffer;
}

BYTE * CBitArray::GetBuffer()
{
	return m_pBuffer;
}

bool CBitArray::operator[]( int iBit ) const
{
	return IsBit( iBit );
}

void CBitArray::operator=( const CBitArray& src )
{
	Init( src.m_pBuffer , src.m_iBitLength );
}

void CBitArray::operator|=( const CBitArray& src )
{
	Set( src );
}

bool CBitArray::operator==( const CBitArray& src ) const
{
	return m_iBitLength == src.m_iBitLength && memcmp( m_pBuffer , src.m_pBuffer , m_iAllocSize ) == 0;
}

bool CBitArray::operator!=( const CBitArray& src ) const
{
	return m_iBitLength != src.m_iBitLength || memcmp( m_pBuffer , src.m_pBuffer , m_iAllocSize ) != 0;
}

bool CBitArray::operator&&( const CBitArray& src ) const
{
	return IsBit( src );
}
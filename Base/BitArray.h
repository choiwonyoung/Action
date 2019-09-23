#pragma once

#define GetBit(a, b)	((((BYTE*)a)[(b)>>3] >> ((b)&7)) & 1)
#define SetBit(a, b)	(((BYTE*)a)[(b)>>3] |= (1 << ((b)&7)))
#define ResetBit(a, b)	(((BYTE*)a)[(b)>>3] &= ~(1 << ((b)&7)))
#define XOrBit(a, b)	(((BYTE*)a)[(b)>>3] ^= (1 << ((b)&7)))

class CBitArray
{
public:
	CBitArray();
	CBitArray( const CBitArray & src );
	CBitArray( BYTE * pBuffer , int iSize );
	CBitArray( int iBitLenght );
	~CBitArray();

public:
	int					GetBitLength() const;	
	int					GetAllocSize() const;
	int					GetOnBitCount() const;

	bool				IsBit( int iBit ) const;
	bool				IsBit( const CBitArray& src ) const;

	void				Set( int iBit );
	void				Set( const CBitArray& src );
	void				Reset( int iBit );
	void				Reset( const CBitArray& src );

	void				ResetAt( const CBitArray & src );	// reset all bits that have ones values at the input bitarray
	void				SetAll();
	void				ResetAll();

	const BYTE *		GetBuffer() const;
	BYTE *				GetBuffer();

	void				SetBitLength( int iBitLength );

	bool operator[]( int iBit ) const;

	void operator=( const CBitArray& src );
	void operator|=( const CBitArray& src );
	void operator&=( const CBitArray& src );
	void operator^=( const CBitArray& src );
	bool operator==( const CBitArray& src ) const;
	bool operator!=( const CBitArray& src ) const;
	bool operator&&( const CBitArray& src ) const;

	CBitArray operator&( const CBitArray& src );
	CBitArray operator|( const CBitArray& src );
	CBitArray operator^( const CBitArray& src );

private:
	void		Init( BYTE * pBuffer , int iBitLength );

private:
	BYTE *		m_pBuffer;				// byte steam pointer

	int			m_iBitLength;
	int			m_iAllocSize;
};


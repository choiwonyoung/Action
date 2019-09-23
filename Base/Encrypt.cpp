#include "stdafx.h"
#include "Encrypt.h"


CEncrypt::CEncrypt()
{
}


CEncrypt::~CEncrypt()
{
}


const char CEncrypt::s_base64_table[] =
{
	'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
	'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
	'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
	'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
	'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '+', '-', '\0'
};

const char CEncrypt::s_base64_pad = '#';


bool CEncrypt::Encode( const void *inbuffer , int length , string & strOut )
{
	const unsigned char *current = ( unsigned char * )inbuffer;
	int i = 0;
	int wi = 0;
	int nAllocSize = ( ( length + 3 - length % 3 ) * 4 / 3 + 1 ) * sizeof( char );
	nAllocSize += ( nAllocSize / 80 + 1 ) * 2;

	strOut.resize( nAllocSize );

	char * result = &strOut[0];

	while( length > 2 )
	{
		result[i++] = s_base64_table[current[0] >> 2];
		result[i++] = s_base64_table[( ( current[0] & 0x03 ) << 4 ) + ( current[1] >> 4 )];
		result[i++] = s_base64_table[( ( current[1] & 0x0f ) << 2 ) + ( current[2] >> 6 )];
		result[i++] = s_base64_table[current[2] & 0x3f];

		current += 3;
		length -= 3;
		wi += 4;

		if( wi % 80 == 0 )
		{
			result[i++] = '\r';
			result[i++] = '\n';
		}
	}

	if( length != 0 )
	{
		result[i++] = s_base64_table[current[0] >> 2];
		if( length > 1 )
		{
			result[i++] = s_base64_table[( ( current[0] & 0x03 ) << 4 ) + ( current[1] >> 4 )];
			result[i++] = s_base64_table[( current[1] & 0x0f ) << 2];
			result[i++] = s_base64_pad;
		}
		else
		{
			result[i++] = s_base64_table[( current[0] & 0x03 ) << 4];
			result[i++] = s_base64_pad;
			result[i++] = s_base64_pad;
		}
	}

	result[i] = '\0';

	strOut.resize( i );

	return true;
}

bool CEncrypt::Encode( const string & strIn , string & strOut )
{
	return Encode( strIn.c_str() , ( int )( sizeof( char ) * strIn.length() ) , strOut );
}

bool CEncrypt::Decode( const void * inbuffer , int length , string & strOut )
{
	const unsigned char *current = ( unsigned char * )inbuffer;
	int ch , i = 0 , j = 0 , k;

	strOut.resize( ( length / 4 * 3 + 1 ) * sizeof( char ) );

	char * result = &strOut[0];

	if( result == NULL )
	{
		return NULL;
	}

	while( ( ch = *current++ ) != '\0' )
	{
		if( ch == s_base64_pad )
			break;

		const char * chp = strchr( s_base64_table , ch );

		if( chp == NULL )
			continue;

		ch = ( int )( chp - s_base64_table );

		switch( i % 4 )
		{
			case 0:
				result[j] = ( char )( ch << 2 );
				break;

			case 1:
				result[j++] |= ch >> 4;
				result[j] = ( ch & 0x0f ) << 4;
				break;

			case 2:
				result[j++] |= ch >> 2;
				result[j] = ( ch & 0x03 ) << 6;
				break;

			case 3:
				result[j++] |= ch;
				break;
		}
		i++;
	}

	k = j;

	strOut.resize( k );

	return true;
}

bool CEncrypt::Decode( const string & strIn , string & strOut )
{
	return Decode( strIn.c_str() , ( int )( sizeof( char ) * strIn.length() ) , strOut );
}
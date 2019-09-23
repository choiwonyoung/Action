#pragma once
class CEncrypt
{
public:
	CEncrypt();
	~CEncrypt();

	bool	Encode( const void * inbuffer , int length , string & strOut );
	bool	Decode( const void * inbuffer , int length , string & strOut );
	bool	Encode( const string & strIn , string & strOut );
	bool	Decode( const string & strIn , string & strOut );

private:
	const static char	s_base64_table[65];
	const static char	s_base64_pad;
};


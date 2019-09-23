#pragma once

#pragma warning (disable : 4996)

class TiXmlDocument;
class RXMLNode;

#include "tinyxml.h"

typedef RXMLNode XMLNode;
typedef std::vector< RXMLNode* > XMLNodes;

class RXML
{	
public:
	RXML(void);
	virtual ~RXML(void);

	bool		Load( const char * pszFilename, bool bErrorMsgBox = true );	
	bool		LoadBuffer( const char *pBuffer, bool bErrorMsgBox = true );
	XMLNodes	GetChilds( const char * pszChildName );
	XMLNode*	GetChild( const char * pszChildName );
	XMLNode *	GetRootChild( const char * pszChildName );
	XMLNodes	GetRootChilds( const char * pszChildName );
	void		Close() { };

	XMLNode *	CreateRootNode(const char *pSzRootName);
	XMLNode *	CreateRootCommentNode(const char *pSzRootName);
	bool		Save(const char* pSzFileName);

private:
	TiXmlDocument	*m_pXMLDocument;	
};

class RXMLNode : public TiXmlNode
{	
public:	
	RXMLNode(void);
	virtual ~RXMLNode(void);

	XMLNode*	GetChild( const char * pszChildName )			{ return (XMLNode*)FirstChild( pszChildName ); }
	XMLNode*	GetChild( const wchar_t * pwszChildName )		{ return (XMLNode*)FirstChild( UniToAnsi2( pwszChildName ) ); }
	XMLNode*	GetChildFormat( const char *pSzFormat, ... );
	XMLNodes	GetChilds( const char * pszChildName );
	XMLNodes	GetChilds();
	string		GetAttr( const char * pszAttrName );
	string		Value();
	void		SetValue(const char * _value);

	void		RemoveAttr( const char * pszAttrName );
	void		SetAttrFloat( const char * pSzAttrName, float &fValue );
	void		SetAttrDWORD( const char *pSzAttrName, ULONG &dwValue );

	int			GetAttrInt( const char *pSzAttrName )		{ string strTemp = GetAttr(pSzAttrName); return strTemp.empty() ? 0 : atoi(strTemp.c_str()); }
	UINT		GetAttrUINT( const char *pSzAttrName )		{ string strTemp = GetAttr(pSzAttrName); return strTemp.empty() ? 0 : (UINT)atoi(strTemp.c_str()); }
	UINT8		GetAttrUCHAR( const char *pSzAttrName )		{ string strTemp = GetAttr(pSzAttrName); return strTemp.empty() ? 0 : (UINT8)atoi(strTemp.c_str()); }
	ULONG		GetAttrDWORD( const char *pSzAttrName )		{ string strTemp = GetAttr(pSzAttrName); return strTemp.empty() ? ULONG_MAX : (ULONG)atoi(strTemp.c_str()); }
	UINT64		GetAttrDWORD64( const char *pSzAttrName )	{ string strTemp = GetAttr(pSzAttrName); return strTemp.empty() ? ULLONG_MAX : (UINT64)_atoi64(strTemp.c_str()); }
	ULONG		GetAttrHexDWORD( const char *pSzAttrName );
	float		GetAttrFloat( const char *pSzAttrName )		{ string strTemp = GetAttr(pSzAttrName); return strTemp.empty() ? 0.0f : (float)atof(strTemp.c_str()); }
	bool		GetAttrBool( const char *pSzAttrName )		{ string strTemp = GetAttr(pSzAttrName); return stricmp( strTemp.c_str(), "TRUE" ) == 0; }
	bool		GetAttrBOOL( const char *pSzAttrName )		{ string strTemp = GetAttr(pSzAttrName); return ( stricmp( strTemp.c_str(), "TRUE" ) == 0 ) ? TRUE : FALSE; }

	bool		GetAttr( const char *pSzAttrName, string& strValue );
	bool		GetAttr( const char *pSzAttrName, wstring & wstrValue );
	bool		GetAttr_UTF8( const char *pSzAttrName, wstring & wstrValue );
	bool		GetAttrInt( const char *pSzAttrName, int &iValue )				{ string strTemp; if(!GetAttr(pSzAttrName, strTemp) || strTemp.empty()) return false; iValue = (int)atoi(strTemp.c_str()); return true; }
	bool		GetAttrUINT( const char *pSzAttrName, UINT & unValue )			{ string strTemp; if(!GetAttr(pSzAttrName, strTemp) || strTemp.empty()) return false; unValue = (UINT)atoi(strTemp.c_str()); return true; }
	bool		GetAttrUCHAR( const char *pSzAttrName, UINT8  & ucValue )		{ string strTemp; if(!GetAttr(pSzAttrName, strTemp) || strTemp.empty()) return false; ucValue = (UINT8)atoi(strTemp.c_str()); return true; }
	bool		GetAttrUSHORT( const char *pSzAttrName, UINT16  & usValue )		{ string strTemp; if(!GetAttr(pSzAttrName, strTemp) || strTemp.empty())	return false; usValue = (UINT16)atoi(strTemp.c_str()); return true; }
	bool		GetAttrDWORD( const char *pSzAttrName, ULONG &dwValue )			{ string strTemp; if(!GetAttr(pSzAttrName, strTemp) || strTemp.empty()) return false; dwValue = (ULONG)atoi(strTemp.c_str()); return true; }
	bool		GetAttrDWORD64( const char *pSzAttrName, UINT64 &ddwValue )		{ string strTemp; if(!GetAttr(pSzAttrName, strTemp) || strTemp.empty())	return false; ddwValue = (UINT64)_atoi64(strTemp.c_str()); return true; }
	bool		GetAttrINT64( const char *pSzAttrName, INT64 &ddwValue )		{ string strTemp; if(!GetAttr(pSzAttrName, strTemp) || strTemp.empty())	return false; ddwValue = (INT64)_atoi64(strTemp.c_str()); return true; }
	bool		GetAttrHexDWORD( const char *pSzAttrName, ULONG &dwValue );
	bool		GetAttrFloat( const char *pSzAttrName, float &fValue )			{ string strTemp; if(!GetAttr(pSzAttrName, strTemp) || strTemp.empty()) return false; fValue = (float)atof(strTemp.c_str()); return true; }
	bool		GetAttrDouble( const char *pSzAttrName, double &dValue )		{ string strTemp; if(!GetAttr(pSzAttrName, strTemp) || strTemp.empty()) return false; dValue = atof( strTemp.c_str()); return true; }
	bool		GetAttrBool( const char *pSzAttrName, bool &bValue )			{ string strTemp; if(!GetAttr(pSzAttrName, strTemp) || strTemp.empty()) return false; bValue = stricmp( strTemp.c_str(), "TRUE" ) == 0; return true; }
	bool		GetAttrBOOL( const char *pSzAttrName, bool &bValue )			{ string strTemp; if(!GetAttr(pSzAttrName, strTemp) || strTemp.empty()) return false; bValue = ( stricmp( strTemp.c_str(), "TRUE" ) == 0 ) ? TRUE : FALSE; return true; }

	string		GetChildAttr( const char * pszChildName, const char * pszAttrName )			{ XMLNode *pNode = GetChild(pszChildName); return pNode ? pNode->GetAttr(pszAttrName) : ""; }
	int			GetChildAttrInt( const char * pszChildName, const char * pszAttrName )		{ XMLNode *pNode = GetChild(pszChildName); return pNode ? pNode->GetAttrInt(pszAttrName) : 0; }
	UINT		GetChildAttrUINT( const char * pszChildName, const char * pszAttrName )		{ XMLNode *pNode = GetChild(pszChildName); return pNode ? pNode->GetAttrUINT(pszAttrName) : 0; }
	UINT8		GetChildAttrUCHAR( const char * pszChildName, const char * pszAttrName )	{ XMLNode *pNode = GetChild(pszChildName); return pNode ? pNode->GetAttrUCHAR( pszAttrName ) : 0; }
	ULONG		GetChildAttrDWORD( const char * pszChildName, const char * pszAttrName )	{ XMLNode *pNode = GetChild(pszChildName); return pNode ? pNode->GetAttrDWORD(pszAttrName) : 0; }
	UINT64		GetChildAttrDWORD64( const char * pszChildName, const char * pszAttrName )	{ XMLNode *pNode = GetChild(pszChildName); return pNode ? pNode->GetAttrDWORD64(pszAttrName) : 0; }
	ULONG		GetChildAttrHexDWORD( const char * pszChildName, const char * pszAttrName )	{ XMLNode *pNode = GetChild(pszChildName); return pNode ? pNode->GetAttrHexDWORD(pszAttrName) : 0; }
	float		GetChildAttrFloat( const char * pszChildName, const char * pszAttrName )	{ XMLNode *pNode = GetChild(pszChildName); return pNode ? pNode->GetAttrFloat(pszAttrName) : 0.0f; }
	bool		GetChildAttrBool( const char * pszChildName, const char * pszAttrName )		{ XMLNode *pNode = GetChild(pszChildName); return pNode ? pNode->GetAttrBool(pszAttrName) : false; }
	bool		GetChildAttrBOOL( const char * pszChildName, const char * pszAttrName )		{ XMLNode *pNode = GetChild(pszChildName); return pNode ? pNode->GetAttrBOOL(pszAttrName) : FALSE; }
	bool		GetChildBinary( const char *pszChildName, void *pData, int iSize );

	bool		GetChildAttrString( const char * pszChildName, const char * pszAttrName, string & strValue )	{ XMLNode *pNode = GetChild(pszChildName); return pNode ? pNode->GetAttr( pszAttrName, strValue ) : false; }
	bool		GetChildAttrWstring( const char * pszChildName, const char * pszAttrName, wstring & wstrValue );
	bool		GetChildAttrInt( const char * pszChildName, const char * pszAttrName, int &iValue )				{ XMLNode *pNode = GetChild(pszChildName); return pNode ? pNode->GetAttrInt(pszAttrName, iValue) : false; }
	bool		GetChildAttrUINT( const char * pszChildName, const char * pszAttrName, UINT& unValue )			{ XMLNode *pNode = GetChild(pszChildName); return pNode ? pNode->GetAttrUINT(pszAttrName, unValue) : false;	}
	bool		GetChildAttrUCHAR( const char * pszChildName, const char * pszAttrName, UINT8& ucValue	)		{ XMLNode *pNode = GetChild(pszChildName); return pNode ? pNode->GetAttrUCHAR(pszAttrName, ucValue) : false; }
	bool		GetChildAttrDWORD( const char * pszChildName, const char * pszAttrName, ULONG &dwValue )		{ XMLNode *pNode = GetChild(pszChildName); return pNode ? pNode->GetAttrDWORD(pszAttrName, dwValue) : false; }
	bool		GetChildAttrDWORD64( const char * pszChildName, const char * pszAttrName, UINT64 &ddwValue )	{ XMLNode *pNode = GetChild(pszChildName); return pNode ? pNode->GetAttrDWORD64(pszAttrName, ddwValue) : false;	}
	bool		GetChildAttrHexDWORD( const char * pszChildName, const char * pszAttrName, ULONG &dwValue )		{ XMLNode *pNode = GetChild(pszChildName); return pNode ? pNode->GetAttrHexDWORD(pszAttrName, dwValue) : false; }
	bool		GetChildAttrFloat( const char * pszChildName, const char * pszAttrName, float &fValue )			{ XMLNode *pNode = GetChild(pszChildName); return pNode ? pNode->GetAttrFloat(pszAttrName, fValue) : false; }
	bool		GetChildAttrDouble( const char * pszChildName, const char * pszAttrName, double &dValue )		{ XMLNode *pNode = GetChild(pszChildName); return pNode ? pNode->GetAttrDouble( pszAttrName, dValue ) : false; }
	bool		GetChildAttrBool( const char * pszChildName, const char * pszAttrName, bool &bValue )			{ XMLNode *pNode = GetChild(pszChildName); return pNode ? pNode->GetAttrBool(pszAttrName, bValue) : false; }
	bool		GetChildAttrBOOL( const char * pszChildName, const char * pszAttrName, bool &bValue )			{ XMLNode *pNode = GetChild(pszChildName); return pNode ? pNode->GetAttrBOOL(pszAttrName, bValue) : false; }

	bool		GetChildAttribute( const char * pszChildName, const char * pszAttrName, string & strValue )		{ return GetChildAttrString( pszChildName, pszAttrName, strValue ); }
	bool		GetChildAttribute( const char * pszChildName, const char * pszAttrName, wstring & wstrValue )	{ return GetChildAttrWstring( pszChildName, pszAttrName, wstrValue ); }
	bool		GetChildAttribute( const char * pszChildName, const char * pszAttrName, int & iValue )			{ return GetChildAttrInt( pszChildName, pszAttrName, iValue ); }
	bool		GetChildAttribute( const char * pszChildName, const char * pszAttrName, ULONG & dwValue )		{ return GetChildAttrDWORD( pszChildName, pszAttrName, dwValue ); }
	bool		GetChildAttribute( const char * pszChildName, const char * pszAttrName, UINT64 & ddwValue )		{ return GetChildAttrDWORD64( pszChildName, pszAttrName, ddwValue ); }
	bool		GetChildAttribute( const char * pszChildName, const char * pszAttrName, float & fValue )		{ return GetChildAttrFloat( pszChildName, pszAttrName, fValue ); }
	bool		GetChildAttribute( const char * pszChildName, const char * pszAttrName, double & dValue )		{ return GetChildAttrDouble( pszChildName, pszAttrName, dValue ); }
	bool		GetChildAttribute( const char * pszChildName, const char * pszAttrName, bool & bValue )			{ return GetChildAttrBool( pszChildName, pszAttrName, bValue ); }
	bool		GetChildAttribute( const char * pszChildName, const char * pszAttrName, UINT & unValue)			{ return GetChildAttrUINT( pszChildName, pszAttrName, unValue ); }

	void		GetChildAttrFloat2( const char * pszChildName, void * pData, int iCount );
	void		GetChildAttrFloat3( const char * pszChildName, void * pData );
	void		GetChildAttrFloat4( const char * pszChildName, void * pData );


	// 노드 추가
	XMLNode *	AddNode( const char * pSzNodeName );
	XMLNode *	AddNode( const wchar_t * pwszNodeName );
	XMLNode *	AddNodeFormat( const char * pSzFormat, ... );

	/////////////////////////////////////////////
	// 속성 추가
	void AddAttribute(const char *pSzAttrName, const char *pSzValue)				{ assert(pSzAttrName); ToElement()->SetAttribute( pSzAttrName, pSzValue ); }
	void AddAttribute(const char *pSzAttrName, const wchar_t *pwszValue)			{ assert(pSzAttrName); ToElement()->SetAttribute( pSzAttrName, UniToAnsi2( pwszValue ) ); }
	void AddAttribute(const char *pSzAttrName, const string & strValue)				{ assert(pSzAttrName); ToElement()->SetAttribute( pSzAttrName, strValue.c_str() ); }
	void AddAttribute(const char *pSzAttrName, const wstring & wstrValue)			{ assert(pSzAttrName); ToElement()->SetAttribute( pSzAttrName, UniToAnsi2( wstrValue.c_str() ) ); }
	void AddAttribute(const char *pSzAttrName, int iValue)							{ assert(pSzAttrName); ToElement()->SetAttribute( pSzAttrName, iValue ); }
	void AddAttribute(const char *pSzAttrName, ULONG dwValue)						{ assert(pSzAttrName); AddAttributeFormat( pSzAttrName, "%d", dwValue ); }
	void AddAttribute(const char *pSzAttrName, UINT64 dwValue)						{ assert(pSzAttrName); AddAttributeFormat( pSzAttrName, "%I64d", dwValue ); }
	void AddAttribute(const char *pSzAttrName, INT64 dwValue)						{ assert(pSzAttrName); AddAttributeFormat( pSzAttrName, "%I64d", dwValue ); }
	void AddAttribute(const char *pSzAttrName, float fValue)						{ assert(pSzAttrName); AddAttributeFormat( pSzAttrName, "%.6f", fValue ); }
	void AddAttribute(const char *pSzAttrName, double dDouble)						{ assert(pSzAttrName); AddAttributeFormat( pSzAttrName, "%.9f", dDouble ); }
	void AddAttribute(const char *pSzAttrName, UINT uiValue)						{ assert(pSzAttrName); AddAttributeFormat( pSzAttrName, "%u", uiValue ); }
	void AddAttribute(const char *pSzAttrName, bool bValue)							{ assert(pSzAttrName); ToElement()->SetAttribute( pSzAttrName, bValue ? "TRUE" : "FALSE" ); }
	void AddAttributeBOOL(const char *pSzAttrName, bool bValue)						{ assert(pSzAttrName); ToElement()->SetAttribute( pSzAttrName, bValue ? "TRUE" : "FALSE" ); }	
	void AddAttributeFormat(const char * pSzAttrName, const char *pSzFormat, ...);
	void AddAttributeFloat2(const void * pData , int iCount);
	void AddAttributeFloat3(const void * pData);
	void AddAttributeText(const char *pSzFormat, ...);
	void AddAttributeHexDword( const char *pSzAttrName, ULONG dwValue);

	/////////////////////////////////////////////
	// 노드 속성 추가
	XMLNode* AddNodeAttribute(const char *pSzNodeName, const char *pSzAttrName, const char *pSzValue)		{ XMLNode *pNode = AddNode(pSzNodeName); pNode->AddAttribute(pSzAttrName, pSzValue); return pNode; }
	XMLNode* AddNodeAttribute(const char *pSzNodeName, const char *pSzAttrName, const string & strValue)	{ XMLNode* pNode = AddNode(pSzNodeName); pNode->AddAttribute(pSzAttrName, strValue); return pNode; }
	XMLNode* AddNodeAttribute(const char *pSzNodeName, const char *pSzAttrName, const wchar_t * pwszValue)	{ XMLNode* pNode = AddNode(pSzNodeName); pNode->AddAttribute(pSzAttrName, pwszValue); return pNode; }
	XMLNode* AddNodeAttribute(const char *pSzNodeName, const char *pSzAttrName, const wstring & wstrValue)	{ XMLNode* pNode = AddNode(pSzNodeName); pNode->AddAttribute(pSzAttrName, wstrValue); return pNode; }
	XMLNode* AddNodeAttribute(const char *pSzNodeName, const char *pSzAttrName, const int iValue)			{ XMLNode *pNode = AddNode(pSzNodeName); pNode->AddAttribute(pSzAttrName, iValue); return pNode; }
	XMLNode* AddNodeAttribute(const char *pSzNodeName, const char *pSzAttrName, const ULONG dwValue)		{ XMLNode *pNode = AddNode(pSzNodeName); pNode->AddAttribute(pSzAttrName, dwValue); return pNode; }
	XMLNode* AddNodeAttribute(const char *pSzNodeName, const char *pSzAttrName, const UINT64 dwValue)		{ XMLNode *pNode = AddNode(pSzNodeName); pNode->AddAttribute(pSzAttrName, dwValue); return pNode; }
	XMLNode* AddNodeAttribute(const char *pSzNodeName, const char *pSzAttrName, const float fValue)			{ XMLNode *pNode = AddNode(pSzNodeName); pNode->AddAttribute(pSzAttrName, fValue); return pNode; }
	XMLNode* AddNodeAttribute(const char *pSzNodeName, const char *pSzAttrName, const double dValue)		{ XMLNode *pNode = AddNode(pSzNodeName); pNode->AddAttribute(pSzAttrName, dValue); return pNode; }
	XMLNode* AddNodeAttribute(const char *pSzNodeName, const char *pSzAttrName, const UINT uiValue)			{ XMLNode *pNode = AddNode(pSzNodeName); pNode->AddAttribute(pSzAttrName, uiValue); return pNode; }
	XMLNode* AddNodeAttribute(const char *pSzNodeName, const char *pSzAttrName, const bool bValue)			{ XMLNode *pNode = AddNode(pSzNodeName); pNode->AddAttribute(pSzAttrName, bValue); return pNode; }
	XMLNode* AddNodeAttributeBOOL(const char *pSzNodeName, const char *pSzAttrName, const bool bValue)		{ XMLNode *pNode = AddNode(pSzNodeName); pNode->AddAttributeBOOL(pSzAttrName, bValue); return pNode; }
	XMLNode* AddNodeAttributeFloat2(const char *pSzNodeName, const void *pData , int iCount)				{ XMLNode *pNode = AddNode(pSzNodeName); pNode->AddAttributeFloat2(pData, iCount); return pNode; }
	XMLNode* AddNodeAttributeFloat3(const char *pSzNodeName, const void *pData)								{ XMLNode *pNode = AddNode(pSzNodeName); pNode->AddAttributeFloat3(pData); return pNode; }
	XMLNode* AddNodeAttributeHexDword(const char *pSzNodeName, const char *pSzAttrName, ULONG dwValue);
	XMLNode* AddNodeBinary(const char *pSzNodeName, void *buff, int size);	 ///< Based64형 텍스트 추가


	//////////////////////////////////////////////////////////////////////////
	// 노드 출력
	void PrintXML( string& strXML );

	inline char* GetToken( string& strOri , int nToken , char* strSep = NULL );
};


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
inline ULONG RXMLNode::GetAttrHexDWORD( const char *pSzAttrName )
{
	string strTemp = GetAttr(pSzAttrName);
	if (strTemp.length() > 0)
	{
		if( GetToken( strTemp , 0 ) != "decimal" )
		{
			ULONG dwValue = 0;
			sscanf( strTemp.c_str(), "%x", &dwValue );
			return dwValue;
		}
		else
		{
			ULONG dwValue = 0;
			int nAlpha = 255;
			int nRed = atoi( GetToken( strTemp , 1 ) );
			int nGreen = atoi( GetToken( strTemp , 2 ) );
			int nBlue = atoi( GetToken( strTemp , 3 ) );

			dwValue = (((nAlpha&0xff)<<24)|((nRed&0xff)<<16)|((nGreen&0xff)<<8)|(nBlue&0xff));
			return dwValue;
		}
	}

	return ULONG_MAX;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
inline bool RXMLNode::GetAttrHexDWORD( const char *pSzAttrName, ULONG &dwValue )
{
	string strTemp;
	if ( GetAttr(pSzAttrName, strTemp) == false || strTemp.empty() )
		return false;

	if( GetToken( strTemp , 0 ) != "decimal" )
	{
		sscanf( strTemp.c_str(), "%x", &dwValue );
	}
	else
	{
		int nAlpha = 255;//strTemp.GetToken( 1 ).A2I();
		int nRed = atoi( GetToken( strTemp , 1 ) );
		int nGreen = atoi( GetToken( strTemp , 2 ) );
		int nBlue = atoi( GetToken( strTemp , 3 ) );

		dwValue = (((nAlpha&0xff)<<24)|((nRed&0xff)<<16)|((nGreen&0xff)<<8)|(nBlue&0xff));
	}

	return true;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 저장 관련
inline XMLNode* XMLNode::AddNodeAttributeHexDword(const char *pSzNodeName, const char *pSzAttrName, ULONG dwValue)
{
	XMLNode *pNode = AddNode(pSzNodeName);

	char szBuffer[256];
	sprintf_s( szBuffer , 256 , "%x" , dwValue );
	pNode->AddAttribute( pSzAttrName, szBuffer );
	return pNode;
}


inline char* XMLNode::GetToken( string& strOri , int nToken , char* strSep )
{
	if( strSep == NULL )
	{
		strSep = " ,\t\n/";
	}

	char* pStrTemp = ( char* )( _alloca( ( strOri.length() + 1 ) * sizeof( char ) ) );
	strcpy( pStrTemp , strOri.c_str() );

	char* pTemp = ( char* )( _alloca( ( strOri.length() + 1 ) * sizeof( char ) ) );
	char* pToken;

	strcpy( pTemp , strOri.c_str() );

	char*  pNextToken = NULL;
	pToken = strtok_s( pTemp , strSep , &pNextToken );

	for( int cToken = 0; cToken < nToken; cToken++ )
	{
		pToken = strtok_s( NULL , strSep , &pNextToken );
		if( pToken == NULL )
		{
			return "";
		}
	}
	if( pToken == NULL )
		return "";

	return pToken;
}
//--------------------------------------------------------------------------------------------------
#pragma warning (default : 4996)
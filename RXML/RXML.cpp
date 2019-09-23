#include "stdafx.h"
#include "RXML.h"
#include "../Base/Encrypt.h"
// #include "../C9Base/C9Error.h"

//----------------------------------------------------------------------------------------------
struct SXmlFloat2
{
	float x;
	float y;
};
struct SXmlFloat3
{
	float x;
	float y;
	float z;
};
struct SXmlFloat4
{
	float r;
	float g;
	float b;
	float a;
};
	
#define	 BOOLVALUE_TO_STRING(b) (b) ? "TRUE" : "FALSE"
#define	 BOOLSTRING_TO_VALUE(b) (strcmp(b, "TRUE")) ? 0 : 1

//----------------------------------------------------------------------------------------------
RXML::RXML(void)
{
	m_pXMLDocument = new TiXmlDocument;
}

RXML::~RXML(void)
{
	Close();
	RSAFE_DELETE(m_pXMLDocument);
}

bool RXML::Load( const char * pszFilename, bool bErrorMsgBox )
{
	if( m_pXMLDocument->LoadFile( pszFilename ) == false )
	{
		wchar_t strError[256];
		wsprintf( strError, L"XML Load Error = %s : %s \n Line = %d", pszFilename, m_pXMLDocument->ErrorDesc(), m_pXMLDocument->ErrorRow() );		
		if (bErrorMsgBox)
			MessageBox( NULL, strError, L"Load XML Error", 0 );
		return false;
	}	
	return true;
}

//-----------------------------------------------------------------------------
bool RXML::Save(const char* pSzFileName)	
{	
	assert(pSzFileName);

	return m_pXMLDocument->SaveFile(pSzFileName);	
}

//-----------------------------------------------------------------------------
XMLNode * RXML::CreateRootNode(const char *pSzRootName)
{
	assert(pSzRootName);

	TiXmlNode *pChildNode;
	pChildNode = m_pXMLDocument->InsertEndChild(TiXmlElement(pSzRootName));

	return (XMLNode*)pChildNode;
}

XMLNode * RXML::CreateRootCommentNode(const char *pSzRootName)
{
	assert(pSzRootName);

	TiXmlNode *pChildNode;
	pChildNode = m_pXMLDocument->InsertEndChild(TiXmlComment(pSzRootName));

	return (XMLNode*)pChildNode;
}


//---------------------------------------------------------------------------------
bool RXML::LoadBuffer( const char *pBuffer, bool bErrorMsgBox )
{	
	m_pXMLDocument->Parse( pBuffer );

	if( m_pXMLDocument->Error() )
	{		
		m_pXMLDocument->Parse( pBuffer );
		if( m_pXMLDocument->Error() )
		{
			wchar_t strError[256];
			wsprintf( strError , L"XML Load Error = %s \n Line = %d", m_pXMLDocument->ErrorDesc(), m_pXMLDocument->ErrorRow() );
			if (bErrorMsgBox)
				MessageBox( NULL, strError, L"Load XML Error", 0 );
			return false;
		}
	}	
	return true;
}

XMLNodes RXML::GetChilds( const char * pszChildName )
{
	XMLNodes lstChildNode;

	TiXmlNode *pChildNode;
	
	pChildNode = m_pXMLDocument->FirstChild()->FirstChild( pszChildName );	
	
	for( ; pChildNode; pChildNode = pChildNode->NextSibling( pszChildName ) )
	{
		lstChildNode.push_back( ( XMLNode*) pChildNode );
	}

	return lstChildNode;
}

XMLNode* RXML::GetChild( const char * pszChildName )
{
	TiXmlNode *pChildNode;
	pChildNode = m_pXMLDocument->FirstChild()->FirstChild( pszChildName );		

	return (XMLNode*)pChildNode;
}

XMLNode *RXML::GetRootChild( const char * pszChildName )
{
	TiXmlNode *pChildNode;
	pChildNode = m_pXMLDocument->FirstChild( pszChildName );		

	return (XMLNode*)pChildNode;
}

XMLNodes RXML::GetRootChilds( const char * pszChildName )
{
	XMLNodes lstChildNode;
	TiXmlNode * pChildNode = m_pXMLDocument->FirstChild( pszChildName );
	for( ; pChildNode; pChildNode = pChildNode->NextSibling( pszChildName ) )
		lstChildNode.push_back( (XMLNode*)pChildNode );

	return lstChildNode;
}


///////////////////////////////////////////////////////////////////////////////////////////////

//----------------------------------------------------------------------------------------------

RXMLNode::RXMLNode(void)
{

}

RXMLNode::~RXMLNode(void)
{

}

XMLNodes RXMLNode::GetChilds( const char * pszChildName )
{
	XMLNodes lstChildNode;

	TiXmlNode *pChildNode;
	
	pChildNode = FirstChild( pszChildName );	
	
	for( ; pChildNode; pChildNode = pChildNode->NextSibling( pszChildName ) )
		lstChildNode.push_back( (XMLNode*)pChildNode );

	return lstChildNode;
}

XMLNodes RXMLNode::GetChilds()
{
	XMLNodes lstChildNode;

	TiXmlNode *pChildNode;
	
	pChildNode = FirstChild();	
	
	for( ; pChildNode; pChildNode = pChildNode->NextSibling() )
	{
		lstChildNode.push_back( (XMLNode*)pChildNode );
	}

	return lstChildNode;
}

//-----------------------------------------------------------------------------
XMLNode* RXMLNode::GetChildFormat(const char *pSzFormat, ...)
{
	assert(pSzFormat);

	char *pSzBuf;
	GetStrFormat(pSzBuf, pSzFormat);

	return GetChild( pSzBuf );
}

string RXMLNode::GetAttr( const char * pszAttrName )
{
	TiXmlElement* pElement = ToElement();
	const char* pAttr = pElement->Attribute( pszAttrName );
	return pAttr ? pAttr : "";
}


//--------------------------------------------------------------------------------------------------
bool	RXMLNode::GetAttr( const char *pSzAttrName, string & strValue )
{
	TiXmlElement* pElement = NULL;
	pElement = ToElement();
	const char *pAttr = pElement->Attribute( pSzAttrName );
	if( pAttr )
	{
		strValue = pAttr;
		return true;
	}

	return false;
}

//--------------------------------------------------------------------------------------------------
bool	RXMLNode::GetAttr( const char *pSzAttrName, wstring & wstrValue )
{
	string strTemp;
	if( !GetAttr( pSzAttrName, strTemp ) )
		return false;

	wstrValue = AnsiToUni2( strTemp.c_str() );
	return true;
}


bool RXMLNode::GetAttr_UTF8(const char *pSzAttrName, wstring & wstrValue)
{
	string strTemp;
	if( !GetAttr( pSzAttrName, strTemp ) )
		return false;

	wstrValue = UTF8ToUni2( strTemp.c_str() );
	return true;
}

//--------------------------------------------------------------------------------------------------
string RXMLNode::Value()
{
	TiXmlNode *pChildNode;
	pChildNode = FirstChild();
	if (pChildNode)
		return pChildNode->Value();
	return "";
}

void RXMLNode::SetValue(const char * _value)
{
	TiXmlNode *pChildNode;
	pChildNode = FirstChild();
	if (pChildNode && pChildNode->Type() == NodeType::TEXT)
		pChildNode->SetValue(_value);
	else
	{
		assert(_value);
		if(pChildNode)
		{
			( XMLNode * )InsertBeforeChild( pChildNode, TiXmlText( _value ) );
		}
		else
		{
			( XMLNode * )InsertEndChild( TiXmlText( _value ) );
		}
	}
}

//--------------------------------------------------------------------------------------------------
bool RXMLNode::GetChildAttrWstring( const char * pszChildName, const char * pszAttrName, wstring & wstrValue )
{
	XMLNode *pNode = GetChild(pszChildName);
	if (pNode)
	{
		string strTemp;
		bool bSucceeded = pNode->GetAttr( pszAttrName, strTemp );
		wstrValue = AnsiToUni2( strTemp.c_str() );		
		return bSucceeded;
	}

	return false;
}

bool RXMLNode::GetChildBinary( const char *pszChildName, void *pData, int iSize )
{
	XMLNode *pNode = GetChild(pszChildName);
	if ( pNode == NULL )
		return false;

	if ( pNode->GetAttr( "binary") != "True" )
		return false;

	//사이즈가 다르면 그냥 리턴
	if( pNode->GetAttrInt( "length" ) != iSize )
	{
		return false;
	}

	string strTemp = pNode->Value();

	string buffer;
	CEncrypt encrypt;
	encrypt.Decode( strTemp.c_str() , strTemp.length() , buffer );
	memcpy( pData, &buffer[0] , iSize );
	return true;
}


void RXMLNode::GetChildAttrFloat2( const char * pszChildName, void * pData, int iCount )
{
	assert(pData);

	char szBuffer[256];
	SXmlFloat2 *pFloat2 = static_cast<SXmlFloat2 *>(pData);
	for (int i=0; i<iCount; i++)
	{
		sprintf_s(szBuffer, 256, "x%d", i);
		GetChildAttrFloat( pszChildName, szBuffer, pFloat2[i].x );
		sprintf_s(szBuffer, 256, "y%d", i);
		GetChildAttrFloat( pszChildName, szBuffer, pFloat2[i].y );
	}
}

void RXMLNode::GetChildAttrFloat3( const char * pszChildName, void *pData )
{
	assert(pData);

	SXmlFloat3 *pFloat3 = static_cast<SXmlFloat3 *>(pData);
	GetChildAttrFloat( pszChildName, "x", pFloat3->x );
	GetChildAttrFloat( pszChildName, "y", pFloat3->y );
	GetChildAttrFloat( pszChildName, "z", pFloat3->z );
}

void RXMLNode::GetChildAttrFloat4( const char * pszChildName, void *pData )
{
	assert(pData);
	
	SXmlFloat4 *pFloat4 = static_cast<SXmlFloat4 *>(pData);
	GetChildAttrFloat( pszChildName, "r", pFloat4->r );
	GetChildAttrFloat( pszChildName, "g", pFloat4->g );
	GetChildAttrFloat( pszChildName, "b", pFloat4->b );
	GetChildAttrFloat( pszChildName, "a", pFloat4->a );
}

//-------------------------------------------------------------------------------
RXMLNode* RXMLNode::AddNode(const char *pSzNodeName)
{
	assert(pSzNodeName);
	return ( XMLNode * )InsertEndChild( TiXmlElement( pSzNodeName ) );
}

XMLNode *	RXMLNode::AddNode( const wchar_t * pwszNodeName )
{
	assert( pwszNodeName );
	return ( XMLNode * )InsertEndChild( TiXmlElement( UniToAnsi2( pwszNodeName ) ) );
}

//-----------------------------------------------------------------------------
RXMLNode* RXMLNode::AddNodeFormat(const char *pSzFormat, ...)
{
	assert(pSzFormat);

	char *pSzBuf;
	GetStrFormat(pSzBuf, pSzFormat);

	TiXmlNode *pChildNode;
	pChildNode = InsertEndChild(TiXmlElement(pSzBuf));
	return (XMLNode*)pChildNode;
}

//-----------------------------------------------------------------------------
void RXMLNode::AddAttributeFormat(const char *pSzAttrName, const char *pSzFormat, ...)
{
	assert(pSzAttrName);
	assert(pSzFormat);

	char *pSzBuf;
	GetStrFormat(pSzBuf, pSzFormat);
	ToElement()->SetAttribute(pSzAttrName, pSzBuf);
}

//-----------------------------------------------------------------------------
void RXMLNode::AddAttributeFloat2(const void * pData , int iCount)
{
	assert(pData);

	char szBuffer[256];
	const SXmlFloat2 *pFloat2 = static_cast<const SXmlFloat2 *>(pData);
	for (int i=0; i<iCount; i++)
	{
		sprintf_s(szBuffer, 256, "x%d", i);
		AddAttributeFormat(szBuffer, "%.9f", pFloat2[i].x);
		sprintf_s(szBuffer, 256, "y%d", i);
		AddAttributeFormat(szBuffer, "%.9f", pFloat2[i].y);
	}
}

//-----------------------------------------------------------------------------
void RXMLNode::AddAttributeFloat3(const void * pData)
{
	assert(pData);

	const SXmlFloat3 *pFloat3 = static_cast<const SXmlFloat3 *>(pData);
	AddAttributeFormat("x", "%.9f", pFloat3->x);
	AddAttributeFormat("y", "%.9f", pFloat3->y);
	AddAttributeFormat("z", "%.9f", pFloat3->z);
}

//-----------------------------------------------------------------------------
void RXMLNode::AddAttributeText(const char *pSzFormat, ...)
{
	assert(pSzFormat);

	char *pSzBuf;
	GetStrFormat(pSzBuf, pSzFormat);
	InsertEndChild(TiXmlText(pSzBuf));
}

//-----------------------------------------------------------------------------
void RXMLNode::AddAttributeHexDword( const char *pSzAttrName, ULONG dwValue)
{
	char szBuffer[256];
	sprintf_s(szBuffer, 256, "%x", dwValue);
	AddAttribute( pSzAttrName, szBuffer );
}

XMLNode* RXMLNode::AddNodeBinary(const char *pSzNodeName, void *buff, int size)
{
	XMLNode *pNode = AddNode(pSzNodeName);
	pNode->AddAttribute("binary", "True");
	pNode->AddAttribute("length", size);

	CEncrypt encrypt;
	string buf;

	if ( encrypt.Encode( buff , size , buf ) )
		pNode->InsertEndChild( TiXmlText((char*)&buf[0]) );

	return pNode;
}

//-----------------------------------------------------------------------------
void RXMLNode::RemoveAttr( const char * pszAttrName )
{
	TiXmlElement* pElement = NULL;
	pElement = ToElement();	
	pElement->RemoveAttribute( pszAttrName );
}

void RXMLNode::SetAttrFloat( const char *pSzAttrName, float &fValue )
{
	assert( pSzAttrName );

	RemoveAttr( pSzAttrName );

	AddAttributeFormat( pSzAttrName, "%f", fValue );
}

void RXMLNode::SetAttrDWORD( const char *pSzAttrName, ULONG &dwValue )
{
	assert( pSzAttrName );

	RemoveAttr( pSzAttrName );

	AddAttributeFormat( pSzAttrName, "%x", dwValue );
}

//////////////////////////////////////////////////////////////////////////
void RXMLNode::PrintXML( string& strXML )
{
	TiXmlPrinter printer;
	printer.SetIndent( "\r\n" );

	Accept( &printer );

	strXML = printer.CStr();
}
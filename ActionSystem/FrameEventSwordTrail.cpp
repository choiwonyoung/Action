#include "stdafx.h"
#include "FrameEventSwordTrail.h"


bool CFrameEventSwordTrail::LoadXML( XMLNode *pXMLNode , List_PreloadString &lstPreloadEffect , List_PreloadString &lstPreloadSound , const char * pszClassName /*= NULL */ )
{
	if( !CFrameEvent::LoadXML( pXMLNode , lstPreloadEffect , lstPreloadSound , pszClassName ? pszClassName : "C9FrameEventSwordTrail" ) )
		return false;

	string strAttr;

	if( pXMLNode->GetAttrInt( "Index" , m_nIndex ) == false )
	{
		char strError[256];
		sprintf_s( strError , 256 , "Index값이 없습니다.(SwordTrail)\n" );
		MessageBoxA( NULL , strError , "Error" , MB_OK );
		return false;
	}

	pXMLNode->GetAttr( "BoneName" , m_strBoneName );

	if( pXMLNode->GetAttrInt( "EndFrame" , m_nEndFrame ) == false )
	{
		char strError[256];
		sprintf_s( strError , 256 , "EndFrame값이 없습니다.(SwordTrail)\n" );
		MessageBoxA( NULL , strError , "Error" , MB_OK );
		return false;
	}

	if( pXMLNode->GetAttrFloat( "StartPos" , m_fStartPos ) == false )
	{
		char strError[256];
		sprintf_s( strError , 256 , "StartPos값이 없습니다.(SwordTrail)\n" );
		MessageBoxA( NULL , strError , "Error" , MB_OK );
		return false;
	}
	if( pXMLNode->GetAttrFloat( "EndPos" , m_fEndPos ) == false )
	{
		char strError[256];
		sprintf_s( strError , 256 , "EndPos값이 없습니다.(SwordTrail)\n" );
		MessageBoxA( NULL , strError , "Error" , MB_OK );
		return false;
	}
	if( pXMLNode->GetAttrHexDWORD( "Color" , m_Color ) == false )
	{
		char strError[256];
		sprintf_s( strError , 256 , "Color값이 없습니다.(SwordTrail)\n" );
		MessageBoxA( NULL , strError , "Error" , MB_OK );
		return false;
	}
	if( pXMLNode->GetAttrInt( "LifeTime" , m_nLifeTime ) == false )
	{
		char strError[256];
		sprintf_s( strError , 256 , "LifeTime값이 없습니다.(SwordTrail)\n" );
		MessageBoxA( NULL , strError , "Error" , MB_OK );
		return false;
	}

	pXMLNode->GetAttrFloat( "HalfFrame" , m_fHalfFrame );

	if( pXMLNode->GetAttr( "Scale" , strAttr ) )
		sscanf( strAttr.c_str() , "%f %f %f" , &m_vecScale.x , &m_vecScale.y , &m_vecScale.z );

	if( pXMLNode->GetAttr( "Axis" , strAttr ) )
		sscanf( strAttr.c_str() , "%f %f %f" , &m_vecAxis.x , &m_vecAxis.y , &m_vecAxis.z );

	pXMLNode->GetAttrInt( "FadeOutTime" , m_nFadeOutTime );
	pXMLNode->GetAttrBool( "FadeOut" , m_bFadeOut );
	pXMLNode->GetAttrBool( "GlareEffect" , m_bGlareEffect );
	pXMLNode->GetAttrBool( "Attach" , m_bUseLocalTrail );
	pXMLNode->GetAttrBool( "InvertColor" , m_bInvertColor );

	return true;
}

void CFrameEventSwordTrail::Dump( C9File * pFile , List_PreloadString & lstPreloadEffect , List_PreloadString &lstPreloadSound )
{
	CFrameEvent::Dump( pFile , lstPreloadEffect , lstPreloadSound );

	static const size_t _sizeOfData = C9_SIZE_OF_BETWEEN_VALUE( m_nEndFrame , m_bInvertColor );

	if( pFile->IsSave() )
	{
		pFile->WriteData( m_strBoneName );

		pFile->WriteData_SizeT( &m_nEndFrame , _sizeOfData );
	}
	else
	{
		pFile->ReadData( m_strBoneName );

		pFile->ReadData_SizeT( &m_nEndFrame , _sizeOfData );
	}
}

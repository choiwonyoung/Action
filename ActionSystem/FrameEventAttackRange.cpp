#include "stdafx.h"
#include "FrameEventAttackRange.h"



bool CFrameEventAttackRange::LoadXML( XMLNode *pXMLNode , List_PreloadString &lstPreloadEffect , List_PreloadString &lstPreloadSound , const char * pszClassName /*= NULL */ )
{
	if( CFrameEventAttackNormal::LoadXML( pXMLNode , lstPreloadEffect , lstPreloadSound , pszClassName ? pszClassName : "C9FrameEventAttackRange" ) == false )
		return false;

	if( pXMLNode->GetAttrInt( "EndFrame" , m_nEndFrame ) == false )
	{
		char strError[256];
		sprintf_s( strError , 256 , "EndFrame값이 없습니다.(C9FrameEventAttackRange)\n" );
		MessageBoxA( NULL , strError , "Error" , MB_OK );
		return false;
	}

	return true;
}

void CFrameEventAttackRange::Dump( C9File * pFile , List_PreloadString & lstPreloadEffect , List_PreloadString &lstPreloadSound )
{
	CFrameEventAttackNormal::Dump( pFile , lstPreloadEffect , lstPreloadSound );

	if( pFile->IsSave() )
	{
		pFile->WriteData( m_nEndFrame );
	}
	else
	{
		pFile->ReadData( m_nEndFrame );
	}
}

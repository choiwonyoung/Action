#include "stdafx.h"
#include "FrameEventCameraShake.h"


//////////////////////////////////////////////////////////////////////////
//
bool CFrameEventCameraShake::LoadXML( XMLNode *pXMLNode , List_PreloadString &lstPreloadEffect , List_PreloadString &lstPreloadSound , const char * pszClassName /*= NULL */ )
{
	if( !CFrameEvent::LoadXML( pXMLNode , lstPreloadEffect , lstPreloadSound , pszClassName ? pszClassName : "C9FrameEventCameraShake" ) )
		return false;

	string strError;

	if( pXMLNode->GetAttrFloat( "ShakeTime" , m_fTime ) == false && pszClassName == NULL )
	{
		char strError[256];
		sprintf_s( strError , 256 , "ShakeTime 값이 없습니다. (C9FrameEventCameraShake)\n" );
		MessageBoxA( NULL , strError , "Error" , MB_OK );
		return false;
	}
	m_fTime *= 0.001f;

	if( pXMLNode->GetAttrFloat( "ShakeScale" , m_fScale ) == false && pszClassName == NULL )
	{
		char strError[256];
		sprintf_s( strError , 256 , "ShakeScale 값이 없습니다. (C9FrameEventCameraShake)\n" );
		MessageBoxA( NULL , strError , "Error" , MB_OK );
		return false;
	}

	pXMLNode->GetAttrFloat( "ShakeRadius" , m_fRadius );
	pXMLNode->GetAttrBool( "DistanceAttenuation" , m_bDistanceAttenuation );
	pXMLNode->GetAttrBool( "TimeAttenuation" , m_bTimeAttenuation );
	pXMLNode->GetAttrBool( "ShakeSure" , m_bSure );

	return true;
}

void CFrameEventCameraShake::Dump( C9File * pFile , List_PreloadString & lstPreloadEffect , List_PreloadString &lstPreloadSound )
{
	CFrameEvent::Dump( pFile , lstPreloadEffect , lstPreloadSound );

	static const size_t _sizeOfData = C9_SIZE_OF_BETWEEN_VALUE( m_fTime , m_bSure );

	if( pFile->IsSave() )
	{
		pFile->WriteData_SizeT( &m_fTime , _sizeOfData );
	}
	else
	{
		pFile->ReadData_SizeT( &m_fTime , _sizeOfData );
	}
}
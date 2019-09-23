#include "stdafx.h"
#include "FrameEventEffect.h"

bool CFrameEventEffect::LoadXML( XMLNode *pXMLNode , List_PreloadString &lstPreloadEffect , List_PreloadString &lstPreloadSound , const char * pszClassName /*= NULL */ )
{
	if( !CFrameEvent::LoadXML( pXMLNode , lstPreloadEffect , lstPreloadSound , pszClassName ? pszClassName : "C9FrameEventEffect" ) )
		return false;

	if( pXMLNode->GetAttr( "EffectFile" , m_strEffectFile ) == false )
	{
		char strError[256];
		sprintf_s( strError , 256 , "EffectFile값이 없습니다.(Effect)\n" );
		MessageBoxA( NULL , strError , "Error" , MB_OK );
		return false;
	}
	lstPreloadEffect.AddStringLower( m_strEffectFile.c_str() );

	pXMLNode->GetAttrBool( "Attach" , m_bAttachCharacter );
	pXMLNode->GetAttr( "Bone" , m_strBone );
	sscanf( pXMLNode->GetAttr( "Scale" ).c_str() , "%f %f %f" , &m_vecScale.x , &m_vecScale.y , &m_vecScale.z );
	sscanf( pXMLNode->GetAttr( "LocalPosition" ).c_str() , "%f %f %f" , &m_vecLocalPos.x , &m_vecLocalPos.y , &m_vecLocalPos.z );
	sscanf( pXMLNode->GetAttr( "Rotation" ).c_str() , "%f %f %f" , &m_vecRotation.x , &m_vecRotation.y , &m_vecRotation.z );
	XMVECTOR tmpVec = XMLoadFloat3( &m_vecRotation );
	float degree = Action::RMATH_DEG2RAD;
	tmpVec = tmpVec * degree;
	XMStoreFloat3( &m_vecRotation , tmpVec );

	pXMLNode->GetAttrInt( "Index" , m_iIndex );
	pXMLNode->GetAttrBool( "CharAniSpeed" , m_bCharAniSpeed );
	pXMLNode->GetAttrBool( "DistCheck" , m_bDistCheck );
	pXMLNode->GetAttrBool( "ApplyScale" , m_bApplyScale );
	pXMLNode->GetAttrBool( "ApplyScalePos" , m_bApplyScalePos );

	return true;
}

void CFrameEventEffect::Dump( C9File * pFile , List_PreloadString & lstPreloadEffect , List_PreloadString &lstPreloadSound )
{
	CFrameEvent::Dump( pFile , lstPreloadEffect , lstPreloadSound );

	static const size_t _sizeOfData = C9_SIZE_OF_BETWEEN_VALUE( m_vecScale , m_bDistCheck );

	if( pFile->IsSave() )
	{
		pFile->WriteData( m_strEffectFile );
		pFile->WriteData( m_strBone );

		pFile->WriteData_SizeT( &m_vecScale , _sizeOfData );
	}
	else
	{
		pFile->ReadData( m_strEffectFile );
		pFile->ReadData( m_strBone );

		pFile->ReadData_SizeT( &m_vecScale , _sizeOfData );


		lstPreloadEffect.AddStringLower( m_strEffectFile.c_str() );
	}
}

void CFrameEventEffect::LoadXMLCopyActionValue( XMLNode *pXMLNode )
{
#ifndef _GAME_RELEASE_

	if( m_iCopyCount > 1 )
	{
		sscanf( pXMLNode->GetAttr( "CopyAddScale" ).c_str() , "%f %f %f" , &m_CopyActionValue.m_vecScale.x , &m_CopyActionValue.m_vecScale.y , &m_CopyActionValue.m_vecScale.z );
	}
#endif
}

void CFrameEventEffect::CopyActionValue( CFrameEvent *pFrameEvent , int iLevel )
{
#ifndef _GAME_RELEASE_

	__super::CopyActionValue( pFrameEvent , iLevel );
	CFrameEventEffect *pCopyFrame = ( CFrameEventEffect * )pFrameEvent;

	if( m_iCopyCount > 1 && iLevel > 0 )
	{
		m_vecScale.x += ( m_CopyActionValue.m_vecScale.x * ( float )iLevel );
		m_vecScale.y += ( m_CopyActionValue.m_vecScale.y * ( float )iLevel );
		m_vecScale.z += ( m_CopyActionValue.m_vecScale.z * ( float )iLevel );
	}
#endif
}

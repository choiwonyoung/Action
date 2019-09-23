#include "stdafx.h"
#include "FrameEventSound.h"



bool CFrameEventSound::LoadXML( XMLNode *pXMLNode , List_PreloadString &lstPreloadEffect , List_PreloadString &lstPreloadSound , const char * pszClassName /*= NULL */ )
{
	if( !CFrameEvent::LoadXML( pXMLNode , lstPreloadEffect , lstPreloadSound , pszClassName ? pszClassName : "C9FrameEventSound" ) )
		return false;

	string strTemp;

	pXMLNode->GetAttr( "SoundFile" , strTemp );
	if( strTemp.empty() == false )
		m_lstSoundFile.push_back( strTemp );

	XMLNodes soundFileNodes = pXMLNode->GetChilds( "SoundFile" );
	for( UINT cSoundFile = 0; cSoundFile < soundFileNodes.size(); ++cSoundFile )
	{
		soundFileNodes[cSoundFile]->GetAttr( "value" , strTemp );
		if( strTemp.empty() == false )
		{
			m_lstSoundFile.push_back( strTemp );
			lstPreloadSound.AddStringLower( strTemp.c_str() );
		}
	}

	if( m_lstSoundFile.empty() )
	{
		char strError[256];
		sprintf_s( strError , 256 , "등록된 SoundFile 이 없습니다. 최소 하나의 사운드는 등록 되어야 합니다.(Sound)\n" );
		MessageBoxA( NULL , strError , "Error" , MB_OK );

		return false;
	}

	pXMLNode->GetAttrFloat( "Volume" , m_fVolume );
	pXMLNode->GetAttrBool( "Attach" , m_bAttachBone );
	pXMLNode->GetAttr( "BoneName" , m_strBoneName );
	pXMLNode->GetAttrInt( "LoopNum" , m_iLoopNum );		if( m_iLoopNum < 0 ) m_iLoopNum = 0;
	pXMLNode->GetAttrFloat( "MinDistance" , m_fMinDistance );
	pXMLNode->GetAttrFloat( "MaxDistance" , m_fMaxDistance );
	pXMLNode->GetAttrBool( "2D" , m_bIs2DSound );

	return true;
}

void CFrameEventSound::Dump( C9File * pFile , List_PreloadString & lstPreloadEffect , List_PreloadString &lstPreloadSound )
{
	CFrameEvent::Dump( pFile , lstPreloadEffect , lstPreloadSound );

	static const size_t _sizeOfData = C9_SIZE_OF_BETWEEN_VALUE( m_fVolume , m_bAttachBone );

	if( pFile->IsSave() )
	{
		size_t uiSoundCount = m_lstSoundFile.size();	pFile->WriteData_SizeT( uiSoundCount );
		for( size_t cSound = 0; cSound < uiSoundCount; ++cSound )
			pFile->WriteData( m_lstSoundFile[cSound] );

		pFile->WriteData( m_strBoneName );

		pFile->WriteData_SizeT( &m_fVolume , _sizeOfData );
	}
	else
	{
		size_t uiSoundCount = 0;	pFile->ReadData_SizeT( uiSoundCount );
		m_lstSoundFile.resize( uiSoundCount );
		for( size_t cSubSound = 0; cSubSound < uiSoundCount; ++cSubSound )
		{
			pFile->ReadData( m_lstSoundFile[cSubSound] );
			lstPreloadSound.AddStringLower( m_lstSoundFile[cSubSound].c_str() );
		}

		pFile->ReadData( m_strBoneName );

		pFile->ReadData_SizeT( &m_fVolume , _sizeOfData );
	}
}

void CFrameEventSound::CopyActionValue( CFrameEvent *pFrameEvent , int iLevel )
{
	CFrameEvent::CopyActionValue( pFrameEvent , iLevel );
	CFrameEventSound* pCopyFrameEvent = ( CFrameEventSound* )pFrameEvent;

	m_fVolume = pCopyFrameEvent->m_fVolume;
	m_iLoopNum = pCopyFrameEvent->m_iLoopNum;
	m_fMinDistance = pCopyFrameEvent->m_fMinDistance;
	m_fMaxDistance = pCopyFrameEvent->m_fMaxDistance;
	m_bIs2DSound = pCopyFrameEvent->m_bIs2DSound;
	m_bAttachBone = pCopyFrameEvent->m_bAttachBone;
}

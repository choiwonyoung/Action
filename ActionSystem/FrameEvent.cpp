#include "stdafx.h"
#include "FrameEvent.h"
#include "ActionDataInfo.h"
#include "ActionDefine.h"

#include "FrameEventAttackNormal.h"
#include "FrameEventAttackBow.h"
#include "FrameEventAttackRange.h"
#include "FrameEventCameraShake.h"
#include "FrameEventEffect.h"
#include "FrameEventSkill.h"
#include "FrameEventSound.h"
#include "FrameEventSwordTrail.h"


//////////////////////////////////////////////////////////////////////////
bool CFrameEvent::LoadXML( XMLNode *pXMLNode , List_PreloadString &lstPreloadEffect , List_PreloadString &lstPreloadSound , const char * pszClassName /*= NULL */ )
{
	if( pXMLNode->GetAttrInt( "Frame" , m_nFrame ) == false )
	{
		char strError[256];
		sprintf_s( strError , 256 , "%s (%s)" , "Frame값이 없습니다." , pszClassName );
		MessageBoxA( NULL , strError , "Error" , MB_OK );
		return false;
	}

	pXMLNode->GetAttrDWORD( "ID" , m_dwID );
	pXMLNode->GetAttrDWORD( "NeedID" , m_dwNeedID );
	pXMLNode->GetAttrDWORD( "CheckSkillType" , m_dwCheckSkillType );

	CActionDataInfo::LoadXmlActionIndex( pXMLNode , m_lstActionIndexHashCode );

	LoadXMLCopyActionValue( pXMLNode );

	return true;
}

void CFrameEvent::Dump( C9File * pFile , List_PreloadString & lstPreloadEffect , List_PreloadString &lstPreloadSound )
{
	static const size_t _sizeOfData = C9_SIZE_OF_BETWEEN_VALUE( m_nFrame , m_uiFrameEventIndex );

	CActionDataInfo::DumpActionIndex( pFile , m_lstActionIndexHashCode );

	if( pFile->IsSave() )
	{
		pFile->WriteData_SizeT( &m_nFrame , _sizeOfData );
	}
	else
	{
		pFile->ReadData_SizeT( &m_nFrame , _sizeOfData );
	}
}

CFrameEventType CFrameEvent::Parse_GetFrameEventType( const char * pszType )
{
	if( strlen( pszType ) > 0 )
	{
		if( strcmp( pszType , "CameraShake" ) == 0 )				return CFE_CameraShake;
		if( strcmp( pszType , "AttackNormal" ) == 0 )				return CFE_AttackNormal;
		if( strcmp( pszType , "AttackRange" ) == 0 )				return CFE_AttackRange;
		if( strcmp( pszType , "AttackBow" ) == 0 )					return CFE_AttackBow;
		if( strcmp( pszType , "Sound" ) == 0 )						return CFE_Sound;
		if( strcmp( pszType , "Skill" ) == 0 )						return CFE_Skill;
		if( strcmp( pszType , "UseSkill" ) == 0 )					return CFE_UseSkill;

		char strError[256];
		sprintf_s( strError , 256 , "알수없는 타입(%s) -> FrameEventType" , pszType );
		MessageBoxA( NULL , strError , "Error" , MB_OK );
	}
	else
	{	
		char strError[256];
		sprintf_s( strError , 256 , "타입이 없습니다.-> FrameEventType" );
		MessageBoxA( NULL , strError , "Error" , MB_OK );
	}

	return CFE_MAX;
}

CFrameEvent* CFrameEvent::Create_FrameEvent( CFrameEventType type , const CActionData & actionData , const CFrameEvent * pOriginal )
{
	switch( type )
	{
		case CFE_CameraShake:					return pOriginal ? new CFrameEventCameraShake( (const CFrameEventCameraShake &)*pOriginal ) : new CFrameEventCameraShake();
		case CFE_AttackNormal:					return pOriginal ? new CFrameEventAttackNormal( (const CFrameEventAttackNormal &)*pOriginal ) : new CFrameEventAttackNormal( actionData );
		case CFE_AttackRange:					return pOriginal ? new CFrameEventAttackRange( (const CFrameEventAttackRange &)*pOriginal ) : new CFrameEventAttackRange( actionData );
		case CFE_AttackBow:						return pOriginal ? new CFrameEventAttackBow( (const CFrameEventAttackBow&)*pOriginal ) : new CFrameEventAttackBow( actionData );
		case CFE_SwordTrail:					return pOriginal ? new CFrameEventSwordTrail( (const CFrameEventSwordTrail &)*pOriginal ) : new CFrameEventSwordTrail();
		case CFE_Sound:							return pOriginal ? new CFrameEventSound( (const CFrameEventSound &)*pOriginal ) : new CFrameEventSound( actionData );
		case CFE_Skill:							return pOriginal ? new CFrameEventSkill( (const CFrameEventSkill &)*pOriginal ) : new CFrameEventSkill();
	}

	assert( false && "타입이 존재하지 않습니다." );
	return NULL;
}

void CFrameEvent::LoadDataVarList( const char *pStrMessage , vector< CAddAttackValue > &varList )
{
	char strSep[] = "/";
	char *pToken;
	char strParam[128];

	int iBufferSize = ( int )( ( strlen( pStrMessage ) + 1 ) * sizeof( char ) );
	char *pTemp = ( char* )( _alloca( iBufferSize ) );
	strcpy_s( pTemp , iBufferSize , pStrMessage );

	char * pNextToken = NULL;
	pToken = strtok_s( pTemp , strSep , &pNextToken );

	while( pToken )
	{
		if( pToken )
		{
			string strInput = pToken;
			if( Action::ActionString::GetStrParam( pToken , 0 , strParam ) )
			{
				CAddAttackValue attackValue;
				// 타입 검사
				if( strcmp( strParam , "Skill" ) == 0 )
				{
					attackValue.iVarType = C9_DATA_INFO_SKILL;
					if( Action::ActionString::GetStrParam( pToken , 1 , strParam ) )
					{
						// 스킬키
						attackValue.dwKey = ( DWORD )atoi( strParam );

						if( Action::ActionString::GetStrParam( pToken , 2 , strParam ) )
						{
							// 변수
							attackValue.dwVarCode = CCrc32Static::StringCrc32( strParam );
							varList.push_back( attackValue );
						}
					}
				}
				else if( strcmp( strParam , "Item" ) == 0 )
				{
					attackValue.iVarType = C9_DATA_INFO_ITEM;
					if( Action::ActionString::GetStrParam( pToken , 1 , strParam ) )
					{
						// 변수
						attackValue.dwVarCode = CCrc32Static::StringCrc32( strParam );
						varList.push_back( attackValue );
					}
				}
			}
		}
		pToken = strtok_s( NULL , strSep , &pNextToken );
	}
}

void CFrameEvent::DumpDataVarList( C9File * pFile , vector< CAddAttackValue > &varList )
{
	if( pFile->IsSave() )
	{
		const size_t _count = varList.size();	pFile->WriteData_SizeT( _count );
		if( _count > 0 )
			pFile->WriteData_SizeT( &varList[0] , sizeof( CAddAttackValue ) * _count );
	}
	else
	{
		size_t _count = 0;		pFile->ReadData_SizeT( _count );
		varList.resize( _count );
		if( _count > 0 )
			pFile->ReadData_SizeT( &varList[0] , sizeof( CAddAttackValue ) * _count );
	}
}




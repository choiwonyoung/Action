#include "stdafx.h"

#include "ActionData.h"
#include "ActionDataInfo.h"
#include "AIActionChart.h"
#include "AIExcute.h"

#include "AIActionChart_Wait.h"
#include "AIActionChart_WalkRandom.h"
#include "AIActionChart_RunTarget.h"
#include "AIActionChart_RotationTarget.h"
#include "AIActionChart_Attack.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//


CAIActionChart::~CAIActionChart()
{
	RSAFE_DELETE_VECTOR( m_lstExecute );
}

AIActionChartType CAIActionChart::Parse_GetAIActionChartType( const char * pszType )
{
	if( strlen( pszType ) > 0 )
	{
		if( strcmp( pszType , "Wait" ) == 0 )				return TYPE_CAIActionChart_Wait;
		if( strcmp( pszType , "WalkRandom" ) == 0 )			return TYPE_CAIActionChart_WalkRandom;
		if( strcmp( pszType , "TargetRotation" ) == 0 )		return TYPE_CAIActionChart_RotationTarget;
		if( strcmp( pszType , "RunTarget" ) == 0 )			return TYPE_CAIActionChart_RunTarget;
		if( strcmp( pszType , "Attack" ) == 0 )				return TYPE_CAIActionChart_Attack;

		char strError[256];
		sprintf_s( strError , 256 , "알수없는 타입(%s) -> AIActionChartType" , pszType );
		MessageBoxA( NULL , strError , "Error" , MB_OK );
	}
	else
	{
		char strError[256];
		sprintf_s( strError , 256 , "타입이 없습니다.-> AIActionChartType" );
		MessageBoxA( NULL , strError , "Error" , MB_OK );
	}

	return TYPE_CAIActionChart_None;
}

CAIActionChart*	CAIActionChart::Create_AIActionChart( AIActionChartType type )
{
	switch( type )
	{
		case TYPE_CAIActionChart_Wait:					return new CAIActionChart_Wait;
		case TYPE_CAIActionChart_WalkRandom:			return new CAIActionChart_WalkRandom;
		case TYPE_CAIActionChart_RotationTarget:		return new CAIActionChart_RotationTarget;
		case TYPE_CAIActionChart_RunTarget:				return new CAIActionChart_RunTarget;
		case TYPE_CAIActionChart_Attack:				return new CAIActionChart_Attack;
	}

	char strError[256];
	sprintf_s( strError , 256 , "타입이 없습니다.-> AIActionChartType" );
	MessageBoxA( NULL , strError , "Error" , MB_OK );

	return NULL;
}



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
bool CAIActionChart::LoadXML( XMLNode *pXMLNode , CAIActionData *pActionData )
{
	string strAttr;

	m_strName = pXMLNode->Value();
	m_dwHashcode = CCrc32Static::StringCrc32( m_strName.c_str() );

	CActionDataInfo::LoadXmlActionIndex( pXMLNode , m_lstActionIndexHashCode );

	pXMLNode->GetAttrBool( "StartTimer" , m_bStartTimer );

	if( GetType() != TYPE_CAIActionChart_Damage && pXMLNode->GetAttr( "RunActionName" , m_strRunActionName ) == false )
	{
		char strError[256];
		sprintf_s( strError , 256 , "수행 액션 이름 정보가 없습니다.(%s) : RunActionName = \n" , m_strName.c_str() );
		MessageBoxA( NULL , strError , "Error" , MB_OK );
		return false;
	}
	m_dwRunActionChartCode = CCrc32Static::StringCrc32( m_strRunActionName.c_str() );

	pXMLNode->GetAttr( "EventAIAction" , m_strEventAIActionName[0] );
	m_dwEventAIAtionCode[0] = CCrc32Static::StringCrc32( m_strEventAIActionName[0].c_str() );

	pXMLNode->GetAttr( "EventAIAction2" , m_strEventAIActionName[1] );
	m_dwEventAIAtionCode[1] = CCrc32Static::StringCrc32( m_strEventAIActionName[1].c_str() );

	pXMLNode->GetAttr( "EventPlayerAction" , m_strPlayerActionName[0] );
	m_dwPlayerActionHashCode[0] = CCrc32Static::StringCrc32( m_strPlayerActionName[0].c_str() );

	pXMLNode->GetAttr( "EventPlayerAction2" , m_strPlayerActionName[1] );
	m_dwPlayerActionHashCode[1] = CCrc32Static::StringCrc32( m_strPlayerActionName[1].c_str() );

	pXMLNode->GetAttrInt( "EventIconIndex" , m_iEventIconIndex );
	pXMLNode->GetAttrInt( "EventIconAniSpeed" , m_iEventIconAniSpeed );
	pXMLNode->GetAttrFloat( "EventDistance" , m_fEventDistance );

	if( LoadAIAction( pXMLNode , pActionData ) == false )
	{
		char strError[256];
		sprintf_s( strError , 256 , "LoadAIAction error(%s)\n" , m_strName.c_str() );
		MessageBoxA( NULL , strError , "Error" , MB_OK );
		return false;
	}

	// execute list --------------------------------------------------------------------------------------
	if( LoadExecute( pXMLNode->GetChilds( "Execute" ) , pActionData ) == false )
	{
		char strError[256];
		sprintf_s( strError , 256 , "LoadExecute error(%s)\n" , m_strName.c_str() );
		MessageBoxA( NULL , strError , "Error" , MB_OK );
		return false;
	}

	XMLNode *pEndAction = pXMLNode->GetChild( "AIActionEnd" );
	if( pEndAction )
	{
		m_strEndAIActionName = pEndAction->Value();
		pEndAction->GetAttrInt( "BlendTime" , m_iEndBlendtime );
		pEndAction->GetAttrBool( "ReturnPreTarget" , m_bReturnPreTarget );
		m_dwEndAIActionCode = CCrc32Static::StringCrc32( m_strEndAIActionName.c_str() );
	}

	pXMLNode->GetAttrBool( "PathCollision" , m_bCollisionForPath );
	pXMLNode->GetAttrBool( "Gravity" , m_bGravity );
	pXMLNode->GetAttrBool( "OnMinimap" , m_bNoteOnMinimap );
	pXMLNode->GetAttrBool( "CheckAllFrame" , m_bCheckAllFrame );
	pXMLNode->GetAttrBool( "IgnoreThreat" , m_bIgnoreThreat );
	pXMLNode->GetAttrBool( "DisableRotateAtEvent" , m_bDisableRotateAtEvent );
	pXMLNode->GetAttrBool( "IgnoreOrder" , m_bIgnoreOrder );

	bool bHitCount = false;
	if( pXMLNode->GetAttrBool( "StartHitCount" , bHitCount ) == false )
	{
		m_iSetHitCountType = -1;
	}
	else
	{
		if( bHitCount )
			m_iSetHitCountType = 1;
		else
			m_iSetHitCountType = 0;
	}

	return true;
}

void CAIActionChart::Dump( C9File * pFile , CAIActionData *pActionData )
{
	static const size_t sizeOfData = C9_SIZE_OF_BETWEEN_VALUE( m_dwHashcode , m_bIgnoreOrder );

	CActionDataInfo::DumpActionIndex( pFile , m_lstActionIndexHashCode );

	if( pFile->IsSave() )
	{
		pFile->WriteData( m_strName );
		pFile->WriteData( m_strRunActionName );
		pFile->WriteData( m_strEndAIActionName );
		pFile->WriteData( m_strEventAIActionName[0] );
		pFile->WriteData( m_strEventAIActionName[1] );
		pFile->WriteData( m_strPlayerActionName[0] );
		pFile->WriteData( m_strPlayerActionName[1] );

		pFile->WriteData_SizeT( &m_dwHashcode , sizeOfData );

		const size_t _ExecuteCount = m_lstExecute.size();		pFile->WriteData_SizeT( _ExecuteCount );
		for( size_t cExecute = 0; cExecute < _ExecuteCount; ++cExecute )
		{
			CAIExecute* pExecute = m_lstExecute[cExecute];
			pFile->WriteData( ( int )pExecute->GetType() );
			pExecute->Dump( pFile , pActionData );
		}
	}
	else
	{
		pFile->ReadData( m_strName );
		pFile->ReadData( m_strRunActionName );
		pFile->ReadData( m_strEndAIActionName );
		pFile->ReadData( m_strEventAIActionName[0] );
		pFile->ReadData( m_strEventAIActionName[1] );
		pFile->ReadData( m_strPlayerActionName[0] );
		pFile->ReadData( m_strPlayerActionName[1] );

		pFile->ReadData_SizeT( &m_dwHashcode , sizeOfData );

		size_t _ExecuteCount = 0;		pFile->ReadData_SizeT( _ExecuteCount );
		for( size_t cExecute = 0; cExecute < _ExecuteCount; ++cExecute )
		{
			AIExecuteType _Type;		pFile->ReadData( ( int & )_Type );
			CAIExecute * pExecute = CAIExecute::Create_AIExecute( _Type );
			assert( pExecute );
			pExecute->Dump( pFile , pActionData );

			m_lstExecute.push_back( pExecute );
		}
	}
}

bool CAIActionChart::LoadExecute( XMLNodes nodes , CAIActionData* pActionData )
{
	for( size_t i = 0; i < nodes.size(); ++i )
	{
		AIExecuteType executeType = CAIExecute::Parse_GetExecuteType( nodes[i]->GetAttr( "Type" ).c_str() );
		CAIExecute * pExecute = CAIExecute::Create_AIExecute( executeType );
		if( pExecute )
		{
			if( pExecute->LoadXML( nodes[i] , pActionData ) == false )
			{
				RSAFE_DELETE( pExecute );
				return false;
			}
			m_lstExecute.push_back( pExecute );
		}
	}
	return true;
}



// EOF
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
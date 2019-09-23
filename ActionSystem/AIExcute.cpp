#include "stdafx.h"
#include "AIExcute.h"
#include "ActionContantable.h"
#include "ActionDataInfo.h"
#include "AICondition.h"
#include "AIActionData.h"

#include "AIExecute_RunAIAction.h"
#include "AIExecute_RunTimer.h"
#include "AIExecute_SetActionIndex.h"
#include "AIExecute_SetSkillTimer.h"

AIExecuteType CAIExecute::Parse_GetExecuteType( const char * pszParameter )
{
	if( strlen( pszParameter ) > 0 )
	{
		if( strcmp( pszParameter , "RunAIAction" ) == 0 )		return TYPE_CAIExecute_RunAIAction;
		if( strcmp( pszParameter , "SkipExecute" ) == 0 )		return TYPE_CAIExecute_SkipExecute;
		if( strcmp( pszParameter , "RunTimer" ) == 0 )			return TYPE_CAIExecute_RunTimer;
		if( strcmp( pszParameter , "SetValue" ) == 0 )			return TYPE_CAIExecute_SetValue;
		if( strcmp( pszParameter , "SetSkillTimer" ) == 0 )		return TYPE_CAIExecute_SetSkillTimer;
		if( strcmp( pszParameter , "AISpeech" ) == 0 )			return TYPE_CAIExecute_AISpeech;
		if( strcmp( pszParameter , "SetActionIndex" ) == 0 )	return TYPE_CAIExecute_SetActionIndex;
		if( strcmp( pszParameter , "GiveOrder" ) == 0 )			return TYPE_CAIExecute_GiveOrder;
		if( strcmp( pszParameter , "SetActionTimer" ) == 0 )	return TYPE_CAIExecute_RunActionTimer;

		char strError[256];
		sprintf_s( strError , 256 , "알수없는 타입(%s) -> AIExecuteType" , pszParameter );
		MessageBoxA( NULL , strError , "Error" , MB_OK );
	}
	else
	{
		char strError[256];
		sprintf_s( strError , 256 , "타입이 없습니다.-> AIExecuteType" );
		MessageBoxA( NULL , strError , "Error" , MB_OK );
	}

	return TYPE_CAIExecute_None;
}

CAIExecute * CAIExecute::Create_AIExecute( AIExecuteType type )
{
	switch( type )
	{
		case TYPE_CAIExecute_RunAIAction:		return new CAIExecute_RunAIAction;
		case TYPE_CAIExecute_RunTimer:			return new CAIExecute_RunTimer;
		case TYPE_CAIExecute_SetSkillTimer:		return new CAIExecute_SetSkillTimer;
		case TYPE_CAIExecute_SetActionIndex:	return new CAIExecute_SetActionIndex;
	}

	assert( 0 );
	return NULL;
}

CAIExecute::~CAIExecute()
{
	RSAFE_DELETE_VECTOR( m_lstCondition );
}

bool CAIExecute::LoadXML( XMLNode *pXMLNode , CAIActionData * pActionData )
{
	string strAttr;

	// execute list --------------------------------------------------------------------------------------
	string strParameter = pXMLNode->GetAttr( "CheckType" );
	if( strParameter.length() > 0 )
	{
		if( Action::ActionString::GetToken( strParameter , 0 ) == "Or" )
			m_bConditionCheckOR = true;
	}

	pXMLNode->GetAttrBool( "WaitActionEnd" , m_bWaitActionEnd );
	pXMLNode->GetAttrBool( "RefreshSetAction" , m_bRefreshSetAction );


	if( pXMLNode->GetAttr( "ActionIndex" , strAttr ) && strAttr.empty() == false )
	{
		char * pNextToken = NULL;
		char * pToken = strtok_s( &strAttr[0] , " " , &pNextToken );
		while( pToken != NULL )
		{
			m_lstActionIndexHashCode.push_back( CCrc32Static::StringCrc32( pToken ) );
			pToken = strtok_s( NULL , " " , &pNextToken );
		}
	}

	if( LoadCondition( pXMLNode->GetChilds( "Condition" ) , pActionData ) == false )
		return false;

	return true;
}

void CAIExecute::Dump( C9File * pFile , CAIActionData * pActionData )
{
	static const size_t sizeOfData = C9_SIZE_OF_BETWEEN_VALUE( m_bConditionCheckOR , m_bRefreshSetAction );

	CActionDataInfo::DumpActionIndex( pFile , m_lstActionIndexHashCode );

	if( pFile->IsSave() )
	{
		const size_t conditionCount = m_lstCondition.size();		pFile->WriteData_SizeT( conditionCount );
		for( size_t cCondition = 0; cCondition < conditionCount; ++cCondition )
		{
			CAICondition * pCondition = m_lstCondition[cCondition];
			pFile->WriteData( ( int )pCondition->GetType() );
			pCondition->Dump( pFile , pActionData );
		}

		pFile->WriteData_SizeT( &m_bConditionCheckOR , sizeOfData );
	}
	else
	{
		size_t conditionCount = 0;		pFile->ReadData_SizeT( conditionCount );
		for( size_t cCondition = 0; cCondition < conditionCount; ++cCondition )
		{
			AIConditionType _Type;		pFile->ReadData( ( int & )_Type );
			CAICondition * pCondition = CAICondition::Create_AICondition( _Type );
			pCondition->Dump( pFile , pActionData );

			m_lstCondition.push_back( pCondition );
		}

		pFile->ReadData_SizeT( &m_bConditionCheckOR , sizeOfData );
	}
}

bool CAIExecute::LoadCondition( XMLNodes nodes , CAIActionData *pActionData )
{
	for( UINT i = 0; i < nodes.size(); ++i )
	{
		AIConditionType conditionType	= CAICondition::Parse_GetConditionType( nodes[i]->GetAttr( "Type" ).c_str() );
		CAICondition * pCondition		= CAICondition::Create_AICondition( conditionType );
		if( pCondition )
		{
			if( pCondition->LoadXML( nodes[i] , pActionData ) == false )
			{
				RSAFE_DELETE( pCondition );
				return false;
			}

			m_lstCondition.push_back( pCondition );
		}
	}
	return true;
}

// bool CAIExecute::GetCheckTimer( DWORD& dwCheckSkillTimer )
// {
// 	for( size_t i = 0; i < m_lstCondition.size(); ++i )
// 	{
// 		if( m_lstCondition[i]->GetType() == TYPE_CAICondition_CheckSkillTimer )
// 		{
// 			dwCheckSkillTimer = ( ( CAICondition_CheckSkillTimer* )m_lstCondition[i] )->m_dwName;
// 			return true;
// 		}
// 	}
// 	return false;
// }

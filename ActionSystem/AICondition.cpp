#include "stdafx.h"

#include "AICondition.h"
#include "ActionData.h"
#include "AIActionData.h"

#include "AICondition_CheckAreaRange.h"
#include "AICondition_CheckTargetRange.h"
#include "AICondition_Random.h"
#include "AICondition_SearchAttackTarget.h"
#include "AIConditoin_CheckTargetStates.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------------------------------------------------------------------
AIConditionType CAICondition::Parse_GetConditionType( const char * pszParameter )
{
	if( strlen( pszParameter ) > 0 )
	{
		if( strcmp( pszParameter , "SearchAttackTarget" ) == 0 )	return TYPE_CAICondition_SearchAttackTarget;
		if( strcmp( pszParameter , "Random" ) == 0 )				return TYPE_CAICondition_Random;
		if( strcmp( pszParameter , "CheckTargetRange" ) == 0 )		return TYPE_CAICondition_CheckTargetRange;
		if( strcmp( pszParameter , "SearchTargetAngle" ) == 0 )		return TYPE_CAICondition_SearchTargetAngle;
		if( strcmp( pszParameter , "CheckRunTimer" ) == 0 )			return TYPE_CAICondition_CheckRunTimer;
		if( strcmp( pszParameter , "CheckSelfStates" ) == 0 )		return TYPE_CAICondition_CheckSelfStates;
		if( strcmp( pszParameter , "CheckTargetStates" ) == 0 )		return TYPE_CAICondition_CheckTargetStates;
		if( strcmp( pszParameter , "CheckValue" ) == 0 )			return TYPE_CAICondition_CheckValue;
		if( strcmp( pszParameter , "CheckTutorialValue" ) == 0 )	return TYPE_CAICondition_CheckTutorialValue;
		if( strcmp( pszParameter , "CheckOurStates" ) == 0 )		return TYPE_CAICondition_CheckOurStates;
		if( strcmp( pszParameter , "CheckOtherStates" ) == 0 )		return TYPE_CAICondition_CheckOtherStates;
		if( strcmp( pszParameter , "CheckEventValue" ) == 0 )		return TYPE_CAICondition_CheckEventValue;
		if( strcmp( pszParameter , "CheckAreaRange" ) == 0 )		return TYPE_CAICondition_CheckAreaRange;
		if( strcmp( pszParameter , "CheckSkillTimer" ) == 0 )		return TYPE_CAICondition_CheckSkillTimer;
		if( strcmp( pszParameter , "CheckRideTarget" ) == 0 )		return TYPE_CAICondition_CheckRideTarget;
		if( strcmp( pszParameter , "CheckLevel" ) == 0 )			return TYPE_CAICondition_CheckLevel;
		if( strcmp( pszParameter , "CheckActionTimer" ) == 0 )		return TYPE_CAICondition_CheckActionTimer;

		char strError[256];
		sprintf_s( strError , 256 , "알수없는 타입(%s) -> AIConditionType" , pszParameter );
		MessageBoxA( NULL , strError , "Error" , MB_OK );
	}
	else
	{
		char strError[256];
		sprintf_s( strError , 256 , "타입이 없습니다.-> AIConditionType" );
		MessageBoxA( NULL , strError , "Error" , MB_OK );
	}

	return TYPE_CAICondition_None;
}

CAICondition * CAICondition::Create_AICondition( AIConditionType type )
{
	switch( type )
	{
		case TYPE_CAICondition_SearchAttackTarget:			return new CAICondition_SearchAttackTarget;
		case TYPE_CAICondition_Random:						return new CAICondition_Random;
		case TYPE_CAICondition_CheckTargetRange:			return new CAICondition_CheckTargetRange;
		case TYPE_CAICondition_CheckTargetStates:			return new CAICondition_CheckTargetStates;
		case TYPE_CAICondition_CheckAreaRange:				return new CAICondition_CheckAreaRange;	
	}


	return NULL;
}

OBJECT_STATES CAICondition::Parse_GetStates( const char * pszState )
{
	if( strlen( pszState ) > 0 )
	{
		if( strcmp( pszState , "HP" ) == 0 )				return OBJECT_STATES_HP;
		if( strcmp( pszState , "MP" ) == 0 )				return OBJECT_STATES_MP;
		if( strcmp( pszState , "DAMAGESTATE" ) == 0 )		return OBJECT_STATES_DAMAGE;
		if( strcmp( pszState , "JUMPSTATE" ) == 0 )			return OBJECT_STATES_JUMP;
		if( strcmp( pszState , "ATTACKSTATE" ) == 0 )		return OBJECT_STATES_ATTACK;
		if( strcmp( pszState , "CHECKSIGHT" ) == 0 )		return OBJECT_STATES_SIGHT;
		if( strcmp( pszState , "ACTIONTYPE" ) == 0 )		return OBJECT_STATES_ACTION;
		if( strcmp( pszState , "CATCHSTATE" ) == 0 )		return OBJECT_STATES_CATCH;
		if( strcmp( pszState , "WALLSTATE" ) == 0 )			return OBJECT_STATES_WALL;
		if( strcmp( pszState , "SUMMONLIMIT" ) == 0 )		return OBJECT_STATES_SUMMONLIMIT;
		if( strcmp( pszState , "ORDERWAITSTATE" ) == 0 )	return OBJECT_STATES_ORDERWAITSTATE;
		if( strcmp( pszState , "TEAM" ) == 0 )				return OBJECT_STATES_TEAM;
		if( strcmp( pszState , "ABNORMAL" ) == 0 )			return OBJECT_STATES_ABNORMAL;
	}

	char strError[256];
	sprintf_s( strError , 256 ,"알수없는 타입(%s) -> States" , pszState );
	MessageBoxA( NULL , strError , "Error" , MB_OK );

	return OBJECT_STATES_HP;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
bool CAICondition::LoadXML( XMLNode * pXMLNode , CAIActionData * pActionData )
{
	pXMLNode->GetAttrBool( "CheckReturn" , m_bCheckReturn );

	return true;
}

void CAICondition::Dump( C9File * pFile , CAIActionData *pActionData )
{
	if( pFile->IsSave() )
	{
		pFile->WriteData( m_bCheckReturn );
	}
	else
	{
		pFile->ReadData( m_bCheckReturn );
	}
}

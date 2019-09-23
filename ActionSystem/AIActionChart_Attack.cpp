#include "stdafx.h"
#include "AIActionChart.h"
#include "AIActionChart_Attack.h"


bool CAIActionChart_Attack::LoadAIAction( XMLNode *pXMLNode , CAIActionData *pActionData )
{
	string strAttr;
	pXMLNode->GetAttr( "AttackableMask" , strAttr );


	if( strAttr.empty() == false )
	{
		char * nextToken = NULL;
		char * token = strtok_s( &strAttr[0] , " " , &nextToken );
		m_iAttackableMask = 0;
		while( token != NULL )
		{
			m_iAttackableMask |= CompareAttackableMask( token );
			token = strtok_s( NULL , " " , &nextToken );
		}
	}
	else
	{
		m_iAttackableMask |= 1 << CDS_NONE;
		m_iAttackableMask |= 1 << CDS_NORMAL;
		m_iAttackableMask |= 1 << CDS_CATCH;
	}
	pXMLNode->GetAttrBool( "SetTagetDirection" , m_bSetTargetDirection );
	pXMLNode->GetAttrBool( "SetTargetFollow" , m_bSetTargetFollow );
	pXMLNode->GetAttrBool( "SetTargetHold" , m_bSetTargetHold );

	return true;
}

void CAIActionChart_Attack::Dump( C9File * pFile , CAIActionData *pActionData )
{
	CAIActionChart::Dump( pFile , pActionData );

	static const size_t sizeOfData = C9_SIZE_OF_BETWEEN_VALUE( m_iAttackableMask , m_bSetTargetHold );

	if( pFile->IsSave() )
	{
		pFile->WriteData_SizeT( &m_iAttackableMask , sizeOfData );
	}
	else
	{
		pFile->ReadData_SizeT( &m_iAttackableMask , sizeOfData );
	}
}

int CAIActionChart_Attack::CompareAttackableMask( char* strTemp )
{
	if( strTemp == NULL )
		return 0;

	if( strcmp( "NONE" , strTemp ) == 0 ) return 1 << CDS_NONE;
	if( strcmp( "NORMAL" , strTemp ) == 0 ) return 1 << CDS_NORMAL;
	if( strcmp( "SKILL" , strTemp ) == 0 ) return 1 << CDS_SKILL;
	if( strcmp( "PULL" , strTemp ) == 0 ) return 1 << CDS_PULL;
	if( strcmp( "CATCH" , strTemp ) == 0 ) return 1 << CDS_CATCH;
	if( strcmp( "DOWN" , strTemp ) == 0 ) return 1 << CDS_DOWN;
	if( strcmp( "STANDUP" , strTemp ) == 0 ) return 1 << CDS_STANDUP;
	if( strcmp( "KNOCKDOWN" , strTemp ) == 0 ) return 1 << CDS_KNOCKDOWN;
	if( strcmp( "DEAD" , strTemp ) == 0 ) return 1 << CDS_DEAD;
	if( strcmp( "DEFENCE_PUSH" , strTemp ) == 0 ) return 1 << CDS_DEFENCE_PUSH;
	if( strcmp( "ICED" , strTemp ) == 0 ) return 1 << CDS_ICED;
	if( strcmp( "STUN" , strTemp ) == 0 ) return 1 << CDS_STUN;
	if( strcmp( "RIGID" , strTemp ) == 0 ) return 1 << CDS_RIGID;
	if( strcmp( "WALLSTUN" , strTemp ) == 0 ) return 1 << CDS_WALLSTUN;
	if( strcmp( "HOOK" , strTemp ) == 0 ) return 1 << CDS_HOOK;
	if( strcmp( "MAX" , strTemp ) == 0 ) return 1 << CDS_MAX;

	return 0;
}

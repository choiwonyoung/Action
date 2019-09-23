#include "stdafx.h"
#include "AICondition_Random.h"
#include "AIActionData.h"

bool CAICondition_Random::LoadXML( XMLNode *pXMLNode , CAIActionData *pActionData )
{
	string strTemp;
	int iValue;

	GET_PARAM_VALUE( "Value" , "ConditionRandom" );
	m_iValue = iValue;


	return CAICondition::LoadXML( pXMLNode , pActionData );
}

void CAICondition_Random::Dump( C9File * pFile , CAIActionData *pActionData )
{
	CAICondition::Dump( pFile , pActionData );

	if( pFile->IsSave() )
	{
		pFile->WriteData( m_iValue );
	}
	else
	{
		pFile->ReadData( m_iValue );
	}
}

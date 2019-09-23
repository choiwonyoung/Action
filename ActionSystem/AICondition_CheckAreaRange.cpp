#include "stdafx.h"
#include "AICondition_CheckAreaRange.h"
#include "AIActionData.h"

bool CAICondition_CheckAreaRange::LoadXML( XMLNode *pXMLNode , CAIActionData *pActionData )
{
	string strTemp;
	int iValue;

	GET_PARAM_VALUE( "MinRange" , "ConditionCheckTargetRange" );
	m_fMinRange = ( float )iValue;

	GET_PARAM_VALUE( "MaxRange" , "ConditionCheckTargetRange" );
	m_fMaxRange = ( float )iValue;

	GET_PARAM_VALUE( "AreaIndex" , "C9AIActionChartMoveArea" );
	m_dwAreaIndex = ( DWORD )iValue;

	return CAICondition::LoadXML( pXMLNode , pActionData );
}

void CAICondition_CheckAreaRange::Dump( C9File * pFile , CAIActionData *pActionData )
{
	CAICondition::Dump( pFile , pActionData );

	static const size_t sizeOfData = C9_SIZE_OF_BETWEEN_VALUE( m_fMinRange , m_dwAreaIndex );

	if( pFile->IsSave() )
	{
		pFile->WriteData_SizeT( &m_fMinRange , sizeOfData );
	}
	else
	{
		pFile->ReadData_SizeT( &m_fMinRange , sizeOfData );
	}
}

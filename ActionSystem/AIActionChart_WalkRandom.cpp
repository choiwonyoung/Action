#include "stdafx.h"

#include "AIActionChart_WalkRandom.h"


bool CAIActionChart_WalkRandom::LoadAIAction( XMLNode *pXMLNode , CAIActionData *pActionData )
{
	string strTemp;
	int iValue;

	GET_PARAM_VALUE( "MinRange" , "AIActionChartWalkRandom" );
	m_fMinRange = ( float )iValue;

	GET_PARAM_VALUE( "MaxRange" , "AIActionChartWalkRandom" );
	m_fMaxRange = ( float )iValue;

	GET_PARAM_VALUE( "MoveSpeed" , "AIActionChartWalkRandom" );
	m_fMoveSpeed = ( float )iValue;

	pXMLNode->GetAttrBool( "BasePosMove" , m_bBasePosMove );

	pXMLNode->GetAttrBool( "CurvedPath" , m_bCurvedPath );

	return true;
}

void CAIActionChart_WalkRandom::Dump( C9File * pFile , CAIActionData *pActionData )
{
	CAIActionChart::Dump( pFile , pActionData );

	static const size_t sizeOfData = C9_SIZE_OF_BETWEEN_VALUE( m_fMinRange , m_bCurvedPath );

	if( pFile->IsSave() )
	{
		pFile->WriteData_SizeT( &m_fMinRange , sizeOfData );
	}
	else
	{
		pFile->ReadData_SizeT( &m_fMinRange , sizeOfData );
	}
}

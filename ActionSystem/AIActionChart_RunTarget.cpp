#include "stdafx.h"
#include "AIActionChart_RunTarget.h"


bool CAIActionChart_RunTarget::LoadAIAction( XMLNode *pXMLNode , CAIActionData* pActionData )
{
	string strTemp;
	int iValue;

	GET_PARAM_VALUE( "MinRange" , "AIActionChartRunTarget" );
	m_fMinRange = ( float )iValue;

	GET_PARAM_VALUE( "MaxRange" , "AIActionChartRunTarget" );
	m_fMaxRange = ( float )iValue;

	GET_PARAM_VALUE( "MoveSpeed" , "AIActionChartRunTarget" );
	m_fMoveSpeed = ( float )iValue;

	pXMLNode->GetAttrBool( "DirectMove" , m_bDirectMove );

	pXMLNode->GetAttrBool( "CurvedPath" , m_bCurvedPath );

	pXMLNode->GetAttrBool( "DestroyObstacle" , m_bDestroyObstacle );

	if( pXMLNode->GetAttrFloat( "RotationSpeed" , m_fRotationSpeed ) == false )
	{
		m_fRotationSpeed = 1.0f;
	}

	if( pXMLNode->GetAttrFloat( "ClosestRange" , m_fClosestRange ) == false )
	{
		m_fClosestRange = 500.0f;	// µðÆúÆ® 5m
	}

	if( pXMLNode->GetAttrFloat( "CheckRunTargetTime" , m_fCheckRunTargetTime ) == false )
	{
		m_fCheckRunTargetTime = 0.3f;
	}

	if( pXMLNode->GetAttr( "PositionType" , strTemp ) )
	{
		if( strTemp == "Back" )
		{
			m_iTargetPosType = TARGET_POS_TYPE_BACK;
		}
		else if( strTemp == "Right" )
		{
			m_iTargetPosType = TARGET_POS_TYPE_RIGHT;
		}
		else if( strTemp == "Left" )
		{
			m_iTargetPosType = TARGET_POS_TYPE_LEFT;
		}
	}

	return true;
}

void CAIActionChart_RunTarget::Dump( C9File * pFile , CAIActionData* pActionData )
{
	CAIActionChart::Dump( pFile , pActionData );

	static const size_t sizeOfData = C9_SIZE_OF_BETWEEN_VALUE( m_fMinRange , m_bDestroyObstacle );

	if( pFile->IsSave() )
	{
		pFile->WriteData_SizeT( &m_fMinRange , sizeOfData );
	}
	else
	{
		pFile->ReadData_SizeT( &m_fMinRange , sizeOfData );
	}
}

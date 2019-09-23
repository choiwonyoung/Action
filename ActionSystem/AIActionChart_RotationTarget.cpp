#include "stdafx.h"
#include "AIActionChart_RotationTarget.h"


bool CAIActionChart_RotationTarget::LoadAIAction( XMLNode *pXMLNode , CAIActionData *pActionData )
{
	pXMLNode->GetAttrFloat( "RotationSpeed" , m_fRotationSpeed );

	return true;
}

void CAIActionChart_RotationTarget::Dump( C9File * pFile , CAIActionData *pActionData )
{
	CAIActionChart::Dump( pFile , pActionData );

	if( pFile->IsSave() )
	{
		pFile->WriteData( m_fRotationSpeed );
	}
	else
	{
		pFile->ReadData( m_fRotationSpeed );
	}
}

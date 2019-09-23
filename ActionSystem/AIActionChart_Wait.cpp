#include "stdafx.h"
#include "AIActionChart_Wait.h"


bool CAIActionChart_Wait::LoadAIAction( XMLNode *pXMLNode , CAIActionData* pActionData )
{
	pXMLNode->GetAttrBool( "LookAtTarget" , m_LookAtTarget );
	pXMLNode->GetAttrBool( "IgnoreCheckTarget" , m_bIgnoreCheckTarget );
	return true;
}

void CAIActionChart_Wait::Dump( C9File * pFile , CAIActionData* pActionData )
{
	CAIActionChart::Dump( pFile , pActionData );

	static const size_t sizeOfData = C9_SIZE_OF_BETWEEN_VALUE( m_LookAtTarget , m_bIgnoreCheckTarget );

	if( pFile->IsSave() )
	{
		pFile->WriteData_SizeT( &m_LookAtTarget , sizeOfData );
	}
	else
	{
		pFile->ReadData_SizeT( &m_LookAtTarget , sizeOfData );
	}
}

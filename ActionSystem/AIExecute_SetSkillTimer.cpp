#include "stdafx.h"
#include "AIExecute_SetSkillTimer.h"
#include "AIActionData.h"


bool CAIExecute_SetSkillTimer::LoadXML( XMLNode *pXMLNode , CAIActionData *pActionData )
{
	string strTemp;
	int iValue;

	GET_PARAM_VALUE( "Name" , "C9AIExecute_SetSkillTimer" );
	m_dwName = CCrc32Static::StringCrc32( strTemp.c_str() );

	pXMLNode->GetAttrFloat( "Time" , m_fTime );

	return CAIExecute::LoadXML( pXMLNode , pActionData );
}

void CAIExecute_SetSkillTimer::Dump( C9File * pFile , CAIActionData * pActionData )
{
	CAIExecute::Dump( pFile , pActionData );

	if( pFile->IsSave() )
	{
		pFile->WriteData( m_dwName );
		pFile->WriteData( m_fTime );
	}
	else
	{
		pFile->ReadData( m_dwName );
		pFile->ReadData( m_fTime );
	}
}

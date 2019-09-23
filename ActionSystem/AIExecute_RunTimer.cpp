#include "stdafx.h"
#include "AIExecute_RunTimer.h"



bool CAIExecute_RunTimer::LoadXML( XMLNode *pXMLNode , CAIActionData *pActionData )
{
	if( pXMLNode->GetAttrBool( "SetRun" , m_bRun ) == false )
	{
		char strError[256];
		sprintf_s( strError , 256 , "SetRun값이 없습니다.(ExecuteRunTimer)\n" );
		MessageBoxA( NULL , strError , "Error" , MB_OK );
		return false;
	}

	pXMLNode->GetAttrBool( "ResetTime" , m_bReset );

	return CAIExecute::LoadXML( pXMLNode , pActionData );
}

void CAIExecute_RunTimer::Dump( C9File * pFile , CAIActionData * pActionData )
{
	CAIExecute::Dump( pFile , pActionData );

	static const size_t sizeOfData = C9_SIZE_OF_BETWEEN_VALUE( m_bRun , m_bReset );

	if( pFile->IsSave() )
	{
		pFile->WriteData_SizeT( &m_bRun , sizeOfData );
	}
	else
	{
		pFile->ReadData_SizeT( &m_bRun , sizeOfData );
	}
}

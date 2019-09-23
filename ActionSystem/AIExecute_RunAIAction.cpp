#include "stdafx.h"
#include "AIExecute_RunAIAction.h"
#include "AIActionData.h"

bool CAIExecute_RunAIAction::LoadXML( XMLNode *pXMLNode , CAIActionData* pActionData )
{
	m_strRunActionName = pXMLNode->Value();

	if( m_strRunActionName.empty() )
	{
		char strError[256];
		sprintf_s( strError , 256 , "ActionName값이 없습니다.(ExecuteRunAction)\n" );
		MessageBoxA( NULL , strError , "Error" , MB_OK );
		return false;
	}
	m_dwRunAIActionCode = CCrc32Static::StringCrc32( m_strRunActionName.c_str() );

	XMLNode * pFailAction = pXMLNode->GetChild( "AIActionFail" );
	if( pFailAction )
	{
		m_strFailActionName = pFailAction->Value();
		m_dwFailAIActionCode = CCrc32Static::StringCrc32( m_strFailActionName.c_str() );
	}

	pXMLNode->GetAttrInt( "BlendTime" , m_iBlendTime );

	return CAIExecute::LoadXML( pXMLNode , pActionData );
}

void CAIExecute_RunAIAction::Dump( C9File * pFile , CAIActionData* pActionData )
{
	CAIExecute::Dump( pFile , pActionData );

	static const size_t sizeOfData = C9_SIZE_OF_BETWEEN_VALUE( m_dwRunAIActionCode , m_iBlendTime );

	if( pFile->IsSave() )
	{
		pFile->WriteData( m_strRunActionName );
		pFile->WriteData( m_strFailActionName );

		pFile->WriteData_SizeT( &m_dwRunAIActionCode , sizeOfData );
	}
	else
	{
		pFile->ReadData( m_strRunActionName );
		pFile->ReadData( m_strFailActionName );

		pFile->ReadData_SizeT( &m_dwRunAIActionCode , sizeOfData );
	}
}

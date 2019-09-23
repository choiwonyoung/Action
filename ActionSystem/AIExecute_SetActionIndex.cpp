#include "stdafx.h"
#include "AIExecute_SetActionIndex.h"
#include "AIActionData.h"


bool CAIExecute_SetActionIndex::LoadXML( XMLNode *pXMLNode , CAIActionData *pActionData )
{
	string strAttr;
	if( pXMLNode->GetAttr( "SetActionIndex" , strAttr ) && strAttr.empty() == false )
	{
		m_dwActionIndexHash = CCrc32Static::StringCrc32( strAttr.c_str() );
	}
	return CAIExecute::LoadXML( pXMLNode , pActionData );
}

void CAIExecute_SetActionIndex::Dump( C9File * pFile , CAIActionData * pActionData )
{
	CAIExecute::Dump( pFile , pActionData );

	if( pFile->IsSave() )
	{
		pFile->WriteData( m_dwActionIndexHash );
	}
	else
	{
		pFile->ReadData( m_dwActionIndexHash );
	}
}

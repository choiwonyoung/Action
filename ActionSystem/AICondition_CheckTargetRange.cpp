#include "stdafx.h"
#include "AICondition_CheckTargetRange.h"
#include "AIActionData.h"

bool CAICondition_CheckTargetRange::LoadXML( XMLNode *pXMLNode , CAIActionData* pActionData )
{
	string strTemp;
	int iValue;
	m_dwIgnoreEventIDCount = 0;

	GET_PARAM_VALUE( "MinRange" , "ConditionCheckTargetRange" );
	m_fMinRange = ( float )iValue;

	GET_PARAM_VALUE( "MaxRange" , "ConditionCheckTargetRange" );
	m_fMaxRange = ( float )iValue;

	pXMLNode->GetAttrBool( "CalcY" , m_bCalcAxisY );
	pXMLNode->GetAttrBool( "CheckClosestMode" , m_bClosestPosMode );
	pXMLNode->GetAttrBool( "TargetBasePosition" , m_bTargetBasePosition );

	pXMLNode->GetAttrInt( "TargetNumber" , m_iTargetNum );

	if( pXMLNode->GetAttr( "IgnoreTargetType" , strTemp ) && strTemp.empty() == false )
	{
		char * pNextIgnoreToken = NULL;
		char * pIgnoreToken = strtok_s( &strTemp[0] , " " , &pNextIgnoreToken );
		while( pIgnoreToken != NULL )
		{
			if( strcmp( pIgnoreToken , "Player" ) == 0 )			m_lstIgnoreTargetType.push_back( SEARCHTARGET_PLAYER );
			else if( strcmp( pIgnoreToken , "Parent" ) == 0 )		m_lstIgnoreTargetType.push_back( SEARCHTARGET_PARENT );
			else if( strcmp( pIgnoreToken , "Event" ) == 0 )
			{
				string strEventTemp;
				char * pNextIgnoreEventToken = NULL;
				char * pIgnoreEventToken = NULL;


				m_lstIgnoreTargetType.push_back( SEARCHTARGET_EVENT );

				if( pXMLNode->GetAttr( "IgnoreEventID" , strEventTemp ) == false )
				{
					char strError[256];
					sprintf_s( strError , 256 ,  "IgnoreEventID 값이 없습니다." );
					MessageBoxA( NULL , strError , "Error" , MB_OK );
					break;
				}
				pIgnoreEventToken = strtok_s( &strEventTemp[0] , " " , &pNextIgnoreEventToken );

				while( pIgnoreEventToken != NULL )
				{
					m_dwIgnoreEventIDCount++;
					m_lstIgnoreEventID.push_back( atoi( pIgnoreEventToken ) );
					pIgnoreEventToken = strtok_s( NULL , " " , &pNextIgnoreEventToken );
				}
			}
			else
			{
				m_lstIgnoreTargetType.clear();
				m_dwIgnoreTypeCount = 0;
				break;
			}
			this->m_dwIgnoreTypeCount++;

			pIgnoreToken = strtok_s( NULL , " " , &pNextIgnoreToken );
		}
	}
	return CAICondition::LoadXML( pXMLNode , pActionData );
}

void CAICondition_CheckTargetRange::Dump( C9File * pFile , CAIActionData* pActionData )
{
	CAICondition::Dump( pFile , pActionData );

	static const size_t sizeOfData = C9_SIZE_OF_BETWEEN_VALUE( m_fMinRange , m_bClosestPosMode );

	if( pFile->IsSave() )
	{
		pFile->WriteData_SizeT( &m_fMinRange , sizeOfData );
		for( list<SEARCHTARGET_TYPE>::iterator pos = m_lstIgnoreTargetType.begin(); pos != m_lstIgnoreTargetType.end(); pos++ )
		{
			pFile->WriteData( &( *pos ) , sizeof( SEARCHTARGET_TYPE ) );
		}
		for( list<DWORD>::iterator pos = m_lstIgnoreEventID.begin(); pos != m_lstIgnoreEventID.end(); pos++ )
		{
			pFile->WriteData( &( *pos ) , sizeof( DWORD ) );
		}
	}
	else
	{
		pFile->ReadData_SizeT( &m_fMinRange , sizeOfData );
		for( DWORD index = 0; index < m_dwIgnoreTypeCount; index++ )
		{
			SEARCHTARGET_TYPE dwTargetType = SEARCHTARGET_TYPE::SEARCHTARGET_NONE;
			pFile->ReadData( &dwTargetType , sizeof( SEARCHTARGET_TYPE ) );
			if( dwTargetType != SEARCHTARGET_NONE )
				m_lstIgnoreTargetType.push_back( dwTargetType );
		}
		for( DWORD index = 0; index < m_dwIgnoreEventIDCount; index++ )
		{
			DWORD dwIgnoreID = 0;
			pFile->ReadData( &dwIgnoreID , sizeof( DWORD ) );
			if( dwIgnoreID != 0 )
				m_lstIgnoreEventID.push_back( dwIgnoreID );
		}
	}
}

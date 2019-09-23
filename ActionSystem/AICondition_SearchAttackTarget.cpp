#include "stdafx.h"
#include "AICondition_SearchAttackTarget.h"
#include "AIActionData.h"



bool CAICondition_SearchAttackTarget::LoadXML( XMLNode *pXMLNode , CAIActionData* pActionData )
{
	string strTemp;
	int iValue;
	m_dwIgnoreEventIDCount = 0;

	GET_PARAM_VALUE( "Range" , "ConditionSearchTarget" );
	m_fSearchRange = ( float )iValue;

	if( pXMLNode->GetAttr( "MinRange" , strTemp ) )
	{
		pActionData->GetParamValue( strTemp.c_str() , iValue );
		m_fMinSearchRange = ( float )iValue;
	}

	pXMLNode->GetAttrFloat( "Height" , m_fSearchHeight );

	pXMLNode->GetAttr( "TargetType" , strTemp );

	if( strTemp == "Player" )			m_eTargetType = SEARCHTARGET_PLAYER;
	else if( strTemp == "Threat" )		m_eTargetType = SEARCHTARGET_THREAT;
	else if( strTemp == "Parent" )		m_eTargetType = SEARCHTARGET_PARENT;
	else if( strTemp == "Event" )		m_eTargetType = SEARCHTARGET_EVENT;
	else if( strTemp == "Abnormal" )	m_eTargetType = SEARCHTARGET_ABNORMAL;
	else if( strTemp == "Other" )		m_eTargetType = SEARCHTARGET_OTHER;
	else								m_eTargetType = SEARCHTARGET_NONE;

	if( pXMLNode->GetAttr( "IgnoreTargetType" , strTemp ) )
	{
		if( strTemp.empty() == false )
		{
			char * pNextToken = NULL;
			char * pToken = strtok_s( &strTemp[0] , " " , &pNextToken );
			while( pToken != NULL )
			{
				if( strcmp( pToken , "Player" ) == 0 )			m_lstIgnoreTargetType.push_back( SEARCHTARGET_PLAYER );
				else if( strcmp( pToken , "Parent" ) == 0 )		m_lstIgnoreTargetType.push_back( SEARCHTARGET_PARENT );
				else if( strcmp( pToken , "Event" ) == 0 )
				{
					string strEventTemp;
					char * pNextIgnoreEventToken = NULL;
					char * pIgnoreEventToken = NULL;

					m_lstIgnoreTargetType.push_back( SEARCHTARGET_EVENT );

					if( pXMLNode->GetAttr( "IgnoreEventID" , strEventTemp ) == false )
					{
						char strError[256];
						sprintf_s( strError , 256 , "IgnoreEventID 값이 없습니다." );
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

				pToken = strtok_s( NULL , " " , &pNextToken );
			}
		}
	}

	if( m_eTargetType == SEARCHTARGET_EVENT )
	{
		if( pXMLNode->GetAttrDWORD( "EventID" , m_dwOffsetID ) == false )
		{
			char strError[256];
			sprintf_s( strError , 256 , "EventID 값이 없습니다." );
			assert( false && strError );
		}
	}
	if( m_eTargetType == SEARCHTARGET_ABNORMAL )
	{
		if( pXMLNode->GetAttrDWORD( "AbnormalKey" , m_dwOffsetID ) == false )
		{
			char strError[256];
			sprintf_s( strError , 256 , "AbnormalKey 값이 없습니다." );
			assert( false && strError );
		}

		if( pXMLNode->GetAttrBOOL( "IsAbnormalType" , m_bOffsetBranch1 ) == false )
			m_bOffsetBranch1 = false;

	}

	m_eAttackTargetType = C9ATT_ENEMY;
	pXMLNode->GetAttr( "AttackTargetType" , strTemp );

	if( strTemp == "Our" )			m_eAttackTargetType = C9ATT_OUR;
	if( strTemp == "All" )			m_eAttackTargetType = C9ATT_ALL;

	return CAICondition::LoadXML( pXMLNode , pActionData );
}

void CAICondition_SearchAttackTarget::Dump( C9File * pFile , CAIActionData* pActionData )
{
	CAICondition::Dump( pFile , pActionData );

	static const size_t sizeOfData = C9_SIZE_OF_BETWEEN_VALUE( m_fSearchRange , m_bOffsetBranch1 );

	if( pFile->IsSave() )
	{
		pFile->WriteData_SizeT( &m_fSearchRange , sizeOfData );
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
		pFile->ReadData_SizeT( &m_fSearchRange , sizeOfData );
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

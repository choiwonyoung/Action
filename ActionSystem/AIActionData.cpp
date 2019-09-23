#include "stdafx.h"
#include "AIActionData.h"
#include "ActionContantable.h"
#include "ActionDefine.h"
#include "ActionDataInfo.h"
#include "AIActionChart.h"
#include "ActionChart.h"


CAIActionData::CAIOrder::CAIOrder()
: strName( "" )
, strAction( "" )
, actionCode( 0 )
{

}

void CAIActionData::CAIOrder::Dump( C9File * pFile )
{

}

CAIActionData::CAIActionData()
{
}


CAIActionData::~CAIActionData()
{
	m_lstAIParam.resize( 0 );
	m_lstAIValueList.resize( 0 );
	m_lstAIOrderParamList.resize( 0 );
	RSAFE_DELETE_VECTOR( m_lstAIActionChart );
}

bool CAIActionData::LoadXML( const char *pSzFileName )
{
	__super::LoadXML( pSzFileName );

	RXML xml;
	if( LOAD_XML_FROM_PACK( pSzFileName , xml ) == false )
		return false;

	XMLNode * pRootNode = xml.GetRootChild( "C9ActionFile" );
	if( pRootNode == NULL )
		return false;

	// AI 차트 리스트 --------------------------------------------------------------------------------------------
	// 파라메터 정보읽기
	_LoadXML_BaseInfo( pRootNode );

	// 액션 차트 리스트 ----------------------------------------------------------------------------------------
	if( LoadAIActionChart( pRootNode ) == false )
		return false;

	if( _LoadXML_AIActionChart( pRootNode ) == false )
		return false;

	m_lstAIParam.resize( 0 );

	return true;
}


bool CAIActionData::Dump( C9File * pFile )
{
	__super::Dump(pFile);

	if (pFile->IsSave())			// 저장
	{
		//////////////////////////////////////////////////////////////////////////
		// AIBaseInfo -UseActionTimer

		const size_t _szActionTimerValue = m_mapActionTimer.size();	pFile->WriteData_SizeT(_szActionTimerValue);
		for (map< DWORD, vector<UseActionTimer> >::iterator itr = m_mapActionTimer.begin(); itr != m_mapActionTimer.end(); ++itr)
		{
			pFile->WriteData(itr->first);

			pFile->WriteData_SizeT(itr->second.size());
			for (size_t i = 0; i < itr->second.size(); ++i)
			{
				pFile->WriteData(itr->second[i].m_dwActionCode);
				pFile->WriteData(itr->second[i].m_dwSkillKey);
				pFile->WriteData(itr->second[i].m_iUseSkillIndex);
			}
		}

		//////////////////////////////////////////////////////////////////////////
		// AIBaseInfo -SocialActionCode
		const size_t iSocialActionValue = m_lstAISocialActionCode.size(); pFile->WriteData_SizeT(iSocialActionValue);
		if (iSocialActionValue > 0)
			pFile->WriteData_SizeT(&m_lstAISocialActionCode[0], sizeof(DWORD)* iSocialActionValue);
		
		//////////////////////////////////////////////////////////////////////////
		// AI 차트 리스트

		// AI 파라메터
		const size_t _szAIParam = m_lstAIParam.size();	pFile->WriteData_SizeT(_szAIParam);
		for (size_t cAIParam = 0; cAIParam < _szAIParam; ++cAIParam)
			m_lstAIParam[cAIParam].Dump(pFile);

		const size_t _szAIValue = m_lstAIValueList.size();	pFile->WriteData_SizeT(_szAIValue);
		for (size_t cAIValue = 0; cAIValue < _szAIValue; ++cAIValue)
			m_lstAIValueList[cAIValue].Dump(pFile);

		const size_t _szAIOrderParam = m_lstAIOrderParamList.size();	pFile->WriteData_SizeT(_szAIOrderParam);
		for (size_t cAIOrder = 0; cAIOrder < _szAIOrderParam; ++cAIOrder)
			m_lstAIOrderParamList[cAIOrder].Dump(pFile);

		const size_t _szBoneLinkedAIValue = m_lstAIBoneLinkedAIValue.size();	pFile->WriteData_SizeT(_szBoneLinkedAIValue);
		for (size_t cAIBone = 0; cAIBone < _szBoneLinkedAIValue; ++cAIBone)
		{
			pFile->WriteData(m_lstAIBoneLinkedAIValue[cAIBone].dwBoneHash);
			pFile->WriteData(m_lstAIBoneLinkedAIValue[cAIBone].dwAIValueNameHahs);
		}

		// AI Action
		const size_t _szAIActionChart = m_lstAIActionChart.size();		pFile->WriteData_SizeT(_szAIActionChart);
		for (size_t i = 0; i < _szAIActionChart; ++i)
		{
			CAIActionChart * pAIActionChart = m_lstAIActionChart[i];
			pFile->WriteData((int)pAIActionChart->GetType());
			pAIActionChart->Dump(pFile, this);
		}
	}
	else							// 읽기
	{
		// 버젼 검사
		UINT uiActionFileVersion = 0;	pFile->ReadData(uiActionFileVersion);
		if (uiActionFileVersion != CActionData::VERSION)
		{
			char strError[256];
			sprintf_s( strError , 256 ,"액션 파일의 버젼이 다릅니다.\n파일명 : %s", pFile->GetFileName() );
			assert( false && strError );
			MessageBoxA(NULL, strError, "액션 파일 버젼 에러", MB_OK);
			return false;
		}

		//////////////////////////////////////////////////////////////////////////
		// 액션 데이터(기본정보)
		size_t _szActionDataInfo = 0;		pFile->ReadData_SizeT(_szActionDataInfo);
		for (size_t i = 0; i < _szActionDataInfo; ++i)
		{
			CActionDataInfo * pActionDataInfo = new CActionDataInfo;
			pActionDataInfo->Dump(pFile, m_lstPreloadEffect, m_lstPreloadSound);
			m_ActionDataInfoList.push_back(pActionDataInfo);
		}

		// 플레이어 액션 변수 리스트
		size_t _szPlayerValue = 0;	pFile->ReadData_SizeT(_szPlayerValue);
		m_lstPlayerValueList.resize(_szPlayerValue);
		for (size_t cValue = 0; cValue < _szPlayerValue; ++cValue)
			m_lstPlayerValueList[cValue].Dump(pFile);


		size_t _szPlayerServerValue = 0;	pFile->ReadData_SizeT(_szPlayerServerValue);
		m_lstPlayerServerValueList.clear();
		DWORD dwNameHash = 0;
		DWORD dwPSValueKey = 0;
		for (size_t cValue = 0; cValue < _szPlayerServerValue; ++cValue)
		{
			pFile->ReadData(dwNameHash);
			pFile->ReadData(dwPSValueKey);

			m_lstPlayerServerValueList.insert(map< DWORD, DWORD >::value_type(dwNameHash, dwPSValueKey));
		}

		//////////////////////////////////////////////////////////////////////////
		// AIBaseInfo -UseActionTimer
		size_t _szActionTimerValue = 0;	pFile->ReadData_SizeT(_szActionTimerValue);
		for (size_t cValue = 0; cValue < _szActionTimerValue; ++cValue)
		{
			DWORD dwName, dwActionCode, dwSkillkey; int iIndex;
			pFile->ReadData(dwName);

			size_t iTimerSize = 0;
			pFile->ReadData_SizeT(iTimerSize);
			for (size_t i = 0; i < iTimerSize; ++i)
			{
				pFile->ReadData(dwActionCode);
				pFile->ReadData(dwSkillkey);
				pFile->ReadData(iIndex);

				m_mapActionTimer[dwName].push_back(UseActionTimer(dwActionCode, dwSkillkey, iIndex));
			}
		}

		//////////////////////////////////////////////////////////////////////////
		// AIBaseInfo -SocialActionCode
		size_t iSocialActionValue = 0; pFile->ReadData_SizeT(iSocialActionValue); m_lstAISocialActionCode.resize(iSocialActionValue);
		if (iSocialActionValue > 0)
			pFile->ReadData_SizeT(&m_lstAISocialActionCode[0], sizeof(DWORD)* iSocialActionValue);


		// 액션 차트 리스트
		size_t _szActionChart = 0;	pFile->ReadData_SizeT(_szActionChart);
		for (size_t cAction = 0; cAction < _szActionChart; ++cAction)
		{
			CActionChart * pActionChart = new CActionChart(*this);
			pActionChart->Dump(pFile, m_lstPreloadEffect, m_lstPreloadSound);
			m_lstActionChart.push_back(pActionChart);
		}

		//////////////////////////////////////////////////////////////////////////
		// AI 차트 리스트

		// AI 파라메터
		size_t _szAIParam = 0;	pFile->ReadData_SizeT(_szAIParam);
		m_lstAIParam.resize(_szAIParam);
		for (size_t cAIParam = 0; cAIParam < _szAIParam; ++cAIParam)
			m_lstAIParam[cAIParam].Dump(pFile);

		size_t _szAIValue = 0;	pFile->ReadData_SizeT(_szAIValue);
		m_lstAIValueList.resize(_szAIValue);
		for (size_t cAIValue = 0; cAIValue < _szAIValue; ++cAIValue)
			m_lstAIValueList[cAIValue].Dump(pFile);

		size_t _szAIOrderParam = 0;	pFile->ReadData_SizeT(_szAIOrderParam);
		m_lstAIOrderParamList.resize(_szAIOrderParam);
		for (size_t cAIOrder = 0; cAIOrder < _szAIOrderParam; ++cAIOrder)
			m_lstAIOrderParamList[cAIOrder].Dump(pFile);

		size_t _szBoneLinkedAIValue = 0;	pFile->ReadData_SizeT(_szBoneLinkedAIValue);
		m_lstAIBoneLinkedAIValue.resize(_szBoneLinkedAIValue);
		for (size_t cAIBone = 0; cAIBone < _szBoneLinkedAIValue; ++cAIBone)
		{
			pFile->ReadData(m_lstAIBoneLinkedAIValue[cAIBone].dwBoneHash);
			pFile->ReadData(m_lstAIBoneLinkedAIValue[cAIBone].dwAIValueNameHahs);
		}

		// AI Action
		size_t _szAIActionChar = 0;		pFile->ReadData_SizeT(_szAIActionChar);
		for (size_t cAIAction = 0; cAIAction < _szAIActionChar; ++cAIAction)
		{
			AIActionChartType _Type;		pFile->ReadData((int &)_Type);
			CAIActionChart * pAIActionChart = CAIActionChart::Create_AIActionChart(_Type);
			assert(pAIActionChart);
			pAIActionChart->Dump(pFile, this);

			m_lstAIActionChart.push_back(pAIActionChart);
		}
	}

	return true;
}

void CAIActionData::SetAiActionChartList( HashMap_AIActionList &aiActionChartList , const DWORD dwActionIndexHashCode , bool isPvPMapAction , const DWORD dwPVPActionIndexHashCode )
{
	aiActionChartList.clear();

	HashMap_AIActionList pvpAiActionChartList;

	if( dwPVPActionIndexHashCode != 0 && isPvPMapAction )
	{
		for( size_t i = 0; i < m_lstAIActionChart.size(); ++i )
		{
			CAIActionChart * pAIActionChart = m_lstAIActionChart[i];
			// 액션 인덱스 검사
			for( size_t cActionIndex = 0; cActionIndex < pAIActionChart->m_lstActionIndexHashCode.size(); ++cActionIndex )
			{
				if( dwPVPActionIndexHashCode == pAIActionChart->m_lstActionIndexHashCode[cActionIndex] )
				{
					HashMap_AIActionList::_Pairib _pairib = pvpAiActionChartList.insert( HashMap_AIActionList::value_type( pAIActionChart->m_dwHashcode , pAIActionChart ) );

					char strError[256];
					sprintf_s( strError , 256 , "동일한 이름의 AI 액션이 이미 존재합니다.\n\n"
							   "기획팀에 문의하세요.\n\n"
							   "AI Action File Name : %s\n"
							   "AI Action Name : %s\n" ,
							   m_strFileName.c_str() , pAIActionChart->m_strName.c_str() );
					assert( _pairib.second && strError );
					break;
				}
			}
		}
	}

	for( size_t i = 0; i < m_lstAIActionChart.size(); ++i )
	{
		CAIActionChart * pAIActionChart = m_lstAIActionChart[i];
		// 액션 인덱스 검사
		for( size_t cActionIndex = 0; cActionIndex < pAIActionChart->m_lstActionIndexHashCode.size(); ++cActionIndex )
		{
			if( dwActionIndexHashCode == pAIActionChart->m_lstActionIndexHashCode[cActionIndex] )
			{
				HashMap_AIActionList_ConstIter pos = pvpAiActionChartList.find( pAIActionChart->m_dwHashcode );
				if( pos == pvpAiActionChartList.end() )
				{
					HashMap_AIActionList::_Pairib _pairib = aiActionChartList.insert( HashMap_AIActionList::value_type( pAIActionChart->m_dwHashcode , pAIActionChart ) );

					char strError[256];
					sprintf_s( strError , 256 , "동일한 이름의 AI 액션이 이미 존재합니다.\n\n"
							   "기획팀에 문의하세요.\n\n"
							   "AI Action File Name : %s\n"
							   "AI Action Name : %s\n" ,
							   m_strFileName.c_str() , pAIActionChart->m_strName.c_str() );
					assert( _pairib.second && strError );

					break;
				}
			}
		}
	}

	for( HashMap_AIActionList_Iter pos = pvpAiActionChartList.begin(); pos != pvpAiActionChartList.end(); ++pos )
	{
		HashMap_AIActionList::_Pairib _pairib = aiActionChartList.insert( HashMap_AIActionList::value_type( pos->first , pos->second ) );

		char strError[256];
		sprintf_s( strError , 256 , "동일한 이름의 AI 액션이 이미 존재합니다.\n\n"
				   "기획팀에 문의하세요.\n\n"
				   "AI Action File Name : %s\n"
				   "AI Action Name : %s\n" ,
				   m_strFileName.c_str() , pos->second->m_strName.c_str() );
		assert( _pairib.second && strError );
	}

	for( size_t i = 0; i < m_lstAIActionChart.size(); ++i )
	{
		CAIActionChart* pAIActionChart = m_lstAIActionChart[i];

		if( pAIActionChart->m_lstActionIndexHashCode.empty() )
		{
			HashMap_AIActionList_ConstIter pos = aiActionChartList.find( pAIActionChart->m_dwHashcode );
			if( pos == aiActionChartList.end() )
			{
				aiActionChartList[pAIActionChart->m_dwHashcode] = pAIActionChart;
			}
		}
	}
}

bool CAIActionData::LoadAIActionChart( XMLNode * pRootNode )
{
	XMLNodes AIActionNodes = pRootNode->GetChilds( "AIAction" );
	string strActionType;
	for( size_t cAIAction = 0; cAIAction < AIActionNodes.size(); ++cAIAction )
	{
		XMLNode * pAIActionNode = AIActionNodes[cAIAction];
		AIActionChartType type				= CAIActionChart::Parse_GetAIActionChartType( pAIActionNode->GetAttr( "ActionType" ).c_str() );
		CAIActionChart * pAIActionChart		= CAIActionChart::Create_AIActionChart( type );
		if( pAIActionChart )
		{
			if( pAIActionChart->LoadXML( pAIActionNode , this ) == false )
			{
				char strError[256];
				sprintf_s( strError , 256 , "AI 액션 정보 읽기 실패\n"
						   "기획팀에 문의 하세요.\n\n"
						   "Action File Name : %s\n" , m_strFileName.c_str() );
				assert( false && strError );

				RSAFE_DELETE( pAIActionChart );
				return false;
			}

			m_lstAIActionChart.push_back( pAIActionChart );
		}
	}
	return true;
}

void CAIActionData::InitPlayerValue( hash_map<DWORD , int>& mapPlayerValue )
{
	for (size_t i = 0; i<m_lstAIValueList.size(); ++i)
	{
		const CValueParam & _valueParam = m_lstAIValueList[i];
		mapPlayerValue.insert(hash_map<DWORD, int>::value_type(_valueParam.dwHash, _valueParam.iValue));
	}
}

bool CAIActionData::GetParamValue(const char * pszTemp, int & iValue)
{
	iValue = (int)atoi(pszTemp);

	if (iValue != 0 || strcmp(pszTemp, "0") == 0)
		return true;

	for (size_t i = 0; i < m_lstAIParam.size(); i++)
	{
		if (m_lstAIParam[i].strName == pszTemp)
		{
			iValue = m_lstAIParam[i].iValue;
			return true;
		}
	}

	char strError[256];
	sprintf_s( strError , 256 ,  "해당 param 이름을 찾을수 없습니다.(%s)\n", pszTemp );
	assert( false && strError );

	return false;
}

void CAIActionData::InitAIValue( hash_map<DWORD , int> &aiValuList , hash_map<DWORD , DWORD> &aiDBoneAIValueList )
{
	for( size_t i = 0; i < m_lstAIValueList.size(); ++i )
	{
		const CValueParam & _valueParam = m_lstAIValueList[i];
		aiValuList.insert( hash_map<DWORD , int>::value_type( _valueParam.dwHash , _valueParam.iValue ) );
	}
}

void CAIActionData::_LoadXML_BaseInfo( XMLNode * pRootNode )
{
	XMLNode * pAIBaseNode = pRootNode->GetChild( "AIBaseInfo" );
	if( pAIBaseNode )
	{
		_LoadXML_Param( pAIBaseNode );

		_LoadXML_AIValue( pAIBaseNode );

		_LoadXML_Order( pAIBaseNode );

		_LoadXML_UseActionTimer( pAIBaseNode );

		_LoadXML_SocialActionCode( pAIBaseNode );
	}
}

bool CAIActionData::_LoadXML_AIActionChart( XMLNode * pRootNode )
{
	XMLNodes AddActionFileNodes = pRootNode->GetChilds( "AddActionFile" );
	for( size_t cAddActionFile = 0; cAddActionFile < AddActionFileNodes.size(); ++cAddActionFile )
	{
		string strAddActionFileName;

		XMLNode * pActionFileNode = AddActionFileNodes[cAddActionFile];
		if( pActionFileNode->GetAttr( "FileName" , strAddActionFileName ) )
		{
			RXML subXml;
			if( LOAD_XML_FROM_PACK( strAddActionFileName.c_str() , subXml ) == false )
				return false;

			XMLNode * pSubRootNode = subXml.GetRootChild( "C9ActionFile" );
			if( pSubRootNode )
			{
				if( LoadAIActionChart( pSubRootNode ) == false )
					return false;
			}
		}
	}

	return true;
}

void CAIActionData::_LoadXML_Param( XMLNode * pAIBaseNode )
{
	XMLNodes AIParamNodes = pAIBaseNode->GetChilds( "Param" );
	for( size_t cAIParam = 0; cAIParam < AIParamNodes.size(); ++cAIParam )
	{
		CValueParam AIParam;
		if( AIParam.LoadXML( AIParamNodes[cAIParam] ) )
			m_lstAIParam.push_back( AIParam );
	}
}


void CAIActionData::_LoadXML_SocialActionCode( XMLNode * pAIBaseNode )
{
	XMLNodes _UseSocialAction = pAIBaseNode->GetChilds( "SocialActionCode" );
	if( _UseSocialAction.empty() == false )
	{
		m_lstAISocialActionCode.clear();
		size_t nNodeSize = _UseSocialAction.size();
		for( size_t cAIValue = 0; cAIValue < nNodeSize; ++cAIValue )
		{
			string strName;
			XMLNode * pAIValueNode = _UseSocialAction[cAIValue];
			pAIValueNode->GetAttr( "AIAction" , strName );
			m_lstAISocialActionCode.push_back( CCrc32Static::StringCrc32( strName.c_str() ) );
		}
	}
}

void CAIActionData::_LoadXML_UseActionTimer( XMLNode * pAIBaseNode )
{
	XMLNodes _UseActionTimer = pAIBaseNode->GetChilds( "UseActionTimer" );
	if( _UseActionTimer.empty() == false )
	{
		size_t nNodeSize = _UseActionTimer.size();
		for( size_t cAIValue = 0; cAIValue < nNodeSize; ++cAIValue )
		{
			string strName;
			XMLNode * pAIValueNode = _UseActionTimer[cAIValue];
			pAIValueNode->GetAttr( "Name" , strName );
			DWORD dwName = CCrc32Static::StringCrc32( strName.c_str() );

			pAIValueNode->GetAttr( "ActionCode" , strName );
			DWORD dwActionCode = CCrc32Static::StringCrc32( strName.c_str() );

			pAIValueNode->GetAttr( "SkillKey" , strName );
			int iUseMonsterSkillIdx = 0;
			DWORD dwSkillKey = 0;

			if( strName.find( "MonsterSkillKey" ) != string::npos )
			{
				size_t idx = strlen( "MonsterSkillKey" );
				iUseMonsterSkillIdx = atoi( &strName[idx] );
			}
			// 펫 관련 스킬 인덱스 추가 
			else if( strName.find( "PetSkillKey" ) != string::npos )
			{
				size_t idx = strlen( "PetSkillKey" );
				iUseMonsterSkillIdx = atoi( &strName[idx] );
			}
			else
			{
				dwSkillKey = ( DWORD )atoi( strName.c_str() );
			}

			m_mapActionTimer[dwName].push_back( UseActionTimer( dwActionCode , dwSkillKey , iUseMonsterSkillIdx ) );
		}

	}
}


void CAIActionData::_LoadXML_Order( XMLNode * pAIBaseNode )
{
	XMLNodes AIOrderNodes = pAIBaseNode->GetChilds( "Order" );
	for( size_t cAIValue = 0; cAIValue < AIOrderNodes.size(); ++cAIValue )
	{
		XMLNode * pAIOrderNode = AIOrderNodes[cAIValue];
		CAIOrder _AIOrder;
		if( pAIOrderNode->GetAttr( "Name" , _AIOrder.strName ) &&
			pAIOrderNode->GetAttr( "AIAction" , _AIOrder.strAction ) )
			m_lstAIOrderParamList.push_back( _AIOrder );
	}
}

void CAIActionData::_LoadXML_AIValue( XMLNode * pAIBaseNode )
{
	XMLNodes AIValueNodes = pAIBaseNode->GetChilds( "AIValue" );
	for( size_t cAIValue = 0; cAIValue < AIValueNodes.size(); ++cAIValue )
	{
		CValueParam AIParam;
		if( AIParam.LoadXML( AIValueNodes[cAIValue] ) )
			m_lstAIValueList.push_back( AIParam );
	}
}
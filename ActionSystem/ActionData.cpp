#include "stdafx.h"
#include "ActionData.h"
#include "ActionDataInfo.h"
#include "ActionContantable.h"
#include "ActionFunction.h"
#include "ActionChart.h"
#include "ActionBackGroundBranch.h"
#include "FrameEvent.h"

const UINT CActionData::VERSION = 1;

CActionData::CActionData()
: m_iRef( 0 )
, m_strFileName( "" )
, m_dwHashCode( 0 )
{
}

CActionData::~CActionData()
{
	RSAFE_DELETE_VECTOR( m_ActionDataInfoList );
	RSAFE_DELETE_VECTOR( m_lstActionChart );

	m_lstPlayerValueList.resize( 0 );
	m_lstPlayerServerValueList.clear();
}

bool CActionData::LoadXML( const char *pSzFileName )
{
	m_strFileName = pSzFileName;
	m_dwHashCode = CCrc32Static::StringCrc32( pSzFileName );

	// 텍스트 읽기
	RXML xml;
	if( LOAD_XML_FROM_PACK( pSzFileName , xml ) == false )
		return false;

	XMLNode * pRootNode = xml.GetRootChild( "C9ActionFile" );
	if( pRootNode == NULL )
		return false;

	if( _LoadXML_BaseActionInfo( pRootNode , pSzFileName ) == false )
		return false;

	_LoadXML_PlayerValue( pRootNode );

	// 플레이어 액션 변수(서버)
	_LoadXML_PlayerServerValue( pRootNode );	

	// ActionFunction 로드
	HashMap_ActionFunction mapActionFunction;
	if( LoadActionFunction( pRootNode , mapActionFunction ) == false )
		return false;

	if( _LoadXML_AddActionFile_LoadFunction( pRootNode , mapActionFunction ) == false )
		return false;

	// 액션 차트 리스트 ----------------------------------------------------------------------------------------
	if( LoadActionChart( pRootNode , pRootNode , mapActionFunction ) == false )
		return false;

	if( _LoadXML_AddActionFile_LoadActionChart( pRootNode , mapActionFunction ) == false )
		return false;

	// ActionFunction 을 비운다.
	for( HashMap_ActionFunction_Iter pos = mapActionFunction.begin(); pos != mapActionFunction.end(); ++pos )
	{
		CActionFunction * pActionFunction = pos->second;
		delete pActionFunction;
	}
	mapActionFunction.clear();
	
	return true;
}

bool CActionData::SaveBinary(const char * pszFullPath)
{
	C9File file;
	if (file.Save(pszFullPath) == false)
	{
		char strError[256];
		sprintf_s( strError , 256 , "액션 파일 바이너리 저장 실패\n파일이 열려 있을 수 있습니다.\n\n"
				   "Action File Name : %s" ,
				   pszFullPath );
		assert( false && strError );
		return false;
	}

	// 파일명 해쉬 코드 저장
	{
		string strUpperFileName = pszFullPath;

		std::transform( strUpperFileName.begin() , strUpperFileName.end() , strUpperFileName.begin() , ::toupper );
		const DWORD dwFileNameHashCode = CCrc32Static::StringCrc32(strUpperFileName.c_str());
		file.WriteData(dwFileNameHashCode);
	}

	if (Dump(&file) == false)
		return false;

	file.Close();



	return true;	
}

bool CActionData::LoadBinary(const char * pSzFileName)
{
	m_strFileName = pSzFileName;
	m_dwHashCode = CCrc32Static::StringCrc32(pSzFileName);

	string strLoadFileName = pSzFileName;
	strLoadFileName = Action::ActionString::ToUpper( strLoadFileName );

	const size_t index = strLoadFileName.find( ".XMA" );
	if( index != string::npos )
		strLoadFileName.replace( index , strlen( ".XMA" ) , ".C9MA" );

	DWORD dwFileKey = 0;
	C9ReadBuffer file;
	if ( LOAD_BINARY_FROM_PACK(strLoadFileName.c_str(), file, true) == false )
		return false;

	// 파일명 헤쉬 코드 검사
	{
		DWORD dwFileNameHashCode = 0;		
		file.ReadData(dwFileNameHashCode);
		if (dwFileNameHashCode == 0)
		{
			char strError[256];
			sprintf_s( strError , 256 , "액션파일 로드 실패\n액션파일의 액션파일이 변조 되었습니다.\n"
					   "액션파일 버젼업을 실행하여 바이너리를 다시 저장하십시오.\n\n"
					   "Action File Name : %s" ,
					   pSzFileName );
			assert( false && strError );
			MessageBoxA(NULL, "액션파일 로드 실패", "액션파일이 변조 되었습니다.", MB_OK);
			return false;
		}
	}

	if (Dump(&file) == false)
		return false;

	return true;
}

bool CActionData::Dump(C9File * pFile)
{
	if (pFile->IsSave())			// 저장
	{
		// 버젼 저장
		pFile->WriteData(CActionData::VERSION);

		//////////////////////////////////////////////////////////////////////////
		// 액션 데이터(기본정보)
		const size_t _szActionDataInfo = m_ActionDataInfoList.size();		pFile->WriteData_SizeT(_szActionDataInfo);
		for (size_t i = 0; i < _szActionDataInfo; ++i)
			m_ActionDataInfoList[i]->Dump(pFile, m_lstPreloadEffect, m_lstPreloadSound);

		// 플레이어 액션 변수 리스트
		const size_t _szPlayerValue = m_lstPlayerValueList.size();	pFile->WriteData_SizeT(_szPlayerValue);
		for (size_t cValue = 0; cValue < _szPlayerValue; ++cValue)
			m_lstPlayerValueList[cValue].Dump(pFile);

		const size_t _szPlayerServerValue = m_lstPlayerServerValueList.size();	pFile->WriteData_SizeT(_szPlayerServerValue);
		for (map< DWORD, DWORD >::iterator itr = m_lstPlayerServerValueList.begin(); itr != m_lstPlayerServerValueList.end(); ++itr)
		{
			pFile->WriteData(itr->first);
			pFile->WriteData(itr->second);
		}

		// 액션 차트 리스트
		const size_t _szActionChart = m_lstActionChart.size();	pFile->WriteData_SizeT(_szActionChart);
		for (size_t i = 0; i<_szActionChart; ++i)
		{
			CActionChart * pActionChart = m_lstActionChart[i];
			pActionChart->Dump(pFile, m_lstPreloadEffect, m_lstPreloadSound);
		}
	}
	else							// 읽기
	{
		// 버젼 검사
		UINT uiActionFileVersion = 0;	pFile->ReadData(uiActionFileVersion);
		if (uiActionFileVersion != CActionData::VERSION)
		{
			char strError[256];
			sprintf_s( strError , 256 , "액션 파일의 버젼이 다릅니다.\n파일명 : %s", pFile->GetFileName() );
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

		// 액션 차트 리스트
		size_t _szActionChart = 0;	pFile->ReadData_SizeT(_szActionChart);
		for (size_t cAction = 0; cAction < _szActionChart; ++cAction)
		{
			CActionChart * pActionChart = new CActionChart(*this);
			pActionChart->Dump(pFile, m_lstPreloadEffect, m_lstPreloadSound);
			m_lstActionChart.push_back(pActionChart);
		}
	}

	return true;
}

bool CActionData::LoadActionFunction(XMLNode * pRootNode, HashMap_ActionFunction & mapActionFunction)
{
	XMLNodes ActionFunctionNodes = pRootNode->GetChilds("ActionFunction");
	for (size_t cFunction = 0; cFunction < ActionFunctionNodes.size(); ++cFunction)
	{
		XMLNode * pFunctionNode = ActionFunctionNodes[cFunction];

		CActionFunction * pActionFunction = new CActionFunction();

		pActionFunction->m_strName = pFunctionNode->Value();

		// 브랜치
		XMLNodes branchNodes = pFunctionNode->GetChilds("ActionBranch");
		for (size_t cBranch = 0; cBranch < branchNodes.size(); ++cBranch)
		{
			XMLNode * pBranchNode = branchNodes[cBranch];
			CActionBranch * pActionBranch = new CActionBranch;

			if (pActionBranch->LoadXML(pBranchNode))
				pActionFunction->m_lstBranch.push_back(pActionBranch);
			else
				RSAFE_DELETE(pActionBranch);
		}

		// 백그라운드브랜치
		XMLNodes backGroundbranchNodes = pFunctionNode->GetChilds("ActionBackGroundBranch");
		for (size_t cBranch = 0; cBranch < backGroundbranchNodes.size(); ++cBranch)
		{
			XMLNode * pBackGroundBranchNode = backGroundbranchNodes[cBranch];
			CActionBackGroundBranch * pActionBackGroundBranch = new CActionBackGroundBranch;

			if (pActionBackGroundBranch->LoadXML(pBackGroundBranchNode))
				pActionFunction->m_lstBranch.push_back(pActionBackGroundBranch);
			else
				RSAFE_DELETE(pActionBackGroundBranch);
		}

		// 프레임 이벤트
		XMLNodes eventNodes = pFunctionNode->GetChilds("FrameEvent");
		for (size_t cEvent = 0; cEvent < eventNodes.size(); ++cEvent)
		{
			XMLNode * pEventNode = eventNodes[cEvent];

			CFrameEventType frameEventType	= CFrameEvent::Parse_GetFrameEventType(pEventNode->GetAttr("Type").c_str());
			CFrameEvent* pFrameEvent		= CFrameEvent::Create_FrameEvent(frameEventType, *this, NULL);
			if (pFrameEvent == NULL)
				continue;

			if (pFrameEvent->LoadXML(pEventNode, m_lstPreloadEffect, m_lstPreloadSound))
				pActionFunction->m_lstFrameEvent.push_back(pFrameEvent);
			else
				RSAFE_DELETE(pFrameEvent);
		}

		const DWORD dwFunctionNameHashCode = CCrc32Static::StringCrc32(pActionFunction->m_strName.c_str());

		HashMap_ActionFunction::_Pairib _pairib = mapActionFunction.insert(HashMap_ActionFunction::value_type(dwFunctionNameHashCode, pActionFunction));
		if (_pairib.second == false)
		{
			char strError[256];
			sprintf_s( strError , 256 , "동일한 이름의 ActionFunction 이 존재 합니다.\n"
					   "기획팀에 문의하세요.\n\n"
					   "ActionName : %s" ,
					   pActionFunction->m_strName.c_str() );
			assert( false && strError );

			RSAFE_DELETE(pActionFunction);
		}
	}

	return true;
}

bool CActionData::LoadActionChart(XMLNode * pRootNode, XMLNode * pFunctionRootNode, HashMap_ActionFunction & mapActionFunction)
{
	XMLNodes actionNodes = pRootNode->GetChilds("Action");
	for (UINT cAction = 0; cAction < actionNodes.size(); ++cAction)
	{
		XMLNode * pActionNode = actionNodes[cAction];
		CActionChart * pActionChart = new CActionChart(*this);
		if (pActionChart->LoadXML(pActionNode, pFunctionRootNode, mapActionFunction, m_lstPreloadEffect, m_lstPreloadSound) == false)
		{
			char strError[256];
			sprintf_s( strError , 256 , "액션 정보 읽기 실패\n"
					   "기획팀에 문의하세요.\n\n"
					   "Action File Name : %s\n" ,
					   m_strFileName.c_str() );
			assert( false && strError );

			RSAFE_DELETE(pActionChart);

			return false;
		}
		// 액션 복사 작업 처리
		if (CopyActionChart(pActionChart) == false)
		{
			m_lstActionChart.push_back(pActionChart);
		}
	}	
	
	return true;
}

bool CActionData::CopyActionChart(CActionChart * pActionChart)
{
	if (pActionChart->m_CopyActionChartValue.m_iCopyCount > 1)
	{
		for (int i = 0; i<pActionChart->m_CopyActionChartValue.m_iCopyCount; i++)
		{
			CActionChart * pCopyActionChart = new CActionChart(*pActionChart);
			pCopyActionChart->CopyActionChartLevel(pActionChart, i);
			m_lstActionChart.push_back(pCopyActionChart);
		}
		RSAFE_DELETE(pActionChart);
		return true;
	}
	return false;
}

CActionDataInfo* CActionData::FindActionDataInfo(const DWORD dwActionIndexHashCode, bool IsPvPMapAction , const DWORD dwPVPActionIndexHashCode )
{
	CActionDataInfo* pActionBaseDataInfo = NULL;
	CActionDataInfo* pSelectActionDataInfo = NULL;

	if ( dwPVPActionIndexHashCode != 0 && IsPvPMapAction )
	{
		for (size_t cActionDataInfo = 0; cActionDataInfo < m_ActionDataInfoList.size(); ++cActionDataInfo)
		{
			CActionDataInfo * pActionDataInfo = m_ActionDataInfoList[cActionDataInfo];
			for (size_t cActionIndex = 0; cActionIndex < pActionDataInfo->m_lstActionIndexHashCode.size(); ++cActionIndex)
			{
				if (dwPVPActionIndexHashCode == pActionDataInfo->m_lstActionIndexHashCode[cActionIndex])
				{
					pSelectActionDataInfo = pActionDataInfo;
					break;
				}
			}

			if (pSelectActionDataInfo != NULL)
				break;
		}
	}

	if (pSelectActionDataInfo == NULL)
	{
		for (size_t cActionDataInfo = 0; cActionDataInfo < m_ActionDataInfoList.size(); ++cActionDataInfo)
		{
			CActionDataInfo * pActionDataInfo = m_ActionDataInfoList[cActionDataInfo];
			if (pActionDataInfo->m_lstActionIndexHashCode.empty())
			{
				pActionBaseDataInfo = pActionDataInfo;
				if (dwActionIndexHashCode == 0)
					break;

				continue;
			}

			if (dwActionIndexHashCode != 0)
			{
				for (size_t cActionIndex = 0; cActionIndex < pActionDataInfo->m_lstActionIndexHashCode.size(); ++cActionIndex)
				{
					if (dwActionIndexHashCode == pActionDataInfo->m_lstActionIndexHashCode[cActionIndex])
					{
						pSelectActionDataInfo = pActionDataInfo;
						break;
					}
				}
			}

			if (pSelectActionDataInfo != NULL)
				break;
		}
	}

	if (pSelectActionDataInfo == NULL)
		pSelectActionDataInfo = pActionBaseDataInfo;

	char strError[256];
	sprintf_s( strError , 256 , "캐릭터 데이터에 설정된 '액션인덱스'가 액션스크립트에 존재 하지 않습니다.\n\n"
			   "ActionFileName : %s" ,
			   m_strFileName.c_str() );
	assert( false && strError );

	return pSelectActionDataInfo;
}

void CActionData::SetActionChartList(HashMap_ActionList & actionChartList, const DWORD dwActionIndexHashCode, bool IsPvPMapAction , const DWORD dwPVPActionIndexHashCode)
{
	actionChartList.clear();

	HashMap_ActionList pvpActionChartList;
	if (dwPVPActionIndexHashCode != 0 && IsPvPMapAction )
	{
		for (size_t i = 0; i<m_lstActionChart.size(); i++)
		{
			CActionChart * pActionChart = m_lstActionChart[i];

			// 액션 인덱스 검사
			for (size_t cActionIndex = 0; cActionIndex < pActionChart->m_lstActionIndexHashCode.size(); ++cActionIndex)
			{
				if (dwPVPActionIndexHashCode == pActionChart->m_lstActionIndexHashCode[cActionIndex])
				{
					HashMap_ActionList::_Pairib _pairib = pvpActionChartList.insert(HashMap_ActionList::value_type(pActionChart->m_dwHashcode, pActionChart));

					char strError[256];
					sprintf_s( strError , 256 , "동일한 이름의 액션이 이미 존재합니다.\n"
							   "기획팀에 문의하세요.\n\n"
							   "Action File Name : %s\n"
							   "Action Name : %s\n" ,
							   m_strFileName.c_str() , pActionChart->m_strActionName.c_str() );
					assert( _pairib.second && strError );
					break;
				}
			}
		}
	}

	for (size_t i = 0; i<m_lstActionChart.size(); i++)
	{
		CActionChart * pActionChart = m_lstActionChart[i];

		// 액션 인덱스 검사
		for (size_t cActionIndex = 0; cActionIndex < pActionChart->m_lstActionIndexHashCode.size(); ++cActionIndex)
		{
			if (dwActionIndexHashCode == pActionChart->m_lstActionIndexHashCode[cActionIndex])
			{
				HashMap_ActionList_ConstIter pos = pvpActionChartList.find(pActionChart->m_dwHashcode);
				if (pos == pvpActionChartList.end())
				{
					HashMap_ActionList::_Pairib _pairib = actionChartList.insert(HashMap_ActionList::value_type(pActionChart->m_dwHashcode, pActionChart));

					char strError[256];
					sprintf_s( strError , 256 , "동일한 이름의 액션이 이미 존재합니다.\n"
							   "기획팀에 문의하세요.\n\n"
							   "Action File Name : %s\n"
							   "Action Name : %s\n" ,
							   m_strFileName.c_str() , pActionChart->m_strActionName.c_str() );
					assert( _pairib.second && strError );
					break;
				}
			}
		}
	}

	for (HashMap_ActionList_Iter pos = pvpActionChartList.begin(); pos != pvpActionChartList.end(); ++pos)
	{
		HashMap_ActionList::_Pairib _pairib = actionChartList.insert(HashMap_ActionList::value_type(pos->first, pos->second));

		char strError[256];
		sprintf_s( strError , 256 , "동일한 이름의 액션이 이미 존재합니다.\n"
				   "기획팀에 문의하세요.\n\n"
				   "Action File Name : %s\n"
				   "Action Name : %s\n" ,
				   m_strFileName.c_str() , pos->second->m_strActionName.c_str() );
		assert( _pairib.second && strError );
	}

	for (size_t i = 0; i<m_lstActionChart.size(); i++)
	{
		CActionChart *pActionChart = m_lstActionChart[i];

		if (pActionChart->m_lstActionIndexHashCode.empty())
		{
			HashMap_ActionList_ConstIter pos = actionChartList.find(pActionChart->m_dwHashcode);
			if (pos == actionChartList.end())
			{
				actionChartList[pActionChart->m_dwHashcode] = pActionChart;
			}
		}
	}
}

C9ReadBuffer::BufferPtr CActionData::GetReadBuffer( DWORD dwSize )
{
	char * pBuffer = static_cast< char * >( malloc( sizeof( char ) * dwSize + 2 ) );
	if( pBuffer == NULL )
	{
		MessageBoxA( NULL , "Out of memory!" , "C9Error" , MB_OK );
	}

	// 버퍼 끝처리
	pBuffer[dwSize] = 0;
	pBuffer[dwSize + 1] = 0;
	return C9ReadBuffer::BufferPtr( pBuffer , Action::ActionString::BufferFree );
	

}

bool CActionData::LOAD_XML_FROM_PACK( const char * pStrFileName , RXML & xml )
{
	int nTextSize = 0;
	C9File file;
	if( file.Open( pStrFileName ) == false )
		return false;

	C9ReadBuffer::BufferPtr spBuffer = GetReadBuffer( file.GetSize() );

	if( file.ReadData( spBuffer.get() , file.GetSize() ) == false )
		return false;

	file.Close();
		
	if( false == xml.LoadBuffer( spBuffer.get() , false ) )
	{
		char strError[256];
		sprintf_s( strError , 256 , "[ %s file]\n" , pStrFileName );
		::MessageBoxA( NULL , strError , "Load XML Error" , 0 );
		return false;
	}

	return true;
}

bool CActionData::LOAD_BINARY_FROM_PACK( const char * pStrFileName , C9ReadBuffer & laodBinary , bool bMemSet )
{
	UNUSED_ARG( bMemSet );

	int iPackBufferSize;
	C9File file;
	if( file.Open( pStrFileName ) == false )
		return false;

	C9ReadBuffer::BufferPtr spBuffer = GetReadBuffer( file.GetSize() );
	iPackBufferSize = file.GetSize();

	if( file.ReadData( spBuffer.get() , file.GetSize() ) == false )
		return false;

	file.Close();

	laodBinary.SetReadBuffer( pStrFileName , spBuffer , iPackBufferSize );

	return true;
}

bool CActionData::_LoadXML_BaseActionInfo( XMLNode * pRootNode , const char * pSzFileName )
{
	//////////////////////////////////////////////////////////////////////////
	// 액션 데이터(기본정보)
	XMLNodes ActionDataNodes = pRootNode->GetChilds( "ActionData" );
	if( ActionDataNodes.size() <= 0 )
	{
		char strError[256];
		sprintf_s( strError , 256 , "액션파일에 액션 <ActionData> 가 없습니다.\n"
				   "기획팀에게 문의하세요.\n\n"
				   "Action File Name : %s" ,
				   pSzFileName );
		assert( false && strError );
		return false;
	}

	for( size_t cActionData = 0; cActionData < ActionDataNodes.size(); ++cActionData )
	{
		XMLNode * pActionDataNode = ActionDataNodes[cActionData];

		CActionDataInfo *pActionDataInfo = new CActionDataInfo;
		if( pActionDataInfo->LoadXML( pActionDataNode , m_lstPreloadEffect , m_lstPreloadSound ) == false )
		{
			RSAFE_DELETE( pActionDataInfo );
			return false;
		}

		m_ActionDataInfoList.push_back( pActionDataInfo );
	}

	return true;
}

void CActionData::_LoadXML_PlayerValue( XMLNode * pRootNode )
{
	// 플레이어 액션 변수
	XMLNode * pPlayerValueNode = pRootNode->GetChild( "PlayerValue" );
	if( pPlayerValueNode )
	{
		XMLNodes ValueNodes = pPlayerValueNode->GetChilds( "PValue" );
		for( size_t cValue = 0; cValue < ValueNodes.size(); ++cValue )
		{
			CValueParam valueParam;
			if( valueParam.LoadXML( ValueNodes[cValue] ) )
				m_lstPlayerValueList.push_back( valueParam );
		}
	}
}

void CActionData::_LoadXML_PlayerServerValue( XMLNode * pRootNode )
{
	XMLNode * pPlayerServerValueNode = pRootNode->GetChild( "PlayerServerValue" );
	if( pPlayerServerValueNode )
	{
		XMLNodes ValueNodes = pPlayerServerValueNode->GetChilds( "PSValue" );
		string			strName;
		DWORD			dwPSValueNameHashCode;
		DWORD			dwPSValueKey;

		m_lstPlayerServerValueList.clear();
		for( size_t cValue = 0; cValue < ValueNodes.size(); ++cValue )
		{
			if( ValueNodes[cValue]->GetAttr( "Name" , strName ) )
			{
				dwPSValueNameHashCode = CCrc32Static::StringCrc32( strName.c_str() );
				if( ValueNodes[cValue]->GetAttrDWORD( "PSValueKey" , dwPSValueKey ) )
					m_lstPlayerServerValueList.insert( map< DWORD , DWORD >::value_type( dwPSValueNameHashCode , dwPSValueKey ) );
			}
		}
	}
}

bool CActionData::_LoadXML_AddActionFile_LoadFunction( XMLNode * pRootNode , HashMap_ActionFunction& mapActionFunction )
{
	XMLNodes AddActionFileNodes = pRootNode->GetChilds( "AddActionFile" );
	for( size_t cAddActionFile = 0; cAddActionFile < AddActionFileNodes.size(); ++cAddActionFile )
	{
		XMLNode * pActionFileNode = AddActionFileNodes[cAddActionFile];

		string strAddActionFileName;
		if( pActionFileNode->GetAttr( "FileName" , strAddActionFileName ) )
		{
			RXML subXml;
			if( LOAD_XML_FROM_PACK( strAddActionFileName.c_str() , subXml ) == false )
				return false;

			XMLNode * pSubRootNode = subXml.GetRootChild( "C9ActionFile" );
			if( pSubRootNode )
			{
				if( LoadActionFunction( pSubRootNode , mapActionFunction ) == false )
					return false;
			}
		}
	}

	return true;
}


bool CActionData::_LoadXML_AddActionFile_LoadActionChart( XMLNode * pRootNode , HashMap_ActionFunction& mapActionFunction )
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
				if( LoadActionChart( pSubRootNode , pRootNode , mapActionFunction ) == false )
					return false;
			}
		}
	}

	return true;
}

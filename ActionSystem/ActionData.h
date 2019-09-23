#pragma once

/*
	@note : 액션에 관한 스크립트 정보를 모두 담아 두는 곳
*/
#include "ActionDefine.h"

struct CValueParam;
class CActionDataInfo;
class CActionChart;
class CAIActionData;
class RXML;

class CActionData
{	
protected:
	static const UINT VERSION; // 액션 버젼 정보..	

public :
	CActionData();
	~CActionData();

	bool							LoadXML( const char *pSzFileName );

	bool							SaveBinary( const char * pszFullPath );
	bool							LoadBinary( const char * pSzFileName );
	virtual bool					Dump( C9File *pFile );
	
	bool							LoadActionFunction( XMLNode * pRootNode, HashMap_ActionFunction & mapActionFunction );
	bool							LoadActionChart( XMLNode * pRootNode, XMLNode *pFunctionRootNode, HashMap_ActionFunction & mapActionFunction );

	bool							CopyActionChart( CActionChart * pActionChart );

	CActionDataInfo*				FindActionDataInfo( const DWORD dwActionIndexHashCode, bool IsPvPMapAction , const DWORD dwPVPActionIndexHashCode = 0 );
	void							SetActionChartList( HashMap_ActionList& actionChartList, const DWORD dwActionIndexHashCode, bool IsPvPMapAction , const DWORD dwPVPActionIndexHashCode = 0 );

	C9ReadBuffer::BufferPtr			GetReadBuffer( DWORD dwSize );
	bool							LOAD_XML_FROM_PACK( const char * pStrFileName , RXML & xml );
	bool							LOAD_BINARY_FROM_PACK( const char * pStrFileName , C9ReadBuffer & laodBinary , bool bMemSet );
	
private:

	bool							_LoadXML_BaseActionInfo( XMLNode * pRootNode , const char * pSzFileName );
	void							_LoadXML_PlayerValue( XMLNode * pRootNode );
	void							_LoadXML_PlayerServerValue( XMLNode * pRootNode );
	bool							_LoadXML_AddActionFile_LoadFunction( XMLNode * pRootNode , HashMap_ActionFunction& mapActionFunction );
	bool							_LoadXML_AddActionFile_LoadActionChart( XMLNode * pRootNode , HashMap_ActionFunction& mapActionFunction );

public:

	int								m_iRef;
	string							m_strFileName;
	DWORD							m_dwHashCode;

	vector< CActionDataInfo * >		m_ActionDataInfoList;
	vector< CActionChart* >			m_lstActionChart;
	
	List_PreloadString				m_lstPreloadEffect;
	List_PreloadString				m_lstPreloadSound;	
	vector< CValueParam >			m_lstPlayerValueList;

	std::map< DWORD, DWORD >		m_lstPlayerServerValueList;

	CAIActionData*					m_pAIActionData;

	
};


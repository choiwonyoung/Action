#pragma once

#include "ActionDefine.h"


//--------------------------------------------------------------------------------------------------------------
#define AIACTIONCHART_DECLARE(name)														\
			virtual enum AIActionChartType GetType() const override { return TYPE_##name; }	\
//--------------------------------------------------------------------------------------------------------------

class CAIActionData;
class CAIExecute;
class CAIActionChart
{
public:
	CAIActionChart();
	~CAIActionChart();

	static enum AIActionChartType	Parse_GetAIActionChartType( const char * pszType );
	static CAIActionChart*			Create_AIActionChart( enum AIActionChartType type );

	bool							LoadXML( XMLNode *pXMLNode , CAIActionData* pActionData );
	virtual void					Dump( C9File * pFile , CAIActionData* pActionData );

	bool							LoadExecute( XMLNodes nodes , CAIActionData* pActionData );
	virtual bool					LoadAIAction( XMLNode *pXMLNode , CAIActionData* pActionData ) { return true; }

	virtual enum AIActionChartType	GetType() const = 0;

public:
	int							m_iSetHitCountType;			// 저장 안함

public:
	vector< DWORD >				m_lstActionIndexHashCode;
	vector< CAIExecute* >		m_lstExecute;

	string						m_strName;					// AI액션명
	string						m_strRunActionName;			// 수행 액션 명
	string						m_strEndAIActionName;		// 액션종료시 분기 AI액션명
	string						m_strEventAIActionName[2];
	string						m_strPlayerActionName[2];

	//////////////////////////////////////////////////////////////////////////
	// 묶음 저장
	DWORD						m_dwHashcode;
	DWORD						m_dwRunActionChartCode;
	DWORD						m_dwEndAIActionCode;
	DWORD						m_dwPlayerActionHashCode[2];
	DWORD						m_dwEventAIAtionCode[2];		// 이벤트 액션

																// evnet
	int							m_iEventIconIndex;
	int							m_iEventIconAniSpeed;
	float						m_fEventDistance;

	int							m_iEndBlendtime;

	bool						m_bStartTimer;
	bool						m_bReturnPreTarget;
	bool						m_bDisableRotateAtEvent;
	bool						m_bCollisionForPath;
	bool						m_bGravity;
	bool						m_bCheckAllFrame;
	bool						m_bNoteOnMinimap;
	bool						m_bIgnoreThreat;
	bool						m_bIgnoreOrder;
	// 묶음 저장 끝
	//////////////////////////////////////////////////////////////////////////
};

inline CAIActionChart::CAIActionChart()
	: m_iSetHitCountType( 0 )

	, m_lstActionIndexHashCode()
	, m_lstExecute()

	, m_strName( "" )
	, m_strRunActionName( "" )
	, m_strEndAIActionName( "" )
	, m_dwHashcode( 0 )
	, m_dwRunActionChartCode( 0 )
	, m_dwEndAIActionCode( 0 )
	, m_iEventIconIndex( 0 )
	, m_iEventIconAniSpeed( 1 )
	, m_fEventDistance( 120.0f )

	, m_iEndBlendtime( 0 )

	, m_bStartTimer( false )
	, m_bReturnPreTarget( false )
	, m_bDisableRotateAtEvent( false )
	, m_bCollisionForPath( true )
	, m_bGravity( true )
	, m_bCheckAllFrame( false )
	, m_bNoteOnMinimap( true )
	, m_bIgnoreThreat( false )
	, m_bIgnoreOrder( false )
{
	m_dwPlayerActionHashCode[0] = 0;
	m_dwPlayerActionHashCode[1] = 0;
	m_dwEventAIAtionCode[0] = 0;
	m_dwEventAIAtionCode[1] = 0;

	m_strEventAIActionName[0] = "";
	m_strPlayerActionName[0] = "";
	m_strEventAIActionName[1] = "";
	m_strPlayerActionName[1] = "";
}

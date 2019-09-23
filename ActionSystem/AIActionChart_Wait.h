#pragma once

#include "AIActionChart.h"
#include "AIActionData.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 대기 액션
class CAIActionChart_Wait : public CAIActionChart
{
public:
	CAIActionChart_Wait();
	AIACTIONCHART_DECLARE( CAIActionChart_Wait );

	virtual bool	LoadAIAction( XMLNode *pXMLNode , CAIActionData* pActionData );
	virtual void	Dump( C9File * pFile , CAIActionData* pActionData );

public:
	//////////////////////////////////////////////////////////////////////////
	// 묶음 저장
	bool	m_LookAtTarget;
	bool	m_bIgnoreCheckTarget;		// 타겟여부에 따라 WAIT AI액션으로 보낼지 결정
										// 묶음 저장 끝
										//////////////////////////////////////////////////////////////////////////

};

inline CAIActionChart_Wait::CAIActionChart_Wait()
	: CAIActionChart()

	, m_LookAtTarget( false )
	, m_bIgnoreCheckTarget( false )
{
}
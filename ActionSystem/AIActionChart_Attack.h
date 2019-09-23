#pragma once


#include "AIActionData.h"

class CAIActionChart;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 공격
class CAIActionChart_Attack : public CAIActionChart
{
public:
	CAIActionChart_Attack();
	AIACTIONCHART_DECLARE( CAIActionChart_Attack );

	virtual bool	LoadAIAction( XMLNode *pXMLNode , CAIActionData *pActionData );
	virtual void	Dump( C9File * pFile , CAIActionData *pActionData );
	int				CAIActionChart_Attack::CompareAttackableMask( char* strTemp );

public:
	//////////////////////////////////////////////////////////////////////////
	// 묶음 저장
	int		m_iAttackableMask;		//공격 가능한 적을 표시하는 마스크
	bool	m_bSetTargetDirection;
	bool	m_bSetTargetFollow;
	bool	m_bSetTargetHold;
	// 묶음 저장 끝
	//////////////////////////////////////////////////////////////////////////
};

inline CAIActionChart_Attack::CAIActionChart_Attack()
: CAIActionChart()
, m_iAttackableMask( 0 )
, m_bSetTargetDirection( false )
, m_bSetTargetFollow( false )
, m_bSetTargetHold( false )
{
}

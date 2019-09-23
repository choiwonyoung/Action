#pragma once


#include "AIActionData.h"

class CAIActionChart;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ����
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
	// ���� ����
	int		m_iAttackableMask;		//���� ������ ���� ǥ���ϴ� ����ũ
	bool	m_bSetTargetDirection;
	bool	m_bSetTargetFollow;
	bool	m_bSetTargetHold;
	// ���� ���� ��
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

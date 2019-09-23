#pragma once

#include "AIActionChart.h"
#include "AIActionData.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ��� �׼�
class CAIActionChart_Wait : public CAIActionChart
{
public:
	CAIActionChart_Wait();
	AIACTIONCHART_DECLARE( CAIActionChart_Wait );

	virtual bool	LoadAIAction( XMLNode *pXMLNode , CAIActionData* pActionData );
	virtual void	Dump( C9File * pFile , CAIActionData* pActionData );

public:
	//////////////////////////////////////////////////////////////////////////
	// ���� ����
	bool	m_LookAtTarget;
	bool	m_bIgnoreCheckTarget;		// Ÿ�ٿ��ο� ���� WAIT AI�׼����� ������ ����
										// ���� ���� ��
										//////////////////////////////////////////////////////////////////////////

};

inline CAIActionChart_Wait::CAIActionChart_Wait()
	: CAIActionChart()

	, m_LookAtTarget( false )
	, m_bIgnoreCheckTarget( false )
{
}
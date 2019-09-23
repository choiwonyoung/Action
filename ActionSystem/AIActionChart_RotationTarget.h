#pragma once
#include "AIActionChart.h"
#include "AIActionData.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Å¸°Ù È¸Àü
class CAIActionChart_RotationTarget : public CAIActionChart
{
public:
	CAIActionChart_RotationTarget();
	AIACTIONCHART_DECLARE( CAIActionChart_RotationTarget );

	virtual bool	LoadAIAction( XMLNode *pXMLNode , CAIActionData *pActionData );
	virtual void	Dump( C9File * pFile , CAIActionData *pActionData );

public:
	float	m_fRotationSpeed;
};

inline CAIActionChart_RotationTarget::CAIActionChart_RotationTarget()
: CAIActionChart()
, m_fRotationSpeed( 0.0f )
{
}
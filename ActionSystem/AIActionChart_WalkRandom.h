#pragma once

#include "AIActionChart.h"
#include "AIActionData.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ∑£¥˝ ¿Ãµø
class CAIActionChart_WalkRandom : public CAIActionChart
{
public:
	CAIActionChart_WalkRandom();
	AIACTIONCHART_DECLARE( CAIActionChart_WalkRandom );

	virtual bool	LoadAIAction( XMLNode *pXMLNode , CAIActionData *pActionData );
	virtual void	Dump( C9File * pFile , CAIActionData *pActionData );

public:
	//////////////////////////////////////////////////////////////////////////
	// π≠¿Ω ¿˙¿Â
	float	m_fMinRange;
	float	m_fMaxRange;
	float	m_fMoveSpeed;
	bool	m_bBasePosMove;
	bool	m_bCurvedPath;
	// π≠¿Ω ¿˙¿Â ≥°
	//////////////////////////////////////////////////////////////////////////
};

inline CAIActionChart_WalkRandom::CAIActionChart_WalkRandom()
	: CAIActionChart()

	, m_fMinRange( 0.0f )
	, m_fMaxRange( 0.0f )
	, m_fMoveSpeed( 0.0f )
	, m_bBasePosMove( true )
	, m_bCurvedPath( false )
{
}
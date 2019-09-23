#pragma once

#include "AIActionChart.h"
#include "AIActionData.h"
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ≈∏∞Ÿ ¿Ãµø
class CAIActionChart_RunTarget : public CAIActionChart
{
public:
	CAIActionChart_RunTarget();
	AIACTIONCHART_DECLARE( CAIActionChart_RunTarget );

	virtual bool	LoadAIAction( XMLNode *pXMLNode , CAIActionData* pActionData );
	virtual void	Dump( C9File * pFile , CAIActionData* pActionData );

	enum TARGET_POS_TYPE
	{
		TARGET_POS_TYPE_FRONT = 0 ,
		TARGET_POS_TYPE_BACK ,
		TARGET_POS_TYPE_RIGHT ,
		TARGET_POS_TYPE_LEFT ,
	};

public:
	//////////////////////////////////////////////////////////////////////////
	// π≠¿Ω ¿˙¿Â
	float	m_fMinRange;
	float	m_fMaxRange;
	float	m_fMoveSpeed;
	float	m_fRotationSpeed;
	float	m_fClosestRange;
	float	m_fCheckRunTargetTime;
	int		m_iTargetPosType;
	bool	m_bDirectMove;
	bool	m_bCurvedPath;
	bool	m_bDestroyObstacle;
	// π≠¿Ω ¿˙¿Â ≥°
	//////////////////////////////////////////////////////////////////////////
};

inline CAIActionChart_RunTarget::CAIActionChart_RunTarget()
	: CAIActionChart()
	, m_fMinRange( 0.0f )
	, m_fMaxRange( 0.0f )
	, m_fMoveSpeed( 0.0f )
	, m_fRotationSpeed( 0.0f )
	, m_fClosestRange( 0.0f )
	, m_fCheckRunTargetTime( 0.3f )
	, m_iTargetPosType( 0 )
	, m_bDirectMove( false )
	, m_bCurvedPath( false )
	, m_bDestroyObstacle( false )
{
}
#pragma once

#include "AICondition.h"
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 지역 검사 ------------------------------------------------------------------------
class CAIActionData;
class CAICondition_CheckAreaRange : public CAICondition
{
public:
	CAICondition_CheckAreaRange();
	AICONDITION_DECLARE( CAICondition_CheckAreaRange );

	virtual bool		LoadXML( XMLNode *pXMLNode , CAIActionData *pActionData );
	virtual void		Dump( C9File * pFile , CAIActionData *pActionData );

public:
	float	m_fMinRange;
	float	m_fMaxRange;
	DWORD	m_dwAreaIndex;
};

inline CAICondition_CheckAreaRange::CAICondition_CheckAreaRange()
: CAICondition()
, m_fMinRange( 0.0f )
, m_fMaxRange( 0.0f )
, m_dwAreaIndex( 0 )
{
}
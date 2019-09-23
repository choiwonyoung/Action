#pragma once

#include "AICondition.h"
#include "ActionDefine.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Å¸°Ù °Å¸®
class CAIActionData;
class CAICondition_CheckTargetRange : public CAICondition
{
public:
	CAICondition_CheckTargetRange();
	AICONDITION_DECLARE( CAICondition_CheckTargetRange );

	virtual bool		LoadXML( XMLNode *pXMLNode , CAIActionData* pActionData );
	virtual void		Dump( C9File * pFile , CAIActionData* pActionData );

public:
	float						m_fMinRange;
	float						m_fMaxRange;
	int							m_iTargetNum;
	DWORD						m_dwIgnoreTypeCount;
	DWORD						m_dwIgnoreEventIDCount;
	bool						m_bTargetBasePosition;

	bool						m_bCalcAxisY;
	bool						m_bClosestPosMode;
	list< DWORD >				m_lstIgnoreEventID;
	list<SEARCHTARGET_TYPE>		m_lstIgnoreTargetType;
};

inline CAICondition_CheckTargetRange::CAICondition_CheckTargetRange()
: CAICondition()

, m_fMinRange( 0.0f )
, m_fMaxRange( 0.0f )
, m_iTargetNum( 0 )
, m_bCalcAxisY( false )
, m_bClosestPosMode( false )
, m_dwIgnoreTypeCount( 0 )
, m_dwIgnoreEventIDCount( 0 )
, m_bTargetBasePosition( false )
{

}
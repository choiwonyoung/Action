#pragma once

#include "AICondition.h"
#include "ActionDefine.h"
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Å¸°Ù °Ë»ö
class CAIActionData;
class CAICondition_SearchAttackTarget : public CAICondition
{
public:
	CAICondition_SearchAttackTarget();
	AICONDITION_DECLARE( CAICondition_SearchAttackTarget );

	virtual bool		LoadXML( XMLNode *pXMLNode , CAIActionData* pActionData );
	virtual void		Dump( C9File * pFile , CAIActionData* pActionData );

public:
	float					m_fSearchRange;
	float					m_fMinSearchRange;
	float					m_fSearchHeight;
	SEARCHTARGET_TYPE		m_eTargetType;
	AttackTargetType		m_eAttackTargetType;
	DWORD					m_dwOffsetID;
	DWORD					m_dwIgnoreTypeCount;
	DWORD					m_dwIgnoreEventIDCount;
	bool					m_bOffsetBranch1;

	list< DWORD >			m_lstIgnoreEventID;
	list<SEARCHTARGET_TYPE> m_lstIgnoreTargetType;

};

inline CAICondition_SearchAttackTarget::CAICondition_SearchAttackTarget()
: CAICondition()

, m_fSearchRange( 0.0f )
, m_fSearchHeight( 0.0f )
, m_eTargetType( SEARCHTARGET_NONE )
, m_fMinSearchRange( 0.0f )
, m_dwOffsetID( 0 )
, m_dwIgnoreTypeCount( 0 )
, m_dwIgnoreEventIDCount( 0 )
, m_eAttackTargetType( C9ATT_ENEMY )
, m_bOffsetBranch1( false )

{
}
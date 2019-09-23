#pragma once

#include "AICondition.h"
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 자신 States 검사 ------------------------------------------------------------------------
class CAIActionData;
class CAICondition_CheckSelfStates : public CAICondition
{
public:
	CAICondition_CheckSelfStates();
	AICONDITION_DECLARE( CAICondition_CheckSelfStates );

	virtual bool		LoadXML( XMLNode *pXMLNode , CAIActionData *pActionData );
	virtual void		Dump( C9File * pFile , CAIActionData *pActionData );

public:
	OBJECT_STATES	m_StatesType;
	int					m_iMinValue;
	int					m_iMaxValue;
	int					m_iState;
	DWORD				m_dwState;
	bool				m_bState;
	bool				m_bRateType;
	bool				m_bSetTarget;
};

inline CAICondition_CheckSelfStates::CAICondition_CheckSelfStates()
: CAICondition()
, m_StatesType( OBJECT_STATES_HP )
, m_iMinValue( 0 )
, m_iMaxValue( 0 )
, m_iState( 0 )
, m_dwState( 0 )
, m_bState( false )
, m_bRateType( false )
, m_bSetTarget( false )
{
}

// 적 States 검사 ----------------------------------------------------------------------------
class CAICondition_CheckTargetStates : public CAICondition_CheckSelfStates
{
public:
	CAICondition_CheckTargetStates();
	AICONDITION_DECLARE( CAICondition_CheckTargetStates );

	virtual bool		LoadXML( XMLNode *pXMLNode , CAIActionData *pActionData );
	virtual void		Dump( C9File * pFile , CAIActionData *pActionData );

public:
};

inline CAICondition_CheckTargetStates::CAICondition_CheckTargetStates()
	: CAICondition_CheckSelfStates()
{
}

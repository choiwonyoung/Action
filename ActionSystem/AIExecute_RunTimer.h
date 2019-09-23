#pragma once

#include "AIExcute.h"
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 타이머 수행 ------------------------------------------------------------------------
class CAIActionData;
class CAIExecute_RunTimer : public CAIExecute
{
public:
	CAIExecute_RunTimer();
	virtual ~CAIExecute_RunTimer() {};

	AIEXECUTE_DECLARE( CAIExecute_RunTimer );

	virtual bool	LoadXML( XMLNode *pXMLNode , CAIActionData *pActionData );
	virtual void	Dump( C9File * pFile , CAIActionData * pActionData );

public:
	bool	m_bRun;
	bool	m_bReset;
};

inline CAIExecute_RunTimer::CAIExecute_RunTimer()
	: CAIExecute()
	, m_bRun( false )
	, m_bReset( false )
{
}

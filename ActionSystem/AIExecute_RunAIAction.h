#pragma once

#include "AIExcute.h"

class CAIActionData;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 다음 AI 액션 수행 ------------------------------------------------------------------------
class CAIExecute_RunAIAction : public CAIExecute
{
public:
	CAIExecute_RunAIAction();
	virtual ~CAIExecute_RunAIAction() {};
	AIEXECUTE_DECLARE( CAIExecute_RunAIAction );

	virtual bool	LoadXML( XMLNode *pXMLNode , CAIActionData* pActionData );
	virtual void	Dump( C9File * pFile , CAIActionData* pActionData );

public:
	string						m_strRunActionName;		// 수행 액션명
	string						m_strFailActionName;

	DWORD						m_dwRunAIActionCode;
	DWORD						m_dwFailAIActionCode;
	int							m_iBlendTime;
};

inline	CAIExecute_RunAIAction::CAIExecute_RunAIAction()
	: CAIExecute()
	, m_strRunActionName( "" )
	, m_strFailActionName( "" )

	, m_dwRunAIActionCode( 0 )
	, m_dwFailAIActionCode( 0 )
	, m_iBlendTime( 0 )
{
}

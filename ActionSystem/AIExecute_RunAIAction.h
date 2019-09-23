#pragma once

#include "AIExcute.h"

class CAIActionData;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���� AI �׼� ���� ------------------------------------------------------------------------
class CAIExecute_RunAIAction : public CAIExecute
{
public:
	CAIExecute_RunAIAction();
	virtual ~CAIExecute_RunAIAction() {};
	AIEXECUTE_DECLARE( CAIExecute_RunAIAction );

	virtual bool	LoadXML( XMLNode *pXMLNode , CAIActionData* pActionData );
	virtual void	Dump( C9File * pFile , CAIActionData* pActionData );

public:
	string						m_strRunActionName;		// ���� �׼Ǹ�
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

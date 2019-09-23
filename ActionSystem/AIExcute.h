#pragma once

#include "ActionDefine.h"


//--------------------------------------------------------------------------------------------------------------
#define AIEXECUTE_DECLARE(name)												\
	virtual AIExecuteType GetType() const override { return TYPE_##name; }	\
//--------------------------------------------------------------------------------------------------------------


class CAIActionData;
class CAICondition;

class CAIExecute
{
public:
	CAIExecute();
	virtual ~CAIExecute();

	virtual enum AIExecuteType	GetType() const = 0;

	static enum AIExecuteType	Parse_GetExecuteType( const char * pszParameter );
	static CAIExecute*			Create_AIExecute( AIExecuteType type );

	virtual bool				LoadXML( XMLNode *pXMLNode , CAIActionData * pActionData );
	virtual void				Dump( C9File * pFile , CAIActionData * pActionData );

	bool						LoadCondition( XMLNodes nodes , CAIActionData *pActionData );

	//bool						GetCheckTimer( DWORD& dwCheckSkillTimer );
public:
	vector< CAICondition * >	m_lstCondition;
	vector< DWORD >				m_lstActionIndexHashCode;

	bool						m_bConditionCheckOR;
	bool						m_bWaitActionEnd;
	bool						m_bRefreshSetAction;
};

inline	CAIExecute::CAIExecute()
: m_lstCondition()
, m_lstActionIndexHashCode()

, m_bConditionCheckOR( false )
, m_bWaitActionEnd( false )
, m_bRefreshSetAction( true )
{
}


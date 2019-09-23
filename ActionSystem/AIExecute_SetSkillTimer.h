#pragma once

#include "AIExcute.h"
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ½ºÅ³ ÄðÅ¸ÀÓ -----------------------------------------------------------------------
class CAIActionData;
class CAIExecute_SetSkillTimer : public CAIExecute
{
public:
	CAIExecute_SetSkillTimer();
	virtual ~CAIExecute_SetSkillTimer() {};

	AIEXECUTE_DECLARE( CAIExecute_SetSkillTimer );

	virtual bool	LoadXML( XMLNode *pXMLNode , CAIActionData *pActionData );
	virtual void	Dump( C9File * pFile , CAIActionData * pActionData );


public:
	DWORD			m_dwName;
	float			m_fTime;
};

inline	CAIExecute_SetSkillTimer::CAIExecute_SetSkillTimer()
	: CAIExecute()
	, m_fTime( 0 )
{
}

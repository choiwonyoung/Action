#pragma once
#include "AIExcute.h"
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ¾×¼Ç ÀÎµ¦½º -----------------------------------------------------------------------
class CAIActionData;
class CAIExecute_SetActionIndex : public CAIExecute
{
public:
	CAIExecute_SetActionIndex();
	virtual ~CAIExecute_SetActionIndex() {};

	AIEXECUTE_DECLARE( CAIExecute_SetActionIndex );

	virtual bool	LoadXML( XMLNode *pXMLNode , CAIActionData *pActionData );
	virtual void	Dump( C9File* pFile , CAIActionData* pActionData );

public:
	DWORD			m_dwActionIndexHash;
};

inline	CAIExecute_SetActionIndex::CAIExecute_SetActionIndex()
	: CAIExecute()
	, m_dwActionIndexHash( 0 )
{
}

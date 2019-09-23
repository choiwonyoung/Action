#pragma once

#include "AICondition.h"
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ·£´ý
class CAIActionData;
class CAICondition_Random : public CAICondition
{
public:
	CAICondition_Random();
	AICONDITION_DECLARE( CAICondition_Random );

	virtual bool		LoadXML( XMLNode *pXMLNode , CAIActionData *pActionData );
	virtual void		Dump( C9File * pFile , CAIActionData *pActionData );

public:
	int		m_iValue;
};

inline CAICondition_Random::CAICondition_Random()
: CAICondition()
, m_iValue( 0 )
{
}
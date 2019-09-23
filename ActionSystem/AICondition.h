#pragma once
#include "ActionDefine.h"

//--------------------------------------------------------------------------------------------------------------
#define AICONDITION_DECLARE(name)													\
			virtual enum AIConditionType GetType() const override { return TYPE_##name; }	\
//--------------------------------------------------------------------------------------------------------------

enum OBJECT_STATES
{
	OBJECT_STATES_HP ,
	OBJECT_STATES_MP ,
	OBJECT_STATES_DAMAGE ,
	OBJECT_STATES_JUMP ,
	OBJECT_STATES_ATTACK ,
	OBJECT_STATES_SIGHT ,
	OBJECT_STATES_ACTION ,
	OBJECT_STATES_CATCH ,
	OBJECT_STATES_WALL ,				// º®¿¡ ºÎµúÈù °æ¿ì
	OBJECT_STATES_SUMMONLIMIT ,
	OBJECT_STATES_ORDERWAITSTATE ,
	OBJECT_STATES_TEAM ,
	OBJECT_STATES_ABNORMAL ,
};

class CAIActionData;
class RXML;
class C9File;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
class CAICondition
{
public:
	CAICondition();
	virtual ~CAICondition() {};
	virtual AIConditionType			GetType() const = 0;

	virtual bool					LoadXML( XMLNode *pXMLNode , CAIActionData *pActionData );
	virtual void					Dump( C9File * pFile , CAIActionData *pActionData );

	virtual bool					CheckTarget() const { return false; }

public:
	static AIConditionType			Parse_GetConditionType( const char * pszParameter );
	static CAICondition*			Create_AICondition( AIConditionType type );
	static OBJECT_STATES			Parse_GetStates( const char * pszState );

public:
	bool		m_bCheckReturn;
};

inline CAICondition::CAICondition()
	: m_bCheckReturn( true )
{
}
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


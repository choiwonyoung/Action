#include "stdafx.h"
#include "AIConditoin_CheckTargetStates.h"
#include "AIActionData.h"
#include "ActionContantable.h"

// ------------------------------------------------------------------------
// 자신 States 검사 
bool CAICondition_CheckSelfStates::LoadXML( XMLNode *pXMLNode , CAIActionData *pActionData )
{
	string strTemp;
	int iValue;

	if( pXMLNode->GetAttr( "State" , strTemp ) )
	{
		m_StatesType = Parse_GetStates( strTemp.c_str() );
	}

	pXMLNode->GetAttrBool( "SetTarget" , m_bSetTarget );

	switch( m_StatesType )
	{
		case OBJECT_STATES_HP:
		{
			GET_PARAM_VALUE( "MinValue" , "ConditionCheckStates" );
			m_iMinValue = iValue;
			GET_PARAM_VALUE( "MaxValue" , "ConditionCheckStates" );
			m_iMaxValue = iValue;

			pXMLNode->GetAttrBool( "Percent" , m_bRateType );
		}
		break;
		case OBJECT_STATES_MP:
		{
			GET_PARAM_VALUE( "MinValue" , "ConditionCheckStates" );
			m_iMinValue = iValue;
			GET_PARAM_VALUE( "MaxValue" , "ConditionCheckStates" );
			m_iMaxValue = iValue;

			pXMLNode->GetAttrBool( "Percent" , m_bRateType );
		}
		break;
		case OBJECT_STATES_DAMAGE:
		{
			pXMLNode->GetAttr( "DamageState" , strTemp );
			string strState = Action::ActionString::GetToken(strTemp , 0 );

			if( strState == "None" )					m_iState = CDS_NONE;
			else if( strState == "Normal" )				m_iState = CDS_NORMAL;
			else if( strState == "Skill" )				m_iState = CDS_SKILL;
			else if( strState == "Pull" )				m_iState = CDS_PULL;
			else if( strState == "Catch" )				m_iState = CDS_CATCH;
			else if( strState == "Down" )				m_iState = CDS_DOWN;
			else if( strState == "Standup" )			m_iState = CDS_STANDUP;
			else if( strState == "KnockDown" )			m_iState = CDS_KNOCKDOWN;
			else if( strState == "Defence_Push" )		m_iState = CDS_DEFENCE_PUSH;
			else if( strState == "Dead" )				m_iState = CDS_DEAD;
			else if( strState == "Iced" )				m_iState = CDS_ICED;
			else if( strState == "Stun" )				m_iState = CDS_STUN;
			else if( strState == "Rigid" )				m_iState = CDS_RIGID;
			else if( strState == "WallStun" )			m_iState = CDS_WALLSTUN;
		}
		break;

		case OBJECT_STATES_JUMP:
		{
			m_bState = true;
		}
		break;
		case OBJECT_STATES_ATTACK:
		{
			m_bState = false;
		}
		break;
		case OBJECT_STATES_SIGHT:
		{
			m_bState = false;
			pXMLNode->GetAttrBool( "CheckObstacle" , m_bState );

			GET_PARAM_VALUE( "MinValue" , "ConditionCheckStates" );
			m_iMinValue = iValue;
			GET_PARAM_VALUE( "MaxValue" , "ConditionCheckStates" );
			m_iMaxValue = iValue;
		}
		break;
		case OBJECT_STATES_ACTION:
		{
			pXMLNode->GetAttr( "ActionState" , strTemp );
			string strState = Action::ActionString::GetToken( strTemp , 0 );
			if( strState == "Wait" )					m_dwState = C9CAS_WAIT;
			else if( strState == "Move" )				m_dwState = C9CAS_MOVE;
			else if( strState == "Attack" )				m_dwState = C9CAS_ATTACK;
			else if( strState == "Skill" )				m_dwState = C9CAS_SKILL;
			else if( strState == "Damage" )				m_dwState = C9CAS_DAMAGE;
			else if( strState == "Dead" )				m_dwState = C9CAS_DEAD;
			else if( strState == "Fly" )				m_dwState = C9CAS_FLY;
			else if( strState == "AttackNormal" )		m_dwState = C9CAS_ATTACK_NORMAL;
			else if( strState == "AttackRange" )		m_dwState = C9CAS_ATTACK_RANGE;
			else if( strState == "AttackHard3" )		m_dwState = C9CAS_ATTACK_HARD3;
			else if( strState == "AttackHard2" )		m_dwState = C9CAS_ATTACK_HARD2;
			else if( strState == "AttackHard1" )		m_dwState = C9CAS_ATTACK_HARD1;
			else if( strState == "MoveLeft" )			m_dwState = C9CAS_MOVE_LEFT;
			else if( strState == "MoveRight" )			m_dwState = C9CAS_MOVE_RIGHT;
			else if( strState == "MoveForward" )		m_dwState = C9CAS_MOVE_FORWARD;
			else if( strState == "MoveBack" )			m_dwState = C9CAS_MOVE_BACK;
			else if( strState == "AttackFire" )			m_dwState = C9CAS_ATTACK_FIRE;

		}
		break;
		case OBJECT_STATES_CATCH:
		{
			m_iState = 0;
			pXMLNode->GetAttrInt( "BoneIndex" , m_iState );

			m_bState = false;
			pXMLNode->GetAttrBool( "AllBone" , m_bState );
		}
		break;
		case OBJECT_STATES_SUMMONLIMIT:
		{
			pXMLNode->GetAttrInt( "MaxValue" , m_iMaxValue );
		}
		break;
		case OBJECT_STATES_ORDERWAITSTATE:
		{
			pXMLNode->GetAttrBool( "Attackable" , m_bState );
		}
		break;
		case OBJECT_STATES_TEAM:
		{
			m_bState = false;
			pXMLNode->GetAttrBool( "Our" , m_bState );
		}
		break;
		case OBJECT_STATES_ABNORMAL:
		{
			m_dwState = 0;
			pXMLNode->GetAttrDWORD( "AbTypeKey" , m_dwState );
		}
		break;
	}

	return CAICondition::LoadXML( pXMLNode , pActionData );
}

void CAICondition_CheckSelfStates::Dump( C9File * pFile , CAIActionData *pActionData )
{
	CAICondition::Dump( pFile , pActionData );

	static const size_t sizeOfData = C9_SIZE_OF_BETWEEN_VALUE( m_StatesType , m_bSetTarget );

	if( pFile->IsSave() )
	{
		pFile->WriteData_SizeT( &m_StatesType , sizeOfData );
	}
	else
	{
		pFile->ReadData_SizeT( &m_StatesType , sizeOfData );
	}
}


// ----------------------------------------------------------------------------
// 적 States 검사 
bool CAICondition_CheckTargetStates::LoadXML( XMLNode *pXMLNode , CAIActionData *pActionData )
{
	return CAICondition_CheckSelfStates::LoadXML(pXMLNode, pActionData);
}

void CAICondition_CheckTargetStates::Dump( C9File * pFile , CAIActionData *pActionData )
{
	CAICondition_CheckSelfStates::Dump( pFile, pActionData );
}

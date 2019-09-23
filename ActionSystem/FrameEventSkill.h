#pragma once

#include "FrameEvent.h"
#include "ActionContantable.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ��ų ����
class CFrameEventSkill : public CFrameEvent
{
public:
	CFrameEventSkill();

	virtual CFrameEventType		GetType() const { return CFE_Skill; }

	virtual bool				LoadXML( XMLNode *pXMLNode , List_PreloadString &lstPreloadEffect , List_PreloadString &lstPreloadSound , const char * pszClassName = NULL );
	virtual void				Dump( C9File * pFile , List_PreloadString & lstPreloadEffect , List_PreloadString &lstPreloadSound );

public:
	//////////////////////////////////////////////////////////////////////////
	// ���� ����
	DWORD					m_dwSkillTypeKey;
	int						m_iUseMonsterSkillkey;	// �����Ϳ� �ִ� ��ų�� ����ϱ� ���� ��ũ��Ʈ �� Ű
	C9_SKILL_TARGET_TYPE	m_eTargetType;
	float					m_fRange;
	bool					m_bTargetSelf;
	bool					m_bTargetParent;
	bool					m_bCheckSkill;		//FrameEvent�� ����� ��ų����	
												// ���� ���� ��
												//////////////////////////////////////////////////////////////////////////
};

inline CFrameEventSkill::CFrameEventSkill()
	: CFrameEvent()
	, m_dwSkillTypeKey( 0 )
	, m_iUseMonsterSkillkey( 0 )
	, m_eTargetType( C9_SKILL_TARGET_CURRUNT )
	, m_fRange( 0.0f )
	, m_bTargetSelf( false )
	, m_bTargetParent( false )
	, m_bCheckSkill( false )
{
}
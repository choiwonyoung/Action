#pragma once

#include "FrameEvent.h"
#include "ActionContantable.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 스킬 시전
class CFrameEventSkill : public CFrameEvent
{
public:
	CFrameEventSkill();

	virtual CFrameEventType		GetType() const { return CFE_Skill; }

	virtual bool				LoadXML( XMLNode *pXMLNode , List_PreloadString &lstPreloadEffect , List_PreloadString &lstPreloadSound , const char * pszClassName = NULL );
	virtual void				Dump( C9File * pFile , List_PreloadString & lstPreloadEffect , List_PreloadString &lstPreloadSound );

public:
	//////////////////////////////////////////////////////////////////////////
	// 묶음 저장
	DWORD					m_dwSkillTypeKey;
	int						m_iUseMonsterSkillkey;	// 데이터에 있는 스킬을 사용하기 위한 스크립트 상 키
	C9_SKILL_TARGET_TYPE	m_eTargetType;
	float					m_fRange;
	bool					m_bTargetSelf;
	bool					m_bTargetParent;
	bool					m_bCheckSkill;		//FrameEvent의 사용할 스킬여부	
												// 묶음 저장 끝
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
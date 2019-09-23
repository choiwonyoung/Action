#pragma once
#include "FrameEvent.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 일반 공격
class CFrameEventAttackNormal : public CFrameEvent
{
public:
	// 액션 복사 /////////////////////////////////////
	struct CCopyActionValue
	{
		float			m_fAttackRange;
		float			m_fDefenseCrashRate;
		vector3			m_vecEffectScale;
		float			m_fAttackDamageVelocity;
		float			m_fAttackFlyFinalHeight;
		float			m_fAttackFloatTime;
		float			m_fFAttackDamageVelocity;
		float			m_fFAttackFlyFinalHeight;
		float			m_fFAttackFloatTime;

		CCopyActionValue()
		{
			memset( this , 0 , sizeof( CCopyActionValue ) );
		}
	};


	enum	SKILL_USE_INDEX_AI { SKILL_USE_MONSTER = 0x0100 , SKILL_USE_PET = 0x0200 , SKILL_INDEX_DECTECTOR = 0x00ff };
	enum	RANGE_SCALE_PREVENTMASK { RANGESCALE_PREVENT_RANGE = 0 , RANGESCALE_PREVENT_HEIGHT = 1 };
public:
	CFrameEventAttackNormal( const CActionData & actionData );
	virtual ~CFrameEventAttackNormal() {}

	virtual CFrameEventType		GetType() const { return CFE_AttackNormal; }
	virtual bool				IsAttackFrameEvent() const override { return true; }

	virtual bool				LoadXML( XMLNode *pXMLNode , List_PreloadString &lstPreloadEffect , List_PreloadString &lstPreloadSound , const char * pszClassName = NULL );
	virtual void				Dump( C9File * pFile , List_PreloadString & lstPreloadEffect , List_PreloadString &lstPreloadSound );

	// 액션 복사
	virtual void				LoadXMLCopyActionValue( XMLNode *pXMLNode );
	virtual void				CopyActionValue( CFrameEvent *pFrameEvent , int iLevel );

	// 스킬키 관련
	static  void				LoadSkillKey( string& strAttr , int& iUseMonsterSkillIdx , DWORD& dwSkillKey );
public:
	CFrameEventAttackEffect		m_AttackEffect;
	CFrameEventAttackValue		m_AttackValue;
#ifndef _GAME_RELEASE_


	CCopyActionValue			m_CopyActionValue;
#endif
	//////////////////////////////////////////////////////////////////////////
	// 묶음 저장
	C9ActionDamageDirection		m_DamageDirection;
	C9ActionAttackType			m_AttackType;
	C9HANDTYPE					m_UseAttackItemType;

	float						m_fAttackRange;					// 공격 범위
	float						m_fAttackHeightRate;			// 공격 높이 비율
	float						m_fAttackNormalHeight;

	DWORD						m_dwSkillType;					// 스킬 타입 ( 0일 경우 일반 평타 공격, 1이상이면 스킬타입 )
	DWORD						m_dwSkillIndex;					// 스킬 인덱스
	int							m_iUseMonsterSkillKeyIndex;
	int							m_nScaleRatePrevent;			// Range 와 Height를 스케일에 따라 조정하는것을 방지하는지에 대한 플래그 값

	UINT						m_nCatchIndex;					// 잡기 인덱스
	vector3						m_vecAttackPositionOffset;

	bool						m_bPositiveHeightOnly;			//attackNormal 타격 판정시 캐릭터의 포지션으로 부터 height /2 만큼 아래위로 높이 박스를 형성하게 되어있는데 이것을 포지션에서 위로 height 만큼 높이 박스를 형성하도록 변경
	bool						m_bAttackTypeForceExecute;
	bool						m_bCatchTypeHold;
	bool						m_bIgnoreDefence;				// 방어 무시
	bool						m_bCheckAllFrame;
	// 묶음 저장 끝
	//////////////////////////////////////////////////////////////////////////


};

inline CFrameEventAttackNormal::CFrameEventAttackNormal( const CActionData & actionData )
	: CFrameEvent()

	, m_AttackValue( actionData )
	, m_AttackEffect()

	, m_DamageDirection( CADD_NormalDown )
	, m_AttackType( CAAT_Normal )
	, m_UseAttackItemType( C9HANDTYPE_RIGHT )

	, m_fAttackRange( 0.0f )
	, m_fAttackHeightRate( 1.0f )

	, m_dwSkillType( 0 )
	, m_dwSkillIndex( 1 )
	, m_iUseMonsterSkillKeyIndex( 0 )

	, m_nCatchIndex( 0 )

	, m_vecAttackPositionOffset( 0.0f , 0.0f , 0.0f )

	, m_bAttackTypeForceExecute( false )
	, m_bCatchTypeHold( false )
	, m_bIgnoreDefence( false )
	, m_bCheckAllFrame( false )
	, m_bPositiveHeightOnly( false )
	, m_nScaleRatePrevent( 0 )
	, m_fAttackNormalHeight( -1 )
{
}
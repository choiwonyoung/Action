#pragma once
#include "FrameEvent.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// �Ϲ� ����
class CFrameEventAttackNormal : public CFrameEvent
{
public:
	// �׼� ���� /////////////////////////////////////
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

	// �׼� ����
	virtual void				LoadXMLCopyActionValue( XMLNode *pXMLNode );
	virtual void				CopyActionValue( CFrameEvent *pFrameEvent , int iLevel );

	// ��ųŰ ����
	static  void				LoadSkillKey( string& strAttr , int& iUseMonsterSkillIdx , DWORD& dwSkillKey );
public:
	CFrameEventAttackEffect		m_AttackEffect;
	CFrameEventAttackValue		m_AttackValue;
#ifndef _GAME_RELEASE_


	CCopyActionValue			m_CopyActionValue;
#endif
	//////////////////////////////////////////////////////////////////////////
	// ���� ����
	C9ActionDamageDirection		m_DamageDirection;
	C9ActionAttackType			m_AttackType;
	C9HANDTYPE					m_UseAttackItemType;

	float						m_fAttackRange;					// ���� ����
	float						m_fAttackHeightRate;			// ���� ���� ����
	float						m_fAttackNormalHeight;

	DWORD						m_dwSkillType;					// ��ų Ÿ�� ( 0�� ��� �Ϲ� ��Ÿ ����, 1�̻��̸� ��ųŸ�� )
	DWORD						m_dwSkillIndex;					// ��ų �ε���
	int							m_iUseMonsterSkillKeyIndex;
	int							m_nScaleRatePrevent;			// Range �� Height�� �����Ͽ� ���� �����ϴ°��� �����ϴ����� ���� �÷��� ��

	UINT						m_nCatchIndex;					// ��� �ε���
	vector3						m_vecAttackPositionOffset;

	bool						m_bPositiveHeightOnly;			//attackNormal Ÿ�� ������ ĳ������ ���������� ���� height /2 ��ŭ �Ʒ����� ���� �ڽ��� �����ϰ� �Ǿ��ִµ� �̰��� �����ǿ��� ���� height ��ŭ ���� �ڽ��� �����ϵ��� ����
	bool						m_bAttackTypeForceExecute;
	bool						m_bCatchTypeHold;
	bool						m_bIgnoreDefence;				// ��� ����
	bool						m_bCheckAllFrame;
	// ���� ���� ��
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
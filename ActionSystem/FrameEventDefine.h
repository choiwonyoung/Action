#pragma once
#include "ActionContantable.h"
#include "ActionDefine.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 공격에 관련된 구조체

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// CAddAttackValue
struct CAddAttackValue
{
	int		iVarType;		// 변수 타입, ( 스킬-C9_DATA_INFO_SKILL, 아이템-C9_DATA_INFO_ITEM )
	DWORD	dwKey;			// 데이터 키
	DWORD	dwVarCode;		// 변수코드

	CAddAttackValue()
		: iVarType( 0 )
		, dwKey( 0 )
		, dwVarCode( 0 )
	{
	}
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// C9FrameEventAttackEffect
struct CFrameEventAttackEffect
{
	string						m_strDamageEffectAttachBone;

	color						m_clrAttackColor;
	int							m_nAttackEffect;
	int							m_nAttackSound;
	vector3						m_vecEffectScale;
	vector3						m_vecEffectRotation;
	bool						m_bEffectAttachTarget;


	CFrameEventAttackEffect()
		: m_strDamageEffectAttachBone( "" )

		, m_clrAttackColor( 0x99F5920A )
		, m_nAttackEffect( -1 )
		, m_nAttackSound( -1 )
		, m_vecEffectScale( 1.0f , 1.0f , 1.0f )
		, m_vecEffectRotation( 0.0f , 0.0f , 0.0f )
		, m_bEffectAttachTarget( false )
	{
	}

	bool	LoadXML( XMLNode *pXMLNode );
	void	Dump( C9File * pFile );
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// CFrameEventAttackValue
class CActionData;
struct CFrameEventAttackValue
{
	// 저장 안함
	float						m_fFrameDelayNow;

	//////////////////////////////////////////////////////////////////////////
	// 묶음 저장
	// 지상에서 적용되는 값
	float						m_fAttackDamageVelocity;
	float						m_fAttackDamageAcceleration;
	float						m_fAttackFlyFinalHeight;
	float						m_fAttackFloatTime;

	// 공중 콤보 중에 적용 되는 값
	float						m_fFlyAttackDamageVelocity;
	float						m_fFlyAttackDamageAcceleration;
	float						m_fFlyAttackFlyFinalHeight;
	float						m_fFlyAttackFloatTime;

	C9KnockDownOtherType		m_KnockDownOtherType;				// 다른 캐릭터를 넘어트리는 공격 타입
	AttackTargetType			m_AttackTargetType;
	C9ReactDirectionType		m_ReactDirectionType;

	float						m_fDelayFrame;
	float						m_fFrameDelaySub;
	float						m_fFrameDelayEnd;
	float						m_fSlamSpeed;						// 내려찍는 공격 속도
	float						m_fRigidTime;						// 경직 시간
	float						m_fAttackAngle;						// 공격 각도
	float						m_fDefenseCrashRate;				// 상대의 방어 무시 확률
	float						m_fGuardCrash;						// 가드크래쉬 값

	int							m_iSuperArmorBreak;					// 슈퍼아머를 깰 수 있느냐를 결정하는 값

	bool						m_bDownAttack;						// 다운된 적도 공격 가능한가?
	bool						m_bSpinAttack;						// 회전 넉다운 공격인가?
																	// 묶음 저장 끝
																	//////////////////////////////////////////////////////////////////////////

	CFrameEventAttackValue( const CActionData & actionData );

	static float					GetDefaultDamageVelocity( C9ActionAttackType attackType );
	static float					GetDefaultDamageAcceleration( C9ActionAttackType attackType );
	static float					GetDefaultFlyFinalHeight( C9ActionAttackType attackType );
	static float					GetDefaultFloatTime( C9ActionAttackType attackType );

	bool							LoadXML( XMLNode *pXMLNode , C9ActionAttackType attackType );
	void							Dump( C9File * pFile );
};
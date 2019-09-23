#pragma once
#include "ActionContantable.h"
#include "ActionDefine.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���ݿ� ���õ� ����ü

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// CAddAttackValue
struct CAddAttackValue
{
	int		iVarType;		// ���� Ÿ��, ( ��ų-C9_DATA_INFO_SKILL, ������-C9_DATA_INFO_ITEM )
	DWORD	dwKey;			// ������ Ű
	DWORD	dwVarCode;		// �����ڵ�

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
	// ���� ����
	float						m_fFrameDelayNow;

	//////////////////////////////////////////////////////////////////////////
	// ���� ����
	// ���󿡼� ����Ǵ� ��
	float						m_fAttackDamageVelocity;
	float						m_fAttackDamageAcceleration;
	float						m_fAttackFlyFinalHeight;
	float						m_fAttackFloatTime;

	// ���� �޺� �߿� ���� �Ǵ� ��
	float						m_fFlyAttackDamageVelocity;
	float						m_fFlyAttackDamageAcceleration;
	float						m_fFlyAttackFlyFinalHeight;
	float						m_fFlyAttackFloatTime;

	C9KnockDownOtherType		m_KnockDownOtherType;				// �ٸ� ĳ���͸� �Ѿ�Ʈ���� ���� Ÿ��
	AttackTargetType			m_AttackTargetType;
	C9ReactDirectionType		m_ReactDirectionType;

	float						m_fDelayFrame;
	float						m_fFrameDelaySub;
	float						m_fFrameDelayEnd;
	float						m_fSlamSpeed;						// ������� ���� �ӵ�
	float						m_fRigidTime;						// ���� �ð�
	float						m_fAttackAngle;						// ���� ����
	float						m_fDefenseCrashRate;				// ����� ��� ���� Ȯ��
	float						m_fGuardCrash;						// ����ũ���� ��

	int							m_iSuperArmorBreak;					// ���۾ƸӸ� �� �� �ִ��ĸ� �����ϴ� ��

	bool						m_bDownAttack;						// �ٿ�� ���� ���� �����Ѱ�?
	bool						m_bSpinAttack;						// ȸ�� �˴ٿ� �����ΰ�?
																	// ���� ���� ��
																	//////////////////////////////////////////////////////////////////////////

	CFrameEventAttackValue( const CActionData & actionData );

	static float					GetDefaultDamageVelocity( C9ActionAttackType attackType );
	static float					GetDefaultDamageAcceleration( C9ActionAttackType attackType );
	static float					GetDefaultFlyFinalHeight( C9ActionAttackType attackType );
	static float					GetDefaultFloatTime( C9ActionAttackType attackType );

	bool							LoadXML( XMLNode *pXMLNode , C9ActionAttackType attackType );
	void							Dump( C9File * pFile );
};
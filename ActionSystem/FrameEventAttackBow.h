#pragma once

#include "FrameEventDefine.h"
#include "FrameEventAttackNormal.h"
#include "ActionContantable.h"
#include "FrameEventCameraShake.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CActionData;
class CFrameEventAttackBow : public CFrameEventAttackNormal
{
public:

	enum ServerManagedProjectileType
	{
		ServerManagedProjectileType_None ,
		ServerManagedProjectileType_Bounce ,

		ServerManagedProjectileType_MAX ,
	};

	enum ArrowTargetType					// TARGET PROCESS TYPE. �߻�ü �߻�� shootelement�� target ���ڸ� ��� ���Ұ����� �� ������ �÷��� 
	{
		TargetType_Normal ,
		TargetType_Abnormal ,
		TargetType_AutoTarget ,
		TargetType_AutoRandomTarget ,		// Ÿ���� �����ϰ� �����ϱ� ���� Ÿ��
		TargetType_None ,
	};

	enum ArrowFireType
	{
		FireType_Single ,				// �ܹ� �߻�ü
		FireType_Shotgun ,				// ��ź �߻�ü
		FireType_MultiShot ,			// ��Ƽ �� ����(�������� ���� ������ ������ ����)
		FireType_MultiShotV ,			// ��Ƽ �� ����(�������� ���� ������ ������ ����)
		FireType_ArrayShot ,			// ��� �� ����(�������� ���� �ʺ�� �������� ���ĵǾ� ����)
		FireType_ArrayShotV ,			// ��� �� ����(�������� ���� �ʺ�� �������� ���ĵǾ� ����)
		FireType_MultiShot_AutoTarget ,	// �ڵ� Ÿ���� �Ǿ� �������� ����

		FireType_Abnormal ,				// Ư�� �����̻��� ���� ������ �ڵ� Ÿ����
		FireType_Target ,				// ���� ������ Target ��������
		FireType_SingleCorner ,			// �ܹ� �߻�ü������ SpreadAngle�������� ���� �߻�
		FireType_SingleCornerV
	};

	enum ArrowLockOnType
	{
		LockOnType_Off ,			// PC : ������ ����, NPC : ĳ������ ȸ�� ����		
		LockOnType_Current ,		// ���� Ÿ��
		LockOnType_Locked ,			// ������ �̺�Ʈ���� �� ������
		LockOnType_Bone ,			// ���� ȸ�� ����
		LockOnType_Order ,			// ��� ���� ��ġ
	};

	enum ArrowFlyType
	{
		FlyType_Normal ,			// �		
		FlyType_Guided ,			// ����
		FlyType_Ground ,			// ���� Ÿ�� ����.
		FlyType_GroundGuided ,		// ���� Ÿ�� ����
		FlyType_Bounce ,			// ���� ���̷� ƨ��鼭 ���� 
		FlyType_Circle ,
		FlyType_Wave ,				// ���̺� ����

	};

	enum ArrowHitType
	{
		HitType_All ,
		HitType_Terrain ,
	};

	// �׼� ���� /////////////////////////////////////
	struct C9CopyActionValueBow
	{
		float			m_fShotRange;
		float			m_fAttackSpeed;
		float			m_fAttackRadius;
		float			m_fEffectScale;
		float			m_fBowEffectScale;
		float			m_fEndEffectScale;
		float			m_fRayCount;
		INT16			m_nSpreadAngle;
		INT16			m_nTargetCheckAngle;


		C9CopyActionValueBow()
		{
			memset( this , 0 , sizeof( C9CopyActionValueBow ) );
		}
	};

	static ArrowTargetType	Parse_TargetType( const char * pszType );
	static ArrowTargetType	Convert_FireToTargetType( const char * pszType );	//Ÿ�� Ÿ�� None �Ͻ� ���̾� Ÿ�Կ��� ���Ƿ� Ÿ�� Ÿ���� ���Ѵ�
	static ArrowFireType	Parse_FireType( const char * pszType );
	static ArrowLockOnType	Parse_LockOnType( const char * pszType );
	static ArrowFlyType		Parse_FlyType( const char * pszType );
	static ArrowHitType		Parse_HitType( const char * pszType );

public:
	CFrameEventAttackBow( const CActionData & actionData );

	virtual CFrameEventType		GetType() const { return CFE_AttackBow; }
	virtual bool				IsProjectileAttackFrameEvent() const { return true; }		// �߻�ü ���Ÿ� ���� ����������

	virtual bool				LoadXML( XMLNode *pXMLNode , List_PreloadString &lstPreloadEffect , List_PreloadString &lstPreloadSound , const char * pszClassName = NULL );
	virtual void				Dump( C9File * pFile , List_PreloadString & lstPreloadEffect , List_PreloadString &lstPreloadSound );

	// �׼� ����
	virtual void				LoadXMLCopyActionValue( XMLNode *pXMLNode );
	virtual void				CopyActionValue( CFrameEvent *pFrameEvent , int iLevel );
	bool						IsServerManagedProjectile() const { return m_ServerManagedType != ServerManagedProjectileType_None; }
private:
	bool						DetermineServerManagedType();
	virtual float				GetLifeTime() { return m_fShootRange / m_fAttackSpeed; }
	virtual	int					GetRayCount() { return m_nRay; }
	virtual	int					GetMaxRayCount() { return m_nMaxRay; }
public:
	int							m_nBowFireBoneIndex;		// ȭ�� �߻�� ������ġ�� ����� ���� ��ġ(Index, ���� ���� )
	CFrameEventCameraShake		m_FrameEventCameraShake;

	ServerManagedProjectileType m_ServerManagedType;

	// �߰���
	vector< CAddAttackValue >	m_AddAttackSpeed;
	vector< CAddAttackValue >	m_AddAttackRange;
	vector< CAddAttackValue >	m_AddShootRange;

	string						m_strBowFireBoneName;		// ȭ�� �߻�� ������ġ�� ����� ���� ��ġ
	string						m_strBowEffectFile;			// �߻�ü ����Ʈ ���ϸ�
	string						m_strEndEffectFile;			// Ÿ�� ����Ʈ ���ϸ�
	string						m_strBowFixedEffectFile;	// ���� �߻�ü ����Ʈ ���ϸ�
	string						m_strBowBreakEffectFile;	// �μ��� �߻�ü ����Ʈ ���ϸ�

#ifndef _GAME_RELEASE_

	C9CopyActionValueBow		m_CopyActionValueBow;

#endif
	//////////////////////////////////////////////////////////////////////////
	// ���� ����
	ArrowTargetType				m_TargetType;
	ArrowFireType				m_FireType;
	ArrowLockOnType				m_LockOnType;
	ArrowFlyType				m_FlyType;
	ArrowHitType				m_HitType;

	float						m_fPierceTerm;			// �����ϴ� �߿�, ���� ĳ���Ϳ� ���Ͽ� �������� �߻��ϴ� ����

	float						m_fAttackSpeed;			// �߻�ü �ӵ�
	float						m_fAttackRadius;		// �߻�ü ������
	float						m_fAttackAccelerate;	// �߻�ü ���ӵ�
	float						m_fAttackHeight;		// ������ ��� ����
	float						m_fShootRange;			// ��ȿ ��Ÿ�

														// ���� ����
	float						m_fTrailSize;
	int							m_nTrailStep;
	color						m_clrTrailColor;
	float						m_fTrailRenewInterval;

	INT16						m_nRotateAngle;
	float						m_fDisAdjustRate4Rotate;			//ȸ���Ҷ� �߻�ü�� �̵� �Ÿ��� ���� �ִ� ȸ�� ������ ���� ���
	int							m_iBouncingLimit;					//flytype_bounce �϶� ƨ��� �ִ� �ִ� Ƚ��
	float						m_fBouncingDistance;				//flytype_bounce ƨ�� ���� Ÿ���� �����Ҷ� Ÿ�����Ҽ� �ִ� �ִ� �Ÿ�
	float						m_fMinorAxis;
	// ����Ʈ ������
	float						m_fEffectScale;
	float						m_fBowEffectScale;
	float						m_fEndEffectScale;
	float						m_fBowFixedEffectScale;
	float						m_fBowBreakEffectScale;
	float						m_fBowFixedDeep;					// ȭ���� ������ ����(Ƣ��� ����)

	float						m_fFireDist;				// ������ �߻� �Ÿ�
	vector3						m_vecFireAxis;				// ������ �߻� ���� ��
	INT16						m_nVerticalAngle;

	int							m_nRay;
	int							m_nMaxRay;
	INT16						m_nSpreadAngle;
	INT16						m_nTargetCheckAngle;
	INT16						m_nBounceAngle;

	DWORD						m_dwAbnType;				// �����̻� Ÿ�Ժ���
	DWORD						m_dwAbnEffIndex;			// ����Ʈ�����̻��� ����Ʈ�ε������� - �����̻�Ÿ������ ����Ʈ�����̻��϶��� ���
	DWORD						m_dwAbnormalKey;			// �����̻� Ű ����
	bool						m_bEnemyInScreen;			// ��ũ���ȿ� �ִ� ������� �����Ҷ� 

	float						m_fWaveFrequncy;			//������ ��
	float						m_fWaveMagnitude;			//������ ����
	int							m_iAngle;					//������ ȸ����

	bool						m_bPierce;					// �����ϴ� �߻�ü �ΰ�?
	bool						m_bTrailGlare;
	bool						m_bEffectDistCheck;
	bool						m_bCurveGuided;
	bool						m_bScalingAxis;
	bool						m_bNoTargetShotType;	//�߻�ÿ� Ÿ���� ������ �ʴ´� 
	bool						m_bIsBouncingBack;		//flytype_bounce �϶� ƨ�ܼ� �����ڿ��� ���ƿ��°�

														// ���� ���� ��
														//////////////////////////////////////////////////////////////////////////
};

inline CFrameEventAttackBow::CFrameEventAttackBow( const CActionData & actionData )
	: CFrameEventAttackNormal( actionData )

	, m_nBowFireBoneIndex( -1 )

	, m_FrameEventCameraShake()

	, m_AddAttackSpeed()
	, m_AddAttackRange()
	, m_AddShootRange()

	, m_strBowFireBoneName( "" )
	, m_strBowEffectFile( "" )
	, m_strEndEffectFile( "" )
	, m_strBowFixedEffectFile( "" )
	, m_strBowBreakEffectFile( "" )

	, m_TargetType( TargetType_None )
	, m_FireType( FireType_Single )
	, m_LockOnType( LockOnType_Current )
	, m_FlyType( FlyType_Normal )
	, m_HitType( HitType_All )
	, m_ServerManagedType( ServerManagedProjectileType_None )
	, m_fPierceTerm( 1.0f )

	, m_fAttackSpeed( 5000.0f )
	, m_fAttackRadius( 10.0f )
	, m_fAttackAccelerate( -100.0f )
	, m_fAttackHeight( 0.0f )
	, m_fShootRange( 5000.0f )

	, m_fTrailSize( 2.0f )
	, m_nTrailStep( 0 )
	, m_clrTrailColor( 127 , 255 , 0 , 0 )
	, m_fTrailRenewInterval( 0.05f )

	, m_nRotateAngle( 0 )
	, m_bCurveGuided( false )

	, m_fEffectScale( 1.0f )
	, m_fBowEffectScale( 1.0f )
	, m_fEndEffectScale( 1.0f )
	, m_fBowFixedEffectScale( 1.0f )
	, m_fBowBreakEffectScale( 1.0f )
	, m_fBowFixedDeep( 0.0f )

	, m_fFireDist( 1.0f )
	, m_vecFireAxis( 0.0f , 0.0f , 1.0f )
	, m_nVerticalAngle( 0 )

	, m_nRay( 1 )
	, m_nMaxRay( 1 )
	, m_nSpreadAngle( 30 )
	, m_nTargetCheckAngle( 30 )
	, m_nBounceAngle( 30 )

	, m_dwAbnType( 0 )
	, m_dwAbnEffIndex( 0 )
	, m_dwAbnormalKey( 0 )
	, m_bEnemyInScreen( false )

	, m_bPierce( false )
	, m_bTrailGlare( false )
	, m_bEffectDistCheck( true )
	, m_iBouncingLimit( 0 )
	, m_fBouncingDistance( 0 )
	, m_bIsBouncingBack( false )
	, m_fMinorAxis( 0 )
	, m_bScalingAxis( false )
	, m_bNoTargetShotType( false )
	, m_fDisAdjustRate4Rotate( 0 )
	, m_fWaveFrequncy( 1.0f )
	, m_fWaveMagnitude( 1.0f )
	, m_iAngle( 0 )
{
	m_fAttackRange = 100.0f;
	m_AttackValue.m_fAttackAngle = Action::RMATH_PI_OVER_SIX;
	m_AttackValue.m_bDownAttack = true;
	m_DamageDirection = CADD_NormalUp;
}
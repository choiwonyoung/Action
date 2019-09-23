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

	enum ArrowTargetType					// TARGET PROCESS TYPE. 발사체 발사시 shootelement의 target 인자를 어떻게 정할것인지 를 나누는 플래그 
	{
		TargetType_Normal ,
		TargetType_Abnormal ,
		TargetType_AutoTarget ,
		TargetType_AutoRandomTarget ,		// 타겟을 랜덤하게 설정하기 위한 타입
		TargetType_None ,
	};

	enum ArrowFireType
	{
		FireType_Single ,				// 단발 발사체
		FireType_Shotgun ,				// 산탄 발사체
		FireType_MultiShot ,			// 멀티 샷 가로(여러발이 일정 각도로 퍼져서 나감)
		FireType_MultiShotV ,			// 멀티 샷 세로(여러발이 일정 각도로 퍼져서 나감)
		FireType_ArrayShot ,			// 어레이 샷 가로(여러발이 일정 너비로 벌어져서 정렬되어 나감)
		FireType_ArrayShotV ,			// 어레이 샷 세로(여러발이 일정 너비로 벌어져서 정렬되어 나감)
		FireType_MultiShot_AutoTarget ,	// 자동 타겟팅 되어 여러발이 나감

		FireType_Abnormal ,				// 특정 상태이상을 가진 적에게 자동 타겟팅
		FireType_Target ,				// 현재 지정된 Target 방향으로
		FireType_SingleCorner ,			// 단발 발사체이지만 SpreadAngle방향으로 꺽어 발사
		FireType_SingleCornerV
	};

	enum ArrowLockOnType
	{
		LockOnType_Off ,			// PC : 조준점 방향, NPC : 캐릭터의 회전 방향		
		LockOnType_Current ,		// 현재 타겟
		LockOnType_Locked ,			// 프레임 이벤트에서 락 놓은것
		LockOnType_Bone ,			// 본의 회전 방향
		LockOnType_Order ,			// 명령 받은 위치
	};

	enum ArrowFlyType
	{
		FlyType_Normal ,			// 곡선		
		FlyType_Guided ,			// 유도
		FlyType_Ground ,			// 땅을 타고 간다.
		FlyType_GroundGuided ,		// 땅을 타고 유도
		FlyType_Bounce ,			// 적들 사이로 튕기면서 유도 
		FlyType_Circle ,
		FlyType_Wave ,				// 웨이브 파형

	};

	enum ArrowHitType
	{
		HitType_All ,
		HitType_Terrain ,
	};

	// 액션 복사 /////////////////////////////////////
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
	static ArrowTargetType	Convert_FireToTargetType( const char * pszType );	//타겟 타입 None 일시 파이어 타입에서 임의로 타겟 타입을 정한다
	static ArrowFireType	Parse_FireType( const char * pszType );
	static ArrowLockOnType	Parse_LockOnType( const char * pszType );
	static ArrowFlyType		Parse_FlyType( const char * pszType );
	static ArrowHitType		Parse_HitType( const char * pszType );

public:
	CFrameEventAttackBow( const CActionData & actionData );

	virtual CFrameEventType		GetType() const { return CFE_AttackBow; }
	virtual bool				IsProjectileAttackFrameEvent() const { return true; }		// 발사체 원거리 공격 프레임인지

	virtual bool				LoadXML( XMLNode *pXMLNode , List_PreloadString &lstPreloadEffect , List_PreloadString &lstPreloadSound , const char * pszClassName = NULL );
	virtual void				Dump( C9File * pFile , List_PreloadString & lstPreloadEffect , List_PreloadString &lstPreloadSound );

	// 액션 복사
	virtual void				LoadXMLCopyActionValue( XMLNode *pXMLNode );
	virtual void				CopyActionValue( CFrameEvent *pFrameEvent , int iLevel );
	bool						IsServerManagedProjectile() const { return m_ServerManagedType != ServerManagedProjectileType_None; }
private:
	bool						DetermineServerManagedType();
	virtual float				GetLifeTime() { return m_fShootRange / m_fAttackSpeed; }
	virtual	int					GetRayCount() { return m_nRay; }
	virtual	int					GetMaxRayCount() { return m_nMaxRay; }
public:
	int							m_nBowFireBoneIndex;		// 화살 발사시 시작위치로 사용할 본의 위치(Index, 저장 안함 )
	CFrameEventCameraShake		m_FrameEventCameraShake;

	ServerManagedProjectileType m_ServerManagedType;

	// 추가값
	vector< CAddAttackValue >	m_AddAttackSpeed;
	vector< CAddAttackValue >	m_AddAttackRange;
	vector< CAddAttackValue >	m_AddShootRange;

	string						m_strBowFireBoneName;		// 화살 발사시 시작위치로 사용할 본의 위치
	string						m_strBowEffectFile;			// 발사체 이펙트 파일명
	string						m_strEndEffectFile;			// 타격 이펙트 파일명
	string						m_strBowFixedEffectFile;	// 박힌 발사체 이펙트 파일명
	string						m_strBowBreakEffectFile;	// 부서진 발사체 이펙트 파일명

#ifndef _GAME_RELEASE_

	C9CopyActionValueBow		m_CopyActionValueBow;

#endif
	//////////////////////////////////////////////////////////////////////////
	// 묶음 저장
	ArrowTargetType				m_TargetType;
	ArrowFireType				m_FireType;
	ArrowLockOnType				m_LockOnType;
	ArrowFlyType				m_FlyType;
	ArrowHitType				m_HitType;

	float						m_fPierceTerm;			// 관통하는 중에, 같은 캐릭터에 대하여 데미지가 발생하는 간격

	float						m_fAttackSpeed;			// 발사체 속도
	float						m_fAttackRadius;		// 발사체 반지름
	float						m_fAttackAccelerate;	// 발사체 가속도
	float						m_fAttackHeight;		// 포물선 곡선의 높이
	float						m_fShootRange;			// 유효 사거리

														// 궤적 관련
	float						m_fTrailSize;
	int							m_nTrailStep;
	color						m_clrTrailColor;
	float						m_fTrailRenewInterval;

	INT16						m_nRotateAngle;
	float						m_fDisAdjustRate4Rotate;			//회전할때 발사체의 이동 거리에 따라 주는 회전 보정에 대한 계수
	int							m_iBouncingLimit;					//flytype_bounce 일때 튕길수 있는 최대 횟수
	float						m_fBouncingDistance;				//flytype_bounce 튕긴 다음 타겟을 결정할때 타겟팅할수 있는 최대 거리
	float						m_fMinorAxis;
	// 이펙트 스케일
	float						m_fEffectScale;
	float						m_fBowEffectScale;
	float						m_fEndEffectScale;
	float						m_fBowFixedEffectScale;
	float						m_fBowBreakEffectScale;
	float						m_fBowFixedDeep;					// 화살이 꽂히는 깊이(튀어나온 길이)

	float						m_fFireDist;				// 직사형 발사 거리
	vector3						m_vecFireAxis;				// 직사형 발사 방향 축
	INT16						m_nVerticalAngle;

	int							m_nRay;
	int							m_nMaxRay;
	INT16						m_nSpreadAngle;
	INT16						m_nTargetCheckAngle;
	INT16						m_nBounceAngle;

	DWORD						m_dwAbnType;				// 상태이상 타입별로
	DWORD						m_dwAbnEffIndex;			// 이펙트상태이상의 이펙트인덱스별로 - 상태이상타입으로 이펙트상태이상일때만 사용
	DWORD						m_dwAbnormalKey;			// 상태이상 키 별로
	bool						m_bEnemyInScreen;			// 스크린안에 있는 모든적을 공격할때 

	float						m_fWaveFrequncy;			//파장의 빈도
	float						m_fWaveMagnitude;			//파장의 진폭
	int							m_iAngle;					//파장의 회전값

	bool						m_bPierce;					// 관통하는 발사체 인가?
	bool						m_bTrailGlare;
	bool						m_bEffectDistCheck;
	bool						m_bCurveGuided;
	bool						m_bScalingAxis;
	bool						m_bNoTargetShotType;	//발사시에 타겟을 가지지 않는다 
	bool						m_bIsBouncingBack;		//flytype_bounce 일때 튕겨서 시전자에게 돌아오는가

														// 묶음 저장 끝
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
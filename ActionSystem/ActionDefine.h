#pragma once


//#include <hash_map>
#include <wtypes.h>

//using namespace stdext;

#include "ActionChart.h"
#include "AIActionChart.h"

class CAIActionChart;

typedef hash_map<DWORD , CActionChart*>						HashMap_ActionList;
typedef hash_map<DWORD , CActionChart*>::iterator			HashMap_ActionList_Iter;
typedef hash_map<DWORD , CActionChart*>::const_iterator		HashMap_ActionList_ConstIter;

typedef hash_map<DWORD , CAIActionChart* >					HashMap_AIActionList;
typedef hash_map<DWORD , CAIActionChart* >::iterator		HashMap_AIActionList_Iter;
typedef hash_map<DWORD , CAIActionChart* >::const_iterator	HashMap_AIActionList_ConstIter;


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ActionBranch
const UINT64	CI_None				= 0x0000000000000000;
const UINT64	CI_W				= 0x0000000000000001;
const UINT64	CI_WW				= 0x0000000000000002;
const UINT64	CI_W_UP				= 0x0000000000000004;
const UINT64	CI_A				= 0x0000000000000008;
const UINT64	CI_AA				= 0x0000000000000010;
const UINT64	CI_A_UP				= 0x0000000000000020;
const UINT64	CI_D				= 0x0000000000000040;
const UINT64	CI_DD				= 0x0000000000000080;
const UINT64	CI_D_UP				= 0x0000000000000100;
const UINT64	CI_S				= 0x0000000000000200;
const UINT64	CI_SS				= 0x0000000000000400;
const UINT64	CI_S_UP				= 0x0000000000000800;

const UINT64	CI_Q				= 0x0000000000001000;
const UINT64	CI_Q_UP				= 0x0000000000002000;
const UINT64	CI_F				= 0x0000000000004000;
const UINT64	CI_F_UP				= 0x0000000000008000;
const UINT64	CI_E				= 0x0000000000010000;
const UINT64	CI_R				= 0x0000000000020000;

const UINT64	CI_SPACE			= 0x0000000000040000;
const UINT64	CI_SPACESPACE		= 0x0000000000080000;
const UINT64	CI_SPACE_UP			= 0x0000000000100000;
const UINT64	CI_SHIFT			= 0x0000000000200000;
const UINT64	CI_INSERT			= 0x0000000000400000;
const UINT64	CI_CAPSLOCK			= 0x0000000000800000;
const UINT64	CI_TAB				= 0x0000000001000000;

const UINT64	CI_M1				= 0x0000000002000000;
const UINT64	CI_M1_UP			= 0x0000000004000000;
const UINT64	CI_M2				= 0x0000000008000000;
const UINT64	CI_M2_UP			= 0x0000000010000000;

const UINT64	CI_LAND				= 0x0000000020000000;	// 착지 상태
const UINT64	CI_WALL				= 0x0000000040000000;
const UINT64	CI_WATERSINK		= 0x0000000080000000;	// 물에 잠긴 상태(Neck과 Spine2 본 중점이, 트리거 수면 높이보다 낮은경우)

const UINT64	CI_HIT				= 0x0000000100000000;
const UINT64	CI_DAMAGEHIT		= 0x0000000200000000;
const UINT64	CI_CATCH			= 0x0000000400000000;
const UINT64	CI_CANTCATCH		= 0x0000000800000000;
const UINT64	CI_BIGCATCH			= 0x0000001000000000;
const UINT64	CI_HOOK				= 0x0000002000000000;
const UINT64	CI_CASTING			= 0x0000004000000000;

const UINT64	CI_DEFHIT			= 0x0000008000000000;
const UINT64	CI_DEFHITKO			= 0x0000010000000000;

const UINT64	CI_NEARITEM			= 0x0000020000000000;

const UINT64	CI_ARROWHIT			= 0x0000040000000000;

const UINT64	CI_ROTATIONLEFT		= 0x0000080000000000;
const UINT64	CI_ROTATIONRIGHT	= 0x0000100000000000;

const UINT64	CI_EVENT			= 0x0000200000000000;
const UINT64	CI_ACTION			= 0x0000400000000000;
const UINT64	CI_TOGGLE			= 0x0000800000000000;

const UINT64	CI_PVALUE			= 0x0001000000000000;	// 플레이어 변수 검사
const UINT64	CI_PTIMER			= 0x0002000000000000;	// 플레이어 타이머 검사

const UINT64	CI_MAXFURY			= 0x0004000000000000;
const UINT64	CI_PVALUE_SERVER	= 0x0008000000000000;

const UINT64	CI_SKILLBOOK		= 0x0010000000000000;	// 스킥북 액션 변경 여부 검사
const UINT64	CI_MOVEDISTANCE		= 0x0020000000000000;	// 특정 거리 이동

const UINT64	CI_ABNORMAL			= 0x0040000000000000;	// 특정 상태이상에 대한 조건이 만족하는가

const UINT64	CI_DFISHING			= 0x0080000000000000;	// 낚시 조건 .
const UINT64	CI_AUTO_FISHING		= 0x0100000000000000;	// 자동낚시.

const UINT64	CI_DNFISHING		= 0x0200000000000000;	// 낚시 조건 충족 검사.

const UINT64	CI_TALISMAN			= 0x0400000000000000;	// 부적 검사

const UINT64	FORCE_MAX_CI		= 0xFFFFFFFFFFFFFFFF;


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 피격자가 넉다운 하거나 밀릴때의 다른 캐릭터를 넘어트리는 타입
enum	C9KnockDownOtherType
{
	C9KDOT_None ,				// 없음
	C9KDOT_Enemy ,				// 공격자의 적만 넘어트림
	C9KDOT_All ,					// 모두 넘어트림
};

static C9KnockDownOtherType StringToKnockDownOtherType( const char * pszType )
{
	if( strcmp( pszType , "Enemy" ) == 0 )	return C9KDOT_Enemy;
	if( strcmp( pszType , "All" ) == 0 )		return C9KDOT_All;

	return C9KDOT_None;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 공격 대상 타입
enum AttackTargetType
{
	C9ATT_ENEMY ,	// 적군 대상
	C9ATT_OUR ,		// 아군 대상
	C9ATT_OURSELF ,	// 나를 포함한 아군 대상
	C9ATT_ALL ,		// 전체 대상(나를 제외)
};

static AttackTargetType StringToAttackTargetType( const char* pszType )
{
	if( strcmp( pszType , "Our" ) == 0 )		return C9ATT_OUR;
	if( strcmp( pszType , "All" ) == 0 )		return C9ATT_ALL;
	return C9ATT_ENEMY;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 피격자가 넉다운 하거나 밀릴때의 방향을 결정하는 타입
enum	C9ReactDirectionType
{
	C9RDT_HitDirFront ,			// 공격방향 정면으로
	C9RDT_HitDirBack ,			// 공격방향 반대로
	C9RDT_AttackerFront ,		// 공격자 회전 방향 정면으로
	C9RDT_AttackerBack ,		// 공격자 회전 방향 반대로
	C9RDT_SuffererFront ,		// 피격자 회전 방향 반대로
	C9RDT_SuffererBack ,		// 피격자 회전 방향 반대로
};

static C9ReactDirectionType StringToReactDirectionType( const char * pszType )
{
	if( strcmp( pszType , "HitDirBack" ) == 0 )		return C9RDT_HitDirBack;
	if( strcmp( pszType , "AttackerFront" ) == 0 )	return C9RDT_AttackerFront;
	if( strcmp( pszType , "AttackerBack" ) == 0 )	return C9RDT_AttackerBack;
	if( strcmp( pszType , "SuffererFront" ) == 0 )	return C9RDT_SuffererFront;
	if( strcmp( pszType , "SuffererBack" ) == 0 )	return C9RDT_SuffererBack;

	return C9RDT_HitDirFront;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
enum C9ActionDamageDirection
{
	CADD_NormalDown ,		// ----> "DAMAGE_D" 액션 호출
	CADD_NormalLeft ,		// ----> "DAMAGE_L" 액션 호출
	CADD_NormalRight ,		// ----> "DAMAGE_R" 액션 호출
	CADD_NormalUp ,			// ----> "DAMAGE_U"	액션 호출	
	CADD_DownDamage ,		// ----> "DOWN_DMAGE" 넉다운 액션 호출
	CADD_FlyingDamage ,		// ----> "DOWN2_DAMAGE" 액션 호출
	CADD_Rigid ,				// ----> "DAMAGE_RIGID" 호출
	CADD_None ,				// ---->  데미지 액션 없음
	CADD_MAX = 0x7F				// ----> 아무 의미 없음 그냥 해당 변수에서 최대 값을 명시하기 위해 사용함 C9_MESSAGE_SET_DAMAGE_ACTION 의 m_iActionDamageDirection 변수 에 사용
};

static C9ActionDamageDirection		StringToActionDamageDirection( const char * pszType )
{
	if( strcmp( pszType , "Down" ) == 0 )			return CADD_NormalDown;
	if( strcmp( pszType , "Left" ) == 0 )			return CADD_NormalLeft;
	if( strcmp( pszType , "Right" ) == 0 )			return CADD_NormalRight;
	if( strcmp( pszType , "Up" ) == 0 )				return CADD_NormalUp;
	if( strcmp( pszType , "None" ) == 0 )			return CADD_None;
	if( strcmp( pszType , "DownDamage" ) == 0 )		return CADD_DownDamage;
	if( strcmp( pszType , "Rigid" ) == 0 )			return CADD_Rigid;

	char strError[256];
	sprintf_s( strError , 256 , "알수없는 타입(%s) -> AttackDirection" , pszType );
	MessageBoxA( NULL , strError , "Error" , MB_OK );

	return CADD_NormalDown;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
enum C9ActionAttackType
{
	CAAT_Normal ,			// 일반 공격
	CAAT_Push ,				// 밀리기 공격
	CAAT_Down ,				// 아래 공격 (밟기)
	CAAT_DownFly ,			// 다운한 상대를 띄우는 공격
	CAAT_Catch ,				// 잡기 공격
	CAAT_Knockdown ,			// 넘어뜨리기 공격
	CAAT_FlyInAttack ,		// 띄운 대상 공격
	CAAT_Rigid ,				// 경직
	CAAT_TagetCatch ,		// 공격 성공한 상대 잡기

	CAAT_None = 0x7F ,			//127  7비트의 최대수 C9_MESSAGE_SET_DAMAGE_ACTION 의 m_iActionAttackType 에 맞춰 변경
};

static C9ActionAttackType		StringToActionAttackType( const char * pszType )
{
	if( strcmp( pszType , "Normal" ) == 0 )			return CAAT_Normal;
	if( strcmp( pszType , "Push" ) == 0 )			return CAAT_Push;
	if( strcmp( pszType , "Down" ) == 0 )			return CAAT_Down;
	if( strcmp( pszType , "Catch" ) == 0 )			return CAAT_Catch;
	if( strcmp( pszType , "KnockDown" ) == 0 )		return CAAT_Knockdown;
	if( strcmp( pszType , "FlyAttack" ) == 0 )		return CAAT_FlyInAttack;
	if( strcmp( pszType , "Rigid" ) == 0 )			return CAAT_Rigid;
	if( strcmp( pszType , "DownFly" ) == 0 )			return CAAT_DownFly;
	if( strcmp( pszType , "TagetCatch" ) == 0 )		return CAAT_TagetCatch;
	if( strcmp( pszType , "None" ) == 0 )			return CAAT_None;

	char strError[256];
	sprintf_s( strError , 256 , "알수없는 타입(%s) -> AttackType" , pszType );
	MessageBoxA( NULL , strError , "Error" , MB_OK );

	return CAAT_Normal;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
enum C9_SKILL_TARGET_TYPE
{
	C9_SKILL_TARGET_CURRUNT = 0 ,
	C9_SKILL_TARGET_PARENT ,		// 부모
	C9_SKILL_TARGET_OTHER ,		// 적
	C9_SKILL_TARGET_OUR ,		// 아군
	C9_SKILL_TARGET_MYSELF ,		// 자기자신
	C9_SKILL_TARGET_OURSELF ,	// 아군(자기자신포함)
};

static C9_SKILL_TARGET_TYPE	StringToSkillTargetType( const char * pszType )
{
	if( strcmp( pszType , "Parent" ) == 0 )		return C9_SKILL_TARGET_PARENT;
	if( strcmp( pszType , "Our" ) == 0 )			return C9_SKILL_TARGET_OUR;
	if( strcmp( pszType , "Other" ) == 0 )		return C9_SKILL_TARGET_OTHER;
	if( strcmp( pszType , "Self" ) == 0 )		return C9_SKILL_TARGET_MYSELF;
	if( strcmp( pszType , "OurSelf" ) == 0 )		return C9_SKILL_TARGET_OURSELF;

	return C9_SKILL_TARGET_CURRUNT;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 손 타입
enum C9HANDTYPE
{
	C9HANDTYPE_RIGHT ,
	C9HANDTYPE_LEFT ,
	C9HANDTYPE_MAX ,
};

static C9HANDTYPE	StringToHandType( const char * pszHandType )
{

	if( strcmp( pszHandType , "Left" ) == 0 )			return C9HANDTYPE_LEFT;
	else if( strcmp( pszHandType , "Right" ) == 0 )		return C9HANDTYPE_RIGHT;

	return C9HANDTYPE_RIGHT;
}



enum AIConditionType
{
	TYPE_CAICondition_None ,
	TYPE_CAICondition_SearchAttackTarget ,
	TYPE_CAICondition_Random ,
	TYPE_CAICondition_CheckTargetRange ,
	TYPE_CAICondition_SearchTargetAngle ,
	TYPE_CAICondition_CheckRunTimer ,
	TYPE_CAICondition_CheckSelfStates ,
	TYPE_CAICondition_CheckTargetStates ,
	TYPE_CAICondition_CheckValue ,
	TYPE_CAICondition_CheckTutorialValue ,
	TYPE_CAICondition_CheckOurStates ,
	TYPE_CAICondition_CheckOtherStates ,
	TYPE_CAICondition_CheckEventValue ,
	TYPE_CAICondition_CheckAreaRange ,
	TYPE_CAICondition_CheckSkillTimer ,
	TYPE_CAICondition_CheckRideTarget ,
	TYPE_CAICondition_CheckLevel ,
	TYPE_CAICondition_CheckActionTimer ,
	TYPE_CAICondition_MAX ,
};

enum AIActionChartType
{
	TYPE_CAIActionChart_None ,
	TYPE_CAIActionChart_Wait ,
	TYPE_CAIActionChart_WaitOrder ,
	TYPE_CAIActionChart_WalkRandom ,
	TYPE_CAIActionChart_RotationTarget ,
	TYPE_CAIActionChart_RunTarget ,
	TYPE_CAIActionChart_RunPosition ,
	TYPE_CAIActionChart_Attack ,
	TYPE_CAIActionChart_AttackWaitWalk ,
	TYPE_CAIActionChart_Damage ,
	TYPE_CAIActionChart_FlyTurning ,
	TYPE_CAIActionChart_FlyTarget ,
	TYPE_CAIActionChart_Skill ,
	TYPE_CAIActionChart_Order ,
	TYPE_CAIActionChart_MoveArea ,
	TYPE_CAIActionChart_ToCelling ,
	TYPE_CAIActionChart_AirMoving ,
	TYPE_CAIActionChart_Threat ,
	TYPE_CAIActionChart_LandTarget ,
	TYPE_CAIActionChart_Teleport ,
	TYPE_CAIActionChart_MoveJump ,
	TYPE_CAIActionChart_RunAway ,
};

enum AIExecuteType
{
	TYPE_CAIExecute_None ,
	TYPE_CAIExecute_RunAIAction ,
	TYPE_CAIExecute_SkipExecute ,
	TYPE_CAIExecute_RunTimer ,
	TYPE_CAIExecute_SetValue ,
	TYPE_CAIExecute_SetSkillTimer ,
	TYPE_CAIExecute_AISpeech ,
	TYPE_CAIExecute_SetActionIndex ,
	TYPE_CAIExecute_GiveOrder ,
	TYPE_CAIExecute_RunActionTimer ,
	TYPE_CAIExecute_MAX ,
};

enum DamageState
{
	CDS_NONE ,
	CDS_NORMAL ,
	CDS_SKILL ,
	CDS_PULL ,
	CDS_CATCH ,
	CDS_DOWN ,
	CDS_STANDUP ,
	CDS_KNOCKDOWN ,
	CDS_DEAD ,
	CDS_DEFENCE_PUSH ,
	CDS_ICED ,
	CDS_STUN ,
	CDS_RIGID ,
	CDS_WALLSTUN ,			// 벽에 부딧혀 스턴이 된 상태
	CDS_HOOK ,

	CDS_MAX ,
};

enum SEARCHTARGET_TYPE
{
	SEARCHTARGET_NONE = 0 ,
	SEARCHTARGET_PLAYER ,
	SEARCHTARGET_PARENT ,
	SEARCHTARGET_EVENT ,
	SEARCHTARGET_ABNORMAL ,
	SEARCHTARGET_OTHER ,
	SEARCHTARGET_THREAT ,
};

class color
{
public:
	union
	{
		struct
		{
			unsigned char b , g , r , a;
		};
		long c;
	};

	color::color( unsigned char ia , unsigned char ir , unsigned char ig , unsigned char ib ) : a( ia ) , r( ir ) , g( ig ) , b( ib ) {}
	color( long lnColor ) : c( lnColor ) {}

	color() {};
	~color() {};
};


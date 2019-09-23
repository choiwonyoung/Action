#pragma once

class CFrameEventAttackNormal;

namespace Action
{
	extern const DWORD C9_CRC_CODE_ACTION_None;
	extern const DWORD C9_CRC_CODE_ACTION_Start_Action;
	extern const DWORD C9_CRC_CODE_ACTION_WAIT;
	extern const DWORD C9_CRC_CODE_ACTION_WAIT_BATTLE;
	extern const DWORD C9_CRC_CODE_ACTION_SUMMON;
	extern const DWORD C9_CRC_CODE_ACTION_DAMAGE_GUARDCRASH;
	extern const DWORD C9_CRC_CODE_ACTION_SUICIDE_DEAD;
	extern const DWORD C9_CRC_CODE_ACTION_STAND_UP;
	extern const DWORD C9_CRC_CODE_ACTION_STAND_UP2;
	extern const DWORD C9_CRC_CODE_ACTION_STUN;
	extern const DWORD C9_CRC_CODE_ACTION_DEAD_DOWN;
	extern const DWORD C9_CRC_CODE_ACTION_DEAD_END;
	extern const DWORD C9_CRC_CODE_ACTION_DEAD_ACTION;
	extern const DWORD C9_CRC_CODE_ACTION_BOUND_DOWN;
	extern const DWORD C9_CRC_CODE_ACTION_Revive_Action;
	extern const DWORD C9_CRC_CODE_ACTION_CATCH_FAILED;
	extern const DWORD C9_CRC_CODE_ACTION_LEVEL_UP;
	extern const DWORD C9_CRC_CODE_ACTION_CLASSCHANGE;
	extern const DWORD C9_CRC_CODE_ACTION_PICK_ITEM;
	extern const DWORD C9_CRC_CODE_ACTION_EVENT_ACTION;

	extern const DWORD C9_CRC_CODE_ACTION_RUN;
	extern const DWORD C9_CRC_CODE_ACTION_WALKLEFT;
	extern const DWORD C9_CRC_CODE_ACTION_WALKRIGHT;
	extern const DWORD C9_CRC_CODE_ACTION_WALKBACK;
	extern const DWORD C9_CRC_CODE_ACTION_MOUSE_RUN;

	extern const DWORD C9_CRC_CODE_ACTION_Move_Front;
	extern const DWORD C9_CRC_CODE_ACTION_Move_Left;
	extern const DWORD C9_CRC_CODE_ACTION_Move_Right;
	extern const DWORD C9_CRC_CODE_ACTION_Move_Back;

	extern const DWORD C9_CRC_CODE_ACTION_JUMP_UP;
	extern const DWORD C9_CRC_CODE_ACTION_JUMP_A;
	extern const DWORD C9_CRC_CODE_ACTION_JUMP_B;
	extern const DWORD C9_CRC_CODE_ACTION_JUMP_C;

	extern const DWORD C9_CRC_CODE_ACTION_JUMP_FALL;
	extern const DWORD C9_CRC_CODE_ACTION_JUMP_FALL_FRONT;
	extern const DWORD C9_CRC_CODE_ACTION_JUMP_FALL_LEFT;
	extern const DWORD C9_CRC_CODE_ACTION_JUMP_FALL_RIGHT;
	extern const DWORD C9_CRC_CODE_ACTION_JUMP_FALL_BACK;

	extern const DWORD C9_CRC_CODE_ACTION_DAMAGE_D;
	extern const DWORD C9_CRC_CODE_ACTION_DAMAGE_L;
	extern const DWORD C9_CRC_CODE_ACTION_DAMAGE_R;
	extern const DWORD C9_CRC_CODE_ACTION_DAMAGE_U;
	extern const DWORD C9_CRC_CODE_ACTION_DAMAGE_CATCH_ME;
	extern const DWORD C9_CRC_CODE_ACTION_DOWN_DAMAGE;
	extern const DWORD C9_CRC_CODE_ACTION_DAMAGE_RIGID;
	extern const DWORD C9_CRC_CODE_ACTION_DOWN_A;
	extern const DWORD C9_CRC_CODE_ACTION_DOWN2_A;

	extern const DWORD C9_CRC_CODE_ACTION_DAMAGE_THROW_A;
	extern const DWORD C9_CRC_CODE_ACTION_DAMAGE_THROW_B;
	extern const DWORD C9_CRC_CODE_ACTION_DAMAGE_THROW_C;
	extern const DWORD C9_CRC_CODE_ACTION_DAMAGE_THROW2_A;
	extern const DWORD C9_CRC_CODE_ACTION_DAMAGE_THROW2_B;
	extern const DWORD C9_CRC_CODE_ACTION_DAMAGE_THROW2_C;
	extern const DWORD C9_CRC_CODE_ACTION_DAMAGE_THROW3_A;
	extern const DWORD C9_CRC_CODE_ACTION_DAMAGE_THROW3_B;
	extern const DWORD C9_CRC_CODE_ACTION_DAMAGE_THROW3_C;
		
	extern const DWORD C9_CRC_CODE_ACTION_DAMAGE_D_STANCE2;
	extern const DWORD C9_CRC_CODE_ACTION_DAMAGE_L_STANCE2;
	extern const DWORD C9_CRC_CODE_ACTION_DAMAGE_R_STANCE2;
	extern const DWORD C9_CRC_CODE_ACTION_DAMAGE_U_STANCE2;
	extern const DWORD C9_CRC_CODE_ACTION_DAMAGE_CATCH_ME_STANCE2;
	extern const DWORD C9_CRC_CODE_ACTION_DOWN_DAMAGE_STANCE2;
	extern const DWORD C9_CRC_CODE_ACTION_DAMAGE_RIGID_STANCE2;
	extern const DWORD C9_CRC_CODE_ACTION_DOWN_A_STANCE2;
	extern const DWORD C9_CRC_CODE_ACTION_DOWN2_A_STANCE2;

	extern const DWORD C9_CRC_CODE_ACTION_DAMAGE_THROW_A_STANCE2;
	extern const DWORD C9_CRC_CODE_ACTION_DAMAGE_THROW_B_STANCE2;
	extern const DWORD C9_CRC_CODE_ACTION_DAMAGE_THROW_C_STANCE2;
	extern const DWORD C9_CRC_CODE_ACTION_DAMAGE_THROW2_A_STANCE2;
	extern const DWORD C9_CRC_CODE_ACTION_DAMAGE_THROW2_B_STANCE2;
	extern const DWORD C9_CRC_CODE_ACTION_DAMAGE_THROW2_C_STANCE2;
	extern const DWORD C9_CRC_CODE_ACTION_DAMAGE_THROW3_A_STANCE2;
	extern const DWORD C9_CRC_CODE_ACTION_DAMAGE_THROW3_B_STANCE2;
	extern const DWORD C9_CRC_CODE_ACTION_DAMAGE_THROW3_C_STANCE2;

	extern const DWORD C9_CRC_CODE_ACTION_STAND_UP_STANCE2;
	extern const DWORD C9_CRC_CODE_ACTION_STAND_UP2_STANCE2;
	
	extern const DWORD C9_CRC_CODE_AI_ACTION_ATTACK_NORMAL;
	extern const DWORD C9_CRC_CODE_AI_ACTION_DAMAGE;
	extern const DWORD C9_CRC_CODE_AI_ACTION_FOLLOWPLAYER;

	extern const DWORD C9_CRC_CODE_ACTION_SWIM_RUN;

	extern const DWORD C9_CRC_CODE_PLAYERVALUE_HASH_CODE_STANCE;

	extern const DWORD C9_CRC_CODE_AI_ACTION_TELEPORT_TO_PC;

	extern const DWORD C9_CRC_CODE_ACTION_PLAYEND_INIT;
	extern const DWORD C9_CRC_CODE_ACTION_FISHING_UNINSTALL;

	extern const DWORD C9_CRC_CODE_ACTION_AWAKEN_LEVEL_UP;


	class CSendAttackData
	{
	public:
		CSendAttackData() : m_pAttackNormal( NULL ) , m_iAttackHitType( 0 ) , m_iAnimationFrame( 0 ) , m_iUseItemID( 0 ) , m_dwActionCode( 0 ) , m_iActionPassIndex( 0 ) { }
		vector<INT64>					m_TargetList;
		int								m_iAttackHitType;
		const CFrameEventAttackNormal*	m_pAttackNormal;
		int								m_iAnimationFrame;
		int								m_iActionPassIndex;
		INT64							m_iUseItemID;		
		DWORD							m_dwActionCode;
	};

	class ActionString
	{
	public:
		static string ToUpper( string& str );
		static string GetToken( string orig , int nToken , char* strSep = NULL );
		static bool GetStrParam( const char* pStrString , int iIndex , char* pStrParam );
		static void BufferFree( void * pData );
	};

	

	const float RMATH_PI				= 3.1415926535897932384626433832795f;
	const float RMATH_QUARTER_PI		= RMATH_PI / 4.0f;
	const float RMATH_PI_OVER_SIX		= RMATH_PI / 6.0f;
	const float RMATH_HALF_PI			= RMATH_PI / 2.0f;
	const float RMATH_TWO_PI			= RMATH_PI * 2.0f;
	const float RMATH_DEG2RAD			= RMATH_PI / 180.0f;	// (RMATH_PI / 180.0f, 60분법을 호도법으로: ex) fRadian = nDegree * RMATH_DEG2RAD;
	const float RMATH_RAD2DEG			= 180.0f / RMATH_PI;	// (180.0f / RMATH_PI, 호도법을 60분법으로: ex) nDegree = fRadian * RMATH_RAD2DEG;


	#define vector3 XMFLOAT3
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
struct CValueParam
{
	string			strName;
	string			strIconName;
	int				iValue;
	DWORD			dwHash;

	CValueParam();
	bool			LoadXML( RXMLNode * pNode );
	void			Dump( C9File * pFile );
};

class CSendAttackData
{
public:
	CSendAttackData() : m_pAttackNormal( NULL ) , m_iAttackHitType( 0 ) , m_iAnimationFrame( 0 ) , m_iUseItemID( 0 ) , m_dwActionCode( 0 ) , m_iActionPassIndex( 0 ) { }
	vector<INT64>					m_TargetList;
	int								m_iAttackHitType;
	const CFrameEventAttackNormal*	m_pAttackNormal;
	int								m_iAnimationFrame;
	int								m_iActionPassIndex;
	INT64							m_iUseItemID;
	DWORD							m_dwActionCode;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// AdditionMove
enum C9AdditionMove
{
	CAM_None ,

	CAM_AddMove ,			// 일반 이동
	CAM_NormalJump ,		// 일반(롱) 점프
	CAM_ShortJump ,			// 짧은 점프

	CAM_AimRotation ,		// 타겟 조준
	CAM_AimRotationMove ,	// 타겟 조준 및 회전가능
	CAM_AimRange ,			// 원거리 조준

	CAM_UpRotation ,			// 캐릭터의 윗방향으로 이동, Fly시 점프키를 누르는 경우 하늘위로 이동함
	CAM_NoneFlyRotation ,	// Fly시 캐릭터 회전 불가능 (카메라 회전 가능) 
	CAM_FlyRotation ,		// Fly시 일반회전 (카메라 방향으로 회전 이동)
	CAM_FlyUpRotation ,		// fly 회전 ( 위로 회전시 : 머리방향으로 )

	CAM_FromAnimation ,		// 애니메이션에서의 위치 지정

	CAM_ShorterJump ,		// 더 짧은 점프
};

static C9AdditionMove	StringToAdditionMove( const char * pszType )
{
	if( strcmp( pszType , "None" ) == 0 )					return CAM_None;
	if( strcmp( pszType , "AddMove" ) == 0 )				return CAM_AddMove;

	if( strcmp( pszType , "Jump" ) == 0 )					return CAM_NormalJump;
	if( strcmp( pszType , "ShortJump" ) == 0 )				return CAM_ShortJump;

	if( strcmp( pszType , "AimRotation" ) == 0 )			return CAM_AimRotation;
	if( strcmp( pszType , "AimRotationMove" ) == 0 )		return CAM_AimRotationMove;
	if( strcmp( pszType , "AimRange" ) == 0 )				return CAM_AimRange;

	if( strcmp( pszType , "UpRotation" ) == 0 )				return CAM_UpRotation;
	if( strcmp( pszType , "NoneFlyRotation" ) == 0 )		return CAM_NoneFlyRotation;
	if( strcmp( pszType , "FlyRotation" ) == 0 )			return CAM_FlyRotation;
	if( strcmp( pszType , "FlyUpRotation" ) == 0 )			return CAM_FlyUpRotation;

	if( strcmp( pszType , "FromAnimation" ) == 0 )			return CAM_FromAnimation;

	if( strcmp( pszType , "ShorterJump" ) == 0 )			return CAM_ShorterJump;

	char strError[256];
	sprintf_s( strError , 256 , "알수없는 타입(%s) -> AdditionMove" , pszType );
	MessageBoxA( NULL , strError , "Error" , MB_OK );

	return CAM_None;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// RotationType
enum C9RotationType
{
	CRT_NoneRotation ,			// 마우스 회전시 카메라 및 캐릭터 회전 안됨
	CRT_CameraRotation ,		// 마우스 회전시 카메라만 회전
	CRT_CharacterRotation ,		// 마우스 회전시 캐릭터 및 카메라 회전	( 기본값 )
	CRT_SlowCharacterRotation ,	// 마우스 회전시 캐릭터가 카메라를 따라서 천천히 회전됨
	CRT_FirstRotation ,			// 처음시작시만 카메라에 의해 회전되고 그 이후에는 고정됨
	CRT_FirstSetCamera ,		// 처음시작시만 카메라 방향으로 캐릭터가 회전되고 그이후에는 CRT_CharacterRotation와 같이 동작됨
};

static C9RotationType StringToRotationType( const char * pszType )
{
	if( strcmp( pszType , "None" ) == 0 )				return CRT_NoneRotation;
	if( strcmp( pszType , "Camera" ) == 0 )				return CRT_CameraRotation;
	if( strcmp( pszType , "Character" ) == 0 )			return CRT_CharacterRotation;
	if( strcmp( pszType , "SlowCharacter" ) == 0 )		return CRT_SlowCharacterRotation;
	if( strcmp( pszType , "FirstRotation" ) == 0 )		return CRT_FirstRotation;
	if( strcmp( pszType , "FirstSetCamera" ) == 0 )		return CRT_FirstSetCamera;

	char strError[256];
	sprintf_s( strError , 256 , "알수없는 타입(%s) -> RotationType" , pszType );
	MessageBoxA( NULL , strError , "Error" , MB_OK );

	return CRT_CharacterRotation;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// AddDirection
enum C9AddDirection
{
	CAD_None ,
	CAD_LEFTRIGHT_TOWARD ,				// 앞으로 이동하면서 카메라 방향에 대한 회전 가능 (왼쪽, 오른쪽 키 가능, 같이 누를 경우 대각선 이동)
	CAD_LEFTRIGHT_BACK ,					// 뒤로 이동하면서 카메라 방향에 대한 회전 가능 (왼쪽, 오른쪽 키 가능, 같이 누를 경우 대각선 이동)
	CAD_LEFTRIGHT_TOWARDFIXED ,			// 앞으로 이동하면서 카메라 방향에 대한 회전 가능 (왼쪽, 오른쪽 키 불가능) - Fixed는 동작중간에 키가 먹히지 않음 ( 공격에서 쓰임 )
	CAD_LEFTRIGHT_BACKFIXED ,			// 뒤로 이동하면서 카메라 방향에 대한 회전 가능 (왼쪽, 오른쪽 키 불가능) - Fixed는 동작중간에 키가 먹히지 않음 ( 공격에서 쓰임 )
	CAD_LEFTRIGHT_ALLFIXED ,				// 카메라방향에 대한 캐릭터 회전 고정 - Fixed는 동작중간에 키가 먹히지 않음 ( 공격에서 쓰임 )
	CAD_LEFTRIGHT_TOWARD_NOROTATE ,		// 앞으로 이동하면서 카메라 방향에 대한 회전 가능 (왼쪽, 오른쪽 키 가능, 대각선 이동 불가능)
	CAD_LEFTRIGHT_BACK_NOROTATE ,		// 뒤로 이동하면서 카메라 방향에 대한 회전 가능 (왼쪽, 오른쪽 키 가능, 대각선 이동 불가능)
};

static C9AddDirection	StringToAddDirection( const char * pszType )
{
	if( strcmp( pszType , "None" ) == 0 )				return CAD_None;
	if( strcmp( pszType , "Toward" ) == 0 )				return CAD_LEFTRIGHT_TOWARD;
	if( strcmp( pszType , "Back" ) == 0 )				return CAD_LEFTRIGHT_BACK;
	if( strcmp( pszType , "TowardFixed" ) == 0 )			return CAD_LEFTRIGHT_TOWARDFIXED;
	if( strcmp( pszType , "BackFixed" ) == 0 )			return CAD_LEFTRIGHT_BACKFIXED;
	if( strcmp( pszType , "AllFixed" ) == 0 )			return CAD_LEFTRIGHT_ALLFIXED;
	if( strcmp( pszType , "Toward_NoRotate" ) == 0 )		return CAD_LEFTRIGHT_TOWARD_NOROTATE;
	if( strcmp( pszType , "Back_NoRotate" ) == 0 ) 		return CAD_LEFTRIGHT_BACK_NOROTATE;

	char strError[256];
	sprintf_s( strError , 256 , "알수없는 타입(%s) -> AddDirection" , pszType );
	MessageBoxA( NULL , strError , "Error" , MB_OK );

	return CAD_None;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ActionSituation
enum C9ActionSituation
{
	CAS_Normal ,							// 일반상태
	CAS_Defence ,						// 방어상태
	CAS_Avoid ,							// 회피상태, 데미지를 맞지 않는다.
	CAS_Crouch ,							// 숙이기 상태
	CAS_Catch ,							// 잡기 상태
	CAS_Invincible ,						// 무적상태(맞을 경우 이펙트는 나오지만, 데미지가 들어가지 않는다.)	
	CAS_PerfectDefence ,					// 완전 방어 상태(깨지지 않고, 가드수치도 소모하지 않는다.)
	CAS_ArrowDefence ,					// 발사체 방어
	CAS_ArrowPerpectDefence ,			// 발사체 완전 방어

	CAS_None ,
};

static const char* ActionSituationToString( C9ActionSituation type )
{
	switch( type )
	{
		case CAS_Normal:				return "Normal";
		case CAS_Defence:				return "Defence";
		case CAS_Avoid:					return "Avoid";
		case CAS_Crouch:				return "Crouch";
		case CAS_Catch:					return "Catch";
		case CAS_Invincible:			return "Invincible";
		case CAS_PerfectDefence:		return "PerfectDefence";
		case CAS_ArrowDefence:			return "ArrowDefence";
		case CAS_ArrowPerpectDefence:	return "ArrowPerpectDefence";
	}

	return "NoneDefined";
}

static C9ActionSituation StringToActionSituation( const char * pszType )
{
	for( int cType = 0; cType < CAS_None; ++cType )
		if( strcmp( pszType , ::ActionSituationToString( ( C9ActionSituation )cType ) ) == 0 )
			return ( C9ActionSituation )cType;

	if( strcmp( pszType , "SuperArmor" ) == 0 ||
		strcmp( pszType , "SemiSuperArmor" ) == 0 ||
		strcmp( pszType , "SuperArmorVsAI" ) == 0 )
		return CAS_Normal;

	char strError[256];
	sprintf_s( strError , 256 , "알수없는 타입(%s) -> ActionSituation" , pszType );
	MessageBoxA( NULL , strError , "Error" , MB_OK );

	return CAS_Normal;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ActionFallCancelType
enum C9ActionFallCancelType
{
	CAFCT_JUMP_FALL ,		// "JUMP_FALL" 액션 호출 (기본값)
	CAFCT_JUMP_FALL_FRONT ,	// "JUMP_FALL_FRONT" 액션 호출
	CAFCT_JUMP_FALL_LEFT ,	// "JUMP_FALL_LEFT" 액션 호출
	CAFCT_JUMP_FALL_RIGHT ,	// "JUMP_FALL_RIGHT" 액션 호출
	CAFCT_JUMP_FALL_BACK ,	// "JUMP_FALL_BACK" 액션 호출
	CAFCT_NONE ,				// 없음(액션호출하지 않음)
	CAFCT_FLY ,				// 플라잉 상태
	CAFCT_CONTINUE_ACTION ,	// 액션 유지, 발칸이 잡기후 점프 찍기
	CAFCT_SWIM ,				// 수영
							//CAFCT_ON_BIGMONSTRE,	// 거대 몬스터 위에 있는 상태
};

static C9ActionFallCancelType		StringToActionFallCancelType( const char * pszType )
{
	if( strcmp( pszType , "Fall" ) == 0 )			return CAFCT_JUMP_FALL;
	if( strcmp( pszType , "FallFront" ) == 0 )		return CAFCT_JUMP_FALL_FRONT;
	if( strcmp( pszType , "FallLeft" ) == 0 )		return CAFCT_JUMP_FALL_LEFT;
	if( strcmp( pszType , "FallRight" ) == 0 )		return CAFCT_JUMP_FALL_RIGHT;
	if( strcmp( pszType , "FallBack" ) == 0 )		return CAFCT_JUMP_FALL_BACK;
	if( strcmp( pszType , "None" ) == 0 )			return CAFCT_NONE;
	if( strcmp( pszType , "Fly" ) == 0 )				return CAFCT_FLY;
	if( strcmp( pszType , "Continue" ) == 0 )		return CAFCT_CONTINUE_ACTION;
	if( strcmp( pszType , "Swim" ) == 0 )			return CAFCT_SWIM;

	char strError[256];
	sprintf_s( strError , 256 , "알수없는 타입(%s) -> FallCancel" , pszType );
	MessageBoxA( NULL , strError , "Error" , MB_OK );

	return CAFCT_NONE;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ActionAddSpeedRateType
enum C9ActionAddSpeedRateType
{
	C9AASR_NONE ,	// 적용 속도 없음
	C9AASR_MOVES ,	// 이동 및 애니메이션 적용 (데이터에서 이속수치)
	C9AASR_ATTACK ,	// 애니메이션 적용 (데이터에서 공속수치)
};


static C9ActionAddSpeedRateType StringToActionAddSpeedRateType( const char * pszType )
{
	if( strcmp( pszType , "None" ) == 0 )	return C9AASR_NONE;
	if( strcmp( pszType , "Move" ) == 0 )	return C9AASR_MOVES;
	if( strcmp( pszType , "Attack" ) == 0 )	return C9AASR_ATTACK;

	char strError[256];
	sprintf_s( strError , 256 , "알수없는 타입(%s) -> AddSpeedRate" , pszType );
	MessageBoxA( NULL , strError , "Error" , MB_OK );

	return C9AASR_NONE;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ActionCheckItemType
enum C9ActionCheckItemType
{
	CACIT_DEFAULT ,			// 기본값 ( 아이템에 상관없이 액션 수행 )
	CACIT_NONE ,			// 아이템이 없을경우에 액션을 수행
	CACIT_RIGHT ,			// 오른쪽 무기가 있을경우에 수행
	CACIT_LEFT ,			// 왼쪽 무기가 있을경우에 수행
	CACIT_TWOHAND ,			// 양손 무기가 있을 경우에 수행
	CACIT_BOTH ,			// 왼쪽, 오른쪽 모두 무기가 있을 경우에 수행
	CACIT_LEFT_BOW ,		// 왼쪽 활 무기가 있을 경우에 수행
	CACIT_LEFT_CROSSBOW ,	// 왼쪽 총 무기가 있을 경우에 수행
};

static C9ActionCheckItemType StringToActionChackItemType( const char * pszType )
{
	if( strcmp( pszType , "Right" ) == 0 )			return CACIT_RIGHT;
	if( strcmp( pszType , "Left" ) == 0 )			return CACIT_LEFT;
	if( strcmp( pszType , "TwoHand" ) == 0 )		return CACIT_TWOHAND;
	if( strcmp( pszType , "Both" ) == 0 )			return CACIT_BOTH;
	if( strcmp( pszType , "LeftBow" ) == 0 )		return CACIT_LEFT_BOW;
	if( strcmp( pszType , "LeftCrossbow" ) == 0 )	return CACIT_LEFT_CROSSBOW;

	return CACIT_DEFAULT;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ActionUseSkillType
enum C9ActionUseSkillType
{
	CACUST_NONE ,			// 기본값 ( 스킬사용 불가능 액션 )
	CACUST_NORMAL ,			// 일반 스킬 사용 가능 액션
};

static C9ActionUseSkillType StringToActionUseSkillType( const char * pszType )
{
	if( strcmp( pszType , "Normal" ) == 0 )			return CACUST_NORMAL;

	return CACUST_NONE;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// IsShowAutoOutline
enum C9ShowOutlineState
{
	C9ShowOutlineState_NONE ,		//ACTIONDATA의 값을 따라감
	C9ShowOutlineState_TRUE ,
	C9ShowOutlineState_FALSE ,
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
enum C9ActionChartAttr
{
	C9ACA_NONE				= 0x00000000 ,
	C9ACA_CONTINUE_USEITEM	= 0x00000001 ,	// 아이템 사용 액션 지속
	C9ACA_SHOW_CROSS		= 0x00000002 ,	// 조준자 표시
	C9ACA_FOOTIKABLE		= 0x00000004 ,	// IK 적용
	C9ACA_SHOW_NAME			= 0x00000008 ,	// 이름표시
	C9ACA_SHOW_HP			= 0x00000010 ,	// HP표시
	C9ACA_USE_CASTINGTIME	= 0x00000020 ,	// 시전시간 적용
	C9ACA_DAMAGEACTION		= 0x00000040 ,	// 데미지 액션				( 내부에서 사용됨 )
	C9ACA_RUN_VOIDACTION	= 0x00000080 ,	// 데미지에서 브랜치 액션(내부에서 지정) 또는 데미지액션을 무시하고 해당 액션을 계속 진행 처리함
	C9ACA_EXIST_TRAIL		= 0x00000100 ,	// 검광정보 존재 여부		( 내부에서 사용됨 )
	C9ACA_AIR_ACTION		= 0x00000200 ,	// 공중에 떠있는 액션
	C9ACA_CATCH_NOT_FOCUS	= 0x00000400 ,	// 잡기시 카메라 포커스를 잡은사람에게 설정하지 않음
	C9ACA_LOOKIKABLE		= 0x00000800 ,	// IK 적용
	C9ACA_INVISIBLE			= 0x00001000 ,	// 적에게 타겟팅 되지 않음
	C9ACA_IGNORE_CATCH		= 0x00002000 ,	// 적의 잡기 공격 무시
	C9ACA_SINGLE_HIT		= 0x00004000 ,	// 액션 중 근접 공격이 한번만 발생 함
	C9ACA_IGNORE_HOOK		= 0x00008000 ,	// 적의 갈고리 공격을 무시
	C9ACA_NOT_NETOWRK_SYNC	= 0x00010000 ,	// 동기를 하지 않는다
	C9ACA_OTHER_ACTION		= 0x00020000 ,	// 액션내에서 다른 액션으로 변경
};



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
enum CFrameEventType
{
	CFE_AttackNormal ,				// 일반공격 (한프레임에 모두 공격)
	CFE_AttackRound ,				// 프레임 단위로 데미지 체크 공격
	CFE_AttackRange ,				// 프레임 단위로 데미지 체크 공격(몬스터 공격시 사용)
	CFE_AttackBomb ,				// 주변 범위 공격
	CFE_AttackBow ,					// 원거리 공격
	CFE_AttackMove ,				// 공격시 이동처리
	CFE_AttackBone ,				// 본에서 공격
	CFE_AttackRigidBody ,			// 물리객체에서 공격
	CFE_CameraShake ,				// 카메라 흔들기
	CFE_Decal ,						// 데칼	
	CFE_Throw ,						// 잡은 상태에서 던지기
	CFE_FrameDelay ,				// 프레임 딜레이
	CFE_SetRotation ,				// 캐릭터 회전
	CFE_ResetCheckTargetID ,		// 한번 검사한 타겟 리스트를 초기화한다.
	CFE_SetClientCameraMode ,		// 클라이언트 카메라 모드 바꾸기
	CFE_SwordTrail ,				// 검기
	CFE_SwordTrailTexture ,			// 검기 텍스처
	CFE_SwordTrailColor ,			// 검기 변화 색상
	CFE_SwordTrailScale ,			// 검기 변화 Scale
	CFE_Effect ,						// 이펙트
	CFE_EffectActive ,				// 이펙트 active, disable
	CFE_EffectRemove ,				// 이펙트 Remove
	CFE_Sound ,						// 사운드
	CFE_MeshSlotShow ,				// 메쉬 슬롯 숨기기 여부
	CFE_PickItem ,					// 아이템집기	
	CFE_CreateObjectScene ,			// 오브젝트 생성
	CFE_DeleteObjectScene ,			// 오브젝트 삭제
	CFE_EffectLightIntensity ,		// 이팩트라이트 밝기
	CFE_TextureChange ,				// 캐릭터 Texture 변환
	CFE_ColorChange_Skin ,			// 캐릭터 칼라 변환 : Skin
	CFE_ColorChange_Hair ,			// 캐릭터 칼라 변환 : Hair
	CFE_ColorChange_C1 ,			// 캐릭터 칼라 변환 : Color1
	CFE_ColorChange_C2 ,			// 캐릭터 칼라 변환 : Color2
	CFE_ColorChange_C3 ,			// 캐릭터 칼라 변환 : Color3
	CFE_ColorChange_C4 ,			// 캐릭터 칼라 변환 : Color4
	CFE_ColorChange_C5 ,			// 캐릭터 칼라 변환 : Color5
	CFE_ColorChange_C6 ,			// 캐릭터 칼라 변환 : Color6
	CFE_SpecularIntensity ,			// 캐릭터 스페큘러값 변환
	CFE_Summon ,					// 캐릭터 소환
	CFE_Skill ,						// 스킬 시전
	CFE_PushPull ,					// 적 밀거나 당기기
	CFE_RangeAreaAttack ,			// 원거리 지역 발사체 공격
	CFE_BoneScale ,					// 본 스케일
	CFE_BoneLight ,					// 본 조명
	CFE_CustomBoneLight ,			// 본 조명 재설정
	CFE_SelfRemove ,				// 자신을 제거
	CFE_Visible ,					// 자신을 보이거나 안보이게..
	CFE_ChangeBonePhysShape ,		// PhysBone의 속성 변경
	CFE_PhysAnimation ,				// Phys Animation 설정
	CFE_Situation ,					// 액션을 실행하는 캐릭터의 상태를 변화 시킴
	CFE_ObstacleEnable ,			// 캐릭터 Obstacle 활성
	CFE_ChangeCollisionType ,
	CFE_CenterBlur ,
	CFE_LocalOffsetEffect ,
	CFE_LocalOffsetEnvironmentFire ,
	CFE_LocalOffsetEnvironmentIce ,
	CFE_ScreenEffectBlurRate ,
	CFE_ShowMouseCursor ,
	CFE_UseSkill ,					// 스킬 사용 여부 타입
	CFE_Force ,
	CFE_CharacterAlpha ,			// 캐릭터에 알파 적용
	CFE_SlowMotion ,
	CFE_LockTargetPosition ,		// 타겟 캐릭터의 위치를 락 한다.(AttackBow 쪽에서 사용)
	CFE_AttackHook ,	
	CFE_Outline ,
	CFE_SetFallSpeed ,
	CFE_GiveOrder ,
	CFE_SetAIValue ,				// AIValue 세팅
	CFE_EnableCharacterShadow ,
	CFE_PlayerValue ,				// 플레이어 변수 설정
	CFE_PlayerServerValue ,			// 플레이어 서버 변수 설정

	CFE_FootstepEffect ,			// 발자국 이펙트, 사운드
	CFE_GroundHitEffect ,			// 지형 충돌 이펙트, 사운드
	CFE_PlayerTimer ,
	CFE_OpenChest ,					// 상자 열기
	CFE_Fury ,						// 분노 사용
	CFE_EffectPick ,				// 이펙트 pick
	CFE_MovingTrigger ,
	CFE_DonutWave ,
	CFE_SetResetSelectEventControl ,// 이벤트 컨트롤 리셋 여부
	CFE_SuperArmorValue ,			// 슈퍼 아머 값을 바꿈

	CFE_MeshMaterialFX_None ,		// 메쉬별 머터리얼 효과 해제
	CFE_MeshMaterialFX_Metal ,		// 메쉬별 재질 효과 (금속)
	CFE_MeshMaterialFX_Glass ,		// 메쉬별 재질 효과 (유리)
	CFE_MeshMaterialFX_Fresnel ,	// 메쉬별 재질 효과 (프레넬반사를 이용한 효과)
	CFE_MeshMaterialFX_Scroll ,		// 메쉬별 재잴 효과 (UV Animation)
	CFE_MeshDissolve ,				// 매쉬가 맵소스에따라서 점점 사라집니다.	

	CFE_ImgProcessing_BGColor ,		// 백그라운드컬러 조정
	CFE_ImgProcessing_ColorBalance ,// 컬러밸런스 조정
	CFE_ImgProcessing_Saturation ,	// 채도 조정
	CFE_ImgProcessing_Contrast ,	// 대비 조정
	CFE_ImgProcessing_Brightness ,	// 밝기 조정

	CFE_AddThreat ,					// 어그로 발생
	CFE_UseSkillEnd ,				// 스킬 사용 종료

	CFE_ChangeCameraFocus ,			// 카메라 포커스 변경
	CFE_ChangeClientCameraProperty ,// Client카메라 포지션, 로테이션 변경
	CFE_ChangePosition ,			// 위치 교환
	CFE_Teleport ,					// 위치 이동
	CFE_ItemEffectShow ,			// 아이템 이펙트 보여주기

	CFE_Targeting_Abnormal ,		// 타겟팅으로 상태이상 걸기
	CFE_Fishing ,					// 낚시.
	CFE_Pickpoint_Effect ,			// 피킹 위치에 이펙트 띄우기.
	CFE_TeleportToObject ,			// 전투시의 텔레포트 처리.
	
	CFE_TeleportRandomTarget ,		// Random으로 타겟을 지정한 대상으로 Teleport하는 형태

	CFE_MAX ,
};

enum EFF_COMMAND
{
	EFF_CMD_START ,
	EFF_CMD_STOP ,
	EFF_CMD_DIE ,
	EFF_CMD_DELETE ,
};

#define _SOUND_DEFAULT_MINDISTANCE_ 1000.0f
#define _SOUND_DEFAULT_MAXDISTANCE_ 5000.0f

enum C9ControlActionStatus
{
	C9CAS_NONE					= 0x00000000 ,
	C9CAS_WAIT					= 0x00000001 ,
	C9CAS_MOVE					= 0x00000002 ,
	C9CAS_ATTACK				= 0x00000004 ,
	C9CAS_SKILL					= 0x00000008 ,
	C9CAS_DAMAGE				= 0x00000010 ,
	C9CAS_DEAD					= 0x00000020 ,
	C9CAS_FLY					= 0x00000040 ,

	C9CAS_ATTACK_NORMAL			= 0x00000080 ,	// 일반 근접 공격
	C9CAS_ATTACK_RANGE			= 0x00000100 ,	// 원거리 공격

	C9CAS_ATTACK_HARD3			= 0x00000200 ,	// 강한 공격 X 3
	C9CAS_ATTACK_HARD2			= 0x00000400 ,	// 강한 공격 X 2
	C9CAS_ATTACK_HARD1			= 0x00000800 ,	// 보통 공격
	C9CAS_MOVE_LEFT				= 0x00001000 ,	// 왼쪽 이동
	C9CAS_MOVE_RIGHT			= 0x00002000 ,	// 오른쪽 이동
	C9CAS_MOVE_FORWARD			= 0x00004000 ,	// 왼쪽 이동
	C9CAS_MOVE_BACK				= 0x00008000 ,	// 오른쪽 이동

	C9CAS_ATTACK_FIRE			= 0x00010000 ,	// 화속성 공격
};

//////////////////////////////////////////////////////////////////////////
// ActionSpecialState
enum C9_Action_Special_State
{
	C9_Action_NONE = 0 ,
	C9_Action_Not_Move_From_UIClick = 1 ,
};


static C9_Action_Special_State	StringToSpecialState( const char * pszType )
{
	if( strcmp( pszType , "NotMoveFromUI" ) == 0 )		return C9_Action_Not_Move_From_UIClick;

	return C9_Action_NONE;
}


//////////////////////////////////////////////////////////////////////////
// Input check state
enum C9_INPUT_CHECK_STATE
{
	C9_INPUT_CHECK_NONE ,
	C9_INPUT_CHECK_HOOK_TARGET ,
	C9_INPUT_CHECK_HOOK_ACTION ,
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ActionInputTiming
enum C9ActionInputTiming
{
	CIT_None ,
	CIT_Entire ,	// 전체 구간 입력
	CIT_Section	// 특정 프레임 구간 입력
};

static C9ActionInputTiming	StringToActionInputTiming( const char * pszType )
{
	if( strcmp( pszType , "Entire" ) == 0 )		return CIT_Entire;
	if( strcmp( pszType , "Section" ) == 0 )	return CIT_Section;

	return CIT_None;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 값 비교 타입
enum ValueCompareType
{
	C9VCT_EQUAL ,		// 상등 (==)
	C9VCT_NOTEQ ,		// 부등 (!=)
	C9VCT_LSTHN ,		// 작다 (<)
	C9VCT_BGTHN ,		// 크다 (>)
	C9VCT_LSEQL ,		// 작거나 같다 (<=)
	C9VCT_BGEQL ,		// 크거나 같다 (>=)

	C9VCT_MAX ,
};

static const char *				ValueCompareTypeToString( ValueCompareType compareType )
{
	switch( compareType )
	{
		case C9VCT_NOTEQ:								return "!=";
		case C9VCT_LSTHN:								return "<";
		case C9VCT_BGTHN:								return ">";
		case C9VCT_LSEQL:								return "<=";
		case C9VCT_BGEQL:								return ">=";
	}

	return "==";
}


static ValueCompareType		StringToValueCompareType( const char * pszCompareType )
{
	if( strcmp( pszCompareType , "!=" ) == 0 )													return C9VCT_NOTEQ;
	else if( strcmp( pszCompareType , "<" ) == 0 || strcmp( pszCompareType , "&lt;" ) == 0 )		return C9VCT_LSTHN;
	else if( strcmp( pszCompareType , ">" ) == 0 || strcmp( pszCompareType , "&gt;" ) == 0 )		return C9VCT_BGTHN;
	else if( strcmp( pszCompareType , "<=" ) == 0 || strcmp( pszCompareType , "&lt;=" ) == 0 )	return C9VCT_LSEQL;
	else if( strcmp( pszCompareType , ">=" ) == 0 || strcmp( pszCompareType , "&gt;=" ) == 0 )	return C9VCT_BGEQL;

	return C9VCT_EQUAL;
}

template < class T >
static bool	ValueCompare( ValueCompareType type , T value1 , T value2 )
{
	switch( type )
	{
		case C9VCT_EQUAL:					return value1 == value2;
		case C9VCT_NOTEQ:					return value1 != value2;
		case C9VCT_LSTHN:					return value1 < value2;
		case C9VCT_BGTHN:					return value1 > value2;
		case C9VCT_LSEQL:					return value1 <= value2;
		case C9VCT_BGEQL:					return value1 >= value2;
	}

	return false;
}



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
enum C9DataInfoType
{
	C9_DATA_INFO_CLASS ,
	C9_DATA_INFO_TribeForce ,
	C9_DATA_INFO_CHARACTER ,
	C9_DATA_INFO_ITEM ,
	C9_DATA_INFO_ABNORMALTYPE ,
	C9_DATA_INFO_ABNORMAL ,
	C9_DATA_INFO_ITEMOPTION ,
	C9_DATA_INFO_ITEMOPTION_PACKAGE ,
	C9_DATA_INFO_ITEMSET ,
	C9_DATA_INFO_SPECIAL_OPTION ,
	C9_DATA_INFO_SKILLTYPE ,
	C9_DATA_INFO_SKILL ,
	C9_DATA_INFO_COMBO ,
	C9_DATA_INFO_DROPGROUP ,
	C9_DATA_INFO_DROPPACKAGE ,
	C9_DATA_INFO_MAP ,
	C9_DATA_INFO_SALEGROUP ,
	C9_DATA_INFO_SALEPRODUCT ,
	C9_DATA_INFO_ARTISAN ,
	C9_DATA_INFO_COMBINATION ,
	C9_DATA_INFO_COMBINATION_TOOL ,
	C9_DATA_INFO_QUESTGROUP ,
	C9_DATA_INFO_QUEST ,
	C9_DATA_INFO_LEGEND ,
	C9_DATA_INFO_ITEM_COMBINATION ,
	C9_DATA_INFO_ITEM_COMBINATION_NPC ,
	C9_DATA_INFO_WEEKLY_RELAY ,
	C9_DATA_INFO_EVENT_SYSTEM ,
	C9_DATA_INFO_ADVENTUREBOOK_SYSTEM ,
	C9_DATA_INFO_CONTENT_DATA_GROUP ,
	C9_DATA_INFO_AOS_SYSTEM ,
	C9_DATA_INFO_SKILLPACKAGE ,
	C9_DATA_INFO_PETOPTION ,
	C9_DATA_INFO_CUSTOMEXPRESSION ,
	C9_DATA_INFO_MAX ,
};
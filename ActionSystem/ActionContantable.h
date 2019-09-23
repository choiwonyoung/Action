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
	const float RMATH_DEG2RAD			= RMATH_PI / 180.0f;	// (RMATH_PI / 180.0f, 60�й��� ȣ��������: ex) fRadian = nDegree * RMATH_DEG2RAD;
	const float RMATH_RAD2DEG			= 180.0f / RMATH_PI;	// (180.0f / RMATH_PI, ȣ������ 60�й�����: ex) nDegree = fRadian * RMATH_RAD2DEG;


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

	CAM_AddMove ,			// �Ϲ� �̵�
	CAM_NormalJump ,		// �Ϲ�(��) ����
	CAM_ShortJump ,			// ª�� ����

	CAM_AimRotation ,		// Ÿ�� ����
	CAM_AimRotationMove ,	// Ÿ�� ���� �� ȸ������
	CAM_AimRange ,			// ���Ÿ� ����

	CAM_UpRotation ,			// ĳ������ ���������� �̵�, Fly�� ����Ű�� ������ ��� �ϴ����� �̵���
	CAM_NoneFlyRotation ,	// Fly�� ĳ���� ȸ�� �Ұ��� (ī�޶� ȸ�� ����) 
	CAM_FlyRotation ,		// Fly�� �Ϲ�ȸ�� (ī�޶� �������� ȸ�� �̵�)
	CAM_FlyUpRotation ,		// fly ȸ�� ( ���� ȸ���� : �Ӹ��������� )

	CAM_FromAnimation ,		// �ִϸ��̼ǿ����� ��ġ ����

	CAM_ShorterJump ,		// �� ª�� ����
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
	sprintf_s( strError , 256 , "�˼����� Ÿ��(%s) -> AdditionMove" , pszType );
	MessageBoxA( NULL , strError , "Error" , MB_OK );

	return CAM_None;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// RotationType
enum C9RotationType
{
	CRT_NoneRotation ,			// ���콺 ȸ���� ī�޶� �� ĳ���� ȸ�� �ȵ�
	CRT_CameraRotation ,		// ���콺 ȸ���� ī�޶� ȸ��
	CRT_CharacterRotation ,		// ���콺 ȸ���� ĳ���� �� ī�޶� ȸ��	( �⺻�� )
	CRT_SlowCharacterRotation ,	// ���콺 ȸ���� ĳ���Ͱ� ī�޶� ���� õõ�� ȸ����
	CRT_FirstRotation ,			// ó�����۽ø� ī�޶� ���� ȸ���ǰ� �� ���Ŀ��� ������
	CRT_FirstSetCamera ,		// ó�����۽ø� ī�޶� �������� ĳ���Ͱ� ȸ���ǰ� �����Ŀ��� CRT_CharacterRotation�� ���� ���۵�
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
	sprintf_s( strError , 256 , "�˼����� Ÿ��(%s) -> RotationType" , pszType );
	MessageBoxA( NULL , strError , "Error" , MB_OK );

	return CRT_CharacterRotation;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// AddDirection
enum C9AddDirection
{
	CAD_None ,
	CAD_LEFTRIGHT_TOWARD ,				// ������ �̵��ϸ鼭 ī�޶� ���⿡ ���� ȸ�� ���� (����, ������ Ű ����, ���� ���� ��� �밢�� �̵�)
	CAD_LEFTRIGHT_BACK ,					// �ڷ� �̵��ϸ鼭 ī�޶� ���⿡ ���� ȸ�� ���� (����, ������ Ű ����, ���� ���� ��� �밢�� �̵�)
	CAD_LEFTRIGHT_TOWARDFIXED ,			// ������ �̵��ϸ鼭 ī�޶� ���⿡ ���� ȸ�� ���� (����, ������ Ű �Ұ���) - Fixed�� �����߰��� Ű�� ������ ���� ( ���ݿ��� ���� )
	CAD_LEFTRIGHT_BACKFIXED ,			// �ڷ� �̵��ϸ鼭 ī�޶� ���⿡ ���� ȸ�� ���� (����, ������ Ű �Ұ���) - Fixed�� �����߰��� Ű�� ������ ���� ( ���ݿ��� ���� )
	CAD_LEFTRIGHT_ALLFIXED ,				// ī�޶���⿡ ���� ĳ���� ȸ�� ���� - Fixed�� �����߰��� Ű�� ������ ���� ( ���ݿ��� ���� )
	CAD_LEFTRIGHT_TOWARD_NOROTATE ,		// ������ �̵��ϸ鼭 ī�޶� ���⿡ ���� ȸ�� ���� (����, ������ Ű ����, �밢�� �̵� �Ұ���)
	CAD_LEFTRIGHT_BACK_NOROTATE ,		// �ڷ� �̵��ϸ鼭 ī�޶� ���⿡ ���� ȸ�� ���� (����, ������ Ű ����, �밢�� �̵� �Ұ���)
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
	sprintf_s( strError , 256 , "�˼����� Ÿ��(%s) -> AddDirection" , pszType );
	MessageBoxA( NULL , strError , "Error" , MB_OK );

	return CAD_None;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ActionSituation
enum C9ActionSituation
{
	CAS_Normal ,							// �Ϲݻ���
	CAS_Defence ,						// ������
	CAS_Avoid ,							// ȸ�ǻ���, �������� ���� �ʴ´�.
	CAS_Crouch ,							// ���̱� ����
	CAS_Catch ,							// ��� ����
	CAS_Invincible ,						// ��������(���� ��� ����Ʈ�� ��������, �������� ���� �ʴ´�.)	
	CAS_PerfectDefence ,					// ���� ��� ����(������ �ʰ�, �����ġ�� �Ҹ����� �ʴ´�.)
	CAS_ArrowDefence ,					// �߻�ü ���
	CAS_ArrowPerpectDefence ,			// �߻�ü ���� ���

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
	sprintf_s( strError , 256 , "�˼����� Ÿ��(%s) -> ActionSituation" , pszType );
	MessageBoxA( NULL , strError , "Error" , MB_OK );

	return CAS_Normal;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ActionFallCancelType
enum C9ActionFallCancelType
{
	CAFCT_JUMP_FALL ,		// "JUMP_FALL" �׼� ȣ�� (�⺻��)
	CAFCT_JUMP_FALL_FRONT ,	// "JUMP_FALL_FRONT" �׼� ȣ��
	CAFCT_JUMP_FALL_LEFT ,	// "JUMP_FALL_LEFT" �׼� ȣ��
	CAFCT_JUMP_FALL_RIGHT ,	// "JUMP_FALL_RIGHT" �׼� ȣ��
	CAFCT_JUMP_FALL_BACK ,	// "JUMP_FALL_BACK" �׼� ȣ��
	CAFCT_NONE ,				// ����(�׼�ȣ������ ����)
	CAFCT_FLY ,				// �ö��� ����
	CAFCT_CONTINUE_ACTION ,	// �׼� ����, ��ĭ�� ����� ���� ���
	CAFCT_SWIM ,				// ����
							//CAFCT_ON_BIGMONSTRE,	// �Ŵ� ���� ���� �ִ� ����
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
	sprintf_s( strError , 256 , "�˼����� Ÿ��(%s) -> FallCancel" , pszType );
	MessageBoxA( NULL , strError , "Error" , MB_OK );

	return CAFCT_NONE;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ActionAddSpeedRateType
enum C9ActionAddSpeedRateType
{
	C9AASR_NONE ,	// ���� �ӵ� ����
	C9AASR_MOVES ,	// �̵� �� �ִϸ��̼� ���� (�����Ϳ��� �̼Ӽ�ġ)
	C9AASR_ATTACK ,	// �ִϸ��̼� ���� (�����Ϳ��� ���Ӽ�ġ)
};


static C9ActionAddSpeedRateType StringToActionAddSpeedRateType( const char * pszType )
{
	if( strcmp( pszType , "None" ) == 0 )	return C9AASR_NONE;
	if( strcmp( pszType , "Move" ) == 0 )	return C9AASR_MOVES;
	if( strcmp( pszType , "Attack" ) == 0 )	return C9AASR_ATTACK;

	char strError[256];
	sprintf_s( strError , 256 , "�˼����� Ÿ��(%s) -> AddSpeedRate" , pszType );
	MessageBoxA( NULL , strError , "Error" , MB_OK );

	return C9AASR_NONE;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ActionCheckItemType
enum C9ActionCheckItemType
{
	CACIT_DEFAULT ,			// �⺻�� ( �����ۿ� ������� �׼� ���� )
	CACIT_NONE ,			// �������� ������쿡 �׼��� ����
	CACIT_RIGHT ,			// ������ ���Ⱑ ������쿡 ����
	CACIT_LEFT ,			// ���� ���Ⱑ ������쿡 ����
	CACIT_TWOHAND ,			// ��� ���Ⱑ ���� ��쿡 ����
	CACIT_BOTH ,			// ����, ������ ��� ���Ⱑ ���� ��쿡 ����
	CACIT_LEFT_BOW ,		// ���� Ȱ ���Ⱑ ���� ��쿡 ����
	CACIT_LEFT_CROSSBOW ,	// ���� �� ���Ⱑ ���� ��쿡 ����
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
	CACUST_NONE ,			// �⺻�� ( ��ų��� �Ұ��� �׼� )
	CACUST_NORMAL ,			// �Ϲ� ��ų ��� ���� �׼�
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
	C9ShowOutlineState_NONE ,		//ACTIONDATA�� ���� ����
	C9ShowOutlineState_TRUE ,
	C9ShowOutlineState_FALSE ,
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
enum C9ActionChartAttr
{
	C9ACA_NONE				= 0x00000000 ,
	C9ACA_CONTINUE_USEITEM	= 0x00000001 ,	// ������ ��� �׼� ����
	C9ACA_SHOW_CROSS		= 0x00000002 ,	// ������ ǥ��
	C9ACA_FOOTIKABLE		= 0x00000004 ,	// IK ����
	C9ACA_SHOW_NAME			= 0x00000008 ,	// �̸�ǥ��
	C9ACA_SHOW_HP			= 0x00000010 ,	// HPǥ��
	C9ACA_USE_CASTINGTIME	= 0x00000020 ,	// �����ð� ����
	C9ACA_DAMAGEACTION		= 0x00000040 ,	// ������ �׼�				( ���ο��� ���� )
	C9ACA_RUN_VOIDACTION	= 0x00000080 ,	// ���������� �귣ġ �׼�(���ο��� ����) �Ǵ� �������׼��� �����ϰ� �ش� �׼��� ��� ���� ó����
	C9ACA_EXIST_TRAIL		= 0x00000100 ,	// �˱����� ���� ����		( ���ο��� ���� )
	C9ACA_AIR_ACTION		= 0x00000200 ,	// ���߿� ���ִ� �׼�
	C9ACA_CATCH_NOT_FOCUS	= 0x00000400 ,	// ���� ī�޶� ��Ŀ���� ����������� �������� ����
	C9ACA_LOOKIKABLE		= 0x00000800 ,	// IK ����
	C9ACA_INVISIBLE			= 0x00001000 ,	// ������ Ÿ���� ���� ����
	C9ACA_IGNORE_CATCH		= 0x00002000 ,	// ���� ��� ���� ����
	C9ACA_SINGLE_HIT		= 0x00004000 ,	// �׼� �� ���� ������ �ѹ��� �߻� ��
	C9ACA_IGNORE_HOOK		= 0x00008000 ,	// ���� ���� ������ ����
	C9ACA_NOT_NETOWRK_SYNC	= 0x00010000 ,	// ���⸦ ���� �ʴ´�
	C9ACA_OTHER_ACTION		= 0x00020000 ,	// �׼ǳ����� �ٸ� �׼����� ����
};



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
enum CFrameEventType
{
	CFE_AttackNormal ,				// �Ϲݰ��� (�������ӿ� ��� ����)
	CFE_AttackRound ,				// ������ ������ ������ üũ ����
	CFE_AttackRange ,				// ������ ������ ������ üũ ����(���� ���ݽ� ���)
	CFE_AttackBomb ,				// �ֺ� ���� ����
	CFE_AttackBow ,					// ���Ÿ� ����
	CFE_AttackMove ,				// ���ݽ� �̵�ó��
	CFE_AttackBone ,				// ������ ����
	CFE_AttackRigidBody ,			// ������ü���� ����
	CFE_CameraShake ,				// ī�޶� ����
	CFE_Decal ,						// ��Į	
	CFE_Throw ,						// ���� ���¿��� ������
	CFE_FrameDelay ,				// ������ ������
	CFE_SetRotation ,				// ĳ���� ȸ��
	CFE_ResetCheckTargetID ,		// �ѹ� �˻��� Ÿ�� ����Ʈ�� �ʱ�ȭ�Ѵ�.
	CFE_SetClientCameraMode ,		// Ŭ���̾�Ʈ ī�޶� ��� �ٲٱ�
	CFE_SwordTrail ,				// �˱�
	CFE_SwordTrailTexture ,			// �˱� �ؽ�ó
	CFE_SwordTrailColor ,			// �˱� ��ȭ ����
	CFE_SwordTrailScale ,			// �˱� ��ȭ Scale
	CFE_Effect ,						// ����Ʈ
	CFE_EffectActive ,				// ����Ʈ active, disable
	CFE_EffectRemove ,				// ����Ʈ Remove
	CFE_Sound ,						// ����
	CFE_MeshSlotShow ,				// �޽� ���� ����� ����
	CFE_PickItem ,					// ����������	
	CFE_CreateObjectScene ,			// ������Ʈ ����
	CFE_DeleteObjectScene ,			// ������Ʈ ����
	CFE_EffectLightIntensity ,		// ����Ʈ����Ʈ ���
	CFE_TextureChange ,				// ĳ���� Texture ��ȯ
	CFE_ColorChange_Skin ,			// ĳ���� Į�� ��ȯ : Skin
	CFE_ColorChange_Hair ,			// ĳ���� Į�� ��ȯ : Hair
	CFE_ColorChange_C1 ,			// ĳ���� Į�� ��ȯ : Color1
	CFE_ColorChange_C2 ,			// ĳ���� Į�� ��ȯ : Color2
	CFE_ColorChange_C3 ,			// ĳ���� Į�� ��ȯ : Color3
	CFE_ColorChange_C4 ,			// ĳ���� Į�� ��ȯ : Color4
	CFE_ColorChange_C5 ,			// ĳ���� Į�� ��ȯ : Color5
	CFE_ColorChange_C6 ,			// ĳ���� Į�� ��ȯ : Color6
	CFE_SpecularIntensity ,			// ĳ���� ����ŧ���� ��ȯ
	CFE_Summon ,					// ĳ���� ��ȯ
	CFE_Skill ,						// ��ų ����
	CFE_PushPull ,					// �� �аų� ����
	CFE_RangeAreaAttack ,			// ���Ÿ� ���� �߻�ü ����
	CFE_BoneScale ,					// �� ������
	CFE_BoneLight ,					// �� ����
	CFE_CustomBoneLight ,			// �� ���� �缳��
	CFE_SelfRemove ,				// �ڽ��� ����
	CFE_Visible ,					// �ڽ��� ���̰ų� �Ⱥ��̰�..
	CFE_ChangeBonePhysShape ,		// PhysBone�� �Ӽ� ����
	CFE_PhysAnimation ,				// Phys Animation ����
	CFE_Situation ,					// �׼��� �����ϴ� ĳ������ ���¸� ��ȭ ��Ŵ
	CFE_ObstacleEnable ,			// ĳ���� Obstacle Ȱ��
	CFE_ChangeCollisionType ,
	CFE_CenterBlur ,
	CFE_LocalOffsetEffect ,
	CFE_LocalOffsetEnvironmentFire ,
	CFE_LocalOffsetEnvironmentIce ,
	CFE_ScreenEffectBlurRate ,
	CFE_ShowMouseCursor ,
	CFE_UseSkill ,					// ��ų ��� ���� Ÿ��
	CFE_Force ,
	CFE_CharacterAlpha ,			// ĳ���Ϳ� ���� ����
	CFE_SlowMotion ,
	CFE_LockTargetPosition ,		// Ÿ�� ĳ������ ��ġ�� �� �Ѵ�.(AttackBow �ʿ��� ���)
	CFE_AttackHook ,	
	CFE_Outline ,
	CFE_SetFallSpeed ,
	CFE_GiveOrder ,
	CFE_SetAIValue ,				// AIValue ����
	CFE_EnableCharacterShadow ,
	CFE_PlayerValue ,				// �÷��̾� ���� ����
	CFE_PlayerServerValue ,			// �÷��̾� ���� ���� ����

	CFE_FootstepEffect ,			// ���ڱ� ����Ʈ, ����
	CFE_GroundHitEffect ,			// ���� �浹 ����Ʈ, ����
	CFE_PlayerTimer ,
	CFE_OpenChest ,					// ���� ����
	CFE_Fury ,						// �г� ���
	CFE_EffectPick ,				// ����Ʈ pick
	CFE_MovingTrigger ,
	CFE_DonutWave ,
	CFE_SetResetSelectEventControl ,// �̺�Ʈ ��Ʈ�� ���� ����
	CFE_SuperArmorValue ,			// ���� �Ƹ� ���� �ٲ�

	CFE_MeshMaterialFX_None ,		// �޽��� ���͸��� ȿ�� ����
	CFE_MeshMaterialFX_Metal ,		// �޽��� ���� ȿ�� (�ݼ�)
	CFE_MeshMaterialFX_Glass ,		// �޽��� ���� ȿ�� (����)
	CFE_MeshMaterialFX_Fresnel ,	// �޽��� ���� ȿ�� (�����ڹݻ縦 �̿��� ȿ��)
	CFE_MeshMaterialFX_Scroll ,		// �޽��� ���� ȿ�� (UV Animation)
	CFE_MeshDissolve ,				// �Ž��� �ʼҽ������� ���� ������ϴ�.	

	CFE_ImgProcessing_BGColor ,		// ��׶����÷� ����
	CFE_ImgProcessing_ColorBalance ,// �÷��뷱�� ����
	CFE_ImgProcessing_Saturation ,	// ä�� ����
	CFE_ImgProcessing_Contrast ,	// ��� ����
	CFE_ImgProcessing_Brightness ,	// ��� ����

	CFE_AddThreat ,					// ��׷� �߻�
	CFE_UseSkillEnd ,				// ��ų ��� ����

	CFE_ChangeCameraFocus ,			// ī�޶� ��Ŀ�� ����
	CFE_ChangeClientCameraProperty ,// Clientī�޶� ������, �����̼� ����
	CFE_ChangePosition ,			// ��ġ ��ȯ
	CFE_Teleport ,					// ��ġ �̵�
	CFE_ItemEffectShow ,			// ������ ����Ʈ �����ֱ�

	CFE_Targeting_Abnormal ,		// Ÿ�������� �����̻� �ɱ�
	CFE_Fishing ,					// ����.
	CFE_Pickpoint_Effect ,			// ��ŷ ��ġ�� ����Ʈ ����.
	CFE_TeleportToObject ,			// �������� �ڷ���Ʈ ó��.
	
	CFE_TeleportRandomTarget ,		// Random���� Ÿ���� ������ ������� Teleport�ϴ� ����

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

	C9CAS_ATTACK_NORMAL			= 0x00000080 ,	// �Ϲ� ���� ����
	C9CAS_ATTACK_RANGE			= 0x00000100 ,	// ���Ÿ� ����

	C9CAS_ATTACK_HARD3			= 0x00000200 ,	// ���� ���� X 3
	C9CAS_ATTACK_HARD2			= 0x00000400 ,	// ���� ���� X 2
	C9CAS_ATTACK_HARD1			= 0x00000800 ,	// ���� ����
	C9CAS_MOVE_LEFT				= 0x00001000 ,	// ���� �̵�
	C9CAS_MOVE_RIGHT			= 0x00002000 ,	// ������ �̵�
	C9CAS_MOVE_FORWARD			= 0x00004000 ,	// ���� �̵�
	C9CAS_MOVE_BACK				= 0x00008000 ,	// ������ �̵�

	C9CAS_ATTACK_FIRE			= 0x00010000 ,	// ȭ�Ӽ� ����
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
	CIT_Entire ,	// ��ü ���� �Է�
	CIT_Section	// Ư�� ������ ���� �Է�
};

static C9ActionInputTiming	StringToActionInputTiming( const char * pszType )
{
	if( strcmp( pszType , "Entire" ) == 0 )		return CIT_Entire;
	if( strcmp( pszType , "Section" ) == 0 )	return CIT_Section;

	return CIT_None;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// �� �� Ÿ��
enum ValueCompareType
{
	C9VCT_EQUAL ,		// ��� (==)
	C9VCT_NOTEQ ,		// �ε� (!=)
	C9VCT_LSTHN ,		// �۴� (<)
	C9VCT_BGTHN ,		// ũ�� (>)
	C9VCT_LSEQL ,		// �۰ų� ���� (<=)
	C9VCT_BGEQL ,		// ũ�ų� ���� (>=)

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
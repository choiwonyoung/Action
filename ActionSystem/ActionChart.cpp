#include "stdafx.h"
#include "ActionChart.h"
#include "ActionDataInfo.h"
#include "ActionData.h"
#include "ActionContantable.h"
#include "ActionBranch.h"
#include "FrameEvent.h"

void CActionChart::CCopyActionChartValue::LoadXML( XMLNode *pXMLNode , CActionChart *pActionChart )
{
	string strAttr;

	// 액션 복사 // 카피 회수 저장
	pXMLNode->GetAttrInt( "CopyCount" , m_iCopyCount );
	if( m_iCopyCount < 2 )
		m_iCopyCount = 0;

	// 액션 복사
	if( m_iCopyCount > 1 )
	{
		pXMLNode->GetAttrFloat( "CopyAddMoveSpeed" , m_fMoveSpeed );
		pXMLNode->GetAttrFloat( "CopyAddAnimationSpeed" , m_fAnimationSpeed );
		pXMLNode->GetAttrFloat( "CopyAddFrameMoveSpeed" , m_fFrameMoveSpeed );
	}
}

CActionChart::CActionChart( const CActionData& actionData )
: m_actionData( actionData )

, m_strActionName( "" )
, m_strAnimationFilename( "" )
, m_strEndActionName( "None" )
, m_strCatchTargetActionName( "" )
, m_strShowCrossCheckAction( "" )

, m_dwHashcode( 0 )
, m_dwEndActionCode( 0 )
, m_dwEndActionSkillType( 0 )
, m_dwCatchTargetActionCode( Action::C9_CRC_CODE_ACTION_DAMAGE_CATCH_ME )
, m_dwShowCrossCheckActionCode( 0 )
, m_dwShowCrossCheckActionSkillType( 0 )
, m_dwAnimationHashCode( 0 )

, m_dwActionAttr( C9ACA_NONE )
, m_ddwInputMask( 0 )
, m_nEndActionBlendFrame( 0 )

, m_dwActionType( 0 )
, m_AdditionMove( CAM_None )
, m_RotationType( CRT_CharacterRotation )
, m_AddDirection( CAD_None )
, m_ActionSituation( CAS_Normal )
, m_FallCancelType( CAFCT_NONE )
, m_AddSpeedRateType( C9AASR_NONE )
, m_ActionCheckItem( CACIT_DEFAULT )
, m_UseSkillType( CACUST_NONE )
, m_iSuperArmorValue( 0 )

, m_fMoveSpeed( 0.0f )
, m_fFlyFallSpeed( 0.0f )
, m_fAddAttackDirection( 0.0f )
, m_fAnimationSpeed( 1.0f )
, m_fMoveDirection( 0.0f )
, m_fCameraRotationSpeed( 0.0f )
, m_nFixRotation( 0 )

, m_nFrameMoveSpeedStartFrame( -1 )
, m_nFrameMoveSpeedEndFrame( -1 )
, m_fFrameMoveSpeed( 0.0f )
, m_fRotation( 0.0f )
, m_fHaveParentRotationValue( 0.0f )

, m_fPickRange( 0.0f )

, m_nChangeSpeedStartFrame( -1 )
, m_nAcceleration( -1 )
, m_nLimitSpeed( -1 )

, m_nHoldMeBoneIndex( 0 )
, m_nPhysBoneActorGroup( 0 )

, m_CopyActionChartValue()

, m_bMoveSpeedFetch( false )
, m_bMoveTargetRotation( false )
, m_bHaveParentIsRotation( false )
, m_bMovePickingDirection( false )
, m_lstActionIndexHashCode()
, m_lstActionBranch()
, m_lstFrameEvent()
, m_bUseSkillLevelName( true )

, m_IsShowOutline( C9ShowOutlineState::C9ShowOutlineState_NONE )
, m_fOutlineThickness( 0.0f )
, m_bIsBackgroundAnimationFetch( true )
, m_fDummyActionEndFrame( 0 )
, m_bPickingAlternativeLand( false )

, m_dwActionSpecialValue( 0 )
{
	// 액션인덱스가 비어 있는 ActionDataInfo 가 있다면 그것으로...
	// 없다면 첫번째 것으로...
	const CActionDataInfo * pActionDataInfo = actionData.m_ActionDataInfoList[0];
	for( size_t i = 0; i < m_actionData.m_ActionDataInfoList.size(); ++i )
	{
		const CActionDataInfo * pInfo = m_actionData.m_ActionDataInfoList[i];
		if( pInfo->m_lstActionIndexHashCode.empty() )
			pActionDataInfo = pInfo;
	}

	if( pActionDataInfo->m_bShowName )		SetActionAttr( C9ACA_SHOW_NAME );
	if( pActionDataInfo->m_bShowHp )		SetActionAttr( C9ACA_SHOW_HP );
	if( pActionDataInfo->m_bShowCross )		SetActionAttr( C9ACA_SHOW_CROSS );

	//m_CollisionType = pActionDataInfo->m_CollisionType;
	m_iSuperArmorValue = pActionDataInfo->m_iSuperArmorValue;
}


CActionChart::~CActionChart()
{
	RSAFE_DELETE_VECTOR( m_lstActionBranch );
	RSAFE_DELETE_VECTOR( m_lstFrameEvent );
}

bool CActionChart::LoadXML( XMLNode *pXMLNode , XMLNode *pRootNode , HashMap_ActionFunction & mapActionFunction , List_PreloadString & lstPreloadEffect , List_PreloadString &lstPreloadSound )
{
	string strAttr;

	m_ddwInputMask = 0x0;
	m_strActionName = pXMLNode->Value();
	m_dwHashcode = CCrc32Static::StringCrc32( m_strActionName.c_str() );

	// 애니메이션 정보
	if( _LoadXML_AnimationInfo( pXMLNode ) == false )
		return false;

	// ActionIndex 에 있는 정보를 가져오기
	_LoadAttrFromActionDataInfo( pXMLNode );

	// 검광 존재 여부 초기화
	ResetActionAttr( C9ACA_EXIST_TRAIL );

	if( _LoadXML_MoveSpeedInfo( pXMLNode , strAttr ) == false )
		return false;

	_LoadXML_OutLineInfo( pXMLNode );

	// 액션 복사 정보
	m_CopyActionChartValue.LoadXML( pXMLNode , this );	

	_LoadXML_ActionTypeInfo( pXMLNode , strAttr );

	pXMLNode->GetAttrFloat( "FlyFallSpeed" , m_fFlyFallSpeed );
	pXMLNode->GetAttrFloat( "DummyAnimationEndFrame" , m_fDummyActionEndFrame );
	if( m_fDummyActionEndFrame > 0 )
		m_bIsBackgroundAnimationFetch = false;

	if( pXMLNode->GetAttr( "FrameMoveSpeed" , strAttr ) )
		sscanf( strAttr.c_str() , "%d %d %f" , &m_nFrameMoveSpeedStartFrame , &m_nFrameMoveSpeedEndFrame , &m_fFrameMoveSpeed );

	pXMLNode->GetAttrBool( "TurnTarget" , m_bMoveTargetRotation );
	pXMLNode->GetAttrFloat( "AddAttackDirection" , m_fAddAttackDirection );
	pXMLNode->GetAttrFloat( "AnimationSpeed" , m_fAnimationSpeed );
	pXMLNode->GetAttrFloat( "TurnAngle" , m_fRotation );
	pXMLNode->GetAttrFloat( "CameraRotationSpeed" , m_fCameraRotationSpeed );
	if( m_fCameraRotationSpeed == 1.0f )
		m_fCameraRotationSpeed = 0.0f;

	pXMLNode->GetAttrBool( "HaveParentIsRot" , m_bHaveParentIsRotation );
	pXMLNode->GetAttrFloat( "HaveParentRotVal" , m_fHaveParentRotationValue );	

	if( pXMLNode->GetAttr( "MoveDirection" , strAttr ) )
	{
		if( strAttr == "FromDamageDirection" )
			m_fMoveDirection = 1000000.0f;
		else if( strAttr == "PickingDirection" )
			m_bMovePickingDirection = true;
		else
			m_fMoveDirection = ( float )atof( strAttr.c_str() );
	}

	if( pXMLNode->GetAttr( "AdditionMove" , strAttr ) )				m_AdditionMove = ::StringToAdditionMove( strAttr.c_str() );
	if( pXMLNode->GetAttr( "RotationType" , strAttr ) )				m_RotationType = ::StringToRotationType( strAttr.c_str() );
	if( pXMLNode->GetAttr( "AddDirection" , strAttr ) )				m_AddDirection = ::StringToAddDirection( strAttr.c_str() );
	if( pXMLNode->GetAttr( "ActionSituation" , strAttr ) )			m_ActionSituation = ::StringToActionSituation( strAttr.c_str() );
	if( pXMLNode->GetAttr( "FallCancel" , strAttr ) )				m_FallCancelType = ::StringToActionFallCancelType( strAttr.c_str() );
	if( pXMLNode->GetAttr( "AddSpeedRate" , strAttr ) )				m_AddSpeedRateType = ::StringToActionAddSpeedRateType( strAttr.c_str() );
	if( pXMLNode->GetAttr( "CheckItem" , strAttr ) )				m_ActionCheckItem = ::StringToActionChackItemType( strAttr.c_str() );
	if( pXMLNode->GetAttr( "UseSkill" , strAttr ) )					m_UseSkillType = ::StringToActionUseSkillType( strAttr.c_str() );
	if( pXMLNode->GetAttr( "ActionSpecialState" , strAttr ) )		m_dwActionSpecialValue = ::StringToSpecialState( strAttr.c_str() );

	pXMLNode->GetAttrInt( "SuperArmorValue" , m_iSuperArmorValue );

	if( pXMLNode->GetAttrInt( "FixRotation" , m_nFixRotation ) )
		m_nFixRotation = ( int )( ( float )m_nFixRotation * Action::RMATH_DEG2RAD );

	if( pXMLNode->GetAttr( "ChangeSpeed" , strAttr ) )
	{
		sscanf( strAttr.c_str() , "%d %d %d" , &m_nChangeSpeedStartFrame , &m_nAcceleration , &m_nLimitSpeed );

		// 처음 이후에는 고정되도록
		if( m_RotationType != CRT_NoneRotation && m_RotationType != CRT_CameraRotation )
			m_RotationType = CRT_FirstRotation;
	}

	// 처음 이후에는 고정되도록
	if( m_AdditionMove == CAM_FromAnimation && m_RotationType != CRT_NoneRotation && m_RotationType != CRT_CameraRotation )
		m_RotationType = CRT_FirstRotation;

	pXMLNode->GetAttrInt( "HoldMeBoneIndex" , m_nHoldMeBoneIndex );
	pXMLNode->GetAttrInt( "BoneActorGroup" , m_nPhysBoneActorGroup );
	pXMLNode->GetAttrFloat( "PickRange" , m_fPickRange );
	pXMLNode->GetAttrBool( "PickAlternativeGround" , m_bPickingAlternativeLand );

	_LoadXML_EndActionNode( pXMLNode );

	// 조준자 거리 체크
	_LoadXML_ShowCrossCheckAction( pXMLNode , strAttr );
	
	// 액션 속성 정보 읽기 //////////////////////////////////////////////////////////////////////////////////////////////////////

	_LoadXML_ActionAttr( pXMLNode );

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// ActionBranch ------------------------------------------------------------
	if( LoadActionBranch( pXMLNode->GetChilds( "ActionBranch" ) ) == false )
	{
		char strError[256];
		sprintf_s( strError , 256 , "LoadActionBranch error(%s)\n" , m_strActionName.c_str() );
		assert( false && strError );
		return false;		
	}

	// ActionBackgroundBranch
	if( LoadActionBackGroundBranch( pXMLNode->GetChilds( "ActionBackGroundBranch" ) ) == false )
	{
		char strError[256];
		sprintf_s( strError , 256 , "LoadActionBackGroundBranch error(%s)\n" , m_strActionName.c_str() );
		assert( false && strError );
		return false;
	}
	// FrameEvent ------------------------------------------------------------
	if( LoadFrameEvent( pXMLNode->GetChilds( "FrameEvent" ) , lstPreloadEffect , lstPreloadSound ) == false )
	{
		char strError[256];
		sprintf_s( strError , 256 , "LoadEventFrame error(%s)\n" , m_strActionName.c_str() );
		assert( false && strError );

		return false;
	}

	// ActionBranchFunction ---------------------------------------------------------
	LoadActionBranchFuntion( pXMLNode , mapActionFunction );


	if( pXMLNode->GetAttr( "CatchTargetAction" , m_strCatchTargetActionName ) )
		m_dwCatchTargetActionCode = CCrc32Static::StringCrc32( m_strCatchTargetActionName.c_str() );

	return true;
}

void CActionChart::_LoadXML_ActionAttr( XMLNode * pXMLNode )
{
	LoadXMLActionAttr( pXMLNode , "ContinueUseItem" , C9ACA_CONTINUE_USEITEM );			// 아이템 사용 액션 연결
	LoadXMLActionAttr( pXMLNode , "FootIKAble" , C9ACA_FOOTIKABLE );			// Foot IK	
	LoadXMLActionAttr( pXMLNode , "LookIKAble" , C9ACA_LOOKIKABLE );			// Look IK
	LoadXMLActionAttr( pXMLNode , "UseCastingTime" , C9ACA_USE_CASTINGTIME );			// 마법시전
	LoadXMLActionAttr( pXMLNode , "ShowCross" , C9ACA_SHOW_CROSS );			// 조준자 표시
	LoadXMLActionAttr( pXMLNode , "ShowName" , C9ACA_SHOW_NAME );			// 이름표시
	LoadXMLActionAttr( pXMLNode , "ShowHp" , C9ACA_SHOW_HP );			// 체력표시
	LoadXMLActionAttr( pXMLNode , "AirAction" , C9ACA_AIR_ACTION );			// 공중액션여부
	LoadXMLActionAttr( pXMLNode , "CatchNotFocus" , C9ACA_CATCH_NOT_FOCUS );			// 잡기시 카메라 포커스가 변경되지 않음
	LoadXMLActionAttr( pXMLNode , "InvisibleTarget" , C9ACA_INVISIBLE );			// 투명화
	LoadXMLActionAttr( pXMLNode , "IgnoreCatch" , C9ACA_IGNORE_CATCH );			// 잡기 무시
	LoadXMLActionAttr( pXMLNode , "SingleHit" , C9ACA_SINGLE_HIT );			// 액션 중 근접 공격이 한번만 발생 함
	LoadXMLActionAttr( pXMLNode , "IgnoreHook" , C9ACA_IGNORE_HOOK );			// 갈고리 공격 무시
	LoadXMLActionAttr( pXMLNode , "RunAvoidAction" , C9ACA_RUN_VOIDACTION );			// 데미지액션을 무시하고 해당 액션을 계속 진행 처리함
}

void CActionChart::_LoadXML_ShowCrossCheckAction( XMLNode * pXMLNode , string &strAttr )
{
	if( pXMLNode->GetAttr( "ShowCrossCheckAction" , strAttr ) )
	{
		char strParam[128];
		if( Action::ActionString::GetStrParam( strAttr.c_str() , 0 , strParam ) )
		{
			m_strShowCrossCheckAction = strParam;
			m_dwShowCrossCheckActionCode = CCrc32Static::StringCrc32( strParam );

			if( Action::ActionString::GetStrParam( strAttr.c_str() , 1 , strParam ) )
			{
				m_dwShowCrossCheckActionSkillType = ( DWORD )atoi( strParam );
			}
		}
	}
}

void CActionChart::_LoadXML_EndActionNode( XMLNode * pXMLNode )
{
	XMLNode * pEndActionNode = pXMLNode->GetChild( "ActionEnd" );
	if( pEndActionNode )
	{
		pEndActionNode->GetAttrInt( "BlendTime" , m_nEndActionBlendFrame );
		pEndActionNode->GetAttrBool( "UseSkillLevelName" , m_bUseSkillLevelName );

		m_strEndActionName = pEndActionNode->Value();
		m_dwEndActionCode = CCrc32Static::StringCrc32( m_strEndActionName.c_str() );

		pEndActionNode->GetAttrDWORD( "SkillType" , m_dwEndActionSkillType );
	}
}

void CActionChart::_LoadXML_ActionTypeInfo( XMLNode * pXMLNode , string strAttr )
{
	if( pXMLNode->GetAttr( "ActionType" , strAttr ) == true )
	{
		char * pNextToken = NULL;
		char * pToken = strtok_s( &strAttr[0] , " " , &pNextToken );
		while( pToken != NULL )
		{
			if( strcmp( pToken , "Attack" ) == 0 )					SET_ATTR( m_dwActionType , C9CAS_ATTACK );
			else if( strcmp( pToken , "AttackNormal" ) == 0 )   	SET_ATTR( m_dwActionType , C9CAS_ATTACK_NORMAL | C9CAS_ATTACK );
			else if( strcmp( pToken , "AttackRange" ) == 0 )		SET_ATTR( m_dwActionType , C9CAS_ATTACK_RANGE | C9CAS_ATTACK );
			else if( strcmp( pToken , "AttackHard3" ) == 0 )		SET_ATTR( m_dwActionType , C9CAS_ATTACK_HARD3 | C9CAS_ATTACK );
			else if( strcmp( pToken , "AttackHard2" ) == 0 )		SET_ATTR( m_dwActionType , C9CAS_ATTACK_HARD2 | C9CAS_ATTACK );
			else if( strcmp( pToken , "AttackHard1" ) == 0 )		SET_ATTR( m_dwActionType , C9CAS_ATTACK_HARD1 | C9CAS_ATTACK );
			else if( strcmp( pToken , "Move" ) == 0 )				SET_ATTR( m_dwActionType , C9CAS_MOVE );
			else if( strcmp( pToken , "Wait" ) == 0 )				SET_ATTR( m_dwActionType , C9CAS_WAIT );
			else if( strcmp( pToken , "MoveLeft" ) == 0 )			SET_ATTR( m_dwActionType , C9CAS_MOVE | C9CAS_MOVE_LEFT );
			else if( strcmp( pToken , "MoveRight" ) == 0 )			SET_ATTR( m_dwActionType , C9CAS_MOVE | C9CAS_MOVE_RIGHT );
			else if( strcmp( pToken , "MoveForward" ) == 0 )		SET_ATTR( m_dwActionType , C9CAS_MOVE | C9CAS_MOVE_FORWARD );
			else if( strcmp( pToken , "MoveBack" ) == 0 )			SET_ATTR( m_dwActionType , C9CAS_MOVE | C9CAS_MOVE_BACK );
			else if( strcmp( pToken , "AttackFire" ) == 0 )			SET_ATTR( m_dwActionType , C9CAS_ATTACK_FIRE | C9CAS_ATTACK );

			pToken = strtok_s( NULL , " " , &pNextToken );
		}
	}
}

void CActionChart::_LoadXML_OutLineInfo( XMLNode * pXMLNode )
{
	bool bShowOutline;
	if( pXMLNode->GetAttrBool( "ShowAutoOutline" , bShowOutline ) )
		m_IsShowOutline = bShowOutline ? C9ShowOutlineState::C9ShowOutlineState_TRUE : C9ShowOutlineState::C9ShowOutlineState_FALSE;
	else
		m_IsShowOutline = C9ShowOutlineState::C9ShowOutlineState_NONE;

	pXMLNode->GetAttrFloat( "OutlineThickness" , m_fOutlineThickness );
}

bool CActionChart::_LoadXML_MoveSpeedInfo( XMLNode * pXMLNode , string &strAttr )
{
	if( pXMLNode->GetAttr( "MoveSpeed" , strAttr ) == false )
		return false;
	
	if( strAttr == "Fetch" )
	{
		m_bMoveSpeedFetch = true;
	}
	else
	{
		m_fMoveSpeed = ( float )atof( strAttr.c_str() );
		if( m_fMoveSpeed <= 0.0f )
		{
			char strError[256];
			sprintf_s( strError , 256 , "MoveSpeed는 0 이상이어야 합니다.(%s)\n" , m_strActionName.c_str() );
			assert( false && strError );
			return false;
		}
	}

	return true;
}

bool CActionChart::_LoadXML_AnimationInfo( XMLNode * pXMLNode )
{
	if( pXMLNode->GetAttr( "AnimationName" , m_strAnimationFilename ) == false )
	{
		char strError[256];
		sprintf_s( strError , 256 , "애니메이션 이름 정보가 없습니다.(%s) : AnimationName = \n" , m_strActionName.c_str() );
		assert( false && strError );
		return false;
	}
	m_dwAnimationHashCode = CCrc32Static::StringCrc32( m_strAnimationFilename.c_str() );

	return true;
}

void CActionChart::LoadActionBranchFuntion( XMLNode * pXMLNode , HashMap_ActionFunction &mapActionFunction )
{
	XMLNodes BranchFunctionNodes = pXMLNode->GetChilds( "ActionBranchFunction" );
	for( size_t i = 0; i < BranchFunctionNodes.size(); ++i )
	{
		const string strFunctionName = BranchFunctionNodes[i]->Value();
		const DWORD dwFunctionNameHashCode = CCrc32Static::StringCrc32( strFunctionName.c_str() );

		HashMap_ActionFunction_Iter functionPos = mapActionFunction.find( dwFunctionNameHashCode );
		// 없으면 에러
		if( functionPos == mapActionFunction.end() )
		{
			char strError[256];
			sprintf_s( strError , 256 , "[%s] 액션브랜치함수를 찾을수 없습니다.[%s]" , strFunctionName.c_str() , m_strActionName.c_str() );
			MessageBoxA( NULL , strError , "Error" , MB_OK );
			continue;
		}

		CActionFunction * pActionFunction = functionPos->second;

		for( size_t cBranch = 0; cBranch < pActionFunction->m_lstBranch.size(); ++cBranch )
		{
			CActionBranch * pOriActionBranch = pActionFunction->m_lstBranch[cBranch];
			CActionBranch * pNewActionBranch;

			pNewActionBranch = new CActionBranch( *pOriActionBranch );

			pNewActionBranch->m_iCopyCount = m_CopyActionChartValue.m_iCopyCount;
			m_ddwInputMask |= pNewActionBranch->m_ddwInput;
			m_lstActionBranch.push_back( pNewActionBranch );
		}

		for( size_t cFrameEvent = 0; cFrameEvent < pActionFunction->m_lstFrameEvent.size(); ++cFrameEvent )
		{
			const CFrameEvent * pOriFrameEvent = pActionFunction->m_lstFrameEvent[cFrameEvent];
			const CFrameEventType frameEventType = pOriFrameEvent->GetType();

			CFrameEvent * pNewFrameEvent = CFrameEvent::Create_FrameEvent( frameEventType , m_actionData , pOriFrameEvent );
			if( pNewFrameEvent == NULL )
				continue;

			pNewFrameEvent->m_iCopyCount = m_CopyActionChartValue.m_iCopyCount;

			if( frameEventType == CFE_SwordTrail || frameEventType == CFE_AttackRound )
				SetActionAttr( C9ACA_EXIST_TRAIL );

			pNewFrameEvent->SetActionCodeAndIndex( m_dwHashcode , ( UINT )m_lstFrameEvent.size() );

			m_lstFrameEvent.push_back( pNewFrameEvent );
		}
	}
}

bool CActionChart::LoadActionBranch( XMLNodes nodes )
{
	for( size_t cBranch = 0; cBranch < nodes.size(); ++cBranch )
	{
		CActionBranch *pActionBranch = new CActionBranch;
		pActionBranch->m_iCopyCount = m_CopyActionChartValue.m_iCopyCount;

		if( pActionBranch->LoadXML( nodes[cBranch] ) == false )
		{
			RSAFE_DELETE( pActionBranch );
			return false;
		}

		m_ddwInputMask |= pActionBranch->m_ddwInput;
		m_lstActionBranch.push_back( pActionBranch );
	}

	return true;
}

bool CActionChart::LoadActionBackGroundBranch( XMLNodes nodes )
{
	for( size_t cBranch = 0; cBranch < nodes.size(); ++cBranch )
	{
		CActionBranch *pActionBranch = new CActionBranch;
		pActionBranch->m_iCopyCount = m_CopyActionChartValue.m_iCopyCount;

		if( pActionBranch->LoadXML( nodes[cBranch] ) == false )
		{
			RSAFE_DELETE( pActionBranch );
			return false;
		}
		pActionBranch->m_bIsBackGroundBranch = true;

		m_ddwInputMask |= pActionBranch->m_ddwInput;
		m_lstActionBranch.push_back( pActionBranch );
	}

	return true;
}

bool CActionChart::LoadFrameEvent( XMLNodes nodes , List_PreloadString &lstPreloadEffect , List_PreloadString &lstPreloadSound )
{
	for( size_t cFrameEvent = 0; cFrameEvent < nodes.size(); ++cFrameEvent )
	{
		CFrameEventType frameEventType	= CFrameEvent::Parse_GetFrameEventType( nodes[cFrameEvent]->GetAttr( "Type" ).c_str() );
		CFrameEvent * pFrameEvent		= CFrameEvent::Create_FrameEvent( frameEventType , m_actionData , NULL );

		if( pFrameEvent == NULL )
			continue;

		pFrameEvent->m_iCopyCount = m_CopyActionChartValue.m_iCopyCount;
		if( pFrameEvent->LoadXML( nodes[cFrameEvent] , lstPreloadEffect , lstPreloadSound ) == false )
		{
			RSAFE_DELETE( pFrameEvent );
			return false;
		}

		if( frameEventType == CFE_SwordTrail || frameEventType == CFE_AttackRound )
			SetActionAttr( C9ACA_EXIST_TRAIL );

		pFrameEvent->SetActionCodeAndIndex( m_dwHashcode , ( UINT )m_lstFrameEvent.size() );

		m_lstFrameEvent.push_back( pFrameEvent );
	}

	return true;
}

bool CActionChart::LoadXMLActionAttr( XMLNode *pXMLNode , const char *pStrName , C9ActionChartAttr attrType )
{
	bool bValue;
	// 아이템 사용 액션 연결
	if( pXMLNode->GetAttrBool( pStrName , bValue ) )
	{
		if( bValue )
			SetActionAttr( attrType );
		else
			ResetActionAttr( attrType );
		return true;
	}
	return false;
}

void CActionChart::CopyActionChartLevel( CActionChart *pActionChart , int iLevel )
{
	m_CopyActionChartValue.m_iCopyCount = iLevel;
	char strActionName[256];
	sprintf_s( strActionName , 256 , "%s%d" , pActionChart->m_strActionName.c_str() , iLevel + 1 );
	m_strActionName = strActionName;
	m_dwHashcode = CCrc32Static::StringCrc32( m_strActionName.c_str() );

	m_fMoveSpeed += ( m_CopyActionChartValue.m_fMoveSpeed * ( float )iLevel );
	m_fAnimationSpeed += ( m_CopyActionChartValue.m_fAnimationSpeed * ( float )iLevel );
	m_fFrameMoveSpeed += ( m_CopyActionChartValue.m_fFrameMoveSpeed * ( float )iLevel );
	m_lstActionBranch.resize( 0 );
	for( size_t i = 0; i < pActionChart->m_lstActionBranch.size(); ++i )
	{
		CActionBranch * pNewActionBranch = new CActionBranch( *( pActionChart->m_lstActionBranch[i] ) );
		pNewActionBranch->CopyActionValue( pActionChart->m_lstActionBranch[i] , iLevel );
		m_lstActionBranch.push_back( pNewActionBranch );
	}

	m_lstFrameEvent.resize( 0 );
	for( size_t i = 0; i < pActionChart->m_lstFrameEvent.size(); ++i )
	{
		CFrameEvent *pFrameEvent		= pActionChart->m_lstFrameEvent[i];
		CFrameEvent * pCopyFrameEvent	= CFrameEvent::Create_FrameEvent( pFrameEvent->GetType() , m_actionData , pFrameEvent );
		if( pCopyFrameEvent == NULL )
			continue;

		pCopyFrameEvent->CopyActionValue( pFrameEvent , iLevel );
		pCopyFrameEvent->SetActionCodeAndIndex( m_dwHashcode , ( UINT )m_lstFrameEvent.size() );

		m_lstFrameEvent.push_back( pCopyFrameEvent );
	}
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// @note : 액션인덱스가 여러개일 경우 액션인덱스에 해당되는 ActionDataIofo 를 찾고 그 값으로 셋팅
bool CActionChart::_LoadAttrFromActionDataInfo( XMLNode *pXMLNode )
{
	CActionDataInfo::LoadXmlActionIndex( pXMLNode , m_lstActionIndexHashCode );

	if( m_lstActionIndexHashCode.empty() || m_actionData.m_ActionDataInfoList.size() < 2 )
		return false;

	if( m_lstActionIndexHashCode.empty() == false && m_actionData.m_ActionDataInfoList.size() > 1 )
	{
		const DWORD dwActionIndex = m_lstActionIndexHashCode[0];

		for( size_t cInfo = 0; cInfo < m_actionData.m_ActionDataInfoList.size(); ++cInfo )
		{
			const CActionDataInfo * pInfo = m_actionData.m_ActionDataInfoList[cInfo];
			if( std::find( pInfo->m_lstActionIndexHashCode.begin() , pInfo->m_lstActionIndexHashCode.end() , dwActionIndex )
				!= pInfo->m_lstActionIndexHashCode.end() )
			{
				if( pInfo->m_bShowName )	SetActionAttr( C9ACA_SHOW_NAME );	else ResetActionAttr( C9ACA_SHOW_NAME );
				if( pInfo->m_bShowHp )		SetActionAttr( C9ACA_SHOW_HP );		else ResetActionAttr( C9ACA_SHOW_HP );
				if( pInfo->m_bShowCross )	SetActionAttr( C9ACA_SHOW_CROSS );	else ResetActionAttr( C9ACA_SHOW_CROSS );
				return true;
			}
		}
	}

	return false;
}

bool CActionChart::_attackFrameEventInverseMessageBox( const char* fileName , const char* actionName , ULONG prevFrameIndex , ULONG nextFrameIndex )
{
	char szText[4096];
	sprintf( szText ,
			 "프레임 이벤트 순서가 뒤바뀌거나 뒤바뀔 수 있도록 중첩되었습니다. 작은 프레임이 먼저 오도록 순서를 조정해 주세요.\n"
			 "취소 버튼을 누르면 더 이상 이 메시지가 뜨지 않습니다.\n"
			 "File[%s], Action[%s], PrevFrameEventIndex[%u], NextFrameEventIndex[%u]" ,
			 fileName , actionName , prevFrameIndex , nextFrameIndex );
	if( IDCANCEL == MessageBoxA( NULL , szText , "프레임 이벤트 경고" , MB_OKCANCEL ) )
	{
		// 더이상 체크하지 않음
		return false;
	}

	return true;
}

void CActionChart::Dump( C9File * pFile , List_PreloadString & lstPreloadEffect , List_PreloadString &lstPreloadSound )
{
	static const size_t sizeOfData = C9_SIZE_OF_BETWEEN_VALUE( m_dwHashcode , m_bMoveTargetRotation );

	CActionDataInfo::DumpActionIndex( pFile , m_lstActionIndexHashCode );

	if( pFile->IsSave() )
	{
		pFile->WriteData( m_strActionName );
		pFile->WriteData( m_strAnimationFilename );
		pFile->WriteData( m_strEndActionName );
		pFile->WriteData( m_strCatchTargetActionName );
		pFile->WriteData( m_strShowCrossCheckAction );

		pFile->WriteData_SizeT( &m_dwHashcode , sizeOfData );

		// ActionBranch
		const size_t _szActionBranch = m_lstActionBranch.size();	pFile->WriteData_SizeT( _szActionBranch );
		for( size_t cActionBranch = 0; cActionBranch < _szActionBranch; ++cActionBranch )
			m_lstActionBranch[cActionBranch]->Dump( pFile );

		// FrameEvent
		const size_t _szFrameEvent = m_lstFrameEvent.size();	pFile->WriteData_SizeT( _szFrameEvent );
		for( size_t cFrameEvent = 0; cFrameEvent < _szFrameEvent; ++cFrameEvent )
		{
			CFrameEvent * pFrameEvent = m_lstFrameEvent[cFrameEvent];

			assert( m_dwHashcode == pFrameEvent->m_dwActionCode );
			assert( cFrameEvent == pFrameEvent->m_uiFrameEventIndex );

			pFile->WriteData( ( int )pFrameEvent->GetType() );
			pFrameEvent->Dump( pFile , lstPreloadEffect , lstPreloadSound );
		}
	}
	else
	{
		pFile->ReadData( m_strActionName );
		pFile->ReadData( m_strAnimationFilename );
		pFile->ReadData( m_strEndActionName );
		pFile->ReadData( m_strCatchTargetActionName );
		pFile->ReadData( m_strShowCrossCheckAction );

		pFile->ReadData_SizeT( &m_dwHashcode , sizeOfData );

		// ActionBranch
		size_t _szActionBranch = 0;		pFile->ReadData_SizeT( _szActionBranch );
		for( size_t cActionBranch = 0; cActionBranch < _szActionBranch; ++cActionBranch )
		{
			CActionBranch * pActionBranch = new CActionBranch;
			pActionBranch->Dump( pFile );

			m_lstActionBranch.push_back( pActionBranch );
		}

		// FrameEvent
		size_t _szFrameEvent = 0;			pFile->ReadData_SizeT( _szFrameEvent );
		for( size_t cFrameEvent = 0; cFrameEvent < _szFrameEvent; ++cFrameEvent )
		{
			CFrameEventType _Type;		pFile->ReadData( ( int & )_Type );
			CFrameEvent * pFrameEvent = CFrameEvent::Create_FrameEvent( _Type , m_actionData , NULL );
			if( pFrameEvent == NULL )
				continue;
			pFrameEvent->Dump( pFile , lstPreloadEffect , lstPreloadSound );

			m_lstFrameEvent.push_back( pFrameEvent );

		}
	}
}


#include "stdafx.h"
#include "ActionBranch.h"
#include "ActionDefine.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
CActionBranch::CActionBranch()
: m_iCopyCount( 0 )

, m_dwTargetActionCode( 0 )
, m_dwTargetAIActionCode( 0 )

, m_InputTiming( CIT_None )
, m_nInputStartTime( -1 )
, m_nInputEndTime( -1 )

, m_ddwInput( 0 )
, m_nHitCount( 0 )
, m_dwClassKey( 0 )
, m_nBlendFrame( 0 )

, m_fCatchDistance( 100.0f )
, m_eInputCheckState( C9_INPUT_CHECK_NONE )

, m_dwPlayerValueNameHashCode( 0 )
, m_iPlayerValue( 0 )
, m_PlayerValueCompareType( C9VCT_EQUAL )

, m_dwPSValueNameHashCode( 0 )
, m_iPlayerServerValue( 0 )
, m_PlayerServerValueCompareType( C9VCT_EQUAL )
, m_bCheckPrePSValue( false )

, m_dwTimerNameHashCode( 0 )
, m_fTimerTime( 0.0f )
, m_TimerCompareType( C9VCT_BGTHN )

, m_CopyActionBranchValue()
, m_dwAbnormalKey( 0 )
, m_dwTarget( 0 )

, m_fMoveDistanceThreshold( 0 )

, m_dwSkillTypeKey( 0 )
, m_bCheckSkill( true )
, m_bUseSkillLevelName( true )

, m_bWaitActionEnd( false )
, m_bIsBackGroundBranch( false )
, m_dwTalisManEnchantLevel( 0 )
{
}

//************************************
// FullName:  C9ActionBranch::Parse_GetInput	; m_ddwInput 을 문자열로 부터 구하기 위함
// Returns:   UINT64							; m_ddwInput 타입과 동일
// Parameter: String strParameter				; ActionBranch 의 Input 속성의 값
//************************************
UINT64 CActionBranch::Parse_GetInput( const char * pszParameter )
{
	UINT64 ddwInput = 0x0;

	const char strSep[] = "+";

	char strTemp[ 512 ];
	strcpy_s( strTemp, 512, pszParameter );

	char * pNextToken = NULL;
	char * pToken = strtok_s( strTemp, strSep, &pNextToken );

	while( pToken )
	{		
		if( strcmp( pToken, "W" ) == 0 )					ddwInput |= CI_W;
		else if( strcmp( pToken, "WW" ) == 0 )				ddwInput |= CI_WW | CI_W;
		else if( strcmp( pToken, "W_UP" ) == 0 )			ddwInput |= CI_W_UP;
		else if( strcmp( pToken, "A" ) == 0 )				ddwInput |= CI_A;
		else if( strcmp( pToken, "AA" ) == 0 )				ddwInput |= CI_AA | CI_A;
		else if( strcmp( pToken, "A_UP" ) == 0 )			ddwInput |= CI_A_UP;
		else if( strcmp( pToken, "D" ) == 0 )				ddwInput |= CI_D;
		else if( strcmp( pToken, "DD" ) == 0 )				ddwInput |= CI_DD | CI_D;
		else if( strcmp( pToken, "D_UP" ) == 0 )			ddwInput |= CI_D_UP;
		else if( strcmp( pToken, "S" ) == 0 )				ddwInput |= CI_S;
		else if( strcmp( pToken, "SS" ) == 0 )				ddwInput |= CI_SS | CI_S;
		else if( strcmp( pToken, "S_UP" ) == 0 )			ddwInput |= CI_S_UP;

		else if( strcmp( pToken, "Q" ) == 0 )				ddwInput |= CI_Q;
		else if( strcmp( pToken, "Q_UP" ) == 0 )			ddwInput |= CI_Q_UP;
		else if( strcmp( pToken, "F" ) == 0 )				ddwInput |= CI_F;
		else if( strcmp( pToken, "F_UP" ) == 0 )			ddwInput |= CI_F_UP;
		else if( strcmp( pToken, "E" ) == 0 )				ddwInput |= CI_E;
		else if( strcmp( pToken, "R" ) == 0 )				ddwInput |= CI_R;

		else if( strcmp( pToken, "SPACE" ) == 0 )			ddwInput |= CI_SPACE;
		else if( strcmp( pToken, "SPACESPACE" ) == 0 )		ddwInput |= CI_SPACESPACE | CI_SPACE;
		else if( strcmp( pToken, "SPACE_UP" ) == 0 )		ddwInput |= CI_SPACE_UP;
		else if( strcmp( pToken, "SHIFT" ) == 0 )			ddwInput |= CI_SHIFT;
		else if( strcmp( pToken, "INSERT" ) == 0 )			ddwInput |= CI_INSERT;
		else if( strcmp( pToken, "CAPSLOCK" ) == 0 )		ddwInput |= CI_CAPSLOCK;
		else if( strcmp( pToken, "TAB" ) == 0 )				ddwInput |= CI_TAB;

		else if( strcmp( pToken, "M1" ) == 0 )				ddwInput |= CI_M1;
		else if( strcmp( pToken, "M1_UP" ) == 0 )			ddwInput |= CI_M1_UP;
		else if( strcmp( pToken, "M2" ) == 0 )				ddwInput |= CI_M2;
		else if( strcmp( pToken, "M2_UP" ) == 0 )			ddwInput |= CI_M2_UP;

		else if( strcmp( pToken, "LAND" ) == 0 )			ddwInput |= CI_LAND;
		else if( strcmp( pToken, "WALL" ) == 0 )			ddwInput |= CI_WALL;
		else if( strcmp( pToken, "WATERSINK" ) == 0 )		ddwInput |=	CI_WATERSINK;

		else if( strcmp( pToken, "HIT" ) == 0 )				ddwInput |= CI_HIT;
		else if( strcmp( pToken, "DAMAGEHIT" ) == 0 )		ddwInput |= CI_DAMAGEHIT;
		else if( strcmp( pToken, "CATCH" ) == 0 )			ddwInput |= CI_CATCH;
		else if( strcmp( pToken, "CANTCATCH" ) == 0 )		ddwInput |= CI_CANTCATCH;
		else if( strcmp( pToken, "BIGCATCH" ) == 0 )		ddwInput |= CI_BIGCATCH;
		else if( strcmp( pToken, "HOOK" ) == 0 )			ddwInput |= CI_HOOK;
		else if( strcmp( pToken, "CASTING" ) == 0 )			ddwInput |= CI_CASTING;

		else if( strcmp( pToken, "DEFHIT" ) == 0 )			ddwInput |= CI_DEFHIT;
		else if( strcmp( pToken, "DEFHITKO" ) == 0 )		ddwInput |= CI_DEFHITKO;

		else if( strcmp( pToken, "NEARITEM" ) == 0 )		ddwInput |= CI_NEARITEM;

		else if( strcmp( pToken, "ARROWHIT" ) == 0 )		ddwInput |= CI_ARROWHIT;

		else if( strcmp( pToken, "ROTATIONLEFT" ) == 0 )	ddwInput |= CI_ROTATIONLEFT;
		else if( strcmp( pToken, "ROTATIONRIGHT" ) == 0 )	ddwInput |= CI_ROTATIONRIGHT;

		else if( strcmp( pToken, "EVENT" ) == 0 )			ddwInput |= CI_EVENT;
		else if( strcmp( pToken, "ACTION" ) == 0 )			ddwInput |= CI_ACTION;
		else if( strcmp( pToken, "TOGGLE" ) == 0 )			ddwInput |= CI_TOGGLE;

		else if( strcmp( pToken, "PVALUE" ) == 0 )			ddwInput |= CI_PVALUE;
		else if( strcmp( pToken, "PTIMER" ) == 0 )			ddwInput |=	CI_PTIMER;
		else if( strcmp( pToken, "MAXFURY" ) == 0 )			ddwInput |= CI_MAXFURY;
		else if( strcmp( pToken, "PSVALUE" ) == 0 )			ddwInput |= CI_PVALUE_SERVER;

		else if( strcmp( pToken, "SKILLBOOK" ) == 0 )		ddwInput |= CI_SKILLBOOK;

		else if( strcmp( pToken, "MOVEDISTANCE" ) == 0 )	ddwInput |= CI_MOVEDISTANCE;
		else if( strcmp( pToken, "ABNORMAL" ) == 0)			ddwInput |= CI_ABNORMAL;

		else if( strcmp( pToken, "AUTOFISHING") == 0 )		ddwInput |= CI_AUTO_FISHING;

		else if( strcmp( pToken, "DFISHING" ) ==0 )			ddwInput |= CI_DFISHING;
		else if( strcmp( pToken, "DNFISHING") == 0 )		ddwInput |= CI_DNFISHING;

		else if( strcmp(pToken , "TALISMAN") == 0 )			ddwInput |= CI_TALISMAN;

		else if( strcmp( pToken, "None" ) == 0 )			;
		else MessageBoxA( NULL, pToken, "키가없습니다.", 0 );

		pToken = strtok_s( NULL, strSep, &pNextToken );
	} 

	return ddwInput;		
}

//************************************
// FullName:  C9ActionBranch::Parse_GetInputString	; m_ddwInput 을 ActionBranch 의 Input 속성의 값 문자열로 변환
// Returns:   std::string						  	; ActionBranch 의 Input 속성의 값 문자열
// Parameter: UINT64 ddwInput					  	; m_ddwInput 타입과 동일
//************************************
string CActionBranch::Parse_GetInputString( UINT64 ddwInput )
{
	string strInput;

	if ( IS_ATTR( ddwInput, CI_W ) )				strInput += "W+";
	if ( IS_ATTR( ddwInput, CI_WW ) )				strInput += "WW+";
	if ( IS_ATTR( ddwInput, CI_W_UP ) )				strInput += "W_UP+";
	if ( IS_ATTR( ddwInput, CI_A ) )				strInput += "A+";
	if ( IS_ATTR( ddwInput, CI_AA ) )				strInput += "AA+";
	if ( IS_ATTR( ddwInput, CI_A_UP ) )				strInput += "A_UP+";
	if ( IS_ATTR( ddwInput, CI_D ) )				strInput += "D+";
	if ( IS_ATTR( ddwInput, CI_DD ) )				strInput += "DD+";
	if ( IS_ATTR( ddwInput, CI_D_UP ) )				strInput += "D_UP+";
	if ( IS_ATTR( ddwInput, CI_S ) )				strInput += "S+";
	if ( IS_ATTR( ddwInput, CI_SS ) )				strInput += "SS+";
	if ( IS_ATTR( ddwInput, CI_S_UP ) )				strInput += "S_UP+";

	if ( IS_ATTR( ddwInput, CI_Q ) )				strInput += "Q+";
	if ( IS_ATTR( ddwInput, CI_Q_UP ) )				strInput += "Q_UP+";
	if ( IS_ATTR( ddwInput, CI_F ) )				strInput += "F+";
	if ( IS_ATTR( ddwInput, CI_F_UP ) )				strInput += "F_UP+";
	if ( IS_ATTR( ddwInput, CI_E ) )				strInput += "E+";
	if ( IS_ATTR( ddwInput, CI_R ) )				strInput += "R+";

	if ( IS_ATTR( ddwInput, CI_SPACE ) )			strInput += "SPACE+";
	if ( IS_ATTR( ddwInput, CI_SPACESPACE ) )		strInput += "SPACESPACE+";
	if ( IS_ATTR( ddwInput, CI_SPACE_UP ) )			strInput += "SPACE_UP+";
	if ( IS_ATTR( ddwInput, CI_SHIFT ) )			strInput += "SHIFT+";
	if ( IS_ATTR( ddwInput, CI_INSERT ) )			strInput += "INSERT+";
	if ( IS_ATTR( ddwInput, CI_CAPSLOCK ) )			strInput += "CAPSLOCK+";
	if ( IS_ATTR( ddwInput, CI_TAB ) )				strInput += "TAB+";

	if ( IS_ATTR( ddwInput, CI_M1 ) )				strInput += "M1+";
	if ( IS_ATTR( ddwInput, CI_M1_UP ) )			strInput += "M1_UP+";
	if ( IS_ATTR( ddwInput, CI_M2 ) )				strInput += "M2+";
	if ( IS_ATTR( ddwInput, CI_M2_UP ) )			strInput += "M2_UP+";

	if ( IS_ATTR( ddwInput, CI_LAND ) )				strInput += "LAND+";
	if ( IS_ATTR( ddwInput, CI_WALL ) )				strInput += "WALL+";
	if ( IS_ATTR( ddwInput, CI_WATERSINK ) )		strInput += "WATERSINK+";

	if ( IS_ATTR( ddwInput, CI_HIT ) )				strInput += "HIT+";
	if ( IS_ATTR( ddwInput, CI_DAMAGEHIT ) )		strInput += "DAMAGEHIT+";
	if ( IS_ATTR( ddwInput, CI_CATCH ) )			strInput += "CATCH+";
	if ( IS_ATTR( ddwInput, CI_CANTCATCH ) )		strInput += "CANTCATCH+";
	if ( IS_ATTR( ddwInput, CI_BIGCATCH ) )			strInput += "BIGCATCH+";
	if ( IS_ATTR( ddwInput, CI_HOOK ) )				strInput += "HOOK+";
	if ( IS_ATTR( ddwInput, CI_CASTING ) )			strInput += "CASTING+";

	if ( IS_ATTR( ddwInput, CI_DEFHIT ) )			strInput += "DEFHIT+";
	if ( IS_ATTR( ddwInput, CI_DEFHITKO ) )			strInput += "DEFHITKO+";

	if ( IS_ATTR( ddwInput, CI_NEARITEM ) )			strInput += "NEARITEM+";

	if ( IS_ATTR( ddwInput, CI_ARROWHIT ) )			strInput += "ARROWHIT+";

	if ( IS_ATTR( ddwInput, CI_ROTATIONLEFT ) )		strInput += "ROTATIONLEFT+";
	if ( IS_ATTR( ddwInput, CI_ROTATIONRIGHT ) )	strInput += "ROTATIONRIGHT+";

	if ( IS_ATTR( ddwInput, CI_EVENT ) )			strInput += "EVENT+";
	if ( IS_ATTR( ddwInput, CI_TOGGLE ) )			strInput += "TOGGLE+";
	if ( IS_ATTR( ddwInput, CI_ACTION ) )			strInput += "ACTION+";

	if ( IS_ATTR( ddwInput, CI_PVALUE ) )			strInput += "PVALUE+";
	if ( IS_ATTR( ddwInput, CI_PTIMER ) )			strInput += "PTIMER+";
	if ( IS_ATTR( ddwInput, CI_MAXFURY ) )			strInput += "MAXFURY+";
	if ( IS_ATTR( ddwInput, CI_PVALUE_SERVER ) )	strInput += "PSVALUE+";

	if ( IS_ATTR( ddwInput, CI_SKILLBOOK ) )		strInput += "SKILLBOOK+";
	if ( IS_ATTR( ddwInput, CI_MOVEDISTANCE ) )		strInput += "MOVEDISTANCE+";
	if ( IS_ATTR( ddwInput, CI_ABNORMAL ) )			strInput += "ABNORMAL+";

	if ( IS_ATTR( ddwInput, CI_AUTO_FISHING ) )		strInput += "AUTOFISHING+";

	if ( IS_ATTR( ddwInput, CI_DFISHING ) )			strInput +=  "DFISHING" ;
	if ( IS_ATTR( ddwInput, CI_DNFISHING ) )		strInput +=  "DNFISHING";

	if ( IS_ATTR( ddwInput, CI_TALISMAN ) )			strInput +=  "TALISMAN";


	return strInput;
}

C9_INPUT_CHECK_STATE CActionBranch::Parse_GetInputCheck( UINT64 ddwInput, const char * pszParameter )
{
	C9_INPUT_CHECK_STATE eCheckIndex = C9_INPUT_CHECK_NONE;
	if ( ddwInput & CI_HOOK )
	{
		if ( strcmp( pszParameter, "HOOK_TARGET" ) == 0 )					eCheckIndex = C9_INPUT_CHECK_HOOK_TARGET;
		else if( strcmp( pszParameter, "HOOK_ACTION" ) == 0 )				eCheckIndex = C9_INPUT_CHECK_HOOK_ACTION;
	}

	return eCheckIndex;
}

//----------------------------------------------------------------------------------------------------------------
bool CActionBranch::LoadXML( XMLNode *pXMLNode )
{
	m_strTargetAction = pXMLNode->Value();
	m_dwTargetActionCode = CCrc32Static::StringCrc32( m_strTargetAction.c_str() );

	if( pXMLNode->GetAttr( "NextAIAction", m_strTargetAIAction ) )
		m_dwTargetAIActionCode = ::CCrc32Static::StringCrc32( m_strTargetAIAction.c_str() );
	

	string strAttr;
	if( pXMLNode->GetAttr( "InputTiming", strAttr ) )
	{
		m_InputTiming = ::StringToActionInputTiming( Action::ActionString::GetToken( strAttr , 0 ).c_str() );
		if( m_InputTiming == CIT_Section )
		{
			char strDumy[ 256 ];
			sscanf( strAttr.c_str(), "%s %d %d", strDumy, &m_nInputStartTime, &m_nInputEndTime );
		}
	}

	m_ddwInput = CActionBranch::Parse_GetInput( pXMLNode->GetAttr( "Input" ).c_str() );
	pXMLNode->GetAttrInt( "BlendTime", m_nBlendFrame );
	pXMLNode->GetAttrInt( "HitCount", m_nHitCount );
	pXMLNode->GetAttrDWORD( "ClassKey", m_dwClassKey );
	pXMLNode->GetAttrDWORD( "SkillType", m_dwSkillTypeKey );
	pXMLNode->GetAttrBool( "CheckSkill", m_bCheckSkill );
	pXMLNode->GetAttrBool( "UseSkillLevelName", m_bUseSkillLevelName );
	pXMLNode->GetAttrFloat( "CatchDistance", m_fCatchDistance );
	pXMLNode->GetAttrFloat( "ActionMoveDistance", m_fMoveDistanceThreshold );
	pXMLNode->GetAttrBool( "WaitActionEnd", m_bWaitActionEnd);
	pXMLNode->GetAttrDWORD( "AbnormalKey", m_dwAbnormalKey );

	pXMLNode->GetAttrDWORD( "TLM_EnchantLevel", m_dwTalisManEnchantLevel );			// 부적 강화 단계레벨 검사
	m_dwTarget = CCrc32Static::StringCrc32( pXMLNode->GetAttr( "Target" ).c_str() );

	m_eInputCheckState = CActionBranch::Parse_GetInputCheck( m_ddwInput, pXMLNode->GetAttr( "StateCheck" ).c_str() );

	m_dwPlayerValueNameHashCode = CCrc32Static::StringCrc32( pXMLNode->GetAttr( "PValueName" ).c_str() );
	pXMLNode->GetAttrInt( "PValue", m_iPlayerValue);
	m_PlayerValueCompareType = ::StringToValueCompareType( pXMLNode->GetAttr( "POperation" ).c_str() );

	m_dwPSValueNameHashCode = CCrc32Static::StringCrc32( pXMLNode->GetAttr( "PSValueName" ).c_str() );
	pXMLNode->GetAttrInt( "PSValue", m_iPlayerServerValue );
	m_PlayerServerValueCompareType = ::StringToValueCompareType( pXMLNode->GetAttr( "PSOperation" ).c_str() );
	pXMLNode->GetAttrBool( "CheckPreValue", m_bCheckPrePSValue );

	m_dwTimerNameHashCode = CCrc32Static::StringCrc32( pXMLNode->GetAttr( "TimerName" ).c_str() );
	pXMLNode->GetAttrFloat( "TimerTime", m_fTimerTime );
	m_TimerCompareType = ::StringToValueCompareType( pXMLNode->GetAttr( "TimerOperation" ).c_str() );

	// 액션 복사 로드	////////////////////////////////
	if ( m_iCopyCount > 1 )
	{
		pXMLNode->GetAttrFloat( "CopyAddTimerTime", m_CopyActionBranchValue.m_fTimerTime );
	}
	/////////////////////////////////////////////////////


	return true;
}

void CActionBranch::CopyActionValue( CActionBranch *pActionBranch, int iLevel )
{
	if ( m_iCopyCount > 1 && iLevel > 0 )
	{
		m_fTimerTime += ( m_CopyActionBranchValue.m_fTimerTime * (float)iLevel );
	}
}

void CActionBranch::Dump( C9File * pFile )
{
	static const size_t sizeOfData = C9_SIZE_OF_BETWEEN_VALUE( m_dwTargetActionCode, m_bWaitActionEnd );

	if( pFile->IsSave() )
	{
		pFile->WriteData( m_strTargetAction );
		pFile->WriteData( m_strTargetAIAction );

		pFile->WriteData_SizeT( &m_dwTargetActionCode, sizeOfData );
	}
	else
	{	
		pFile->ReadData( m_strTargetAction );
		pFile->ReadData( m_strTargetAIAction );

		pFile->ReadData_SizeT( &m_dwTargetActionCode, sizeOfData );

	}
}
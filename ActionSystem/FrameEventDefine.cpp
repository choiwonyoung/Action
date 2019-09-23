#include "stdafx.h"
#include "FrameEventDefine.h"
#include "ActionData.h"

bool CFrameEventAttackEffect::LoadXML( XMLNode *pXMLNode )
{
	pXMLNode->GetAttrInt( "AttackEffect" , m_nAttackEffect );

	if( m_nAttackEffect > -1 /*&& g_pDataMgr->GetBaseEffect( m_nAttackEffect ) == NULL*/ )
	{
		char strError[256];
		sprintf_s( strError , 256 , "[%d] 인덱스의 AttackEffect 를 찾을수 없습니다." , m_nAttackEffect );
		MessageBoxA( NULL , strError , "Error" , MB_OK );
		return false;
	}

	pXMLNode->GetAttrInt( "AttackSound" , m_nAttackSound );

	if( m_nAttackSound > -1 /*&& g_pDataMgr->GetBaseSound( m_nAttackSound ) == NULL*/ )
	{
		char strError[256];
		sprintf_s( strError , 256 , "[%d] 인덱스의 AttackSound 를 찾을수 없습니다." , m_nAttackSound );
		MessageBoxA( NULL , strError , "Error" , MB_OK );
		return false;
	}

	pXMLNode->GetAttrHexDWORD( "AttackColor" , ( DWORD & )m_clrAttackColor.c );

	pXMLNode->GetAttrBool( "EffectAttachTarget" , m_bEffectAttachTarget );
	pXMLNode->GetAttr( "DamageEffectAttachBone" , m_strDamageEffectAttachBone );

	string strAttr;
	if( pXMLNode->GetAttr( "EffectScale" , strAttr ) )
		sscanf_s( strAttr.c_str() , "%f %f %f" , &m_vecEffectScale.x , &m_vecEffectScale.y , &m_vecEffectScale.z );

	if( pXMLNode->GetAttr( "EffectRotation" , strAttr ) )
	{
		sscanf_s( strAttr.c_str() , "%f %f %f" , &m_vecEffectRotation.x , &m_vecEffectRotation.y , &m_vecEffectRotation.z );
		XMVECTOR tmpVec = XMLoadFloat3( &m_vecEffectRotation );
		float degree = Action::RMATH_DEG2RAD;
		tmpVec = tmpVec * degree;
		XMStoreFloat3( &m_vecEffectRotation , tmpVec );

	}

	return true;
}


void CFrameEventAttackEffect::Dump( C9File * pFile )
{
	static const size_t _sizeOfData = C9_SIZE_OF_BETWEEN_VALUE( m_clrAttackColor , m_bEffectAttachTarget );

	if( pFile->IsSave() )
	{
		pFile->WriteData( m_strDamageEffectAttachBone );

		pFile->WriteData_SizeT( &m_clrAttackColor , _sizeOfData );
	}
	else
	{
		pFile->ReadData( m_strDamageEffectAttachBone );

		pFile->ReadData_SizeT( &m_clrAttackColor , _sizeOfData );
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// CFrameEventAttackValue
CFrameEventAttackValue::CFrameEventAttackValue( const CActionData& actionData )
	: m_fFrameDelayNow( 0.0f )

	, m_fAttackDamageVelocity( 0.0f )
	, m_fAttackDamageAcceleration( 0.0f )
	, m_fAttackFlyFinalHeight( 0.0f )
	, m_fAttackFloatTime( 0.0f )

	, m_fFlyAttackDamageVelocity( 0.0f )
	, m_fFlyAttackDamageAcceleration( 0.0f )
	, m_fFlyAttackFlyFinalHeight( 0.0f )
	, m_fFlyAttackFloatTime( 0.0f )

	, m_KnockDownOtherType( C9KDOT_None )
	, m_AttackTargetType( C9ATT_ENEMY )
	, m_ReactDirectionType( C9RDT_HitDirFront )

	, m_fDelayFrame( 0.0f )
	, m_fFrameDelaySub( 0.0f )
	, m_fFrameDelayEnd( 0.0f )
	, m_fSlamSpeed( 0.0f )
	, m_fRigidTime( 0.0f )
	, m_fAttackAngle( Action::RMATH_HALF_PI )
	, m_fDefenseCrashRate( 0.0f )
	, m_fGuardCrash( 1.0f )

	/*, m_iSuperArmorBreak( actionData.m_ActionDataInfoList[0]->m_iSuperArmorBreak )*/

	, m_bDownAttack( false )
	, m_bSpinAttack( false )
{
	actionData.m_dwHashCode;
}

float CFrameEventAttackValue::GetDefaultDamageVelocity( C9ActionAttackType attackType )
{
	if( attackType == CAAT_Normal ||
		attackType == CAAT_Down )
		return 300.0f;
	else if( attackType == CAAT_Push )
		return 1000.0f;
	else if( attackType == CAAT_Knockdown )
		return 500.0f;
	else if( attackType == CAAT_DownFly )
		return 200.0f;

	return 0.0f;
}

float CFrameEventAttackValue::GetDefaultDamageAcceleration( C9ActionAttackType attackType )
{
	if( attackType == CAAT_Push )
		return -3500.0f;
	else if( attackType == CAAT_Knockdown )
		return -350.0f;
	else if( attackType == CAAT_DownFly )
		return -400.0f;

	return 0.0f;
}

float CFrameEventAttackValue::GetDefaultFlyFinalHeight( C9ActionAttackType attackType )
{
	if( attackType == CAAT_Knockdown )
		return 70.0f;
	else if( attackType == CAAT_DownFly )
		return 200.0f;

	return 0.0f;
}

float CFrameEventAttackValue::GetDefaultFloatTime( C9ActionAttackType attackType )
{
	if( attackType == CAAT_Knockdown ||
		attackType == CAAT_DownFly )
		return 0.3f;

	return 0.0f;
}

bool CFrameEventAttackValue::LoadXML( XMLNode *pXMLNode , C9ActionAttackType attackType )
{
	string strAttr;

	if( !pXMLNode->GetAttrFloat( "AttackDamageVelocity" , m_fAttackDamageVelocity ) )				m_fAttackDamageVelocity = GetDefaultDamageVelocity( attackType );
	if( !pXMLNode->GetAttrFloat( "AttackDamageAcceleration" , m_fAttackDamageAcceleration ) )		m_fAttackDamageAcceleration = GetDefaultDamageAcceleration( attackType );
	if( !pXMLNode->GetAttrFloat( "AttackFlyFinalHeight" , m_fAttackFlyFinalHeight ) )				m_fAttackFlyFinalHeight = GetDefaultFlyFinalHeight( attackType );
	if( !pXMLNode->GetAttrFloat( "AttackFloatTime" , m_fAttackFloatTime ) )							m_fAttackFloatTime = GetDefaultFloatTime( attackType );

	if( !pXMLNode->GetAttrFloat( "FAttackDamageVelocity" , m_fFlyAttackDamageVelocity ) )			m_fFlyAttackDamageVelocity = GetDefaultDamageVelocity( attackType );
	if( !pXMLNode->GetAttrFloat( "FAttackDamageAcceleration" , m_fFlyAttackDamageAcceleration ) )	m_fFlyAttackDamageAcceleration = GetDefaultDamageAcceleration( attackType );
	if( !pXMLNode->GetAttrFloat( "FAttackFlyFinalHeight" , m_fFlyAttackFlyFinalHeight ) )			m_fFlyAttackFlyFinalHeight = GetDefaultFlyFinalHeight( attackType );
	if( !pXMLNode->GetAttrFloat( "FAttackFloatTime" , m_fFlyAttackFloatTime ) )						m_fFlyAttackFloatTime = GetDefaultFloatTime( attackType );

	if( pXMLNode->GetAttr( "KnockDownOther" , strAttr ) )											m_KnockDownOtherType = ::StringToKnockDownOtherType( strAttr.c_str() );
	if( pXMLNode->GetAttr( "AttackTargetType" , strAttr ) )											m_AttackTargetType = ::StringToAttackTargetType( strAttr.c_str() );
	if( pXMLNode->GetAttr( "ReactDirection" , strAttr ) )											m_ReactDirectionType = ::StringToReactDirectionType( strAttr.c_str() );

	pXMLNode->GetAttrFloat( "DelayFrame" , m_fDelayFrame );
	pXMLNode->GetAttrFloat( "FrameDelaySub" , m_fFrameDelaySub );
	pXMLNode->GetAttrFloat( "FrameDelayEnd" , m_fFrameDelayEnd );
	m_fFrameDelayNow = m_fDelayFrame;

	pXMLNode->GetAttrFloat( "SlamSpeed" , m_fSlamSpeed );
	pXMLNode->GetAttrFloat( "RigidTime" , m_fRigidTime );
	if( pXMLNode->GetAttrFloat( "AttackAngle" , m_fAttackAngle ) )
		m_fAttackAngle = m_fAttackAngle * Action::RMATH_DEG2RAD * 0.5f;

	pXMLNode->GetAttrFloat( "DefenseCrashRate" , m_fDefenseCrashRate );
	pXMLNode->GetAttrFloat( "GuardCrash" , m_fGuardCrash );

	pXMLNode->GetAttrInt( "SuperArmorBreak" , m_iSuperArmorBreak );

	pXMLNode->GetAttrBool( "DownAttack" , m_bDownAttack );
	pXMLNode->GetAttrBool( "SpinAttack" , m_bSpinAttack );

	return true;
}


void CFrameEventAttackValue::Dump( C9File * pFile )
{
	static const size_t _sizeOfData = C9_SIZE_OF_BETWEEN_VALUE( m_fAttackDamageVelocity , m_bSpinAttack );

	if( pFile->IsSave() )
	{
		pFile->WriteData_SizeT( &m_fAttackDamageVelocity , _sizeOfData );
	}
	else
	{
		pFile->ReadData_SizeT( &m_fAttackDamageVelocity , _sizeOfData );

		m_fFrameDelayNow = m_fDelayFrame;
	}
}

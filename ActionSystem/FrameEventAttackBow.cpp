#include "stdafx.h"
#include "FrameEventAttackBow.h"
#include "FrameEventAttackNormal.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// CFrameEventAttackBow
CFrameEventAttackBow::ArrowTargetType	CFrameEventAttackBow::Parse_TargetType( const char * pszType )
{
	if( strcmp( pszType , "Normal" ) == 0 )					return TargetType_Normal;
	if( strcmp( pszType , "AbnormalTarget" ) == 0 )			return TargetType_Abnormal;
	if( strcmp( pszType , "MultiAutoTarget" ) == 0 )		return TargetType_AutoTarget;
	if( strcmp( pszType , "AutoRandomTarget" ) == 0 )		return TargetType_AutoRandomTarget;

	return TargetType_None;
}

CFrameEventAttackBow::ArrowTargetType	CFrameEventAttackBow::Convert_FireToTargetType( const char * pszType )	//타겟 타입 None 일시 파이어 타입에서 임의로 타겟 타입을 정한다
{
	if( strcmp( pszType , "MultiAutoTarget" ) == 0 )	return TargetType_AutoTarget;
	if( strcmp( pszType , "AbnormalTarget" ) == 0 )		return TargetType_Abnormal;

	return TargetType_Normal;
}

CFrameEventAttackBow::ArrowFireType	CFrameEventAttackBow::Parse_FireType( const char * pszType )
{
	if( strcmp( pszType , "Shotgun" ) == 0 )			return FireType_Shotgun;
	if( strcmp( pszType , "MultiShot" ) == 0 )			return FireType_MultiShot;
	if( strcmp( pszType , "MultiShotV" ) == 0 )			return FireType_MultiShotV;
	if( strcmp( pszType , "ArrayShot" ) == 0 )			return FireType_ArrayShot;
	if( strcmp( pszType , "ArrayShotV" ) == 0 )			return FireType_ArrayShotV;
	if( strcmp( pszType , "MultiAutoTarget" ) == 0 )	return FireType_Target;
	
	if( strcmp( pszType , "ToTarget" ) == 0 )			return FireType_Target;
	if( strcmp( pszType , "SingleCorner" ) == 0 )		return FireType_SingleCorner;
	if( strcmp( pszType , "SingleCornerV" ) == 0 )		return FireType_SingleCornerV;


	return FireType_Single;
}

CFrameEventAttackBow::ArrowLockOnType CFrameEventAttackBow::Parse_LockOnType( const char * pszType )
{
	if( strcmp( pszType , "Off" ) == 0 )				return LockOnType_Off;
	if( strcmp( pszType , "Locked" ) == 0 )				return LockOnType_Locked;
	if( strcmp( pszType , "Bone" ) == 0 )				return LockOnType_Bone;
	if( strcmp( pszType , "Order" ) == 0 )				return LockOnType_Order;

	return LockOnType_Current;
}

CFrameEventAttackBow::ArrowFlyType	CFrameEventAttackBow::Parse_FlyType( const char * pszType )
{
	if( strcmp( pszType , "Guided" ) == 0 )				return FlyType_Guided;
	if( strcmp( pszType , "Ground" ) == 0 )				return FlyType_Ground;
	if( strcmp( pszType , "GroundGuided" ) == 0 )		return FlyType_GroundGuided;
	if( strcmp( pszType , "Bounce" ) == 0 )				return FlyType_Bounce;
	if( strcmp( pszType , "Circle" ) == 0 )				return FlyType_Circle;
	if( strcmp( pszType , "Wave" ) == 0 )				return FlyType_Wave;

	return FlyType_Normal;
}

CFrameEventAttackBow::ArrowHitType CFrameEventAttackBow::Parse_HitType( const char * pszType )
{
	if( strcmp( pszType , "Terrain" ) == 0 )			return HitType_Terrain;

	return HitType_All;
}

bool CFrameEventAttackBow::LoadXML( XMLNode *pXMLNode , List_PreloadString &lstPreloadEffect , List_PreloadString &lstPreloadSound , const char * pszClassName /*= NULL */ )
{
	if( !CFrameEventAttackNormal::LoadXML( pXMLNode , lstPreloadEffect , lstPreloadSound , pszClassName ? pszClassName : "C9FrameEventAttackBow" ) )
		return false;

	m_FrameEventCameraShake.LoadXML( pXMLNode , lstPreloadEffect , lstPreloadSound , pszClassName ? pszClassName : "C9FrameEventAttackBow" );

	string strAttr;

	if( pXMLNode->GetAttr( "TargetType" , strAttr ) )		m_TargetType = Parse_TargetType( strAttr.c_str() );
	if( pXMLNode->GetAttr( "FireType" , strAttr ) )			m_FireType = Parse_FireType( strAttr.c_str() );
	if( pXMLNode->GetAttr( "LockOnType" , strAttr ) )			m_LockOnType = Parse_LockOnType( strAttr.c_str() );
	if( pXMLNode->GetAttr( "FlyType" , strAttr ) )			m_FlyType = Parse_FlyType( strAttr.c_str() );
	if( pXMLNode->GetAttr( "HitType" , strAttr ) )			m_HitType = Parse_HitType( strAttr.c_str() );

	if( m_TargetType == TargetType_None )
	{
		if( pXMLNode->GetAttr( "FireType" , strAttr ) )
			m_TargetType = Convert_FireToTargetType( strAttr.c_str() );
		else
			m_TargetType = CFrameEventAttackBow::ArrowTargetType::TargetType_Normal;
	}

	// 이낭
	pXMLNode->GetAttrDWORD( "AbnormalType" , m_dwAbnType );
	pXMLNode->GetAttrDWORD( "AbnEffIndex" , m_dwAbnEffIndex );
	pXMLNode->GetAttrDWORD( "AbnormalKey" , m_dwAbnormalKey );
	pXMLNode->GetAttrBool( "IsEnemyInScreen" , m_bEnemyInScreen );

	pXMLNode->GetAttrBool( "Pierce" , m_bPierce );
	pXMLNode->GetAttrFloat( "PierceTerm" , m_fPierceTerm );
	if( m_fPierceTerm <= 0.1f )
	{
		// 피어싱 텀이 0이면 피어싱을 전혀 사용하지 않는다.
		m_bPierce = false;
	}
	pXMLNode->GetAttrFloat( "BouncingDistance" , m_fBouncingDistance );
	pXMLNode->GetAttrInt( "BouncingLimit" , m_iBouncingLimit );
	pXMLNode->GetAttrBool( "IsBounceBack" , m_bIsBouncingBack );
	pXMLNode->GetAttrBool( "IsNoTargetShotType" , m_bNoTargetShotType );

	pXMLNode->GetAttrFloat( "MinorAxis" , m_fMinorAxis );
	pXMLNode->GetAttrBool( "ScalingAxis" , m_bScalingAxis );

	pXMLNode->GetAttrFloat( "AttackSpeed" , m_fAttackSpeed );
	pXMLNode->GetAttrFloat( "AttackAccelerate" , m_fAttackAccelerate );
	if( pXMLNode->GetAttrFloat( "AttackHeight" , m_fAttackHeight ) )
		m_fAttackHeight *= 0.001f;

	pXMLNode->GetAttrFloat( "AttackRadius" , m_fAttackRadius );
	pXMLNode->GetAttrFloat( "ShotRange" , m_fShootRange );

	pXMLNode->GetAttrFloat( "TrailSize" , m_fTrailSize );
	pXMLNode->GetAttrInt( "TrailStep" , m_nTrailStep );
	pXMLNode->GetAttrHexDWORD( "TrailColor" , ( DWORD & )m_clrTrailColor.c );
	pXMLNode->GetAttrFloat( "TrailRenewInterval" , m_fTrailRenewInterval );
	pXMLNode->GetAttrBool( "TrailGlare" , m_bTrailGlare );

	int nRotateAngle = 0;
	if( pXMLNode->GetAttrInt( "RotateAngle" , nRotateAngle ) )
		m_nRotateAngle = ( INT16 )nRotateAngle;

	pXMLNode->GetAttrFloat( "RotationAdjustRate" , m_fDisAdjustRate4Rotate );
	pXMLNode->GetAttrBool( "CurveGuided" , m_bCurveGuided );

	if( pXMLNode->GetAttr( "BowEffectFile" , m_strBowEffectFile ) && m_strBowEffectFile.empty() == false )						lstPreloadEffect.AddStringLower( m_strBowEffectFile.c_str() );
	if( pXMLNode->GetAttr( "EndEffectFile" , m_strEndEffectFile ) && m_strEndEffectFile.empty() == false )						lstPreloadEffect.AddStringLower( m_strEndEffectFile.c_str() );
	if( pXMLNode->GetAttr( "BowFixedEffectFile" , m_strBowFixedEffectFile ) && m_strBowFixedEffectFile.empty() == false )		lstPreloadEffect.AddStringLower( m_strBowFixedEffectFile.c_str() );
	if( pXMLNode->GetAttr( "BowBreakEffectFile" , m_strBowBreakEffectFile ) && m_strBowBreakEffectFile.empty() == false )		lstPreloadEffect.AddStringLower( m_strBowBreakEffectFile.c_str() );
	pXMLNode->GetAttrBool( "EffectDistCheck" , m_bEffectDistCheck );

	pXMLNode->GetAttrFloat( "EffectScale" , m_fEffectScale );					if( m_fEffectScale <= 0.0f )			m_fEffectScale = 1.0f;
	pXMLNode->GetAttrFloat( "BowEffectScale" , m_fBowEffectScale );				if( m_fBowEffectScale <= 0.0f )			m_fBowEffectScale = 1.0f;
	pXMLNode->GetAttrFloat( "EndEffectScale" , m_fEndEffectScale );				if( m_fEndEffectScale <= 0.0f )			m_fEndEffectScale = 1.0f;
	pXMLNode->GetAttrFloat( "BowFixedEffectScale" , m_fBowFixedEffectScale );	if( m_fBowFixedEffectScale <= 0.0f )	m_fBowFixedEffectScale = 1.0f;
	pXMLNode->GetAttrFloat( "BowBreakEffectScale" , m_fBowBreakEffectScale );	if( m_fBowBreakEffectScale <= 0.0f )	m_fBowBreakEffectScale = 1.0f;
	pXMLNode->GetAttrFloat( "BowFixedDeep" , m_fBowFixedDeep );

	pXMLNode->GetAttrInt( "RayCount" , m_nRay );
	pXMLNode->GetAttrInt( "MaxRayCount" , m_nMaxRay );

	if( m_nRay > m_nMaxRay )
		m_nMaxRay = m_nRay;

	int nBounceAngle , nSpreadAngle , nTargetCheckAngle , nVerticalAngle , nRandomAngle = 0;

	if( pXMLNode->GetAttrInt( "RandomAngle" , nRandomAngle ) )
	{
		m_nSpreadAngle = ( INT16 )nRandomAngle;
		m_nTargetCheckAngle = ( INT16 )nRandomAngle;
	}
	else
	{
		if( m_FireType == FireType_SingleCorner || m_FireType == FireType_SingleCornerV )
			m_nSpreadAngle = 0;
	}

	if( pXMLNode->GetAttrInt( "SpreadAngle" , nSpreadAngle ) )
	{
		m_nSpreadAngle = ( INT16 )nSpreadAngle;
	}
	if( pXMLNode->GetAttrInt( "TargetCheckAngle" , nTargetCheckAngle ) )
	{
		m_nTargetCheckAngle = ( INT16 )nTargetCheckAngle;
	}

	if( pXMLNode->GetAttrInt( "BounceAngle" , nBounceAngle ) )
	{
		m_nBounceAngle = ( INT16 )nBounceAngle;
	}


	pXMLNode->GetAttr( "FireBoneName" , m_strBowFireBoneName );
	if( pXMLNode->GetAttrInt( "VerticalAngle" , nVerticalAngle ) )
		m_nVerticalAngle = ( INT16 )nVerticalAngle;

	pXMLNode->GetAttrFloat( "StartLeg" , m_fFireDist );

	string strAxis;
	if( pXMLNode->GetAttr( "FireAxis" , strAxis ) && strAxis.empty() == false )
		sscanf_s( strAxis.c_str() , "%f %f %f" , &m_vecFireAxis.x , &m_vecFireAxis.y , &m_vecFireAxis.z );

	// 변수
	LoadDataVarList( pXMLNode->GetAttr( "AddAttackSpeed" ).c_str() , m_AddAttackSpeed );
	LoadDataVarList( pXMLNode->GetAttr( "AddAttackRange" ).c_str() , m_AddAttackRange );
	LoadDataVarList( pXMLNode->GetAttr( "AddShootRange" ).c_str() , m_AddShootRange );

	//serverManagedProj 타입 결정
#ifndef _C9_PROJECTILE_MANAGEMETHOD_RENEWAL_
	DetermineServerManagedType();
#endif

	pXMLNode->GetAttrFloat( "WaveFrequency" , m_fWaveFrequncy );
	pXMLNode->GetAttrFloat( "WaveMagnitude" , m_fWaveMagnitude );
	pXMLNode->GetAttrInt( "WaveAngle" , m_iAngle );

	return true;
}

void CFrameEventAttackBow::Dump( C9File * pFile , List_PreloadString & lstPreloadEffect , List_PreloadString &lstPreloadSound )
{
	CFrameEventAttackNormal::Dump( pFile , lstPreloadEffect , lstPreloadSound );

	m_FrameEventCameraShake.Dump( pFile , lstPreloadEffect , lstPreloadSound );

	DumpDataVarList( pFile , m_AddAttackSpeed );
	DumpDataVarList( pFile , m_AddAttackRange );
	DumpDataVarList( pFile , m_AddShootRange );

	static const size_t _sizeOfData = C9_SIZE_OF_BETWEEN_VALUE( m_TargetType , m_bIsBouncingBack );

	if( pFile->IsSave() )
	{
		pFile->WriteData( m_strBowFireBoneName );
		pFile->WriteData( m_strBowEffectFile );
		pFile->WriteData( m_strBowFixedEffectFile );
		pFile->WriteData( m_strBowBreakEffectFile );
		pFile->WriteData( m_strEndEffectFile );

		pFile->WriteData_SizeT( &m_TargetType , _sizeOfData );
	}
	else
	{
		pFile->ReadData( m_strBowFireBoneName );
		pFile->ReadData( m_strBowEffectFile );
		pFile->ReadData( m_strBowFixedEffectFile );
		pFile->ReadData( m_strBowBreakEffectFile );
		pFile->ReadData( m_strEndEffectFile );

		pFile->ReadData_SizeT( &m_TargetType , _sizeOfData );


		if( !m_strBowEffectFile.empty() )			lstPreloadEffect.AddStringLower( m_strBowEffectFile.c_str() );
		if( !m_strBowFixedEffectFile.empty() )		lstPreloadEffect.AddStringLower( m_strBowFixedEffectFile.c_str() );
		if( !m_strBowBreakEffectFile.empty() )		lstPreloadEffect.AddStringLower( m_strBowBreakEffectFile.c_str() );
		if( !m_strEndEffectFile.empty() )			lstPreloadEffect.AddStringLower( m_strEndEffectFile.c_str() );

		DetermineServerManagedType();
	}
}

void CFrameEventAttackBow::LoadXMLCopyActionValue( XMLNode *pXMLNode )
{
#ifndef _GAME_RELEASE_

	if( m_iCopyCount > 1 )
	{
		pXMLNode->GetAttrFloat( "CopyAddShotRange" , m_CopyActionValueBow.m_fShotRange );
		pXMLNode->GetAttrFloat( "CopyAddAttackSpeed" , m_CopyActionValueBow.m_fAttackSpeed );
		pXMLNode->GetAttrFloat( "CopyAddAttackRadius" , m_CopyActionValueBow.m_fAttackRadius );
		pXMLNode->GetAttrFloat( "CopyAddEffectScale" , m_CopyActionValueBow.m_fEffectScale );
		pXMLNode->GetAttrFloat( "CopyAddBowEffectScale" , m_CopyActionValueBow.m_fBowEffectScale );
		pXMLNode->GetAttrFloat( "CopyAddEndEffectScale" , m_CopyActionValueBow.m_fEndEffectScale );
		pXMLNode->GetAttrFloat( "CopyAddRayCount" , m_CopyActionValueBow.m_fRayCount );
		
		int nTemp = 0;
		float fRandomAngleTemp = 0;

		if( pXMLNode->GetAttrFloat( "CopyAddRandomAngle" , fRandomAngleTemp ) )
		{
			m_CopyActionValueBow.m_nSpreadAngle = ( INT16 )fRandomAngleTemp;
			m_CopyActionValueBow.m_nTargetCheckAngle = ( INT16 )fRandomAngleTemp;
		}

		if( pXMLNode->GetAttrInt( "CopyAddSpreadAngle" , nTemp ) )
			m_CopyActionValueBow.m_nSpreadAngle = ( INT16 )nTemp;
		if( pXMLNode->GetAttrInt( "CopyAddTargetCheckAngle" , nTemp ) )
			m_CopyActionValueBow.m_nTargetCheckAngle = ( INT16 )nTemp;


	}
#endif
}

void CFrameEventAttackBow::CopyActionValue( CFrameEvent *pFrameEvent , int iLevel )
{
#ifndef _GAME_RELEASE_

	//#if defined _PERFORMANCE_BUILD_ || defined _DEBUG 
	__super::CopyActionValue( pFrameEvent , iLevel );


	CFrameEventAttackBow *pCopyFrame = ( CFrameEventAttackBow * )pFrameEvent;

	if( m_iCopyCount > 1 && iLevel > 0 )
	{
		m_fShootRange		+= ( m_CopyActionValueBow.m_fShotRange * ( float )iLevel );
		m_fAttackSpeed		+= ( m_CopyActionValueBow.m_fAttackSpeed * ( float )iLevel );
		m_fAttackRadius		+= ( int )( m_CopyActionValueBow.m_fAttackRadius * ( float )iLevel );
		m_fEffectScale		+= ( m_CopyActionValueBow.m_fEffectScale * ( float )iLevel );
		m_fBowEffectScale	+= ( m_CopyActionValueBow.m_fBowEffectScale * ( float )iLevel );
		m_fEndEffectScale	+= ( m_CopyActionValueBow.m_fEndEffectScale * ( float )iLevel );
		m_nRay				+= ( int )( m_CopyActionValueBow.m_fRayCount * ( float )iLevel );
		m_nSpreadAngle		+= ( int )( m_CopyActionValueBow.m_nSpreadAngle * ( float )iLevel );
		m_nTargetCheckAngle += ( int )( m_CopyActionValueBow.m_nTargetCheckAngle * ( float )iLevel );

	}
#endif
}

bool CFrameEventAttackBow::DetermineServerManagedType()
{
	// 필요에 따라 코드 변경 및 추가할 것
	if( this->m_FlyType == ArrowFlyType::FlyType_Bounce )
	{
		m_ServerManagedType = ServerManagedProjectileType_Bounce;
		return true;
	}

	m_ServerManagedType = ServerManagedProjectileType_None;

	return false;
}


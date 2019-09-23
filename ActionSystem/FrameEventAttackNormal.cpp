#include "stdafx.h"
#include "FrameEventAttackNormal.h"


//////////////////////////////////////////////////////////////////////////
bool CFrameEventAttackNormal::LoadXML( XMLNode *pXMLNode , List_PreloadString &lstPreloadEffect , List_PreloadString &lstPreloadSound , const char * pszClassName /*= NULL */ )
{
	if( !CFrameEvent::LoadXML( pXMLNode , lstPreloadEffect , lstPreloadSound , pszClassName ? pszClassName : "C9FrameEventAttackNormal" ) )
		return false;

	CFrameEventAttackNormal::LoadXMLCopyActionValue( pXMLNode );

	string strAttr;
	if( pXMLNode->GetAttr( "AttackDirection" , strAttr ) )		m_DamageDirection = ::StringToActionDamageDirection( strAttr.c_str() );
	if( pXMLNode->GetAttr( "AttackType" , strAttr ) )				m_AttackType = ::StringToActionAttackType( strAttr.c_str() );

	pXMLNode->GetAttrBool( "AllFrame" , m_bCheckAllFrame );
	pXMLNode->GetAttrFloat( "AttackRange" , m_fAttackRange );
	pXMLNode->GetAttrFloat( "AttackNormalHeight" , m_fAttackNormalHeight );

	if( pXMLNode->GetAttr( "UseAttackItemType" , strAttr ) )	m_UseAttackItemType = ::StringToHandType( strAttr.c_str() );

	if( pXMLNode->GetAttrFloat( "AttackHeightRate" , m_fAttackHeightRate ) )
		m_fAttackHeightRate *= 0.01f;

	pXMLNode->GetAttrUINT( "CatchIndex" , m_nCatchIndex );
	pXMLNode->GetAttrBool( "AttackTypeForceExecute" , m_bAttackTypeForceExecute );
	pXMLNode->GetAttrBool( "CatchTypeHold" , m_bCatchTypeHold );

	if( pXMLNode->GetAttr( "AttackPosOffset" , strAttr ) )
		sscanf_s( strAttr.c_str() , "%f %f %f" , &m_vecAttackPositionOffset.x , &m_vecAttackPositionOffset.y , &m_vecAttackPositionOffset.z );

	pXMLNode->GetAttrBool( "PositiveHeightOnly" , m_bPositiveHeightOnly );

	bool bIsRangeScalingApply = true;
	if( !pXMLNode->GetAttrBool( "AttackRangeScale" , bIsRangeScalingApply ) )
		bIsRangeScalingApply = true;

	bool bIsHeightScalingApply = true;
	if( !pXMLNode->GetAttrBool( "AttackHeightScale" , bIsHeightScalingApply ) )
		bIsHeightScalingApply = true;

	int iScaledFlagTemp = 0;

	if( !bIsRangeScalingApply )
		iScaledFlagTemp |= 1 << CFrameEventAttackNormal::RANGESCALE_PREVENT_RANGE;

	if( !bIsHeightScalingApply )
		iScaledFlagTemp |= 1 << CFrameEventAttackNormal::RANGESCALE_PREVENT_HEIGHT;

	m_nScaleRatePrevent = iScaledFlagTemp;

	pXMLNode->GetAttrBool( "IgnoreDefence" , m_bIgnoreDefence );

	if( m_AttackEffect.LoadXML( pXMLNode ) == false )
		return false;

	m_AttackValue.LoadXML( pXMLNode , m_AttackType );

	return true;
}

void CFrameEventAttackNormal::Dump( C9File * pFile , List_PreloadString & lstPreloadEffect , List_PreloadString &lstPreloadSound )
{
	CFrameEvent::Dump( pFile , lstPreloadEffect , lstPreloadSound );

	m_AttackEffect.Dump( pFile );
	m_AttackValue.Dump( pFile );

	static const size_t _sizeOfData = C9_SIZE_OF_BETWEEN_VALUE( m_DamageDirection , m_bCheckAllFrame );

	if( pFile->IsSave() )
	{
		pFile->WriteData_SizeT( &m_DamageDirection , _sizeOfData );
	}
	else
	{
		pFile->ReadData_SizeT( &m_DamageDirection , _sizeOfData );
	}
}

void CFrameEventAttackNormal::LoadXMLCopyActionValue( XMLNode *pXMLNode )
{
#ifndef _GAME_RELEASE_

	if( m_iCopyCount > 1 )
	{
		pXMLNode->GetAttrFloat( "CopyAddAttackRange" , m_CopyActionValue.m_fAttackRange );
		pXMLNode->GetAttrFloat( "CopyAddDefenseCrashRate" , m_CopyActionValue.m_fDefenseCrashRate );
		string strAttr;
		if( pXMLNode->GetAttr( "CopyAddEffectScale" , strAttr ) )
			sscanf_s( strAttr.c_str() , "%f %f %f" , &m_CopyActionValue.m_vecEffectScale.x , &m_CopyActionValue.m_vecEffectScale.y , &m_CopyActionValue.m_vecEffectScale.z );
		pXMLNode->GetAttrFloat( "CopyAddAttackDamageVelocity" , m_CopyActionValue.m_fAttackDamageVelocity );
		pXMLNode->GetAttrFloat( "CopyAddAttackFlyFinalHeight" , m_CopyActionValue.m_fAttackFlyFinalHeight );
		pXMLNode->GetAttrFloat( "CopyAddAttackFloatTime" , m_CopyActionValue.m_fAttackFloatTime );
		pXMLNode->GetAttrFloat( "CopyAddFAttackDamageVelocity" , m_CopyActionValue.m_fFAttackDamageVelocity );
		pXMLNode->GetAttrFloat( "CopyAddFAttackFlyFinalHeight" , m_CopyActionValue.m_fFAttackFlyFinalHeight );
		pXMLNode->GetAttrFloat( "CopyAddFAttackFloatTime" , m_CopyActionValue.m_fFAttackFloatTime );
	}

#endif
}

void CFrameEventAttackNormal::CopyActionValue( CFrameEvent *pFrameEvent , int iLevel )
{
#ifndef _GAME_RELEASE_
	__super::CopyActionValue( pFrameEvent , iLevel );
	CFrameEventAttackNormal *pCopyFrame = ( CFrameEventAttackNormal * )pFrameEvent;

	if( m_iCopyCount > 1 && iLevel > 0 )
	{
		m_fAttackRange += ( m_CopyActionValue.m_fAttackRange * ( float )iLevel );
		m_AttackValue.m_fDefenseCrashRate += ( m_CopyActionValue.m_fDefenseCrashRate * ( float )iLevel );
		m_AttackEffect.m_vecEffectScale.x += ( m_CopyActionValue.m_vecEffectScale.x * ( float )iLevel );
		m_AttackEffect.m_vecEffectScale.y += ( m_CopyActionValue.m_vecEffectScale.y * ( float )iLevel );
		m_AttackEffect.m_vecEffectScale.z += ( m_CopyActionValue.m_vecEffectScale.z * ( float )iLevel );
		m_AttackValue.m_fAttackDamageVelocity += ( m_CopyActionValue.m_fAttackDamageVelocity * ( float )iLevel );
		m_AttackValue.m_fAttackFlyFinalHeight += ( m_CopyActionValue.m_fAttackFlyFinalHeight * ( float )iLevel );
		m_AttackValue.m_fAttackFloatTime += ( m_CopyActionValue.m_fAttackFloatTime * ( float )iLevel );
		m_AttackValue.m_fFlyAttackDamageVelocity += ( m_CopyActionValue.m_fFAttackDamageVelocity * ( float )iLevel );
		m_AttackValue.m_fFlyAttackFlyFinalHeight += ( m_CopyActionValue.m_fFAttackFlyFinalHeight * ( float )iLevel );
		m_AttackValue.m_fFlyAttackFloatTime += ( m_CopyActionValue.m_fFAttackFloatTime * ( float )iLevel );
	}

#endif
}

void CFrameEventAttackNormal::LoadSkillKey( string& strAttr , int& iUseMonsterSkillIdx , DWORD& dwSkillKey )
{
	iUseMonsterSkillIdx = 0; dwSkillKey = 0;
	// 스킬인덱스가 16이 넘어가지 않는다는 가정하에 3번째 비트(16진수로)에 
	// 몬스터인지 펫인지를 지정하게한다.

	if( strAttr.find( "MonsterSkillKey" ) != string::npos )
	{
		size_t idx = strlen( "MonsterSkillKey" );
		iUseMonsterSkillIdx = atoi( &strAttr[idx] );
		// 몬스터스킬은 0 < x < 5
		if( iUseMonsterSkillIdx > 0 && iUseMonsterSkillIdx < 5 )
			iUseMonsterSkillIdx |= SKILL_USE_MONSTER;
		else
			iUseMonsterSkillIdx = 0;
	}
	// 펫 관련 스킬 인덱스 추가 
	else if( strAttr.find( "PetSkillKey" ) != string::npos )
	{
		size_t idx = strlen( "PetSkillKey" );
		iUseMonsterSkillIdx = atoi( &strAttr[idx] );

		if( iUseMonsterSkillIdx > 0 )
			iUseMonsterSkillIdx |= SKILL_USE_PET;
		else
			iUseMonsterSkillIdx = 0;
	}
	else
	{
		dwSkillKey = ( DWORD )atoi( strAttr.c_str() );
	}
}

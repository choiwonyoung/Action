#include "stdafx.h"
#include "ActionDataInfo.h"
#include "FrameEvent.h"
#include "FrameEventEffect.h"

void CActionFileMeshInfo::Dump( C9File * pFile )
{
	static const size_t sizeOfData = C9_SIZE_OF_BETWEEN_VALUE( m_nSlotIndex , m_nMiddleCategory );

	if( pFile->IsSave() )
	{
		pFile->WriteData( m_strMeshFile );
		pFile->WriteData( m_strTextureFile );

		pFile->WriteData_SizeT( &m_nSlotIndex , sizeOfData );
	}
	else
	{
		pFile->ReadData( m_strMeshFile );
		pFile->ReadData( m_strTextureFile );

		pFile->ReadData_SizeT( &m_nSlotIndex , sizeOfData );
	}
}


void CChangeTextureInfo::Dump( C9File * pFile )
{
	static const size_t sizeOfData = C9_SIZE_OF_BETWEEN_VALUE( m_nMeshSlotIndex , m_nTextureIndex );

	if( pFile->IsSave() )
	{
		pFile->WriteData( m_strTextureName );

		pFile->WriteData_SizeT( &m_nMeshSlotIndex , sizeOfData );
	}
	else
	{
		pFile->ReadData( m_strTextureName );

		pFile->ReadData_SizeT( &m_nMeshSlotIndex , sizeOfData );
	}
}

void CCustomScaleBoneInfo::Dump( C9File * pFile )
{
	if( pFile->IsSave() )
	{
		pFile->WriteData( dwBoneHashCode );
		pFile->WriteData( &vecSize , sizeof( vector3 ) );
	}
	else
	{
		pFile->ReadData( dwBoneHashCode );
		pFile->ReadData( &vecSize , sizeof( vector3 ) );
	}
}


void C9CatchBoneInfo::Dump( C9File * pFile )
{
	static const size_t sizeOfData = C9_SIZE_OF_BETWEEN_VALUE( vecAngle , vecPos );

	if( pFile->IsSave() )
	{
		pFile->WriteData( strName );

		pFile->WriteData_SizeT( &vecAngle , sizeOfData );
	}
	else
	{
		pFile->ReadData( strName );

		pFile->ReadData_SizeT( &vecAngle , sizeOfData );
	}
}


//////////////////////////////////////////////////////////////////////////
void CActionDataInfo::LoadXmlActionIndex( XMLNode * pXMLNode , vector< DWORD > & lstActionIndexHashCode )
{
	string strAttr;

	if( pXMLNode->GetAttr( "ActionIndex" , strAttr ) && strAttr.empty() == false )
	{
		char * pNextToken = NULL;
		char * pToken = strtok_s( &strAttr[0] , " " , &pNextToken );
		while( pToken != NULL )
		{
			lstActionIndexHashCode.push_back( CCrc32Static::StringCrc32( pToken ) );
			pToken = strtok_s( NULL , " " , &pNextToken );
		}
	}
}

void CActionDataInfo::DumpActionIndex( C9File * pFile , vector< DWORD > & lstActionIndexHashCode )
{
	if( pFile->IsSave() )
	{
		const size_t actionIndexHashCodeCount = lstActionIndexHashCode.size();
		pFile->WriteData_SizeT( actionIndexHashCodeCount );
		if( actionIndexHashCodeCount > 0 )
			pFile->WriteData_SizeT( &lstActionIndexHashCode[0] , sizeof( DWORD ) * actionIndexHashCodeCount );
	}
	else
	{
		size_t actionIndexHashCodeCount = 0;	pFile->ReadData_SizeT( actionIndexHashCodeCount );
		lstActionIndexHashCode.resize( actionIndexHashCodeCount );
		if( actionIndexHashCodeCount > 0 )
			pFile->ReadData_SizeT( &lstActionIndexHashCode[0] , sizeof( DWORD ) * actionIndexHashCodeCount );
	}
}

CActionDataInfo::CActionDataInfo()
: m_fAnimationSpeed( 1.0f )
, m_fAddRenderDistance( 0.0f )
, m_fObstacleThickness( 40.0f )
, m_fSoundMinDistance( _SOUND_DEFAULT_MINDISTANCE_ )
, m_fSoundMaxDistance( _SOUND_DEFAULT_MAXDISTANCE_ )

, m_iShowHpNum( 5 )
, m_iSuperArmorValue( 0 )
, m_bUseStanceMode2( false )

, m_fCatchHeight( 0.0f )
, m_fCatchCameraDistance( 0.0f )
, m_fOutlineThickness( 0.0f )
, m_fTurnRatio1( 0.2f )
, m_fTurnRatio2( 0.3f )
, m_bCurvedPath( false )

, m_bNotUnloadCharacterSecene( false )
, m_bPreloadCharacterSecene( false )
, m_bAlwaysRenderSelfShadow( false )
, m_bAlwaysRenderShadow( false )
, m_bDisableRenderSelfShadow( false )
, m_bDisableBoneLOD( false )
, m_bJumpAble( false )
, m_bWallRideAble( false )
, m_bPitchRotateAble( false )
, m_bInvincible( false )
, m_bShowName( true )
, m_bShowHp( true )
, m_bShowMp( false )
, m_bInsight( true )
, m_bShowEventHp( false )
, m_bShowCross( false )
, m_bNoteOnMinimap( true )
, m_bGenerateObstacle( false )
, m_bNoAiAgent( false )
, m_bNoNxController( false )
, m_bMoveRigidBody( false )
, m_bPositionFix( false )
, m_bNoDamageFrameDelay( false )
, m_bExcludeTargeting( false )
, m_bIsBigMonster( false )
, m_bIsAlwaysAnimated( false )
, m_bDeadRemain( false )
, m_bDeadEffect( true )
, m_bIsShowAutoOutline( true )
, m_lstActionIndexHashCode()

, m_strActiveWeaponType( "" )
, m_strAnimationPack( "" )

, m_strBoneName( "" )
, m_strCenterBoneName( "" )
, m_lstCustomScaleBoneInfo()
, m_lstMeshData()
, m_lstSiegeMeshData()

, m_lstMeshTypeInfo()

, m_lstChangeTextureData()

, m_lstCatchBoneInfo()

, m_lstHoldMeBoneName()
{
}


CActionDataInfo::~CActionDataInfo()
{
}

bool CActionDataInfo::LoadXML( XMLNode * pActionDataNode , List_PreloadString &lstPreloadEffect , List_PreloadString &lstPreloadSound )
{
	string strAttr;

	_LoadXML_BaseInfo( pActionDataNode );


	if( _LoadXNL_BoneInfo( pActionDataNode ) == false )
		return false;

	if( _LoadXML_BoneScaleInfo( pActionDataNode , strAttr ) == false )
		return false;

	if( _LoadXML_AnimationInfo( pActionDataNode ) == false )
		return false;

	// 기본 메쉬-------------
	_LoadXML_MeshInfo( pActionDataNode );

	// 공성용 메쉬-------------
	_LoadXML_MeshSiegeInfo( pActionDataNode );

	// 변경할 Texture -------------
	_LoadXML_ChangeTexture( pActionDataNode );

	// 잡기 본 List ----------------
	_LoadXML_CatchBoneInfo( pActionDataNode , strAttr );

	// 잡힐 본 List ----------------
	_LoadXML_HoldBone( pActionDataNode );

	// C9 파티클 지속 리스트 --------------------------------------------------------------------------------------
	_LoadXML_PreloadParticle( pActionDataNode , lstPreloadEffect , lstPreloadSound );
	
	return true;
}



void CActionDataInfo::Dump( C9File *pFile , List_PreloadString &lstPreloadEffect , List_PreloadString &lstPreloadSound )
{
	static const size_t sizeOfData = C9_SIZE_OF_BETWEEN_VALUE( m_fAnimationSpeed , m_bIsShowAutoOutline );

	CActionDataInfo::DumpActionIndex( pFile , m_lstActionIndexHashCode );

	if( pFile->IsSave() )			// 저장
	{
		pFile->WriteData_SizeT( &m_fAnimationSpeed , sizeOfData );

		pFile->WriteData( m_strActiveWeaponType );
		pFile->WriteData( m_strAnimationPack );
		pFile->WriteData( m_strBoneName );
		pFile->WriteData( m_strCenterBoneName );

		// 본 스케일
		_Dump_SaveBoneScale( pFile );

		// 메쉬
		_Dump_SaveMeshData( pFile );

		// 공성용 메쉬
		_Dump_SaveSiegeMeshData( pFile );

		// 변경할 Texture
		_Dump_SaveChangeTextureData( pFile );

		// 잡기 본
		_Dump_SaveCatchBoneData( pFile );

		// 잡힐 본
		_Dump_SaveHoldBoneData( pFile );

		// C9 파티클 지속 리스트 --------------------------------------------------------------------------------------
		_Dump_SaveBaseParticleName( pFile , lstPreloadEffect , lstPreloadSound );
	}
	else
	{
		pFile->ReadData_SizeT( &m_fAnimationSpeed , sizeOfData );

		pFile->ReadData( m_strActiveWeaponType );
		pFile->ReadData( m_strAnimationPack );
		pFile->ReadData( m_strBoneName );
		pFile->ReadData( m_strCenterBoneName );
				
		// 본 스케일
		_Dump_LoadBoneScaleData( pFile );

		// 메쉬
		_Dump_LoadMeshData( pFile );

		// 공성용 메쉬
		_Dump_LoadSiegeMeshData( pFile );

		// 변경할 Texture
		_Dump_LoadChangeTextureData( pFile );

		// 잡기 본
		_Dump_LoadCatchBoneData( pFile );

		// 잡힐 본
		_Dump_LoadHoldBoneData( pFile );

		// C9 파티클 지속 리스트
		_Dump_LoadBaseParticleName( pFile , lstPreloadEffect , lstPreloadSound );	
	}
}

void CActionDataInfo::_Dump_LoadBaseParticleName( C9File * pFile , List_PreloadString & lstPreloadEffect , List_PreloadString & lstPreloadSound )
{
	size_t _szBaseParticle = 0;		pFile->ReadData_SizeT( _szBaseParticle );
	m_lstBaseC9ParticleName.resize( _szBaseParticle );
	for( size_t cParticle = 0; cParticle < _szBaseParticle; ++cParticle )
	{
		CFrameEventEffect & kBaseC9Particle = m_lstBaseC9ParticleName[cParticle];
		kBaseC9Particle.Dump( pFile , lstPreloadEffect , lstPreloadSound );
		pFile->ReadData( ( int & )kBaseC9Particle.m_eCommandState );
	}
}

void CActionDataInfo::_Dump_LoadHoldBoneData( C9File * pFile )
{
	size_t _szHoldMeBoneName = 0;	pFile->ReadData_SizeT( _szHoldMeBoneName );
	m_lstHoldMeBoneName.resize( _szHoldMeBoneName );
	for( size_t cHoldMeBone = 0; cHoldMeBone < _szHoldMeBoneName; ++cHoldMeBone )
		pFile->ReadData( m_lstHoldMeBoneName[cHoldMeBone] );
}

void CActionDataInfo::_Dump_LoadCatchBoneData( C9File * pFile )
{
	size_t _szCatchBone = 0;	pFile->ReadData_SizeT( _szCatchBone );
	m_lstCatchBoneInfo.resize( _szCatchBone );
	for( size_t cCatchBone = 0; cCatchBone < _szCatchBone; ++cCatchBone )
		m_lstCatchBoneInfo[cCatchBone].Dump( pFile );
}

void CActionDataInfo::_Dump_LoadChangeTextureData( C9File * pFile )
{
	size_t _szChangeTextureData = 0;	pFile->ReadData_SizeT( _szChangeTextureData );
	m_lstChangeTextureData.resize( _szChangeTextureData );
	for( size_t cTexture = 0; cTexture < _szChangeTextureData; ++cTexture )
		m_lstChangeTextureData[cTexture].Dump( pFile );
}

void CActionDataInfo::_Dump_LoadSiegeMeshData( C9File * pFile )
{
	size_t _szSiegeMeshData = 0;	pFile->ReadData_SizeT( _szSiegeMeshData );
	m_lstSiegeMeshData.resize( _szSiegeMeshData );
	for( size_t cMesh = 0; cMesh < _szSiegeMeshData; ++cMesh )
		m_lstSiegeMeshData[cMesh].Dump( pFile );
}

void CActionDataInfo::_Dump_LoadMeshData( C9File * pFile )
{
	size_t uiMeshCount = 0;	pFile->ReadData_SizeT( uiMeshCount );
	if( uiMeshCount > 0 )
	{
		hash_map<DWORD , CActionFileMeshInfo>	hash_mapResTypeInfo;
		for( size_t cMesh = 0; cMesh < uiMeshCount; ++cMesh )
		{
			CActionFileMeshInfo	meshData;
			DWORD					dwMeshTypeInfo;

			pFile->ReadData( dwMeshTypeInfo );
			meshData.Dump( pFile );


			if( dwMeshTypeInfo == 0 )
				m_lstMeshData.push_back( meshData );
		}

		for( hash_map<DWORD , CActionFileMeshInfo>::iterator pos = hash_mapResTypeInfo.begin(); pos != hash_mapResTypeInfo.end(); ++pos )
		{
			m_lstMeshData.push_back( pos->second );
		}
	}
}

void CActionDataInfo::_Dump_LoadBoneScaleData( C9File * pFile )
{
	size_t _szCustomScaleBone = 0;	pFile->ReadData_SizeT( _szCustomScaleBone );
	m_lstCustomScaleBoneInfo.resize( _szCustomScaleBone );
	for( size_t cBoneScale = 0; cBoneScale < _szCustomScaleBone; ++cBoneScale )
		m_lstCustomScaleBoneInfo[cBoneScale].Dump( pFile );
}

void CActionDataInfo::_Dump_SaveBaseParticleName( C9File * pFile , List_PreloadString & lstPreloadEffect , List_PreloadString & lstPreloadSound )
{
	const size_t _szBaseParticle = m_lstBaseC9ParticleName.size();	pFile->WriteData_SizeT( _szBaseParticle );
	for( size_t cParticle = 0; cParticle < _szBaseParticle; ++cParticle )
	{
		CFrameEventEffect & kBaseC9Particle = m_lstBaseC9ParticleName[cParticle];
		kBaseC9Particle.Dump( pFile , lstPreloadEffect , lstPreloadSound );
		pFile->WriteData( ( int )kBaseC9Particle.m_eCommandState );
	}
}

void CActionDataInfo::_Dump_SaveHoldBoneData( C9File * pFile )
{
	const size_t _szHoldMeBoneName = m_lstHoldMeBoneName.size();	pFile->WriteData_SizeT( _szHoldMeBoneName );
	for( size_t cHoldMeBone = 0; cHoldMeBone < _szHoldMeBoneName; ++cHoldMeBone )
		pFile->WriteData( m_lstHoldMeBoneName[cHoldMeBone] );
}

void CActionDataInfo::_Dump_SaveCatchBoneData( C9File * pFile )
{
	const size_t _szCatchBone = m_lstCatchBoneInfo.size();	pFile->WriteData_SizeT( _szCatchBone );
	for( size_t cCatchBone = 0; cCatchBone < _szCatchBone; ++cCatchBone )
		m_lstCatchBoneInfo[cCatchBone].Dump( pFile );
}

void CActionDataInfo::_Dump_SaveChangeTextureData( C9File * pFile )
{
	const size_t _szChangeTextureData = m_lstChangeTextureData.size();	pFile->WriteData_SizeT( _szChangeTextureData );
	for( size_t cTexture = 0; cTexture < _szChangeTextureData; ++cTexture )
		m_lstChangeTextureData[cTexture].Dump( pFile );
}

void CActionDataInfo::_Dump_SaveSiegeMeshData( C9File * pFile )
{
	const size_t _szSiegeMeshData = m_lstSiegeMeshData.size();	pFile->WriteData_SizeT( _szSiegeMeshData );
	for( size_t cMesh = 0; cMesh < _szSiegeMeshData; ++cMesh )
		m_lstSiegeMeshData[cMesh].Dump( pFile );
}

void CActionDataInfo::_Dump_SaveMeshData( C9File * pFile )
{
	const size_t _szMeshTypeInfo = m_lstMeshData.size();	pFile->WriteData_SizeT( _szMeshTypeInfo );
	for( size_t cMesh = 0; cMesh < _szMeshTypeInfo; ++cMesh )
	{
		pFile->WriteData( m_lstMeshTypeInfo[cMesh] );
		m_lstMeshData[cMesh].Dump( pFile );
	}
}

void CActionDataInfo::_Dump_SaveBoneScale( C9File * pFile )
{
	const size_t _szCustomScaleBone = m_lstCustomScaleBoneInfo.size();	pFile->WriteData_SizeT( _szCustomScaleBone );
	for( size_t cBoneScale = 0; cBoneScale < _szCustomScaleBone; ++cBoneScale )
		m_lstCustomScaleBoneInfo[cBoneScale].Dump( pFile );
}

void CActionDataInfo::_LoadXML_PreloadParticle( XMLNode * pActionDataNode , List_PreloadString & lstPreloadEffect , List_PreloadString & lstPreloadSound )
{
	XMLNodes particleNodes = pActionDataNode->GetChilds( "PreC9ParticleLoad" );
	for( UINT cParticle = 0; cParticle < particleNodes.size(); ++cParticle )
	{
		XMLNode * pParticleNode = particleNodes[cParticle];
		CFrameEventEffect kBaseC9Particle;

		kBaseC9Particle.LoadXML( pParticleNode , lstPreloadEffect , lstPreloadSound , "PreC9ParticleLoad" );
		string strControlState;
		pParticleNode->GetAttr( "ControlState" , strControlState );

		if( strControlState == "STOP" )
			kBaseC9Particle.m_eCommandState = EFF_CMD_STOP;
		else if( strControlState == "DIE" )
			kBaseC9Particle.m_eCommandState = EFF_CMD_DIE;
		else
			kBaseC9Particle.m_eCommandState = EFF_CMD_START;

		m_lstBaseC9ParticleName.push_back( kBaseC9Particle );
	}
}

void CActionDataInfo::_LoadXML_HoldBone( XMLNode * pActionDataNode )
{
	XMLNodes HoldMeBoneNodes = pActionDataNode->GetChilds( "HoldMeBone" );

	m_lstHoldMeBoneName.push_back( "b_CatchMe" );

	for( UINT cBone = 0; cBone < HoldMeBoneNodes.size(); ++cBone )
	{
		XMLNode * pBoneNode = HoldMeBoneNodes[cBone];

		string strBone = pBoneNode->Value();
		m_lstHoldMeBoneName.push_back( strBone );
	}
}

void CActionDataInfo::_LoadXML_ChangeTexture( XMLNode * pActionDataNode )
{
	XMLNodes textureNodes = pActionDataNode->GetChilds( "ChangeTexture" );
	for( UINT cTexture = 0; cTexture < textureNodes.size(); ++cTexture )
	{
		XMLNode * ptextureNode = textureNodes[cTexture];

		string strTexture		= Action::ActionString::GetToken( ptextureNode->Value() , 0 );
		string strMeshSlot		= Action::ActionString::GetToken( ptextureNode->Value() , 1 );
		string strTextureSlot	= Action::ActionString::GetToken( ptextureNode->Value() ,2 );

		if( strMeshSlot.empty() == false )
		{
			CChangeTextureInfo		changeTextureInfo;
			changeTextureInfo.m_strTextureName = strTexture;
			//changeTextureInfo.m_nMeshSlotIndex = C9DataInfoItem::Parse_GetEquipType( strMeshSlot.GetString() );
			//changeTextureInfo.m_nTextureIndex = strTextureSlot.A2I();
			m_lstChangeTextureData.push_back( changeTextureInfo );
		}
	}
}

void CActionDataInfo::_LoadXML_CatchBoneInfo( XMLNode * pActionDataNode , string &strAttr )
{
	XMLNodes catchBoneNodes = pActionDataNode->GetChilds( "CatchBone" );

	C9CatchBoneInfo _CatchBoneInfo;
	_CatchBoneInfo.strName = "b_EnemyCatch";
	m_lstCatchBoneInfo.push_back( _CatchBoneInfo );

	for( UINT cBone = 0; cBone < catchBoneNodes.size(); ++cBone )
	{
		XMLNode * pBoneNode = catchBoneNodes[cBone];

		C9CatchBoneInfo _TempCatchBoneInfo;
		_TempCatchBoneInfo.strName = pBoneNode->Value();

		if( pBoneNode->GetAttr( "Angle" , strAttr ) )
			sscanf( strAttr.c_str() , "%f %f %f" , &_TempCatchBoneInfo.vecAngle.x , &_TempCatchBoneInfo.vecAngle.y , &_TempCatchBoneInfo.vecAngle.z );

		XMVECTOR tmpVec = XMLoadFloat3( &_TempCatchBoneInfo.vecAngle );
		float degree = Action::RMATH_DEG2RAD;
		tmpVec = tmpVec * degree;
		XMStoreFloat3( &_TempCatchBoneInfo.vecAngle , tmpVec );

		if( pBoneNode->GetAttr( "Pos" , strAttr ) )
			sscanf( strAttr.c_str() , "%f %f %f" , &_TempCatchBoneInfo.vecPos.x , &_TempCatchBoneInfo.vecPos.y , &_TempCatchBoneInfo.vecPos.z );

		m_lstCatchBoneInfo.push_back( _TempCatchBoneInfo );
	}
}

void CActionDataInfo::_LoadXML_MeshSiegeInfo( XMLNode * pActionDataNode )
{
	XMLNodes meshNodes = pActionDataNode->GetChilds( "Mesh_Siege" );
	for( UINT cMesh = 0; cMesh < meshNodes.size(); ++cMesh )
	{
		CActionFileMeshInfo	MeshData;
		GetCharacterMeshInfo( meshNodes[cMesh] , &MeshData );

		m_lstSiegeMeshData.push_back( MeshData );
	}
}

void CActionDataInfo::GetCharacterMeshInfo( XMLNode * pMeshNode , CActionFileMeshInfo* pMeshData )
{	
	pMeshData->m_strMeshFile	= Action::ActionString::GetToken( pMeshNode->Value() , 0 );
	string strMeshSlot			= Action::ActionString::GetToken( pMeshNode->Value(), 1 );
	string strMeshHide			= Action::ActionString::GetToken( pMeshNode->Value() , 2 );
	pMeshData->m_strTextureFile = Action::ActionString::GetToken( pMeshNode->Value() , 3 );
}

void CActionDataInfo::_LoadXML_MeshInfo( XMLNode * pActionDataNode )
{
	vector<CActionFileMeshInfo>		lstTempData;

	XMLNodes meshNodes = pActionDataNode->GetChilds( "Mesh" );
	for( UINT cMesh = 0; cMesh < meshNodes.size(); ++cMesh )
	{
		CActionFileMeshInfo		MeshData;
		GetCharacterMeshInfo( meshNodes[cMesh] , &MeshData );
		lstTempData.push_back( MeshData );
	}
}

bool CActionDataInfo::_LoadXML_AnimationInfo( XMLNode * pActionDataNode )
{
	// 애니메이션 ------------------
	XMLNode * pAniNode = pActionDataNode->GetChild( "AnimationPack" );
	if( pAniNode == NULL )
	{
		MessageBoxA( NULL , "애니메이션팩파일정보가 없습니다. <AnimationPack>\n" , "Error" , MB_OK );
		return false;
	}
	m_strAnimationPack = pAniNode->Value();

	return true;
}

bool CActionDataInfo::_LoadXML_BoneScaleInfo( XMLNode * pActionDataNode , string &strAttr )
{
	// 본 스케일 -------------------
	XMLNodes boneScaleNodes = pActionDataNode->GetChilds( "CustomBoneScale" );

	for( UINT cBoneScale = 0; cBoneScale < boneScaleNodes.size(); ++cBoneScale )
	{
		XMLNode * pBoneScaleNode = boneScaleNodes[cBoneScale];
		CCustomScaleBoneInfo _CustomScaleBoneInfo;

		if( pBoneScaleNode->GetAttr( "BoneName" , strAttr ) == false )
		{
			MessageBoxA( NULL , "본 스케일의 본 이름이 없습니다. <CustomBoneScale BoneName=???>\n" , "Error" , MB_OK );
			return false;
		}
		_CustomScaleBoneInfo.dwBoneHashCode = CCrc32Static::StringCrc32( strAttr.c_str() );

		string strBoneSize;
		if( pBoneScaleNode->GetAttr( "Scale" , strBoneSize ) == false )
		{
			MessageBoxA( NULL , "본 스케일의 스케일 값이 없습니다. <CustomBoneScale ... Scale=???>\n" , "Error" , MB_OK );
			return false;
		}

		sscanf( strBoneSize.c_str() , "%f %f %f" , &_CustomScaleBoneInfo.vecSize.x , &_CustomScaleBoneInfo.vecSize.y , &_CustomScaleBoneInfo.vecSize.z );

		m_lstCustomScaleBoneInfo.push_back( _CustomScaleBoneInfo );
	}

	return true;
}

void CActionDataInfo::_LoadXML_BaseInfo( XMLNode * pActionDataNode )
{
	CActionDataInfo::LoadXmlActionIndex( pActionDataNode , m_lstActionIndexHashCode );

	pActionDataNode->GetAttrFloat( "AnimationSpeed" , m_fAnimationSpeed );
	pActionDataNode->GetAttrFloat( "SoundMinDistance" , m_fSoundMinDistance );
	pActionDataNode->GetAttrFloat( "SoundMaxDistance" , m_fSoundMaxDistance );

	pActionDataNode->GetAttrFloat( "ObstacleThickness" , m_fObstacleThickness );
	pActionDataNode->GetAttrFloat( "AddRenderDistance" , m_fAddRenderDistance );

	pActionDataNode->GetAttrFloat( "CatchHeight" , m_fCatchHeight );
	pActionDataNode->GetAttrFloat( "CatchCameraDistance" , m_fCatchCameraDistance );

	pActionDataNode->GetAttrFloat( "OutlineThickness" , m_fOutlineThickness );

	pActionDataNode->GetAttrFloat( "CurveRatio1" , m_fTurnRatio1 );
	pActionDataNode->GetAttrFloat( "CurveRatio2" , m_fTurnRatio2 );
	pActionDataNode->GetAttrBool( "CurvedPath" , m_bCurvedPath );

	pActionDataNode->GetAttrInt( "ShowHpNum" , m_iShowHpNum );
	pActionDataNode->GetAttrInt( "SuperArmorValue" , m_iSuperArmorValue );
	pActionDataNode->GetAttrBool( "UseStanceMode2" , m_bUseStanceMode2 );

	pActionDataNode->GetAttrBool( "SceneNotUnload" , m_bNotUnloadCharacterSecene );
	pActionDataNode->GetAttrBool( "PreloadCharacterScene" , m_bPreloadCharacterSecene );
	pActionDataNode->GetAttrBool( "AlwaysRenderSelfShadow" , m_bAlwaysRenderSelfShadow );
	pActionDataNode->GetAttrBool( "DisableRenderSelfShadow" , m_bDisableRenderSelfShadow );
	pActionDataNode->GetAttrBool( "DisableBoneLOD" , m_bDisableBoneLOD );
	pActionDataNode->GetAttrBool( "JumpAble" , m_bJumpAble );
	pActionDataNode->GetAttrBool( "WallRideAble" , m_bWallRideAble );
	pActionDataNode->GetAttrBool( "PitchRotateAble" , m_bPitchRotateAble );
	pActionDataNode->GetAttrBool( "Invincible" , m_bInvincible );
	pActionDataNode->GetAttrBool( "ShowName" , m_bShowName );
	pActionDataNode->GetAttrBool( "ShowHp" , m_bShowHp );
	pActionDataNode->GetAttrBool( "ShowMp" , m_bShowMp );
	pActionDataNode->GetAttrBool( "ShowInsight" , m_bInsight );
	pActionDataNode->GetAttrBool( "ShowHpEvent" , m_bShowEventHp );
	pActionDataNode->GetAttrBool( "DeadRemain" , m_bDeadRemain );
	pActionDataNode->GetAttrBool( "GenerateObstacle" , m_bGenerateObstacle );
	pActionDataNode->GetAttrBool( "NoAiAgent" , m_bNoAiAgent );
	pActionDataNode->GetAttrBool( "ShowCross" , m_bShowCross );
	pActionDataNode->GetAttrBool( "PositionFix" , m_bPositionFix );
	pActionDataNode->GetAttrBool( "NoDamageFrameDelay" , m_bNoDamageFrameDelay );
	pActionDataNode->GetAttrBool( "ExcludeTargeting" , m_bExcludeTargeting );
	pActionDataNode->GetAttrBool( "OnMinimap" , m_bNoteOnMinimap );
	pActionDataNode->GetAttrBool( "DeadEffect" , m_bDeadEffect );
	pActionDataNode->GetAttrBool( "ShowAutoOutline" , m_bIsShowAutoOutline );
	pActionDataNode->GetAttrBool( "NoNxController" , m_bNoNxController );
	pActionDataNode->GetAttrBool( "MoveWithRigidBody" , m_bMoveRigidBody );
	pActionDataNode->GetAttrBool( "AlwaysRenderShadow" , m_bAlwaysRenderShadow );

	pActionDataNode->GetAttr( "ActiveWeaponType" , m_strActiveWeaponType );
}

bool CActionDataInfo::_LoadXNL_BoneInfo( XMLNode * pActionDataNode )
{
	//////////////////////////////////////////////////////////////////////////	
	// 본
	XMLNode * pBoneNode = pActionDataNode->GetChild( "Bone" );
	if( pBoneNode == NULL )
	{
		MessageBoxA( NULL , "본파일정보가 없습니다. <Bone>\n" , "Error" , MB_OK );
		return false;
	}
	m_strBoneName = pBoneNode->Value();

	// CenterBone
	XMLNode * pCenterBoneNode = pActionDataNode->GetChild( "CenterBoneName" );
	if( pCenterBoneNode )
		m_strCenterBoneName = pCenterBoneNode->Value();

	return true;
}


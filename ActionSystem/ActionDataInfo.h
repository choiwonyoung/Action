#pragma once

#include "ActionContantable.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// C9ActionFileMeshInfo
struct CActionFileMeshInfo
{
	string		m_strMeshFile;
	string		m_strTextureFile;

	int			m_nSlotIndex;
	int			m_bHide;
	int			m_nMiddleCategory;

	void		Dump( C9File * pFile );
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// C9ChangeTextureInfo
struct CChangeTextureInfo
{
	string		m_strTextureName;
	int			m_nMeshSlotIndex;
	int			m_nTextureIndex;

	void		Dump( C9File * pFile );
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
struct CCustomScaleBoneInfo
{
	DWORD		dwBoneHashCode;
	vector3		vecSize;

	CCustomScaleBoneInfo()
		: dwBoneHashCode( 0 )
		, vecSize( 1.0f , 1.0f , 1.0f )
	{
	}

	void		Dump( C9File * pFile );
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// C9CatchBoneInfo 
struct C9CatchBoneInfo
{
	string			strName;		// 잡은 BoneIndex
	vector3			vecAngle;		// 잡은 Bone 추가 회전 값
	vector3			vecPos;			// 잡은 Bone 추가 이동 값

	C9CatchBoneInfo()
		: strName( "" )
		, vecAngle( 0.0f , 0.0f , 0.0f )
		, vecPos( 0.0f , 0.0f , 0.0f )
	{
	}

	void		Dump( C9File * pFile );
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 액션의 헤더라고 볼 수 있음. 기본 액션 형태를 정의함 
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CFrameEventEffect;
class CActionDataInfo
{
public:
	static void							LoadXmlActionIndex( XMLNode * pXMLNode, vector< DWORD > & lstActionIndexHashCode );
	static void							DumpActionIndex( C9File * pFile, vector< DWORD > & lstActionIndexHashCode );
public:

	CActionDataInfo();
	~CActionDataInfo();

	bool								LoadXML( XMLNode * pActionDataNode, List_PreloadString &lstPreloadEffect, List_PreloadString &lstPreloadSound );
	void								Dump( C9File *pFile , List_PreloadString &lstPreloadEffect , List_PreloadString &lstPreloadSound );

	// 메쉬 정보를 얻는다.
	void								GetCharacterMeshInfo( XMLNode * pMeshNode , CActionFileMeshInfo* pMeshData );

	
private:
	void								_LoadXML_BaseInfo( XMLNode * pActionDataNode );
	bool								_LoadXNL_BoneInfo( XMLNode * pActionDataNode );
	bool								_LoadXML_BoneScaleInfo( XMLNode * pActionDataNode , string &strAttr );
	void								_LoadXML_PreloadParticle( XMLNode * pActionDataNode , List_PreloadString & lstPreloadEffect , List_PreloadString & lstPreloadSound );
	void								_LoadXML_HoldBone( XMLNode * pActionDataNode );
	void								_LoadXML_ChangeTexture( XMLNode * pActionDataNode );
	void								_LoadXML_CatchBoneInfo( XMLNode * pActionDataNode , string &strAttr );
	void								_LoadXML_MeshSiegeInfo( XMLNode * pActionDataNode );
	void								_LoadXML_MeshInfo( XMLNode * pActionDataNode );
	bool								_LoadXML_AnimationInfo( XMLNode * pActionDataNode );

	// Save Binary
	void								_Dump_SaveHoldBoneData( C9File * pFile );
	void								_Dump_SaveCatchBoneData( C9File * pFile );
	void								_Dump_SaveChangeTextureData( C9File * pFile );
	void								_Dump_SaveSiegeMeshData( C9File * pFile );
	void								_Dump_SaveMeshData( C9File * pFile );
	void								_Dump_SaveBoneScale( C9File * pFile );

	// Load Binary
	void								_Dump_LoadBaseParticleName( C9File * pFile , List_PreloadString & lstPreloadEffect , List_PreloadString & lstPreloadSound );
	void								_Dump_LoadHoldBoneData( C9File * pFile );
	void								_Dump_LoadCatchBoneData( C9File * pFile );
	void								_Dump_LoadChangeTextureData( C9File * pFile );
	void								_Dump_LoadSiegeMeshData( C9File * pFile );
	void								_Dump_LoadMeshData( C9File * pFile );
	void								_Dump_LoadBoneScaleData( C9File * pFile );
	void								_Dump_SaveBaseParticleName( C9File * pFile , List_PreloadString & lstPreloadEffect , List_PreloadString & lstPreloadSound );

public:
	vector< DWORD >						m_lstActionIndexHashCode;		// ActionIndex 의 해쉬 코드 목록(@note : ActionData 를 여러개 기입해서 사용하는 ActionChart 에서 ActionIndex값으로 구분하기 위해서

	string								m_strActiveWeaponType;
	string								m_strAnimationPack;				
	// 본
	string								m_strBoneName;					// Bone 정보가 담긴 파일 이름
	string								m_strCenterBoneName;

	// 본 크기 설정 ( [index] = {Name, Size} )
	vector< CCustomScaleBoneInfo >		m_lstCustomScaleBoneInfo;

	//////////////////////////////////////////////////////////////////////////
	// 메쉬
	vector< CActionFileMeshInfo >		m_lstMeshData;
	vector< CActionFileMeshInfo >		m_lstSiegeMeshData;

	// 사용할 메쉬가 국가별 설정이나 저사양 버젼이 있는지 저장(XML에서만 사용한다.)
	vector<DWORD>						m_lstMeshTypeInfo;

	// 변경할 텍스쳐
	vector< CChangeTextureInfo >		m_lstChangeTextureData;

	// 잡기 본 리스트
	vector< C9CatchBoneInfo >			m_lstCatchBoneInfo;

	// 잡힐 본 리스트
	vector< string >					m_lstHoldMeBoneName;			// 잡힐 BoneIndex

																		// C9 파티클 기본(지속) 리스트
	vector< CFrameEventEffect >			m_lstBaseC9ParticleName;



	//////////////////////////////////////////////////////////////////////////
	// 묶음 저장
	float								m_fAnimationSpeed;				// 기본 애니메이션 속도
	float								m_fAddRenderDistance;			// 렌더링 거리
	float								m_fObstacleThickness;			// 캐릭터에 생성되는 Obstacle 두께(두께의 반임)
	float								m_fSoundMinDistance;			// 사운드 FrameEvent 가 발동될 때 적용되는 사운드 최소 거리
	float								m_fSoundMaxDistance;			// 사운드 FrameEvent 가 발동될 때 적용되는 사운드 최대 거리

	int									m_iShowHpNum;					// HP 표시 단계 여부

	int									m_iSuperArmorValue;				// 현재 액션이 슈퍼아머 인지를 결정하는 값

	float								m_fCatchHeight;					// 잡기시 카메라의 목표타겟 높이
	float								m_fCatchCameraDistance;			// 잡기시 카메라 거리
	float								m_fOutlineThickness;			// 외곽선 굵기

	float								m_fTurnRatio1;					// 길찾기 이동시 회전 비율 (AI 에서 사용됨)
	float								m_fTurnRatio2;					// 길찾기 이동시 회전 비율 (AI 에서 사용됨)
	bool								m_bCurvedPath;					// 이동시 곡선 이동을 사용하는가? (AI 에서 사용됨)

	bool								m_bUseStanceMode2;				// 스탠스모드2를 사용할것인가의 여부.(에르타등에 사용됨)
	bool								m_bNotUnloadCharacterSecene;	// 거리와 무관하게 캐릭터 리소스 해제하지 않는 여부 (리소스 할당/해제 오버헤드가 큰 특정 보스급 캐릭터에 쓰임)
	bool								m_bPreloadCharacterSecene;		// 로딩시점에 캐릭터를 미리로드함
	bool								m_bAlwaysRenderSelfShadow;		// 언제나 보임. 그림자도 보임.
	bool								m_bDisableRenderSelfShadow;		// 자신의 그림자를 생성하지 않음.
	bool								m_bDisableBoneLOD;				// 거리에 따른 BoneLOD를 사용하지 않는다.
	bool								m_bJumpAble;					// 점프가 가능한가? (AI 에서 사용됨)
	bool								m_bWallRideAble;				// 벽을 탈 수 있는가? (AI 에서 사용됨)
	bool								m_bPitchRotateAble;				// X축(pitch) 회전이 가능한가? m_bWallRideAble 와 혼합 불가
	bool								m_bInvincible;					// 무적 여부
	bool								m_bShowName;					// 이름 표시 여부
	bool								m_bShowHp;						// HP 표시 여부
	bool								m_bShowMp;						// MP 표시 여부
	bool								m_bInsight;						// 종족 세력 표시 여부
	bool								m_bShowEventHp;					// 이벤트 몹의 체력을 전면에 표시
	bool								m_bShowCross;					// 조준자 표시 여부 (ex ; 활 기술)
	bool								m_bNoteOnMinimap;				// 미니맵 표시 여부
	bool								m_bGenerateObstacle;			// 캐릭터 위치에 패스엔진의 Obstacle 을 생성 (door(문) 종료에 필요)
	bool								m_bNoAiAgent;					// AiAgent 를 생성하지 않음. 고정형 캐릭터에 AI 캐릭터 이동시 걸리면 안될 시 사용. (ex ; trap 류)
	bool								m_bNoNxController;				// 물리엔진의 컨트롤러를 생성하지 않음 (ex ; door)
	bool								m_bMoveRigidBody;				// 이동시 물리 엔진을 사용 함.
	bool								m_bPositionFix;					// 위치를 고정. 밀리지 않고 움직일 수 없음. (GMK, 마을NPC 에 사용되며, 이 경우 디폴트도 true, 아니면 디폴트는 false)
	bool								m_bNoDamageFrameDelay;			// 피격 프레임 딜레이 주지 않기
	bool								m_bExcludeTargeting;			// 타겟팅 되지 않음 여부
	bool								m_bIsBigMonster;				// 거대 몬스터 여부 (잡기 불가 등의 속성 지정에 참고됨)
	bool								m_bIsAlwaysAnimated;			// 항상 애니메이션을 하도록 처리
	bool								m_bDeadRemain;					// 죽어도 남아 있음 (GMK 류에 해줄 필요 있음)
	bool								m_bAlwaysRenderShadow;			// 항상 그림자를 그리는 캐릭터입니다.
	bool								m_bDeadEffect;					// 보스 몬스터가 죽을 경우 슬로우 효과 유뮤
	bool								m_bIsShowAutoOutline;			// 외곽선 자동 표시 온 오프
	// 묶음 저장 끝
	//////////////////////////////////////////////////////////////////////////
};


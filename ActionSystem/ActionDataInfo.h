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
	string			strName;		// ���� BoneIndex
	vector3			vecAngle;		// ���� Bone �߰� ȸ�� ��
	vector3			vecPos;			// ���� Bone �߰� �̵� ��

	C9CatchBoneInfo()
		: strName( "" )
		, vecAngle( 0.0f , 0.0f , 0.0f )
		, vecPos( 0.0f , 0.0f , 0.0f )
	{
	}

	void		Dump( C9File * pFile );
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// �׼��� ������ �� �� ����. �⺻ �׼� ���¸� ������ 
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

	// �޽� ������ ��´�.
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
	vector< DWORD >						m_lstActionIndexHashCode;		// ActionIndex �� �ؽ� �ڵ� ���(@note : ActionData �� ������ �����ؼ� ����ϴ� ActionChart ���� ActionIndex������ �����ϱ� ���ؼ�

	string								m_strActiveWeaponType;
	string								m_strAnimationPack;				
	// ��
	string								m_strBoneName;					// Bone ������ ��� ���� �̸�
	string								m_strCenterBoneName;

	// �� ũ�� ���� ( [index] = {Name, Size} )
	vector< CCustomScaleBoneInfo >		m_lstCustomScaleBoneInfo;

	//////////////////////////////////////////////////////////////////////////
	// �޽�
	vector< CActionFileMeshInfo >		m_lstMeshData;
	vector< CActionFileMeshInfo >		m_lstSiegeMeshData;

	// ����� �޽��� ������ �����̳� ����� ������ �ִ��� ����(XML������ ����Ѵ�.)
	vector<DWORD>						m_lstMeshTypeInfo;

	// ������ �ؽ���
	vector< CChangeTextureInfo >		m_lstChangeTextureData;

	// ��� �� ����Ʈ
	vector< C9CatchBoneInfo >			m_lstCatchBoneInfo;

	// ���� �� ����Ʈ
	vector< string >					m_lstHoldMeBoneName;			// ���� BoneIndex

																		// C9 ��ƼŬ �⺻(����) ����Ʈ
	vector< CFrameEventEffect >			m_lstBaseC9ParticleName;



	//////////////////////////////////////////////////////////////////////////
	// ���� ����
	float								m_fAnimationSpeed;				// �⺻ �ִϸ��̼� �ӵ�
	float								m_fAddRenderDistance;			// ������ �Ÿ�
	float								m_fObstacleThickness;			// ĳ���Ϳ� �����Ǵ� Obstacle �β�(�β��� ����)
	float								m_fSoundMinDistance;			// ���� FrameEvent �� �ߵ��� �� ����Ǵ� ���� �ּ� �Ÿ�
	float								m_fSoundMaxDistance;			// ���� FrameEvent �� �ߵ��� �� ����Ǵ� ���� �ִ� �Ÿ�

	int									m_iShowHpNum;					// HP ǥ�� �ܰ� ����

	int									m_iSuperArmorValue;				// ���� �׼��� ���۾Ƹ� ������ �����ϴ� ��

	float								m_fCatchHeight;					// ���� ī�޶��� ��ǥŸ�� ����
	float								m_fCatchCameraDistance;			// ���� ī�޶� �Ÿ�
	float								m_fOutlineThickness;			// �ܰ��� ����

	float								m_fTurnRatio1;					// ��ã�� �̵��� ȸ�� ���� (AI ���� ����)
	float								m_fTurnRatio2;					// ��ã�� �̵��� ȸ�� ���� (AI ���� ����)
	bool								m_bCurvedPath;					// �̵��� � �̵��� ����ϴ°�? (AI ���� ����)

	bool								m_bUseStanceMode2;				// ���Ľ����2�� ����Ұ��ΰ��� ����.(����Ÿ� ����)
	bool								m_bNotUnloadCharacterSecene;	// �Ÿ��� �����ϰ� ĳ���� ���ҽ� �������� �ʴ� ���� (���ҽ� �Ҵ�/���� ������尡 ū Ư�� ������ ĳ���Ϳ� ����)
	bool								m_bPreloadCharacterSecene;		// �ε������� ĳ���͸� �̸��ε���
	bool								m_bAlwaysRenderSelfShadow;		// ������ ����. �׸��ڵ� ����.
	bool								m_bDisableRenderSelfShadow;		// �ڽ��� �׸��ڸ� �������� ����.
	bool								m_bDisableBoneLOD;				// �Ÿ��� ���� BoneLOD�� ������� �ʴ´�.
	bool								m_bJumpAble;					// ������ �����Ѱ�? (AI ���� ����)
	bool								m_bWallRideAble;				// ���� Ż �� �ִ°�? (AI ���� ����)
	bool								m_bPitchRotateAble;				// X��(pitch) ȸ���� �����Ѱ�? m_bWallRideAble �� ȥ�� �Ұ�
	bool								m_bInvincible;					// ���� ����
	bool								m_bShowName;					// �̸� ǥ�� ����
	bool								m_bShowHp;						// HP ǥ�� ����
	bool								m_bShowMp;						// MP ǥ�� ����
	bool								m_bInsight;						// ���� ���� ǥ�� ����
	bool								m_bShowEventHp;					// �̺�Ʈ ���� ü���� ���鿡 ǥ��
	bool								m_bShowCross;					// ������ ǥ�� ���� (ex ; Ȱ ���)
	bool								m_bNoteOnMinimap;				// �̴ϸ� ǥ�� ����
	bool								m_bGenerateObstacle;			// ĳ���� ��ġ�� �н������� Obstacle �� ���� (door(��) ���ῡ �ʿ�)
	bool								m_bNoAiAgent;					// AiAgent �� �������� ����. ������ ĳ���Ϳ� AI ĳ���� �̵��� �ɸ��� �ȵ� �� ���. (ex ; trap ��)
	bool								m_bNoNxController;				// ���������� ��Ʈ�ѷ��� �������� ���� (ex ; door)
	bool								m_bMoveRigidBody;				// �̵��� ���� ������ ��� ��.
	bool								m_bPositionFix;					// ��ġ�� ����. �и��� �ʰ� ������ �� ����. (GMK, ����NPC �� ���Ǹ�, �� ��� ����Ʈ�� true, �ƴϸ� ����Ʈ�� false)
	bool								m_bNoDamageFrameDelay;			// �ǰ� ������ ������ ���� �ʱ�
	bool								m_bExcludeTargeting;			// Ÿ���� ���� ���� ����
	bool								m_bIsBigMonster;				// �Ŵ� ���� ���� (��� �Ұ� ���� �Ӽ� ������ �����)
	bool								m_bIsAlwaysAnimated;			// �׻� �ִϸ��̼��� �ϵ��� ó��
	bool								m_bDeadRemain;					// �׾ ���� ���� (GMK ���� ���� �ʿ� ����)
	bool								m_bAlwaysRenderShadow;			// �׻� �׸��ڸ� �׸��� ĳ�����Դϴ�.
	bool								m_bDeadEffect;					// ���� ���Ͱ� ���� ��� ���ο� ȿ�� ����
	bool								m_bIsShowAutoOutline;			// �ܰ��� �ڵ� ǥ�� �� ����
	// ���� ���� ��
	//////////////////////////////////////////////////////////////////////////
};


#pragma once

#pragma pack(push, 1)

#include "ActionContantable.h"
#include "ActionFunction.h"

class CActionData;
class CActionBranch;
class CFrameEvent;

class CActionChart
{
public:
	struct CCopyActionChartValue
	{
		int							m_iCopyCount;
		float						m_fMoveSpeed;
		float						m_fAnimationSpeed;
		float						m_fFrameMoveSpeed;

		CCopyActionChartValue()
		{
			memset( this , 0 , sizeof( CCopyActionChartValue ) );
		}

		void	LoadXML( XMLNode *pXMLNode , CActionChart *pActionChart );
	};

public:
	CActionChart( const CActionData& actionData );
	~CActionChart();

	void								SetActionAttr( DWORD dwAttr )		{ SET_ATTR( m_dwActionAttr , dwAttr ); }
	void								ResetActionAttr( DWORD dwAttr )		{ RESET_ATTR( m_dwActionAttr , dwAttr ); }
	bool								IsActionAttr( DWORD dwAttr ) const	{ return IS_ATTR( m_dwActionAttr , dwAttr ); }

	void								Dump( C9File * pFile , List_PreloadString & lstPreloadEffect , List_PreloadString &lstPreloadSound );

	bool								LoadXML( XMLNode *pXMLNode , XMLNode *pRootNode , HashMap_ActionFunction & mapActionFunction , List_PreloadString & lstPreloadEffect , List_PreloadString &lstPreloadSound );


	void								LoadActionBranchFuntion( XMLNode * pXMLNode , HashMap_ActionFunction &mapActionFunction );

	bool								LoadActionBranch( XMLNodes nodes );
	bool								LoadActionBackGroundBranch( XMLNodes nodes );
	bool								LoadFrameEvent( XMLNodes nodes , List_PreloadString &lstPreloadEffect , List_PreloadString &lstPreloadSound );
	bool								LoadXMLActionAttr( XMLNode *pXMLNode , const char *pStrName , C9ActionChartAttr attrType );
	void								CopyActionChartLevel( CActionChart *pActionChart , int iLevel );

private:
	bool								_LoadAttrFromActionDataInfo( XMLNode *pXMLNode );
	bool								_attackFrameEventInverseMessageBox( const char* fileName , const char* actionName , ULONG prevFrameIndex , ULONG nextFrameIndex );

	void								_LoadXML_ActionTypeInfo( XMLNode * pXMLNode , string strAttr );
	void								_LoadXML_OutLineInfo( XMLNode * pXMLNode );
	bool								_LoadXML_MoveSpeedInfo( XMLNode * pXMLNode , string &strAttr );
	bool								_LoadXML_AnimationInfo( XMLNode * pXMLNode );
	void								_LoadXML_EndActionNode( XMLNode * pXMLNode );
	void								_LoadXML_ActionAttr( XMLNode * pXMLNode );
	void								_LoadXML_ShowCrossCheckAction( XMLNode * pXMLNode , string &strAttr );


public:

	const CActionData&					m_actionData;

	vector< DWORD >						m_lstActionIndexHashCode;				// ����(?) Action Tag �� ���� ActionIndex ����
	vector< CActionBranch *>			m_lstActionBranch;						// �׼� �귣ġ ����Ʈ	(delete �� C9ActionChart ����)
	vector< CFrameEvent  *>				m_lstFrameEvent;						// �̺�Ʈ ������ ����Ʈ

	string								m_strActionName;						// �׼Ǹ�
	string								m_strAnimationFilename;					// �ִϸ��̼Ǹ�
	string								m_strEndActionName;						// ���� �׼Ǹ�
	string								m_strCatchTargetActionName;				// ���� ��뿡�� ���� ��ų��� �׼�
	string								m_strShowCrossCheckAction;

	//////////////////////////////////////////////////////////////////////////
	// ���� ����
	DWORD								m_dwHashcode;							// �ؽ��� (�׼Ǹ�)

	DWORD								m_dwEndActionCode;
	DWORD								m_dwEndActionSkillType;					// ���� �׼� ��ųŸ��
	DWORD								m_dwCatchTargetActionCode;				// ���� ��ų��� �׼�
	DWORD								m_dwShowCrossCheckActionCode;
	DWORD								m_dwShowCrossCheckActionSkillType;
	DWORD							    m_dwAnimationHashCode;					// �ִϸ��̼Ǹ�

	DWORD								m_dwActionAttr;							// �׼� �Ӽ�
	UINT64								m_ddwInputMask;							// �׼� �귣ġ�� �Է� ����ũ ��
	int									m_nEndActionBlendFrame;					// ���� �׼� ���� Ÿ��

	DWORD								m_dwActionType;							// C9ControlActionStatus :: C9CAS_* �� bit ����
	C9AdditionMove						m_AdditionMove;
	C9RotationType						m_RotationType;							// ī�޶� �� ĳ���� ȸ�� Ÿ��
	C9AddDirection						m_AddDirection;
	C9ActionSituation					m_ActionSituation;
	C9ActionFallCancelType				m_FallCancelType;						// ĳ���Ͱ� �̵��� ������ �������� �������� Ÿ��(�������� �ִϸ��̼��� ����)
	C9ActionAddSpeedRateType			m_AddSpeedRateType;						// �̵� �Ǵ� ���ݼӵ��� �����Ϳ��� ������ �����Ѵ�.
	C9ActionCheckItemType				m_ActionCheckItem;						// �տ� ��� �ִ� ������ üũ
	C9ActionUseSkillType				m_UseSkillType;							// ��ų ��� ����
	C9ShowOutlineState					m_IsShowOutline;						// �ƿ� ������ ������ ���ΰ�.
	int									m_iSuperArmorValue;						// ���� �׼��� ���۾Ƹ� ������ �����ϴ� ��
	float								m_fOutlineThickness;

	float								m_fMoveSpeed;							// �̵� �ӵ�
	float								m_fFlyFallSpeed;
	float								m_fAddAttackDirection;					// ���ݽ� ���� ����
	float								m_fAnimationSpeed;						// �ִϸ��̼� �ӵ�
	float								m_fMoveDirection;						// �̵��� �̵� ����
	float								m_fCameraRotationSpeed;					// ī�޶� �� ĳ���� ȸ�� �ӵ�
	int									m_nFixRotation;							// �ִϸ��̼� ������ ĳ���� ȸ���� (180�̸� �ִ������� ĳ���ʹ� 180���� ȸ����)

																				// �ɸ����� Ư�� ��Ȳ�� ����
	DWORD								m_dwActionSpecialValue;					// �׼��� Ư����Ȳ( ����ġ ���� ���� �߰� �� ����ϸ�ɵ�..)

																				// ���Ϳ��Ը� ���� (������ �̵� �ӵ� ����)
	int									m_nFrameMoveSpeedStartFrame;			// ���� ������
	int									m_nFrameMoveSpeedEndFrame;				// ���� ������
	float								m_fFrameMoveSpeed;						// �̵� �ӵ�
	float								m_fRotation;							// ȸ��

	float								m_fHaveParentRotationValue;				// �θ� ���� ����� Ư�� �׼ǿ��� �ٶ󺸴� ������ ������ �� �� �ְ� �ϴ� ��


	float								m_fPickRange;							// C9FrameEventRangeAreaAttack ��ŷ �ݰ�

																				//��׶��� �׼ǿ�
	float								m_fDummyActionEndFrame;
	//
	// �ӵ� ��ȭ
	int									m_nChangeSpeedStartFrame;				// ����������
	int									m_nAcceleration;						// ���ӵ�
	int									m_nLimitSpeed;							// ���� �ӵ�

	int									m_nHoldMeBoneIndex;						// ���� �� �ε���
	int									m_nPhysBoneActorGroup;					// Bone Actor�� �׷�ID
																			
	CCopyActionChartValue				m_CopyActionChartValue;					// �׼� ����

	bool								m_bIsBackgroundAnimationFetch;			//��׶��� �׼ǿ�. ���� �������� �ִϸ��̼��� �ӵ��� �ð����� ���ͼ� ��
	bool								m_bPickingAlternativeLand;				//ũ�ν� ���� ��ŷ �ҽ� ���� ��ŷ�� ������ ���ٸ� ���� �Ʒ��� ������ ��ŷ�ϵ��� ��
	bool								m_bUseSkillLevelName;
	bool								m_bMovePickingDirection;
	bool								m_bMoveSpeedFetch;						// ���� �׼� �ӵ� ���� ����

	bool								m_bHaveParentIsRotation;				// �θ� ���� ����� ȸ������ �̿��� �� ����

	bool								m_bMoveTargetRotation;
	// ���� ���� ��
	//////////////////////////////////////////////////////////////////////////
};

#pragma pack(pop)
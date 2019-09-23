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

	vector< DWORD >						m_lstActionIndexHashCode;				// 같은(?) Action Tag 에 대한 ActionIndex 모음
	vector< CActionBranch *>			m_lstActionBranch;						// 액션 브랜치 리스트	(delete 는 C9ActionChart 에서)
	vector< CFrameEvent  *>				m_lstFrameEvent;						// 이벤트 프레임 리스트

	string								m_strActionName;						// 액션명
	string								m_strAnimationFilename;					// 애니메이션명
	string								m_strEndActionName;						// 종료 액션명
	string								m_strCatchTargetActionName;				// 잡힌 상대에게 적용 시킬상대 액션
	string								m_strShowCrossCheckAction;

	//////////////////////////////////////////////////////////////////////////
	// 묶음 저장
	DWORD								m_dwHashcode;							// 해쉬값 (액션명)

	DWORD								m_dwEndActionCode;
	DWORD								m_dwEndActionSkillType;					// 종료 액션 스킬타입
	DWORD								m_dwCatchTargetActionCode;				// 적용 시킬상대 액션
	DWORD								m_dwShowCrossCheckActionCode;
	DWORD								m_dwShowCrossCheckActionSkillType;
	DWORD							    m_dwAnimationHashCode;					// 애니메이션명

	DWORD								m_dwActionAttr;							// 액션 속성
	UINT64								m_ddwInputMask;							// 액션 브랜치의 입력 마스크 합
	int									m_nEndActionBlendFrame;					// 종료 액션 블랜드 타임

	DWORD								m_dwActionType;							// C9ControlActionStatus :: C9CAS_* 의 bit 조합
	C9AdditionMove						m_AdditionMove;
	C9RotationType						m_RotationType;							// 카메라 및 캐릭터 회전 타입
	C9AddDirection						m_AddDirection;
	C9ActionSituation					m_ActionSituation;
	C9ActionFallCancelType				m_FallCancelType;						// 캐릭터가 이동중 벼랑을 만났을때 떨어지는 타입(떨어지는 애니메이션을 결정)
	C9ActionAddSpeedRateType			m_AddSpeedRateType;						// 이동 또는 공격속도를 데이터에서 가져와 조절한다.
	C9ActionCheckItemType				m_ActionCheckItem;						// 손에 들고 있는 아이템 체크
	C9ActionUseSkillType				m_UseSkillType;							// 스킬 사용 여부
	C9ShowOutlineState					m_IsShowOutline;						// 아웃 라인을 보여줄 것인가.
	int									m_iSuperArmorValue;						// 현재 액션이 슈퍼아머 인지를 결정하는 값
	float								m_fOutlineThickness;

	float								m_fMoveSpeed;							// 이동 속도
	float								m_fFlyFallSpeed;
	float								m_fAddAttackDirection;					// 공격시 공격 방향
	float								m_fAnimationSpeed;						// 애니메이션 속도
	float								m_fMoveDirection;						// 이동시 이동 방향
	float								m_fCameraRotationSpeed;					// 카메라 및 캐릭터 회전 속도
	int									m_nFixRotation;							// 애니메이션 종료후 캐릭터 회전값 (180이면 애니종료후 캐릭터는 180도로 회전됨)

																				// 케릭터의 특수 상황을 설정
	DWORD								m_dwActionSpecialValue;					// 액션의 특수상황( 예상치 못한 변수 추가 로 사용하면될듯..)

																				// 몬스터에게만 쓰임 (프레임 이동 속도 지정)
	int									m_nFrameMoveSpeedStartFrame;			// 시작 프레임
	int									m_nFrameMoveSpeedEndFrame;				// 종료 프레임
	float								m_fFrameMoveSpeed;						// 이동 속도
	float								m_fRotation;							// 회전

	float								m_fHaveParentRotationValue;				// 부모를 가진 대상이 특정 액션에서 바라보는 방향을 결정해 줄 수 있게 하는 값


	float								m_fPickRange;							// C9FrameEventRangeAreaAttack 피킹 반경

																				//백그라운드 액션용
	float								m_fDummyActionEndFrame;
	//
	// 속도 변화
	int									m_nChangeSpeedStartFrame;				// 시작프레임
	int									m_nAcceleration;						// 가속도
	int									m_nLimitSpeed;							// 최저 속도

	int									m_nHoldMeBoneIndex;						// 잡힐 본 인덱스
	int									m_nPhysBoneActorGroup;					// Bone Actor의 그룹ID
																			
	CCopyActionChartValue				m_CopyActionChartValue;					// 액션 복사

	bool								m_bIsBackgroundAnimationFetch;			//백그라운드 액션용. 현재 실행중인 애니메이션의 속도와 시간등을 따와서 씀
	bool								m_bPickingAlternativeLand;				//크로스 헤어로 픽킹 할시 만약 픽킹한 지점이 없다면 수직 아래의 지면을 픽킹하도록 함
	bool								m_bUseSkillLevelName;
	bool								m_bMovePickingDirection;
	bool								m_bMoveSpeedFetch;						// 이전 액션 속도 유지 여부

	bool								m_bHaveParentIsRotation;				// 부모를 가진 대상이 회전각을 이용할 지 여부

	bool								m_bMoveTargetRotation;
	// 묶음 저장 끝
	//////////////////////////////////////////////////////////////////////////
};

#pragma pack(pop)
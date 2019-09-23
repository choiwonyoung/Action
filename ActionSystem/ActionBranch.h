#pragma once
#pragma pack(push, 1)
#include "ActionContantable.h"

class CActionBranch
{
public:
	// 액션 복사 ////////////////////////////////////////////////////////////////
	struct CopyActionBranchValue
	{
		float						m_fTimerTime;

		CopyActionBranchValue()
		{
			memset( this , 0 , sizeof( CopyActionBranchValue ) );
		}
	};

public:
	CActionBranch();

	bool						LoadXML( XMLNode *pXMLNode );
	void						Dump( C9File * pFile );

	static UINT64				Parse_GetInput( const char * pszParameter );
	static string				Parse_GetInputString( UINT64 ddwInput );
	static C9_INPUT_CHECK_STATE	Parse_GetInputCheck( UINT64 ddwInput , const char* pszParameter );
	void						CopyActionValue( CActionBranch *pActionBranch , int iLevel );

public:
	int							m_iCopyCount;					// 복사 횟수(저장 안함)

public:

	string						m_strTargetAction;				// 브랜칭이 일어나면 전환될 액션명
	string						m_strTargetAIAction;			// AI액션 설정

	//////////////////////////////////////////////////////////////////////////
	// 묶음 저장
	DWORD						m_dwTargetActionCode;			// m_strTargetAction 에 대한 해쉬코드
	DWORD						m_dwTargetAIActionCode;			// m_strTargetAIAction 에 대한 코드
																// 시간 조건
	C9ActionInputTiming			m_InputTiming;					// 전체 구간인지, 특정 구간에서만 일어나는 브랜칭인지?
	int							m_nInputStartTime;				// 특정 구간(CIT_Section)에서만 사용됨 ; 시작 시간 (이전까지는 조건을 만족해도 브랜칭이 일어나지 않음)
	int							m_nInputEndTime;				// 특정 구간(CIT_Section)에서만 사용됨 ; 마지막 시간 (이후에서는 조건을 만족해도 브랜칭이 일어나지 않음)

																// 입력 조건
	UINT64						m_ddwInput;						// 입력(혹은 특정 상태) 조건에 사용되는 입력 상태
	int							m_nHitCount;					// m_ddwInput & CI_TOGGLE (A,D 로 잡기 빠져나오는 키) 인 경우 몇 번을 눌러야 브랜칭이 일어나는가? (다른 키도 쓰여야 하나, 현재로서는 TOGGLE 외에는 의미가 없음)
	DWORD						m_dwClassKey;					// PC 클래스 키 ( 일종의 클래스 판별 분기 조건문에서 참고함 )

	int							m_nBlendFrame;					// 얼마간의 대기 시간 후 브랜칭 발생하는지 (??)

	float						m_fCatchDistance;				// Input="CATCH" ; 잡기 상태인 경우, 브랜칭이 일어나는 최대(?) 거리 제한 수치
	C9_INPUT_CHECK_STATE		m_eInputCheckState;				// Input 입력시 부가적인 상태 체크

																// 플레이어 변수 (스크립트에서 검사)
	DWORD						m_dwPlayerValueNameHashCode;
	int							m_iPlayerValue;
	ValueCompareType			m_PlayerValueCompareType;

	// 플레이어 서버 변수 (스크립트에서 검사)
	DWORD						m_dwPSValueNameHashCode;
	int							m_iPlayerServerValue;
	ValueCompareType			m_PlayerServerValueCompareType;

	// 플레이어 타이머 (조건에 사용됨?)
	DWORD						m_dwTimerNameHashCode;
	float						m_fTimerTime;
	ValueCompareType			m_TimerCompareType;

	// 액션 복사
	CopyActionBranchValue		m_CopyActionBranchValue;

	DWORD						m_dwAbnormalKey;
	DWORD						m_dwTarget;

	// 거리이동 수치
	float						m_fMoveDistanceThreshold;
	// 스킬 사용 조건
	DWORD						m_dwSkillTypeKey;				// 어떤 스킬(타입)을 사용할 때 브랜칭이 일어나는가?
	DWORD						m_dwTalisManEnchantLevel;		// 부적아이템 강화 레벨
	bool						m_bIsBackGroundBranch;			// 백그라운드 브랜치인가
	bool						m_bCheckSkill;					// 스킬 사용 검사 여부(?) ; 플레이어 캐릭터만 사용되는듯(?)
	bool						m_bUseSkillLevelName;
	bool						m_bCheckPrePSValue;				// PSVALUE의 변경전 값을 검사할것인가

	bool						m_bWaitActionEnd;				// 액션이 완전히 끝나야 브랜칭이 일어나는가? (??)

	// 묶음 저장 끝
	//////////////////////////////////////////////////////////////////////////
};

#pragma pack(pop)

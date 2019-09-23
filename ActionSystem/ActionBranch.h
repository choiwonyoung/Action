#pragma once
#pragma pack(push, 1)
#include "ActionContantable.h"

class CActionBranch
{
public:
	// �׼� ���� ////////////////////////////////////////////////////////////////
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
	int							m_iCopyCount;					// ���� Ƚ��(���� ����)

public:

	string						m_strTargetAction;				// �귣Ī�� �Ͼ�� ��ȯ�� �׼Ǹ�
	string						m_strTargetAIAction;			// AI�׼� ����

	//////////////////////////////////////////////////////////////////////////
	// ���� ����
	DWORD						m_dwTargetActionCode;			// m_strTargetAction �� ���� �ؽ��ڵ�
	DWORD						m_dwTargetAIActionCode;			// m_strTargetAIAction �� ���� �ڵ�
																// �ð� ����
	C9ActionInputTiming			m_InputTiming;					// ��ü ��������, Ư�� ���������� �Ͼ�� �귣Ī����?
	int							m_nInputStartTime;				// Ư�� ����(CIT_Section)������ ���� ; ���� �ð� (���������� ������ �����ص� �귣Ī�� �Ͼ�� ����)
	int							m_nInputEndTime;				// Ư�� ����(CIT_Section)������ ���� ; ������ �ð� (���Ŀ����� ������ �����ص� �귣Ī�� �Ͼ�� ����)

																// �Է� ����
	UINT64						m_ddwInput;						// �Է�(Ȥ�� Ư�� ����) ���ǿ� ���Ǵ� �Է� ����
	int							m_nHitCount;					// m_ddwInput & CI_TOGGLE (A,D �� ��� ���������� Ű) �� ��� �� ���� ������ �귣Ī�� �Ͼ�°�? (�ٸ� Ű�� ������ �ϳ�, ����μ��� TOGGLE �ܿ��� �ǹ̰� ����)
	DWORD						m_dwClassKey;					// PC Ŭ���� Ű ( ������ Ŭ���� �Ǻ� �б� ���ǹ����� ������ )

	int							m_nBlendFrame;					// �󸶰��� ��� �ð� �� �귣Ī �߻��ϴ��� (??)

	float						m_fCatchDistance;				// Input="CATCH" ; ��� ������ ���, �귣Ī�� �Ͼ�� �ִ�(?) �Ÿ� ���� ��ġ
	C9_INPUT_CHECK_STATE		m_eInputCheckState;				// Input �Է½� �ΰ����� ���� üũ

																// �÷��̾� ���� (��ũ��Ʈ���� �˻�)
	DWORD						m_dwPlayerValueNameHashCode;
	int							m_iPlayerValue;
	ValueCompareType			m_PlayerValueCompareType;

	// �÷��̾� ���� ���� (��ũ��Ʈ���� �˻�)
	DWORD						m_dwPSValueNameHashCode;
	int							m_iPlayerServerValue;
	ValueCompareType			m_PlayerServerValueCompareType;

	// �÷��̾� Ÿ�̸� (���ǿ� ����?)
	DWORD						m_dwTimerNameHashCode;
	float						m_fTimerTime;
	ValueCompareType			m_TimerCompareType;

	// �׼� ����
	CopyActionBranchValue		m_CopyActionBranchValue;

	DWORD						m_dwAbnormalKey;
	DWORD						m_dwTarget;

	// �Ÿ��̵� ��ġ
	float						m_fMoveDistanceThreshold;
	// ��ų ��� ����
	DWORD						m_dwSkillTypeKey;				// � ��ų(Ÿ��)�� ����� �� �귣Ī�� �Ͼ�°�?
	DWORD						m_dwTalisManEnchantLevel;		// ���������� ��ȭ ����
	bool						m_bIsBackGroundBranch;			// ��׶��� �귣ġ�ΰ�
	bool						m_bCheckSkill;					// ��ų ��� �˻� ����(?) ; �÷��̾� ĳ���͸� ���Ǵµ�(?)
	bool						m_bUseSkillLevelName;
	bool						m_bCheckPrePSValue;				// PSVALUE�� ������ ���� �˻��Ұ��ΰ�

	bool						m_bWaitActionEnd;				// �׼��� ������ ������ �귣Ī�� �Ͼ�°�? (??)

	// ���� ���� ��
	//////////////////////////////////////////////////////////////////////////
};

#pragma pack(pop)

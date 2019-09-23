#pragma once

#include "ActionContantable.h"
#include "ActionDefine.h"
#include "FrameEventDefine.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// C9FrameEvent
class CActionData;
class CFrameEvent
{
public:
	CFrameEvent();
	virtual ~CFrameEvent() {};

	virtual CFrameEventType		GetType() const = 0;
	virtual bool 				IsAttackFrameEvent() const				{ return false; }
	virtual bool				IsProjectileAttackFrameEvent() const	{ return false; }		// �߻�ü ���Ÿ� ���� ����������
	virtual int					GetEndFrame() const						{ return m_nFrame; }	// �� �������� �ִ� ���, �� �������� �����Ѵ�.

	virtual bool 				LoadXML( XMLNode *pXMLNode , List_PreloadString &lstPreloadEffect , List_PreloadString &lstPreloadSound , const char * pszClassName = NULL );
	virtual void 				Dump( C9File * pFile , List_PreloadString & lstPreloadEffect , List_PreloadString &lstPreloadSound );

	static CFrameEventType		Parse_GetFrameEventType( const char * pszType );
	static CFrameEvent *		Create_FrameEvent( CFrameEventType type , const CActionData & actionData , const CFrameEvent * pOriginal );

	// ������ ���� ����
	static void					LoadDataVarList( const char *pStrMessage , vector< CAddAttackValue > &varList );
	static void					DumpDataVarList( C9File * pFile , vector< CAddAttackValue > &varList );

	virtual void				SetActionCodeAndIndex( DWORD dwActionCode , UINT uiIndex )	{ m_dwActionCode = dwActionCode; m_uiFrameEventIndex = uiIndex; }
	DWORD						GetActionCode() const										{ return m_dwActionCode; }
	UINT						GetFrameEventIndex() const									{ return m_uiFrameEventIndex; }

	///////////
	//�߻�ü������ ���� �Լ���
	virtual float				GetLifeTime() { return 0.0f; }
	virtual int					GetRayCount() { return 0; }
	virtual int					GetMaxRayCount() { return 0; }

	///////////

	virtual void 				LoadXMLCopyActionValue( XMLNode *pXMLNode ) { };
	virtual void 				CopyActionValue( CFrameEvent *pFrameEvent , int iLevel ) { };

public:
	// ���� ����
	int							m_iCopyCount;

public:
	vector< DWORD >				m_lstActionIndexHashCode;

	//////////////////////////////////////////////////////////////////////////
	// ���� ����
	int							m_nFrame;
	DWORD						m_dwID;
	DWORD						m_dwNeedID;				// FrameEvent ID�� �ο��� ���� ���� ID�� �����Ǿ����� Ȯ���Ϸ��� ���� ����
	DWORD						m_dwCheckSkillType;

	DWORD						m_dwActionCode;
	UINT						m_uiFrameEventIndex;
	// ���� ����
	//////////////////////////////////////////////////////////////////////////
};

inline CFrameEvent::CFrameEvent()
: m_iCopyCount( 0 )

, m_lstActionIndexHashCode()

, m_nFrame( 0 )
, m_dwID( 0xFFFFFFFF )
, m_dwNeedID( 0xFFFFFFFF )
, m_dwActionCode( 0 )

, m_dwCheckSkillType( 0 )
, m_uiFrameEventIndex( 0 )
{
}

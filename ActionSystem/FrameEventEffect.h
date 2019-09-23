#pragma once

#include "FrameEvent.h"
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ����Ʈ
class CFrameEventEffect : public CFrameEvent
{
	// �׼� ���� /////////////////////////////////////
	struct C9CopyActionValue
	{
		vector3			m_vecScale;

		C9CopyActionValue()
		{
			memset( this , 0 , sizeof( C9CopyActionValue ) );
		}
	};

public:
	CFrameEventEffect();

	virtual CFrameEventType		GetType() const { return CFE_Effect; }

	virtual bool				LoadXML( XMLNode *pXMLNode , List_PreloadString &lstPreloadEffect , List_PreloadString &lstPreloadSound , const char * pszClassName = NULL );
	virtual void				Dump( C9File * pFile , List_PreloadString & lstPreloadEffect , List_PreloadString &lstPreloadSound );

	// �׼� ����
	virtual void				LoadXMLCopyActionValue( XMLNode *pXMLNode );
	virtual void				CopyActionValue( CFrameEvent *pFrameEvent , int iLevel );

public:
	EFF_COMMAND					m_eCommandState;		// ���� ����

	C9CopyActionValue			m_CopyActionValue;

public:
	string						m_strEffectFile;		// ����Ʈ ���ϸ�
	string						m_strBone;

	//////////////////////////////////////////////////////////////////////////
	// ���� ����
	vector3						m_vecScale;
	vector3						m_vecLocalPos;
	vector3						m_vecRotation;

	int							m_iIndex;

	bool						m_bAttachCharacter;
	bool						m_bCharAniSpeed;
	bool						m_bApplyScale;
	bool						m_bApplyScalePos;
	bool						m_bDistCheck;			// �Ÿ��� ���� ���� ���� LOD
	// ���� ���� ��
	//////////////////////////////////////////////////////////////////////////
};

inline CFrameEventEffect::CFrameEventEffect()
	: CFrameEvent()

	, m_eCommandState( EFF_CMD_START )

	, m_strEffectFile( "" )
	, m_strBone( "" )

	, m_vecScale( 1.0f , 1.0f , 1.0f )
	, m_vecLocalPos( 0.0f , 0.0f , 0.0f )
	, m_vecRotation( 0.0f , 0.0f , 0.0f )

	, m_iIndex( 0 )

	, m_bDistCheck( true )
	, m_bAttachCharacter( true )
	, m_bCharAniSpeed( true )
	, m_bApplyScale( true )
	, m_bApplyScalePos( false )
{
}

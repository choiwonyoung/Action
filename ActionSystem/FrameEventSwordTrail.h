#pragma once

#include "FrameEvent.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// �˱� ǥ��
class CFrameEventSwordTrail : public CFrameEvent
{
public:
	CFrameEventSwordTrail();

	virtual CFrameEventType		GetType() const { return CFE_SwordTrail; }
	virtual int					GetEndFrame() const { return m_nEndFrame; }

	virtual bool				LoadXML( XMLNode *pXMLNode , List_PreloadString &lstPreloadEffect , List_PreloadString &lstPreloadSound , const char * pszClassName = NULL );
	virtual void				Dump( C9File * pFile , List_PreloadString & lstPreloadEffect , List_PreloadString &lstPreloadSound );

public:
	string						m_strBoneName;		// bone name
													//////////////////////////////////////////////////////////////////////////
													// ���� ����
	int							m_nEndFrame;
	int							m_nIndex;			// �˱� ��ȣ
	float						m_fStartPos;		// ���� ��ġ
	float						m_fEndPos;			// ���� ��ġ
	DWORD						m_Color;			// �˱� ����
	int							m_nLifeTime;		// ���� �ð�
	float						m_fHalfFrame;
	int							m_nFadeOutTime;		// ���̵� �ƿ� �ð�
	vector3						m_vecScale;			// ����/�߰�/�� ������ ��
	vector3						m_vecAxis;			// �˱� ��

	bool						m_bFadeOut;
	bool						m_bGlareEffect;
	bool						m_bUseLocalTrail;
	bool						m_bInvertColor;
	// ���� ���� ��
	//////////////////////////////////////////////////////////////////////////
};

inline CFrameEventSwordTrail::CFrameEventSwordTrail()
	: CFrameEvent()

	, m_strBoneName( "Bip01 Weapon1" )

	, m_nEndFrame( 0 )
	, m_nIndex( 0 )
	, m_fStartPos( 0.0f )
	, m_fEndPos( 0.0f )
	, m_Color( 0 )
	, m_nLifeTime( 0 )
	, m_fHalfFrame( -1.0f )
	, m_nFadeOutTime( 0 )
	, m_vecScale( 1.0f , 1.0f , 1.0f )
	, m_vecAxis( 0.0f , 1.0f , 0.0f )

	, m_bFadeOut( false )
	, m_bGlareEffect( true )
	, m_bUseLocalTrail( true )
	, m_bInvertColor( false )
{
}

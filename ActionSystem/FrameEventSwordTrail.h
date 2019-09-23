#pragma once

#include "FrameEvent.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 검기 표시
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
													// 묶음 저장
	int							m_nEndFrame;
	int							m_nIndex;			// 검기 번호
	float						m_fStartPos;		// 시작 위치
	float						m_fEndPos;			// 종료 위치
	DWORD						m_Color;			// 검기 색상
	int							m_nLifeTime;		// 지속 시간
	float						m_fHalfFrame;
	int							m_nFadeOutTime;		// 페이드 아웃 시간
	vector3						m_vecScale;			// 시작/중간/끝 스케일 값
	vector3						m_vecAxis;			// 검기 축

	bool						m_bFadeOut;
	bool						m_bGlareEffect;
	bool						m_bUseLocalTrail;
	bool						m_bInvertColor;
	// 묶음 저장 끝
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

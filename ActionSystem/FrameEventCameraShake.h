#pragma once

#include "FrameEvent.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 카메라 흔들기

class CFrameEventCameraShake : public CFrameEvent
{
public:
	CFrameEventCameraShake();

	virtual CFrameEventType		GetType() const { return CFE_CameraShake; }

	virtual bool				LoadXML( XMLNode *pXMLNode , List_PreloadString &lstPreloadEffect , List_PreloadString &lstPreloadSound , const char * pszClassName = NULL );
	virtual void				Dump( C9File * pFile , List_PreloadString & lstPreloadEffect , List_PreloadString &lstPreloadSound );

public:
	//////////////////////////////////////////////////////////////////////////
	// 묶음 저장
	float						m_fTime;					// 진동 시간
	float						m_fScale;					// 진동 크기
	float						m_fRadius;					// 진동 반경(캐릭터를 중심으로 진동을 느낄 수 있는 반경)
	bool						m_bDistanceAttenuation;		// 진동을 거리에 따라 감쇄 하는가?
	bool						m_bTimeAttenuation;			// 진동을 시간에 따라 감쇄 하는가?
	bool						m_bSure;					// 모든 PC가 느낄 수 있는 진동인가?
															// 묶음 저장 끝
															//////////////////////////////////////////////////////////////////////////
};

inline CFrameEventCameraShake::CFrameEventCameraShake()
	: CFrameEvent()
	, m_fTime( 0.0f )
	, m_fScale( 0.0f )
	, m_fRadius( 1000.0f )
	, m_bDistanceAttenuation( true )
	, m_bTimeAttenuation( true )
	, m_bSure( false )
{
}
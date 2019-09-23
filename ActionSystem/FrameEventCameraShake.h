#pragma once

#include "FrameEvent.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ī�޶� ����

class CFrameEventCameraShake : public CFrameEvent
{
public:
	CFrameEventCameraShake();

	virtual CFrameEventType		GetType() const { return CFE_CameraShake; }

	virtual bool				LoadXML( XMLNode *pXMLNode , List_PreloadString &lstPreloadEffect , List_PreloadString &lstPreloadSound , const char * pszClassName = NULL );
	virtual void				Dump( C9File * pFile , List_PreloadString & lstPreloadEffect , List_PreloadString &lstPreloadSound );

public:
	//////////////////////////////////////////////////////////////////////////
	// ���� ����
	float						m_fTime;					// ���� �ð�
	float						m_fScale;					// ���� ũ��
	float						m_fRadius;					// ���� �ݰ�(ĳ���͸� �߽����� ������ ���� �� �ִ� �ݰ�)
	bool						m_bDistanceAttenuation;		// ������ �Ÿ��� ���� ���� �ϴ°�?
	bool						m_bTimeAttenuation;			// ������ �ð��� ���� ���� �ϴ°�?
	bool						m_bSure;					// ��� PC�� ���� �� �ִ� �����ΰ�?
															// ���� ���� ��
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
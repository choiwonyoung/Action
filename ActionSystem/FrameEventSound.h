#pragma once
#include "FrameEvent.h"
#include "ActionData.h"
#include "ActionDataInfo.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 사운드
class CFrameEventSound : public CFrameEvent
{
public:
	CFrameEventSound( const CActionData & actionData );
	virtual ~CFrameEventSound() {};

	virtual CFrameEventType		GetType() const { return CFE_Sound; }

	virtual bool				LoadXML( XMLNode *pXMLNode , List_PreloadString &lstPreloadEffect , List_PreloadString &lstPreloadSound , const char * pszClassName = NULL );
	virtual void				Dump( C9File * pFile , List_PreloadString & lstPreloadEffect , List_PreloadString &lstPreloadSound );
	virtual void 				CopyActionValue( CFrameEvent *pFrameEvent , int iLevel );

public:
	vector< string >			m_lstSoundFile;
	string						m_strBoneName;				// 본 이름

	//////////////////////////////////////////////////////////////////////////
	// 묶음 저장
	float						m_fVolume;
	int							m_iLoopNum;
	float						m_fMinDistance;
	float						m_fMaxDistance;
	bool						m_bIs2DSound;
	bool						m_bAttachBone;
	// 묶음 저장 끝
	//////////////////////////////////////////////////////////////////////////
};

inline CFrameEventSound::CFrameEventSound( const CActionData& actionData )
: CFrameEvent()
, m_lstSoundFile()
, m_strBoneName( "" )

, m_fVolume( 0.7f )
, m_iLoopNum( 0 )
, m_fMinDistance( actionData.m_ActionDataInfoList[0]->m_fSoundMinDistance )
, m_fMaxDistance( actionData.m_ActionDataInfoList[0]->m_fSoundMaxDistance )
, m_bIs2DSound( false )
, m_bAttachBone( false )
{
}
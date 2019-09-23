#pragma once

#include "FrameEventAttackNormal.h"
#include "ActionContantable.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
class CActionData;
class CFrameEventAttackRange : public CFrameEventAttackNormal
{
public:
	CFrameEventAttackRange( const CActionData & actionData );

	virtual CFrameEventType		GetType() const { return CFE_AttackRange; }
	virtual int					GetEndFrame() const { return m_nEndFrame; }

	virtual bool				LoadXML( XMLNode *pXMLNode , List_PreloadString &lstPreloadEffect , List_PreloadString &lstPreloadSound , const char * pszClassName = NULL );
	virtual void				Dump( C9File * pFile , List_PreloadString & lstPreloadEffect , List_PreloadString &lstPreloadSound );

public:
	int							m_nEndFrame;
};

inline CFrameEventAttackRange::CFrameEventAttackRange( const CActionData & actionData )
	: CFrameEventAttackNormal( actionData )

	, m_nEndFrame( 0 )
{
}
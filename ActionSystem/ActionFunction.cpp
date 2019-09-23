#include "stdafx.h"
#include "ActionFunction.h"
#include "FrameEvent.h"
#include "ActionBranch.h"

CActionFunction::CActionFunction()
: m_strName( "" )
, m_dwNameHashCode( 0 )
, m_lstBranch()
, m_lstFrameEvent()
{
}

CActionFunction::~CActionFunction()
{
	RSAFE_DELETE_VECTOR( m_lstBranch );
	RSAFE_DELETE_VECTOR( m_lstFrameEvent );
}

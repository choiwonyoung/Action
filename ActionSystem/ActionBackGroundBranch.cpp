#include "stdafx.h"
#include "ActionBackGroundBranch.h"


CActionBackGroundBranch::CActionBackGroundBranch()
{
	m_bIsBackGroundBranch = true;
}


bool CActionBackGroundBranch::LoadXML( XMLNode *pXMLNode )
{
	__super::LoadXML( pXMLNode );
	return true;
}
void CActionBackGroundBranch::Dump( C9File * pFile )
{
	__super::Dump( pFile );

}

void CActionBackGroundBranch::CopyActionValue( CActionBackGroundBranch *pActionBackGroundBranch , int iLevel )
{
	__super::CopyActionValue( pActionBackGroundBranch , iLevel );
}
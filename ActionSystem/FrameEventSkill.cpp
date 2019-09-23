#include "stdafx.h"
#include "FrameEventSkill.h"

#include "FrameEventAttackNormal.h"

bool CFrameEventSkill::LoadXML( XMLNode *pXMLNode , List_PreloadString &lstPreloadEffect , List_PreloadString &lstPreloadSound , const char * pszClassName /*= NULL */ )
{
	if( !CFrameEvent::LoadXML( pXMLNode , lstPreloadEffect , lstPreloadSound , pszClassName ? pszClassName : "C9FrameEventSkill" ) )
		return false;

	string strAttr;
	if( pXMLNode->GetAttr( "SkillTypeKey" , strAttr ) )
	{
		CFrameEventAttackNormal::LoadSkillKey( strAttr , m_iUseMonsterSkillkey , m_dwSkillTypeKey );
	}
	pXMLNode->GetAttrBool( "TargetSelf" , m_bTargetSelf );
	pXMLNode->GetAttrBool( "TargetParent" , m_bTargetParent );
	pXMLNode->GetAttrBool( "CheckSkill" , m_bCheckSkill );
	m_eTargetType = ::StringToSkillTargetType( pXMLNode->GetAttr( "TargetType" ).c_str() );
	pXMLNode->GetAttrFloat( "Range" , m_fRange );

	return true;
}

void CFrameEventSkill::Dump( C9File * pFile , List_PreloadString & lstPreloadEffect , List_PreloadString &lstPreloadSound )
{
	CFrameEvent::Dump( pFile , lstPreloadEffect , lstPreloadSound );

	static const size_t _sizeOfData = C9_SIZE_OF_BETWEEN_VALUE( m_dwSkillTypeKey , m_bCheckSkill );

	if( pFile->IsSave() )
	{
		pFile->WriteData_SizeT( &m_dwSkillTypeKey , _sizeOfData );
	}
	else
	{
		pFile->ReadData_SizeT( &m_dwSkillTypeKey , _sizeOfData );
	}
}

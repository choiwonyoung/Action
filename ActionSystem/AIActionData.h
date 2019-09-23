#pragma once

#include "ActionData.h"


#define GET_PARAM_VALUE(name, strMessage)										\
	if (pXMLNode->GetAttr( name, strTemp ) == false)							\
	{																			\
																				\
		return false;															\
	}																			\
	if (pActionData->GetParamValue( strTemp.c_str(), iValue ) == false)			\
	{																			\
		return false;															\
	}																			\

struct CBoneLinkedAIValue
{
	DWORD dwBoneHash;
	DWORD dwAIValueNameHahs;
};


struct CValueParam;
class CAIActionChart;
class CAIActionData : public CActionData
{
public:
	struct CAIOrder
	{
		string	strName;
		string	strAction;
		ULONG	actionCode;

		CAIOrder();
		void	Dump( C9File * pFile );
	};

	// 클라 서버 간에 액션에 있는 스킬과 액션이 다르게 전달될 때 발생하는 문제를 해결 하기 위한 정보 구조체
	struct UseActionTimer
	{
		DWORD	m_dwActionCode;
		DWORD	m_dwSkillKey;
		int		m_iUseSkillIndex;
		UseActionTimer() :m_dwActionCode( 0 ) , m_dwSkillKey( 0 ) , m_iUseSkillIndex( 0 ) {}
		~UseActionTimer() {}
		UseActionTimer( DWORD dwAction , DWORD dwSkilkey , int iIndex ) :m_dwActionCode( dwAction ) , m_dwSkillKey( dwSkilkey ) , m_iUseSkillIndex( iIndex ) {}
	};

public:
	vector< CValueParam >			m_lstAIParam;
	vector< CValueParam >			m_lstAIValueList;
	vector< CAIOrder >				m_lstAIOrderParamList;
	vector< CAIActionChart* >		m_lstAIActionChart;
	vector< CBoneLinkedAIValue >	m_lstAIBoneLinkedAIValue;

	
	std::map< DWORD , vector<UseActionTimer> >	
									m_mapActionTimer;
	vector<DWORD>					m_lstAISocialActionCode;
public:
	CAIActionData();
	~CAIActionData();


	bool							LoadXML( const char *pSzFileName );

	virtual bool					Dump(C9File *pFile);

	void							SetAiActionChartList( HashMap_AIActionList &aiActionChartList , const DWORD dwActionIndexHashCode , bool isPvPMapAction , const DWORD dwPVPActionIndexHashCode = 0 );
	bool							LoadAIActionChart( XMLNode * pRootNode );

	void							InitPlayerValue(hash_map<DWORD, int>& mapPlayerValue);
	bool							GetParamValue(const char * pszTemp, int & iValue);
	void							InitAIValue( hash_map<DWORD, int> &aiValuList, hash_map<DWORD, DWORD> &aiDBoneAIValueList );	

private:
	void							_LoadXML_BaseInfo( XMLNode * pRootNode );

	void							_LoadXML_SocialActionCode( XMLNode * pAIBaseNode );
	void							_LoadXML_UseActionTimer( XMLNode * pAIBaseNode );	
	void							_LoadXML_Order( XMLNode * pAIBaseNode );
	void							_LoadXML_AIValue( XMLNode * pAIBaseNode );
	void							_LoadXML_Param( XMLNode * pAIBaseNode );
	bool							_LoadXML_AIActionChart( XMLNode * pRootNode );



};




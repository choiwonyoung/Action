#pragma once


class CActionBranch;
class CFrameEvent;
class CActionFunction
{
public:
	CActionFunction();
	~CActionFunction();

	// Contents
	vector<CActionBranch*>		m_lstBranch;
	vector<CFrameEvent*>		m_lstFrameEvent;

public:
	// Identity
	string						m_strName;				// ActionFunction Name
	DWORD						m_dwNameHashCode;		// ÇØ½¬°ª (ActionFunction Name)
};

typedef hash_map< DWORD , CActionFunction * >				HashMap_ActionFunction;
typedef hash_map< DWORD , CActionFunction * >::iterator		HashMap_ActionFunction_Iter;
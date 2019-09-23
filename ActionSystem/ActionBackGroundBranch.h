#pragma once

#pragma pack(push, 1)

#include "ActionBranch.h"

class CActionBackGroundBranch : public CActionBranch
{
public:

	CActionBackGroundBranch();

	virtual bool						LoadXML( XMLNode *pXMLNode );
	virtual void						Dump( C9File * pFile );

	void								CopyActionValue( CActionBackGroundBranch *pActionBackGroundBranch , int iLevel );
};
#pragma pack(pop)



// Console.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../ActionSystem/ActionData.h"

int main()
{
	CActionData aData;

	if( aData.LoadXML( "../Data/CharacterAction_Fighter.XMA" ) == false )
	{
		printf( "Load Failed\n" );		
	}
	else
		printf( "Load Successed\n" );

	system("pause");

    return 0;
}


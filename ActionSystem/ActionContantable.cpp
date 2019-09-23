#include "stdafx.h"
#include "ActionContantable.h"

namespace Action
{	
	// Hash 값 비교가 필요한 것들은 이곳에 추가....
	const DWORD C9_CRC_CODE_ACTION_None						= CCrc32Static::StringCrc32( "None" );
	const DWORD C9_CRC_CODE_ACTION_Start_Action				= CCrc32Static::StringCrc32( "Start_Action" );
	const DWORD C9_CRC_CODE_ACTION_WAIT						= CCrc32Static::StringCrc32( "WAIT" );
	const DWORD C9_CRC_CODE_ACTION_WAIT_BATTLE				= CCrc32Static::StringCrc32( "WAIT_BATTLE" );

	const DWORD C9_CRC_CODE_ACTION_SUMMON					= CCrc32Static::StringCrc32( "SummonAction" );
	const DWORD C9_CRC_CODE_ACTION_DAMAGE_GUARDCRASH		= CCrc32Static::StringCrc32( "DAMAGE_GUARDCRASH" );
	const DWORD C9_CRC_CODE_ACTION_SUICIDE_DEAD				= CCrc32Static::StringCrc32( "SUICIDE_DEAD" );
	const DWORD C9_CRC_CODE_ACTION_STAND_UP					= CCrc32Static::StringCrc32( "STAND_UP" );
	const DWORD C9_CRC_CODE_ACTION_STAND_UP2				= CCrc32Static::StringCrc32( "STAND_UP2" );
	const DWORD C9_CRC_CODE_ACTION_STUN						= CCrc32Static::StringCrc32( "STUN" );
	const DWORD C9_CRC_CODE_ACTION_DEAD_DOWN				= CCrc32Static::StringCrc32( "DEAD_DOWN" );
	const DWORD C9_CRC_CODE_ACTION_DEAD_END					= CCrc32Static::StringCrc32( "DEAD_END" );
	const DWORD C9_CRC_CODE_ACTION_DEAD_ACTION				= CCrc32Static::StringCrc32( "DEAD_ACTION" );
	const DWORD C9_CRC_CODE_ACTION_BOUND_DOWN				= CCrc32Static::StringCrc32( "BOUND_DOWN" );
	const DWORD C9_CRC_CODE_ACTION_Revive_Action			= CCrc32Static::StringCrc32( "Revive_Action" );
	const DWORD C9_CRC_CODE_ACTION_CATCH_FAILED				= CCrc32Static::StringCrc32( "CATCH_FAILED" );
	const DWORD C9_CRC_CODE_ACTION_LEVEL_UP					= CCrc32Static::StringCrc32( "LEVEL_UP" );
	const DWORD C9_CRC_CODE_ACTION_CLASSCHANGE				= CCrc32Static::StringCrc32( "CLASSCHANGE" );
	const DWORD C9_CRC_CODE_ACTION_PICK_ITEM				= CCrc32Static::StringCrc32( "PICK_ITEM" );
	const DWORD C9_CRC_CODE_ACTION_EVENT_ACTION				= CCrc32Static::StringCrc32( "EVENT_ACTION" );
	
	const DWORD C9_CRC_CODE_ACTION_RUN						= CCrc32Static::StringCrc32( "RUN" );
	const DWORD C9_CRC_CODE_ACTION_WALKLEFT					= CCrc32Static::StringCrc32( "WALKLEFT" );
	const DWORD C9_CRC_CODE_ACTION_WALKRIGHT				= CCrc32Static::StringCrc32( "WALKRIGHT" );
	const DWORD C9_CRC_CODE_ACTION_WALKBACK					= CCrc32Static::StringCrc32( "WALKBACK" );
	const DWORD C9_CRC_CODE_ACTION_MOUSE_RUN				= CCrc32Static::StringCrc32( "MOUSE_RUN" );

	const DWORD C9_CRC_CODE_ACTION_Move_Front				= CCrc32Static::StringCrc32( "Move_Front" );
	const DWORD C9_CRC_CODE_ACTION_Move_Left				= CCrc32Static::StringCrc32( "Move_Left" );
	const DWORD C9_CRC_CODE_ACTION_Move_Right				= CCrc32Static::StringCrc32( "Move_Right" );
	const DWORD C9_CRC_CODE_ACTION_Move_Back				= CCrc32Static::StringCrc32( "Move_Back" );

	const DWORD C9_CRC_CODE_ACTION_JUMP_UP					= CCrc32Static::StringCrc32( "JUMP_UP" );
	const DWORD C9_CRC_CODE_ACTION_JUMP_A					= CCrc32Static::StringCrc32( "JUMP_A" );
	const DWORD C9_CRC_CODE_ACTION_JUMP_B					= CCrc32Static::StringCrc32( "JUMP_B" );
	const DWORD C9_CRC_CODE_ACTION_JUMP_C					= CCrc32Static::StringCrc32( "JUMP_C" );

	const DWORD C9_CRC_CODE_ACTION_JUMP_FALL				= CCrc32Static::StringCrc32( "JUMP_FALL" );
	const DWORD C9_CRC_CODE_ACTION_JUMP_FALL_FRONT			= CCrc32Static::StringCrc32( "JUMP_FALL_FRONT" );
	const DWORD C9_CRC_CODE_ACTION_JUMP_FALL_LEFT			= CCrc32Static::StringCrc32( "JUMP_FALL_LEFT" );
	const DWORD C9_CRC_CODE_ACTION_JUMP_FALL_RIGHT			= CCrc32Static::StringCrc32( "JUMP_FALL_RIGHT" );
	const DWORD C9_CRC_CODE_ACTION_JUMP_FALL_BACK			= CCrc32Static::StringCrc32( "JUMP_FALL_BACK" );

	const DWORD C9_CRC_CODE_ACTION_DAMAGE_D					= CCrc32Static::StringCrc32( "DAMAGE_D" );
	const DWORD C9_CRC_CODE_ACTION_DAMAGE_L					= CCrc32Static::StringCrc32( "DAMAGE_L" );
	const DWORD C9_CRC_CODE_ACTION_DAMAGE_R					= CCrc32Static::StringCrc32( "DAMAGE_R" );
	const DWORD C9_CRC_CODE_ACTION_DAMAGE_U					= CCrc32Static::StringCrc32( "DAMAGE_U" );
	const DWORD C9_CRC_CODE_ACTION_DAMAGE_CATCH_ME			= CCrc32Static::StringCrc32( "DAMAGE_CATCH_ME" );
	const DWORD C9_CRC_CODE_ACTION_DOWN_DAMAGE				= CCrc32Static::StringCrc32( "DOWN_DAMAGE" );
	const DWORD C9_CRC_CODE_ACTION_DAMAGE_RIGID				= CCrc32Static::StringCrc32( "DAMAGE_RIGID" );
	const DWORD C9_CRC_CODE_ACTION_DOWN_A					= CCrc32Static::StringCrc32( "DOWN_A" );
	const DWORD C9_CRC_CODE_ACTION_DOWN2_A					= CCrc32Static::StringCrc32( "DOWN2_A" );

	const DWORD C9_CRC_CODE_ACTION_DAMAGE_THROW_A			= CCrc32Static::StringCrc32( "DAMAGE_THROW_A" );
	const DWORD C9_CRC_CODE_ACTION_DAMAGE_THROW_B			= CCrc32Static::StringCrc32( "DAMAGE_THROW_B" );
	const DWORD C9_CRC_CODE_ACTION_DAMAGE_THROW_C			= CCrc32Static::StringCrc32( "DAMAGE_THROW_C" );
	const DWORD C9_CRC_CODE_ACTION_DAMAGE_THROW2_A			= CCrc32Static::StringCrc32( "DAMAGE_THROW2_A" );
	const DWORD C9_CRC_CODE_ACTION_DAMAGE_THROW2_B			= CCrc32Static::StringCrc32( "DAMAGE_THROW2_B" );
	const DWORD C9_CRC_CODE_ACTION_DAMAGE_THROW2_C			= CCrc32Static::StringCrc32( "DAMAGE_THROW2_C" );
	const DWORD C9_CRC_CODE_ACTION_DAMAGE_THROW3_A			= CCrc32Static::StringCrc32( "DAMAGE_THROW3_A" );
	const DWORD C9_CRC_CODE_ACTION_DAMAGE_THROW3_B			= CCrc32Static::StringCrc32( "DAMAGE_THROW3_B" );
	const DWORD C9_CRC_CODE_ACTION_DAMAGE_THROW3_C			= CCrc32Static::StringCrc32( "DAMAGE_THROW3_C" );
	
	const DWORD C9_CRC_CODE_ACTION_DAMAGE_D_STANCE2			= CCrc32Static::StringCrc32( "DAMAGE_D_STANCE2" );
	const DWORD C9_CRC_CODE_ACTION_DAMAGE_L_STANCE2			= CCrc32Static::StringCrc32( "DAMAGE_L_STANCE2" );
	const DWORD C9_CRC_CODE_ACTION_DAMAGE_R_STANCE2			= CCrc32Static::StringCrc32( "DAMAGE_R_STANCE2" );
	const DWORD C9_CRC_CODE_ACTION_DAMAGE_U_STANCE2			= CCrc32Static::StringCrc32( "DAMAGE_U_STANCE2" );
	const DWORD C9_CRC_CODE_ACTION_DAMAGE_CATCH_ME_STANCE2	= CCrc32Static::StringCrc32( "DAMAGE_CATCH_ME_STANCE2" );
	const DWORD C9_CRC_CODE_ACTION_DOWN_DAMAGE_STANCE2		= CCrc32Static::StringCrc32( "DOWN_DAMAGE_STANCE2" );
	const DWORD C9_CRC_CODE_ACTION_DAMAGE_RIGID_STANCE2		= CCrc32Static::StringCrc32( "DAMAGE_RIGID_STANCE2" );
	const DWORD C9_CRC_CODE_ACTION_DOWN_A_STANCE2			= CCrc32Static::StringCrc32( "DOWN_A_STANCE2" );
	const DWORD C9_CRC_CODE_ACTION_DOWN2_A_STANCE2			= CCrc32Static::StringCrc32( "DOWN2_A_STANCE2" );

	const DWORD C9_CRC_CODE_ACTION_DAMAGE_THROW_A_STANCE2	= CCrc32Static::StringCrc32( "DAMAGE_THROW_A_STANCE2" );
	const DWORD C9_CRC_CODE_ACTION_DAMAGE_THROW_B_STANCE2	= CCrc32Static::StringCrc32( "DAMAGE_THROW_B_STANCE2" );
	const DWORD C9_CRC_CODE_ACTION_DAMAGE_THROW_C_STANCE2	= CCrc32Static::StringCrc32( "DAMAGE_THROW_C_STANCE2" );
	const DWORD C9_CRC_CODE_ACTION_DAMAGE_THROW2_A_STANCE2	= CCrc32Static::StringCrc32( "DAMAGE_THROW2_A_STANCE2" );
	const DWORD C9_CRC_CODE_ACTION_DAMAGE_THROW2_B_STANCE2	= CCrc32Static::StringCrc32( "DAMAGE_THROW2_B_STANCE2" );
	const DWORD C9_CRC_CODE_ACTION_DAMAGE_THROW2_C_STANCE2	= CCrc32Static::StringCrc32( "DAMAGE_THROW2_C_STANCE2" );
	const DWORD C9_CRC_CODE_ACTION_DAMAGE_THROW3_A_STANCE2	= CCrc32Static::StringCrc32( "DAMAGE_THROW3_A_STANCE2" );
	const DWORD C9_CRC_CODE_ACTION_DAMAGE_THROW3_B_STANCE2	= CCrc32Static::StringCrc32( "DAMAGE_THROW3_B_STANCE2" );
	const DWORD C9_CRC_CODE_ACTION_DAMAGE_THROW3_C_STANCE2	= CCrc32Static::StringCrc32( "DAMAGE_THROW3_C_STANCE2" );

	const DWORD C9_CRC_CODE_ACTION_STAND_UP_STANCE2			= CCrc32Static::StringCrc32( "STAND_UP_STANCE2" );
	const DWORD C9_CRC_CODE_ACTION_STAND_UP2_STANCE2		= CCrc32Static::StringCrc32( "STAND_UP2_STANCE2" );

	const DWORD C9_CRC_CODE_AI_ACTION_ATTACK_NORMAL			= CCrc32Static::StringCrc32( "ATTACK_NORMAL" );
	const DWORD C9_CRC_CODE_AI_ACTION_DAMAGE				= CCrc32Static::StringCrc32( "DAMAGE" );
	const DWORD C9_CRC_CODE_AI_ACTION_FOLLOWPLAYER			= CCrc32Static::StringCrc32( "FOLLOWPLAYER" );

	const DWORD C9_CRC_CODE_PLAYERVALUE_HASH_CODE_STANCE	= CCrc32Static::StringCrc32( "Stance" );	

	const DWORD C9_CRC_CODE_ACTION_SWIM_RUN					= CCrc32Static::StringCrc32( "SWIM_RUN" );
	const DWORD C9_CRC_CODE_ACTION_AWAKEN_LEVEL_UP			= CCrc32Static::StringCrc32( "LEVEL_UP_AWAKEN" );	
	const DWORD C9_CRC_CODE_AI_ACTION_TELEPORT_TO_PC		= CCrc32Static::StringCrc32( "TELEPORT_TO_PC" );
	const DWORD C9_CRC_CODE_ACTION_PLAYEND_INIT				= CCrc32Static::StringCrc32( "END_INIT" );
	const DWORD C9_CRC_CODE_ACTION_FISHING_UNINSTALL		= CCrc32Static::StringCrc32( "Fishing_uninstall" );	



	string ActionString::ToUpper( string& str )
	{
		string strTemp = str;
		std::transform( strTemp.begin() , strTemp.end() , strTemp.begin() , ::toupper );

		return strTemp;
	}

	string ActionString::GetToken( string orig , int nToken , char* strSep /*= NULL*/ )
	{
		if( strSep == NULL )
		{
			strSep = " ,\t\n/";
		}

		char* pStrTemp = ( char* )( _alloca( ( orig.length() + 1 ) * sizeof( char ) ) );
		strcpy( pStrTemp , orig.c_str() );

		char* pTemp = ( char* )( _alloca( ( orig.length() + 1 ) * sizeof( char ) ) );
		char* pToken;

		strcpy( pTemp , orig.c_str() );

		char*  pNextToken = NULL;
		pToken = strtok_s( pTemp , strSep , &pNextToken );

		for( int cToken = 0; cToken < nToken; cToken++ )
		{
			pToken = strtok_s( NULL , strSep , &pNextToken );
			if( pToken == NULL )
			{
				return "";
			}
		}
		if( pToken == NULL )
			return "";

		return pToken;
	}

	bool ActionString::GetStrParam( const char* pStrString , int iIndex , char* pStrParam )
	{
		const char* pFinder = pStrString;
		int iCount = 0;
		bool bOpen = false;
		int iParam = 0;
		int i = 0;
		while( pFinder[i] != '\0' && iCount <= iIndex )
		{
			if( pFinder[i] == '"' )
			{
				bOpen = ( bOpen == false ) ? true : false;
			}
			else
			{
				if( bOpen == false && ( pFinder[i] == ' ' || pFinder[i] == '\t' ) )
				{
					iCount++;
				}
				else
				{
					if( iCount == iIndex )
						pStrParam[iParam++] = pFinder[i];
				}
			}
			i++;
		}
		pStrParam[iParam] = '\0';

		if( iParam == 0 )
			return false;

		return true;
	}

	void ActionString::BufferFree( void * pData )
	{
		free( pData );
	}
}


CValueParam::CValueParam()
: strName( "" )
, strIconName( "" )
, iValue( 1 )
, dwHash( 0 )
{
}

bool CValueParam::LoadXML( RXMLNode * pNode )
{
	if( pNode->GetAttr( "Name" , strName ) == false )
		return false;
	dwHash = CCrc32Static::StringCrc32( strName.c_str() );

	if( pNode->GetAttrInt( "Value" , iValue ) == false )
		return false;

	pNode->GetAttr( "IconName" , strIconName );

	return true;
}

void CValueParam::Dump( C9File * pFile )
{
	static const size_t sizeOfData = C9_SIZE_OF_BETWEEN_VALUE( iValue , dwHash );

	if( pFile->IsSave() )
	{
		pFile->WriteData( strName );
		pFile->WriteData( strIconName );

		pFile->WriteData_SizeT( &iValue , sizeOfData );
	}
	else
	{
		pFile->ReadData( strName );
		pFile->ReadData( strIconName );

		pFile->ReadData_SizeT( &iValue , sizeOfData );
	}
}

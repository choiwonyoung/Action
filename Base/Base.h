#pragma once
#include <set>

#define RSAFE_DELETE(p)       { if(p) { delete (p);     (p)=NULL; } }
#define RSAFE_DELETE_ARRAY(p) { if(p) { delete[] (p);   (p)=NULL; } }
#define RSAFE_RELEASE(p)      { if(p) { (p)->Release(); (p)=NULL; } }

#define RSAFE_DELETE_VECTOR(p) { if(!p.empty()) { for(UINT uiVecCount=0; uiVecCount<(UINT)p.size(); uiVecCount++) RSAFE_DELETE(p[uiVecCount]); p.resize(0); } }
#define RSAFE_DELETE_VECTOR_ARRAY(p) { if(!p.empty()) { for(UINT uiVecCount=0; uiVecCount<(UINT)p.size(); uiVecCount++) RSAFE_DELETE_ARRAY(p[uiVecCount]); p.resize(0); } }
#define RSAFE_DELETE_LIST(type, p) { if (!p.empty()) { for(list<type>::iterator listPos=p.begin(); listPos != p.end(); ++listPos) { RSAFE_DELETE(*listPos); } p.clear(); } }

#define UNUSED_ARG(x) x			// 컴파일 시 (/W4) warning 방지용..

#define SET_ATTR(baseAttr, setAttr) ((baseAttr) |= (setAttr))
#define RESET_ATTR(baseAttr, setAttr) ((baseAttr) &= ~(setAttr))
#define IS_ATTR(baseAttr, setAttr) (((baseAttr) & (setAttr)) ? true : false)
#define IS_ATTR_ALL(baseAttr, setAttr) ((((baseAttr) & (setAttr)) == (setAttr)) ? true: false)

//---------------------------------------------------------------------
#define GetStrFormat(buf, fmt)	\
	va_list args;\
	va_start(args, fmt);\
	int len = _vscprintf(fmt, args) + 1;\
	buf = static_cast<char *>(_alloca(len * sizeof(char)));\
	vsprintf_s(buf, len, fmt, args);

#define GetStrFormatW(buf, fmt)	\
	va_list args;\
	va_start(args, fmt);\
	int len = _vscwprintf(fmt, args) + 1;\
	buf = static_cast<wchar_t *>(_alloca(len * sizeof(wchar_t)));\
	vswprintf_s(buf, len, fmt, args);



//---------------------------------------------------------------------
class CUniToAnsi2
{
public:
	CUniToAnsi2( const wchar_t *pStrUni );;
	~CUniToAnsi2();
	operator char*( );

	char *m_pString;
};

#define UniToAnsi2(str) string(CUniToAnsi2(str)).c_str()

//---------------------------------------------------------------------
class CAnsiToUni2
{
public:
	CAnsiToUni2( const char *pStrAnsi );
	~CAnsiToUni2();
	operator wchar_t*( );

	wchar_t *m_pString;
};

#define AnsiToUni2(str) wstring(CAnsiToUni2(str)).c_str()

//---------------------------------------------------------------------
class CUTF8ToUni2
{
public:
	CUTF8ToUni2( const char *pStrAnsi );
	~CUTF8ToUni2();
	operator wchar_t*( );

	wchar_t *m_pString;
};


#define UTF8ToUni2(str) wstring(CUTF8ToUni2(str)).c_str()


//---------------------------------------------------------------------
typedef	std::set< std::string > Set_String;
struct List_PreloadString
{
	Set_String						m_PreloadList;
	void AddStringLower( const char * pStringName )
	{
		//확장자,점까지 4자 이하면 잘못된 파일이름
		if( strlen( pStringName ) < 5 )
			return;

		char strLower[MAX_PATH * 2];
		strcpy_s( strLower , _countof( strLower ) , pStringName );
		_strlwr_s( strLower , _countof( strLower ) );
		m_PreloadList.insert( strLower );
	}
};

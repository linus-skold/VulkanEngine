#ifndef DL_ASSERT_HEADER
#define DL_ASSERT_HEADER

#include <stdlib.h>
#include <crtdbg.h>

#include "Debug.h"
#include <crtdefs.h>

#ifdef __cplusplus
extern "C"
{
#endif

	_CRTIMP void __cdecl _wassert( _In_z_ const wchar_t* _Message, _In_z_ const wchar_t* _File, _In_ unsigned _Line );

#ifdef __cplusplus
}
#endif

#ifdef assert
#undef assert
#endif
#ifdef NDEBUG
#define assert( x ) ( (void)0 )
#else

#define assert( _Expression )            \
	if( !( _Expression ) )               \
	{                                    \
		ASSERT_OVERRIDE( #_Expression ); \
	}
#endif

/*

#undef  assert

#ifdef  NDEBUG

#define assert(_Expression)     ((void)0)

#else

#ifdef  __cplusplus
extern "C" {
#endif

_CRTIMP void __cdecl _wassert(_In_z_ const wchar_t * _Message, _In_z_ const wchar_t *_File, _In_ unsigned _Line);

#ifdef  __cplusplus
}
#endif

#define assert(_Expression) (void)( (!!(_Expression)) || (_wassert(_CRT_WIDE(#_Expression), _CRT_WIDE(__FILE__),
__LINE__), 0) )

#endif  /* NDEBUG */

#endif

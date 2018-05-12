/*
 * ctype.h
 *
 * Functions for character classification and conversion.
 *
 * $Id: ctype.h,v 6895efd6bc57 2017/01/29 10:09:49 keithmarshall $
 *
 * Written by Colin Peters <colin@bird.fu.is.saga-u.ac.jp>
 * Copyright (C) 1997-2008, 2016, 2017, MinGW.org Project
 *
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice, this permission notice, and the following
 * disclaimer shall be included in all copies or substantial portions of
 * the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OF OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 */
#ifndef _CTYPE_H
#pragma GCC system_header
#define _CTYPE_H

/* All MinGW headers must include <_mingw.h>
 */
#include <_mingw.h>

/* Although conflicting with both ISO-C and POSIX, Microsoft say that,
 * in addition to the single byte character classification API which is
 * properly declared here, this file should also declare elements of the
 * wide classification API, which is properly declared in <wctype.h>
 *
 * To avoid the burden of maintaining duplicate declarations in two
 * locations, we keep the wide character declarations where ISO-C and
 * POSIX say they belong, in <wctype.h>, while accommodating Microsoft
 * compatibility by providing for selective inclusion of the relevant
 * elements of it here.  (Note that we must do this early, because to
 * avoid duplication, we delegate the definition of common character
 * classification macros, with the exception of _LEADBYTE, which is
 * not required in both headers, to <wctype.h>; we use the quoted
 * form of inclusion here, to ensure that we get our own "wctype.h",
 * and not any predecessor which may have been insinuated into the
 * system include path, and which may interfere with our mechanism
 * for partial inclusion of shared header content).
 */
#define __CTYPE_H_SOURCED__
#include "wctype.h"

/* This is the one character classification macro, for which definition
 * is NOT delegated to <wctype.h>
 */
#define _LEADBYTE	0x8000

#ifndef RC_INVOKED

_BEGIN_C_DECLS

_CRTIMP __cdecl __MINGW_NOTHROW  int isalnum(int);
_CRTIMP __cdecl __MINGW_NOTHROW  int isalpha(int);
_CRTIMP __cdecl __MINGW_NOTHROW  int iscntrl(int);
_CRTIMP __cdecl __MINGW_NOTHROW  int isdigit(int);
_CRTIMP __cdecl __MINGW_NOTHROW  int isgraph(int);
_CRTIMP __cdecl __MINGW_NOTHROW  int islower(int);
_CRTIMP __cdecl __MINGW_NOTHROW  int isleadbyte (int);
_CRTIMP __cdecl __MINGW_NOTHROW  int isprint(int);
_CRTIMP __cdecl __MINGW_NOTHROW  int ispunct(int);
_CRTIMP __cdecl __MINGW_NOTHROW  int isspace(int);
_CRTIMP __cdecl __MINGW_NOTHROW  int isupper(int);
_CRTIMP __cdecl __MINGW_NOTHROW  int isxdigit(int);

#if _ISOC99_SOURCE
__cdecl __MINGW_NOTHROW  int isblank (int);
#endif

#ifndef __STRICT_ANSI__
_CRTIMP __cdecl __MINGW_NOTHROW  int _isctype (int, int);
#endif

/* These are ISO-C conforming functions, with correct checking of
 * argument; they are exported by MSVCRT.DLL, and by CRTDLL.DLL as
 * such, and are NOT simply old-name mapped variants; however...
 */
_CRTIMP __cdecl __MINGW_NOTHROW  int tolower (int);
_CRTIMP __cdecl __MINGW_NOTHROW  int toupper (int);

#ifndef	__STRICT_ANSI__
/* ...Microsoft's beloved underscore decorated variants are also
 * exported.  These are cheap non-standard versions: their return
 * values are undefined if the argument is not an ASCII character,
 * or is not of appropriate case for the requested conversion.
 *
 * Note that these appear to be approximately equivalent to POSIX
 * macros of the same names, (declared obsolescent in POSIX.1-2008),
 * but are implemented as DLL functions, rather than macros.
 */
_CRTIMP __cdecl __MINGW_NOTHROW  int _tolower (int);
_CRTIMP __cdecl __MINGW_NOTHROW  int _toupper (int);
#endif

#ifndef MB_CUR_MAX
/* FIXME: also defined in stdlib.h; should be factored into ONE
 * location ONLY, and included into the other.
 */
# ifdef __DECLSPEC_SUPPORTED
#  ifdef __MSVCRT__
#   define MB_CUR_MAX		 __mb_cur_max
    __MINGW_IMPORT int		 __mb_cur_max;

#  else	/* !__MSVCRT__ */
#   define MB_CUR_MAX		 __mb_cur_max_dll
    __MINGW_IMPORT int		 __mb_cur_max_dll;
#  endif	/* !__MSVCRT__ */

# else	/* !__DECLSPEC_SUPPORTED */
#  ifdef __MSVCRT__
#   define MB_CUR_MAX		(*_imp____mb_cur_max)
    extern int			 *_imp____mb_cur_max;

#  else	/* !__MSVCRT__ */
#   define MB_CUR_MAX		(*_imp____mb_cur_max_dll)
    extern int			 *_imp____mb_cur_max_dll;
#  endif /* !__MSVCRT__ */
# endif /*  __DECLSPEC_SUPPORTED */
#endif  /* ! MB_CUR_MAX */

#ifdef __DECLSPEC_SUPPORTED
# if __MSVCRT_VERSION__ <= __MSVCR70_DLL
  __MINGW_IMPORT unsigned short   _ctype[];
# endif

# ifdef __MSVCRT__
  __MINGW_IMPORT unsigned short  *_pctype;

# else	/* !__MSVCRT__ (implies CRTDLL) */
# define  _pctype _pctype_dll
  __MINGW_IMPORT unsigned short  *_pctype_dll;
# endif

#else	/* !__DECLSPEC_SUPPORTED */
# if __MSVCRT_VERSION__ <= __MSVCR70_DLL
# define _ctype 		(*_imp___ctype)
  extern unsigned short 	**_imp___ctype;
# endif

# ifdef __MSVCRT__
# define _pctype		(*_imp___pctype)
  extern unsigned short 	**_imp___pctype;

# else	/* !__MSVCRT__ (implies CRTDLL) */
# define _pctype		(*_imp___pctype_dll)
  extern unsigned short 	**_imp___pctype_dll;
# endif /* CRTDLL */
#endif	/* !__DECLSPEC_SUPPORTED */

/* Use inlines here rather than macros, because macros will upset
 * C++ usage (eg, ::isalnum), and so usually get undefined
 *
 * According to standard for SB chars, these function are defined only
 * for input values representable by unsigned char or EOF.
 * Thus, there is no range test.
 * This reproduces behaviour of MSVCRT.dll lib implemention for SB chars.
 *
 * If no MB char support is needed, these can be simplified even
 * more by command line define -DMB_CUR_MAX=1.  The compiler will then
 * optimise away the constant condition.
 */

#if !(defined (__NO_INLINE__)  || defined (__NO_CTYPE_INLINES) \
	|| defined (__STRICT_ANSI__))

/* Use simple lookup in single byte locales, else _isctype()
 */
#define __ISCTYPE(c, mask)  (MB_CUR_MAX == 1 ? (_pctype[c] & mask) : _isctype (c, mask))

__CRT_INLINE __cdecl __MINGW_NOTHROW  int isalnum (int c)
{ return __ISCTYPE(c, (_ALPHA|_DIGIT)); }

__CRT_INLINE __cdecl __MINGW_NOTHROW  int isalpha (int c)
{ return __ISCTYPE(c, _ALPHA); }

__CRT_INLINE __cdecl __MINGW_NOTHROW  int iscntrl (int c)
{ return __ISCTYPE(c, _CONTROL); }

__CRT_INLINE __cdecl __MINGW_NOTHROW  int isdigit (int c)
{ return __ISCTYPE(c, _DIGIT); }

__CRT_INLINE __cdecl __MINGW_NOTHROW  int isgraph (int c)
{ return __ISCTYPE(c, (_PUNCT|_ALPHA|_DIGIT)); }

__CRT_INLINE __cdecl __MINGW_NOTHROW  int islower (int c)
{ return __ISCTYPE(c, _LOWER); }

__CRT_INLINE __cdecl __MINGW_NOTHROW  int isprint (int c)
{ return __ISCTYPE(c, (_BLANK|_PUNCT|_ALPHA|_DIGIT)); }

__CRT_INLINE __cdecl __MINGW_NOTHROW  int ispunct (int c)
{ return __ISCTYPE(c, _PUNCT); }

__CRT_INLINE __cdecl __MINGW_NOTHROW  int isspace (int c)
{ return __ISCTYPE(c, _SPACE); }

__CRT_INLINE __cdecl __MINGW_NOTHROW  int isupper (int c)
{ return __ISCTYPE(c, _UPPER); }

__CRT_INLINE __cdecl __MINGW_NOTHROW  int isxdigit (int c)
{ return __ISCTYPE(c, _HEX); }

#if _ISOC99_SOURCE
__CRT_INLINE __cdecl __MINGW_NOTHROW  int isblank (int c)
{ return (__ISCTYPE(c, _BLANK) || c == '\t'); }
#endif

/* These reproduce the behaviour of their DLL exported namesakes,
 * and thus ARE the effective equivalents of the similarly named,
 * and now-obsolescent, POSIX macros.
 */
__CRT_INLINE __cdecl __MINGW_NOTHROW  int _tolower (int c)
{ return (c - 'A' + 'a'); }

__CRT_INLINE __cdecl __MINGW_NOTHROW  int _toupper (int c)
{ return (c - 'a' + 'A'); }

/* TODO: is it worth inlining ANSI tolower(), and toupper()?
 * Probably only if we only want C-locale.
 */
#endif /* _NO_CTYPE_INLINES */

__CRT_INLINE __cdecl __MINGW_NOTHROW  int isleadbyte (int c)
{ return (_pctype[(unsigned char)(c)] & _LEADBYTE); }

#ifndef	__STRICT_ANSI__
__cdecl __MINGW_NOTHROW  int __isascii (int);
__cdecl __MINGW_NOTHROW  int __toascii (int);
__cdecl __MINGW_NOTHROW  int __iscsymf (int);	/* Valid as first character in a C symbol */
__cdecl __MINGW_NOTHROW  int __iscsym (int);	/* Valid character in C symbol (after first) */

#if !(defined (__NO_INLINE__) || defined (__NO_CTYPE_INLINES))

__CRT_INLINE __cdecl __MINGW_NOTHROW  int __isascii (int c)
{ return ((c & ~0x7F) == 0); }

__CRT_INLINE __cdecl __MINGW_NOTHROW  int __toascii (int c)
{ return (c & 0x7F); }

__CRT_INLINE __cdecl __MINGW_NOTHROW  int __iscsymf (int c)
{ return (isalpha(c) || (c == '_')); }

__CRT_INLINE __cdecl __MINGW_NOTHROW  int __iscsym (int c)
{ return  (isalnum(c) || (c == '_')); }

#endif /* !__NO_CTYPE_INLINES */

#ifndef	_NO_OLDNAMES
/* Not _CRTIMP */
__cdecl __MINGW_NOTHROW  int isascii (int);
__cdecl __MINGW_NOTHROW  int toascii (int);
__cdecl __MINGW_NOTHROW  int iscsymf (int);
__cdecl __MINGW_NOTHROW  int iscsym (int);
#endif	/* !_NO_OLDNAMES */

#endif	/* !__STRICT_ANSI__ */

_END_C_DECLS

#endif	/* ! RC_INVOKED */

#undef __CTYPE_H_SOURCED__
#endif	/* !_CTYPE_H: $RCSfile: ctype.h,v $: end of file */

/*
 * wctype.h
 *
 * Functions for wide character classification and conversion.
 *
 * $Id: wctype.h,v 6895efd6bc57 2017/01/29 10:09:49 keithmarshall $
 *
 * Written by Mumit Khan <khan@xraylith.wisc.edu>
 * Copyright (C) 1999-2003, 2005-2007, 2016, 2017, MinGW.org Project
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
#ifndef _WCTYPE_H
#pragma GCC system_header

#ifndef __CTYPE_H_SOURCED__
/* Perversely, (since they provide <wctype.h> themselves), Microsoft
 * say that most of the definitions and declarations which follow are
 * provided by <ctype.h>, rather than here; (this conflicts with both
 * ISO-C and POSIX).  We prefer to provide them here, for ISO-C/POSIX
 * conformance, while also exposing them for selective inclusion by
 * <ctype.h>, to maintain Microsoft compatibility.
 *
 * We define the <wctype.h> multiple inclusion guard macro only when
 * <wctype.h> is included directly, NOT when included via <ctype.h>
 */
#define _WCTYPE_H

/* All MinGW headers must include <_mingw.h>; when sourced by <ctype.h>,
 * we may delegate that responsibility to it, but in the case of direct
 * inclusion, we must address it ourselves.
 */
#include <_mingw.h>
#endif

/* The following flags are used to tell iswctype() and _isctype() what
 * character classes are to be matched; (note that _BLANK will match for
 * SP and non-ASCII horizontal space chars -- e.g. for "no-break space",
 * 0xA0, in CP1250 -- but NOT for HT).
 *
 * These are defined such that they will be made visible by inclusion
 * of either <wctype.h> (this file), or <ctype.h>:
 */
#define _ALPHA		0x0103
#define _LOWER		0x0002
#define _UPPER		0x0001
#define _DIGIT		0x0004
#define _SPACE		0x0008		/* HT  LF  VT  FF  CR  SP */
#define _PUNCT		0x0010
#define _CONTROL	0x0020
#define _BLANK		0x0040
#define _HEX		0x0080

#ifndef RC_INVOKED

/* ISO-C and POSIX specify that <wctype.h> must define wint_t, wctype_t,
 * and the WEOF macro, (which also requires wchar_t), as they are defined
 * in <wchar.h>; since <wchar.h> gets wint_t, (and wchar_t), from <stddef.h>,
 * we do likewise here.  Furthermore, to maintain Microsoft compatibility,
 * we must also do this on behalf of <ctype.h>; however...
 */
#if !(defined _WCTYPE_H && defined _CTYPE_H)
/* ...we need not incur the overhead of doing it twice, when both <ctype.h>
 * and <wctype.h> have been included.
 */
#define __need_wint_t
#define __need_wchar_t
#include <stddef.h>

typedef wchar_t  wctype_t;
#define WEOF	(wchar_t)(0xffff)

_BEGIN_C_DECLS

/* Wide character classification functions.  In typically perverse
 * fashion, and contrary to both ISO-C and POSIX, Microsoft specify
 * that these should be declared in <ctype.h>; thus, to accommodate
 * this persersity, we make them visible here, irrespective of any
 * selective inclusion filter macro.
 */
_CRTIMP __cdecl __MINGW_NOTHROW  int iswalnum (wint_t);
_CRTIMP __cdecl __MINGW_NOTHROW  int iswalpha (wint_t);
_CRTIMP __cdecl __MINGW_NOTHROW  int iswascii (wint_t);
_CRTIMP __cdecl __MINGW_NOTHROW  int iswcntrl (wint_t);
_CRTIMP __cdecl __MINGW_NOTHROW  int iswctype (wint_t, wctype_t);
_CRTIMP __cdecl __MINGW_NOTHROW  int iswdigit (wint_t);
_CRTIMP __cdecl __MINGW_NOTHROW  int iswgraph (wint_t);
_CRTIMP __cdecl __MINGW_NOTHROW  int iswlower (wint_t);
_CRTIMP __cdecl __MINGW_NOTHROW  int iswprint (wint_t);
_CRTIMP __cdecl __MINGW_NOTHROW  int iswpunct (wint_t);
_CRTIMP __cdecl __MINGW_NOTHROW  int iswspace (wint_t);
_CRTIMP __cdecl __MINGW_NOTHROW  int iswupper (wint_t);
_CRTIMP __cdecl __MINGW_NOTHROW  int iswxdigit (wint_t);

__MINGW_ATTRIB_DEPRECATED
/* This function is exported by all versions of MSVCRT.DLL, (up to and
 * including that in Windows-7), and in all non-free counterparts up to
 * and including MSVCR120.DLL, but as of MSVC-2013, Microsoft declare
 * it to be obsolete.  DO NOT USE IT!  Use iswctype() instead.
 */
_CRTIMP __cdecl __MINGW_NOTHROW  int is_wctype (wint_t, wctype_t);

#if _ISOC99_SOURCE
__cdecl __MINGW_NOTHROW  int iswblank (wint_t);
#endif

/* Wide character case transliteration functions; the following conform
 * to the ISO-C and POSIX standard declarations; Microsoft, at one time,
 * specified both as taking a wchar_t argument, and returning a wchar_t
 * result, but now take a wint_t argument, and return int.
 */
_CRTIMP __cdecl __MINGW_NOTHROW  wint_t towlower (wint_t);
_CRTIMP __cdecl __MINGW_NOTHROW  wint_t towupper (wint_t);

#if !(defined __NO_INLINE__ || defined __NO_CTYPE_INLINES)
/* Provide inline alternatives to the DLL-exported isw*() functions.
 * Note that POSIX stipulates that these alternatives should be macros;
 * we prefer __CRT_INLINEs, (which GCC effectively treats as macros),
 * because they do not interfere with C++ namespace qualification.
 */
__CRT_INLINE __cdecl __MINGW_NOTHROW  int iswalnum (wint_t wc)
{ return (iswctype (wc, _ALPHA | _DIGIT)); }

__CRT_INLINE __cdecl __MINGW_NOTHROW  int iswalpha (wint_t wc)
{ return (iswctype (wc, _ALPHA )); }

__CRT_INLINE __cdecl __MINGW_NOTHROW  int iswascii (wint_t wc)
{ return ((wc & ~0x7F) == 0); }

__CRT_INLINE __cdecl __MINGW_NOTHROW  int iswcntrl (wint_t wc)
{ return (iswctype (wc, _CONTROL)); }

__CRT_INLINE __cdecl __MINGW_NOTHROW  int iswdigit (wint_t wc)
{ return (iswctype (wc, _DIGIT)); }

__CRT_INLINE __cdecl __MINGW_NOTHROW  int iswgraph (wint_t wc)
{ return (iswctype (wc, _PUNCT | _ALPHA | _DIGIT)); }

__CRT_INLINE __cdecl __MINGW_NOTHROW  int iswlower (wint_t wc)
{ return (iswctype (wc, _LOWER)); }

__CRT_INLINE __cdecl __MINGW_NOTHROW  int iswprint (wint_t wc)
{ return (iswctype (wc, _BLANK | _PUNCT | _ALPHA | _DIGIT)); }

__CRT_INLINE __cdecl __MINGW_NOTHROW  int iswpunct (wint_t wc)
{ return (iswctype (wc, _PUNCT)); }

__CRT_INLINE __cdecl __MINGW_NOTHROW  int iswspace (wint_t wc)
{ return (iswctype (wc, _SPACE)); }

__CRT_INLINE __cdecl __MINGW_NOTHROW  int iswupper (wint_t wc)
{ return (iswctype (wc, _UPPER)); }

__CRT_INLINE __cdecl __MINGW_NOTHROW  int iswxdigit (wint_t wc)
{ return (iswctype (wc, _HEX)); }

#if _ISOC99_SOURCE
__CRT_INLINE __cdecl __MINGW_NOTHROW  int iswblank (wint_t wc)
{ return (iswctype (wc, _BLANK) || wc == L'\t'); }
#endif
#endif	/* !__NO_CTYPE_INLINES */

_END_C_DECLS

#endif	/* !(_WCTYPE_H && _CTYPE_H) */

#ifdef _WCTYPE_H
/* Although Microsoft make most of the content, which ISO-C and POSIX say
 * should be in <wctype.h>, available through <ctype.h>, the declarations
 * in this section are exclusive to <wctype.h>
 */
typedef wchar_t  wctrans_t;

_BEGIN_C_DECLS

/* These are provided in libmingwex.a.  Note, that they are also exported
 * by the MS C++ runtime lib (MSVCP60.DLL).  The MSVCP60.DLL implementations
 * of wctrans and towctrans are not C99 compliant in that wctrans("tolower")
 * returns 0, while C99 specifies that a non-zero value should be returned
 * for a valid string descriptor.  If you want the MS behaviour (and you
 * have MSVCP60.DLL in your path) add -lmsvcp60 to your command line.
 */
__cdecl __MINGW_NOTHROW  wint_t towctrans (wint_t, wctrans_t);
__cdecl __MINGW_NOTHROW  wctrans_t wctrans (const char*);
__cdecl __MINGW_NOTHROW  wctype_t wctype (const char*);

_END_C_DECLS

#endif	/* _WCTYPE_H */
#endif	/* ! RC_INVOKED */
#endif	/* !_WCTYPE_H: $RCSfile: wctype.h,v $: end of file */

/*
 * wchar.h
 *
 * Declarations relating to support for wide characters; many are simply
 * inherited by (sub-optimal) inclusion of other header files.
 *
 * $Id: wchar.h,v ec519c2a99b3 2017/01/28 16:20:51 keithmarshall $
 *
 * Unattributed original source.
 * Adapted by Rob Savoye <rob@cygnus.com>
 * Copyright (C) 1997, 1999-2009, 2011, 2015, 2016, MinGW.org Project.
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
#ifndef _WCHAR_H
#pragma GCC system_header

/* This header declares prototypes for wchar_t string functions, as are
 * prescribed by ISO-C, but which MSVC also expects, (in contravention of
 * ISO-C prescriptions), to find in <string.h>.  To accommodate this MSVC
 * anomaly, we make provision for <string.h> to include a selected subset
 * of <wchar.h>; thus, we do not immediately define _WCHAR_T...
 */
#ifndef __STRING_H_SOURCED__
/* ...but defer it until we have confirmed that this is NOT inclusion for
 * only this subset of <wchar.h> declarations.
 */
#define _WCHAR_H

/* All MinGW headers are required to include <_mingw.h>; in the case of
 * selective inclusion by <string.h>, we expect it to have already done
 * so, but since that doesn't apply here, we must do it ourselves.
 */
#include <_mingw.h>

#ifndef __STRICT_ANSI__
 /* MSDN says that isw* char classifications appear in both <wchar.h>,
  * and in <wctype.h>.  Although these <wctype.h> classifications are as
  * prescribed by ISO-C, their exposure in <wchar.h> is not; nonetheless,
  * we replicate them here, for MSDN conformity.
  */
# include <wctype.h>

 /* This is also necessary, to support the non-ANSI wchar.h declarations
  * which MSDN identifies as being provided here.
  */
# include <sys/types.h>

#endif	/* !__STRICT_ANSI__ */

#define WCHAR_MIN	0
#define WCHAR_MAX	0xffff

#define WEOF		(wchar_t)(0xffff)

#ifndef RC_INVOKED
#define __WCHAR_H_SOURCED__
/* ISO-C, POSIX, and Microsoft specify an overlap of content between
 * <wchar.h> and other system header files; by inclusion of such other
 * headers within this "__WCHAR_H_SOURCED__" scope, we may selectively
 * retrieve the overlapping content, without requiring duplication of
 * that content here; thus, from...
 */
#include "stdio.h"
/* ...we obtain (possibly indirect) definitions and declarations for:
 *
 *  macros  NULL, FILENAME_MAX
 *  types   size_t, wchar_t, wint_t, va_list (a.k.a. __VALIST), FILE
 *  types   ssize_t, off_t, __off64_t, (conditionally, as needed)
 *
 *  int     fwprintf (FILE *, const wchar_t *, ...);
 *  int     wprintf (const wchar_t *, ...);
 *  int     vfwprintf (FILE *, const wchar_t *, __VALIST);
 *  int     vwprintf (const wchar_t *, __VALIST);
 *  int     snwprintf (wchar_t *, size_t, const wchar_t *, ...);
 *  int    _snwprintf (wchar_t *, size_t, const wchar_t *, ...);
 *  int    _vscwprintf (const wchar_t *, __VALIST);
 *  int    _vsnwprintf (wchar_t *, size_t, const wchar_t *, __VALIST);
 *  int     vsnwprintf (wchar_t *, size_t, const wchar_t *, __VALIST);
 *  int     fwscanf (FILE *, const wchar_t *, ...);
 *  int     wscanf (const wchar_t *, ...);
 *  int     swscanf (const wchar_t *, const wchar_t *, ...);
 *  int     vwscanf (const wchar_t *, __VALIST);
 *  int     vfwscanf (FILE *, const wchar_t *, __VALIST);
 *  int     vswscanf (const wchar_t *, const wchar_t *, __VALIST);
 *  wint_t  fgetwc (FILE *);
 *  wint_t  fputwc (wchar_t, FILE *);
 *  wint_t  ungetwc (wchar_t, FILE *);
 *
 * The following pair of Microsoft functions conflict with their
 * corresponding ISO-C prototypes; consequently they will not be
 * declared when "__STRICT_ANSI__" checking is in effect:
 *
 *  int  swprintf (wchar_t *, const wchar_t *, ...);
 *  int  vswprintf (wchar_t *, const wchar_t *, __VALIST);
 *
 * The following group of functions is specified by ISO-C, but
 * their Microsoft implementations are available only if use of
 * "__MSVCRT__" is specified:
 *
 *  wchar_t * fgetws (wchar_t *, int, FILE *);
 *  int       fputws (const wchar_t *, FILE *);
 *  wint_t    getwc (FILE *);
 *  wint_t    getwchar (void);
 *  wint_t    putwc (wint_t, FILE *);
 *  wint_t    putwchar (wint_t);
 *
 * The following group of functions is also dependent on use of
 * "__MSVCRT__"; however, these are Microsoft specific, so they
 * are not declared if "__STRICT_ANSI__" checking is specified:
 *
 *  wchar_t * _getws (wchar_t *);
 *  int       _putws (const wchar_t *);
 *  FILE    * _wfdopen (int, const wchar_t *);
 *  FILE    * _wfopen (const wchar_t *, const wchar_t *);
 *  FILE    * _wfreopen (const wchar_t *, const wchar_t *, FILE *);
 *  FILE    * _wfsopen (const wchar_t *, const wchar_t *, int);
 *  wchar_t * _wtmpnam (wchar_t *);
 *  wchar_t * _wtempnam (const wchar_t *, const wchar_t *);
 *  int       _wrename (const wchar_t *, const wchar_t *);
 *  int       _wremove (const wchar_t *);
 *  void      _wperror (const wchar_t *);
 *  FILE    * _wpopen (const wchar_t *, const wchar_t *);
 *
 *
 * In similar fashion, from...
 */
#include "stdlib.h"
/* ...we obtain prototypes for universally supported functions:
 *
 *  long wcstol (const wchar_t *, wchar_t **, int);
 *  unsigned long wcstoul (const wchar_t *, wchar_t **, int);
 *  double wcstod (const wchar_t *, wchar_t **);
 *
 * The following are Microsoft specific, and require MSCVRT.DLL,
 * or any of its non-free derivatives; they are not available to
 * applications which use CRTDLL.DLL:
 *
 *  wchar_t *_wgetenv (const wchar_t *);
 *  int _wputenv (const wchar_t *);
 *  void _wsearchenv (const wchar_t *, const wchar_t *, wchar_t *);
 *  int _wsystem (const wchar_t *);
 *  void _wmakepath (wchar_t *, const wchar_t *, const wchar_t *,
 *          const wchar_t *, const wchar_t *
 *        );
 *  void _wsplitpath (const wchar_t *, wchar_t *, wchar_t *,
 *          wchar_t *, wchar_t *
 *        );
 *  wchar_t *_wfullpath (wchar_t *, const wchar_t *, size_t);
 *
 * ...with this pair requiring either WinXP (or later), or one of
 * the non-free MSVC runtimes from MSVCR70.DLL onwards:
 *
 *  __int64 _wcstoi64 (const wchar_t *, wchar_t **, int);
 *  unsigned __int64 _wcstoui64 (const wchar_t *, wchar_t **, int);
 *
 *  ...and this pair requiring Win-Vista (or later), or a non-free
 *  MSVC runtime from MSVCR80.DLL onwards:
 *
 *  __int64 _wcstoi64_l (const wchar_t *, wchar_t **, int, _locale_t);
 *  unsigned __int64 _wcstoui64_l (const wchar_t *, wchar_t **,
 *          int, _locale_t);
 *        );
 *
 * ...while this pair are ISO-C99 standards, which are available
 * in libmingwex.a, but not in any version of MSVCRT.DLL, (nor in
 * any of its non-free derivatives prior to MSVCR120.DLL), nor in
 * CRTDLL.DLL:
 *
 *  float wcstof (const wchar_t *restrict, wchar_t **restrict);
 *  long double wcstold (const wchar_t *restrict, wchar_t **restrict);
 *
 *
 * while...
 */
#ifndef __STRICT_ANSI__
/* ...when NOT compiling with "__STRICT_ANSI__" conformity checking,
 * from...
 */
#include "direct.h"
/* ...we obtain prototypes for each of the following functions,
 * (none of which are available when using CRTDLL.DLL):
 *
 *  int _wchdir (const wchar_t *);
 *  wchar_t *_wgetcwd (wchar_t *, int);
 *  wchar_t *_wgetdcwd (int, wchar_t *, int);
 *  int _wmkdir (const wchar_t *);
 *  int _wrmdir (const wchar_t *);
 *
 *
 * while from...
 */
#include "sys/stat.h"
/* ...we obtain function prototypes, and all associated data type
 * definitions for this pair of actual functions, in all versions of
 * MSVCRT.DLL, and its non-free derivatives preceding MSVCR80.DLL, (or
 * inline replacement implementations for MSVCR80.DLL and later):
 *
 *  int _wstat (const wchar_t *, struct _stat *);
 *  int _wstati64 (const wchar_t *, struct _stati64 *);
 *
 * ...this additional actual function, available in MSVCRT.DLL from
 * Win2K onwards, or in non-free MSVCR61.DLL and again requiring an
 * inline replacement from MSVCR80.DLL onwards:
 *
 *  int _wstat64 (const wchar_t *, struct __stat64 *);
 *
 * ...and these actual functions, which are available only in non-free
 * MSVCR80.DLL, and its later derivatives:
 *
 *  int _wstat32 (const wchar_t *, struct __stat32 *);
 *  int _wstat32i64 (const wchar_t *, struct _stat32i64 *);
 *  int _wstat64i32 (const wchar_t *, struct _stat64i32 *);
 *
 *
 * and from...
 */
#include "io.h"
/* ...we obtain function prototypes for each of the following, which
 * are available in all versions of MSVCRT.DLL, (and all its non-free
 * derivatives), but are not supported by CRTDLL.DLL:
 *
 *  int _waccess (const wchar_t *, int);
 *  int _wchmod (const wchar_t *, int);
 *  int _wcreat (const wchar_t *, int);
 *  int _wopen (const wchar_t *, int, ...);
 *  int _wsopen (const wchar_t *, int, int, ...);
 *  int _wunlink (const wchar_t *);
 *  wchar_t *_wmktemp (wchar_t *);
 *
 * ...and also function prototypes and definitions of all associated
 * data types and manifest constants for the following, each of which
 * is physically implemented in all versions of MSVCRT.DLL, and in each
 * of its non-free variants prior to MSVCR80.DLL, or emulated by inline
 * replacement functions for MSVCR80.DLL and later:
 *
 *  intptr_t _wfindfirst (wchar_t *, struct _wfinddata_t *);
 *  int _wfindnext (intptr_t, struct _wfinddata_t *);
 *
 *  intptr_t _wfindfirsti64 (wchar_t *, struct _wfinddatai64_t *);
 *  int _wfindnexti64 (intptr_t, struct _wfinddatai64_t *);
 *
 * ...this additional pair of functions, available in all versions of
 * MSVCRT.DLL from Win2K, and non-free variants from MSVCR61.DLL:
 *
 *  intptr_t _wfindfirst64 (wchar_t *, struct __wfinddata64_t *);
 *  int _wfindnext64 (intptr_t, struct __wfinddata64_t *);
 *
 * ...and these, which are only available in the non-free run-times
 * from MSVCR80.DLL onwards:
 *
 *  intptr_t _wfindfirst32 (wchar_t *, struct _wfinddata32_t *);
 *  int _wfindnext32 (intptr_t, struct _wfinddata32_t *);
 *
 *  intptr_t _wfindfirst32i64 (wchar_t *, struct _wfinddata32i64_t *);
 *  int _wfindnext32i64 (intptr_t, struct _wfinddata32i64_t *);
 *
 *  intptr_t _wfindfirst64i32 (wchar_t *, struct _wfinddata64i32_t *);
 *  int _wfindnext64i32 (intptr_t, struct _wfinddata64i32_t *);
 *
 * Additionally, although Microsoft's <wchar.h> may not declare it,
 * this is required to complement all variants of the _wfindfirst()
 * and _wfindnext() API, so we also declare the prototype for:
 *
 *  int _findclose (intptr_t);
 */
#endif	/* !__STRICT_ANSI__ */

/* From...
 */
#include "time.h"
/* ...we always obtain an opaque forward declaration of:
 *
 *  struct tm
 *
 * ...and prototype declarations for the following ISO-C99 function,
 * (which is always provided):
 *
 *  size_t wcsftime (wchar_t *, size_t, const wchar_t *, const struct tm *);
 *
 * ...together with the following non-ISO-C functions, (which are
 * NOT exposed when "__STRICT_ANSI__" checking is enabled):
 *
 *  wchar_t *_wctime (const time_t *);
 *  wchar_t *_wasctime (const struct tm *);
 *  wchar_t *_wstrdate (wchar_t *);
 *  wchar_t *_wstrtime (wchar_t *);
 *
 * Of the preceding group, we also note that, while it remains in
 * all versions of MSVCRT.DLL, (using a strictly 32-bit data type
 * to represent its "time_t" argument), the _wctime() function is
 * NOT present in MSVCR80.DLL, and later versions of the non-free
 * MSVC runtime libraries, in which it is replaced by either of:
 *
 *  wchar_t *_wctime64 (const __time64_t *);
 *  wchar_t *_wctime32 (const __time32_t *);
 *
 * ...with the actual replacement being chosen at compile time, on
 * the basis of the user specified "_USE_32BIT_TIME_T" feature test
 * macro, (a Microsoft specific, brain damaged concept), which maps
 * _wctime() itself, as an in-line alias for its corresponding
 * replacement library function.
 *
 */
#ifndef __STRICT_ANSI__
/* Once again, when NOT compiling with "__STRICT_ANSI__" conformity
 * checking, from...
 */
#include "locale.h"
/* ...we obtain the declaration for:
 *
 *   wchar_t *_wsetlocale (int, const wchar_t *);
 *
 *
 * and from...
 */
#include "process.h"
/* ...we obtain function prototypes for:
 *
 *  intptr_t _wexecl (const wchar_t *, const wchar_t *, ...);
 *  intptr_t _wexecle (const wchar_t *, const wchar_t *, ...);
 *  intptr_t _wexeclp (const wchar_t *, const wchar_t *, ...);
 *  intptr_t _wexeclpe (const wchar_t *, const wchar_t *, ...);
 *
 *  intptr_t _wexecv (const wchar_t *, const wchar_t * const *);
 *  intptr_t _wexecve (
 *    const wchar_t *, const wchar_t * const *, const wchar_t * const *
 *   );
 *  intptr_t _wexecvp (const wchar_t *, const wchar_t * const *);
 *  intptr_t _wexecvpe (
 *    const wchar_t *, const wchar_t * const *, const wchar_t * const *
 *   );
 *
 *  intptr_t _wspawnl (int, const wchar_t *, const wchar_t *, ...);
 *  intptr_t _wspawnle (int, const wchar_t *, const wchar_t *, ...);
 *  intptr_t _wspawnlp (int, const wchar_t *, const wchar_t *, ...);
 *  intptr_t _wspawnlpe (int, const wchar_t *, const wchar_t *, ...);
 *
 *  intptr_t _wspawnv (int, const wchar_t *, const wchar_t * const *);
 *  intptr_t _wspawnve (
 *    int, const wchar_t *, const wchar_t * const *, const wchar_t * const *
 *   );
 *  intptr_t _wspawnvp (int, const wchar_t *, const wchar_t * const *);
 *  intptr_t _wspawnvpe (
 *    int, const wchar_t *, const wchar_t * const *, const wchar_t * const *
 *   );
 *
 */
#endif	/* !__STRICT_ANSI__ */

_BEGIN_C_DECLS

/* Wide character string functions must be specified here, as required
 * by the ISO-C Standard; however, MSVC contravenes this standard by also
 * requiring them to appear in <string.h>.  We declare them here, where
 * they rightfully belong, but we also arrange for them to be available
 * for selective inclusion by <string.h>; to facilitate this, we must
 * change the declarative condition...
 */
#endif	/* ! RC_INVOKED */
#endif	/* !__STRING_H_SOURCED__ */
#if ! defined RC_INVOKED
#if !(defined _WCHAR_H && (defined _STRING_H && ! defined __STRICT_ANSI__))
/* ...such that these declarations are exposed when either _WCHAR_H is defined,
 * or when _STRING_H is defined and __STRICT_ANSI__ is not, but NOT when BOTH of
 * these apply, since that indicates that this group of declarations has already
 * been processed, during partial inclusion of <wchar.h> by <string.h>, whereas
 * we are now including <wchar.h> in its own right.
 *
 *
 * Wide character versions of the ISO-C standard string functions.
 */
_CRTIMP __cdecl __MINGW_NOTHROW  wchar_t *wcscat (wchar_t *, const wchar_t *);
_CRTIMP __cdecl __MINGW_NOTHROW  wchar_t *wcschr (const wchar_t *, wchar_t);
_CRTIMP __cdecl __MINGW_NOTHROW  int wcscmp (const wchar_t *, const wchar_t *);
_CRTIMP __cdecl __MINGW_NOTHROW  int wcscoll (const wchar_t *, const wchar_t *);
_CRTIMP __cdecl __MINGW_NOTHROW  wchar_t *wcscpy (wchar_t *, const wchar_t *);
_CRTIMP __cdecl __MINGW_NOTHROW  size_t wcscspn (const wchar_t *, const wchar_t *);
_CRTIMP __cdecl __MINGW_NOTHROW  size_t wcslen (const wchar_t *);
_CRTIMP __cdecl __MINGW_NOTHROW  wchar_t *wcsncat (wchar_t *, const wchar_t *, size_t);
_CRTIMP __cdecl __MINGW_NOTHROW  int wcsncmp (const wchar_t *, const wchar_t *, size_t);
_CRTIMP __cdecl __MINGW_NOTHROW  wchar_t *wcsncpy (wchar_t *, const wchar_t *, size_t);
_CRTIMP __cdecl __MINGW_NOTHROW  wchar_t *wcspbrk (const wchar_t *, const wchar_t *);
_CRTIMP __cdecl __MINGW_NOTHROW  wchar_t *wcsrchr (const wchar_t *, wchar_t);
_CRTIMP __cdecl __MINGW_NOTHROW  size_t wcsspn (const wchar_t *, const wchar_t *);
_CRTIMP __cdecl __MINGW_NOTHROW  wchar_t *wcsstr (const wchar_t *, const wchar_t *);
_CRTIMP __cdecl __MINGW_NOTHROW  wchar_t *wcstok (wchar_t *, const wchar_t *);
_CRTIMP __cdecl __MINGW_NOTHROW  size_t wcsxfrm (wchar_t *, const wchar_t *, size_t);

#ifndef __STRICT_ANSI__
/* UTF-16LE versions of non-ANSI string functions provided by CRTDLL.DLL
 */
_CRTIMP __cdecl __MINGW_NOTHROW  wchar_t *_wcsdup (const wchar_t *);
_CRTIMP __cdecl __MINGW_NOTHROW  int _wcsicmp (const wchar_t *, const wchar_t *);
_CRTIMP __cdecl __MINGW_NOTHROW  int _wcsicoll (const wchar_t *, const wchar_t *);
_CRTIMP __cdecl __MINGW_NOTHROW  wchar_t *_wcslwr (wchar_t*);
_CRTIMP __cdecl __MINGW_NOTHROW  int _wcsnicmp (const wchar_t *, const wchar_t *, size_t);
_CRTIMP __cdecl __MINGW_NOTHROW  wchar_t *_wcsnset (wchar_t *, wchar_t, size_t);
_CRTIMP __cdecl __MINGW_NOTHROW  wchar_t *_wcsrev (wchar_t *);
_CRTIMP __cdecl __MINGW_NOTHROW  wchar_t *_wcsset (wchar_t *, wchar_t);
_CRTIMP __cdecl __MINGW_NOTHROW  wchar_t *_wcsupr (wchar_t *);

#ifdef __MSVCRT__
_CRTIMP __cdecl __MINGW_NOTHROW  int _wcsncoll (const wchar_t *, const wchar_t *, size_t);
_CRTIMP __cdecl __MINGW_NOTHROW  int _wcsnicoll (const wchar_t *, const wchar_t *, size_t);

/* A wide character counterpart to the strerror() API was introduced in
 * MSVCR70.DLL, and subsequently back-ported to MSVCRT.DLL in WinXP.
 */
#if __MSVCRT_VERSION__ >= __MSVCR70_DLL || NTDDI_VERSION >= NTDDI_WINXP
 /*
  * These are are the wide character counterparts to the strerror()
  * function itself, and the _strerror() function, respectively.
  */
_CRTIMP __cdecl __MINGW_NOTHROW  wchar_t *_wcserror (int);
_CRTIMP __cdecl __MINGW_NOTHROW  wchar_t *__wcserror (const wchar_t *);

#endif	/* MSVCR70.DLL || WinXP */
#endif	/* __MSVCRT__ */

/* MSVCRT.DLL provides neither _wcscmpi() nor wcscmpi(); the heritage
 * is uncertain, but for the convenience, (and portability), of legacy
 * applications which assume wcscmpi() should be available:
 */
#define _wcscmpi _wcsicmp
int __cdecl __MINGW_NOTHROW  wcscmpi (const wchar_t *, const wchar_t *);

#ifndef __NO_INLINE__
__CRT_ALIAS __JMPSTUB__(( FUNCTION = wcscmpi, REMAPPED = _wcsicmp ))
  int wcscmpi (const wchar_t *__ws1, const wchar_t *__ws2)
  { return _wcsicmp (__ws1, __ws2); }
#endif	/* __NO_INLINE__ */

#ifndef _NO_OLDNAMES
/* Older CRTDLL.DLL versions may have provided these alternatively named
 * functions; we continue to support them, via the OLDNAME libraries:
 */
_CRTIMP __cdecl __MINGW_NOTHROW  wchar_t *wcsdup (const wchar_t *);
_CRTIMP __cdecl __MINGW_NOTHROW  int wcsicmp (const wchar_t *, const wchar_t *);
_CRTIMP __cdecl __MINGW_NOTHROW  int wcsicoll (const wchar_t *, const wchar_t *);
_CRTIMP __cdecl __MINGW_NOTHROW  wchar_t *wcslwr (wchar_t *);
_CRTIMP __cdecl __MINGW_NOTHROW  int wcsnicmp (const wchar_t *, const wchar_t *, size_t);
_CRTIMP __cdecl __MINGW_NOTHROW  wchar_t *wcsnset (wchar_t *, wchar_t, size_t);
_CRTIMP __cdecl __MINGW_NOTHROW  wchar_t *wcsrev (wchar_t *);
_CRTIMP __cdecl __MINGW_NOTHROW  wchar_t *wcsset (wchar_t *, wchar_t);
_CRTIMP __cdecl __MINGW_NOTHROW  wchar_t *wcsupr (wchar_t *);

#endif	/* !_NO_OLDNAMES */
#endif	/* !__STRICT_ANSI__ */

#if _POSIX_C_SOURCE >= 200809L
#if __MSVCRT_VERSION__ >= __MSVCR80_DLL
/* MSVCR80.DLL adds a (mostly) POSIX.1-2008 conforming wcsnlen(); (it's
 * also available in MSVCRT.DLL from _WIN32_WINNT_VISTA onwards, but we
 * pretend otherwise, since recent GCC will try to use the function when
 * it can be found in libmsvcrt.a, so breaking it for use on WinXP and
 * earlier).
 */
#ifndef __STRICT_ANSI__   /* N.B.: this is not an ISO-C function */
_CRTIMP __cdecl __MINGW_NOTHROW  char *wcsnlen (const wchar_t *, size_t);
#endif

#else	/* MSVCRT.DLL || pre-MSVCR80.DLL */
/* Emulation, to support recent POSIX.1; we prefer this for ALL versions
 * of MSVCRT.DLL, (even those which already provide wcsnlen()); to avoid
 * the GCC breakage noted above.  (Note that we implement wcsnlen() with
 * the alternative external name, __mingw_wcsnlen() in libmingwex.a, to
 * avoid possible link time collision with MSVCR80.DLL's implementation,
 * then map this to wcsnlen() via a __CRT_ALIAS, with stubs designated
 * for linking from within the appropriate oldname libraries.
 */
extern size_t __mingw_wcsnlen (const wchar_t *, size_t);

__JMPSTUB__(( LIB=coldname; FUNCTION=wcsnlen ))
__CRT_ALIAS size_t wcsnlen (const wchar_t *__text, size_t __maxlen)
{ return __mingw_wcsnlen (__text, __maxlen); }

#endif	/* MSVCRT.DLL || pre-MSVCR80.DLL */
#endif	/* _POSIX_C_SOURCE >= 200809L */

/* This completes the set of declarations which are to be duplicated by
 * inclusion of <string.h>; revert the declarative condition, to make it
 * specific to <wchar.h> alone.
 */
#endif	/* !(_WCHAR_H && (_STRING_H && !__STRICT_ANSI__)) */
#endif	/* ! RC_INVOKED */

#if defined _WCHAR_H && ! defined RC_INVOKED
#ifndef __STRICT_ANSI__
typedef wchar_t  _Wint_t;
#endif

typedef int mbstate_t;

/* The following multi-byte character conversion functions are
 * implemented in libmingwex.a, (and maybe also in some non-free
 * Microsoft libraries, such as MSVCP60.DLL and later).
 */
__cdecl __MINGW_NOTHROW  wint_t btowc (int);
__cdecl __MINGW_NOTHROW  int wctob (wint_t);

__cdecl __MINGW_NOTHROW
size_t mbrlen (const char *__restrict__, size_t, mbstate_t *__restrict__);

__cdecl __MINGW_NOTHROW  size_t mbrtowc
(wchar_t *__restrict__, const char *__restrict__, size_t, mbstate_t *__restrict__);

__cdecl __MINGW_NOTHROW  size_t mbsrtowcs
(wchar_t *__restrict__, const char **__restrict__, size_t, mbstate_t *__restrict__);

__cdecl __MINGW_NOTHROW
size_t wcrtomb (char * __restrict__, wchar_t, mbstate_t *__restrict__);

__cdecl __MINGW_NOTHROW  size_t wcsrtombs
(char *__restrict__, const wchar_t **__restrict__, size_t, mbstate_t *__restrict__);

#if defined _ISOC99_SOURCE || defined __cplusplus
/* These ISO-C99 functions are implemented in libmingwex.a,
 * or, in some cases, as inline stubs; while provided as MinGW
 * extensions to support ISO-C99, they are also required by
 * GNU C++.
 */
__cdecl __MINGW_NOTHROW  int fwide (FILE *, int);
__cdecl __MINGW_NOTHROW  int mbsinit (const mbstate_t *);

#ifndef __NO_INLINE__
__CRT_INLINE __cdecl __MINGW_NOTHROW
int fwide (FILE *__UNUSED_PARAM(stream), int mode)
  { return mode; } /* Nothing to do  */

__CRT_INLINE __cdecl __MINGW_NOTHROW
int mbsinit (const mbstate_t *__UNUSED_PARAM(ps))
  { return 1; }
#endif

__cdecl __MINGW_NOTHROW  wchar_t *wmemset (wchar_t *, wchar_t, size_t);
__cdecl __MINGW_NOTHROW  wchar_t *wmemchr (const wchar_t *, wchar_t, size_t);

/* FIXME: what makes this so different from every other function
 * in this group?  Why is it not qualified with the __cdecl, and
 * __MINGW_NOTHROW attributes?
 */
int wmemcmp (const wchar_t *, const wchar_t *, size_t);

__cdecl __MINGW_NOTHROW
wchar_t *wmemcpy (wchar_t *__restrict__, const wchar_t *__restrict__, size_t);

__cdecl __MINGW_NOTHROW  wchar_t *wmemmove (wchar_t *, const wchar_t *, size_t);

__cdecl __MINGW_NOTHROW
long long wcstoll (const wchar_t *__restrict__, wchar_t **__restrict__, int);

__cdecl __MINGW_NOTHROW  unsigned long long wcstoull
(const wchar_t *__restrict__, wchar_t **__restrict__, int);
#endif /* _ISOC99_SOURCE */

_END_C_DECLS

#undef __WCHAR_H_SOURCED__
#endif	/* _WCHAR_H && ! RC_INVOKED */
#endif	/* !_WCHAR_H: $RCSfile: wchar.h,v $: end of file */

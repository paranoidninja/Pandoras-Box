/*
 * locale.h
 *
 * Functions and types for localization (ie. changing the appearance of
 * output based on the standards of a certain country, or region).
 *
 * $Id: locale.h,v a3059ad5ee79 2016/06/12 19:22:07 keithmarshall $
 *
 * Written by Colin Peters <colin@bird.fu.is.saga-u.ac.jp>
 * Copyright (C) 1997, 1999-2001, 2003, 2004, 2007, 2016, MinGW.org Project.
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
#ifndef	_LOCALE_H
#pragma GCC system_header

/* Some headers will include this file, just to acquire a globally
 * consistent definition for the opaque locale_t data object type; it
 * is only useful on Vista, or for users of non-free MSVCR80.DLL, (or
 * its later derivatives), so, when either of these is applicable,
 * ensure that we define it, (if we haven't done so already).
 */
#if ! defined __have_typedef_locale_t \
&& (__MSVCRT_VERSION__ >= __MSVCR80_DLL || _WIN32_WINNT >= _WIN32_WINNT_VISTA)
/*
 * FIXME: Do these actually have any value for Vista?  Although the Vista
 * release of MSVCRT.DLL exports several functions which require locale_t
 * parameters, it appears to lack any mechanism whereby an object of that
 * type might be created, or otherwise, a reference to such an object may
 * be acquired.
 */
typedef struct __mingw_opaque_locale_t  *_locale_t;
typedef struct __mingw_opaque_locale_t  * locale_t;

/* Set a (private) pre-processor flag, to indicate that these data types
 * have been defined; although GCC versions from 4.x onwards may accept
 * repeated (consistent) definitions, this flag gives us the facility to
 * avoid the overhead of repeatedly parsing this file, just to satisfy a
 * __need_locale_t request which has been satisfied already.
 */
#define __have_typedef_locale_t  1
#endif	/* !__have_typedef_locale_t */

/* When we are interested in more than just locale_t...
 */
#ifndef __need_locale_t
/* ...content from <locale.h> is selectively shared with <wchar.h>;
 * defer definition of the normal repeat inclusion guard, until...
 */
#ifndef __WCHAR_H_SOURCED__
 /* ...we have confirmed that this inclusion is NOT the <wchar.h>
  * selective request, or just a __need_locale_t request.
  */
#define	_LOCALE_H

/* All MinGW headers should include <_mingw.h>; do so only when NOT
 * sourced by <wchar.h>, (which should have included it already).
 */
#include <_mingw.h>

#define	LC_ALL		0
#define LC_COLLATE	1
#define LC_CTYPE	2
#define	LC_MONETARY	3
#define	LC_NUMERIC	4
#define	LC_TIME		5
#define	LC_MIN		LC_ALL
#define	LC_MAX		LC_TIME

#ifndef RC_INVOKED
/* Both ISO-C and POSIX stipulate that <locale.h> should reproduce the
 * definition of NULL, from <stddef.h>; although not required by either
 * standard, we also require wchar_t, to support our declaration of the
 * Microsoft specific _wsetlocale() function, below.
 */
#define __need_NULL
#define __need_wchar_t
#include <stddef.h>

struct lconv
{ /* The structure returned by the localeconv() function.
   *
   * AUTHOR'S NOTE:
   * I have tried to test this, but I am limited by my knowledge of
   * locale issues. The structure does not bomb if you look at the
   * values, and 'decimal_point' even seems to be correct, but the
   * rest of the values may, by default, not be particularly useful;
   * indeed, they may even be meaningless, and in no way related to
   * the international settings of the system.
   */
  char	*decimal_point;
  char	*thousands_sep;
  char	*grouping;
  char	*int_curr_symbol;
  char	*currency_symbol;
  char	*mon_decimal_point;
  char	*mon_thousands_sep;
  char	*mon_grouping;
  char	*positive_sign;
  char	*negative_sign;
  char	 int_frac_digits;
  char	 frac_digits;
  char	 p_cs_precedes;
  char	 p_sep_by_space;
  char	 n_cs_precedes;
  char	 n_sep_by_space;
  char	 p_sign_posn;
  char	 n_sign_posn;
};

#endif	/* ! RC_INVOKED */
#endif	/* !__WCHAR_H_SOURCED__ */

#ifndef RC_INVOKED

_BEGIN_C_DECLS

#ifdef _LOCALE_H
 /* The following pair of function prototypes are to be declared
  * only when including <locale.h> in its own right, (i.e. when NOT
  * sourced by <wchar.h>)...
  */
_CRTIMP __cdecl __MINGW_NOTHROW  char *setlocale (int, const char *);
_CRTIMP __cdecl __MINGW_NOTHROW  struct lconv *localeconv (void);

#endif
 /* ...whereas, this must be declared in either case; (note that it
  * not necessary to guard against a possible repeat declaration, as
  * the compiler should accept this, without complaint, provided any
  * prior declaration is consistent).
  */
_CRTIMP __cdecl __MINGW_NOTHROW  wchar_t *_wsetlocale (int, const wchar_t *);

#if __MSVCRT_VERSION__ >= __MSVCR80_DLL
/* The following are available to users of non-free MSVCR80.DLL, and
 * its later derivatives.  They are REQUIRED to create, or otherwise
 * acquire a reference to, a locale_t object; they SHOULD also have
 * been made available in MSVCRT.DLL, from Vista onwards, to support
 * the use of functions added in that release which require locale_t
 * parameters, but it seems that Microsoft, exhibiting their usual
 * ineptitude, have neglected that requirement.
 */
#ifdef _LOCALE_H
/* This triplet of functions are to be declared only when <locale.h>
 * is included directly, and so is parsed in full...
 */
_CRTIMP __cdecl __MINGW_NOTHROW  _locale_t _create_locale (int, const char *);
_CRTIMP __cdecl __MINGW_NOTHROW  _locale_t _get_current_locale (void);
_CRTIMP __cdecl __MINGW_NOTHROW   void     _free_locale (locale_t);

#endif
/* ...whereas, this is required both when included directly, and also
 * when indirectly included by <wchar.h>
 */
_CRTIMP __cdecl __MINGW_NOTHROW  _locale_t _wcreate_locale (int, const wchar_t *);

#endif	/* __MSVCRT_VERSION__ >= __MSVCR80_DLL */

_END_C_DECLS

#endif	/* ! RC_INVOKED */
#endif	/* !__need_locale_t */

/* We've already handled any pending __need_locale_t request; ensure
 * that we cancel it, so that any more comprehensive further request,
 * before _LOCALE_H is defined, will be handled appropriately.
 */
#undef	__need_locale_t

#endif  /* !_LOCALE_H: $RCSfile: locale.h,v $: end of file */

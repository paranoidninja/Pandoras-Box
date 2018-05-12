/*
 * stdlib.h
 *
 * ANSI/POSIX + Microsoft compatible standard library function prototypes,
 * associated macros, and manifest constant definitions.
 *
 * $Id: stdlib.h,v 2f3798017d64 2016/11/28 14:14:48 keithmarshall $
 *
 * Written by Colin Peters <colin@bird.fu.is.saga-u.ac.jp>
 * Copyright (C) 1997-2009, 2011, 2014-2016, MinGW.org Project.
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
#ifndef _STDLIB_H
#pragma GCC system_header

/* Some of the content of this header is made selectively accessible,
 * when indirectly included via <wchar.h>; only when we have established
 * that this inclusion is NOT via this selective method...
 */
#ifndef __WCHAR_H_SOURCED__
 /* ...do we define the repeat inclusion guard for <stdlib.h> itself.
  */
#define _STDLIB_H

/* All MinGW headers must include <_mingw.h>; if included via <wchar.h>,
 * we assume that this has been done already, otherwise we must attend to
 * it for <stdlib.h>.
 */
#include <_mingw.h>

#ifndef RC_INVOKED
#define __need_size_t
#define __need_wchar_t
#define __need_NULL
#include <stddef.h>
#endif /* RC_INVOKED */

/* RAND_MAX is the maximum value that may be returned by rand.
 * The minimum is zero.
 */
#define RAND_MAX	0x7FFF

/* These values may be used as exit status codes.
 */
#define EXIT_SUCCESS	0
#define EXIT_FAILURE	1

/* Definitions for path name functions.
 * NOTE: All of these values have simply been chosen to be conservatively
 * high.  Remember that with long file names we can no longer depend on
 * extensions being short.
 */
#ifndef __STRICT_ANSI__

#ifndef MAX_PATH
#define MAX_PATH	(260)
#endif

#define _MAX_PATH	MAX_PATH
#define _MAX_DRIVE	(3)
#define _MAX_DIR	256
#define _MAX_FNAME	256
#define _MAX_EXT	256

#endif	/* !__STRICT_ANSI__ */
#endif	/* !__WCHAR_H_SOURCED__ */

#ifndef RC_INVOKED

_BEGIN_C_DECLS

#ifdef _STDLIB_H
#if ! defined __STRICT_ANSI__
/* This seems like a convenient place to declare these variables, which
 * give programs using WinMain (or main for that matter) access to main-ish
 * argc and argv. environ is a pointer to a table of environment variables.
 * NOTE: Strings in _argv and environ are ANSI strings.
 */
extern int     _argc;
extern char  **_argv;

#ifdef __MSVCRT__
/* Imports from the runtime DLL, for the above variables.
 */
extern __cdecl __MINGW_NOTHROW  int       *__p___argc(void);
extern __cdecl __MINGW_NOTHROW  char    ***__p___argv(void);
extern __cdecl __MINGW_NOTHROW  wchar_t ***__p___wargv(void);

#define __argc (*__p___argc())
#define __argv (*__p___argv())
#define __wargv (*__p___wargv())

#else  /* ! __MSVCRT__ */

#ifndef __DECLSPEC_SUPPORTED

extern int    *_imp____argc_dll;
extern char ***_imp____argv_dll;

#define __argc (*_imp____argc_dll)
#define __argv (*_imp____argv_dll)

#else  /* __DECLSPEC_SUPPORTED */

__MINGW_IMPORT int    __argc_dll;
__MINGW_IMPORT char **__argv_dll;

#define __argc __argc_dll
#define __argv __argv_dll

#endif  /* __DECLSPEC_SUPPORTED */

#endif  /* __MSVCRT__ */
#endif  /* __STRICT_ANSI__ */

#ifndef MB_CUR_MAX
/* FIXME: also defined in <ctype.h>; should be factored out.
 */
#ifdef __DECLSPEC_SUPPORTED
# ifdef __MSVCRT__
#  define MB_CUR_MAX __mb_cur_max
   __MINGW_IMPORT int __mb_cur_max;
# else  /* ! __MSVCRT__ */
#  define MB_CUR_MAX __mb_cur_max_dll
   __MINGW_IMPORT int __mb_cur_max_dll;
# endif  /* ! __MSVCRT__ */

#else  /* ! __DECLSPEC_SUPPORTED */
# ifdef __MSVCRT__
   extern int* _imp____mb_cur_max;
#  define MB_CUR_MAX (*_imp____mb_cur_max)
# else  /* ! __MSVCRT__ */
   extern int*  _imp____mb_cur_max_dll;
#  define MB_CUR_MAX (*_imp____mb_cur_max_dll)
# endif  /* ! __MSVCRT__ */
#endif  /*  __DECLSPEC_SUPPORTED */
#endif  /* MB_CUR_MAX */

/* FIXME: Nominally in <errno.h>, Microsoft likes to declare errno
 * in <stdlib.h> as well; we should factor this out.
 */
#ifdef _UWIN
# undef errno
  extern int errno;
#else
_CRTIMP __cdecl __MINGW_NOTHROW  int *_errno(void);
# define errno  (*_errno())
#endif
_CRTIMP __cdecl __MINGW_NOTHROW  int *__doserrno(void);
#define _doserrno  (*__doserrno())

#if !defined (__STRICT_ANSI__)
/* Use environ from the DLL, not as a global.
 */
#ifdef __MSVCRT__
# define _environ  (*__p__environ())
extern _CRTIMP __cdecl __MINGW_NOTHROW  char ***__p__environ(void);
# define _wenviron  (*__p__wenviron())
extern _CRTIMP __cdecl __MINGW_NOTHROW  wchar_t ***__p__wenviron(void);

#else  /* ! __MSVCRT__ */
# ifndef __DECLSPEC_SUPPORTED
# define _environ (*_imp___environ_dll)
extern char ***_imp___environ_dll;

# else  /* __DECLSPEC_SUPPORTED */
# define _environ  _environ_dll
__MINGW_IMPORT char ** _environ_dll;
# endif  /* __DECLSPEC_SUPPORTED */
#endif  /* ! __MSVCRT__ */

#define environ _environ

#ifdef	__MSVCRT__
/* One of the MSVCRTxx libraries */

#ifndef __DECLSPEC_SUPPORTED
# define sys_nerr  (*_imp___sys_nerr)
extern int *_imp___sys_nerr;

#else /* __DECLSPEC_SUPPORTED */
__MINGW_IMPORT int _sys_nerr;

# ifndef _UWIN
# define sys_nerr  _sys_nerr
# endif  /* _UWIN */
#endif  /* __DECLSPEC_SUPPORTED */

#else  /* ! __MSVCRT__ */
/* CRTDLL run time library */

#ifndef __DECLSPEC_SUPPORTED
  extern int*	_imp___sys_nerr_dll;
# define sys_nerr	(*_imp___sys_nerr_dll)
#else  /* __DECLSPEC_SUPPORTED */
  __MINGW_IMPORT int	_sys_nerr_dll;
# define sys_nerr	_sys_nerr_dll
#endif  /* __DECLSPEC_SUPPORTED */

#endif  /* ! __MSVCRT__ */

#ifndef __DECLSPEC_SUPPORTED
#define sys_errlist  (*_imp___sys_errlist)
extern char ***_imp__sys_errlist;

#else  /* __DECLSPEC_SUPPORTED */
__MINGW_IMPORT char *_sys_errlist[];

#ifndef _UWIN
#define sys_errlist  _sys_errlist
#endif  /* _UWIN */
#endif  /* __DECLSPEC_SUPPORTED */

/* OS version and such constants.
 */
#ifdef	__MSVCRT__ /* MSVCRT.DLL and MSVCRxx.DLL variants */

extern _CRTIMP __cdecl __MINGW_NOTHROW  unsigned int *__p__osver(void);
extern _CRTIMP __cdecl __MINGW_NOTHROW  unsigned int *__p__winver(void);
extern _CRTIMP __cdecl __MINGW_NOTHROW  unsigned int *__p__winmajor(void);
extern _CRTIMP __cdecl __MINGW_NOTHROW  unsigned int *__p__winminor(void);

#ifndef __DECLSPEC_SUPPORTED
# define _osver     (*__p__osver())
# define _winver    (*__p__winver())
# define _winmajor  (*__p__winmajor())
# define _winminor  (*__p__winminor())

#else /* __DECLSPEC_SUPPORTED */
__MINGW_IMPORT  unsigned int _osver;
__MINGW_IMPORT  unsigned int _winver;
__MINGW_IMPORT  unsigned int _winmajor;
__MINGW_IMPORT  unsigned int _winminor;
#endif  /* __DECLSPEC_SUPPORTED */

#else  /* ! __MSVCRT__; thus CRTDLL */
#ifndef __DECLSPEC_SUPPORTED

#define _osver	    (*_imp___osver_dll)
#define _winver    (*_imp___winver_dll)
#define _winmajor  (*_imp___winmajor_dll)
#define _winminor  (*_imp___winminor_dll)

extern unsigned int *_imp___osver_dll;
extern unsigned int *_imp___winver_dll;
extern unsigned int *_imp___winmajor_dll;
extern unsigned int *_imp___winminor_dll;

#else  /* __DECLSPEC_SUPPORTED */

#define _osver	    _osver_dll
#define _winver    _winver_dll
#define _winmajor  _winmajor_dll
#define _winminor  _winminor_dll

__MINGW_IMPORT unsigned int _osver_dll;
__MINGW_IMPORT unsigned int _winver_dll;
__MINGW_IMPORT unsigned int _winmajor_dll;
__MINGW_IMPORT unsigned int _winminor_dll;

#endif  /* __DECLSPEC_SUPPORTED */
#endif  /* CRTDLL */

#if defined  __MSVCRT__
/* Although _pgmptr is exported as DATA, be safe and use the access
 * function __p__pgmptr() to get it.
 */
#define _pgmptr  (*__p__pgmptr())
_CRTIMP __cdecl __MINGW_NOTHROW  char **__p__pgmptr(void);

#define _wpgmptr  (*__p__wpgmptr())
_CRTIMP __cdecl __MINGW_NOTHROW  wchar_t **__p__wpgmptr(void);

#else  /* ! __MSVCRT__; thus CRTDLL */

# ifndef __DECLSPEC_SUPPORTED
# define _pgmptr  (*_imp___pgmptr_dll)
extern char **__imp__pgmptr_dll;

# else  /* __DECLSPEC_SUPPORTED */

# define _pgmptr _pgmptr_dll
__MINGW_IMPORT  char *_pgmptr_dll;
/* no wide version in CRTDLL */

# endif /* __DECLSPEC_SUPPORTED */
#endif	/* CRTDLL */

/* This variable determines the default file mode.
 * TODO: Which flags work?
 */
#if !defined (__DECLSPEC_SUPPORTED) || defined (__IN_MINGW_RUNTIME)

#ifdef __MSVCRT__
#define _fmode  (*_imp___fmode)
extern int *_imp___fmode;
#else
/* CRTDLL */
#define _fmode  (*_imp___fmode_dll)
extern int *_imp___fmode_dll;
#endif

#else  /* __DECLSPEC_SUPPORTED */
#ifdef __MSVCRT__
__MINGW_IMPORT  int _fmode;

#else  /* ! __MSVCRT__ */
#define _fmode	_fmode_dll
__MINGW_IMPORT  int _fmode_dll;

#endif  /* !__MSVCRT__ */
#endif  /* __DECLSPEC_SUPPORTED */
#endif  /* !__STRICT_ANSI__ */

_CRTIMP __cdecl __MINGW_NOTHROW  int atoi (const char *);
_CRTIMP __cdecl __MINGW_NOTHROW  long atol (const char *);

_CRTIMP __cdecl __MINGW_NOTHROW  double strtod (const char *, char **);
_CRTIMP __cdecl __MINGW_NOTHROW  double atof (const char *);

#if !defined (__STRICT_ANSI__)
_CRTIMP __cdecl __MINGW_NOTHROW  double _wtof (const wchar_t *);
_CRTIMP __cdecl __MINGW_NOTHROW  int _wtoi (const wchar_t *);
_CRTIMP __cdecl __MINGW_NOTHROW  long _wtol (const wchar_t *);
#endif

#if __USE_MINGW_ANSI_STDIO
/* Microsoft's strtod() and atof() implementations, (in MSVCRT.DLL),
 * mishandle infinities and NaNs; on the basis that this conditional
 * exposes a more ISO-C conforming printf() I/O family implementaion,
 * we substitute a similarly more conforming implementation for each
 * of this pair of (somewhat related) functions.
 *
 * Note that we provide neither __JMPSTUB__ nor __LIBIMPL__ external
 * equivalents for either of these two inline functions, because they
 * would conflict with the runtime DLL implementations; users needing
 * an address reference for either must provide an equivalent of the
 * inline implementation, as non-inlined within their own code.
 */
extern __cdecl __MINGW_NOTHROW
double __strtod (const char *__restrict__, char **__restrict__);

__CRT_ALIAS __cdecl __MINGW_NOTHROW
double strtod (const char *__restrict__ __nptr, char **__restrict__ __endptr)
{ return __strtod( __nptr, __endptr ); }

__CRT_ALIAS __cdecl __MINGW_NOTHROW
double atof (const char *__nptr) { return __strtod( __nptr, NULL ); }

#endif  /* __USE_MINGW_ANSI_STDIO */

#ifdef _ISOC99_SOURCE
/* Irrespective of requested standards conformity, where MSVCRT.DLL
 * falls short, ISO-C99 offers this pair of alternative return type
 * specific variants of strtod(), which MSVCRT.DLL does not, but we
 * do, in libmingwex.a:
 */
__cdecl __MINGW_NOTHROW
float strtof (const char *__restrict__, char **__restrict__);

__cdecl __MINGW_NOTHROW
long double strtold (const char *__restrict__, char **__restrict__);
#endif  /* _ISOC99_SOURCE */

_CRTIMP __cdecl __MINGW_NOTHROW  long strtol (const char *, char **, int);
_CRTIMP __cdecl __MINGW_NOTHROW  unsigned long strtoul (const char *, char **, int);

#endif	/* _STDLIB_H only */
#if ! (defined _STDLIB_H && defined _WCHAR_H)
/* Prototypes which are to be declared both here, in <stdlib.h>,
 * and also in <wchar.h>; declare them here, such that they may be
 * selectively included by <wchar.h>.
 */
_CRTIMP __cdecl __MINGW_NOTHROW
long wcstol (const wchar_t *, wchar_t **, int);

_CRTIMP __cdecl __MINGW_NOTHROW
unsigned long wcstoul (const wchar_t *, wchar_t **, int);

_CRTIMP __cdecl __MINGW_NOTHROW  double wcstod (const wchar_t *, wchar_t **);

#ifdef _ISOC99_SOURCE
/* Variants on wcstod(), specified by ISO-C99; once again, MSVCRT.DLL
 * doesn't have them, but we offer them in libmingwex.a
 */
__cdecl __MINGW_NOTHROW
float wcstof (const wchar_t *__restrict__, wchar_t **__restrict__);

__cdecl __MINGW_NOTHROW
long double wcstold (const wchar_t *__restrict__, wchar_t **__restrict__);
#endif  /* _ISOC99_SOURCE */

#ifdef __MSVCRT__
#if __MSVCRT_VERSION__ >= __MSVCR70_DLL || _WIN32_WINNT >= _WIN32_WINNT_WINXP
/* This pair of wide character equivalents for ISO-C99's strtoll() and
 * strtoull() require either WinXP (or later), or a non-free MSVC runtime
 * from MSVCR70.DLL onwards...
 */
_CRTIMP __cdecl __MINGW_NOTHROW
__int64 _wcstoi64(const wchar_t *, wchar_t **, int);

_CRTIMP __cdecl __MINGW_NOTHROW
unsigned __int64 _wcstoui64(const wchar_t *, wchar_t **, int);

#endif	/* WinXP || MSVCR70.DLL || later */

#if __MSVCRT_VERSION__ >= __MSVCR80_DLL || _WIN32_WINNT >= _WIN32_WINNT_VISTA
/* ...while the following pair require Win-Vista (or later), or non-free
 * MSVCRT runtime from MSVCR80.DLL onwards; they also require...
 */
#ifndef __have_typedef_locale_t
/* ...this opaque data type, which we may obtain by selective inclusion
 * from <locale.h>.  (Note that this may render them unusable for users of
 * MSVCRT.DLL; see the explanation in <locale.h>, regarding the difficulty
 * in creating, or otherwise acquiring a reference to, a _locale_t object,
 * notwithstanding the availability of the functions in MSVCRT.DLL, from
 * the release of Win-Vista onwards).
 */
#define __need_locale_t
#include <locale.h>
#endif	/* !__have_typedef_locale_t */

_CRTIMP __cdecl __MINGW_NOTHROW
__int64 _wcstoi64_l(const wchar_t *, wchar_t **, int, _locale_t);

_CRTIMP __cdecl __MINGW_NOTHROW
unsigned __int64 _wcstoui64_l(const wchar_t *, wchar_t **, int, _locale_t);

#endif	/* Win-Vista || MSVCR80.DLL || later */

_CRTIMP __cdecl __MINGW_NOTHROW  wchar_t *_wgetenv (const wchar_t *);
_CRTIMP __cdecl __MINGW_NOTHROW  int _wputenv (const wchar_t *);

_CRTIMP __cdecl __MINGW_NOTHROW
void _wsearchenv (const wchar_t *, const wchar_t *, wchar_t *);

_CRTIMP __cdecl __MINGW_NOTHROW  int _wsystem (const wchar_t *);

_CRTIMP __cdecl __MINGW_NOTHROW
void _wmakepath (wchar_t *, const wchar_t *, const wchar_t *, const wchar_t *,
    const wchar_t *
  );

_CRTIMP __cdecl __MINGW_NOTHROW
void _wsplitpath (const wchar_t *, wchar_t *, wchar_t *, wchar_t *, wchar_t *);

_CRTIMP __cdecl __MINGW_NOTHROW
wchar_t *_wfullpath (wchar_t *, const wchar_t *, size_t);

#endif	/* __MSVCRT__ */
#endif	/* _STDLIB_H || _WCHAR_H */

#ifdef _STDLIB_H  /* <stdlib.h> only */
_CRTIMP __cdecl __MINGW_NOTHROW  size_t wcstombs (char *, const wchar_t *, size_t);
_CRTIMP __cdecl __MINGW_NOTHROW  int wctomb (char *, wchar_t);

_CRTIMP __cdecl __MINGW_NOTHROW  int mblen (const char *, size_t);
_CRTIMP __cdecl __MINGW_NOTHROW  size_t mbstowcs (wchar_t *, const char *, size_t);
_CRTIMP __cdecl __MINGW_NOTHROW  int mbtowc (wchar_t *, const char *, size_t);

_CRTIMP __cdecl __MINGW_NOTHROW  int rand (void);
_CRTIMP __cdecl __MINGW_NOTHROW  void srand (unsigned int);

_CRTIMP __cdecl __MINGW_NOTHROW  void *calloc (size_t, size_t) __MINGW_ATTRIB_MALLOC;
_CRTIMP __cdecl __MINGW_NOTHROW  void *malloc (size_t) __MINGW_ATTRIB_MALLOC;
_CRTIMP __cdecl __MINGW_NOTHROW  void *realloc (void *, size_t);
_CRTIMP __cdecl __MINGW_NOTHROW  void free (void *);
_CRTIMP __cdecl __MINGW_NOTHROW  void abort (void) __MINGW_ATTRIB_NORETURN;
_CRTIMP __cdecl __MINGW_NOTHROW  void exit (int) __MINGW_ATTRIB_NORETURN;

/* Note: this is in startup code, not imported directly from the runtime DLL
 */
int __cdecl __MINGW_NOTHROW atexit (void (*)(void));

_CRTIMP __cdecl __MINGW_NOTHROW  int system (const char *);
_CRTIMP __cdecl __MINGW_NOTHROW  char *getenv (const char *);

/* bsearch() and qsort() are declared both here, in <stdlib.h>, and in
 * non-ANSI header <search.h>; we reproduce these declarations in both,
 * with no attempt to guard them, so the compiler may verify that they
 * are consistent, if both headers are included.
 */
_CRTIMP __cdecl  void *bsearch
(const void *, const void *, size_t, size_t, int (*)(const void *, const void *));

_CRTIMP __cdecl  void qsort
(void *, size_t, size_t, int (*)(const void *, const void *));

_CRTIMP __cdecl __MINGW_NOTHROW  int abs (int) __MINGW_ATTRIB_CONST;
_CRTIMP __cdecl __MINGW_NOTHROW  long labs (long) __MINGW_ATTRIB_CONST;

/* div_t and ldiv_t are structures used to return the results of div()
 * and ldiv() functions.
 *
 * NOTE: div() and ldiv() appear not to work correctly unless
 *       -fno-pcc-struct-return is specified. This is included in the
 *       mingw32 specs file.
 */
typedef struct { int quot, rem; } div_t;
typedef struct { long quot, rem; } ldiv_t;

_CRTIMP __cdecl __MINGW_NOTHROW  div_t div (int, int) __MINGW_ATTRIB_CONST;
_CRTIMP __cdecl __MINGW_NOTHROW  ldiv_t ldiv (long, long) __MINGW_ATTRIB_CONST;

#if !defined __STRICT_ANSI__ || (defined _ISOC99_SOURCE && !defined __NO_INLINE__)
/* Although not nominally valid in "__STRICT_ANSI__" mode, when compiling C99
 * source, we use Microsoft's _exit() function to facilitate our provision of
 * an inline implementation of ISO-C99's _Exit() function.
 */
_CRTIMP __cdecl __MINGW_NOTHROW  void _exit (int) __MINGW_ATTRIB_NORETURN;

#ifdef __MSVCRT__
/* Similarly, we use Microsoft's MSVCRT.DLL specific _atoi64() function,
 * to facilitate an inline implementation of ISO-C99's atoll() function.
 */
_CRTIMP __cdecl __MINGW_NOTHROW  __int64 _atoi64 (const char *);

#endif	/* __MSVCRT__ */
#endif	/* !__STRICT_ANSI__ || (_ISOC99_SOURCE && !__NO_INLINE__) */

#if !defined (__STRICT_ANSI__)
/* NOTE: Officially the three following functions are obsolete. The Win32 API
 *       functions SetErrorMode, Beep and Sleep are their replacements.
 */
_CRTIMP __cdecl __MINGW_NOTHROW  void _beep (unsigned int, unsigned int) __MINGW_ATTRIB_DEPRECATED;
/* Not to be confused with  _set_error_mode (int).  */
_CRTIMP __cdecl __MINGW_NOTHROW  void _seterrormode (int) __MINGW_ATTRIB_DEPRECATED;
_CRTIMP __cdecl __MINGW_NOTHROW  void _sleep (unsigned long) __MINGW_ATTRIB_DEPRECATED;

/* _onexit is a Microsoft extension. Use atexit for portability. */
/* Note: This is in startup code, not imported directly from dll */
typedef  int (* _onexit_t)(void);
__cdecl __MINGW_NOTHROW  _onexit_t _onexit( _onexit_t );

_CRTIMP __cdecl __MINGW_NOTHROW  int _putenv (const char *);
_CRTIMP __cdecl __MINGW_NOTHROW
void _searchenv (const char *, const char *, char *);

_CRTIMP __cdecl __MINGW_NOTHROW  char *_ecvt (double, int, int *, int *);
_CRTIMP __cdecl __MINGW_NOTHROW  char *_fcvt (double, int, int *, int *);
_CRTIMP __cdecl __MINGW_NOTHROW  char *_gcvt (double, int, char *);

_CRTIMP __cdecl __MINGW_NOTHROW
void _makepath (char *, const char *, const char *, const char *, const char *);

_CRTIMP __cdecl __MINGW_NOTHROW
void _splitpath (const char *, char *, char *, char *, char *);

_CRTIMP __cdecl __MINGW_NOTHROW  char *_fullpath (char*, const char*, size_t);

_CRTIMP __cdecl __MINGW_NOTHROW  char *_itoa (int, char *, int);
_CRTIMP __cdecl __MINGW_NOTHROW  char *_ltoa (long, char *, int);
_CRTIMP __cdecl __MINGW_NOTHROW  char *_ultoa(unsigned long, char *, int);
_CRTIMP __cdecl __MINGW_NOTHROW  wchar_t *_itow (int, wchar_t *, int);
_CRTIMP __cdecl __MINGW_NOTHROW  wchar_t *_ltow (long, wchar_t *, int);
_CRTIMP __cdecl __MINGW_NOTHROW  wchar_t *_ultow (unsigned long, wchar_t *, int);

#ifdef __MSVCRT__
_CRTIMP __cdecl __MINGW_NOTHROW  char* _i64toa (__int64, char *, int);
_CRTIMP __cdecl __MINGW_NOTHROW  char* _ui64toa (unsigned __int64, char *, int);
_CRTIMP __cdecl __MINGW_NOTHROW  __int64 _wtoi64 (const wchar_t *);
_CRTIMP __cdecl __MINGW_NOTHROW  wchar_t* _i64tow (__int64, wchar_t *, int);
_CRTIMP __cdecl __MINGW_NOTHROW  wchar_t* _ui64tow (unsigned __int64, wchar_t *, int);

_CRTIMP __cdecl __MINGW_NOTHROW  unsigned int (_rotl)(unsigned int, int) __MINGW_ATTRIB_CONST;
_CRTIMP __cdecl __MINGW_NOTHROW  unsigned int (_rotr)(unsigned int, int) __MINGW_ATTRIB_CONST;
_CRTIMP __cdecl __MINGW_NOTHROW  unsigned long (_lrotl)(unsigned long, int) __MINGW_ATTRIB_CONST;
_CRTIMP __cdecl __MINGW_NOTHROW  unsigned long (_lrotr)(unsigned long, int) __MINGW_ATTRIB_CONST;

_CRTIMP __cdecl __MINGW_NOTHROW  int _set_error_mode (int);

# define _OUT_TO_DEFAULT	0
# define _OUT_TO_STDERR 	1
# define _OUT_TO_MSGBOX 	2
# define _REPORT_ERRMODE	3

# if __MSVCRT_VERSION__ >= __MSVCR80_DLL
#  ifndef _UINTPTR_T_DEFINED
#   define _UINTPTR_T_DEFINED
#   ifdef _WIN64
      typedef unsigned __int64 uintptr_t;
#   else
      typedef unsigned int uintptr_t;
#   endif
#  endif

_CRTIMP __cdecl __MINGW_NOTHROW
unsigned int _set_abort_behavior (unsigned int, unsigned int);

/* These masks work with msvcr80.dll version 8.0.50215.44 (a beta release).
 */
#  define _WRITE_ABORT_MSG	1
#  define _CALL_REPORTFAULT	2

typedef void
(* _invalid_parameter_handler) (
    const wchar_t *,
    const wchar_t *,
    const wchar_t *,
    unsigned int,
    uintptr_t);
_invalid_parameter_handler _set_invalid_parameter_handler (_invalid_parameter_handler);

# endif /* __MSVCRT_VERSION__ >= __MSVCR80_DLL */
#endif	/* __MSVCRT__ */

#ifndef _NO_OLDNAMES
_CRTIMP __cdecl __MINGW_NOTHROW  int putenv (const char*);
_CRTIMP __cdecl __MINGW_NOTHROW  void searchenv (const char*, const char*, char*);

_CRTIMP __cdecl __MINGW_NOTHROW  char* itoa (int, char*, int);
_CRTIMP __cdecl __MINGW_NOTHROW  char* ltoa (long, char*, int);

#ifndef _UWIN
_CRTIMP __cdecl __MINGW_NOTHROW  char* ecvt (double, int, int*, int*);
_CRTIMP __cdecl __MINGW_NOTHROW  char* fcvt (double, int, int*, int*);
_CRTIMP __cdecl __MINGW_NOTHROW  char* gcvt (double, int, char*);

#endif	/* ! _UWIN */
#endif	/* ! _NO_OLDNAMES */
#endif	/* ! __STRICT_ANSI__ */

#ifdef _ISOC99_SOURCE
/* Further APIs required to support ISO-C99, but missing from MSVCRT.DLL;
 * we provide them in libmingwex.a:
 *
 * ISO-C99 name for _exit()
 */
__cdecl __MINGW_NOTHROW  void _Exit(int) __MINGW_ATTRIB_NORETURN;

#ifndef __NO_INLINE__
__CRT_INLINE __JMPSTUB__(( FUNCTION = _Exit, REMAPPED = _exit ))
__cdecl __MINGW_NOTHROW  void _Exit( int __status ){ _exit (__status); }
#endif

typedef struct { long long quot, rem; } lldiv_t;
__cdecl __MINGW_NOTHROW  lldiv_t lldiv (long long, long long) __MINGW_ATTRIB_CONST;

__cdecl __MINGW_NOTHROW  long long llabs (long long);

#ifndef __NO_INLINE__
__CRT_INLINE
/* No JMPSTUB or LIBIMPL reference here -- we provide a free-standing
 * implementation, along with imaxabs(), in mingwex/imaxabs.c
 */
__cdecl __MINGW_NOTHROW  long long llabs( long long __j )
{ return __j >= 0 ? __j : -__j; }
#endif

__cdecl __MINGW_NOTHROW
long long strtoll (const char *__restrict__, char **__restrict, int);

__cdecl __MINGW_NOTHROW
unsigned long long strtoull (const char *__restrict__, char **__restrict__, int);

#ifdef __MSVCRT__
/* MSVCRT.DLL does not provide ISO-C99's atoll() function, but it does
 * provide an analogue, in _atoi64(); map it accordingly.
 */
__cdecl __MINGW_NOTHROW  long long atoll (const char *);

#ifndef __NO_INLINE__
__CRT_INLINE __JMPSTUB__(( FUNCTION = atoll, REMAPPED = _atoi64 ))
__cdecl __MINGW_NOTHROW  long long atoll (const char * _c){ return _atoi64 (_c); }
#endif

#endif  /* __MSVCRT__ */
#endif  /* _ISOC99_SOURCE */

#if defined __MSVCRT__ && ! defined __STRICT_ANSI__
#if __MSVCRT_VERSION__ >= __MSVCR70_DLL || _WIN32_WINNT >= _WIN32_WINNT_WINXP
/* Microsoft specific alternatives to ISO-C99 strtoll() and strtoull(); the
 * first pair require WinXP (or later) or non-free MSVCR70.DLL onwards...
 */
_CRTIMP __cdecl __MINGW_NOTHROW
__int64 _strtoi64(const char*, char **, int);

_CRTIMP __cdecl __MINGW_NOTHROW
unsigned __int64 _strtoui64(const char*, char **, int);

#endif	/* WinXP || MSVCR70.DLL || later */
#if __MSVCRT_VERSION__ >= __MSVCR80_DLL || _WIN32_WINNT >= _WIN32_WINNT_VISTA
/* ...while the following pair require Win-Vista (or later), or non-free
 * MSVCR80.DLL onwards; (note that, like their wide character counterparts,
 * they may actually be unusable without MSVCR80.DLL onwards, because of
 * the difficulty in acquiring a reference to a _locale_t object).
 */
_CRTIMP __cdecl __MINGW_NOTHROW
__int64 _strtoi64_l(const char *, char **, int, _locale_t);

_CRTIMP __cdecl __MINGW_NOTHROW
unsigned __int64 _strtoui64_l(const char *, char **, int, _locale_t);

#endif	/* Win-Vista || MSVCR80.DLL || later */

/* Type long long analogues for MSVCRT.DLL specific type long functions;
 * none are actually provided by any version of MSVCRT.DLL, with names as
 * specified here, but rather as called by the inline functions used to
 * implement them, (i.e. the REMAPPED name specified in each__JMPSTUB__
 * function reference respectively).
 *
 * FIXME: Not one of these is specified by ISO-C99, nor by POSIX, either;
 * is there really any justification for us to specify them at all?  For
 * the time being, declare as deprecated; perhaps remove later?
 */
__cdecl __MINGW_NOTHROW __MINGW_ATTRIB_DEPRECATED  long long wtoll (const wchar_t *);
__cdecl __MINGW_NOTHROW __MINGW_ATTRIB_DEPRECATED  char *lltoa (long long, char *, int);
__cdecl __MINGW_NOTHROW __MINGW_ATTRIB_DEPRECATED  char *ulltoa (unsigned long long , char *, int);
__cdecl __MINGW_NOTHROW __MINGW_ATTRIB_DEPRECATED  wchar_t *lltow (long long, wchar_t *, int);
__cdecl __MINGW_NOTHROW __MINGW_ATTRIB_DEPRECATED  wchar_t *ulltow (unsigned long long, wchar_t *, int);

#ifndef __NO_INLINE__
/* None of these functions would exist at all, without either these inline
 * implementations, or their respective __JMPSTUB__ equivalents.
 */
__CRT_INLINE __JMPSTUB__(( FUNCTION = lltoa, REMAPPED = _i64toa ))
__cdecl __MINGW_NOTHROW  char *lltoa (long long __n, char * __c, int __i)
{ return _i64toa (__n, __c, __i); }

__CRT_INLINE __JMPSTUB__(( FUNCTION = ulltoa, REMAPPED = _ui64toa ))
__cdecl __MINGW_NOTHROW  char *ulltoa (unsigned long long __n, char * __c, int __i)
{ return _ui64toa (__n, __c, __i); }

__CRT_INLINE __JMPSTUB__(( FUNCTION = wtoll, REMAPPED = _wtoi64 ))
__cdecl __MINGW_NOTHROW  long long wtoll (const wchar_t * __w){ return _wtoi64 (__w); }

__CRT_INLINE __JMPSTUB__(( FUNCTION = lltow, REMAPPED = _i64tow ))
__cdecl __MINGW_NOTHROW  wchar_t *lltow (long long __n, wchar_t * __w, int __i)
{ return _i64tow (__n, __w, __i); }

__CRT_INLINE __JMPSTUB__(( FUNCTION = ulltow, REMAPPED = _ui64tow ))
__cdecl __MINGW_NOTHROW  wchar_t *ulltow (unsigned long long __n, wchar_t * __w, int __i)
{ return _ui64tow (__n, __w, __i); }

#endif  /* ! __NO_INLINE__ */
#endif  /* __MSVCRT__ && ! __STRICT_ANSI__ */

/* POSIX/BSD extensions in libmingwex.a; these should be exposed only on
 * the basis of appropriate POSIX or BSD specific feature tests...
 *
 * mkstemp(3) function support; added per feature request #2003.
 * POSIX wants _XOPEN_SOURCE >= 500, (implying _POSIX_C_SOURCE >= 200112L).
 */
#if _POSIX_C_SOURCE >= 200112L

__cdecl __MINGW_NOTHROW  int mkstemp (char *);
__cdecl __MINGW_NOTHROW  int __mingw_mkstemp (int, char *);

/* On POSIX platforms, programmers may adopt an idiom such as:
 *
 *   if( mkstemp( template ) >= 0 )
 *   { unlink( template );
 *     . . .
 *   }
 *
 * to ensure that a temporary file does NOT persist after it is
 * closed; MS-Windows does not allow such use of unlink(2), while
 * the file remains open.  Thus, MS-Windows programmers must take
 * extra care, to close and unlink temporary files AFTER use, if
 * similar behaviour is desired.
 *
 * To mitigate this MS-Windows limitation, we provide support for
 * an alternative, MinGW specific idiom:
 *
 *   #include <fcntl.h>
 *
 *   _MKSTEMP_SETMODE( _O_TEMPORARY );
 *   if( mkstemp( template ) >= 0 )
 *   {
 *     . . .
 *   }
 *
 * to achieve a similar effect to that of the above POSIX idiom; the
 * following macros are a MinGW specific extension, to facilite such
 * use of _O_TEMPORARY, (in addition to the POSIX required attributes),
 * when creating the temporary file.  Note that they require <fcntl.h>,
 * which <stdlib.h> should NOT automatically include; we leave it to
 * the user to explicitly include it, if using _MKSTEMP_SETMODE.
 */
#define _MKSTEMP_INVOKE       0
#define _MKSTEMP_DEFAULT     _O_CREAT | _O_EXCL | _O_RDWR
#define _MKSTEMP_SETMODE(M) __mingw_mkstemp( _MKSTEMP_DEFAULT | (M), NULL )

#ifndef _NO_OLDNAMES
#define MKSTEMP_SETMODE(M)  __mingw_mkstemp( _MKSTEMP_DEFAULT | (M), NULL )
#endif

__CRT_ALIAS __LIBIMPL__(( FUNCTION = mkstemp ))
__cdecl __MINGW_NOTHROW  int mkstemp (char *__filename_template)
{ return __mingw_mkstemp( _MKSTEMP_INVOKE, __filename_template ); }

#endif	/* _POSIX_C_SOURCE >= 200112L (for mkstemp()) */

/* mkdtemp(3) function support: added as adjunct to feature request #2003.
 * POSIX wants _XOPEN_SOURCE >= 700, (implying _POSIX_C_SOURCE >= 200809L).
 */
#if _POSIX_C_SOURCE >= 200809L

__cdecl __MINGW_NOTHROW  char *mkdtemp (char *);
__cdecl __MINGW_NOTHROW  char *__mingw_mkdtemp (char *);

__CRT_ALIAS __JMPSTUB__(( FUNCTION = mkdtemp ))
__cdecl __MINGW_NOTHROW  char *mkdtemp (char *__dirname_template)
{ return __mingw_mkdtemp( __dirname_template ); }

#endif	/* _POSIX_C_SOURCE >= 200809L (for mkdtemp()) */

#if _POSIX_C_SOURCE >= 200112L
/* setenv() and unsetenv() are also available, from POSIX.1-2001 onwards.
 */
__cdecl __MINGW_NOTHROW  int setenv( const char *, const char *, int );
__cdecl __MINGW_NOTHROW  int unsetenv( const char * );

__cdecl __MINGW_NOTHROW  int __mingw_setenv( const char *, const char *, int );

__CRT_ALIAS __JMPSTUB__(( FUNCTION = setenv ))
__cdecl __MINGW_NOTHROW  int setenv( const char *__n, const char *__v, int __f )
{ return __mingw_setenv( __n, __v, __f ); }

__CRT_ALIAS __LIBIMPL__(( FUNCTION = unsetenv ))
__cdecl __MINGW_NOTHROW  int unsetenv( const char *__name )
{ return __mingw_setenv( __name, NULL, 1 ); }

#endif	/* _POSIX_C_SOURCE >= 200112L (for setenv()) */
#endif	/* _STDLIB_H */

_END_C_DECLS

#endif	/* ! RC_INVOKED */
#endif	/* ! _STDLIB_H: $RCSfile: stdlib.h,v $: end of file */

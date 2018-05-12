/*
 * stat.h
 *
 * Symbolic constants for opening and creating files, also stat, fstat and
 * chmod functions.
 *
 * $Id: stat.h,v 4cf5070e9a04 2016/07/14 17:59:07 keithmarshall $
 *
 * Written by Colin Peters <colin@bird.fu.is.saga-u.ac.jp>
 * Copyright (C) 1997-2001, 2003-2005, 2007, 2016, MinGW.org Project.
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
#ifndef _SYS_STAT_H
#pragma GCC system_header

/* To support selective (partial) inclusion by <wchar.h>...
 */
#ifndef __WCHAR_H_SOURCED__
/* ...we defer the definition of the normal multiple inclusion guard macro,
 * until we know that this is NOT the <wchar.h> selective inclusion case.
 */
#define _SYS_STAT_H

/* All MinGW headers are required to include <_mingw.h>; however, Microsoft
 * also stipulate that USERS MUST include <sys/types.h>, BEFORE they include
 * <sys/stat.h>.  This is not only appallingly bad software engineering, on
 * Microsoft's part, but it is a potential obstacle to portability of POSIX
 * source code; (POSIX requires that <sys/stat.h> should be self-contained,
 * with no requirement for any specific header inclusion order).  Although
 * it is more inclusive that POSIX requires, we may mitigate the deficiency
 * inherent in Microsoft's poor software engineering, by simply including
 * <sys/types.h> here; in so doing, we may also delegate the inclusion of
 * <_mingw.h>, and the definition of all data types required herein, to...
 */
#include <sys/types.h>

/* Constants for the st_mode member of struct stat, and its Microsoft
 * specific variants.
 */
#define _S_IFIFO 	0x1000	/* FIFO */
#define _S_IFCHR 	0x2000	/* Character */
#define _S_IFDIR 	0x4000	/* Directory */
#define _S_IFREG 	0x8000	/* Regular */

#ifdef _MINGW_S_IFBLK_KLUDGE
/* For preference, this kludge should NOT be enabled; for rationale,
 * see: https://sourceforge.net/p/mingw/bugs/1146
 *
 * MS-Windows doesn't support testing for block special devices via the
 * st_mode flags; ideally, client code to be ported to Windows should not
 * blindly assume that S_IFBLK (or _S_IFBLK) is defined, but should rather
 * check for it, and compile dependent code conditionally.  Notwithstanding,
 * this kludge allows the user to force a definition, which we arbitrarily
 * choose to ensure that S_ISBLK (or _S_ISBLK) always returns FALSE, (i.e.
 * choose a value such that _S_IFBLK & _S_IFMT can NEVER equal _S_IFBLK).
 */
#define _S_IFBLK 	0x3001	/* Block: unsupported on Win32 */
#endif

#define _S_IFMT  	0xF000	/* File type mask */

#define _S_IEXEC 	0x0040
#define _S_IWRITE	0x0080
#define _S_IREAD 	0x0100

#define _S_IRWXU 	(_S_IREAD | _S_IWRITE | _S_IEXEC)
#define _S_IXUSR 	_S_IEXEC
#define _S_IWUSR 	_S_IWRITE
#define _S_IRUSR 	_S_IREAD

#define _S_ISDIR(m)	(((m) & _S_IFMT) == _S_IFDIR)
#define _S_ISFIFO(m)	(((m) & _S_IFMT) == _S_IFIFO)
#define _S_ISCHR(m)	(((m) & _S_IFMT) == _S_IFCHR)
#define _S_ISBLK(m)	(((m) & _S_IFMT) == _S_IFBLK)
#define _S_ISREG(m)	(((m) & _S_IFMT) == _S_IFREG)

#ifndef _NO_OLDNAMES

#define S_IFIFO 	_S_IFIFO
#define S_IFCHR 	_S_IFCHR
#ifdef _S_IFBLK
#define S_IFBLK 	_S_IFBLK
#endif
#define S_IFDIR 	_S_IFDIR
#define S_IFREG 	_S_IFREG
#define S_IFMT  	_S_IFMT
#define S_IEXEC 	_S_IEXEC
#define S_IWRITE	_S_IWRITE
#define S_IREAD 	_S_IREAD
#define S_IRWXU 	_S_IRWXU
#define S_IXUSR 	_S_IXUSR
#define S_IWUSR 	_S_IWUSR
#define S_IRUSR 	_S_IRUSR

#define S_ISDIR(m)	(((m) & S_IFMT) == S_IFDIR)
#define S_ISFIFO(m)	(((m) & S_IFMT) == S_IFIFO)
#define S_ISCHR(m)	(((m) & S_IFMT) == S_IFCHR)
#define S_ISBLK(m)	(((m) & S_IFMT) == S_IFBLK)
#define S_ISREG(m)	(((m) & S_IFMT) == S_IFREG)

#endif	/* !_NO_OLDNAMES */

#ifndef _S_IFBLK
/* When the _S_IFBLK kludge is NOT enabled, (as it ideally should not be),
 * ensure that any attempt to use its dependent macros is denied...
 */
# pragma GCC poison _S_ISBLK

# if defined _NO_UNSUPPORTED || defined _NO_OLDNAMES
  /* ...including that for the standard POSIX macro, when unsupported
   * features, or Microsoft's old names, are explicitly forbidden...
   */
#  pragma GCC poison S_ISBLK

# else /* !(_NO_UNSUPPORTED || _NO_OLDNAMES) */
  /* ...otherwise assume that the kludge is automatically enabled with
   * respect to S_ISBLK, (because GCC gratuitously misuses it).
   */
#  define S_IFBLK 	0x3001	/* Block: unsupported on Win32 */

# endif /* !(_NO_UNSUPPORTED || _NO_OLDNAMES) */
#endif	/* !_S_IFBLK */
#endif	/* !__WCHAR_H_SOURCED__ */

#ifndef RC_INVOKED
#ifndef __struct_stat_defined
/* The structure manipulated and returned by stat() and fstat(); note that
 * expansion of the macro provided below will yield variants of struct stat
 * to conform with Microsoft's usage, (and POSIX usage up to and including
 * POSIX.1-2001, but NOT the extended specification of POSIX.1-2008).
 *
 * NOTE: If called on a directory the values in the time fields are not only
 * invalid, they will cause localtime et. al. to return NULL. And calling
 * asctime with a NULL pointer causes an Invalid Page Fault. So watch it!
 */
#define __struct_stat_defined(__st_off_t, __st_time_t)			     \
{ _dev_t	st_dev; 	/* Equivalent to drive number 0=A 1=B ... */ \
  _ino_t	st_ino; 	/* Always zero ? */			     \
  _mode_t	st_mode;	/* See above constants */		     \
   short 	st_nlink;	/* Number of links. */			     \
   short 	st_uid; 	/* User: Maybe significant on NT ? */	     \
   short 	st_gid; 	/* Group: Ditto */			     \
  _dev_t	st_rdev;	/* Seems useless (not even filled in) */     \
  __st_off_t	st_size;	/* File size in bytes */		     \
  __st_time_t	st_atime;	/* Access time (always 00:00 on FAT) */	     \
  __st_time_t	st_mtime;	/* Modified time */			     \
  __st_time_t	st_ctime;	/* Creation time */			     \
}

/* Here, we expand the preceding macro to yield the actual definition
 * of struct stat, under its current Microsoft "uglified" name...
 */
struct _stat __struct_stat_defined( _off_t, time_t );

#ifndef _NO_OLDNAMES
/* ...while this alternative expansion yields its standard POSIX name,
 * (and its original Microsoft name); apart from its name, this must be
 * defined identically to struct _stat above.
 */
struct stat __struct_stat_defined( _off_t, time_t );
#endif	/* !_NO_OLDNAMES */

#if defined __MSVCRT__
/* This variant of struct stat is required to support the use of the
 * _stati64() function, which is provided by MSVCRT.DLL, but was not
 * present in CRTDLL.DLL...
 */
struct _stati64 __struct_stat_defined( __off64_t, time_t );

#if __MSVCRT_VERSION__ >= __MSVCR61_DLL || _WIN32_WINNT >= _WIN32_WINNT_WIN2K
/* ...while this supports the use of the _stat64() function, introduced
 * by MSVCR61.DLL, and subsequently added to MSVCRT.DLL for releases from
 * Win2K onwards...
 */
struct __stat64 __struct_stat_defined( __off64_t, __time64_t );

#if __MSVCRT_VERSION__ >= __MSVCR80_DLL
/* ...and these are specific to additional function variants, added to
 * the non-free MSVCR80.DLL, and its later derivatives, but not present
 * in MSVCRT.DLL (or CRTDLL.DLL).
 */
struct __stat32 __struct_stat_defined( __off32_t, __time32_t );
struct _stat32i64 __struct_stat_defined( __off64_t, __time32_t );
struct _stat64i32 __struct_stat_defined( __off32_t, __time64_t );

#endif	/* __MSVCRT_VERSION__ >= __MSVCR80_DLL */
#endif	/* __MSVCRT_VERSION__ >= __MSVCR61_DLL */
#endif	/* __MSVCRT__ */

/* From here on, it is sufficient to leave __struct_stat_defined as
 * a macro which expands to nothing.
 */
#undef  __struct_stat_defined
#define __struct_stat_defined

#endif /* !__struct_stat_defined */

_BEGIN_C_DECLS

#ifdef _SYS_STAT_H
/* This set of function prototypes are to be declared only when
 * <sys/stat.h> is included directly.
 */
_CRTIMP __cdecl __MINGW_NOTHROW  int _umask (int);
_CRTIMP __cdecl __MINGW_NOTHROW  int _chmod (const char *, int);

#if __MSVCRT_VERSION__ < __MSVCR80_DLL
/* This pair of functions are present in all versions of MSVCRT.DLL, but
 * they are NOT present in MSVCR80.DLL, nor in any of its later non-free
 * variants, all of which rely on inline aliases (defined below).
 */
_CRTIMP __cdecl __MINGW_NOTHROW  int _fstat (int, struct _stat *);
_CRTIMP __cdecl __MINGW_NOTHROW  int _stat (const char *, struct _stat *);
#endif	/* __MSVCRT_VERSION__ < __MSVCR80_DLL */

#ifndef	_NO_OLDNAMES
/* These are the standard POSIX names, (and the original Microsoft names),
 * for the preceding four functions.
 */
_CRTIMP __cdecl __MINGW_NOTHROW  int umask (int);
_CRTIMP __cdecl __MINGW_NOTHROW  int chmod (const char *, int);

#if __MSVCRT_VERSION__ < __MSVCR80_DLL
/* Since the underlying functions, with "uglified" names, are not supported
 * by MSVCR80.DLL and its later derivitaves, there is also nothing to which
 * to map these originally named alternatives; declare prototypes only when
 * using DLL versions which can support them, while falling back to the use
 * of inline replacements (defined below) in the unsupported cases.
 */
_CRTIMP __cdecl __MINGW_NOTHROW  int fstat (int, struct stat *);
_CRTIMP __cdecl __MINGW_NOTHROW  int stat (const char *, struct stat *);
#endif	/* __MSVCRT_VERSION__ < __MSVCR80_DLL */
#endif	/* !_NO_OLDNAMES */

#if defined __MSVCRT__
#if __MSVCRT_VERSION__ < __MSVCR80_DLL
/* This pair of functions were withdrawn from MSVCR80.DLL, and its later
 * derivatives, but remain in all versions of MSVCRT.DLL
 */
_CRTIMP __cdecl __MINGW_NOTHROW  int _fstati64 (int, struct _stati64 *);
_CRTIMP __cdecl __MINGW_NOTHROW  int _stati64 (const char *, struct _stati64 *);
#endif	/* __MSVCRT_VERSION__ < __MSVCR80_DLL */

#if __MSVCRT_VERSION__ >= __MSVCR61_DLL || _WIN32_WINNT >= _WIN32_WINNT_WIN2K
/* This pair of functions were introduced in MSVCR61.DLL, and were subsequently
 * added to MSVCRT.DLL from the release accompanying Win2K onwards...
 */
_CRTIMP __cdecl __MINGW_NOTHROW  int _fstat64 (int, struct __stat64 *);
_CRTIMP __cdecl __MINGW_NOTHROW  int _stat64 (const char *, struct __stat64 *);

#if __MSVCRT_VERSION__ >= __MSVCR80_DLL
/* ...whereas this group were introduced in MSVCR80.DLL, and its later
 * derivatives, but are not present in MSVCRT.DLL
 */
_CRTIMP __cdecl __MINGW_NOTHROW  int _fstat32 (int, struct __stat32 *);
_CRTIMP __cdecl __MINGW_NOTHROW  int _stat32 (const char *, struct __stat32 *);
_CRTIMP __cdecl __MINGW_NOTHROW  int _fstat32i64 (int, struct _stat32i64 *);
_CRTIMP __cdecl __MINGW_NOTHROW  int _fstat64i32 (int, struct _stat64i32 *);
_CRTIMP __cdecl __MINGW_NOTHROW  int _stat32i64 (const char *, struct _stat32i64 *);
_CRTIMP __cdecl __MINGW_NOTHROW  int _stat64i32 (const char *, struct _stat64i32 *);

#ifdef _USE_32BIT_TIME_T
/* We must provide inline replacements for the four MSVCRT.DLL functions
 * which have been withdrawn from MSVCR80.DLL, and its later derivatives;
 * this first set of replacements are compatible with their MSVCRT.DLL
 * equivalents, but require the user to define _USE_32BIT_TIME_T...
 */
__CRT_ALIAS __cdecl __MINGW_NOTHROW  int _fstat (int __v1, struct _stat *__v2)
  { return _fstat32 (__v1, (struct __stat32 *)(__v2)); }

__CRT_ALIAS __cdecl __MINGW_NOTHROW  int _stat (const char *__v1, struct _stat *__v2)
  { return _stat32  (__v1, (struct __stat32 *)(__v2)); }

__CRT_ALIAS __cdecl __MINGW_NOTHROW  int _fstati64 (int __v1, struct _stati64 *__v2)
  { return _fstat32i64 (__v1, (struct _stat32i64 *)(__v2)); }

__CRT_ALIAS __cdecl __MINGW_NOTHROW  int _stati64 (const char *__v1, struct _stati64 *__v2)
  { return _stat32i64  (__v1, (struct _stat32i64 *)(__v2)); }

#else	/* !_USE_32BIT_TIME_T */
/* ...whereas, the following alternatives emulate the brain-damaged
 * behaviour of Microsoft's own implementations, which take effect when
 * the user does not define _USE_32BIT_TIME_T; they break compatibility
 * with MSVCRT.DLL
 */
__CRT_ALIAS __cdecl __MINGW_NOTHROW  int _fstat (int __v1, struct _stat *__v2)
  { return _fstat64i32 (__v1, (struct _stat64i32 *)(__v2)); }

__CRT_ALIAS __cdecl __MINGW_NOTHROW  int _stat (const char *__v1, struct _stat *__v2)
  { return _stat64i32  (__v1, (struct _stat64i32 *)(__v2)); }

__CRT_ALIAS __cdecl __MINGW_NOTHROW  int _fstati64 (int __v1, struct _stati64 *__v2)
  { return _fstat64 (__v1, (struct __stat64 *)(__v2)); }

__CRT_ALIAS __cdecl __MINGW_NOTHROW  int _stati64 (const char *__v1, struct _stati64 *__v2)
  { return _stat64  (__v1,(struct __stat64*)(__v2)); }
#endif	/* !_USE_32BIT_TIME_T */

#ifndef _NO_OLDNAMES
/* Irrespective of the state of _USE_32BIT_TIME_T, we may provide inline
 * replacements for the stat() and fstat() functions, (which are missing
 * from MSVCR80.DLL and its later derivatives), simply by aliasing them
 * to their corresponding replacements with "uglified" names.
 */
__CRT_ALIAS __cdecl __MINGW_NOTHROW  int fstat (int __v1, struct _stat *__v2)
  { return _fstat (__v1, __v2); }

__CRT_ALIAS __cdecl __MINGW_NOTHROW  int stat (const char *__v1, struct _stat *__v2)
  { return _stat (__v1, __v2); }

#endif	/* !_NO_OLDNAMES */
#endif	/* __MSVCRT_VERSION__ >= __MSVCR80_DLL */
#endif	/* __MSVCRT_VERSION__ >= __MSVCR61_DLL */
#endif	/* __MSVCRT__ */
#endif	/* _SYS_STAT_H */

#if defined __MSVCRT__ && !(defined _SYS_STAT_H && defined _WCHAR_H)
/* This final group of function prototypes, specific to MSVCRT.DLL and its
 * non-free derivatives, are to be declared both when <sys/stat.h> is included
 * directly, and when it is selectively included by <wchar.h>; however, if both
 * _SYS_STAT_H and _WCHAR_H are defined, by the time we get to here, then this
 * must be the direct inclusion case, after having already declared these via
 * selective inclusion by <wchar.h>, and we should not declare these again;
 * (in particular, we should not repeat inline function implementations).
 */
#if __MSVCRT_VERSION__ < __MSVCR80_DLL
/* As is the case for their regular counterparts, this pair of functions
 * remain available in MSVCRT.DLL itself, but they are not exported from its
 * non-free derivatives from MSVCR80.DLL onwards, whence it is expected that
 * they will be replaced by inline implementations.
 */
_CRTIMP __cdecl __MINGW_NOTHROW  int _wstat(const wchar_t *, struct _stat *);
_CRTIMP __cdecl __MINGW_NOTHROW  int _wstati64 (const wchar_t *, struct _stati64 *);
#endif	/* __MSVCRT_VERSION__ < __MSVCR80_DLL */

#if __MSVCRT_VERSION__ >= __MSVCR61_DLL || _WIN32_WINNT >= _WIN32_WINNT_WIN2K
/* Similarly, this variant was introduced in MSVCR80.DLL, and was subsequently
 * added to MSVCRT.DLL with the release of Win2K...
 */
_CRTIMP __cdecl __MINGW_NOTHROW  int _wstat64 (const wchar_t *, struct __stat64 *);

#if __MSVCRT_VERSION__ >= __MSVCR80_DLL
/* ...whereas these variants are exclusive to the non-free MSVCR80.DLL, and
 * its later derivatives; they are not available in MSVCRT.DLL.
 */
_CRTIMP __cdecl __MINGW_NOTHROW  int _wstat32 (const wchar_t *, struct __stat32 *);
_CRTIMP __cdecl __MINGW_NOTHROW  int _wstat32i64 (const wchar_t *, struct _stat32i64 *);
_CRTIMP __cdecl __MINGW_NOTHROW  int _wstat64i32 (const wchar_t *, struct _stat64i32 *);

#ifdef _USE_32BIT_TIME_T
/* Once again, we must furnish inline replacements for the functions which
 * were withdrawn from MSVCR80.DLL and its later derivatives; these are the
 * implementations which remain compatible with MSVCRT.DLL, but require the
 * user to define _USE_32BIT_TIME_T...
 */
__CRT_ALIAS __cdecl __MINGW_NOTHROW  int _wstat (const wchar_t *__v1, struct _stat *__v2)
  { return _wstat32 (__v1, (struct __stat32 *)(__v2)); }

__CRT_ALIAS __cdecl __MINGW_NOTHROW  int _wstati64 (const wchar_t *__v1, struct _stati64 *__v2)
  { return _wstat32i64 (__v1, (struct _stat32i64 *)(__v2)); }

#else	/* !_USE_32BIT_TIME_T */
/* ...whereas these emulate the brain-damaged Microsoft behaviour, for the
 * case when the user does not define _USE_32BIT_TIME_T, breaking MSVCRT.DLL
 * compatibility.
 */
__CRT_ALIAS __cdecl __MINGW_NOTHROW  int _wstat (const wchar_t *__v1, struct _stat *__v2)
  { return _wstat64i32 (__v1, (struct _stat64i32 *)(__v2)); }

__CRT_ALIAS __cdecl __MINGW_NOTHROW  int _wstati64 (const wchar_t *__v1, struct _stati64 *__v2)
  { return _wstat64 (__v1, (struct __stat64 *)(__v2)); }

#endif	/* !_USE_32BIT_TIME_T */
#endif	/* __MSVCRT_VERSION__ >= 0x0800 */
#endif	/* __MSVCRT_VERSION__ >= 0x0601 */
#endif	/* __MSVCRT__ && !(_SYS_STAT_H && _WCHAR_H) */

_END_C_DECLS

#endif	/* ! RC_INVOKED */
#endif	/* !_SYS_STAT__H: $RCSfile: stat.h,v $: end of file */

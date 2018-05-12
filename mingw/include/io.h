/*
 * io.h
 *
 * System level I/O functions and types.
 *
 * $Id: io.h,v 82e816df4c9b 2016/10/30 18:40:10 keithmarshall $
 *
 * Written by Colin Peters <colin@bird.fu.is.saga-u.ac.jp>
 * Copyright (C) 1997-2004, 2007, 2009, 2010, 2014-2016, MinGW.org Project.
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
 *
 * NOTE: The file manipulation functions provided by Microsoft seem to
 * work with either slash (/) or backslash (\) as the directory separator;
 * (this is consistent with Microsoft's own documentation, on MSDN).
 *
 */
#ifndef _IO_H
#pragma GCC system_header

/* Defer definition of the _IO_H multiple inclusion guard, to allow
 * for selective inclusion by <wchar.h>, (in which case we should
 * NOT define it).
 */
#ifndef __WCHAR_H_SOURCED__
#define _IO_H

/* All MinGW headers must include <_mingw.h>; we may do it here,
 * assuming that <wchar.h> will have already take care to do so in
 * the selective inclusion case.
 */
#include <_mingw.h>

/* We also need time_t, and off_t, (and their variants); although
 * it gives us more than we really need, this will provide them...
 */
#include <sys/types.h>

#endif	/* !__WCHAR_H_SOURCED__ */

/* This will give us intptr_t, which we need in ALL cases, whether
 * including <io.h> directly, or selectively via <wchar.h>; (note: we
 * use the #include "..." form here, to ensure that we read the type
 * definition directly from the stdint.h header located in the same
 * directory as this <io.h> file).
 */
#define __need_intptr_t
#include "stdint.h"

/* Attributes of files as returned by _findfirst() et al.  MSDN is not
 * explicit about whether or not these should be defined when including
 * <wchar.h>, but since they complement the _wfindfirst() API, which is
 * declared there, it seems logical to make them visible in all cases
 * of <io.h> inclusion.
 */
#define _A_NORMAL	0x00000000
#define _A_RDONLY	0x00000001
#define _A_HIDDEN	0x00000002
#define _A_SYSTEM	0x00000004
#define _A_VOLID	0x00000008
#define _A_SUBDIR	0x00000010
#define _A_ARCH 	0x00000020

#ifndef RC_INVOKED

/* The maximum length of a file name.  It may be better to use the Windows'
 * GetVolumeInformation() function in preference to this constant, but hey,
 * this works!  In any case, we use this manifest constant when we declare
 * the _findfirst() API, so its definition must be visible in all places
 * where this, or any of its variants, is declared.
 *
 * Note that <stdio.h> also defines this, but we don't guard it, so that
 * the compiler has a chance to catch inconsistencies.
 */
#define FILENAME_MAX	(260)

/* We must define _fsize_t, but some compilers (including GCC prior to
 * version 4.0), may choke if we try to do so more than once...
 */
#if ! (defined _IO_H && defined _WCHAR_H) || defined __STRICT_ANSI__
 /* ...so DO NOT define it during direct <io.h> inclusion, (i.e. _IO_H
  * is defined), if <wchar.h> has already caused it to be defined, (i.e.
  * _WCHAR_H is ALSO defined, but __STRICT_ANSI__ is NOT).
  */
typedef	unsigned long	_fsize_t;
#endif	/* ! (_IO_H && _WCHAR_H) */

/* Functions for searching for files: _findfirst() sets errno to ENOENT,
 * and returns -1 if no match is found; otherwise it returns a handle to
 * be used in _findnext() and _findclose() calls. _findnext() may then be
 * used to identify further matches; it updates the search data, returning
 * zero, each time a further match is found, ultimately setting errno to
 * ENOENT, and returning -1 when no further match can be found.  When all
 * expected matches have been identified, _findclose() should be called,
 * to release the resources allocated to the search data.
 *
 * The API comprises several variants of the _findfirst() and _findnext()
 * functions, conforming generally to the usage model:
 *
 *  intptr_t handle = _findfirst (filespec, &search_data );
 *  if (handle >= (intptr_t)(0)) do { process search_data;
 *   } while (_findnext (handle, &search_data));
 *
 * where "filespec" represents a char *, or a wchar_t * specification,
 * (which may include wild cards), for a file name pattern to be matched,
 * and "search_data" represents a variant of the structure:
 */
#define __struct_finddata_t(__fd_time_t, __fd_size_t)			\
{ unsigned	attrib;		/* Attributes, see constants above. */	\
  __fd_time_t	time_create;						\
  __fd_time_t	time_access;	/* always midnight local time */	\
  __fd_time_t	time_write;						\
  __fd_size_t	size;							\
  __fd_name_t	name[FILENAME_MAX];	/* may include spaces. */	\
}

/* Time type and file size variations for __struct_finddata_t apply, for the
 * various functions comprising the file name search API, as tabulated below:
 *
 * Note: this is a reproduction of reference data as published in the MSDN
 * online documentation for the file name search API; it applies, specifically,
 * to the implementation of this API in the non-free run-time library versions
 * from MSVCR80.DLL onwards, (i.e. when __MSVCRT_VERSION__ is defined, and is
 * assigned a value >= 0x800).  When linking to the freely available MSVCRT.DLL
 * runtime, (__MSVCRT_VERSION__ should not be defined), or any earlier version
 * of the non-free run-time, the _USE_32BIT_TIME_T feature test is irrelevant;
 * the information presented in this table should be interpreted as if this
 * feature is always implicitly enabled.
 *
 *  Functions	       _USE_32BIT_TIME_T defined?    __fd_time_t     __fd_size_t
 *
 * _findfirst(),	Not defined			64-bit		32-bit
 * _wfindfirst()
 * _findfirst(),	Defined				32-bit		32-bit
 * _wfindfirst()
 *
 * _findfirst32(),	Not affected by the macro	32-bit		32-bit
 * _wfindfirst32()	definition
 *
 * _findfirst64(),	Not affected by the macro	64-bit		64-bit
 * _wfindfirst64()	definition
 *
 * _findfirsti64(),	Not defined			64-bit		64-bit
 * _wfindfirsti64()
 * _findfirsti64(),	Defined				32-bit		64-bit
 * _wfindfirsti64()
 *
 * _findfirst32i64(),	Not affected by the macro	32-bit		64-bit
 * _wfindfirst32i64()	definition
 *
 * _findfirst64i32(),	Not affected by the macro	64-bit		32-bit
 * _wfindfirst64i32()	definition
 *
 */
_BEGIN_C_DECLS

#ifdef _IO_H
#define __fd_name_t  char

/* The most universally available variants of the file name search
 * API employ either a generic representation of the related data, or
 * a variant in which the time stamps are represented generically, but
 * the file size is explicitly expressed as a 64-bit value.
 */
struct _finddata_t __struct_finddata_t (time_t, _fsize_t);
struct _finddatai64_t __struct_finddata_t (time_t, __int64);

/* Functions to manipulate data in either of these representations are
 * provided, as physical entities, in ALL versions of MSVCRT.DLL, and
 * in the non-free variants predating MSVCR80.DLL; (each such physical
 * function implementation interprets "generic" as 32-bit for both the
 * time_t and _fsize_t data fields).  From MSVCR80.DLL onward, there is
 * no physical implementation of these functions; they are emulated by
 * inline replacements (implemented below), which introduce ambiguity
 * in the interpretation of "generic", (noted as applicable): thus...
 */
#if __MSVCRT_VERSION__ < __MSVCR80_DLL
/* ...these physical function APIs are declared only when it is NOT
 * specified that MSVCR80.DLL or later is to be used.
 */
_CRTIMP __cdecl __MINGW_NOTHROW
intptr_t _findfirst (const char *, struct _finddata_t *);

_CRTIMP __cdecl __MINGW_NOTHROW
int _findnext (intptr_t, struct _finddata_t *);

_CRTIMP __cdecl __MINGW_NOTHROW
intptr_t _findfirsti64 (const char *, struct _finddatai64_t *);

_CRTIMP __cdecl __MINGW_NOTHROW
int _findnexti64 (intptr_t, struct _finddatai64_t *);

#endif	/* __MSVCRT_VERSION__ < __MSVCR80_DLL */

#if _WIN32_WINNT >= _WIN32_WINNT_WIN2K || __MSVCRT_VERSION__ >= __MSVCR61_DLL
/* The Win2K release of MSVCRT.DLL added a third variant of the API,
 * which had originally been introduced in MSVCR61.DLL; this variant
 * uses a data representation having both 64-bit time stamp values,
 * and 64-bit file size values.  (Note that there was no explictly
 * all 32-bit variant added at this point in the evolution of the
 * API; had there been, it would have been identically equivalent
 * to the original generic _findfirst()/_findnext() implementation).
 */
struct __finddata64_t __struct_finddata_t (__time64_t, __int64);
/*
 * Some MSDN documents, (particularly more recent documents), may
 * inconsistently refer to this structural type by the anomalous
 * name of _finddata64_t; support this anomaly.
 */
#define _finddata64_t  __finddata64_t

_CRTIMP __cdecl __MINGW_NOTHROW
intptr_t _findfirst64 (const char *, struct __finddata64_t *);

_CRTIMP __cdecl __MINGW_NOTHROW
int _findnext64 (intptr_t, struct __finddata64_t *);

#if __MSVCRT_VERSION__ >= __MSVCR80_DLL
/* MSVCR80.DLL introduced three new data structures, with explicitly
 * sized elements; in the order specified below, the first and second
 * of these three are identically equivalent to the representations of
 * struct _finddata_t, and struct _finddatai64_t, as they are required
 * to be implemented to match the implementations of the corresponding
 * functions in ALL versions of MSVCRT.DLL, whereas the third has no
 * counterpart, in ANY version of MSVCRT.DLL.
 */
struct _finddata32_t __struct_finddata_t (__time32_t, __int32);
struct _finddata32i64_t __struct_finddata_t (__time32_t, __int64);
struct _finddata64i32_t __struct_finddata_t (__time64_t, __int32);

/* The actual functions implemented in MSVCR80.DLL, and its derivatives,
 * corresponding to each of these three data structures are:
 */
_CRTIMP __cdecl __MINGW_NOTHROW
intptr_t _findfirst32 (const char *, struct _finddata32_t *);

_CRTIMP __cdecl __MINGW_NOTHROW
int _findnext32 (intptr_t, struct _finddata32_t *);

_CRTIMP __cdecl __MINGW_NOTHROW
intptr_t _findfirst32i64 (const char *, struct _finddata32i64_t *);

_CRTIMP __cdecl __MINGW_NOTHROW
int _findnext32i64 (intptr_t, struct _finddata32i64_t *);

_CRTIMP __cdecl __MINGW_NOTHROW
intptr_t _findfirst64i32 (const char *, struct _finddata64i32_t *);

_CRTIMP __cdecl __MINGW_NOTHROW
int _findnext64i32 (intptr_t, struct _finddata64i32_t *);

/* Since MSVCR80.DLL, and its later derivatives, provide no physical
 * implementations of the original file name search API functions, we
 * must emulate them, (as Microsoft do), by providing replacements in
 * the form of inline functions; in doing so, we also need to contend
 * with the insane ambiguity of Microsoft's _USE_32BIT_TIME_T feature
 * test; thus...
 */
#if defined _USE_32BIT_TIME_T
/* ...when the user has defined the _USE_32BIT_TIME_T macro, we provide
 * inline implementations which remain fully compatible with the actual
 * functions, as provided by MSVCRT.DLL; (note that we do not provide
 * __JMPSTUB__ or __LIBIMPL__ references here, since we have no basis
 * for a rational choice between ambiguous alternatives).
 */
__CRT_ALIAS __cdecl __MINGW_NOTHROW
intptr_t _findfirst (const char *__filespec, struct _finddata_t *__search)
{ return _findfirst32 (__filespec, (struct _finddata32_t *)(__search)); }

__CRT_ALIAS __cdecl __MINGW_NOTHROW
int _findnext (intptr_t __handle, struct _finddata_t *__search)
{ return _findnext32 (__handle, (struct _finddata32_t *)(__search)); }

__CRT_ALIAS __cdecl __MINGW_NOTHROW
intptr_t _findfirsti64 (const char *__filespec, struct _finddatai64_t *__search)
{ return _findfirst32i64 (__filespec, (struct _finddata32i64_t *)(__search)); }

__CRT_ALIAS __cdecl __MINGW_NOTHROW
int _findnexti64 (intptr_t __handle, struct _finddatai64_t *__search)
{ return _findnext32i64 (__handle, (struct _finddata32i64_t *)(__search)); }

#else	/* !_USE_32BIT_TIME_T */
/* ...but, when the user has NOT defined _USE_32BIT_TIME_T, we emulate
 * the brain damaged default behaviour of Microsoft's own SDKs.  This
 * accommodates an extended range of valid time stamp values, but it
 * utterly destroys compatibility with MSVCRT.DLL!
 */
__CRT_ALIAS __cdecl __MINGW_NOTHROW
intptr_t _findfirst (const char *__filespec, struct _finddata_t *__search)
{ return _findfirst64i32 (__filespec, (struct _finddata64i32_t *)(__search)); }

__CRT_ALIAS __cdecl __MINGW_NOTHROW
int _findnext (intptr_t __handle, struct _finddata_t *__search)
{ return _findnext64i32 (__handle, (struct _finddata64i32_t *)(__search)); }

__CRT_ALIAS __cdecl __MINGW_NOTHROW
intptr_t _findfirsti64 (const char *__filespec, struct _finddatai64_t *__search)
{ return _findfirst64 (__filespec, (struct __finddata64_t *)(__search)); }

__CRT_ALIAS __cdecl __MINGW_NOTHROW
int _findnexti64 (intptr_t __handle, struct _finddatai64_t *__search)
{ return _findnext64 (__handle, (struct __finddata64_t *)(__search)); }

#endif	/* !_USE_32BIT_TIME_T */
#endif	/* __MSVCRT_VERSION__ >= __MSVCR80_DLL */
#endif	/* >= WIN2K || >= MSVCR61.DLL */

#undef  __fd_name_t
#endif	/* _IO_H */

#if ! (defined _IO_H && defined _WCHAR_H)
/* Wide character file name analogue of the file name search API;
 * declared both here, in <io.h>, and via selective inclusion from
 * <wchar.h>, it mirrors all aspects of the preceding API declarations,
 * except that all file names are expressed as wchar_t.
 */
#define __fd_name_t  wchar_t

/* Thus, the original API comprised this pair of generically specified
 * data structures...
 */
struct _wfinddata_t __struct_finddata_t (time_t, _fsize_t);
struct _wfinddatai64_t __struct_finddata_t (time_t, __int64);

#if __MSVCRT_VERSION__ < __MSVCR80_DLL
/* ...with corresponding functions to manipulate them; once again, there
 * is no physical implementation of these in MSVCR80.DLL or later, so we
 * declare them only when it is NOT specified that one of these run-time
 * library versions is to be used.
 */
_CRTIMP __cdecl __MINGW_NOTHROW
intptr_t _wfindfirst (const wchar_t *, struct _wfinddata_t *);

_CRTIMP __cdecl __MINGW_NOTHROW
int _wfindnext (intptr_t, struct _wfinddata_t *);

_CRTIMP __cdecl __MINGW_NOTHROW
intptr_t _wfindfirsti64 (const wchar_t *, struct _wfinddatai64_t *);

_CRTIMP __cdecl __MINGW_NOTHROW
int _wfindnexti64 (intptr_t, struct _wfinddatai64_t *);

#endif	/* __MSVCRT_VERSION__ < __MSVCR80_DLL */

#if _WIN32_WINNT >= _WIN32_WINNT_WIN2K || __MSVCRT_VERSION__ >= __MSVCR61_DLL
/* Win2K also added an all-64-bit variant of the _wfinddata API to
 * MSVCRT.DLL, after it originally appeared in MSVCR61.DLL.
 */
struct __wfinddata64_t __struct_finddata_t (__time64_t, __int64);
/*
 * As in the case of the __finddata64_t structure, some MSDN
 * documents, (particularly more recent documents), may refer
 * to __wfinddata64_t by the inconsistently anomalous name of
 * _wfinddata64_t; also support this anomaly.
 */
#define _wfinddata64_t  __wfinddata64_t

_CRTIMP __cdecl __MINGW_NOTHROW
intptr_t _wfindfirst64 (const wchar_t *, struct __wfinddata64_t *);

_CRTIMP __cdecl __MINGW_NOTHROW
int _wfindnext64 (intptr_t, struct __wfinddata64_t *);

#if __MSVCRT_VERSION__ >= __MSVCR80_DLL
/* MSVCR80.DLL introduced a further three variants, which remain
 * exclusive to it and its later derivatives; none of these are
 * available in any version of MSVCRT.DLL.
 */
struct _wfinddata32_t    __struct_finddata_t (__time32_t, __int32);
struct _wfinddata32i64_t __struct_finddata_t (__time32_t, __int64);
struct _wfinddata64i32_t __struct_finddata_t (__time64_t, __int32);
/*
 * As in the __finddata64_t vs. _finddata64_t, and __wfinddata64_t
 * vs. _wfinddata64_t anomalous cases, there is at least one historic
 * MSDN reference to a __wfinddata32_t structural type, in a context
 * where _wfinddata32_t may be expected.  In this case, it appears
 * that __wfinddata32_t is the anomaly, and that it may be peculiar
 * to the VS-2005 documentation; nevertheless, the corresponding
 * definition is provided here, for the possible convenience of
 * any user who may depend on it, (but please avoid it).
 */
#define __wfinddata32_t  _wfinddata32_t

_CRTIMP __cdecl __MINGW_NOTHROW
intptr_t _wfindfirst32 (const wchar_t *, struct _wfinddata32_t *);

_CRTIMP __cdecl __MINGW_NOTHROW
int _wfindnext32 (intptr_t, struct _wfinddata32_t *);

_CRTIMP __cdecl __MINGW_NOTHROW
intptr_t _wfindfirst32i64 (const wchar_t *, struct _wfinddata32i64_t *);

_CRTIMP __cdecl __MINGW_NOTHROW
int _wfindnext32i64 (intptr_t, struct _wfinddata32i64_t *);

_CRTIMP __cdecl __MINGW_NOTHROW
intptr_t _wfindfirst64i32 (const wchar_t *, struct _wfinddata64i32_t *);

_CRTIMP __cdecl __MINGW_NOTHROW
int _wfindnext64i32 (intptr_t, struct _wfinddata64i32_t *);

/* Once again, the variants of this API with generic time_t data
 * fields are NOT supported by any physical function implementation
 * in MSVCR80.DLL and later, so must be emulated; (again, we do not
 * provide any __JMPSTUB__ or __LIBIMPL__ references).
 */
#ifdef _USE_32BIT_TIME_T
/* First, we provide inline implementations which retain compatibility
 * with the physical implementations in MSVCRT.DLL; they require the
 * user to define the _USE_32BIT_TIME_T feature test macro...
 */
__CRT_ALIAS __cdecl __MINGW_NOTHROW
intptr_t _wfindfirst (const wchar_t *__filespec, struct _wfinddata_t *__search)
{ return _wfindfirst32 (__filespec, (struct _wfinddata32_t *)(__search)); }

__CRT_ALIAS __cdecl __MINGW_NOTHROW
int _wfindnext (intptr_t __handle, struct _wfinddata_t *__search)
{ return _wfindnext32 (__handle, (struct _wfinddata32_t *)(__search)); }

__CRT_ALIAS __cdecl __MINGW_NOTHROW
intptr_t _wfindfirsti64 (const wchar_t *__filespec, struct _wfinddatai64_t *__search)
{ return _wfindfirst32i64 (__filespec, (struct _wfinddata32i64_t *)(__search)); }

__CRT_ALIAS __cdecl __MINGW_NOTHROW
int _wfindnexti64 (intptr_t __handle, struct _wfinddatai64_t *__search)
{ return _wfindnext32i64 (__handle, (struct _wfinddata32i64_t *)(__search)); }

#else	/* !_USE_32BIT_TIME_T */
/* ...whereas the brain damaged Microsoft defaults, which apply when
 * _USE_32BIT_TIME_T is not defined, break MSVCRT.DLL compatibility.
 */
__CRT_ALIAS __cdecl __MINGW_NOTHROW
intptr_t _wfindfirst (const wchar_t *__filespec, struct _wfinddata_t *__search)
{ return _wfindfirst64i32 (__filespec, (struct _wfinddata64i32_t *)(__search)); }

__CRT_ALIAS __cdecl __MINGW_NOTHROW
int _wfindnext (intptr_t __handle, struct _wfinddata_t *__search)
{ return _wfindnext64i32 (__handle, (struct _wfinddata64i32_t *)(__search)); }

__CRT_ALIAS __cdecl __MINGW_NOTHROW
intptr_t _wfindfirsti64 (const wchar_t *__filespec, struct _wfinddatai64_t *__search)
{ return _wfindfirst64 (__filespec, (struct __wfinddata64_t *)(__search)); }

__CRT_ALIAS __cdecl __MINGW_NOTHROW
int _wfindnexti64 (intptr_t __handle, struct _wfinddatai64_t *__search)
{ return _wfindnext64 (__handle, (struct __wfinddata64_t *)(__search)); }

#endif	/* !_USE_32BIT_TIME_T */
#endif	/* __MSVCRT_VERSION__ >= MSVCR80.DLL */
#endif	/* >= _WIN2K || >= MSVCR61.DLL */

#undef __fd_name_t
#endif	/* ! (_IO_H && _WCHAR_H) */

/* We have no further use for the __struct_finddata_t macro; delete it!
 */
#undef __struct_finddata_t

/* MSDN documents that <io.h> must be included to get a prototype for
 * _findclose(), which kind of negates the usefulness of declaring the
 * wchar_t variants of the file name search API in <wchar.h>; mitigate
 * this anomaly, by declaring _findclose() such that either <io.h> or
 * <wchar.h> will provide it.
 */
_CRTIMP __cdecl __MINGW_NOTHROW  int _findclose (intptr_t);

#ifdef _IO_H
/* The following declarations are to be exposed only when <io.h> is
 * included directly.
 */
_CRTIMP __cdecl __MINGW_NOTHROW  int _chdir (const char *);
_CRTIMP __cdecl __MINGW_NOTHROW  char *_getcwd (char *, int);
_CRTIMP __cdecl __MINGW_NOTHROW  int _mkdir (const char *);
_CRTIMP __cdecl __MINGW_NOTHROW  char *_mktemp (char *);
_CRTIMP __cdecl __MINGW_NOTHROW  int _rmdir (const char *);
_CRTIMP __cdecl __MINGW_NOTHROW  int _chmod (const char *, int);

#ifdef __MSVCRT__
_CRTIMP __cdecl __MINGW_NOTHROW  __int64 _filelengthi64 (int);
_CRTIMP __cdecl __MINGW_NOTHROW  __int64 _lseeki64 (int, __int64, int);
_CRTIMP __cdecl __MINGW_NOTHROW  __int64 _telli64 (int);

#ifndef __NO_MINGW_LFS
__CRT_INLINE __off64_t lseek64 (int, __off64_t, int);
__CRT_INLINE __JMPSTUB__(( FUNCTION = lseek64, REMAPPED = _lseeki64 ))
__off64_t lseek64 (int fd, __off64_t offset, int whence)
{ return _lseeki64 (fd, (__int64)(offset), whence); }
#endif

#endif /* __MSVCRT__ */

#ifndef _NO_OLDNAMES

#ifndef _UWIN
_CRTIMP __cdecl __MINGW_NOTHROW  int chdir (const char *);
_CRTIMP __cdecl __MINGW_NOTHROW  char *getcwd (char *, int);
_CRTIMP __cdecl __MINGW_NOTHROW  int mkdir (const char *);
_CRTIMP __cdecl __MINGW_NOTHROW  char *mktemp (char *);
_CRTIMP __cdecl __MINGW_NOTHROW  int rmdir (const char *);
_CRTIMP __cdecl __MINGW_NOTHROW  int chmod (const char *, int);
#endif /* _UWIN */

#endif /* !_NO_OLDNAMES */
#endif	/* _IO_H */

_END_C_DECLS

#endif	/* ! RC_INVOKED */

#ifdef _IO_H
/* Still applicable only when <io.h> is included directly, but we also
 * allow the resource compiler to see these.
 *
 * TODO: Maximum number of open handles has not been tested; we just set
 * it the same as FOPEN_MAX.
 */
#define HANDLE_MAX	FOPEN_MAX

/* Some defines for _access() mode checking: (Microsoft doesn't define
 * them, but it doesn't seem to hurt to add them ... or perhaps it does
 * hurt; on newer versions of MSVCRT.DLL, an access mode of 1 may raise
 * an invalid parameter error!
 */
#define F_OK	0	/* Check for file existence */
#define X_OK	1	/* MS access() doesn't check for execute permission. */
#define W_OK	2	/* Check for write permission */
#define R_OK	4	/* Check for read permission */
#endif	/* _IO_H */

#ifndef RC_INVOKED

_BEGIN_C_DECLS

#ifdef _IO_H
/* Again, specific to <io.h>, but not applicable to resources.
 */
_CRTIMP __cdecl __MINGW_NOTHROW  int _access (const char *, int);
_CRTIMP __cdecl __MINGW_NOTHROW  int _chsize (int, long);
_CRTIMP __cdecl __MINGW_NOTHROW  int _close (int);
_CRTIMP __cdecl __MINGW_NOTHROW  int _commit (int);

/* NOTE: The only significant permissions bit appears to be
 * bit 7 (0x80), the "owner write permission" bit (on FAT).
 */
_CRTIMP __cdecl __MINGW_NOTHROW  int _creat (const char *, int);

_CRTIMP __cdecl __MINGW_NOTHROW  int _dup (int);
_CRTIMP __cdecl __MINGW_NOTHROW  int _dup2 (int, int);
_CRTIMP __cdecl __MINGW_NOTHROW  long _filelength (int);
_CRTIMP __cdecl __MINGW_NOTHROW  long _get_osfhandle (int);
_CRTIMP __cdecl __MINGW_NOTHROW  int _isatty (int);

#ifndef	_STREAM_COMPAT
/* In a very odd turn of events this function is excluded from those
 * files which define _STREAM_COMPAT. This is required in order to
 * build GNU libio because of a conflict with _eof in streambuf.h
 * line 107. Actually I might just be able to change the name of
 * the enum member in streambuf.h ... we'll see. TODO
 */
_CRTIMP __cdecl __MINGW_NOTHROW  int _eof (int);
#endif

/* Locking files: attribute constants are defined in <sys/locking.h>,
 * which users are expected to include.
 */
_CRTIMP __cdecl __MINGW_NOTHROW  int _locking (int, int, long);

_CRTIMP __cdecl __MINGW_NOTHROW  long _lseek (int, long, int);

/* Opening files, (or streams); manifest constants for construction of
 * the mode flags are defined in <fctl.h>, which users are expected to
 * include.  The "optional" third argument is an unsigned int; it is
 * REQUIRED, when creating a new file, to specify the permissions to
 * apply when said file is released by the creating process.
 */
_CRTIMP __cdecl __MINGW_NOTHROW  int _open (const char *, int, ...);

_CRTIMP __cdecl __MINGW_NOTHROW  int _open_osfhandle (intptr_t, int);
_CRTIMP __cdecl __MINGW_NOTHROW  int _pipe (int *, unsigned int, int);
_CRTIMP __cdecl __MINGW_NOTHROW  int _read (int, void *, unsigned int);
_CRTIMP __cdecl __MINGW_NOTHROW  int _setmode (int, int);

/* Microsoft declares remove() & rename(), (but not their wchar_t
 * counterparts), in <io.h> as well as in <stdio.h>; these should be
 * consistent with <stdio.h>, but we trust the compiler to alert us
 * (eventually) if not.
 */
_CRTIMP __cdecl __MINGW_NOTHROW  int remove (const char *);
_CRTIMP __cdecl __MINGW_NOTHROW  int rename (const char *, const char *);

/* Open files with specified sharing attributes; manifest constants
 * for constructing the sharing mode argument are in <share.h>, which
 * users must include.  The optional fourth argument is an unsigned
 * int, specifing permissions to apply after closing a new file.
 */
_CRTIMP __cdecl __MINGW_NOTHROW  int _sopen (const char *, int, int, ...);

_CRTIMP __cdecl __MINGW_NOTHROW  long _tell (int);

/* FIXME: POSIX wants umask() in <sys/stat.h>, and, although vague,
 * Microsoft may agree; we declare it here as well!
 */
_CRTIMP __cdecl __MINGW_NOTHROW  int _umask (int);
_CRTIMP __cdecl __MINGW_NOTHROW  int _unlink (const char *);
_CRTIMP __cdecl __MINGW_NOTHROW  int _write (int, const void *, unsigned int);
#endif	/* _IO_H */

#if defined __MSVCRT__ && ! (defined _IO_H && defined _WCHAR_H)
/* These wchar_t functions are made available for selective inclusion
 * by <wchar.h>, in addition to direct inclusion of <io.h>, but they
 * are only supported by MSVCRT.DLL and derivatives; they don't exist
 * in CRTDLL.DLL.  Furthermore, if both _IO_H and _WCHAR_H have been
 * defined, by the time we get here, then this must be direct <io.h>
 * inclusion, and we've already declared these by prior inclusion of
 * <wchar.h>; there is no need to declare them again.
 */
_CRTIMP __cdecl __MINGW_NOTHROW  int _waccess (const wchar_t *, int);
_CRTIMP __cdecl __MINGW_NOTHROW  int _wchmod (const wchar_t *, int);
_CRTIMP __cdecl __MINGW_NOTHROW  int _wcreat (const wchar_t *, int);
_CRTIMP __cdecl __MINGW_NOTHROW  int _wunlink (const wchar_t *);
_CRTIMP __cdecl __MINGW_NOTHROW  int _wopen (const wchar_t *, int, ...);
_CRTIMP __cdecl __MINGW_NOTHROW  int _wsopen (const wchar_t *, int, int, ...);
_CRTIMP __cdecl __MINGW_NOTHROW  wchar_t *_wmktemp (wchar_t *);
#endif /* __MSVCRT__ && ! (_IO_H && _WCHAR_H) */

#if defined _IO_H && ! defined _NO_OLDNAMES
/* Non-underscored versions of non-ANSI functions to improve portability;
 * these are implemented in libmoldname.a, and once again are declared
 * only when <io.h> is included directly.
 */
#ifndef _UWIN
_CRTIMP __cdecl __MINGW_NOTHROW  int access (const char*, int);
_CRTIMP __cdecl __MINGW_NOTHROW  int chsize (int, long );
_CRTIMP __cdecl __MINGW_NOTHROW  int close (int);
_CRTIMP __cdecl __MINGW_NOTHROW  int creat (const char*, int);
_CRTIMP __cdecl __MINGW_NOTHROW  int dup (int);
_CRTIMP __cdecl __MINGW_NOTHROW  int dup2 (int, int);
_CRTIMP __cdecl __MINGW_NOTHROW  int eof (int);
_CRTIMP __cdecl __MINGW_NOTHROW  long filelength (int);
_CRTIMP __cdecl __MINGW_NOTHROW  int isatty (int);
_CRTIMP __cdecl __MINGW_NOTHROW  long lseek (int, long, int);
_CRTIMP __cdecl __MINGW_NOTHROW  int open (const char*, int, ...);
_CRTIMP __cdecl __MINGW_NOTHROW  int read (int, void*, unsigned int);
_CRTIMP __cdecl __MINGW_NOTHROW  int setmode (int, int);
_CRTIMP __cdecl __MINGW_NOTHROW  int sopen (const char*, int, int, ...);
_CRTIMP __cdecl __MINGW_NOTHROW  long tell (int);
_CRTIMP __cdecl __MINGW_NOTHROW  int umask (int);
_CRTIMP __cdecl __MINGW_NOTHROW  int unlink (const char*);
_CRTIMP __cdecl __MINGW_NOTHROW  int write (int, const void*, unsigned int);
#endif /* !_UWIN */

#ifdef __USE_MINGW_ACCESS
/* Old versions of MSVCRT.DLL's access() just ignored X_OK, while the
 * version shipped with Vista fails; this inline implementation of the
 * portably named access() function protects against such failure.
 */
#define access(__fname,__mode)  __mingw_access (__fname, __mode)
static __inline__ int __mingw_access (const char* __fname, int __mode)
  { return  _access (__fname, __mode & ~X_OK); }
#endif	/* _USE_MINGW_ACCESS */

#if 0
/* FIXME:
 * Wide character versions: may also be declared in <wchar.h>.
 * Where do these live?  Not in libmoldname.a nor in libmsvcrt.a;
 * do they exist at all?
 */
int 		waccess(const wchar_t *, int);
int 		wchmod(const wchar_t *, int);
int 		wcreat(const wchar_t *, int);
long 		wfindfirst(wchar_t *, struct _wfinddata_t *);
int 		wfindnext(long, struct _wfinddata_t *);
int 		wunlink(const wchar_t *);
int 		wrename(const wchar_t *, const wchar_t *);
int 		wopen(const wchar_t *, int, ...);
int 		wsopen(const wchar_t *, int, int, ...);
wchar_t * 	wmktemp(wchar_t *);
#endif

#endif	/* !_NO_OLDNAMES */

_END_C_DECLS

#endif	/* ! RC_INVOKED */
#endif	/* !_IO_H: $RCSfile: io.h,v $: end of file */

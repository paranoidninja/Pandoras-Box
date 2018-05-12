/*
 * sys/types.h
 *
 * Definitions of (primarily POSIX) system data types.
 *
 * $Id: types.h,v 6ceeab058f30 2016/10/13 20:03:56 keithmarshall $
 *
 * Written by Colin Peters <colin@bird.fu.is.saga-u.ac.jp>
 * Copyright (C) 1997-1999, 2001, 2003, 2004, 2008, 2011, 2014-2016,
 *   MinGW.org Project.
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
#ifndef _SYS_TYPES_H
#pragma GCC system_header

/* All the headers include this file.
 */
#include <_mingw.h>

/* Duplicates of some type definitions from here are also to be
 * provided by other system headers; use __need_TYPENAME selector
 * macros to make them selectively visible...
 */
#if ! defined __need_off_t && ! defined __need___off64_t \
 && ! defined __need_ssize_t && ! defined __need_time_t
 /*
  * ...and define the multiple inclusion guard macro for this
  * header, ONLY IF no such selector macro is defined.
  */
#define _SYS_TYPES_H
#endif

#ifndef RC_INVOKED
/* First handle those typedefs which POSIX requires us to be able
 * to expose selectively, via other system headers.
 */
#if ! defined __have_typedef_off_t \
 && ( defined _SYS_TYPES_H || defined __need_off_t )
 /* We base this on an implementation specific private typedef,
  * analogous to our __off64_t (defined below)...
  */
  typedef __int32  __off32_t;

 /* The POSIX off_t typedef is uglified, by Microsoft, as _off_t;
  * ensure that we provide support for the Microsoft form...
  */
  typedef __off32_t  _off_t;

# if _POSIX_C_SOURCE || ! defined _NO_OLDNAMES
  /* ...but note that this form should ALWAYS be preferred when
   * compiling POSIX compatible source code, and should also be
   * made generally available unless Microsoft's old names have
   * been suppressed, (by defining _NO_OLDNAMES).
   */
  typedef _off_t  off_t;
# endif
# if __GNUC__ < 4
  /* Some compilers, including GCC prior to v4, may get upset
   * if we try to specify these typedefs more than once.
   */
#  define __have_typedef_off_t
# endif
#endif
#undef __need_off_t

#if ! defined __have_typedef___off64_t \
 && ( defined _SYS_TYPES_H || defined __need___off64_t )
 /* This is neither an ISO-C standard type, nor even a POSIX
  * standard type; keep it runtime implementation specific.
  */
  typedef __int64  __off64_t;

# ifndef __STRICT_ANSI__
  /* GCC itself, (specifically libgfortran.a), gratuitously
   * assumes that non-standard type off64_t is defined; make
   * it so, pending upstream correction.
   */
  typedef __off64_t  off64_t;
# endif

# if __GNUC__ < 4
  /* Some compilers, including GCC prior to v4, may get upset
   * if we try to specify these typedefs more than once.
   */
#  define __have_typedef___off64_t
# endif
#endif
#undef __need___off64_t

#if ! defined __have_typedef_ssize_t \
 && ( defined _SYS_TYPES_H || defined __need_ssize_t )
 /* POSIX ssize_t typedef, uglified by Microsoft as _ssize_t; ensure
  * that we support the Microsoft form...
  */
  typedef int  _ssize_t;

# if _POSIX_C_SOURCE || ! defined _NO_OLDNAMES
  /* ...but note that this form should ALWAYS be preferred when
   * compiling POSIX compatible source code, and should also be
   * made generally available unless Microsoft's old names have
   * been suppressed, (by defining _NO_OLDNAMES).
   */
  typedef _ssize_t  ssize_t;
# endif
# if __GNUC__ < 4
  /* Some compilers, including GCC prior to v4, may get upset
   * if we try to specify these typedefs more than once.
   */
#  define __have_typedef_ssize_t
# endif
#endif
#undef __need_ssize_t

#if ! defined __have_typedef_time_t \
 && ( defined _SYS_TYPES_H || defined __need_time_t )
 /* Current versions of MSVC define time_t ambiguously, in terms of
  * one of the following unambiguous internal types:
  */
  typedef __int32 __time32_t;	/* unambiguous 32-bit time_t */
  typedef __int64 __time64_t;	/* unambiguous 64-bit time_t */

# if __MSVCRT_VERSION__ < __MSVCR80_DLL || defined _USE_32BIT_TIME_T
  /* From MSVCR80.DLL onwards, Microsoft have royally messed up the
   * definition of time_t; maintain POSIX consistency, (as MSVCRT.DLL
   * itself does), unless the user is explicitly using one of these
   * brain damaged DLL variants, and has not elected to retain the
   * 32-bit time_t representation.
   */
   typedef __time32_t time_t;

# else
  /* Microsoft's brain damaged default, from MSVCR80.DLL onwards.
   */
   typedef __time64_t time_t;
# endif
# if __GCC__ < 4
  /* Assume any compiler which is not GCC-4.x or newer may require
   * guarding against repeated time_t typedefs.
   */
#  define __have_typedef_time_t  1
# endif
#endif
#undef __need_time_t

#ifdef _SYS_TYPES_H
/* This is normal <sys/types.h> inclusion, i.e. for its own sake.
 *
 * A small subset of the required type definitions are actually
 * furnished by <stddef.h>; get them by selective inclusion...
 */
#define __need_size_t
#define __need_ptrdiff_t
#define __need_wchar_t
#include <stddef.h>

/* Today, Microsoft generally prefers to prefix POSIX type names
 * with an ugly initial underscore; ensure that we provide support
 * for this ungainly practice.
 */
#ifdef __MSVCRT__
 /* Additionally, note that _dev_t is a special case, requiring
  * this definition when linking with MSVCRT.DLL...
  */
typedef unsigned int	_dev_t;

#else
 /* ...but this alternative, when linking with CRTDLL.DLL
  */
typedef short		_dev_t;

#endif
 /* ...while the remaining type names have consistent definitions,
  * regardless of any particular DLL association.
  */
typedef short		_ino_t;
typedef unsigned short	_mode_t;
typedef int		_pid_t;
typedef int		_sigset_t;

/* Users who value portability should prefer...
 */
#if _POSIX_C_SOURCE || ! defined _NO_OLDNAMES
 /* ...the standard POSIX type names, (which are consistent with
  * earlier Microsoft naming practice, and are also historically
  * exposed by MinGW, except when _NO_OLDNAMES is defined).
  */
typedef _dev_t		 dev_t;
typedef _ino_t		 ino_t;
typedef _mode_t 	 mode_t;
typedef _pid_t		 pid_t;
typedef _sigset_t	 sigset_t;
#endif

typedef __int64 	 fpos64_t;

#if _POSIX_C_SOURCE
/* useconds_t is an obsolete POSIX data type; we continue to define
 * it here, for backward compatibility, but we flag it as deprecated,
 * due to its obsolete status.
 */
typedef unsigned long useconds_t __MINGW_ATTRIB_DEPRECATED;
#endif
#endif  /* _SYS_TYPES_H normal inclusion */

#endif	/* ! RC_INVOKED */
#endif	/* !_SYS_TYPES_H: $RCSfile: types.h,v $: end of file */

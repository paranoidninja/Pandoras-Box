/*
 * limits.h
 *
 * Manifest constants defining the sizes of integral types.
 *
 * $Id: limits.h,v 2499eb7464e6 2017/01/29 14:24:00 keithmarshall $
 *
 * Written by Colin Peters <colin@bird.fu.is.saga-u.ac.jp>
 * Copyright (C) 1997, 1999-2001, 2004, 2005, 2010, 2012, 2017,
 *   MinGW.org Project
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
#ifndef _LIMITS_H
#pragma GCC system_header
#define _LIMITS_H

/* All MinGW headers are required to include <_mingw.h>
 */
#include <_mingw.h>

/* File system limits
 *
 * TODO (REVIEW): Are NAME_MAX and OPEN_MAX file system limits, or not?
 * Are they the same as FILENAME_MAX and FOPEN_MAX from <stdio.h>?
 *
 * NOTE: PATH_MAX is the POSIX equivalent for Microsoft's MAX_PATH; the
 * two are semantically identical, with a limit of 259 characters for the
 * path name, plus one for a terminating NUL, making a total of 260.
 */
#ifndef __STRICT_ANSI__
# define PATH_MAX	260
#endif

/* Characteristics of the char data type.
 *
 * FIXME: Is MB_LEN_MAX correct?  Probably yes, for Microsoft MBCS, which
 * effectively seem to all be DBCS.
 */
#define CHAR_BIT	8
#define MB_LEN_MAX	2

#define SCHAR_MIN	(-128)
#define SCHAR_MAX	127

#define UCHAR_MAX	255

#if '\x80' < 0
/* FIXME: is this safe?  I think it might just be testing
 * the preprocessor, not the compiler itself.
 */
# define CHAR_MIN	SCHAR_MIN
# define CHAR_MAX	SCHAR_MAX
#else
# define CHAR_MIN	0
# define CHAR_MAX	UCHAR_MAX
#endif

/* Maximum and minimum values for ints.
 */
#define INT_MAX		2147483647
#define INT_MIN		(-INT_MAX-1)

#define UINT_MAX	0xFFFFFFFF

/* Maximum and minimum values for shorts.
 */
#define SHRT_MAX	32767
#define SHRT_MIN	(-SHRT_MAX-1)

#define USHRT_MAX	0xFFFF

/* Maximum and minimum values for longs and unsigned longs;
 * this isn't correct for Alphas, which have 64 bit longs, but
 * that is probably no longer a concern.
 */
#define LONG_MAX	2147483647L
#define LONG_MIN	(-LONG_MAX-1)

#define ULONG_MAX	0xFFFFFFFFUL

#ifndef __STRICT_ANSI__
/* POSIX wants this.
 */
#define SSIZE_MAX	LONG_MAX
#endif

#if _ISOC99_SOURCE
/* Implicitly defined in <_mingw.h>, (or explicitly defined by
 * the user), for C99, C++, or POSIX.1-2001; make these ISO-C99
 * macro names available.
 */
#define LLONG_MAX	9223372036854775807LL
#define LLONG_MIN	(-LLONG_MAX - 1)
#define ULLONG_MAX	(2ULL * LLONG_MAX + 1)
#endif

#if defined __GNUC__ && ! defined __STRICT_ANSI__
/* The GNU C compiler also allows 'long long int', but we don't
 * want that capability polluting the strict ANSI namespace.
 */
#define LONG_LONG_MAX	9223372036854775807LL
#define LONG_LONG_MIN	(-LONG_LONG_MAX-1)
#define ULONG_LONG_MAX	(2ULL * LONG_LONG_MAX + 1)

/* MSVC compatibility
 */
#define _I64_MIN	LONG_LONG_MIN
#define _I64_MAX	LONG_LONG_MAX
#define _UI64_MAX	ULONG_LONG_MAX

#endif	/* __GNUC__ && !__STRICT_ANSI__ */
#endif	/* !_LIMITS_H: $RCSfile: limits.h,v $: end of file */

/*
 * stdint.h
 *
 * Integer type definitions, as prescribed by ISO-C9x Section 7.18
 * Based on ISO/IEC SC22/WG14 9899 Committee draft (SC22 N2794)
 *
 * $Id: stdint.h,v 0e4f78dbc1ba 2016/06/17 14:16:01 keithmarshall $
 *
 * Written by Danny Smith <danny_r_smith_2001@yahoo.co.nz>
 * Copyright (C) 2000-2002, 2004, 2005, 2007, 2009, 2016, MinGW.org Project.
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
#ifndef _STDINT_H
#pragma GCC system_header

/* To support selective definition of just intptr_t or uintptr_t,
 * we defer definition of the normal multiple inclusion guard macro,
 * until we've determined that neither selection is active.
 */
#if ! defined __need_intptr_t && ! defined __need_uintptr_t
#define _STDINT_H

/* All MinGW system headers are expected to include <_mingw.h>;
 * ensure that we have done so.
 */
#include <_mingw.h>

/* We need to duplicate the definitions of wint_t and wchar_t, as
 * they are defined in <stddef.h>; get them, by selective inclusion
 * from that header itself.
 */
#define __need_wint_t
#define __need_wchar_t
#include <stddef.h>

/* 7.18.1.1  Exact-width integer types.
 */
typedef signed char		int8_t;
typedef unsigned char		uint8_t;
typedef short			int16_t;
typedef unsigned short		uint16_t;
typedef int			int32_t;
typedef unsigned		uint32_t;
typedef long long		int64_t;
typedef unsigned long long	uint64_t;

/* 7.18.1.2  Minimum-width integer types.
 */
typedef signed char		int_least8_t;
typedef unsigned char		uint_least8_t;
typedef short			int_least16_t;
typedef unsigned short		uint_least16_t;
typedef int			int_least32_t;
typedef unsigned		uint_least32_t;
typedef long long		int_least64_t;
typedef unsigned long long	uint_least64_t;

/*  7.18.1.3  Fastest minimum-width integer types
 *  Not actually guaranteed to be fastest for all purposes
 *  Here we use the exact-width types for 8 and 16-bit ints.
 */
typedef signed char		int_fast8_t;
typedef unsigned char		uint_fast8_t;
typedef short			int_fast16_t;
typedef unsigned short		uint_fast16_t;
typedef int			int_fast32_t;
typedef unsigned  int		uint_fast32_t;
typedef long long		int_fast64_t;
typedef unsigned long long	uint_fast64_t;

/* We actually DO need both selections, which had to be omitted
 * to get us into this conditional block; force them!
 */
#define __need_intptr_t
#define __need_uintptr_t

#endif	/* !__need_intptr_t && !__need_uintptr_t */

/* 7.18.1.4  Integer types capable of holding object pointers.
 */
#if defined __need_intptr_t && ! defined __intptr_t
#define __intptr_t __intptr_t
#ifdef _WIN64
 typedef __int64 __intptr_t;
#else
 typedef int __intptr_t;
#endif
typedef __intptr_t intptr_t;

#endif	/* __need_intptr_t */
#undef __need_intptr_t

#if defined __need_uintptr_t && ! defined __uintptr_t
#define __uintptr_t __uintptr_t
#ifdef _WIN64
 typedef unsigned __int64 __uintptr_t;
#else
 typedef unsigned int __uintptr_t;
#endif
typedef __uintptr_t uintptr_t;

#endif	/* __need_uintptr_t */
#undef __need_uintptr_t

#ifdef  _STDINT_H
/* 7.18.1.5  Greatest-width integer types.
 */
typedef long long  intmax_t;
typedef unsigned long long uintmax_t;

/* 7.18.2  Limits of specified-width integer types.
 * (always defined in C, but C++ needs __STDC_LIMIT_MACROS)
 */
#if ! defined __cplusplus || defined __STDC_LIMIT_MACROS

/* 7.18.2.1  Limits of exact-width integer types.
 */
#define INT8_MIN		(-128)
#define INT16_MIN		(-32768)
#define INT32_MIN		(-2147483647 - 1)
#define INT64_MIN		(-9223372036854775807LL - 1)

#define INT8_MAX		127
#define INT16_MAX		32767
#define INT32_MAX		2147483647
#define INT64_MAX		9223372036854775807LL

#define UINT8_MAX		0xffU			/* 255U */
#define UINT16_MAX		0xffffU			/* 65535U */
#define UINT32_MAX		0xffffffffUL		/* 4294967295U */
#define UINT64_MAX		0xffffffffffffffffULL	/* 18446744073709551615ULL */

/* 7.18.2.2  Limits of minimum-width integer types.
 */
#define INT_LEAST8_MIN		INT8_MIN
#define INT_LEAST16_MIN 	INT16_MIN
#define INT_LEAST32_MIN 	INT32_MIN
#define INT_LEAST64_MIN 	INT64_MIN

#define INT_LEAST8_MAX		INT8_MAX
#define INT_LEAST16_MAX 	INT16_MAX
#define INT_LEAST32_MAX 	INT32_MAX
#define INT_LEAST64_MAX 	INT64_MAX

#define UINT_LEAST8_MAX 	UINT8_MAX
#define UINT_LEAST16_MAX	UINT16_MAX
#define UINT_LEAST32_MAX	UINT32_MAX
#define UINT_LEAST64_MAX	UINT64_MAX

/* 7.18.2.3  Limits of fastest minimum-width integer types.
 */
#define INT_FAST8_MIN		INT8_MIN
#define INT_FAST16_MIN		INT16_MIN
#define INT_FAST32_MIN		INT32_MIN
#define INT_FAST64_MIN		INT64_MIN

#define INT_FAST8_MAX		INT8_MAX
#define INT_FAST16_MAX		INT16_MAX
#define INT_FAST32_MAX		INT32_MAX
#define INT_FAST64_MAX		INT64_MAX

#define UINT_FAST8_MAX		UINT8_MAX
#define UINT_FAST16_MAX 	UINT16_MAX
#define UINT_FAST32_MAX 	UINT32_MAX
#define UINT_FAST64_MAX 	UINT64_MAX

/* 7.18.2.4  Limits of integer types capable of holding object pointers.
 */
#ifdef _WIN64
# define INTPTR_MIN		INT64_MIN
# define INTPTR_MAX		INT64_MAX
# define UINTPTR_MAX		UINT64_MAX
#else
# define INTPTR_MIN		INT32_MIN
# define INTPTR_MAX		INT32_MAX
# define UINTPTR_MAX		UINT32_MAX
#endif

/* 7.18.2.5  Limits of greatest-width integer types.
 */
#define INTMAX_MIN		INT64_MIN
#define INTMAX_MAX		INT64_MAX
#define UINTMAX_MAX		UINT64_MAX

/* 7.18.3  Limits of other integer types.
 */
#define PTRDIFF_MIN		INTPTR_MIN
#define PTRDIFF_MAX		INTPTR_MAX

#define SIG_ATOMIC_MIN		INTPTR_MIN
#define SIG_ATOMIC_MAX		INTPTR_MAX

#define SIZE_MAX		UINTPTR_MAX

/* The following pair are also defined in <wchar.h>, but leave them
 * unguarded, so that the compiler may check for consistency.
 */
#define WCHAR_MIN		0
#define WCHAR_MAX		0xffff /* UINT16_MAX */

/* wint_t is unsigned short for compatibility with MS runtime
 */
#define WINT_MIN		0
#define WINT_MAX		0xffff /* UINT16_MAX */

#endif	/* !__cplusplus || __STDC_LIMIT_MACROS */

/* 7.18.4  Macros for integer constants.
 * (always defined in C, but C++ needs __STDC_CONSTANT_MACROS)
 */
#if ! defined __cplusplus || defined __STDC_CONSTANT_MACROS

/* 7.18.4.1  Macros for minimum-width integer constants
 *
 * According to Douglas Gwyn <gwyn@arl.mil>:
 *  "This spec was changed in ISO/IEC 9899:1999 TC1; in ISO/IEC
 *  9899:1999 as initially published, the expansion was required
 *  to be an integer constant of precisely matching type, which
 *  is impossible to accomplish for the shorter types on most
 *  platforms, because C99 provides no standard way to designate
 *  an integer constant with width less than that of type int.
 *  TC1 changed this to require just an integer constant
 *  EXPRESSION with PROMOTED type".
 */
#define INT8_C(val)		val
#define UINT8_C(val)		val
#define INT16_C(val)		val
#define UINT16_C(val)		val

#define INT32_C(val)		val
#define UINT32_C(val)		val##U
#define INT64_C(val)		val##LL
#define UINT64_C(val)		val##ULL

/* 7.18.4.2  Macros for greatest-width integer constants.
 */
#define INTMAX_C(val)		INT64_C(val)
#define UINTMAX_C(val)		UINT64_C(val)

#endif  /* !__cplusplus || __STDC_CONSTANT_MACROS */
#endif	/* _STDINT_H */

#endif	/* !_STDINT_H: $RCSfile: stdint.h,v $: end of file */

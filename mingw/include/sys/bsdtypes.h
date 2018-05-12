/*
 * bsdtypes.h
 *
 * Defines non-standard data types, typically used in BSD source code,
 * and adopted by the Windows sockets implementation; users are advised
 * to avoid using these data types, and use standard types instead.
 *
 * $Id: bsdtypes.h,v 52143273fae9 2017/10/25 14:45:18 keithmarshall $
 *
 * Abstracted from MinGW.org's WinSock implementation
 * Copyright (C) 2017, MinGW.org Project
 *
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 */
#ifndef _SYS_BSDTYPES_H
#pragma  GCC system_header
#define _SYS_BSDTYPES_H

/* This additional guard macro is required, to co-operate with newlib's
 * <sys/types.h>, which also defines the data types defined herein.
 */
#ifndef _BSDTYPES_DEFINED

/* All MinGW.org headers are required to include <_mingw.h>
 */
#include <_mingw.h>

#if ! __IN_MINGWRT_TESTSUITE__ \
 && ! (defined _BSD_SOURCE || defined _WINSOCK_H)
 /* Users are STRONGLY recommended to avoid using the non-standard BSD
  * data types defined herein, unless compiling code which proclaims its
  * _BSD_SOURCE heritage, or which uses the Windows Sockets API, (which
  * has ill-advisedly adopted them).
  */
# warning "Use of non-standard BSD type definitions is ill-advised."
#endif

/* Use "unsigned foo" instead of these "u_foo" shorthand aliases.
 */
typedef unsigned char	u_char;
typedef unsigned short	u_short;
typedef unsigned int	u_int;
typedef unsigned long	u_long;

#define _BSDTYPES_DEFINED
#endif	/* !_BSDTYPES_DEFINED */
#endif	/* _SYS_BSDTYPES_H: $RCSfile: bsdtypes.h,v $: end of file */

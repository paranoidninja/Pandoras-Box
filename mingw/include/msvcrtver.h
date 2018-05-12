/*
 * msvcrtver.h
 *
 * Macros for identification of specific versions of MSVC runtime
 * libraries, which may be substituted for MSVCRT.DLL
 *
 * $Id: msvcrtver.h,v 6d8ad2c4dde7 2015/06/19 11:43:28 keithmarshall $
 *
 * Written by Keith Marshall <keithmarshall@users.sourceforge.net>
 * Copyright (C) 2015, MinGW.org Project
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
#ifndef _MSVCRTVER_H
#define _MSVCRTVER_H
#pragma GCC system_header

/* When it is intended to link an application with any one of the
 * MSVC version specific MSVCRxx.DLL libraries, rather than with the
 * OS default MSVCRT.DLL, the particular substitute MSVCRxx.DLL may
 * be specified as any one of the following...
 */
#define __MSVCR60_DLL		0x0600
#define __MSVCR61_DLL		0x0601
#define __MSVCR70_DLL		0x0700
#define __MSVCR71_DLL		0x0701
#define __MSVCR80_DLL		0x0800
#define __MSVCR90_DLL		0x0900
#define __MSVCR100_DLL		0x1000
#define __MSVCR110_DLL		0x1100
#define __MSVCR120_DLL		0x1200

#ifndef __MSVCRT_VERSION__
/* This may be set, when the intent is to link with any of the above
 * non-freely distributable MSVCRxx.DLL libraries, rather than with the
 * pseudo-free MSVCRT.DLL provided as an OS component.  High byte is the
 * major version number, low byte is the minor; however, users are advised
 * to use custom GCC specs files to set this, while also substituting the
 * appropriate library in place of MSVCRT.DLL, rather than to simply set
 * it directly.
 *
 * It should be noted that __MSVCRT_VERSION__ is NOT a good indicator of
 * evolving MSVCRT.DLL features; that is better accomplished by using the
 * NTDDI_VERSION setting from the Windows API.  Thus, users of MSVCRT.DLL
 * should NOT set __MSVCRT_VERSION__, leaving us to establish a default,
 * equivalent to MSVCR60.DLL, which seems reasonably well aligned with
 * the feature set of the earliest MSVCRT.DLL version we support.
 */
# define __MSVCRT_VERSION__  __MSVCR60_DLL
#endif

/* This is an exception to the normal rule, that all mingwrt system
 * header files should include _mingw.h, since inclusion of _mingw.h
 * itself will cause this file to be included.  Thus, we recommend
 * that this file should not be included directly, but we do not
 * forbid doing so; however, in this event...
 */
#ifndef __MINGW_H
/* ...we must ensure that _mingw.h has also been included.
 */
# include <_mingw.h>
#endif

#endif /* !_MSVCRTVER_H: $RCSfile: msvcrtver.h,v $: end of file */

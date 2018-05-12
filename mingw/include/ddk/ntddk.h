/*
 * ddk/ntddk.h
 *
 * Windows Device Driver Kit -- common defines:
 *  DBG               -  Debugging enabled/disabled (0/1)
 *  POOL_TAGGING      -  Enable pool tagging
 *  _X86_             -  X86 environment
 *  __USE_NTOSKRNL__  -  Use ntoskrnl.exe instead of kernel32.dll
 *
 * $Id: ntddk.h,v 0e0292c3eba8 2015/11/14 21:06:19 keithmarshall $
 *
 * Written by Casper S. Hornstrup  <chorns@users.sourceforge.net>
 * Copyright (C) 2002, 2004, 2006, 2015, MinGW.org Project.
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
#ifndef _DDK_NTDDK_H
#define _DDK_NTDDK_H
#pragma GCC system_header

#ifndef __USE_NTOSKRNL__
#define __USE_NTOSKRNL__ 1
#endif

#include <stdarg.h>
#include <windef.h>
#include <ntdef.h>
#include <basetyps.h>

_BEGIN_C_DECLS

/* Base types, structures and definitions.
 */
typedef short CSHORT;
typedef CONST int CINT;
typedef CONST char *PCSZ;

#ifndef STATIC
#define STATIC static
#endif

#ifndef CALLBACK
#define CALLBACK
#endif

#ifndef DECL_IMPORT
#define DECL_IMPORT __declspec(dllimport)
#endif

#ifndef DECL_EXPORT
#define DECL_EXPORT __declspec(dllexport)
#endif

/* Windows NT status codes.
 */
#include "ntstatus.h"

/* Windows NT definitions exported to user mode.
 */
#include <winnt.h>

/* Windows Device Driver Kit.
 */
#include "winddk.h"

/* Definitions only in Windows XP.
 */
#include "winxp.h"

/* Definitions only in Windows 2000.
 */
#include "win2k.h"

/* Definitions only in Windows NT 4.
 */
#include "winnt4.h"

_END_C_DECLS

#endif /* _DDK_NTDDK_H: $RCSfile: ntddk.h,v $: end of file */

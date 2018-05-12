/*
 * _winsock.h
 *
 * A private system header, included wherever other system headers may
 * require declaration of the WinSock API, without explicitly specifying
 * a particular WinSock version dependency.
 *
 *
 * $Id: _winsock.h,v 7258c92e2a48 2017/11/14 20:07:02 keith $
 *
 * Written by Keith Marshall <keith@users.osdn.me>
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
#ifndef _WINSOCK_H
#pragma GCC system_header

/* The WinSock API dependency may be satisfied by including either <winsock.h>
 * or <winsock2.h>; note that, regardless of whichever of these alternatives we
 * choose, _WINSOCK_H will become defined, thus satisfying the repeat inclusion
 * guard for this header file itself, without any requirement for us to provide
 * an explicit definition herein.
 */
#include <sdkddkver.h>
#if _WIN32_WINNT >= _WIN32_WINNT_NT4
/* When the target operating system is WinNT4, or later, we prefer to support
 * the WinSock v2 API, by default; (this is consistent with the default choice
 * which was traditionally specified within MinGW.org's <windows.h>)...
 */
#include <winsock2.h>

#else
/* ...whereas, for operating systems predating WinNT4, we elect to offer
 * support for only WinSock v1.1
 */
#include <winsock.h>
#endif

#endif	/* !_WINSOCK_H: $RCSfile: _winsock.h,v $: end of file */

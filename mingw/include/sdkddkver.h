/*
 * sdkddkver.h
 *
 * Macros to set up the compilation environment, such that it provides
 * support for a user specified host OS version, (default Win2K).
 *
 * $Id: sdkddkver.h,v d7ac2ac748a9 2016/11/25 21:29:02 keithmarshall $
 *
 * Written by Earnie Boyd  <earnie@users.sourceforge.net>
 * Copyright (C) 2012, 2013, 2015, MinGW.org Project
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
#ifndef _SDKDDKVER_H
#define _SDKDDKVER_H
#pragma GCC system_header

/* Define masks for extracting version components from NTDDI_VERSION;
 * values and names are guessed based on comments in the documentation; see
 * http://msdn.microsoft.com/en-us/library/windows/desktop/aa383745(v=vs.85).aspx
 */
#define OSVERSION_MASK  	0xFFFF0000
#define SPVERSION_MASK  	0x0000FF00
#define SUBVERSION_MASK 	0x000000FF

/* Macros to facilitate such extraction; derived from comments on MSDN or
 * on social.microsoft.com
 */
#define OSVER(ver)		((ver) & OSVERSION_MASK)
#define SPVER(ver)		(((ver) & SPVERSION_MASK) >> 8)
#define SUBVER(ver)		((ver) & SUBVERSION_MASK)
#define WINNTVER(ver)		((ver) >> 16)

/* Macros to construct a minimal NTDDI_VERSION from a _WIN32_WINNT value.
 */
#define NTDDI_VERSION_FROM_WIN32_WINNT(ver) _NTDDI_VERSION_FROM_WIN32_WINNT(ver)
#define _NTDDI_VERSION_FROM_WIN32_WINNT(ver) ver##0000

/* Version constants specifying _WIN32_WINNT versions; these are defined at
 * http://msdn.microsoft.com/en-us/library/windows/desktop/aa383745(v=vs.85).aspx
 * (values for legacy platforms have been inferred from historical knowledge).
 */
#define _WIN32_WINNT_NT4	0x0400		/* Windows NT4 */
#define _WIN32_WINNT_NT4E	0x0401		/* Windows NT4E */
#define _WIN32_WINNT_NT4SP3	0x0403		/* Windows NT4 + ServicePack 3 */
#define _WIN32_WINDOWS_95	0x0400		/* Windows 95 */
#define _WIN32_WINDOWS_98	0x0410		/* Windows 98 */
#define _WIN32_WINDOWS_ME	0x0490		/* Windows Millenium Edition */
#define _WIN32_WINNT_WIN2K	0x0500		/* Windows 2000 */
#define _WIN32_WINNT_WINXP	0x0501		/* Windows XP */
#define _WIN32_WINNT_WS03	0x0502		/* Windows Server 2003 */
#define _WIN32_WINNT_WIN6	0x0600		/* Alias for Windows Vista */
#define _WIN32_WINNT_VISTA	0x0600		/* Windows Vista */
#define _WIN32_WINNT_WS08	0x0600		/* Windows Server 2008 */
#define _WIN32_WINNT_LONGHORN	0x0600		/* Alias for Windows Vista */
#define _WIN32_WINNT_WIN7	0x0601		/* Windows 7 */
#define _WIN32_WINNT_WIN8	0x0602		/* Windows 8 */
#define _WIN32_WINNT_WINBLUE	0x0603		/* Windows 8.1 */

/* Version constants specifying Internet Explorer versions; also defined at
 * http://msdn.microsoft.com/en-us/library/windows/desktop/aa383745(v=vs.85).aspx
 */
#define _WIN32_IE_IE50  	0x0500
#define _WIN32_IE_IE501 	0x0501
#define _WIN32_IE_IE55  	0x0550
#define _WIN32_IE_IE56  	0x0560
#define _WIN32_IE_IE60  	0x0600
#define _WIN32_IE_IE60SP1 	0x0601
#define _WIN32_IE_IE60SP2 	0x0603
#define _WIN32_IE_IE70  	0x0700
#define _WIN32_IE_IE80  	0x0800

#define _WIN32_IE_IE30  	0x0300
#define _WIN32_IE_IE301 	0x0301
#define _WIN32_IE_IE302 	0x0302
#define _WIN32_IE_IE40  	0x0400
#define _WIN32_IE_IE401 	0x0401

/* Version constants specifying NTDDI_VERSION; these are also defined at
 * http://msdn.microsoft.com/en-us/library/windows/desktop/aa383745(v=vs.85).aspx
 */
#define __NTDDI_WIN5		0x05000000
#define __NTDDI_WIN51		0x05010000
#define __NTDDI_WIN52		0x05020000
#define __NTDDI_WIN6		0x06000000
#define __NTDDI_WIN61		0x06010000
#define __NTDDI_WIN62		0x06020000
#define __NTDDI_WIN63		0x06030000
#define __NTDDI_SP0		0x00000000
#define __NTDDI_SP1		0x00000100
#define __NTDDI_SP2		0x00000200
#define __NTDDI_SP3		0x00000300
#define __NTDDI_SP4		0x00000400

#define NTDDI_WIN2K		__NTDDI_WIN5 + __NTDDI_SP0
#define NTDDI_WIN2KSP1		__NTDDI_WIN5 + __NTDDI_SP1
#define NTDDI_WIN2KSP2		__NTDDI_WIN5 + __NTDDI_SP2
#define NTDDI_WIN2KSP3		__NTDDI_WIN5 + __NTDDI_SP3
#define NTDDI_WIN2KSP4		__NTDDI_WIN5 + __NTDDI_SP4

#define NTDDI_WINXP		__NTDDI_WIN51 + __NTDDI_SP0
#define NTDDI_WINXPSP1		__NTDDI_WIN51 + __NTDDI_SP1
#define NTDDI_WINXPSP2		__NTDDI_WIN51 + __NTDDI_SP2
#define NTDDI_WINXPSP3		__NTDDI_WIN51 + __NTDDI_SP3

#define NTDDI_WS03		__NTDDI_WIN52 + __NTDDI_SP0
#define NTDDI_WS03SP1		__NTDDI_WIN52 + __NTDDI_SP1
#define NTDDI_WS03SP2		__NTDDI_WIN52 + __NTDDI_SP2

#define NTDDI_VISTA		__NTDDI_WIN6 + __NTDDI_SP0
#define NTDDI_VISTASP1		__NTDDI_WIN6 + __NTDDI_SP1
#define NTDDI_VISTASP2		__NTDDI_WIN6 + __NTDDI_SP2

#define NTDDI_LONGHORN		NTDDI_VISTA

#define NTDDI_WIN6		NTDDI_VISTA
#define NTDDI_WIN6SP1		NTDDI_VISTASP1
#define NTDDI_WIN6SP2		NTDDI_VISTASP2

#define NTDDI_WS08		__NTDDI_WIN6 + __NTDDI_SP1

#define NTDDI_WIN7		__NTDDI_WIN61 + __NTDDI_SP0

#define NTDDI_WIN8		__NTDDI_WIN62 + __NTDDI_SP0

#define NTDDI_WINBLUE		__NTDDI_WIN63 + __NTDDI_SP0

/* Although NTDDI_VERSION is now the preferred designator for the
 * level of support required from the operating system, legacy code
 * is likely to have specified WINVER, from which _WIN32_WINNT may
 * be inferred.
 */
#if defined WINVER && ! defined _WIN32_WINNT
# define _WIN32_WINNT WINVER

/* Additionally, legacy code intended for deployment on the Win9x
 * series operating systems may have specified _WIN32_WINDOWS, as
 * an alternative to, or in addition to, _WIN32_WINNT.
 */
#elif defined _WIN32_WINDOWS && ! defined _WIN32_WINNT
# define _WIN32_WINNT _WIN32_WINDOWS
#endif

/* Stipulate defaults; check consistency of any user specified overrides.
 */
#ifdef NTDDI_VERSION
# ifdef _WIN32_WINNT
#  if _WIN32_WINNT != WINNTVER(NTDDI_VERSION)
#   error "_WIN32_WINNT setting conflicts with specified NTDDI_VERSION"
#  endif
# else
#  define _WIN32_WINNT WINNTVER(NTDDI_VERSION)
#  ifndef WINVER
#   define WINVER _WIN32_WINNT
#  endif
# endif
#endif

#ifndef _WIN32_WINNT
# ifdef WINVER
#  define _WIN32_WINNT WINVER
# else
#  ifdef _WARN_DEFAULTS
#   warning "Assuming default setting of _WIN32_WINNT_WIN2K for _WIN32_WINNT"
#  endif
#  define _WIN32_WINNT _WIN32_WINNT_WIN2K
# endif
#endif

#ifndef WINVER
# define WINVER _WIN32_WINNT
#elif WINVER != _WIN32_WINNT
 /* TODO(REVIEW): is this appropriate for WINVER consistency checking?
  */
# error "_WIN32_WINNT setting conflicts with specified WINVER"
#endif

#ifndef NTDDI_VERSION
# ifdef _WARN_DEFAULTS
#  warning "Assuming default NTDDI_VERSION setting to match _WIN32_WINNT"
# endif
# define NTDDI_VERSION NTDDI_VERSION_FROM_WIN32_WINNT(_WIN32_WINNT)
#endif

/* Map GCC architecture identification macros to their MSVC equivalents.
 * This mapping was previously specified in <winnt.h>, and duplicated in
 * <windows.h>; it is now only defined here, because both <windows.h> and
 * <winnt.h> must include this file anyway, and the potentially error prone
 * burden of maintaining duplicates is as unnecessary as it is undesirable.
 */
#ifndef _M_IX86
 /* Note that we must process the _M_IX86 equivalent macros in diminishing
  * order of processor version, since GCC defines __i386__ as identification
  * for the X86 processor family, in addition to any one of the other three
  * macros, which may be used to identify a particular processor version.
  */
# if defined(__i686__)
#  define _M_IX86		600

# elif defined(__i586__)
#  define _M_IX86		500

# elif defined(__i486__)
#  define _M_IX86		400

# elif defined(__i386__)
#  define _M_IX86		300
# endif
#endif

/* The preceding logic may have established the host type as X86, or it
 * may have done nothing at all; we must check further.
 */
#ifdef _M_IX86
 /* We've established that we ARE compiling for an X86 host; any MinGW32
  * compiler SHOULD have set this for us already...
  */
# ifndef _X86_
  /* ...but cross-check it anyway, in case the user may have some unusual
   * compiler configuration in place.
   */
#  define _X86_ 		1
# endif

# ifndef _M_IX86_FP
  /* MSVC defines this, to provide additional information about particular
   * capabilties of the X86 host environment; specifically...
   */
#  ifdef __SSE2__
   /* ...this indicates that the SSE2 instruction set (or better) may be
    * assumed to be supported...
    */
#   define _M_IX86_FP		2

#  elif defined(__SSE__)
   /* ...whereas, this promises only basic SSE instruction set support...
    */
#   define _M_IX86_FP		1

#  else
   /* ...and this disallows its use, entirely.
    */
#   define _M_IX86_FP		0
#  endif
# endif

/* When not compiling for an X86 host; check mapping from other possible
 * GCC architecture identifiers, to their MSVC equivalents.
 */
#elif defined(__x86_64__) || defined(__amd64__)
 /* This represents an Intel X86-64, or (compatible) AMD-64 processor;
  * MSVC defines...
  */
# ifndef _M_X64
  /* ...this to represent the former, together with...
   */
#  define _M_X64		1
# endif
# ifndef _M_AMD64
  /* ...this alias, to represent the latter.
   */
#  define _M_AMD64		1
# endif

#elif defined(__ia64__)
 /* This represents an Intel Itanium processor, which MSVC designates
  * by defining this feature test macro.
  */
# ifndef _M_IA64
#  define _M_IA64		1
# endif
#endif	/* !_M_IX86 */

#endif /* _SDKDDKVER_H: $RCSfile: sdkddkver.h,v $: end of file */

/*
 * w32api.h
 *
 * Package version identification, operating system support level set up,
 * and "convenience" macros to be shared by all package header files.
 *
 * $Id: w32api.h.in,v 0bd67cc9bc86 2017/03/20 20:01:38 keithmarshall $
 *
 * Written by Earnie Boyd  <earnie@users.sourceforge.net>
 * Copyright (C) 2001-2011, 2015, 2016, MinGW.org Project
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
#ifndef _W32API_H
#define _W32API_H
#pragma GCC system_header

/* Package version identification: formerly specified as a simple
 * dotted numeric pair representing major.minor, this doesn't adapt
 * well to the inclusion of the patch-level, since the dotted triplet
 * representation of major.minor.patch is not a valid representation
 * of a numeric entity.  Thus, from version 3.18 onwards we adopt a
 * representation which encodes the version as a long integer value,
 * expressing:
 *
 *   __W32API_VERSION = 1,000,000 * major + 1,000 * minor + patch
 *
 * DO NOT EDIT these package version assignments manually; they are
 * derived from the package version specification within configure.ac,
 * whence they are propagated automatically, at package build time.
 */
#define __W32API_VERSION           5000002L
#define __W32API_MAJOR_VERSION           5
#define __W32API_MINOR_VERSION           0
#define __W32API_PATCHLEVEL              2

/* The underlying operating system platform version, and its
 * identifying macros for application support, are established by:
 */
#include <sdkddkver.h>

/* The following defines are for documentation purposes.  Although not used
 * within it, they were provided in earlier versions of the Win32 API, as a
 * convenience for users who wished to symbolically declare a minimum level
 * of required operating system and Internet Explorer version support, when
 * assigning WINVER, _WIN32_WINDOWS, _WIN32_WINNT, and _WIN32_IE values.
 *
 * Each of the following "old name" macros is now considered deprecated in
 * favour of manifest "preferred name" macro definitions from <sdkddkver.h>.
 * Hence, redefine each in terms of the appropriate "preferred name" macro;
 * new code should avoid the old names, and use the preferred name instead.
 *
 *
 * _WIN32_WINDOWS and/or WINVER may be set to any of the following manifest
 * values, to specify a minimum Win9x support level requirement:
 *
 *      Old Name	Preferred Name
 *      -------------	------------------
 */
#define Windows95	_WIN32_WINDOWS_95
#define Windows98	_WIN32_WINDOWS_98
#define WindowsME	_WIN32_WINDOWS_ME

/* _WIN32_WINNT and/or WINVER may be set to any of the following manifest
 * values, to specify a minimum WinNT support level requirement:
 *
 *      Old Name	Preferred Name
 *      -------------	------------------
 */
#define WindowsNT4	_WIN32_WINNT_NT4
#define Windows2000	_WIN32_WINNT_WIN2K
#define WindowsXP	_WIN32_WINNT_WINXP
#define Windows2003	_WIN32_WINNT_WS03
#define WindowsVista	_WIN32_WINNT_VISTA

/* _WIN32_IE may be set to any of the following manifest values, to
 * specify a minimum Internet Explorer support level requirement:
 *
 *      Old Name	Preferred Name
 *      -------------	------------------
 */
#define IE3		_WIN32_IE_IE30
#define IE301		_WIN32_IE_IE301
#define IE302		_WIN32_IE_IE302
#define IE4		_WIN32_IE_IE40
#define IE401		_WIN32_IE_IE401
#define IE5		_WIN32_IE_IE50
#define IE5a		_WIN32_IE_IE50
#define IE5b		_WIN32_IE_IE50
#define IE501		_WIN32_IE_IE501
#define IE55		_WIN32_IE_IE55
#define IE56		_WIN32_IE_IE56
#define IE6		_WIN32_IE_IE60
#define IE601		_WIN32_IE_IE60SP1
#define IE602		_WIN32_IE_IE60SP2
#define IE7		_WIN32_IE_IE70


/* Only Microsoft could attempt to justify this insanity: when building
 * a UTF-16LE application -- apparently their understanding of Unicode is
 * limited to this -- the C/C++ runtime requires that the user must define
 * the _UNICODE macro, while to use the Windows API's UTF-16LE capabilities,
 * it is the UNICODE macro, (without the leading underscore), which must be
 * defined.  The (bogus) explanation appears to be that it is the C standard
 * which dictates the requirement for the leading underscore, to avoid any
 * possible conflict with a user defined symbol; (bogus because the macro
 * must be user defined anyway -- it is not a private symbol -- and in
 * any case, the Windows API already reserves the UNICODE symbol as
 * a user defined macro, with equivalent intent.
 *
 * The real explanation, of course, is that this is just another example
 * of Microsoft irrationality; in any event, there seems to be no sane
 * scenario in which defining one without the other would be required,
 * or indeed would not raise potential for internal inconsistency, so we
 * ensure that either both are, or neither is defined.
 */
#if defined UNICODE && ! defined _UNICODE
# define _UNICODE  UNICODE
#elif defined _UNICODE && ! defined UNICODE
# define UNICODE  _UNICODE
#endif
/* Related to the UNICODE macro definition, there are many functions in
 * the Win32 API with a generic name, which is mapped to a variant with
 * wchar_t UTF-16LE encoding of string arguments, in cases when UNICODE
 * is defined, as facilitated by the following macro...
 */
#ifdef UNICODE
 /* ...by appending a "W" suffix to the generic function name...
  */
# define __AW_SUFFIXED__(__NAME__)  __NAME__##W
#else
 /* ...or by appending an "A" suffix, to select an ANSI variant with
  * char encoding of string arguments, when UNICODE is not defined.
  */
# define __AW_SUFFIXED__(__NAME__)  __NAME__##A
#endif
/* Further related, the __AW_EXTENDED__ macro reproduces the effect of
 * __AW_SUFFIXED__, with the addition of a single underscore character
 * separating the base name from the appropriate suffix.
 */
#define __AW_EXTENDED__(__NAME__)  __AW_SUFFIXED__(__NAME__##_)

/* __AW_EXTENDED__ may often be used to map manifest string constants.
 * The following triplet provide a convenient mechanism to derive the
 * UNICODE variant of the string from its ANSI definition; (note that
 * this requires a two stage expansion, to ensure that the "L" prefix
 * is attached to the expansion of the ANSI string definition, rather
 * than just to the defining macro name).
 */
#define __AW_STRING_A__(__TEXT__)  __TEXT__
#define __AW__WCHAR_T__(__TEXT__)  __AW_STRING_A__(L##__TEXT__)
#define __AW_STRING_W__(__TEXT__)  __AW__WCHAR_T__(__TEXT__)

/* Further uses of __AW_SUFFIXED__ and __AW_EXTENDED__, encapsulated
 * within __AW_ALIAS__ and __AW_ALIAS_EX__; each provides a convenient
 * generic mapping for type names with alternative representations for
 * UNICODE and non-UNICODE usage.
 */
#define __AW_ALIAS__(__NAME__)     __AW_SUFFIXED__(__NAME__) __NAME__
#define __AW_ALIAS_EX__(__NAME__)  __AW_EXTENDED__(__NAME__) __NAME__

#ifdef __cplusplus
/* When compiling C++ code, these macros provide a convenient notation
 * for designating those sections of system header files which declare
 * prototypes for API functions with "C" binding...
 */
# define _EXTERN_C       extern "C"
# define _BEGIN_C_DECLS  extern "C" {
# define _END_C_DECLS    }

#else
/* ...while remaining transparent, when compiling C code.
 */
# define _EXTERN_C       extern
# define _BEGIN_C_DECLS
# define _END_C_DECLS
#endif

#endif /* ! _W32API_H: $RCSfile: w32api.h.in,v $: end of file */

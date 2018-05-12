/*
 * strings.h
 *
 * API declarations for POSIX.1-2008 string functions supported by MinGW.
 *
 * $Id: strings.h,v afe05b778eef 2017/01/10 19:43:48 keithmarshall $
 *
 * Written by Keith Marshall <keithmarshall@users.sourceforge.net>
 * Copyright (C) 2015-2017, MinGW.org Project.
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
#ifndef _STRINGS_H
#pragma GCC system_header

/* In addition to the POSIX strcasecmp() and strncasecmp() functions,
 * this header declares the prototypes for the MSVC specific stricmp()
 * and strincmp() functions, which MSVC expects to find in <string.h>;
 * thus, we support selective partial inclusion by <string.h>, to make
 * this pair of function prototypes available as MSVC expects...
 */
#ifndef __STRING_H_SOURCED__
/* ...and we define the _STRINGS_H guard macro only when NOT included
 * in this partial fashion.
 */
#define _STRINGS_H

/* All MinGW system headers must include <_mingw.h>; if we had been
 * sourced by <string.h>, we could safely assume that it had already
 * done this, but since that doesn't apply in this case, we must do
 * it ourselves.
 */
#include <_mingw.h>

#ifndef RC_INVOKED
/* POSIX.1-2008 requires this header to expose the typedef for size_t; to
 * ensure consistency, we import this from GCC's own <stddef.h> header.
 */
#define __need_size_t
#include <stddef.h>

_BEGIN_C_DECLS

int __cdecl __MINGW_NOTHROW strcasecmp( const char *, const char * );
int __cdecl __MINGW_NOTHROW strncasecmp( const char *, const char *, size_t );

#endif	/* ! RC_INVOKED */
#endif	/* !__STRING_H_SOURCED__ */

#if ! (defined __STRICT_ANSI__ && defined __NO_INLINE__)
/* These are the MSVCRT.DLL equivalents for POSIX.1's strcasecmp() and
 * strncasecmp() functions, for which we provide in-line implementations
 * in <strings.h> respectively; MSVC expects to find these prototypes in
 * <string.h>, but we also need them here, in <strings.h>, to facilitate
 * the in-line function implementations; we declare them here, and allow
 * <string.h> to include them selectively.  Note that <string.h> doesn't
 * need these if __STRICT_ANSI__ is defined, while <strings.h> doesn't
 * if __NO_INLINE__ is defined; thus we declare them, unless BOTH of
 * these conditions for not requiring them are satisfied.
 */
_CRTIMP __cdecl __MINGW_NOTHROW  int _stricmp( const char *, const char * );
_CRTIMP __cdecl __MINGW_NOTHROW  int _strnicmp( const char *, const char *, size_t );
#endif	/* !(__STRICT_ANSI__ && __NO_INLINE__) */

#if defined _STRINGS_H && ! defined RC_INVOKED
#ifndef __NO_INLINE__
/* Provide in-line implementations for strcasecmp(), and strncasecmp(),
 * effectively aliasing them to the respective MSVCRT.DLL (non-standard)
 * equivalents, as prototyped above.
 */
__CRT_ALIAS __JMPSTUB__(( FUNCTION = strcasecmp, REMAPPED = _stricmp ))
  int strcasecmp( const char *__s1, const char *__s2 )
  { return _stricmp( __s1, __s2 ); }

__CRT_ALIAS __JMPSTUB__(( FUNCTION = strncasecmp, REMAPPED = _strnicmp ))
  int strncasecmp( const char *__s1, const char *__s2, size_t __n )
  { return _strnicmp( __s1, __s2, __n ); }

#endif	/* !__NO_INLINE__ */

_END_C_DECLS

#endif	/* _STRINGS_H && ! RC_INVOKED */
#endif	/* !_STRINGS_H: $RCSfile: strings.h,v $: end of file */

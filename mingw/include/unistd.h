/*
 * unistd.h
 *
 * Standard header file declaring MinGW's POSIX compatibility features.
 *
 * $Id: unistd.h,v 7fd51383513c 2017/02/11 12:35:12 keithmarshall $
 *
 * Written by Rob Savoye <rob@cygnus.com>
 * Modified by Earnie Boyd <earnie@users.sourceforge.net>
 *   Danny Smith <dannysmith@users.sourceforge.net>
 *   Ramiro Polla <ramiro@lisha.ufsc.br>
 *   Gregory McGarry  <gregorymcgarry@users.sourceforge.net>
 *   Keith Marshall  <keithmarshall@users.sourceforge.net>
 * Copyright (C) 1997, 1999, 2002-2004, 2007-2009, 2014-2017,
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
#ifndef _UNISTD_H
#define _UNISTD_H  1
#pragma GCC system_header

/* All MinGW headers MUST include _mingw.h before anything else,
 * to ensure proper initialization of feature test macros.
 */
#include <_mingw.h>

/* unistd.h maps (roughly) to Microsoft's <io.h>
 * Other headers included by <unistd.h> may be selectively processed;
 * __UNISTD_H_SOURCED__ enables such selective processing.
 */
#define __UNISTD_H_SOURCED__ 1

/* Use "..." inclusion here, to ensure that we get our own headers, which
 * are designed to interoperate with the __UNISTD_H_SOURCED__ filter.
 */
#include "io.h"
#include "process.h"
#include "getopt.h"

/* These are defined in stdio.h.  POSIX also requires that they
 * are to be consistently defined here; don't guard against prior
 * definitions, as this might conceal inconsistencies.
 */
#define SEEK_SET   0
#define SEEK_CUR   1
#define SEEK_END   2

#if _POSIX_C_SOURCE
/* POSIX process/thread suspension functions; all are supported by a
 * common MinGW API in libmingwex.a, providing for suspension periods
 * ranging from mean values of ~7.5 milliseconds, (see the comments in
 * <time.h>), extending up to a maximum of ~136 years.
 *
 * Note that, whereas POSIX supports early wake-up of any suspended
 * process/thread, in response to a signal, this implementation makes
 * no attempt to emulate this signalling behaviour, (since signals are
 * not well supported by Windows); thus, unless impeded by an invalid
 * argument, this implementation always returns an indication as if
 * the sleeping period ran to completion.
 */
_BEGIN_C_DECLS

__cdecl __MINGW_NOTHROW
int __mingw_sleep( unsigned long, unsigned long );

/* The nanosleep() function provides the most general purpose API for
 * process/thread suspension; it is declared in <time.h>, (where it is
 * accompanied by an in-line implementation), rather than here, and it
 * provides for specification of suspension periods in the range from
 * ~7.5 ms mean, (on WinNT derivatives; ~27.5 ms on Win9x), extending
 * up to ~136 years, (effectively eternity).
 *
 * The usleep() function, and its associated useconds_t type specifier
 * were made obsolete in POSIX.1-2008; declared here, only for backward
 * compatibility, its continued use is not recommended.  (It is limited
 * to specification of suspension periods ranging from ~7.5 ms mean up
 * to a maximum of 999,999 microseconds only).
 */
typedef unsigned long useconds_t __MINGW_ATTRIB_DEPRECATED;
int __cdecl __MINGW_NOTHROW usleep( useconds_t )__MINGW_ATTRIB_DEPRECATED;

#ifndef __NO_INLINE__
__CRT_INLINE __LIBIMPL__(( FUNCTION = usleep ))
int usleep( useconds_t period ){ return __mingw_sleep( 0, 1000 * period ); }
#endif

/* The sleep() function is, perhaps, the most commonly used of all the
 * process/thread suspension APIs; it provides support for specification
 * of suspension periods ranging from 1 second to ~136 years.  (However,
 * POSIX recommends limiting the maximum period to 65535 seconds, to
 * maintain portability to platforms with only 16-bit ints).
 */
unsigned __cdecl __MINGW_NOTHROW sleep( unsigned );

#ifndef __NO_INLINE__
__CRT_INLINE __LIBIMPL__(( FUNCTION = sleep ))
unsigned sleep( unsigned period ){ return __mingw_sleep( period, 0 ); }
#endif


/* POSIX ftruncate() function.
 *
 * Microsoft's _chsize() function is incorrectly described, on MSDN,
 * as a preferred replacement for the POSIX chsize() function.  There
 * never was any such POSIX function; the actual POSIX equivalent is
 * the ftruncate() function.
 */
int __cdecl ftruncate( int, off_t );

#ifndef __NO_INLINE__
__CRT_INLINE __JMPSTUB__(( FUNCTION = ftruncate, DLLENTRY = _chsize ))
int ftruncate( int __fd, off_t __length ){ return _chsize( __fd, __length ); }
#endif

_END_C_DECLS

#endif /* _POSIX_C_SOURCE */

#undef __UNISTD_H_SOURCED__
#endif /* !_UNISTD_H: $RCSfile: unistd.h,v $: end of file */

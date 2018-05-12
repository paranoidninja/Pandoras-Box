/*
 * sys/time.h
 *
 * Time type definitions pertaining to system timer and clock APIs
 *
 *
 * $Id: time.h,v aa598b2db894 2017/09/15 20:35:48 keithmarshall $
 *
 * Written by Danny Smith <dannysmith@users.sourceforge.net>
 * Copyright (C) 2002, 2004, 2006, 2007, 2017, MinGW.org Project
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
#ifndef _SYS_TIME_H
#pragma GCC system_header

#ifndef __WINSOCK_H_SOURCED__
#define _SYS_TIME_H

/* FIXME: Do we need to do this?  There's nothing here which
 * explicitly requires it; are users entitled to assume that
 * including <sys/time.h> will also expose all of <time.h>?
 * (If not <time.h>, we do need <_mingw.h> instead).
 */
#include <time.h>

_BEGIN_C_DECLS

#endif	/* !__WINSOCK_H_SOURCED__ */

#if ! (defined _SYS_TIME_H && defined _WINSOCK_H)
/* The following definitions must be exposed both when <sys/time.h>
 * is included in its own right, and when it is included selectively
 * on behalf of <winsock.h>, but they must not be processed twice.
 */
struct timeval
{ /* Nominally a BSD or POSIX.1 structure, (with tv_sec declared as
   * time_t), but subverted by Microsoft with tv_sec declared as long,
   * to avoid __time32_t vs. __time64_t ambiguity; (tv_sec is ALWAYS
   * a 32-bit entity in Windows' use of this structure).  Addionally,
   * POSIX.1-2001 mandates that tv_usec should be suseconds_t, (which
   * is nominally an alias for long), but we retain long to maintain
   * consistency with Microsoft usage.
   */
  long tv_sec;		/* whole number of seconds in interval */
  long tv_usec; 	/* additional fraction as microseconds */
};

/* FIXME: The following convenience macros, for manipulating data in
 * timeval structures, are derived from BSD; they are neither standard
 * in Windows code, nor specified in POSIX.1, but have been adopted by
 * GNU.  Consider making them dependent on _BSD_SOURCE or _GNU_SOURCE
 * feature test filters, (but note that <winsock.h> must be able to
 * expose timerclear, timerisset, and timercmp, regardless of the
 * order in which <sys/time.h> and <winsock.h> are included).
 */
#define timerclear( tvp )  (tvp)->tv_sec = (tvp)->tv_usec = 0
#define timerisset( tvp )  ((tvp)->tv_sec || (tvp)->tv_usec)

#define timercmp( tvp, uvp, cmp )  (((tvp)->tv_sec != (uvp)->tv_sec)	\
	  ? ((tvp)->tv_sec cmp (uvp)->tv_sec)				\
	  : ((tvp)->tv_usec cmp (uvp)->tv_usec))

#endif	/* ! (_SYS_TIME_H && _WINSOCK_H) */

#ifdef _SYS_TIME_H
struct timezone
{ /* FIXME: Deprecate this...
   * Provided for compatibility with code that assumes that the
   * presence of the gettimeofday() function implies that it may
   * be safely assumed that a definition of struct timezone will
   * also be provided.  This is an obsolete derivative from BSD;
   * DO NOT USE IT!
   */
  int tz_minuteswest;		/* of the Greenwich meridian */
  int tz_dsttime;		/* type of DST correction to apply */
};

/* Declaration of POSIX.1 compatible gettimeofday() function:
 *
 * Implementation per POSIX.1-1996, (declared obsolescent in POSIX.1-2008),
 * as described in the Open Group Base Specification, Issue 7, which is also
 * designated as IEEE Std 1003.1, 2016 Edition; the struct timezone pointer
 * argument of some Unix implementations (declared as a pointer to void in
 * POSIX.1) is ignored, as are all error conditions.
 *
 * FIXME: Deprecate this for _POSIX_C_SOURCE >= 200809L
 */
int __cdecl __MINGW_NOTHROW gettimeofday
(struct timeval *__restrict__, void *__restrict__ /* tzp (unused) */);

_END_C_DECLS

#endif	/* _SYS_TIME_H */
#endif	/* !_SYS_TIME_H: $RCSfile: time.h,v $: end of file */

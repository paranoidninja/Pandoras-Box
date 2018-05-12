/*
 * getopt.h
 *
 * Defines constants and function prototypes required to implement
 * the getopt(), getopt_long() and getopt_long_only() APIs.
 *
 * $Id: getopt.h,v 7fd51383513c 2017/02/11 12:35:12 keithmarshall $
 *
 * Written by Keith Marshall <keithmarshall@users.sourceforge.net>
 * Copyright (C) 2003, 2008, 2009, 2017, MinGW.org Project.
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
#ifndef _GETOPT_H
#pragma GCC system_header

#ifndef __UNISTD_H_SOURCED__
/* POSIX requires the getopt() API to be specified in <unistd.h>; thus,
 * <unistd.h> includes <getopt.h>.  However, we do not want to expose the
 * getopt_long() or getopt_long_only() APIs, when included in this manner.
 * Thus, we process only part of <getopt.h> when __UNISTD_H_SOURCED__ has
 * been defined, and activate the _GETOPT_H repeat inclusion guard macro
 * only when it has not.
 */
#define _GETOPT_H

/* All MinGW headers are required to include <_mingw.h>, before anything
 * else; however, when sourced by <unistd.h>, this has been done already.
 */
#include <_mingw.h>
#endif

_BEGIN_C_DECLS

#if ! (defined _GETOPT_H && defined _UNISTD_H)
/* This section of <getopt.h> is always to be processed, but it doesn't
 * need to be processed twice; if both _GETOPT_H and _UNISTD_H have been
 * defined, when we get to here, then we have reached this point for the
 * second time, so we may safely skip this section.
 */
extern int optind;		/* index of first non-option in argv      */
extern int optopt;		/* single option character, as parsed     */
extern int opterr;		/* flag to enable built-in diagnostics... */
				/* (user may set to zero, to suppress)    */

extern char *optarg;		/* pointer to argument of current option  */

extern int getopt( int, char * const [], const char * );

#ifdef _BSD_SOURCE
/* BSD adds the non-standard "optreset" feature, for reinitialization
 * of getopt() parsing.  We support this feature, for applications which
 * proclaim their BSD heritage, before including this header; however,
 * to maintain portability, developers are advised to avoid it.
 */
# define optreset  __mingw_optreset

extern int optreset;

#endif	/* _BSD_SOURCE */
#endif	/* !(_GETOPT_H && _UNISTD_H) */

#ifdef _GETOPT_H
/* This is the section of <getopt.h> which declares the getopt_long()
 * and getopt_long_only() APIs; it is processed only when <getopt.h>
 * is included directly.
 */
struct option		/* specification for a long form option...	*/
{ const char *name;		/* option name, without leading hyphens */
  int         has_arg;		/* does it take an argument?		*/
  int        *flag;		/* where to save its status, or NULL	*/
  int         val;		/* its associated status value		*/
};

enum    		/* permitted values for its "has_arg" field...	*/
{ no_argument = 0,      	/* option never takes an argument	*/
  required_argument,		/* option always requires an argument	*/
  optional_argument		/* option may take an argument		*/
};

extern int getopt_long( int, char * const [], const char *, const struct option *, int * );
extern int getopt_long_only( int, char * const [], const char *, const struct option *, int * );

#endif	/* _GETOPT_H */

_END_C_DECLS

#endif	/* !_GETOPT_H: $RCSfile: getopt.h,v $: end of file */

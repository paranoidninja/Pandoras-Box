#ifndef _GLOB_H
/*
 * glob.h
 *
 * Header file supporting a MinGW implementation of an (approximately)
 * POSIX conforming glob() and globfree() API.
 *
 * $Id: glob.h,v 441f10158594 2017/02/12 10:12:06 keithmarshall $
 *
 * Written by Keith Marshall <keithmarshall@users.sourceforge.net>
 * Copyright (C) 2011, 2012, 2014, 2016, 2017, MinGW.org Project.
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
#define _GLOB_H  1
#pragma GCC system_header

/* All MinGW.org system headers are required to include <_mingw.h>.
 */
#include <_mingw.h>

#ifndef RC_INVOKED
/* POSIX requires glob.h to define the size_t type; we need to
 * get this from GCC's <stddef.h>, just as <sys/types.h> does.
 */
#define __need_size_t
#include <stddef.h>

typedef
struct glob_t
{ /* The structure, in which glob() returns the list of file system
   * entities which it has matched.
   */
  void     * gl_magic;	/* reserved field; pointer to a glob signature	*/
  size_t     gl_pathc;	/* counter for paths matched			*/
  char    ** gl_pathv;	/* list of matching path names			*/
  size_t     gl_offs;	/* number of initial unused slots in gl_pathv	*/
} glob_t;

/* A macro to facilitate definition of the flags which are used to
 * control the operation of glob().
 */
#define __GLOB_FLAG__(NAME)  (1 << __GLOB_##NAME##_OFFSET)
enum {
  /* Identify the zero-based offset values which are used to specify
   * the individual bit positions for each __GLOB_FLAG; the initial
   * list specifies the standard set of flags required by POSIX.
   */
  __GLOB_APPEND_OFFSET = 0,
  __GLOB_DOOFFS_OFFSET,
  __GLOB_ERR_OFFSET,
  __GLOB_MARK_OFFSET,
  __GLOB_NOCHECK_OFFSET,
  __GLOB_NOESCAPE_OFFSET,
  __GLOB_NOSORT_OFFSET,
  /*
   * GNU's implementation of glob() supports a supplementary set of
   * options, none of which are required by POSIX.  We include these
   * for reference, and to reserve the flag identities for a possible
   * future implementation; of these extensions, the current MinGW
   * implementation supports only GLOB_BRACE.
   */
  __GLOB_TILDE_OFFSET,
  __GLOB_TILDE_CHECK_OFFSET,
  __GLOB_PERIOD_OFFSET,
  __GLOB_BRACE_OFFSET,
  __GLOB_ONLYDIR_OFFSET,
  __GLOB_ALTDIRFUNC_OFFSET,
  __GLOB_NOMAGIC_OFFSET,
  /*
   * This MinGW implementation DOES add support for the following
   * custom options, which offer improved handling of MS-Windows
   * specific peculiarities:--
   *
   *   GLOB_CASEMATCH	    makes glob() respect case sensitivity
   *			    in path name matches; this is similar
   *			    to default behaviour on POSIX systems,
   *			    but to better support the MS-Windows
   *			    file system, the MinGW implementation
   *			    of glob() performs a CASE INSENSITIVE
   *			    character match by default.
   */
  __GLOB_CASEMATCH_OFFSET,
  /*
   * The following is a convenience, to mark the end of the enumeration;
   * it is NEVER used to locate any user visible __GLOB_FLAG__, but it
   * MUST remain as the final entry in the enumerated list.
   */
  __GLOB_FLAG_OFFSET_HIGH_WATER_MARK
};

/* Definitions of the mandatory flags, as specified by POSIX.
 */
#define GLOB_APPEND	  __GLOB_FLAG__(APPEND)
#define GLOB_DOOFFS	  __GLOB_FLAG__(DOOFFS)
#define GLOB_ERR	  __GLOB_FLAG__(ERR)
#define GLOB_MARK	  __GLOB_FLAG__(MARK)
#define GLOB_NOCHECK	  __GLOB_FLAG__(NOCHECK)
#define GLOB_NOESCAPE	  __GLOB_FLAG__(NOESCAPE)
#define GLOB_NOSORT	  __GLOB_FLAG__(NOSORT)

/* Flag definitions for those GNU extensions, as listed above, for which
 * we provide support; (i.e. GLOB_BRACE only, at present).
 */
#define GLOB_BRACE	  __GLOB_FLAG__(BRACE)

/* Additional flags definitions, for MinGW specific extensions.
 */
#define GLOB_CASEMATCH	  __GLOB_FLAG__(CASEMATCH)

_BEGIN_C_DECLS
/*
 * Function prototypes.  Formally POSIX mandates:
 *
 *  int glob( const char *, int, int (*)( const char *, int ), glob_t * );
 *  void globfree( glob_t * );
 *
 * However, our actual function implementations are provided via this
 * pair of reserved function names...
 */
int __mingw_glob (const char *, int, int (*)(const char *, int), glob_t *);
void __mingw_globfree (glob_t *);

/* ...to which the standard names are then mapped as aliases,
 * via __CRT_ALIAS inline function expansion.
 */
__CRT_ALIAS __JMPSTUB__(( FUNCTION = glob ))
# define __ERRFUNC_P  (*__errfunc) (const char *, int)
int glob (const char *__pattern, int __flags, int __ERRFUNC_P, glob_t *__data)
{ return __mingw_glob (__pattern, __flags, __errfunc, __data); }
# undef __ERRFUNC_P

__CRT_ALIAS __JMPSTUB__(( FUNCTION = globfree ))
void globfree (glob_t *__data){ return __mingw_globfree (__data); }

_END_C_DECLS

/* Manifest definitions for the possible status values
 * which glob() may return.
 */
#define GLOB_SUCCESS	(0)
#define GLOB_ABORTED	(1)
#define GLOB_NOMATCH	(2)
#define GLOB_NOSPACE	(3)

#endif /* ! RC_INVOKED */
#endif /* !_GLOB_H: $RCSfile: glob.h,v $: end of file */

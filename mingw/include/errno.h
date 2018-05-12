/*
 * errno.h
 *
 * Definition of error codes, and error code retrieval mechanism.
 *
 * $Id: errno.h,v 99ef1a520f95 2016/11/14 17:57:05 keithmarshall $
 *
 * Written by Colin Peters <colin@bird.fu.is.saga-u.ac.jp>
 * Copyright (C) 1997-1999, 2001, 2003-2005, 2007, 2016, MinGW.org Project.
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
#ifndef _ERRNO_H
#define _ERRNO_H

/* All MinGW headers are expected to include <_mingw.h>; however...
 */
#ifndef __ASSEMBLER__
/* ...the overhead of doing so is unwarranted, when <errno.h> has been
 * included directly in preprocessed assembly language code.
 */
#include <_mingw.h>
#endif

/* Error code numbers.
 *
 * TODO: Can't be sure of some of these assignments, I guessed from the
 * names given by strerror and the defines in the Cygnus errno.h. A lot
 * of the names from the Cygnus errno.h are not represented, and a few
 * of the descriptions returned by strerror do not obviously match
 * their error naming.
 */
#define EPERM		 1	/* Operation not permitted */
#define ENOFILE 	 2	/* No such file or directory */
#define ENOENT		 2
#define ESRCH		 3	/* No such process */
#define EINTR		 4	/* Interrupted function call */
#define EIO		 5	/* Input/output error */
#define ENXIO		 6	/* No such device or address */
#define E2BIG		 7	/* Arg list too long */
#define ENOEXEC 	 8	/* Exec format error */
#define EBADF		 9	/* Bad file descriptor */
#define ECHILD		10	/* No child processes */
#define EAGAIN		11	/* Resource temporarily unavailable */
#define ENOMEM		12	/* Not enough space */
#define EACCES		13	/* Permission denied */
#define EFAULT		14	/* Bad address */
/* 15 - Unknown Error */
#define EBUSY		16	/* strerror reports "Resource device" */
#define EEXIST		17	/* File exists */
#define EXDEV		18	/* Improper link (cross-device link?) */
#define ENODEV		19	/* No such device */
#define ENOTDIR 	20	/* Not a directory */
#define EISDIR		21	/* Is a directory */
#define EINVAL		22	/* Invalid argument */
#define ENFILE		23	/* Too many open files in system */
#define EMFILE		24	/* Too many open files */
#define ENOTTY		25	/* Inappropriate I/O control operation */
/* 26 - Unknown Error */
#define EFBIG		27	/* File too large */
#define ENOSPC		28	/* No space left on device */
#define ESPIPE		29	/* Invalid seek (seek on a pipe?) */
#define EROFS		30	/* Read-only file system */
#define EMLINK		31	/* Too many links */
#define EPIPE		32	/* Broken pipe */
#define EDOM		33	/* Domain error (math functions) */
#define ERANGE		34	/* Result too large (possibly too small) */
/* 35 - Unknown Error */
#define EDEADLOCK	36	/* Resource deadlock avoided (non-Cyg) */
#define EDEADLK 	36
/* 37 - Unknown Error */
#define ENAMETOOLONG	38	/* Filename too long (91 in Cyg?) */
#define ENOLCK		39	/* No locks available (46 in Cyg?) */
#define ENOSYS		40	/* Function not implemented (88 in Cyg?) */
#define ENOTEMPTY	41	/* Directory not empty (90 in Cyg?) */
#define EILSEQ		42	/* Illegal byte sequence */

/* C language function prototype declarations are unnecessary, when
 * compiling resource files, and they actually represent syntactically
 * invalid statements, in preprocessed assembly language code.
 */
#if ! defined RC_INVOKED && ! defined __ASSEMBLER__

_BEGIN_C_DECLS

/* Definitions of errno. For _doserrno, sys_nerr and * sys_errlist, see
 * stdlib.h.
 */
#ifdef _UWIN
#undef errno
extern int errno;
#else
_CRTIMP int* __cdecl __MINGW_NOTHROW _errno(void);
#define	errno		(*_errno())
#endif

_END_C_DECLS

#endif	/* ! RC_INVOKED && !__ASSEMBLY__ */

#if defined __PTW32_H && ! defined _PTW32_ERRNO_H
/* As a courtesy to users of pthreads-win32, ensure that the appropriate
 * additional error codes, as defined by that package, are automatically
 * defined when <errno.h> is included AFTER any pthreads-win32 header; a
 * complementary hook, in <_ptw32.h>, ensures that such additional error
 * codes are defined, if <errno.h> is included BEFORE any pthreads-win32
 * header is subsequently included.
 *
 * NOTE: this assumes pthreads-win32-2.10 or later, with corresponding
 * MinGW.org patches applied; it will favour "ptw32_errno.h" installed
 * in the mingwrt system include directory.
 */
#include "ptw32_errno.h"

#endif	/* __PTW32_H */
#endif	/* !_ERRNO_H: $RCSfile: errno.h,v $: end of file */

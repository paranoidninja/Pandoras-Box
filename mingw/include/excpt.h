/*
 * excpt.h
 *
 * Experimental support for operating system level structured handling
 * of exceptions.
 *
 * $Id: excpt.h,v c4f543eaadd6 2016/11/27 12:40:01 keithmarshall $
 *
 * Written by Colin Peters <colin@bird.fu.is.saga-u.ac.jp>
 * Revised by Keith Marshall <keithmarshall@users.sourceforge.net>
 * Copyright (C) 1997, 1999, 2001-2002, 2004, 2007, 2012, 2016,
 *  MinGW.org Project.
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
#ifndef _EXCPT_H
#pragma GCC system_header
#define _EXCPT_H

/* FIXME: this utility macro, to allocate stack space for any aggregate
 * data type, with an explicit type cast of a pointer to that data type,
 * deserves a place in a more universally accessible header file.  The
 * type cast is not strictly necessary for C, (but is permitted); it is
 * essential for C++.
 */
#define __typecast_alloca(type) (type *)(__builtin_alloca( sizeof(type) ))

/* All MinGW CRT headers are required to include <_mingw.h>
 */
#include <_mingw.h>

/* Exception handler functions require definitions of _CONTEXT, and
 * _EXCEPTION_RECORD structures, which are provided in <windef.h>
 */
#include <windef.h>

#ifndef _EXCPT_W32API_H
/* FIXME: These constants, structs, and typedefs should be defined
 * in the Win32 API headers; (we need to establish where -- perhaps
 * this header itself should be redesignated as a W32API header).
 */
#define EH_NONCONTINUABLE	0x01
#define EH_UNWINDING		0x02
#define EH_EXIT_UNWIND		0x04
#define EH_STACK_INVALID	0x08
#define EH_NESTED_CALL		0x10

#ifndef RC_INVOKED

typedef enum
{ ExceptionContinueExecution,
  ExceptionContinueSearch,
  ExceptionNestedException,
  ExceptionCollidedUnwind
} EXCEPTION_DISPOSITION;

#endif	/* ! RC_INVOKED */
#endif	/* !_EXCPT_W2API_H */

#ifndef RC_INVOKED

_BEGIN_C_DECLS

/* The type of function that is expected as an exception handler,
 * to be installed by the __try1(__handler) primitive.
 */
typedef EXCEPTION_DISPOSITION (*PEXCEPTION_HANDLER)
(struct _EXCEPTION_RECORD *, void *, struct _CONTEXT *, void *);

typedef struct _EXCEPTION_REGISTRATION
{ /* Maps the structure of the exception handler registration
   * block, as installed by the __try1(__handler) primitive.
   */
  struct _EXCEPTION_REGISTRATION	*prev;
  PEXCEPTION_HANDLER			 handler;
} EXCEPTION_REGISTRATION, *PEXCEPTION_REGISTRATION;

/* Aliases which may be preferred, when referring to the
 * EXCEPTION_REGISTRATION structure.
 */
typedef EXCEPTION_REGISTRATION EXCEPTION_REGISTRATION_RECORD;
typedef PEXCEPTION_REGISTRATION PEXCEPTION_REGISTRATION_RECORD;

/* Deployment of exception handlers is facilitated by the pair
 * of macros, __try1(_handler) and __except1.
 *
 * CAUTION: __try1(__handler) and __except1 must be deployed as
 * a complementary pair, within the scope of the stack frame of
 * a single function, with __try1(__handler) preceding the use
 * of __except1.  Failure to invoke __except1 before release of
 * any stack frame, in which __try1(__handler) has been invoked,
 * will invalidate the EXCEPTION_REGISTRATION_RECORD, which has
 * been installed by __try1(_handler), at the head of the active
 * exception handler chain; this will cause undefined behaviour,
 * which is sure to go badly.
 *
 * To accommodate implementation differences between _WIN32 and
 * _WIN64 hosts, the actual implementations of __try1(__handler)
 * and __except1 are expressed in terms of a pair of lower level
 * internal macros, namely:
 *
 * Macro: __try1_setup(__handler,__wsize,__ts)
 *
 * Helper for implementation of macro __try1(__handler); allocate
 * a block of memory, within the stack frame of the calling function,
 * which is then initialized as an EXCEPTION_REGISTRATION_RECORD, and
 * linked to the head of the installed exception handler chain.
 *
 * Inputs:
 *  __handler	pointer to an EXCEPTION_HANDLER function.
 *  __wsize	the Intel host word size pointer description.
 *  __ts	thread information segment register name.
 */
#define __try1_setup(__handler,__wsize,__ts)				\
{ EXCEPTION_REGISTRATION *__hook;					\
  __hook = __typecast_alloca( EXCEPTION_REGISTRATION ); 		\
  __hook->handler = __handler;						\
  __asm__ __volatile__							\
  ( "mov{%z0}\t{%%|%0, " __wsize " }" __ts ":{|[}0x0{, %0|]}\n\t"	\
    "mov{%z1}\t{%1, %%|" __wsize " }" __ts ":{|[}0x0{|], %1}"		\
    :"=r"(__hook->prev):"r"(__hook):"memory"				\
  );									\
}

/* Macro: __except1_teardown(__wsize,__ts)
 *
 * Helper which provides the implementation for the __except1
 * complement to __try1(__handler) macro; it unlinks the first
 * EXCEPTION_REGISTRATION_RECORD from the head of the exception
 * handler chain.  Arguments are as described for those of the
 * same name, in the __try1_setup macro argument list.
 */
#define __except1_teardown(__wsize,__ts) 				\
{ register EXCEPTION_REGISTRATION *__hook;				\
  __asm__ __volatile__							\
  ( "mov{%z0}\t{%%|%0, " __wsize " }" __ts ":{|[}0x0{, %0|]}\n\t"	\
    "mov{%z0}\t{(}%0{)}, {|" __wsize " [}%0{|]}\n\t"			\
    "mov{%z0}\t{%0, %%|" __wsize " }" __ts ":{|[}0x0{|], %0}"		\
    :"+r"(__hook)::"memory"						\
  );									\
}

/* Specialization of the above primitives, creating __try1(__handler),
 * and its complementary __except1 implementation, with the appropriate
 * assignments of word size and TIB segment register, for each of...
 */
#ifdef _WIN64
/* ...64-bit windows, for which the word size for representation of
 * pointers, in Intel-syntax code, is "QWORD PTR", and the gs segment
 * is used for access to the thread information block...
 */
# define __try1(__handler) __try1_setup(__handler,"QWORD PTR","gs")
# define __except1 __except1_teardown("QWORD PTR","gs")

#else	/* _WIN32 */
/* ...while in 32-bit windows, the corresponding pointer word size
 * is "DWORD PTR", and the the thread information block is located
 * in the fs segment.
 */
# define __try1(__handler) __try1_setup(__handler,"DWORD PTR","fs")
# define __except1 __except1_teardown("DWORD PTR","fs")
#endif

_END_C_DECLS

#endif	/* ! RC_INVOKED */
#endif	/* !_EXCPT_H: $RCSfile: excpt.h,v $: end of file */

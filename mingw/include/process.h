/*
 * process.h
 *
 * Declarations of functions for spawning child processes.
 *
 * $Id: process.h,v 0e4f78dbc1ba 2016/06/17 14:16:01 keithmarshall $
 *
 * Written by Colin Peters <colin@bird.fu.is.saga-u.ac.jp>
 * Copyright (C) 1997-2001, 2003-2004, 2007-2008, 2016, MinGW.org Project.
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
#ifndef _PROCESS_H
#pragma GCC system_header

/* Defer defining the normal _PROCESS_H multiple inclusion guard macro,
 * to facilitate selective inclusion by <wchar.h>, (in which case we do
 * not wish to define it).
 */
#ifndef __WCHAR_H_SOURCED__
#define _PROCESS_H

/* All MinGW headers must include <_mingw.h>; do so here, assuming
 * that <wchar.h> will have already taken care of it, for the case
 * of selective inclusion.
 */
#include <_mingw.h>

/* This gives us more than we really need, but it gets us _pid_t
 * (and its pid_t equivalent), which we do need.
 */
#include <sys/types.h>

/* Constants for cwait actions; obsolete for Win32.
 */
#define _WAIT_CHILD		0
#define _WAIT_GRANDCHILD	1

#ifndef _NO_OLDNAMES
#define WAIT_CHILD		_WAIT_CHILD
#define WAIT_GRANDCHILD 	_WAIT_GRANDCHILD
#endif	/* !_NO_OLDNAMES */
#endif	/* !__WCHAR_H_SOURCED__ */

/* Mode constants for spawn() functions.
 */
#define _P_WAIT 		0
#define _P_NOWAIT		1
#define _P_OVERLAY		2
#define _OLD_P_OVERLAY		_P_OVERLAY
#define _P_NOWAITO		3
#define _P_DETACH		4

#ifndef _NO_OLDNAMES
#define P_WAIT			_P_WAIT
#define P_NOWAIT		_P_NOWAIT
#define P_OVERLAY		_P_OVERLAY
#define OLD_P_OVERLAY		_OLD_P_OVERLAY
#define P_NOWAITO		_P_NOWAITO
#define P_DETACH		_P_DETACH
#endif	/* !_NO_OLDNAMES */

#ifndef RC_INVOKED

/* All Microsoft implementations of the exec() and spawn() functions
 * are declared with intptr_t as their return type; get its definition
 * by selective inclusion from "stdint.h"; (note: use #include "..."
 * here, to avoid side effects from any alternative <stdint.h>, which
 * is not in the same directory as this <process.h>).
 */
#define __need_intptr_t
#include "stdint.h"

_BEGIN_C_DECLS

#ifdef _PROCESS_H
_CRTIMP __cdecl __MINGW_NOTHROW  void _cexit (void);
_CRTIMP __cdecl __MINGW_NOTHROW  void _c_exit (void);

_CRTIMP __cdecl __MINGW_NOTHROW  int _cwait (int *, _pid_t, int);

_CRTIMP __cdecl __MINGW_NOTHROW  _pid_t _getpid (void);

_CRTIMP __cdecl __MINGW_NOTHROW
intptr_t _execl (const char *, const char *, ...);

_CRTIMP __cdecl __MINGW_NOTHROW
intptr_t _execle (const char *, const char *, ...);

_CRTIMP __cdecl __MINGW_NOTHROW
intptr_t _execlp (const char *, const char *, ...);

_CRTIMP __cdecl __MINGW_NOTHROW
intptr_t _execlpe (const char *, const char *, ...);

_CRTIMP __cdecl __MINGW_NOTHROW
intptr_t _execv (const char *, const char * const *);

_CRTIMP __cdecl __MINGW_NOTHROW
intptr_t _execve (const char *, const char * const *, const char * const *);

_CRTIMP __cdecl __MINGW_NOTHROW
intptr_t _execvp (const char *, const char * const *);

_CRTIMP __cdecl __MINGW_NOTHROW
intptr_t _execvpe (const char *, const char * const *, const char * const *);

_CRTIMP __cdecl __MINGW_NOTHROW
intptr_t _spawnl (int, const char *, const char *, ...);

_CRTIMP __cdecl __MINGW_NOTHROW
intptr_t _spawnle (int, const char *, const char *, ...);

_CRTIMP __cdecl __MINGW_NOTHROW
intptr_t _spawnlp (int, const char *, const char *, ...);

_CRTIMP __cdecl __MINGW_NOTHROW
intptr_t _spawnlpe (int, const char *, const char *, ...);

_CRTIMP __cdecl __MINGW_NOTHROW
intptr_t _spawnv (int, const char *, const char * const *);

_CRTIMP __cdecl __MINGW_NOTHROW
intptr_t _spawnve (int, const char *, const char * const *, const char * const *);

_CRTIMP __cdecl __MINGW_NOTHROW
intptr_t _spawnvp (int, const char *, const char * const *);

_CRTIMP __cdecl __MINGW_NOTHROW
intptr_t _spawnvpe (int, const char *, const char * const *, const char * const *);

/* Thread initiation and termination functions.
 *
 * NOTE: Apparently _endthread() calls CloseHandle() on the handle of the
 * thread, creating a potential for race conditions, if you are not careful.
 * Basically, you MUST ensure that NOTHING attempts to do ANYTHING with the
 * thread handle after the thread calls _endthread(), or returns from the
 * thread function.
 *
 * NOTE: No old names for these functions.  Use the underscore.
 */
_CRTIMP __cdecl __MINGW_NOTHROW
unsigned long _beginthread (void (*)(void *), unsigned, void *);

_CRTIMP __cdecl __MINGW_NOTHROW  void _endthread (void);

#ifdef __MSVCRT__
_CRTIMP __cdecl __MINGW_NOTHROW  unsigned long _beginthreadex
(void *, unsigned, unsigned (__stdcall *) (void *), void *, unsigned, unsigned *);

_CRTIMP __cdecl __MINGW_NOTHROW  void _endthreadex (unsigned);
#endif

#ifndef _NO_OLDNAMES
/* Functions named without the leading underscore, for portability.
 * These functions live in liboldnames.a.
 */
_CRTIMP __cdecl __MINGW_NOTHROW  int cwait (int *, pid_t, int);
_CRTIMP __cdecl __MINGW_NOTHROW  pid_t getpid (void);

_CRTIMP __cdecl __MINGW_NOTHROW
intptr_t execl (const char *, const char *, ...);

_CRTIMP __cdecl __MINGW_NOTHROW
intptr_t execle (const char *, const char *, ...);

_CRTIMP __cdecl __MINGW_NOTHROW
intptr_t execlp (const char *, const char *, ...);

_CRTIMP __cdecl __MINGW_NOTHROW
intptr_t execlpe (const char *, const char *,...);

_CRTIMP __cdecl __MINGW_NOTHROW
intptr_t execv (const char *, const char * const *);

_CRTIMP __cdecl __MINGW_NOTHROW
intptr_t execve (const char *, const char * const *, const char * const *);

_CRTIMP __cdecl __MINGW_NOTHROW
intptr_t execvp (const char *, const char * const *);

_CRTIMP __cdecl __MINGW_NOTHROW
intptr_t execvpe (const char *, const char * const *, const char * const *);

_CRTIMP __cdecl __MINGW_NOTHROW
intptr_t spawnl (int, const char *, const char *, ...);

_CRTIMP __cdecl __MINGW_NOTHROW
intptr_t spawnle (int, const char *, const char *, ...);

_CRTIMP __cdecl __MINGW_NOTHROW
intptr_t spawnlp (int, const char *, const char *, ...);

_CRTIMP __cdecl __MINGW_NOTHROW
intptr_t spawnlpe (int, const char *, const char *, ...);

_CRTIMP __cdecl __MINGW_NOTHROW
intptr_t spawnv (int, const char *, const char * const *);

_CRTIMP __cdecl __MINGW_NOTHROW
intptr_t spawnve (int, const char *, const char * const *, const char * const *);

_CRTIMP __cdecl __MINGW_NOTHROW
intptr_t spawnvp (int, const char *, const char * const *);

_CRTIMP __cdecl __MINGW_NOTHROW
intptr_t spawnvpe (int, const char *, const char * const *, const char * const *);

#endif	/* !_NO_OLDNAMES */
#endif	/* _PROCESS_H */

#if ! (defined _PROCESS_H && defined _WCHAR_H)
/* Wide character variations of the exec() and spawn() functions are
 * declared both when <process.h> is included directly, and when it is
 * selectively included by <wchar.h>; however, if both _PROCESS_H and
 * _WCHAR_H are defined, by the time we get to here, then this must be
 * the direct inclusion case, and these have already been declared as
 * a result of selective inclusion; there is no need to declare them
 * a second time.
 */
_CRTIMP __cdecl __MINGW_NOTHROW
intptr_t _wexecl (const wchar_t *, const wchar_t *, ...);

_CRTIMP __cdecl __MINGW_NOTHROW
intptr_t _wexecle (const wchar_t *, const wchar_t *, ...);

_CRTIMP __cdecl __MINGW_NOTHROW
intptr_t _wexeclp (const wchar_t *, const wchar_t *, ...);

_CRTIMP __cdecl __MINGW_NOTHROW
intptr_t _wexeclpe (const wchar_t *, const wchar_t *, ...);

_CRTIMP __cdecl __MINGW_NOTHROW
intptr_t _wexecv (const wchar_t *, const wchar_t * const *);

_CRTIMP __cdecl __MINGW_NOTHROW  intptr_t _wexecve
(const wchar_t *, const wchar_t * const *, const wchar_t * const *);

_CRTIMP __cdecl __MINGW_NOTHROW
intptr_t _wexecvp (const wchar_t *, const wchar_t * const *);

_CRTIMP __cdecl __MINGW_NOTHROW  intptr_t _wexecvpe
(const wchar_t *, const wchar_t * const *, const wchar_t * const *);

_CRTIMP __cdecl __MINGW_NOTHROW
intptr_t _wspawnl (int, const wchar_t *, const wchar_t *, ...);

_CRTIMP __cdecl __MINGW_NOTHROW
intptr_t _wspawnle (int, const wchar_t *, const wchar_t *, ...);

_CRTIMP __cdecl __MINGW_NOTHROW
intptr_t _wspawnlp (int, const wchar_t *, const wchar_t *, ...);

_CRTIMP __cdecl __MINGW_NOTHROW
intptr_t _wspawnlpe (int, const wchar_t *, const wchar_t *, ...);

_CRTIMP __cdecl __MINGW_NOTHROW
intptr_t _wspawnv (int, const wchar_t *, const wchar_t * const *);

_CRTIMP __cdecl __MINGW_NOTHROW  intptr_t _wspawnve
(int, const wchar_t *, const wchar_t * const *, const wchar_t * const *);

_CRTIMP __cdecl __MINGW_NOTHROW
intptr_t _wspawnvp (int, const wchar_t *, const wchar_t * const *);

_CRTIMP __cdecl __MINGW_NOTHROW intptr_t _wspawnvpe
(int, const wchar_t *, const wchar_t * const *, const wchar_t * const *);

#endif	/* ! (_PROCESS_H && _WCHAR_H) */

_END_C_DECLS

#endif	/* ! RC_INVOKED */
#endif	/* !_PROCESS_H: $RCSfile: process.h,v $: end of file */

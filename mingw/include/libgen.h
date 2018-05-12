#ifndef _LIBGEN_H_
/*
 * libgen.h
 *
 * Functions for splitting pathnames into dirname and basename components.
 *
 * $Id: libgen.h,v 916f43b3e665 2014/11/08 23:54:51 keithmarshall $
 *
 * Written by Keith Marshall <keithmarshall@users.sourceforge.net>
 * Copyright (C) 2006, 2007, 2014, MinGW.org Project
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
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OF OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 */
#define _LIBGEN_H_

/* All the headers include this file. */
#include <_mingw.h>

_BEGIN_C_DECLS

extern __cdecl __MINGW_NOTHROW char *basename (char *);
extern __cdecl __MINGW_NOTHROW char *dirname  (char *);

extern __cdecl __MINGW_NOTHROW char *__mingw_basename (char *);
extern __cdecl __MINGW_NOTHROW char *__mingw_dirname  (char *);

__CRT_ALIAS __JMPSTUB__(( FUNCTION = basename ))
__cdecl char *basename (char *__path){ return __mingw_basename (__path); }

__CRT_ALIAS __JMPSTUB__(( FUNCTION = dirname ))
__cdecl char *dirname (char *__path){ return __mingw_dirname (__path); }

_END_C_DECLS

#endif	/* _LIBGEN_H_: end of file */

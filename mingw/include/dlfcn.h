/*
 * dlfcn.h
 *
 * Public interface declarations for (approximately) POSIX conforming
 * dlopen(), dlsym(), dlclose(), and dlerror() API functions.
 *
 * $Id: dlfcn.h,v 82d2db93e4de 2014/11/11 18:13:14 keithmarshall $
 *
 * Written by Keith Marshall <keithmarshall@users.sourceforge.net>
 * Copyright (C) 2014, MinGW.org Project
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
#ifndef _DLFCN_H
#define _DLFCN_H  1
#pragma GCC system_header

#include <_mingw.h>

/* POSIX requires the following four definitions.  Our implementation
 * (currently) does not support the behaviour associated with RTLD_LAZY;
 * if specified, it is simply ignored; RTLD_NOW behaviour will prevail.
 */
#define RTLD_NOW	0
#define RTLD_LAZY	1
#define RTLD_GLOBAL	2
#define RTLD_LOCAL	4

/* POSIX does not yet require the following pair, but reserves them for
 * future capabilities; they will be used in contexts where a DLL module
 * handle is expected, so we reserve values of suitable type, which are
 * unlikely to ever occur as real module handles in practice.
 */
#define RTLD_DEFAULT	(void *)(-1)
#define RTLD_NEXT	(void *)(-3)

/* The four dlfcn API functions, dlopen(), dlsym(), dlerror(), and dlclose(),
 * are each defined privately, and made publicly accessible via corresponding
 * function pointers, within the following publicly visible structure.
 */
_EXTERN_C struct __dlfcn__
{ void *(*dlopen)( const char *, int );
  void *(*dlsym)( void *__restrict__, const char *__restrict__ );
  char *(*dlerror)( void );
  int (*dlclose)( void * );
} __mingw_dlfcn;

/* Declare the public API for each of these functions...
 */
_BEGIN_C_DECLS

/* In any event, we always declare prototypes for all four functions.
 */
void * dlopen( const char *, int );
void * dlsym( void *__restrict__, const char *__restrict__ );
int    dlclose( void * );
char * dlerror( void );

__CRT_ALIAS __LIBIMPL__(( FUNCTION = dlopen ))
void *dlopen( const char *__name, int __mode )
{ return __mingw_dlfcn.dlopen( __name, __mode ); }

__CRT_ALIAS __LIBIMPL__(( FUNCTION = dlsym ))
void *dlsym( void *__restrict__ __module, const char *__restrict__ __name )
{ return __mingw_dlfcn.dlsym( __module, __name ); }

__CRT_ALIAS __LIBIMPL__(( FUNCTION = dlclose ))
int dlclose( void *__module ){ return __mingw_dlfcn.dlclose( __module ); }

__CRT_ALIAS __LIBIMPL__(( FUNCTION = dlerror ))
char *dlerror( void ){ return __mingw_dlfcn.dlerror(); }

_END_C_DECLS

#endif /* _DLFCN_H: $RCSfile: dlfcn.h,v $: end of file */

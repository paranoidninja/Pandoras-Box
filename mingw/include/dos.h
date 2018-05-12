/*
 * dos.h
 *
 * Functions and structures inherited from MS-DOS.
 *
 * $Id: dos.h,v 466a876b8525 2016/09/13 20:14:13 keithmarshall $
 *
 * Written by Jan-Jaap van der Heijden
 * Copyright (C) 1997-1999, 2001-2004, 2007, 2016, MinGW.org Project.
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
#ifndef	_DOS_H
#pragma GCC system_header

/* This header supports selective inclusion by <direct.h>, for delegated
 * access to the content of <io.h>, and for declaration of the prototype
 * and associated data structure for the _getdiskfree() function; since
 * including <dos.h> in this manner does not make all of its content
 * visible, we defer definition of its multiple inclusion guard...
 */
#ifndef __DIRECT_H_SOURCED__
 /* ...until we have determined that this inclusion is NOT a selective
  * request from <direct.h>; in spite of it being obsolete, it appears
  * that the user may have included <dos.h> directly.
  */
#define	_DOS_H
/* If the user does include <dos.h> directly, we should raise an alert
 * to advise that <direct.h> is the preferred alternative; however, the
 * warning will interfere with the testsuite result...
 */
#ifndef __IN_MINGWRT_TESTSUITE__
/* ...so we suppress it in this specific instance.
 */
#warning "<dos.h> is obsolete; consider using <direct.h> instead."
#endif
#endif	/* !__DIRECT_H_SOURCED__ */

/* All MinGW headers are required to include <_mingw.h>; additionally,
 * for DOS file attributes, we must include <io.h>.  By unconditionally
 * including <io.h> here, we may delegate the inclusion of <_mingw.h> to
 * it, while also allowing <direct.h> to delegate responsibility for the
 * inclusion of both <_mingw.h> and <io.h> to us.
 */
#include "io.h"

#ifndef RC_INVOKED

_BEGIN_C_DECLS

/* The following declarations are to be visible ONLY when <dos.h>
 * is included in its own right; they represent entities which are
 * present in CRTDLL.DLL, but not in MSVCRT.DLL
 */
#if defined _DOS_H && ! defined __MSVCRT__
#ifndef __DECLSPEC_SUPPORTED

# define _basemajor    (*_imp___basemajor_dll)
# define _baseminor    (*_imp___baseminor_dll)
# define _baseversion  (*_imp___baseversion_dll)
# define _osmajor      (*_imp___osmajor_dll)
# define _osminor      (*_imp___osminor_dll)
# define _osmode       (*_imp___osmode_dll)

extern unsigned int *_imp___basemajor_dll;
extern unsigned int *_imp___baseminor_dll;
extern unsigned int *_imp___baseversion_dll;
extern unsigned int *_imp___osmajor_dll;
extern unsigned int *_imp___osminor_dll;
extern unsigned int *_imp___osmode_dll;

#else /* __DECLSPEC_SUPPORTED */

# define _basemajor    _basemajor_dll
# define _baseminor    _baseminor_dll
# define _baseversion  _baseversion_dll
# define _osmajor      _osmajor_dll
# define _osminor      _osminor_dll
# define _osmode       _osmode_dll

__MINGW_IMPORT unsigned int _basemajor_dll;
__MINGW_IMPORT unsigned int _baseminor_dll;
__MINGW_IMPORT unsigned int _baseversion_dll;
__MINGW_IMPORT unsigned int _osmajor_dll;
__MINGW_IMPORT unsigned int _osminor_dll;
__MINGW_IMPORT unsigned int _osmode_dll;

#endif	/* __DECLSPEC_SUPPORTED */
#endif	/* _DOS_H && !__MSVCRT__ */

/* The following section, which declares the _getdiskfree() function
 * prototype, and also defines its associated _diskfree_t data structure,
 * is to be processed both when including <dos.h> in its own right, and
 * when selectively included by <direct.h>; however...
 */
#if ! (defined _DOS_H && defined _DIRECT_H)
 /* ...when both the _DOS_H guard, and the _DIRECT_H multiple inclusion
  * guards have been defined, by the time we get to here, then this is
  * <dos.h> inclusion in its own right, and we have ALREADY processed
  * these definitions through selective inclusion by <direct.h>; we
  * MUST NOT process them a second time.
  */
#ifndef	_NO_OLDNAMES
# define diskfree_t  _diskfree_t
#endif

struct _diskfree_t
{ /* A structure in which to store information about disk
   * free space, as returned by the _getdiskfree() function.
   */
  unsigned total_clusters;
  unsigned avail_clusters;
  unsigned sectors_per_cluster;
  unsigned bytes_per_sector;
};

_CRTIMP __cdecl __MINGW_NOTHROW
unsigned _getdiskfree (unsigned, struct _diskfree_t *);

#endif	/* ! ( _DOS_H && _DIRECT_H) */

_END_C_DECLS

#endif	/* ! RC_INVOKED */
#endif  /* !_DOS_H: $RCSfile: dos.h,v $: end of file */

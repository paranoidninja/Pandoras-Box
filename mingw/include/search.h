/*
 * search.h
 *
 * Functions for searching and sorting.
 *
 * $Id: search.h,v b5eb78a1f3b9 2016/07/03 19:23:28 keithmarshall $
 *
 * Written by Danny Smith <dannysmith@users.sourceforge.net>
 * Copyright (C) 2003, 2004, 2007, 2016, MinGW.org Project.
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
#ifndef _SEARCH_H
#pragma GCC system_header
#define _SEARCH_H

/* All MinGW headers must include <_mingw.h>
 */
#include <_mingw.h>

#ifndef RC_INVOKED

_BEGIN_C_DECLS

/* POSIX specifies that <search.h> must define size_t, as it
 * is defined in <sys/types.h>; get it from <stddef.h>, just as
 * <sys/types.h> does.
 */
#define __need_size_t
#include <stddef.h>

/* All search functions require a user-specified comparator
 * function, to be passed as an argument; this typedef is a
 * convenient shorthand for its generic prototype.
 */
typedef int (*__search_comparator)(const void *, const void *);

/* POSIX specifies that bsearch() and qsort() are to be declared in
 * <stdlib.h>, and NOT here; they ARE duplicated here, for Microsoft
 * compatibility only.
 */
_CRTIMP __cdecl  void *bsearch
(const void *, const void *, size_t, size_t, __search_comparator );

_CRTIMP __cdecl  void qsort (void *, size_t, size_t, __search_comparator );

/* This pair of functions are Microsoft specific; see below for their
 * POSIX counterparts, (corresponding to Microsoft's old names).
 */
_CRTIMP __cdecl  void *_lfind
(const void *, const void *, unsigned int *, unsigned int, __search_comparator );

_CRTIMP __cdecl  void *_lsearch
(const void *, void *, unsigned int *, unsigned int, __search_comparator );

#ifdef _POSIX_C_SOURCE
/* Documentation for the following POSIX definitions and prototypes
 * may be found in the Open Group Base Specifications Issue 7, (which
 * corresponds to IEEE Std 1003.1, 2008 Edition); see:
 *
 * http://pubs.opengroup.org/onlinepubs/9699919799/basedefs/search.h.html
 */
typedef
struct entry
{ char	*key;
  void	*data;
} ENTRY;

typedef
enum { FIND, ENTER } ACTION;

typedef
enum { preorder, postorder, endorder, leaf } VISIT;

#ifdef _SEARCH_PRIVATE
/* For private use within the respective tree function implementations,
 * we define a structured representation of a tree node.
 *
 * FIXME: this really doesn't belong here!  Users should NEVER enable
 * this feature test; they should not be given this opportunity.
 */
typedef
struct node
{ const void	*key;
  struct node 	*llink, *rlink;
} node_t;

/* Suppress non-null argument annotations, when building the tsearch(),
 * tfind(), tdelete(), and twalk() implementations, to ensure that GCC
 * does not optimize away internal argument validation checks.
 */
#undef  __MINGW_ATTRIB_NONNULL
#define __MINGW_ATTRIB_NONNULL(ARG_INDEX)  /* NOTHING */

#endif	/* _SEARCH_PRIVATE */

__cdecl  void *tdelete
(const void *__restrict__, void **__restrict__, __search_comparator)
__MINGW_ATTRIB_NONNULL(2) __MINGW_ATTRIB_NONNULL(3);

__cdecl  void *tfind (const void *, void *const *, __search_comparator)
__MINGW_ATTRIB_NONNULL(2) __MINGW_ATTRIB_NONNULL(3);

__cdecl  void *tsearch (const void *, void **, __search_comparator)
__MINGW_ATTRIB_NONNULL(2) __MINGW_ATTRIB_NONNULL(3);

__cdecl  void  twalk (const void *, void (*)(const void *, VISIT, int))
__MINGW_ATTRIB_NONNULL(1) __MINGW_ATTRIB_NONNULL(2);

#endif	/* _POSIX_C_SOURCE */

#if !defined _NO_OLDNAMES || defined _POSIX_C_SOURCE
/* Declared as deprecated, by Microsoft, but these are the POSIX names
 * for the functions which Microsoft now call _lfind() and _lsearch().
 */
_CRTIMP __cdecl  void *lfind
(const void *, const void *, unsigned int *, unsigned int, __search_comparator);

_CRTIMP __cdecl  void *lsearch
(const void *, void *, unsigned int *, unsigned int, __search_comparator);
#endif

_END_C_DECLS

#endif	/* ! RC_INVOKED */
#endif	/* !_SEARCH_H: $RCSfile: search.h,v $: end of file */

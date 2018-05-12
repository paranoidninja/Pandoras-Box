/*
 * winable.h
 *
 * Obsolete header replaced by <winuser.h>; this stub is retained for
 * backward compatibility only.
 *
 * $Id: obsolete.h.in,v 756f7efeba83 2016/11/26 22:35:10 keithmarshall $
 *
 * Written by Keith Marshall <keithmarshall@users.sourceforge.net>
 * Copyright (C) 2016, MinGW.org Project
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
#ifndef _WINABLE_H
#pragma GCC system_header
#define _WINABLE_H

/* Header <winable.h> is obsolete, and we would like to advise the user to
 * use <winuser.h> instead; however...
 */
#ifndef __IN_W32API_TESTSUITE__
/* ...this warning may interfere with any testsuite results, so display it
 * only in normal use, (i.e. suppress it when running the testsuite)...
 */
#warning "<winable.h> is obsolete; please use <winuser.h> instead."
#endif
/* ...always including the appropriate replacement header, regardless.
 */
#include "winuser.h"

#endif	/* !_WINABLE_H: $RCSfile: obsolete.h.in,v $: end of file */

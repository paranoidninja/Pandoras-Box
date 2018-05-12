/*
 * dir.h
 *
 * Obsolete header replaced by <io.h>; this stub is retained for
 * backward compatibility only.
 *
 * $Id: dir.h,v 466a876b8525 2016/09/13 20:14:13 keithmarshall $
 *
 * Written by Colin Peters <colin@bird.fu.is.saga-u.ac.jp>
 * Copyright (C) 1997-1999, 2001, 2016, MinGW.org Project
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
#ifndef _DIR_H
#pragma GCC system_header
#define _DIR_H

/* Header <dir.h> is obsolete, and we would like to advise the user to
 * use <io.h> instead; however...
 */
#ifndef __IN_MINGWRT_TESTSUITE__
/* ...this warning will interfere with the testsuite result, so display
 * it only in normal use, (i.e. suppress it when running the testsuite)...
 */
#warning "<dir.h> is obsolete; please use <io.h> instead."
#endif
/* ...always including the appropriate replacement header, regardless.
 */
#include "io.h"

#endif	/* !_DIR_H: $RCSfile: dir.h,v $: end of file */

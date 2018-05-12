/*
 * float.h
 *
 * Constants related to floating point arithmetic.  Also included here are
 * some non-ANSI mechanisms for accessing the floating point controller.
 *
 * $Id: float.h,v af569eb5aad7 2017/02/27 17:46:27 keithmarshall $
 *
 * Written by Colin Peters <colin@bird.fu.is.saga-u.ac.jp>
 * Copyright (C) 1997, 1999-2005, 2007, 2010, 2011, 2017, MinGW.org Project
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
#ifndef _MINGW_FLOAT_H
#pragma  GCC system_header
#define _MINGW_FLOAT_H
/*
 * NOTE:
 *
 * GCC provides float.h, but it doesn't include the non-standard stuff for
 * accessing the fp controller.  We parse the GCC-supplied header, for its
 * standard content, and then define the MS-specific extensions here.
 *
 * In a MinGW standard Win32 hosted environment, this should be the float.h
 * found by a system include path search, but this can't be guaranteed; for
 * a cross-compiler setup, the GCC-supplied header, which is guarded by the
 * _FLOAT_H___ macro, may be found first, thus, except when compiling any
 * __LIBIMPL__ stub...
 *
 */
#if !defined(_FLOAT_H___) && !defined(__FLOAT_H)
 /* ...when we didn't find the GCC-supplied header first, we want to pull
  * it in now; include_next should achieve this, (and we must rely on the
  * GCC header maintainers to extend us the same courtesy, to get this one
  * pulled in, when the GCC-supplied header is found first).
  */
# define _MINGW_FLOAT_H_  1	/* GCC's <float.h> needs to see this */
# include_next <float.h>	/* !__CRT_ALIAS __LIBIMPL__( FUNCTION = fpreset ) */
#endif

/* All MinGW headers are required to include <_mingw.h>
 */
#include <_mingw.h>

/* Functions and definitions for controlling the FPU.
 */
#ifndef __STRICT_ANSI__

/* TODO: These constants are only valid for x86 machines */

/* Control word masks for unMask
 */
#define _MCW_EM 		0x0008001F	/* Error masks */
#define _MCW_IC 		0x00040000	/* Infinity */
#define _MCW_RC 		0x00000300	/* Rounding */
#define _MCW_PC 		0x00030000	/* Precision */

/* Control word values for unNew (use with related unMask above)
 */
#define _EM_INVALID		0x00000010
#define _EM_DENORMAL		0x00080000
#define _EM_ZERODIVIDE		0x00000008
#define _EM_OVERFLOW		0x00000004
#define _EM_UNDERFLOW		0x00000002
#define _EM_INEXACT		0x00000001
#define _IC_AFFINE		0x00040000
#define _IC_PROJECTIVE		0x00000000
#define _RC_CHOP		0x00000300
#define _RC_UP			0x00000200
#define _RC_DOWN		0x00000100
#define _RC_NEAR		0x00000000
#define _PC_24			0x00020000
#define _PC_53			0x00010000
#define _PC_64			0x00000000

#ifndef __MINGW_FPCLASS_DEFINED
#define __MINGW_FPCLASS_DEFINED  1
/* These are also defined in MinGW <math.h>; these duplicates are
 * needed here, to work around GCC build issues.  FIXME: we should
 * be able to factor this, at least to avoid any potential for the
 * introduction of inconsistent definitions.
 *
 *
 * Return values for fpclass.
 */
#define _FPCLASS_SNAN		    0x0001	/* Signaling "Not a Number" */
#define _FPCLASS_QNAN		    0x0002	/* Quiet "Not a Number" */
#define _FPCLASS_NINF		    0x0004	/* Negative Infinity */
#define _FPCLASS_NN		    0x0008	/* Negative Normal */
#define _FPCLASS_ND		    0x0010	/* Negative Denormal */
#define _FPCLASS_NZ		    0x0020	/* Negative Zero */
#define _FPCLASS_PZ		    0x0040	/* Positive Zero */
#define _FPCLASS_PD		    0x0080	/* Positive Denormal */
#define _FPCLASS_PN		    0x0100	/* Positive Normal */
#define _FPCLASS_PINF		    0x0200	/* Positive Infinity */

#endif /* __MINGW_FPCLASS_DEFINED */

/* Invalid subconditions (_SW_INVALID also set)
 */
#define _SW_UNEMULATED		    0x0040	/* unemulated instruction */
#define _SW_SQRTNEG		    0x0080	/* square root of a neg number */
#define _SW_STACKOVERFLOW	    0x0200	/* FP stack overflow */
#define _SW_STACKUNDERFLOW	    0x0400	/* FP stack underflow */

/* Floating point error signals and return codes
 */
#define _FPE_INVALID		      0x81
#define _FPE_DENORMAL		      0x82
#define _FPE_ZERODIVIDE 	      0x83
#define _FPE_OVERFLOW		      0x84
#define _FPE_UNDERFLOW		      0x85
#define _FPE_INEXACT		      0x86
#define _FPE_UNEMULATED 	      0x87
#define _FPE_SQRTNEG		      0x88
#define _FPE_STACKOVERFLOW	      0x8A
#define _FPE_STACKUNDERFLOW	      0x8B
#define _FPE_EXPLICITGEN	      0x8C	/* raise SIGFPE */

#ifndef RC_INVOKED

_BEGIN_C_DECLS

/* Set the FPU control word as cw = (cw & ~unMask) | (unNew & unMask),
 * i.e. change the bits in unMask to have the values they have in unNew,
 * leaving other bits unchanged.
 */
_CRTIMP __cdecl __MINGW_NOTHROW  unsigned int _controlfp (unsigned int unNew, unsigned int unMask);
_CRTIMP __cdecl __MINGW_NOTHROW  unsigned int _control87 (unsigned int unNew, unsigned int unMask);

#define _clear87   _clearfp
#define _status87  _statusfp

_CRTIMP __cdecl __MINGW_NOTHROW  unsigned int _clearfp (void);	/* Clear the FPU status word */
_CRTIMP __cdecl __MINGW_NOTHROW  unsigned int _statusfp (void);	/* Report the FPU status word */


/* MSVCRT.DLL provides _fpreset() to initialize the FPU; it initializes
 * the control register to 0x27F, (thus selecting 53-bit precision), the
 * status register to zero and the tag word to 0FFFFh.  This differs from
 * Intel's default configuration, (as established by the asm instructions
 * "finit" and "fninit"), which set the control word to 0x37F, (yielding
 * 64-bit precison rather than 53-bit).
 *
 * Nominally, MinGW prefers to configure the FPU for 64-bit precision, as
 * that is a better fit for support of GCC's 10-byte long doubles.  This
 * was formerly achieved by provision of an alternative implementation of
 * _fpreset(), intended to be statically linked into MinGW applications,
 * (with variants enabling 64-bit precision by default, or alternatively,
 * when the application is explicitly linked with CRT_fp8.o, providing
 * 53-bit precision instead).  Unfortunately, this linking strategy may
 * lead to non-deterministic ambiguity over which _fpreset() variant is
 * called, in the event of the call originating in any user implemented,
 * or third party DLL.  Consequently, support for this strategy has been
 * withdrawn.  _fpreset() now ALWAYS refers to the MSVCRT.DLL function,
 * (and thus ALWAYS selects 53-bit precision); MinGW applications should
 * now use the ISO-C99 standard fesetenv() function to configure the FPU,
 * (as the start-up code now does, to enable 64-bit precision by default,
 * but continuing to support linking with CRT_fp8.o, to initialize the
 * configuration to 53-bit precision).
 */
_CRTIMP __cdecl __MINGW_NOTHROW  void _fpreset (void);

/* Former MinGW releases also provided fpreset(), implemented as an alias
 * for _fpreset(), (in whichever guise it was deployed); deprecate this,
 * but retain the association for backward compatibility, (noting that it
 * will now redirect the call to fesetenv(), as recommended above, with
 * the configuration selection set to FE_DFL_ENV).
 */
__cdecl __MINGW_NOTHROW  void fpreset (void) __MINGW_ATTRIB_DEPRECATED;

#ifndef __NO_INLINE__
/* Provide the implementation of fpreset() as an inline stub; for this,
 * we need to expose a minimal opaque subset of <fenv.h>, and we assume
 * that FE_DFL_ENV is equivalent to (const fenv_t *)(0), (as it is, in
 * the MinGW implementation of <fenv.h>).
 */
typedef struct __fenv_t fenv_t;
__cdecl __MINGW_NOTHROW  int fesetenv (const fenv_t *);

__CRT_ALIAS __LIBIMPL__( FUNCTION = fpreset )
void fpreset (void){ fesetenv ((const fenv_t *)(0)); }
#endif

/* Global 'variable' for the current floating point error code.
 */
#define _fpecode  (*(__fpecode()))
_CRTIMP __cdecl __MINGW_NOTHROW  int *__fpecode (void);

/* IEEE recommended functions.  Microsoft puts them in <float.h>,
 * but they really belong in math.h.
 */
_CRTIMP __cdecl __MINGW_NOTHROW  double _chgsign (double);
_CRTIMP __cdecl __MINGW_NOTHROW  double _copysign (double, double);
_CRTIMP __cdecl __MINGW_NOTHROW  double _logb (double);
_CRTIMP __cdecl __MINGW_NOTHROW  double _nextafter (double, double);
_CRTIMP __cdecl __MINGW_NOTHROW  double _scalb (double, long);

_CRTIMP __cdecl __MINGW_NOTHROW  int _finite (double);
_CRTIMP __cdecl __MINGW_NOTHROW  int _fpclass (double);
_CRTIMP __cdecl __MINGW_NOTHROW  int _isnan (double);

_END_C_DECLS

#endif	/* ! RC_INVOKED */
#endif	/* !__STRICT_ANSI__ */

#endif	/* _MINGW_FLOAT_H: $RCSfile: float.h,v $: end of file */

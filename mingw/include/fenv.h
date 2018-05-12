/*
 * fenv.h
 *
 * Structures and constants defining, and functions for management of,
 * the floating point environment.
 *
 * $Id: fenv.h,v af569eb5aad7 2017/02/27 17:46:27 keithmarshall $
 *
 * Written by Danny Smith <dannysmith@users.sourceforge.net>
 * Copyright (C) 2002, 2003, 2005-2007, 2017, MinGW.org Project
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
#ifndef _FENV_H
#pragma  GCC system_header
#define _FENV_H

/* All MinGW headers are required to include <_mingw.h>
 */
#include <_mingw.h>

/* FPU status word flags indicating exceptions.  Each is represented
 * by a single bit, sequentially and contiguously assigned to the low
 * order bits of the status word, enumerated from lowest:
 */
enum
{ __FE_INVALID_EXCEPT_FLAG_SHIFT,
  __FE_DENORMAL_EXCEPT_FLAG_SHIFT,
  __FE_DIVBYZERO_EXCEPT_FLAG_SHIFT,
  __FE_OVERFLOW_EXCEPT_FLAG_SHIFT,
  __FE_UNDERFLOW_EXCEPT_FLAG_SHIFT,
  __FE_INEXACT_EXCEPT_FLAG_SHIFT,

  /* The final entry in the shift enumeration represents the order
   * of the rightmost bit which does NOT represent an exception flag;
   * we use it as a high water mark, for generation of the aggregate
   * mask for ALL exception flags; arithmetically, this becomes the
   * numeric value of a pseudo-flag placed at the high water mark,
   * less one.
   */
  __FE_ALL_EXCEPT_HWM_SHIFT
# define FE_ALL_EXCEPT		((0x01 << __FE_ALL_EXCEPT_HWM_SHIFT) - 1)
};

#define __FE_EXCEPT(__NAME__)	 (0x01 << __FE_##__NAME__##_EXCEPT_FLAG_SHIFT)

#define FE_INVALID		  __FE_EXCEPT(INVALID)
#define FE_DENORMAL		  __FE_EXCEPT(DENORMAL)
#define FE_DIVBYZERO		  __FE_EXCEPT(DIVBYZERO)
#define FE_OVERFLOW		  __FE_EXCEPT(OVERFLOW)
#define FE_UNDERFLOW		  __FE_EXCEPT(UNDERFLOW)
#define FE_INEXACT		  __FE_EXCEPT(INEXACT)

/* FPU control word flags to specify rounding mode; this may be
 * represented as a selection from a four-way enumeration...
 */
enum
{ __FE_ROUND_TONEAREST,
  __FE_ROUND_DOWNWARD,
  __FE_ROUND_UPWARD,
  __FE_ROUND_TOWARDZERO
};
/* ...with the actual flag bits offset 10-bits from the rightmost
 * bit in the control word; hence, the rounding mode macros become:
 */
#define __FE_ROUND(__MODE__)	(__FE_ROUND_##__MODE__ << 10)

#define FE_TONEAREST		 __FE_ROUND(TONEAREST)
#define FE_DOWNWARD		 __FE_ROUND(DOWNWARD)
#define FE_UPWARD		 __FE_ROUND(UPWARD)
#define FE_TOWARDZERO		 __FE_ROUND(TOWARDZERO)

/* The MXCSR exception flags are the same as those for the FPU...
 */
#define __MXCSR_EXCEPT_FLAG_SHIFT  0

/* ...and the corresponding mask bits are offset by a further 7-bit
 * shift to the left...
 */
#define __MXCSR_EXCEPT_MASK_SHIFT  7

/* ...while the MXCSR rounding mode flags adopt the same enumeration,
 * but are offset a further 3-bits to the left of those representing
 * the FPU rounding mode selection flags.
 */
#define __MXCSR_ROUND_FLAG_SHIFT   3

#ifndef RC_INVOKED
/* For now, support only for the basic abstraction of flags that are
 * either set or clear; fexcept_t could be a structure that holds more
 * info about the fp environment.
 */
typedef unsigned short fexcept_t;

typedef struct __fenv_t
{ /* This 28-byte structure represents the entire floating point
   * environment of the FPU, as stored by either the "fnstenv", or
   * the "fstenv" instruction.
   */
  unsigned short	__control_word;
  unsigned short	__unused0;
  unsigned short	__status_word;
  unsigned short	__unused1;
  unsigned short	__tag_word;
  unsigned short	__unused2;
  unsigned int		__ip_offset;    /* instruction pointer offset */
  unsigned short	__ip_selector;
  unsigned short	__opcode;
  unsigned int		__data_offset;
  unsigned short	__data_selector;
  unsigned short	__unused3;

  /* The structure is extended, beyond the 28 byte requirement to
   * store the FPU state, by 4 additional bytes, which then makes it
   * sufficient to also store the contents of the MXCSR register, as
   * stored by the "stmxcsr" instruction, (if the CPU supports it).
   */
  unsigned int		__mxcsr;	/* content of the MXCSR register */
} fenv_t;

/* The ISO-C99 standard, section 7.6 paragraph 8 requires us to define
 * the FE_DFL_ENV macro; it specifies restoration of the FPU environment
 * to its default state, as established at application start-up.
 */
#define FE_DFL_ENV    ((const fenv_t *)(0))

/* Paragraph 9 of the same section of ISO-C99 provides for the definition
 * of implementation-specific macros to identify alternative predefined
 * FPU environment configuration; we exploit this licence to offer:
 *
 *   FP_PC64_ENV  --  Intel standard 80-bit (64-bit precision); this is
 *		      consistent with IEEE-754 extended precision, and
 *		      the configuration preferred by MinGW, because it
 *		      matches the format of GCC's 80-bit long doubles.
 *
 *   FP_PC53_ENV  --  IEEE-754 64-bit (53-bit precision); consistent
 *		      with Microsoft's preferred FPU configuration;
 *		      (they offer no better than 64-bit long doubles).
 */
#define FE_PC64_ENV   ((const fenv_t *)(-1))
#define FE_PC53_ENV   ((const fenv_t *)(-2))

/* The following pair of additional predefined environment macros serve
 * as aliases for the preceding pair, respectively, with the added side
 * effect that, when passed to fesetenv(), each causes its respective
 * alias to become associated with FE_DFL_ENV in subsequent calls.
 */
#define FE_PD64_ENV   ((const fenv_t *)(-3))
#define FE_PD53_ENV   ((const fenv_t *)(-4))

_BEGIN_C_DECLS

/*TODO: Some of these could be inlined */

/* ISO-C99 section 7.6.2 -- Floating Point Exception Handling
 */
extern __cdecl __MINGW_NOTHROW  int feclearexcept (int);
extern __cdecl __MINGW_NOTHROW  int fegetexceptflag (fexcept_t *, int);
extern __cdecl __MINGW_NOTHROW  int feraiseexcept (int);
extern __cdecl __MINGW_NOTHROW  int fesetexceptflag (const fexcept_t *, int);
extern __cdecl __MINGW_NOTHROW  int fetestexcept (int);

/* ISO-C99 section 7.6.3 -- Floating Point Rounding Mode Control
 */
extern __cdecl __MINGW_NOTHROW  int fegetround (void);
extern __cdecl __MINGW_NOTHROW  int fesetround (int);

/* ISO-C99 section 7.6.4 -- Floating Point Environment Configuration
 */
extern __cdecl __MINGW_NOTHROW  int fegetenv (fenv_t *);
extern __cdecl __MINGW_NOTHROW  int fesetenv (const fenv_t *);
extern __cdecl __MINGW_NOTHROW  int feupdateenv (const fenv_t *);
extern __cdecl __MINGW_NOTHROW  int feholdexcept (fenv_t *);

_END_C_DECLS

#endif	/* ! RC_INVOKED */
#endif	/* !_FENV_H: $RCSfile: fenv.h,v $: end of file */

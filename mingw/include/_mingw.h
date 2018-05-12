#ifndef __MINGW_H
/*
 * _mingw.h
 *
 * MinGW specific macros included by ALL mingwrt include files; (this file
 * is part of the MinGW32 runtime library package).
 *
 * $Id: _mingw.h.in,v dab5f46101c7 2017/06/05 19:15:12 keithmarshall $
 *
 * Written by Mumit Khan  <khan@xraylith.wisc.edu>
 * Copyright (C) 1999, 2001-2011, 2014-2017, MinGW.org Project
 *
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 */
#define __MINGW_H

/* In previous versions, __MINGW32_VERSION was expressed as a dotted
 * numeric pair, representing major.minor; unfortunately, this doesn't
 * adapt well to the inclusion of a patch-level component, since the
 * major.minor.patch dotted triplet representation is not valid as a
 * numeric entity.  Thus, for this version, we adopt a representation
 * which encodes the version as a long integer value, expressing:
 *
 *   __MINGW32_VERSION = 1,000,000 * major + 1,000 * minor + patch
 *
 * DO NOT EDIT these package version assignments manually; they are
 * derived from the package version specification within configure.ac,
 * whence they are propagated automatically, at package build time.
 */
#define __MINGW32_VERSION           5000002L
#define __MINGW32_MAJOR_VERSION           5
#define __MINGW32_MINOR_VERSION           0
#define __MINGW32_PATCHLEVEL              2

#if __GNUC__ >= 3 && ! defined __PCC__
#pragma GCC system_header
#endif

#ifndef _MSVCRTVER_H
/* Legacy versions of mingwrt use the macro __MSVCRT_VERSION__ to
 * enable evolving features of different MSVCRT.DLL versions.  This
 * usage is no longer recommended, but the __MSVCRT_VERSION__ macro
 * remains useful when a non-freely distributable MSVCRxx.DLL is to
 * be substituted for MSVCRT.DLL; for such usage, the substitute
 * MSVCRxx.DLL may be identified as specified in...
 */
# include <msvcrtver.h>
#endif

/* A better inference than __MSVCRT_VERSION__, of the capabilities
 * supported by the operating system default MSVCRT.DLL, is provided
 * by the Windows API version identification macros.
 */
#include <w32api.h>

/* The following are defined by the user (or by the compiler), to specify how
 * identifiers are imported from a DLL.  All headers should include this first,
 * and then use __DECLSPEC_SUPPORTED to choose between the old ``__imp__name''
 * style or the __MINGW_IMPORT style for declarations.
 *
 * __DECLSPEC_SUPPORTED            Defined if dllimport attribute is supported.
 * __MINGW_IMPORT                  The attribute definition to specify imported
 *                                 variables/functions.
 * _CRTIMP                         As above.  For MS compatibility.
 *
 * Macros to enable MinGW features which deviate from standard MSVC
 * compatible behaviour; these may be specified directly in user code,
 * activated implicitly, (e.g. by specifying _POSIX_C_SOURCE or such),
 * or by inclusion in __MINGW_FEATURES__:
 *
 * __USE_MINGW_ANSI_STDIO          Select a more ANSI C99 compatible
 *                                 implementation of printf() and friends;
 *                                 (users should not set this directly).
 *
 * Other macros:
 *
 * __int64                         define to be long long.  Using a typedef
 *                                 doesn't work for "unsigned __int64"
 *
 *
 * Manifest definitions for flags to control globbing of the command line
 * during application start up, (before main() is called).  The first pair,
 * when assigned as bit flags within _CRT_glob, select the globbing algorithm
 * to be used; (the MINGW algorithm overrides MSCVRT, if both are specified).
 * Prior to mingwrt-3.21, only the MSVCRT option was supported; this choice
 * may produce different results, depending on which particular version of
 * MSVCRT.DLL is in use; (in recent versions, it seems to have become
 * definitively broken, when globbing within double quotes).
 */
#define __CRT_GLOB_USE_MSVCRT__  	0x0001

/* From mingwrt-3.21 onward, this should be the preferred choice; it will
 * produce consistent results, regardless of the MSVCRT.DLL version in use.
 */
#define __CRT_GLOB_USE_MINGW__   	0x0002

/* When the __CRT_GLOB_USE_MINGW__ flag is set, within _CRT_glob, the
 * following additional options are also available; they are not enabled
 * by default, but the user may elect to enable any combination of them,
 * by setting _CRT_glob to the boolean sum (i.e. logical OR combination)
 * of __CRT_GLOB_USE_MINGW__ and the desired options.
 *
 *    __CRT_GLOB_USE_SINGLE_QUOTE__	allows use of single (apostrophe)
 *    					quoting characters, analogously to
 *    					POSIX usage, as an alternative to
 *    					double quotes, for collection of
 *    					arguments separated by white space
 *    					into a single logical argument.
 *
 *    __CRT_GLOB_BRACKET_GROUPS__	enable interpretation of bracketed
 *    					character groups as POSIX compatible
 *    					globbing patterns, matching any one
 *    					character which is either included
 *    					in, or excluded from the group.
 *
 * The following options, which may also be specified within _CRT_glob,
 * are specified in terms of their glob() flags, as defined in <glob.h>
 *
 *    GLOB_CASEMATCH			enable case sensitive matching for
 *    					globbing patterns; this is default
 *    					behaviour for POSIX, but because of
 *    					the case insensitive nature of the
 *    					MS-Windows file system, it is more
 *    					appropriate to use case insensitive
 *    					globbing as the MinGW default.
 *
 *    GLOB_BRACE			enable expansion of GNU style brace
 *    					delimited expression groups within
 *    					the globbing pattern.
 *
 */
#define __CRT_GLOB_USE_SINGLE_QUOTE__	0x0010
#define __CRT_GLOB_BRACKET_GROUPS__	0x0020

/* The MinGW globbing algorithm uses the ASCII DEL control code as a marker
 * for globbing characters which were embedded within quoted arguments; (the
 * quotes are stripped away BEFORE the argument is globbed; the globbing code
 * treats the marked character as immutable, and strips out the DEL markers,
 * before storing the resultant argument).  The DEL code is mapped to this
 * function here; DO NOT change it, without rebuilding the runtime.
 */
#define __CRT_GLOB_ESCAPE_CHAR__	(char)(127)


/* Manifest definitions identifying the flag bits, controlling activation
 * of MinGW features, as specified by the user in __MINGW_FEATURES__.
 */
#define __MINGW_ANSI_STDIO__		0x0000000000000001ULL
/*
 * The following three are not yet formally supported; they are
 * included here, to document anticipated future usage.
 */
#define __MINGW_LC_EXTENSIONS__ 	0x0000000000000050ULL
#define __MINGW_LC_MESSAGES__		0x0000000000000010ULL
#define __MINGW_LC_ENVVARS__		0x0000000000000040ULL


/* Try to avoid problems with outdated checks for GCC __attribute__ support.
 */
#undef __attribute__

#if defined (__PCC__)
#  undef __DECLSPEC_SUPPORTED
# ifndef __MINGW_IMPORT
#  define __MINGW_IMPORT extern
# endif
# ifndef _CRTIMP
#  define _CRTIMP
# endif
# ifndef __cdecl
#  define __cdecl  _Pragma("cdecl")
# endif
# ifndef __stdcall
#  define __stdcall _Pragma("stdcall")
# endif
# ifndef __int64
#  define __int64 long long
# endif
# ifndef __int32
#  define __int32 long
# endif
# ifndef __int16
#  define __int16 short
# endif
# ifndef __int8
#  define __int8 char
# endif
# ifndef __small
#  define __small char
# endif
# ifndef __hyper
#  define __hyper long long
# endif
# ifndef __volatile__
#  define __volatile__ volatile
# endif
# ifndef __restrict__
#  define __restrict__ restrict
# endif
# define NONAMELESSUNION
#elif defined(__GNUC__)
# ifdef __declspec
#  ifndef __MINGW_IMPORT
   /* Note the extern. This is needed to work around GCC's
      limitations in handling dllimport attribute.  */
#   define __MINGW_IMPORT  extern __attribute__((__dllimport__))
#  endif
#  ifndef _CRTIMP
#   ifdef __USE_CRTIMP
#    define _CRTIMP  __attribute__((dllimport))
#   else
#    define _CRTIMP
#   endif
#  endif
#  define __DECLSPEC_SUPPORTED
# else /* __declspec */
#  undef __DECLSPEC_SUPPORTED
#  undef __MINGW_IMPORT
#  ifndef _CRTIMP
#   define _CRTIMP
#  endif
# endif /* __declspec */
/*
 * The next two defines can cause problems if user code adds the
 * __cdecl attribute like so:
 * void __attribute__ ((__cdecl)) foo(void);
 */
# ifndef __cdecl
#  define __cdecl  __attribute__((__cdecl__))
# endif
# ifndef __stdcall
#  define __stdcall __attribute__((__stdcall__))
# endif
# ifndef __int64
#  define __int64 long long
# endif
# ifndef __int32
#  define __int32 long
# endif
# ifndef __int16
#  define __int16 short
# endif
# ifndef __int8
#  define __int8 char
# endif
# ifndef __small
#  define __small char
# endif
# ifndef __hyper
#  define __hyper long long
# endif
#else /* ! __GNUC__ && ! __PCC__ */
# ifndef __MINGW_IMPORT
#  define __MINGW_IMPORT  __declspec(dllimport)
# endif
# ifndef _CRTIMP
#  define _CRTIMP  __declspec(dllimport)
# endif
# define __DECLSPEC_SUPPORTED
# define __attribute__(x) /* nothing */
#endif

#if defined (__GNUC__) && defined (__GNUC_MINOR__)
#define __MINGW_GNUC_PREREQ(major, minor) \
  (__GNUC__ > (major) \
   || (__GNUC__ == (major) && __GNUC_MINOR__ >= (minor)))
#else
#define __MINGW_GNUC_PREREQ(major, minor)  0
#endif

#ifdef __cplusplus
# define __CRT_INLINE    inline
#else
# if __GNUC_STDC_INLINE__
#  define __CRT_INLINE   extern inline __attribute__((__gnu_inline__))
# else
#  define __CRT_INLINE   extern __inline__
# endif
#endif

# ifdef __GNUC__
  /* A special form of __CRT_INLINE is provided; it will ALWAYS request
   * inlining when possible.  Originally specified as _CRTALIAS, this is
   * now deprecated in favour of __CRT_ALIAS, for syntactic consistency
   * with __CRT_INLINE itself.
   */
#  define  _CRTALIAS   __CRT_INLINE __attribute__((__always_inline__))
#  define __CRT_ALIAS  __CRT_INLINE __attribute__((__always_inline__))
# else
#  define  _CRTALIAS   __CRT_INLINE	/* deprecated form */
#  define __CRT_ALIAS  __CRT_INLINE	/* preferred form */
# endif
/*
 * Each function which is implemented as a __CRT_ALIAS should also be
 * accompanied by an externally visible interface.  The following pair
 * of macros provide a mechanism for implementing this, either as a stub
 * redirecting to an alternative external function, or by compilation of
 * the normally inlined code into free standing object code; each macro
 * provides a way for us to offer arbitrary hints for use by the build
 * system, while remaining transparent to the compiler.
 */
#define __JMPSTUB__(__BUILD_HINT__)
#define __LIBIMPL__(__BUILD_HINT__)

#ifdef __cplusplus
# define __UNUSED_PARAM(x)
#else
# ifdef __GNUC__
#  define __UNUSED_PARAM(x) x __attribute__((__unused__))
# else
#  define __UNUSED_PARAM(x) x
# endif
#endif

#ifdef __GNUC__
#define __MINGW_ATTRIB_NORETURN __attribute__((__noreturn__))
#define __MINGW_ATTRIB_CONST __attribute__((__const__))
#else
#define __MINGW_ATTRIB_NORETURN
#define __MINGW_ATTRIB_CONST
#endif

#if __MINGW_GNUC_PREREQ (3, 0)
#define __MINGW_ATTRIB_MALLOC __attribute__((__malloc__))
#define __MINGW_ATTRIB_PURE __attribute__((__pure__))
#else
#define __MINGW_ATTRIB_MALLOC
#define __MINGW_ATTRIB_PURE
#endif

/* Attribute `nonnull' was valid as of gcc 3.3.  We don't use GCC's
   variadiac macro facility, because variadic macros cause syntax
   errors with  --traditional-cpp.  */
#if  __MINGW_GNUC_PREREQ (3, 3)
#define __MINGW_ATTRIB_NONNULL(arg) __attribute__((__nonnull__(arg)))
#else
#define __MINGW_ATTRIB_NONNULL(arg)
#endif /* GNUC >= 3.3 */

#if  __MINGW_GNUC_PREREQ (3, 1)
#define __MINGW_ATTRIB_DEPRECATED __attribute__((__deprecated__))
#else
#define __MINGW_ATTRIB_DEPRECATED
#endif /* GNUC >= 3.1 */

#if  __MINGW_GNUC_PREREQ (3, 3)
#define __MINGW_NOTHROW __attribute__((__nothrow__))
#else
#define __MINGW_NOTHROW
#endif /* GNUC >= 3.3 */


/* TODO: Mark (almost) all CRT functions as __MINGW_NOTHROW.  This will
allow GCC to optimize away some EH unwind code, at least in DW2 case.  */

/* Activation of MinGW specific extended features:
 */
#ifndef __USE_MINGW_ANSI_STDIO
/* Users should not set this directly; rather, define one (or more)
 * of the feature test macros (tabulated below), or specify any of the
 * compiler's command line options, (e.g. -posix, -ansi, or -std=c...),
 * which cause _POSIX_SOURCE, or __STRICT_ANSI__ to be defined.
 *
 * We must check this BEFORE we specifiy any implicit _POSIX_C_SOURCE,
 * otherwise we would always implicitly choose __USE_MINGW_ANSI_STDIO,
 * even if none of these selectors are specified explicitly...
 */
# if   defined __STRICT_ANSI__  ||  defined _ISOC99_SOURCE \
   ||  defined _POSIX_SOURCE    ||  defined _POSIX_C_SOURCE \
   ||  defined _XOPEN_SOURCE    ||  defined _XOPEN_SOURCE_EXTENDED \
   ||  defined _GNU_SOURCE      ||  defined _BSD_SOURCE \
   ||  defined _SVID_SOURCE
   /*
    * but where any of these source code qualifiers are specified,
    * then assume ANSI I/O standards are preferred over Microsoft's...
    */
#  define __USE_MINGW_ANSI_STDIO    1
# else
   /* otherwise use whatever __MINGW_FEATURES__ specifies...
    */
#  define __USE_MINGW_ANSI_STDIO    (__MINGW_FEATURES__ & __MINGW_ANSI_STDIO__)
# endif
#endif

/* Some applications may define _XOPEN_SOURCE, without assigning any
 * value to it.  Such usage may have been permitted in early SUS, but
 * it became obsolete as of SUSv2.  Attempt to detect obsolete usage,
 * as it makes an effective evaluation of any _XOPEN_SOURCE version
 * dependency difficult, (without the use of ugly kludges at EVERY
 * point of reference which attempts a version comparison).
 */
#define __paste(prefix,suffix)  prefix ## suffix
#define __valueless(token)  ((token - 0) == 0) && (__paste(token,10) == 10)

#if defined _XOPEN_SOURCE && __valueless(_XOPEN_SOURCE)
/* _XOPEN_SOURCE appears to have been defined without its mandatory
 * value; diagnose this brain-damaged obsolete usage (verbosely)...
 */
#warning "_XOPEN_SOURCE seems to have been improperly defined."
#warning "Mandatory _XOPEN_SOURCE value assignment appears to be missing."
#warning "Redefining _XOPEN_SOURCE to mitigate obsolete misuse."

/* ...and redefine, emulating implicit behaviour of -D_XOPEN_SOURCE on
 * the GCC command line, (which DOES assign an implied value of one).
 */
#undef  _XOPEN_SOURCE
#define _XOPEN_SOURCE  1
#endif

#ifndef _POSIX_C_SOURCE
 /* Users may define this, either directly or indirectly, to explicitly
  * enable a particular level of visibility for the subset of those POSIX
  * features which are supported by MinGW; (notice that this offers no
  * guarantee that any particular POSIX feature will be supported).
  */
# if defined _XOPEN_SOURCE
  /* Specifying this is the preferred method for setting _POSIX_C_SOURCE;
   * (POSIX defines an explicit relationship to _XOPEN_SOURCE).  Note that
   * any such explicit setting will augment the set of features which are
   * available to any compilation unit, even if it seeks to be strictly
   * ANSI-C compliant.
   */
#  if _XOPEN_SOURCE < 500
#   define _POSIX_C_SOURCE  1L		/* POSIX.1-1990 / SUSv1 */

#  elif _XOPEN_SOURCE < 600
#   define _POSIX_C_SOURCE  199506L	/* POSIX.1-1996 / SUSv2 */

#  elif _XOPEN_SOURCE < 700
#   define _POSIX_C_SOURCE  200112L	/* POSIX.1-2001 / SUSv3 */

#  else
#   define _POSIX_C_SOURCE  200809L	/* POSIX.1-2008 / SUSv4 */
#  endif

# elif defined _GNU_SOURCE || defined _BSD_SOURCE || ! defined __STRICT_ANSI__
  /*
   * No explicit level of support has been specified; implicitly grant
   * the most comprehensive level to any compilation unit which requests
   * either GNU or BSD feature support, or does not seek to be strictly
   * ANSI-C compliant.
   */
#  define _POSIX_C_SOURCE  200809L

#  if ! defined _EMULATE_GLIBC && ! defined _POSIX_SOURCE
   /* For this default case, unless it has already been specified
    * otherwise, we enable some GNU glibc extensions, which may be
    * considered as violations of strict POSIX.1 conformance.
    */
#   define _EMULATE_GLIBC  1
#  endif

# elif defined _POSIX_SOURCE
  /* Now formally deprecated by POSIX, some old code may specify this;
   * it will enable a minimal level of POSIX support, in addition to the
   * limited feature set enabled for strict ANSI-C conformity.
   */
#  define _POSIX_C_SOURCE  1L
# endif
#endif

#ifndef _ISOC99_SOURCE
 /* libmingwex.a provides free-standing implementations for many of the
  * functions which were introduced in C99; MinGW headers do not expose
  * prototypes for these, unless this feature test macro is defined, by
  * the user, or implied by other standards.  We will use a bit-mapped
  * representation, comprising the bit-wise sum of:
  *
  *   0x08  user declared
  *   0x04  required by C compiler, supporting ISO-C99
  *   0x02  required by C++ compiler, supporting ISO-C++11
  *   0x01  required to support recent POSIX.1 features
  *
  * to ensure that we can identify the reason for implicit declaration,
  * (in the event that we may need to discriminate).
  */
# if __STDC_VERSION__ >= 199901L
  /* This represents a compiler supporting ISO-C99; enable all potential
   * use of ISO-C99 features, (to the maximum extent supportable), which
   * presumably also covers all C++11 and POSIX.1 usage.
   */
#  define _ISOC99_SOURCE  0x07

# elif __cplusplus >= 201103L
  /* C++11 also incorporates many (if not all) of the ISO-C99 features,
   * which we have guarded by _ISOC99_SOURCE; enable such features, to
   * the required extent, (which is likely also sufficient to support
   * any POSIX.1 dependencies).
   */
#  define _ISOC99_SOURCE  0x03

# elif _POSIX_C_SOURCE >= 200112L
  /* This represents the minimum level of ISO-C99 support, which may be
   * required by POSIX.1, (and which may be no less than full support).
   */
#  define _ISOC99_SOURCE  0x01
# endif

#else
 /* The the user has explicitly declared a source level dependency on
  * ISO-C99 features; regardless of how it was declared, redefine it to
  * ensure that any plausible dependency is covered.
  */
# undef _ISOC99_SOURCE
# define _ISOC99_SOURCE  0x0F

#endif	/* _ISOC99_SOURCE */

#if _ISOC99_SOURCE && __cplusplus >= 201103L && __GNUC__ < 6
 /* Due to a configuration defect in GCC versions prior to GCC-6, when
  * compiling C++11 code, the ISO-C99 functions may not be incorporated
  * into the appropriate namespace(s); we may be able to mitigate this,
  * by ensuring that these GCC configuration macros are defined.
  */
# define _GLIBCXX_USE_C99	1
# define _GLIBCXX_HAVE_WCSTOF	1
#endif

#if ! defined _MINGW32_SOURCE_EXTENDED && ! defined __STRICT_ANSI__
 /* Enable mingw32 extensions by default, except when __STRICT_ANSI__
  * conformity mode has been enabled.
  */
# define _MINGW32_SOURCE_EXTENDED  1
#endif

#endif /* __MINGW_H: $RCSfile: _mingw.h.in,v $: end of file */

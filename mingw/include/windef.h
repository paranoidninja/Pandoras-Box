/*
 * windef.h
 *
 * Common definitions for the Win32 API.
 *
 * $Id: windef.h,v 34e5e7606781 2016/05/23 18:31:09 keithmarshall $
 *
 * Written by Anders Norlander  <anorland@hem2.passagen.se>
 * Copyright (C) 1998-2002, 2006-2008, 2010, 2015, MinGW.org Project
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
#ifndef _WINDEF_H
#define _WINDEF_H
#pragma GCC system_header

/* We used to provide preprocessor code here, to ensure that WINVER
 * and _WIN32_WINNT are defined; this is now handled by inclusion of
 * w32api.h, which in turn includes sdkddkver.h, so implementing the
 * preferred technique of deriving these from a user assigned, (or
 * default), NTDDI_VERSION setting.
 */
#include <w32api.h>

_BEGIN_C_DECLS

#ifndef WIN32
#define WIN32
#endif
#ifndef _WIN32
#define _WIN32
#endif
#define FAR
#define far
#define NEAR
#define near
#ifndef CONST
#define CONST const
#endif
#undef MAX_PATH
#define MAX_PATH 260

#ifndef NULL
#ifdef __cplusplus
#define NULL 0
#else
#define NULL ((void*)0)
#endif
#endif
#ifndef FALSE
#define FALSE 0
#endif
#ifndef TRUE
#define TRUE 1
#endif

#ifndef _NO_W32_PSEUDO_MODIFIERS
/* Pseudo-modifiers support function argument classification:
 * we don't use these unnecessary defines in the w32api headers,
 * but define them by default, since that is what people expect;
 * this is conditional, so that users may avoid the pollution.
 */
# define IN
# define OUT
# ifndef OPTIONAL
#  define OPTIONAL
# endif
#endif

#ifdef __GNUC__
#ifndef _fastcall
#define _fastcall __attribute__((fastcall))
#endif
#ifndef __fastcall
#define __fastcall __attribute__((fastcall))
#endif
#ifndef _stdcall
#define _stdcall __attribute__((stdcall))
#endif
#ifndef __stdcall
#define __stdcall __attribute__((stdcall))
#endif
#ifndef _cdecl
#define _cdecl __attribute__((cdecl))
#endif
#ifndef __cdecl
#define __cdecl __attribute__((cdecl))
#endif
#ifndef __declspec
#define __declspec(e) __attribute__((e))
#endif
#ifndef _declspec
#define _declspec(e) __attribute__((e))
#endif
#else
#define _cdecl
#define __cdecl
#endif

#undef pascal
#undef _pascal
#undef __pascal
#define pascal __stdcall
#define _pascal __stdcall
#define __pascal __stdcall
#define PASCAL _pascal
#define CDECL _cdecl
#define STDCALL __stdcall
#define FASTCALL __fastcall
#define WINAPI __stdcall
#define WINAPIV __cdecl
#define APIENTRY __stdcall
#define CALLBACK __stdcall
#define APIPRIVATE __stdcall

#define DECLSPEC_IMPORT __declspec(dllimport)
#define DECLSPEC_EXPORT __declspec(dllexport)
#ifdef __GNUC__
#define DECLSPEC_NORETURN __declspec(noreturn)
#define DECLARE_STDCALL_P( type ) __stdcall type
#elif defined(__WATCOMC__)
#define DECLSPEC_NORETURN
#define DECLARE_STDCALL_P( type ) type __stdcall
#endif /* __GNUC__/__WATCOMC__ */
#define MAKEWORD(a,b)	((WORD)(((BYTE)(a))|(((WORD)((BYTE)(b)))<<8)))
#define MAKELONG(a,b)	((LONG)(((WORD)(a))|(((DWORD)((WORD)(b)))<<16)))
#define LOWORD(l)	((WORD)((DWORD)(l)))
#define HIWORD(l)	((WORD)(((DWORD)(l)>>16)&0xFFFF))
#define LOBYTE(w)	((BYTE)(w))
#define HIBYTE(w)	((BYTE)(((WORD)(w)>>8)&0xFF))

#ifndef __WATCOMC__
#ifndef _export
#define _export
#endif
#ifndef __export
#define __export
#endif
#endif

#ifndef NOMINMAX
#ifndef max
#define max(a,b) ((a)>(b)?(a):(b))
#endif
#ifndef min
#define min(a,b) ((a)<(b)?(a):(b))
#endif
#endif

#define UNREFERENCED_PARAMETER(P) {(P)=(P);}
#define UNREFERENCED_LOCAL_VARIABLE(L) {(L)=(L);}
#define DBG_UNREFERENCED_PARAMETER(P)
#define DBG_UNREFERENCED_LOCAL_VARIABLE(L)

#ifndef NONAMELESSUNION
#ifdef __GNUC__
#if __GNUC__ > 2 || (__GNUC__ == 2 && __GNUC_MINOR__ >= 95)
#define _ANONYMOUS_UNION __extension__
#define _ANONYMOUS_STRUCT __extension__
#else
#if defined(__cplusplus)
#define _ANONYMOUS_UNION __extension__
#endif /* __cplusplus */
#endif /* __GNUC__ > 2 || (__GNUC__ == 2 && __GNUC_MINOR__ >= 95) */
#elif defined(__WATCOMC__)
#define _ANONYMOUS_UNION
#define _ANONYMOUS_STRUCT
#endif /* __GNUC__/__WATCOMC__ */
#endif /* NONAMELESSUNION */

#ifndef _ANONYMOUS_UNION
#define _ANONYMOUS_UNION
#define _UNION_NAME(x) x
#define DUMMYUNIONNAME	u
#define DUMMYUNIONNAME2	u2
#define DUMMYUNIONNAME3	u3
#define DUMMYUNIONNAME4	u4
#define DUMMYUNIONNAME5	u5
#define DUMMYUNIONNAME6	u6
#define DUMMYUNIONNAME7	u7
#define DUMMYUNIONNAME8	u8
#else
#define _UNION_NAME(x)
#define DUMMYUNIONNAME
#define DUMMYUNIONNAME2
#define DUMMYUNIONNAME3
#define DUMMYUNIONNAME4
#define DUMMYUNIONNAME5
#define DUMMYUNIONNAME6
#define DUMMYUNIONNAME7
#define DUMMYUNIONNAME8
#endif
#ifndef _ANONYMOUS_STRUCT
#define _ANONYMOUS_STRUCT
#define _STRUCT_NAME(x) x
#define DUMMYSTRUCTNAME	s
#define DUMMYSTRUCTNAME2 s2
#define DUMMYSTRUCTNAME3 s3
#else
#define _STRUCT_NAME(x)
#define DUMMYSTRUCTNAME
#define DUMMYSTRUCTNAME2
#define DUMMYSTRUCTNAME3
#endif

#ifndef NO_STRICT
#ifndef STRICT
#define STRICT 1
#endif
#endif

#if defined (__GNUC__) && defined (__SEH_NOOP)
/* FIXME: This will make some code compile. The programs will most
 * likely crash when an exception is raised, but at least they will
 * compile.
 */
# define __try
# define __except(x) if (0) /* don't execute handler */
# define __finally

# define _try __try
# define _except __except
# define _finally __finally
#endif

typedef unsigned long DWORD;
typedef int WINBOOL,*PWINBOOL,*LPWINBOOL;
/* FIXME: Is there a good solution to this? */
#ifndef XFree86Server
#ifndef __OBJC__
typedef WINBOOL BOOL;
#else
#define BOOL WINBOOL
#endif
typedef unsigned char BYTE;
#endif /* ndef XFree86Server */
typedef BOOL *PBOOL,*LPBOOL;
typedef unsigned short WORD;
typedef float FLOAT;
typedef FLOAT *PFLOAT;
typedef BYTE *PBYTE,*LPBYTE;
typedef int *PINT,*LPINT;
typedef WORD *PWORD,*LPWORD;
typedef long *LPLONG;
typedef DWORD *PDWORD,*LPDWORD;
typedef CONST void *PCVOID,*LPCVOID;
typedef int INT;
typedef unsigned int UINT,*PUINT,*LPUINT;

#include <winnt.h>

typedef UINT_PTR WPARAM;
typedef LONG_PTR LPARAM;
typedef LONG_PTR LRESULT;
#ifndef _HRESULT_DEFINED
typedef LONG HRESULT;
#define _HRESULT_DEFINED
#endif
#ifndef XFree86Server
typedef WORD ATOM;
#endif /* XFree86Server */
typedef HANDLE HHOOK;
typedef HANDLE HGLOBAL;
typedef HANDLE HLOCAL;
typedef HANDLE GLOBALHANDLE;
typedef HANDLE LOCALHANDLE;
typedef void *HGDIOBJ;
DECLARE_HANDLE(HACCEL);
DECLARE_HANDLE(HBITMAP);
DECLARE_HANDLE(HBRUSH);
DECLARE_HANDLE(HCOLORSPACE);
DECLARE_HANDLE(HDC);
DECLARE_HANDLE(HGLRC);
DECLARE_HANDLE(HDESK);
DECLARE_HANDLE(HENHMETAFILE);
DECLARE_HANDLE(HFONT);
DECLARE_HANDLE(HICON);
DECLARE_HANDLE(HKEY);
/* FIXME: How to handle these. SM_CMONITORS etc in winuser.h also. */
DECLARE_HANDLE(HMONITOR);
#define HMONITOR_DECLARED 1
DECLARE_HANDLE(HTERMINAL);
DECLARE_HANDLE(HWINEVENTHOOK);

typedef HKEY *PHKEY;
DECLARE_HANDLE(HMENU);
DECLARE_HANDLE(HMETAFILE);
DECLARE_HANDLE(HINSTANCE);
typedef HINSTANCE HMODULE;
DECLARE_HANDLE(HPALETTE);
DECLARE_HANDLE(HPEN);
DECLARE_HANDLE(HRGN);
DECLARE_HANDLE(HRSRC);
DECLARE_HANDLE(HSTR);
DECLARE_HANDLE(HTASK);
DECLARE_HANDLE(HWND);
DECLARE_HANDLE(HWINSTA);
DECLARE_HANDLE(HKL);
typedef int HFILE;
typedef HICON HCURSOR;
typedef DWORD COLORREF;
typedef int (WINAPI *FARPROC)();
typedef int (WINAPI *NEARPROC)();
typedef int (WINAPI *PROC)();
typedef struct tagRECT {
	LONG left;
	LONG top;
	LONG right;
	LONG bottom;
} RECT,*PRECT,*LPRECT;
typedef const RECT *LPCRECT;
typedef struct tagRECTL {
	LONG left;
	LONG top;
	LONG right;
	LONG bottom;
} RECTL,*PRECTL,*LPRECTL;
typedef const RECTL *LPCRECTL;
typedef struct tagPOINT {
	LONG x;
	LONG y;
} POINT,POINTL,*PPOINT,*LPPOINT,*PPOINTL,*LPPOINTL;
typedef struct tagSIZE {
	LONG cx;
	LONG cy;
} SIZE,SIZEL,*PSIZE,*LPSIZE,*PSIZEL,*LPSIZEL;
typedef struct tagPOINTS {
	SHORT x;
	SHORT y;
} POINTS,*PPOINTS,*LPPOINTS;

_END_C_DECLS

#endif /* _WINDEF_H: $RCSfile: windef.h,v $: end of file */

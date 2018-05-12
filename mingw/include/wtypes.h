/*
 * wtypes.h
 *
 * Miscellaneous Windows data type definitions.
 *
 *
 * $Id: wtypes.h,v 4ea637f851c5 2017/10/30 10:27:32 keithmarshall $
 *
 * Written by Anders Norlander <anorland@hem2.passagen.se>
 * Copyright (C) 1998-2002, 2004, 2007, 2017, MinGW.org Project
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
#ifndef _WTYPES_H
#pragma GCC system_header

/* This file may be selectively included by <nspapi.h>, (possibly
 * on behalf of <winsock2.h>), to expose only the definition of the
 * BLOB data structure.
 */
#ifndef __NSPAPI_H_SOURCED__
/* Only when NOT included in this selective manner, do we proceed
 * to define its full content; note that we continue to defer the
 * definition of the repeat inclusion guard for <wtypes.h> itself,
 * to ensure that the appropriate content remains accessible for
 * recursive inclusion (selectively) while processing <rpc.h>, or
 * <rpcndr.h>, upon both of which <wtypes.h> is dependent.
 */
#include <rpc.h>
#include <rpcndr.h>

_BEGIN_C_DECLS

#define IID_NULL			     GUID_NULL
#define CLSID_NULL 			     GUID_NULL

#define CBPCLIPDATA(d)		  ((d).cbSize-sizeof((d).ulClipFmt))

#define ROTFLAGS_REGISTRATIONKEEPSALIVE 	0x01
#define ROTFLAGS_ALLOWANYCLIENT 		0x02

_END_C_DECLS

#endif	/* !__NSPAPI_H_SOURCED__ */

#ifndef __BLOB_DATA_TYPE_DEFINED__
/* Regardles of how we have been included, we must always define
 * the BLOB data type, (but we must do so only once; note that we
 * use a data type specific guard here, to simplify detection of
 * duplicate exposure of this definition).
 */
_BEGIN_C_DECLS

typedef
struct _BLOB
{ ULONG 		 cbSize;
  BYTE			*pBlobData;
} BLOB, *PBLOB, *LPBLOB;

_END_C_DECLS

#define __BLOB_DATA_TYPE_DEFINED__
#endif	/* !__BLOB_DATA_TYPE_DEFINED__ */

#if ! (defined _WTYPES_H || defined __NSPAPI_H_SOURCED__)
/* Resume specification of the full content of <wtypes.h>; note that,
 * only now, may we safely define the repeat inclusion guard.
 */
#define _WTYPES_H

_BEGIN_C_DECLS

typedef
enum tagDVASPECT
{ DVASPECT_CONTENT			=	 1,
  DVASPECT_THUMBNAIL			=	 2,
  DVASPECT_ICON 			=	 4,
  DVASPECT_DOCPRINT			=	 8
} DVASPECT;

typedef
enum tagDVASPECT2
{ DVASPECT_OPAQUE			=	16,
  DVASPECT_TRANSPARENT			=	32
} DVASPECT2;

typedef
enum tagSTATFLAG
{ STATFLAG_DEFAULT			=	 0,
  STATFLAG_NONAME			=	 1
} STATFLAG;

typedef
enum tagMEMCTX
{ MEMCTX_LOCAL				=	 0,
  MEMCTX_TASK,
  MEMCTX_SHARED,
  MEMCTX_MACSYSTEM,
  MEMCTX_UNKNOWN			=	-1,
  MEMCTX_SAME				=	-2
} MEMCTX;

typedef
enum tagMSHCTX
{ MSHCTX_LOCAL				=	 0,
  MSHCTX_NOSHAREDMEM,
  MSHCTX_DIFFERENTMACHINE,
  MSHCTX_INPROC,
  MSHCTX_CROSSCTX
} MSHCTX;

typedef
enum tagCLSCTX
{ CLSCTX_INPROC_SERVER			=	 1,
  CLSCTX_INPROC_HANDLER 		=	 2,
  CLSCTX_LOCAL_SERVER			=	 4,
  CLSCTX_INPROC_SERVER16		=	 8,
  CLSCTX_REMOTE_SERVER			=	16
} CLSCTX;

typedef
enum tagMSHLFLAGS
{ MSHLFLAGS_NORMAL,
  MSHLFLAGS_TABLESTRONG,
  MSHLFLAGS_TABLEWEAK
} MSHLFLAGS;

typedef
struct _FLAGGED_WORD_BLOB
{ unsigned long 		 fFlags;
  unsigned long 		 clSize;
  unsigned short		 asData[1];
} FLAGGED_WORD_BLOB;

#ifndef OLE2ANSI
typedef WCHAR			 OLECHAR;
typedef LPWSTR			 LPOLESTR;
typedef LPCWSTR 		 LPCOLESTR;

#define OLESTR(s)		 L##s

#else
typedef char			 OLECHAR;
typedef LPSTR			 LPOLESTR;
typedef LPCSTR			 LPCOLESTR;

#define OLESTR(s)		 s
#endif

typedef unsigned short		 VARTYPE;
typedef short			 VARIANT_BOOL;
typedef VARIANT_BOOL		_VARIANT_BOOL;

#define VARIANT_TRUE   ((VARIANT_BOOL)(0xFFFF))
#define VARIANT_FALSE  ((VARIANT_BOOL)(0))

typedef OLECHAR 		*BSTR;
typedef FLAGGED_WORD_BLOB	*wireBSTR;
typedef BSTR			*LPBSTR;
typedef LONG			 SCODE;
typedef void			*HCONTEXT;

typedef
union tagCY
{ _ANONYMOUS_STRUCT struct
  { unsigned long		   Lo;
    long			   Hi;
  }				_STRUCT_NAME(s);
  LONGLONG			 int64;
} CY;

typedef double  DATE;

typedef
struct  tagBSTRBLOB
{ ULONG 			 cbSize;
  PBYTE 			 pData;
} BSTRBLOB, *LPBSTRBLOB;

typedef
struct tagCLIPDATA
{ ULONG 			 cbSize;
  long				 ulClipFmt;
  PBYTE 			 pClipData;
} CLIPDATA;

typedef
enum tagSTGC
{ STGC_DEFAULT,
  STGC_OVERWRITE,
  STGC_ONLYIFCURRENT,
  STGC_DANGEROUSLYCOMMITMERELYTODISKCACHE
} STGC;

typedef
enum tagSTGMOVE
{ STGMOVE_MOVE,
  STGMOVE_COPY,
  STGMOVE_SHALLOWCOPY
} STGMOVE;

enum VARENUM
{ VT_EMPTY,
  VT_NULL,
  VT_I2,
  VT_I4,
  VT_R4,
  VT_R8,
  VT_CY,
  VT_DATE,
  VT_BSTR,
  VT_DISPATCH,
  VT_ERROR,
  VT_BOOL,
  VT_VARIANT,
  VT_UNKNOWN,
  VT_DECIMAL,
  VT_I1 				=	16,
  VT_UI1,
  VT_UI2,
  VT_UI4,
  VT_I8,
  VT_UI8,
  VT_INT,
  VT_UINT,
  VT_VOID,
  VT_HRESULT,
  VT_PTR,
  VT_SAFEARRAY,
  VT_CARRAY,
  VT_USERDEFINED,
  VT_LPSTR,
  VT_LPWSTR,
  VT_RECORD				=	36,
  VT_INT_PTR				=	37,
  VT_UINT_PTR				=	38,
  VT_FILETIME				=	64,
  VT_BLOB,
  VT_STREAM,
  VT_STORAGE,
  VT_STREAMED_OBJECT,
  VT_STORED_OBJECT,
  VT_BLOB_OBJECT,
  VT_CF,
  VT_CLSID,
  VT_BSTR_BLOB				=   0x0FFF,
  VT_VECTOR				=   0x1000,
  VT_ARRAY				=   0x2000,
  VT_BYREF				=   0x4000,
  VT_RESERVED				=   0x8000,
  VT_ILLEGAL				=   0xFFFF,
  VT_ILLEGALMASKED			=   0x0FFF,
  VT_TYPEMASK				=   0x0FFF
};

typedef
struct _BYTE_SIZEDARR
{ unsigned long 		 clSize;
  byte				*pData;
} BYTE_SIZEDARR;

typedef
struct _SHORT_SIZEDARR
{ unsigned long 		 clSize;
  unsigned short		*pData;
} WORD_SIZEDARR;

typedef
struct _LONG_SIZEDARR
{ unsigned long 		 clSize;
  unsigned long 		*pData;
} DWORD_SIZEDARR;

typedef
struct _HYPER_SIZEDARR
{ unsigned long 		 clSize;
  hyper 			*pData;
} HYPER_SIZEDARR;

typedef double  DOUBLE;

typedef
struct tagDEC
{ USHORT			 wReserved;
  _ANONYMOUS_UNION union
  { _ANONYMOUS_STRUCT struct
    { BYTE			     scale;
      BYTE			     sign;
    }				  _STRUCT_NAME(s);
    USHORT			   signscale;
  }				 DUMMYUNIONNAME;
  ULONG 			 Hi32;
  _ANONYMOUS_UNION union
  { _ANONYMOUS_STRUCT struct
    { ULONG			     Lo32;
      ULONG			     Mid32;
    }				  _STRUCT_NAME(s2);
    ULONGLONG			   Lo64;
  }				 DUMMYUNIONNAME2;
} DECIMAL, *LPDECIMAL;

#define DECIMAL_NEG ((BYTE)(0x80))

#ifdef NONAMELESSUNION
#define DECIMAL_SETZERO(d)						     \
  { (d).DUMMYUNIONNAME2.Lo64 = (d).Hi32 = (d).DUMMYUNIONNAME.signscale = 0;  \
  }

#else
#define DECIMAL_SETZERO(d)  { (d).Lo64 = (d).Hi32 = (d).signscale = 0; }
#endif

typedef void  *HMETAFILEPICT;

_END_C_DECLS

#endif	/* _WTYPES_H full content definitions */
#endif	/* _WTYPES_H: $RCSfile: wtypes.h,v $: end of file */

/*
 * nspapi.h
 *
 * Windows Sockets Namespace Service Provider API definitions.
 *
 *
 * $Id: nspapi.h,v 7258c92e2a48 2017/11/14 20:07:02 keith $
 *
 * Written by Anders Norlander <anorland@hem2.passagen.se>
 * Copyright (C) 1998, 1999, 2002, 2004, 2017, MinGW.org Project
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
#ifndef _NSPAPI_H
#pragma GCC system_header

/* <winsock2.h> will include <nspapi.i> selectively, to resolve circular
 * definition references; thus...
 */
#ifndef __WINSOCK2_H_SOURCED__
/* ...only when NOT engaged in such selective inclusion, do we process
 * the entire content of <nspapi.h>; furthermore, before we DO process
 * the full content, we must process the WinSock API declarations from
 * <winsock.h> or <winsock2.h>, BEFORE we define the <nspapi.h> repeat
 * inclusion guard, so that <winsock2.h> may, if necessary, recurse to
 * access the selectively exposed content.  Inclusion of the following
 * private header will declare the necessary WinSock API, choosing to
 * include either <winsock.h> or <winsock2.h> by default, on the same
 * basis as the similar choice made in <windows.h>
 */
#include "_winsock.h"

/* We can now be confident that the WinSock API has been appropriately
 * declared; we may now define the <nspapi.h> repeat inclusion guard.
 */
#define _NSPAPI_H

#define NS_ALL					 0

#define NS_SAP					 1
#define NS_NDS					 2
#define NS_PEER_BROWSE				 3

#define NS_TCPIP_LOCAL				10
#define NS_TCPIP_HOSTS				11
#define NS_DNS					12
#define NS_NETBT				13
#define NS_WINS 				14

#define NS_NBP					20

#define NS_MS					30
#define NS_STDA 				31
#define NS_NTDS 				32

#define NS_X500 				40
#define NS_NIS					41
#define NS_NISPLUS				42

#define NS_WRQ					50

#define SERVICE_REGISTER			 1
#define SERVICE_DEREGISTER			 2
#define SERVICE_FLUSH				 3
#define SERVICE_FLAG_HARD		0x00000002

#endif	/* !__WINSOCK2_H_SOURCED__ */

#ifndef RC_INVOKED
#if ! (defined _NSPAPI_H && defined _WINSOCK2_H)
/* The following definitions are exposed either when <nspapi.h> is included
 * directly, or when selectively included by <winsock2.h>, but we must take
 * care to define them only on the first time of reading.
 *
 * We need a complete definition for the BLOB data type, which is provided
 * in "wtypes.h", (and possibly exposed due to prior selective inclusion by
 * <winsock2.h>); if neither of these have been included previously, we may
 * acquire the requisite definition by selective inclusion now.
 */
#define __NSPAPI_H_SOURCED__  1
#include "wtypes.h"

_BEGIN_C_DECLS

/* Technically, according to MSDN, the SOCKET_ADDRESS structure should be
 * defined in <winsock2.h>, which has not necessarily been included by the
 * time we get to here, yet the CSADDR_INFO structure, (which is correctly
 * defined in this file), requires its full definition.  Furthermore, the
 * CSADDR_INFO structure is representative of the data which is returned
 * by the GetAddressByName() function, (also declared in this file), which
 * is declared as deprecated in WinSock v2, (and thus, we would not expect
 * any such dependency on this WinSock v2 specific <winsock2.h> data type).
 * This Microsoft API design is critically flawed, but we can mitigate the
 * fault by defining the SOCKET_ADDRESS structure here, whence we make it
 * available to <winsock2.h> via selective inclusion.
 */
typedef
struct _SOCKET_ADDRESS
{ LPSOCKADDR		 lpSockaddr;
  INT			 iSockaddrLength;
} SOCKET_ADDRESS, *PSOCKET_ADDRESS, *LPSOCKET_ADDRESS;

/* Notwithstanding that, according to MSDN,  the CSADDR_INFO structure is
 * correctly defined below, (it should not be defined in <winsock2.h>, and
 * user code should include <nspapi.h> to obtain the complete definition),
 * <winsock2.h> DOES define the WSAQUERYSET data type, which requires at
 * least an incomplete type definition for the LPCSADDR_INFO pointer type;
 * thus, it is convenient to expose this incomplete definition when this
 * file, <nspapi.h>, is selectively included by <winsock2.h>, whereas the
 * complete definition of the CSADDR_INFO data type may be deferred until
 * the user includes <nspapi.h> directly.
 */
typedef struct _CSADDR_INFO  CSADDR_INFO, *PCSADDR_INFO, *LPCSADDR_INFO;

_END_C_DECLS

#undef __NSPAPI_H_SOURCED__
#endif	/* ! (_NSPAPI_H && _WINSOCK2_H) */

#ifdef _NSPAPI_H
/* This indicates that <nspapi.h> has been included directly...
 */
_BEGIN_C_DECLS

/* ...thus it is now appropriate to provide the complete type definition
 * for the CSADDR_INFO structure...
 */
struct _CSADDR_INFO
{ SOCKET_ADDRESS	 LocalAddr;
  SOCKET_ADDRESS	 RemoteAddr;
  INT			 iSocketType;
  INT			 iProtocol;
};

/* ...in addition to other data types, and function prototypes, which are
 * specific to this header file.
 */
typedef
struct _SERVICE_ADDRESS
{ DWORD 		 dwAddressType;
  DWORD 		 dwAddressFlags;
  DWORD 		 dwAddressLength;
  DWORD 		 dwPrincipalLength;
  BYTE			*lpAddress;
  BYTE			*lpPrincipal;
} SERVICE_ADDRESS;

typedef
struct _SERVICE_ADDRESSES
{ DWORD 		 dwAddressCount;
  SERVICE_ADDRESS	 Addresses[1];
} SERVICE_ADDRESSES, *PSERVICE_ADDRESSES, *LPSERVICE_ADDRESSES;

typedef
struct _SERVICE_INFOA
{ LPGUID		 lpServiceType;
  LPSTR 		 lpServiceName;
  LPSTR 		 lpComment;
  LPSTR 		 lpLocale;
  DWORD 		 dwDisplayHint;
  DWORD 		 dwVersion;
  DWORD 		 dwTime;
  LPSTR 		 lpMachineName;
  LPSERVICE_ADDRESSES	 lpServiceAddress;
  BLOB			 ServiceSpecificInfo;
} SERVICE_INFOA, *LPSERVICE_INFOA;

typedef
struct _SERVICE_INFOW
{ LPGUID		 lpServiceType;
  LPWSTR		 lpServiceName;
  LPWSTR		 lpComment;
  LPWSTR		 lpLocale;
  DWORD 		 dwDisplayHint;
  DWORD 		 dwVersion;
  DWORD 		 dwTime;
  LPWSTR		 lpMachineName;
  LPSERVICE_ADDRESSES	 lpServiceAddress;
  BLOB			 ServiceSpecificInfo;
} SERVICE_INFOW, *LPSERVICE_INFOW;

typedef __AW_ALIAS__(SERVICE_INFO), *LPSERVICE_INFO;
typedef void *LPSERVICE_ASYNC_INFO;

#define SetService __AW_SUFFIXED__(SetService)
INT WINAPI SetServiceA
  ( DWORD, DWORD, DWORD, LPSERVICE_INFOA, LPSERVICE_ASYNC_INFO, LPDWORD
  );
INT WINAPI SetServiceW
  ( DWORD, DWORD, DWORD, LPSERVICE_INFOW, LPSERVICE_ASYNC_INFO, LPDWORD
  );

#define GetAddressByName __AW_SUFFIXED__(GetAddressByName)
INT WINAPI GetAddressByNameA
  ( DWORD, LPGUID, LPSTR, LPINT, DWORD, LPSERVICE_ASYNC_INFO, LPVOID,
    LPDWORD, LPSTR, LPDWORD
  );
INT WINAPI GetAddressByNameW
  ( DWORD, LPGUID, LPWSTR, LPINT, DWORD, LPSERVICE_ASYNC_INFO, LPVOID,
    LPDWORD, LPWSTR, LPDWORD
  );

#define _SERVICE_INFO __AW_SUFFIXED__(SERVICE_INFO)

_END_C_DECLS

#endif	/* _NSPAPI_H */
#endif	/* ! RC_INVOKED */

#endif	/* _NSPAPI_H: $RCSfile: nspapi.h,v $: end of file */

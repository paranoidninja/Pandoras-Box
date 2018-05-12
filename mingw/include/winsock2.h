/*
 * winsock2.h
 *
 * Definitions for WinSock Version 2 API; provides the additional definitions
 * which are required by WinSock v2, to augment those which are already defined
 * in <winsock.h>, and are common to WinSock Versions 1.1 and 2.
 *
 *
 * $Id: winsock2.h,v a346ddcc5d76 2017/11/28 13:28:34 keith $
 *
 * Contributed by the WINE Project.
 * Adaptation by Mumit Khan <khan@xraylith.wisc.edu>
 * Copyright (C) 1998-2005, 2011, 2016, 2017, MinGW.org Project
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
 * Portions Copyright (C) 1980, 1983, 1988, 1993
 * The Regents of the University of California.  All rights reserved.
 *
 * Portions Copyright (C) 1993 by Digital Equipment Corporation.
 *
 */
#ifndef _WINSOCK2_H
#pragma GCC system_header
#define _WINSOCK2_H

#ifdef _WINSOCK_H  /* included prematurely */
/* Oops!  <winsock.h> appears to have been included already, which now
 * precludes any use of WinSock v2 protocol.
 */
#error "Including <winsock2.h> after <winsock.h> is unsupported."
#warning "Falling back to WinSock v1.1 protocol."

#else	/* !_WINSOCK_H included prematurely */
/* This is correct WinSock v2 protocol usage: <winsock.h> has not been
 * included previously, so we include it now, to establish definitions
 * which are common to both WinSock v1 and WinSock v2 protocols.  This
 * is filtered, on our prior definition of _WINSOCK2_H, to exclude any
 * obsolete or conflicting definitions from WinSock v1, which are no
 * longer applicable in WinSock v2, and on __WINSOCK2_DEPRECATED to
 * identify any which remain available, but have been deprecated.
 */
#define __WINSOCK2_DEPRECATED  __MINGW_ATTRIB_DEPRECATED
#include "winsock.h"

#define __WINSOCK2_H_SOURCED__

/* We need a definition for the BLOB data type; although an incomplete
 * type definition would suffice here, other related headers, <nspapi.h>
 * in particular, require the full definition, so we may just as well
 * incorporate that here, by selective inclusion from "wtypes.h", by
 * way of indirect inclusion from "nspapi.h"
 */
#include "nspapi.h"

_BEGIN_C_DECLS

#define ADDR_ANY			  INADDR_ANY

#define IN_CLASSD(i)	    (((long)(i) & 0xF0000000) == 0xE0000000)
#define IN_CLASSD_NET			  0xF0000000
#define IN_CLASSD_NSHIFT			  28
#define IN_CLASSD_HOST			  0x0FFFFFFF
#define IN_MULTICAST(i) 		 IN_CLASSD(i)

#define FROM_PROTOCOL_INFO			 (-1)

#define SO_GROUP_ID			      0x2001
#define SO_GROUP_PRIORITY		      0x2002
#define SO_MAX_MSG_SIZE 		      0x2003

#define SO_PROTOCOL_INFO	__AW_SUFFIXED__(SO_PROTOCOL_INFO)
#define SO_PROTOCOL_INFOA		      0x2004
#define SO_PROTOCOL_INFOW		      0x2005

#define PVD_CONFIG			      0x3001

#define MSG_INTERRUPT				0x10

#define WSAAPI				      WINAPI
#define WSAEVENT			      HANDLE
#define LPWSAEVENT			    LPHANDLE
#define WSAOVERLAPPED			  OVERLAPPED

typedef	struct _OVERLAPPED  *LPWSAOVERLAPPED;

#define WSA_IO_PENDING			(ERROR_IO_PENDING)
#define WSA_IO_INCOMPLETE		(ERROR_IO_INCOMPLETE)
#define WSA_INVALID_HANDLE		(ERROR_INVALID_HANDLE)
#define WSA_INVALID_PARAMETER		(ERROR_INVALID_PARAMETER)
#define WSA_NOT_ENOUGH_MEMORY		(ERROR_NOT_ENOUGH_MEMORY)
#define WSA_OPERATION_ABORTED		(ERROR_OPERATION_ABORTED)

#define WSA_INVALID_EVENT		((WSAEVENT)NULL)
#define WSA_MAXIMUM_WAIT_EVENTS 	(MAXIMUM_WAIT_OBJECTS)
#define WSA_WAIT_FAILED 		((DWORD)-1L)
#define WSA_WAIT_EVENT_0		(WAIT_OBJECT_0)
#define WSA_WAIT_IO_COMPLETION		(WAIT_IO_COMPLETION)
#define WSA_WAIT_TIMEOUT		(WAIT_TIMEOUT)
#define WSA_INFINITE			(INFINITE)

typedef
struct _WSABUF
{ unsigned long 	 len;
  char			*buf;
} WSABUF, *LPWSABUF;

typedef enum
{ BestEffortService,
  ControlledLoadService,
  PredictiveService,
  GuaranteedDelayService,
  GuaranteedService
} GUARANTEE;

/* IPv6 protocol options: these are additional to protocol option constants
 * already defined in <winsock.h>; they are unsupported prior to WinSock v2.
 */
#define IPPROTO_HOPOPTS 			   0  /* IPv6 Hop-by-Hop options */
#define IPPROTO_IPV6				  41  /* IPv6 header */
#define IPPROTO_ROUTING 			  43  /* IPv6 Routing header */
#define IPPROTO_FRAGMENT			  44  /* IPv6 fragmentation header */
#define IPPROTO_ESP				  50  /* encapsulating security payload */
#define IPPROTO_AH				  51  /* authentication header */
#define IPPROTO_ICMPV6				  58  /* ICMPv6 */
#define IPPROTO_NONE				  59  /* IPv6 no next header */
#define IPPROTO_DSTOPTS 			  60  /* IPv6 Destination options */

/* Address family definitions: these extend the set which has been defined
 * already, in <winsock.h>; they are applicable only for WinSock v2.
 */
#define AF_CLUSTER				  24
#define AF_12844				  25
#define AF_IRDA 				  26
#define AF_NETDES				  28

#ifndef __INSIDE_MSYS__
/* MSYS provides its own definition for AF_MAX; otherwise, <winsock.h> has
 * already defined it as 24, but we need to override that to accommodate the
 * additional constants, defined above.
 */
#undef  AF_MAX
#define AF_MAX					  29

/* Portable IPv6/IPv4 version of sockaddr, based on RFC 2553.
 * The sockaddr_storage structure is padded to force 8 byte alignment of
 * its member fields, and its size is fixed at 128 bytes.
 *
 * Desired design maximum size and alignment.
 */
#define _SS_MAXSIZE				 128
#define _SS_ALIGNSIZE			sizeof(__int64)

/* Definitions used for sockaddr_storage structure padding.
 */
#define _SS_PAD1SIZE   (_SS_ALIGNSIZE - sizeof(short))
#define _SS_PAD2SIZE   (_SS_MAXSIZE - (sizeof(short) + _SS_PAD1SIZE + _SS_ALIGNSIZE))

struct sockaddr_storage
{ short 		ss_family;
  char		      __ss_pad1[_SS_PAD1SIZE];	/* pad to 8 */
  __int64	      __ss_align;		/* force alignment */
  char		      __ss_pad2[_SS_PAD2SIZE];	/* pad to 128 */
};

/* As in the case of AF_MAX, MSYS provides its own value for SOMAXCONN;
 * otherwise, <winsock.h> has already defined it, with a value of 5; this
 * was correct for WinSock v1.1, but we must now override it with this
 * alternative definition, to make it correct for WinSock v2.
 */
#undef  SOMAXCONN
#define SOMAXCONN			  0x7FFFFFFF

/* SO_EXCLUSIVEADDRUSE is not applicable, prior to WinSock v2; it is
 * derived from SO_REUSEADDR, which has been defined in <winsock.h>
 */
#define SO_EXCLUSIVEADDRUSE		((u_int)(~SO_REUSEADDR))
#endif  /* !__INSIDE_MSYS__ */

/* FIXME: FLOWSPEC and related definitions belong in qos.h */

/* Windows Sockets 2 Application Programming Interface,
 * revision 2.2.2 (1997) uses the type uint32 for SERVICETYPE
 * and the elements of _flowspec, but the type uint32 is not defined
 * or used anywhere else in the w32api. For now, just use
 * unsigned int, which is 32 bits on _WIN32 and _WIN64.
 */
typedef unsigned int  SERVICETYPE;

typedef
struct _flowspec
{ unsigned int		 TokenRate;
  unsigned int		 TokenBucketSize;
  unsigned int		 PeakBandwidth;
  unsigned int		 Latency;
  unsigned int		 DelayVariation;
  SERVICETYPE		 ServiceType;
  unsigned int		 MaxSduSize;
  unsigned int		 MinimumPolicedSize;
} FLOWSPEC, *PFLOWSPEC, *LPFLOWSPEC;

typedef
struct _QualityOfService
{ FLOWSPEC		 SendingFlowspec;
  FLOWSPEC		 ReceivingFlowspec;
  WSABUF		 ProviderSpecific;
} QOS, *LPQOS;

#define CF_ACCEPT			      0x0000
#define CF_REJECT			      0x0001
#define CF_DEFER			      0x0002

typedef unsigned int  GROUP;

#define SG_UNCONSTRAINED_GROUP			0x01
#define SG_CONSTRAINED_GROUP			0x02

typedef
struct _WSANETWORKEVENTS
{ long			 lNetworkEvents;
  int			 iErrorCode[FD_MAX_EVENTS];
} WSANETWORKEVENTS, *LPWSANETWORKEVENTS;

#define MAX_PROTOCOL_CHAIN			   7

#define BASE_PROTOCOL				   1
#define LAYERED_PROTOCOL			   0

typedef
enum _WSAESETSERVICEOP
{ RNRSERVICE_REGISTER				=  0,
  RNRSERVICE_DEREGISTER,
  RNRSERVICE_DELETE
} WSAESETSERVICEOP, *PWSAESETSERVICEOP, *LPWSAESETSERVICEOP;

typedef
struct _AFPROTOCOLS
{ INT			 iAddressFamily;
  INT			 iProtocol;
} AFPROTOCOLS, *PAFPROTOCOLS, *LPAFPROTOCOLS;

typedef
enum _WSAEcomparator
{ COMP_EQUAL					=  0,
  COMP_NOTLESS
} WSAECOMPARATOR, *PWSAECOMPARATOR, *LPWSAECOMPARATOR;

typedef
struct _WSAVersion
{ DWORD 		 dwVersion;
  WSAECOMPARATOR	 ecHow;
} WSAVERSION, *PWSAVERSION, *LPWSAVERSION;

typedef
struct _SOCKET_ADDRESS_LIST
{ INT			 iAddressCount;
  SOCKET_ADDRESS	 Address[1];
} SOCKET_ADDRESS_LIST, *LPSOCKET_ADDRESS_LIST;

typedef
struct _WSAQuerySetA
{ DWORD 		 dwSize;
  LPSTR 		 lpszServiceInstanceName;
  LPGUID		 lpServiceClassId;
  LPWSAVERSION		 lpVersion;
  LPSTR 		 lpszComment;
  DWORD 		 dwNameSpace;
  LPGUID		 lpNSProviderId;
  LPSTR 		 lpszContext;
  DWORD 		 dwNumberOfProtocols;
  LPAFPROTOCOLS 	 lpafpProtocols;
  LPSTR 		 lpszQueryString;
  DWORD 		 dwNumberOfCsAddrs;
  LPCSADDR_INFO 	 lpcsaBuffer;
  DWORD 		 dwOutputFlags;
  LPBLOB		 lpBlob;
} WSAQUERYSETA, *PWSAQUERYSETA, *LPWSAQUERYSETA;

typedef
struct _WSAQuerySetW
{ DWORD 		 dwSize;
  LPWSTR		 lpszServiceInstanceName;
  LPGUID		 lpServiceClassId;
  LPWSAVERSION		 lpVersion;
  LPWSTR		 lpszComment;
  DWORD 		 dwNameSpace;
  LPGUID		 lpNSProviderId;
  LPWSTR		 lpszContext;
  DWORD 		 dwNumberOfProtocols;
  LPAFPROTOCOLS 	 lpafpProtocols;
  LPWSTR		 lpszQueryString;
  DWORD 		 dwNumberOfCsAddrs;
  LPCSADDR_INFO 	 lpcsaBuffer;
  DWORD 		 dwOutputFlags;
  LPBLOB		 lpBlob;
} WSAQUERYSETW, *PWSAQUERYSETW, *LPWSAQUERYSETW;

typedef __AW_ALIAS__( WSAQUERYSET );
typedef __AW_ALIAS__( PWSAQUERYSET );
typedef __AW_ALIAS__( LPWSAQUERYSET );

#define LUP_DEEP			      0x0001
#define LUP_CONTAINERS			      0x0002
#define LUP_NOCONTAINERS		      0x0004
#define LUP_NEAREST			      0x0008
#define LUP_RETURN_NAME 		      0x0010
#define LUP_RETURN_TYPE 		      0x0020
#define LUP_RETURN_VERSION		      0x0040
#define LUP_RETURN_COMMENT		      0x0080
#define LUP_RETURN_ADDR 		      0x0100
#define LUP_RETURN_BLOB 		      0x0200
#define LUP_RETURN_ALIASES		      0x0400
#define LUP_RETURN_QUERY_STRING 	      0x0800
#define LUP_RETURN_ALL			      0x0FF0
#define LUP_RES_SERVICE 		      0x8000
#define LUP_FLUSHCACHE			      0x1000
#define LUP_FLUSHPREVIOUS		      0x2000

typedef
struct _WSANSClassInfoA
{ LPSTR 		 lpszName;
  DWORD 		 dwNameSpace;
  DWORD 		 dwValueType;
  DWORD 		 dwValueSize;
  LPVOID		 lpValue;
} WSANSCLASSINFOA, *PWSANSCLASSINFOA, *LPWSANSCLASSINFOA;

typedef
struct _WSANSClassInfoW
{ LPWSTR		 lpszName;
  DWORD 		 dwNameSpace;
  DWORD 		 dwValueType;
  DWORD 		 dwValueSize;
  LPVOID		 lpValue;
} WSANSCLASSINFOW, *PWSANSCLASSINFOW, *LPWSANSCLASSINFOW;

typedef __AW_ALIAS__( WSANSCLASSINFO );
typedef __AW_ALIAS__( PWSANSCLASSINFO );
typedef __AW_ALIAS__( LPWSANSCLASSINFO );

typedef
struct _WSAServiceClassInfoA
{ LPGUID		 lpServiceClassId;
  LPSTR 		 lpszServiceClassName;
  DWORD 		 dwCount;
  LPWSANSCLASSINFOA	 lpClassInfos;
} WSASERVICECLASSINFOA, *PWSASERVICECLASSINFOA, *LPWSASERVICECLASSINFOA;

typedef
struct _WSAServiceClassInfoW
{ LPGUID		 lpServiceClassId;
  LPWSTR		 lpszServiceClassName;
  DWORD 		 dwCount;
  LPWSANSCLASSINFOW	 lpClassInfos;
} WSASERVICECLASSINFOW, *PWSASERVICECLASSINFOW, *LPWSASERVICECLASSINFOW;

typedef __AW_ALIAS__( WSASERVICECLASSINFO );
typedef __AW_ALIAS__( PWSASERVICECLASSINFO );
typedef __AW_ALIAS__( LPWSASERVICECLASSINFO );

typedef
struct _WSANAMESPACE_INFOA
{ GUID			 NSProviderId;
  DWORD 		 dwNameSpace;
  BOOL			 fActive;
  DWORD 		 dwVersion;
  LPSTR 		 lpszIdentifier;
} WSANAMESPACE_INFOA, *PWSANAMESPACE_INFOA, *LPWSANAMESPACE_INFOA;

typedef
struct _WSANAMESPACE_INFOW
{ GUID			 NSProviderId;
  DWORD 		 dwNameSpace;
  BOOL			 fActive;
  DWORD 		 dwVersion;
  LPWSTR		 lpszIdentifier;
} WSANAMESPACE_INFOW, *PWSANAMESPACE_INFOW, *LPWSANAMESPACE_INFOW;

typedef __AW_ALIAS__( WSANAMESPACE_INFO );
typedef __AW_ALIAS__( PWSANAMESPACE_INFO );
typedef __AW_ALIAS__( LPWSANAMESPACE_INFO );

typedef
struct _WSAPROTOCOLCHAIN
{ int			 ChainLen;
  DWORD 		 ChainEntries[MAX_PROTOCOL_CHAIN];
} WSAPROTOCOLCHAIN, *LPWSAPROTOCOLCHAIN;

#define WSAPROTOCOL_LEN 			 255

typedef
struct _WSAPROTOCOL_INFOA
{ DWORD 		 dwServiceFlags1;
  DWORD 		 dwServiceFlags2;
  DWORD 		 dwServiceFlags3;
  DWORD 		 dwServiceFlags4;
  DWORD 		 dwProviderFlags;
  GUID			 ProviderId;
  DWORD 		 dwCatalogEntryId;
  WSAPROTOCOLCHAIN	 ProtocolChain;
  int			 iVersion;
  int			 iAddressFamily;
  int			 iMaxSockAddr;
  int			 iMinSockAddr;
  int			 iSocketType;
  int			 iProtocol;
  int			 iProtocolMaxOffset;
  int			 iNetworkByteOrder;
  int			 iSecurityScheme;
  DWORD 		 dwMessageSize;
  DWORD 		 dwProviderReserved;
  CHAR			 szProtocol[WSAPROTOCOL_LEN+1];
} WSAPROTOCOL_INFOA, *LPWSAPROTOCOL_INFOA;

typedef
struct _WSAPROTOCOL_INFOW
{ DWORD 		 dwServiceFlags1;
  DWORD 		 dwServiceFlags2;
  DWORD 		 dwServiceFlags3;
  DWORD 		 dwServiceFlags4;
  DWORD 		 dwProviderFlags;
  GUID			 ProviderId;
  DWORD 		 dwCatalogEntryId;
  WSAPROTOCOLCHAIN	 ProtocolChain;
  int			 iVersion;
  int			 iAddressFamily;
  int			 iMaxSockAddr;
  int			 iMinSockAddr;
  int			 iSocketType;
  int			 iProtocol;
  int			 iProtocolMaxOffset;
  int			 iNetworkByteOrder;
  int			 iSecurityScheme;
  DWORD 		 dwMessageSize;
  DWORD 		 dwProviderReserved;
  WCHAR 		 szProtocol[WSAPROTOCOL_LEN+1];
} WSAPROTOCOL_INFOW, *LPWSAPROTOCOL_INFOW;

typedef __AW_ALIAS__( WSAPROTOCOL_INFO );
typedef __AW_ALIAS__( LPWSAPROTOCOL_INFO );

typedef int (CALLBACK *LPCONDITIONPROC) (LPWSABUF, LPWSABUF, LPQOS, LPQOS, LPWSABUF, LPWSABUF, GROUP *, DWORD);
typedef void (WINAPI *LPWSAOVERLAPPED_COMPLETION_ROUTINE) (DWORD, DWORD, LPWSAOVERLAPPED, DWORD);

/* Needed for XP & .NET Server function WSANSPIoctl. */

typedef
enum _WSACOMPLETIONTYPE
{ NSP_NOTIFY_IMMEDIATELY			=  0,
  NSP_NOTIFY_HWND,
  NSP_NOTIFY_EVENT,
  NSP_NOTIFY_PORT,
  NSP_NOTIFY_APC
} WSACOMPLETIONTYPE, *PWSACOMPLETIONTYPE, *LPWSACOMPLETIONTYPE;

typedef
struct _WSACOMPLETION
{ WSACOMPLETIONTYPE				 Type;
  union
  { struct
    { HWND					     hWnd;
      UINT					     uMsg;
      WPARAM					     context;
    }						   WindowMessage;
    struct
    { LPWSAOVERLAPPED				     lpOverlapped;
    }						   Event;
    struct
    { LPWSAOVERLAPPED				     lpOverlapped;
      LPWSAOVERLAPPED_COMPLETION_ROUTINE	     lpfnCompletionProc;
    }						   Apc;
    struct
    { LPWSAOVERLAPPED				     lpOverlapped;
      HANDLE					     hPort;
      ULONG_PTR 				     Key;
    }						   Port;
  }						 Parameters;
} WSACOMPLETION, *PWSACOMPLETION, *LPWSACOMPLETION;

#define PFL_MULTIPLE_PROTO_ENTRIES		  0x00000001
#define PFL_RECOMMENDED_PROTO_ENTRY		  0x00000002
#define PFL_HIDDEN				  0x00000004
#define PFL_MATCHES_PROTOCOL_ZERO		  0x00000008
#define XP1_CONNECTIONLESS			  0x00000001
#define XP1_GUARANTEED_DELIVERY 		  0x00000002
#define XP1_GUARANTEED_ORDER			  0x00000004
#define XP1_MESSAGE_ORIENTED			  0x00000008
#define XP1_PSEUDO_STREAM			  0x00000010
#define XP1_GRACEFUL_CLOSE			  0x00000020
#define XP1_EXPEDITED_DATA			  0x00000040
#define XP1_CONNECT_DATA			  0x00000080
#define XP1_DISCONNECT_DATA			  0x00000100
#define XP1_SUPPORT_BROADCAST			  0x00000200
#define XP1_SUPPORT_MULTIPOINT			  0x00000400
#define XP1_MULTIPOINT_CONTROL_PLANE		  0x00000800
#define XP1_MULTIPOINT_DATA_PLANE		  0x00001000
#define XP1_QOS_SUPPORTED			  0x00002000
#define XP1_INTERRUPT				  0x00004000
#define XP1_UNI_SEND				  0x00008000
#define XP1_UNI_RECV				  0x00010000
#define XP1_IFS_HANDLES 			  0x00020000
#define XP1_PARTIAL_MESSAGE			  0x00040000

#define BIGENDIAN				      0x0000
#define LITTLEENDIAN				      0x0001

#define SECURITY_PROTOCOL_NONE			      0x0000
#define JL_SENDER_ONLY					0x01
#define JL_RECEIVER_ONLY				0x02
#define JL_BOTH 					0x04
#define WSA_FLAG_OVERLAPPED				0x01
#define WSA_FLAG_MULTIPOINT_C_ROOT			0x02
#define WSA_FLAG_MULTIPOINT_C_LEAF			0x04
#define WSA_FLAG_MULTIPOINT_D_ROOT			0x08
#define WSA_FLAG_MULTIPOINT_D_LEAF			0x10
#define IOC_UNIX				  0x00000000
#define IOC_WS2 				  0x08000000
#define IOC_PROTOCOL				  0x10000000
#define IOC_VENDOR				  0x18000000

#define _WSAIO(x,y)				(IOC_VOID|(x)|(y))
#define _WSAIOR(x,y)				(IOC_OUT|(x)|(y))
#define _WSAIOW(x,y)				(IOC_IN|(x)|(y))
#define _WSAIORW(x,y)				(IOC_INOUT|(x)|(y))

#define SIO_ASSOCIATE_HANDLE			_WSAIOW(IOC_WS2,1)
#define SIO_ENABLE_CIRCULAR_QUEUEING		_WSAIO(IOC_WS2,2)
#define SIO_FIND_ROUTE				_WSAIOR(IOC_WS2,3)
#define SIO_FLUSH				_WSAIO(IOC_WS2,4)
#define SIO_GET_BROADCAST_ADDRESS		_WSAIOR(IOC_WS2,5)
#define SIO_GET_EXTENSION_FUNCTION_POINTER	_WSAIORW(IOC_WS2,6)
#define SIO_GET_QOS				_WSAIORW(IOC_WS2,7)
#define SIO_GET_GROUP_QOS			_WSAIORW(IOC_WS2,8)
#define SIO_MULTIPOINT_LOOPBACK 		_WSAIOW(IOC_WS2,9)
#define SIO_MULTICAST_SCOPE			_WSAIOW(IOC_WS2,10)
#define SIO_SET_QOS				_WSAIOW(IOC_WS2,11)
#define SIO_SET_GROUP_QOS			_WSAIOW(IOC_WS2,12)
#define SIO_TRANSLATE_HANDLE			_WSAIORW(IOC_WS2,13)
#define SIO_ROUTING_INTERFACE_QUERY		_WSAIORW(IOC_WS2,20)
#define SIO_ROUTING_INTERFACE_CHANGE		_WSAIOW(IOC_WS2,21)
#define SIO_ADDRESS_LIST_QUERY			_WSAIOR(IOC_WS2,22)
#define SIO_ADDRESS_LIST_CHANGE 		_WSAIO(IOC_WS2,23)
#define SIO_QUERY_TARGET_PNP_HANDLE		_WSAIOR(IOC_WS2,24)
#define SIO_NSP_NOTIFY_CHANGE			_WSAIOW(IOC_WS2,25)
#define SIO_UDP_CONNRESET			_WSAIOW(IOC_VENDOR,12)

#define TH_NETDEV				  0x00000001
#define TH_TAPI 				  0x00000002

typedef SOCKET (PASCAL *LPFN_ACCEPT) (SOCKET, struct sockaddr *, int *);

typedef int (PASCAL *LPFN_BIND) (SOCKET, const struct sockaddr *, int);
typedef int (PASCAL *LPFN_CLOSESOCKET) (SOCKET);
typedef int (PASCAL *LPFN_CONNECT) (SOCKET, const struct sockaddr *, int);
typedef int (PASCAL *LPFN_IOCTLSOCKET) (SOCKET, long, u_long *);
typedef int (PASCAL *LPFN_GETPEERNAME) (SOCKET, struct sockaddr *, int *);
typedef int (PASCAL *LPFN_GETSOCKNAME) (SOCKET, struct sockaddr *, int *);
typedef int (PASCAL *LPFN_GETSOCKOPT) (SOCKET, int, int, char *, int *);

typedef u_long (PASCAL *LPFN_HTONL) (u_long);
typedef u_short (PASCAL *LPFN_HTONS) (u_short);

typedef unsigned long (PASCAL *LPFN_INET_ADDR) (const char *);

typedef char *(PASCAL *LPFN_INET_NTOA) (struct in_addr);

typedef int (PASCAL *LPFN_LISTEN) (SOCKET, int);

typedef u_long (PASCAL *LPFN_NTOHL) (u_long);
typedef u_short (PASCAL *LPFN_NTOHS) (u_short);

typedef int (PASCAL *LPFN_RECV) (SOCKET, char *, int, int);
typedef int (PASCAL *LPFN_RECVFROM) (SOCKET, char *, int, int, struct sockaddr *, int *);
typedef int (PASCAL *LPFN_SELECT) (int, fd_set *, fd_set *, fd_set *, const struct timeval *);
typedef int (PASCAL *LPFN_SEND) (SOCKET, const char *, int, int);
typedef int (PASCAL *LPFN_SENDTO) (SOCKET, const char *, int, int, const struct sockaddr *, int);
typedef int (PASCAL *LPFN_SETSOCKOPT) (SOCKET, int, int, const char *, int);
typedef int (PASCAL *LPFN_SHUTDOWN) (SOCKET, int);

typedef SOCKET (PASCAL *LPFN_SOCKET) (int, int, int);

typedef struct hostent *(PASCAL *LPFN_GETHOSTBYADDR) ( const char *, int, int);
typedef struct hostent *(PASCAL *LPFN_GETHOSTBYNAME) ( const char *);

typedef int (PASCAL *LPFN_GETHOSTNAME) (char *, int);

typedef struct servent *(PASCAL *LPFN_GETSERVBYPORT) (int, const char *);
typedef struct servent *(PASCAL *LPFN_GETSERVBYNAME) (const char *, const char *);
typedef struct protoent *(PASCAL *LPFN_GETPROTOBYNUMBER) (int);
typedef struct protoent *(PASCAL *LPFN_GETPROTOBYNAME) (const char *);

typedef int (PASCAL *LPFN_WSASTARTUP) (WORD, LPWSADATA);
typedef int (PASCAL *LPFN_WSACLEANUP) (void);
typedef int (PASCAL *LPFN_WSAGETLASTERROR) (void);
typedef void (PASCAL *LPFN_WSASETLASTERROR) (int);

typedef BOOL (PASCAL *LPFN_WSAISBLOCKING) (void);
typedef int (PASCAL *LPFN_WSAUNHOOKBLOCKINGHOOK) (void);
typedef FARPROC (PASCAL *LPFN_WSASETBLOCKINGHOOK) (FARPROC);
typedef int (PASCAL *LPFN_WSACANCELBLOCKINGCALL) (void);

typedef HANDLE (PASCAL *LPFN_WSAASYNCGETSERVBYNAME) (HWND, u_int, const char *, const char *, char *, int);
typedef HANDLE (PASCAL *LPFN_WSAASYNCGETSERVBYPORT) (HWND, u_int, int, const char *, char *, int);
typedef HANDLE (PASCAL *LPFN_WSAASYNCGETPROTOBYNAME) (HWND, u_int, const char*, char*, int);
typedef HANDLE (PASCAL *LPFN_WSAASYNCGETPROTOBYNUMBER) (HWND, u_int, int, char*, int);
typedef HANDLE (PASCAL *LPFN_WSAASYNCGETHOSTBYADDR) (HWND, u_int, const char*, int, int, char*, int);

typedef int (PASCAL *LPFN_WSACANCELASYNCREQUEST) (HANDLE);
typedef int (PASCAL *LPFN_WSAASYNCSELECT) (SOCKET, HWND, u_int, long);

typedef struct sockaddr_storage SOCKADDR_STORAGE, *PSOCKADDR_STORAGE;

WINSOCK_API_LINKAGE SOCKET WINAPI WSAAccept (SOCKET, struct sockaddr *, LPINT, LPCONDITIONPROC, DWORD);

#define WSAAddressToString __AW_SUFFIXED__(WSAAddressToString)
WINSOCK_API_LINKAGE INT WINAPI WSAAddressToStringA (LPSOCKADDR, DWORD, LPWSAPROTOCOL_INFOA, LPSTR, LPDWORD);
WINSOCK_API_LINKAGE INT WINAPI WSAAddressToStringW (LPSOCKADDR, DWORD, LPWSAPROTOCOL_INFOW, LPWSTR, LPDWORD);

WINSOCK_API_LINKAGE BOOL WINAPI WSACloseEvent (WSAEVENT);
WINSOCK_API_LINKAGE int WINAPI WSAConnect (SOCKET, const struct sockaddr *, int, LPWSABUF, LPWSABUF, LPQOS, LPQOS);
WINSOCK_API_LINKAGE WSAEVENT WINAPI WSACreateEvent (void);

#define WSADuplicateSocket __AW_SUFFIXED__(WSADuplicateSocket)
WINSOCK_API_LINKAGE int WINAPI WSADuplicateSocketA (SOCKET, DWORD, LPWSAPROTOCOL_INFOA);
WINSOCK_API_LINKAGE int WINAPI WSADuplicateSocketW (SOCKET, DWORD, LPWSAPROTOCOL_INFOW);

#define WSAEnumNameSpaceProviders __AW_SUFFIXED__(WSAEnumNameSpaceProviders)
WINSOCK_API_LINKAGE INT WINAPI WSAEnumNameSpaceProvidersA (LPDWORD, LPWSANAMESPACE_INFOA);
WINSOCK_API_LINKAGE INT WINAPI WSAEnumNameSpaceProvidersW (LPDWORD, LPWSANAMESPACE_INFOW);

WINSOCK_API_LINKAGE int WINAPI WSAEnumNetworkEvents (SOCKET, WSAEVENT, LPWSANETWORKEVENTS);

#define WSAEnumProtocols __AW_SUFFIXED__(WSAEnumProtocols)
WINSOCK_API_LINKAGE int WINAPI WSAEnumProtocolsA (LPINT, LPWSAPROTOCOL_INFOA, LPDWORD);
WINSOCK_API_LINKAGE int WINAPI WSAEnumProtocolsW (LPINT, LPWSAPROTOCOL_INFOW, LPDWORD);

WINSOCK_API_LINKAGE int WINAPI WSAEventSelect (SOCKET, WSAEVENT, long);
WINSOCK_API_LINKAGE BOOL WINAPI WSAGetOverlappedResult (SOCKET, LPWSAOVERLAPPED, LPDWORD, BOOL, LPDWORD);
WINSOCK_API_LINKAGE BOOL WINAPI WSAGetQOSByName (SOCKET, LPWSABUF, LPQOS);

#define WSAGetServiceClassInfo __AW_SUFFIXED__(WSAGetServiceClassInfo)
WINSOCK_API_LINKAGE INT WINAPI WSAGetServiceClassInfoA (LPGUID, LPGUID, LPDWORD, LPWSASERVICECLASSINFOA);
WINSOCK_API_LINKAGE INT WINAPI WSAGetServiceClassInfoW (LPGUID, LPGUID, LPDWORD, LPWSASERVICECLASSINFOW);

#define WSAGetServiceClassNameByClassId __AW_SUFFIXED__(WSAGetServiceClassNameByClassId)
WINSOCK_API_LINKAGE INT WINAPI WSAGetServiceClassNameByClassIdA (LPGUID, LPSTR, LPDWORD);
WINSOCK_API_LINKAGE INT WINAPI WSAGetServiceClassNameByClassIdW (LPGUID, LPWSTR, LPDWORD);

WINSOCK_API_LINKAGE int WINAPI WSAHtonl (SOCKET, unsigned long, unsigned long *);
WINSOCK_API_LINKAGE int WINAPI WSAHtons (SOCKET, unsigned short, unsigned short *);

#define WSAInstallServiceClass __AW_SUFFIXED__(WSAInstallServiceClass)
WINSOCK_API_LINKAGE INT WINAPI WSAInstallServiceClassA (LPWSASERVICECLASSINFOA);
WINSOCK_API_LINKAGE INT WINAPI WSAInstallServiceClassW (LPWSASERVICECLASSINFOW);

WINSOCK_API_LINKAGE int WINAPI WSAIoctl (SOCKET, DWORD, LPVOID, DWORD, LPVOID, DWORD, LPDWORD, LPWSAOVERLAPPED, LPWSAOVERLAPPED_COMPLETION_ROUTINE);
WINSOCK_API_LINKAGE SOCKET WINAPI WSAJoinLeaf (SOCKET, const struct sockaddr *, int, LPWSABUF, LPWSABUF, LPQOS, LPQOS, DWORD);

#define WSALookupServiceBegin __AW_SUFFIXED__(WSALookupServiceBegin)
WINSOCK_API_LINKAGE INT WINAPI WSALookupServiceBeginA (LPWSAQUERYSETA, DWORD, LPHANDLE);
WINSOCK_API_LINKAGE INT WINAPI WSALookupServiceBeginW (LPWSAQUERYSETW, DWORD, LPHANDLE);

#define WSALookupServiceNext __AW_SUFFIXED__(WSALookupServiceNext)
WINSOCK_API_LINKAGE INT WINAPI WSALookupServiceNextA (HANDLE, DWORD, LPDWORD, LPWSAQUERYSETA);
WINSOCK_API_LINKAGE INT WINAPI WSALookupServiceNextW (HANDLE, DWORD, LPDWORD, LPWSAQUERYSETW);

WINSOCK_API_LINKAGE INT WINAPI WSALookupServiceEnd (HANDLE);
WINSOCK_API_LINKAGE int WINAPI WSANSPIoctl (HANDLE, DWORD, LPVOID, DWORD, LPVOID, DWORD, LPDWORD, LPWSACOMPLETION); /* XP or .NET Server */
WINSOCK_API_LINKAGE int WINAPI WSANtohl (SOCKET, unsigned long, unsigned long *);
WINSOCK_API_LINKAGE int WINAPI WSANtohs (SOCKET, unsigned short, unsigned short *);
WINSOCK_API_LINKAGE int WINAPI WSARecv (SOCKET, LPWSABUF, DWORD, LPDWORD, LPDWORD, LPWSAOVERLAPPED, LPWSAOVERLAPPED_COMPLETION_ROUTINE);
WINSOCK_API_LINKAGE int WINAPI WSARecvDisconnect (SOCKET, LPWSABUF);
WINSOCK_API_LINKAGE int WINAPI WSARecvFrom (SOCKET, LPWSABUF, DWORD, LPDWORD, LPDWORD, struct sockaddr *, LPINT, LPWSAOVERLAPPED, LPWSAOVERLAPPED_COMPLETION_ROUTINE);
WINSOCK_API_LINKAGE INT WINAPI WSARemoveServiceClass (LPGUID);
WINSOCK_API_LINKAGE BOOL WINAPI WSAResetEvent (WSAEVENT);
WINSOCK_API_LINKAGE int WINAPI WSASend (SOCKET, LPWSABUF, DWORD, LPDWORD, DWORD, LPWSAOVERLAPPED, LPWSAOVERLAPPED_COMPLETION_ROUTINE);
WINSOCK_API_LINKAGE int WINAPI WSASendDisconnect (SOCKET, LPWSABUF);
WINSOCK_API_LINKAGE int WINAPI WSASendTo (SOCKET, LPWSABUF, DWORD, LPDWORD, DWORD, const struct sockaddr *, int, LPWSAOVERLAPPED, LPWSAOVERLAPPED_COMPLETION_ROUTINE);
WINSOCK_API_LINKAGE BOOL WINAPI WSASetEvent (WSAEVENT);

#define WSASetService __AW_SUFFIXED__(WSASetService)
WINSOCK_API_LINKAGE INT WSAAPI WSASetServiceA (LPWSAQUERYSETA, WSAESETSERVICEOP, DWORD);
WINSOCK_API_LINKAGE INT WINAPI WSASetServiceW (LPWSAQUERYSETW, WSAESETSERVICEOP, DWORD);

#define WSASocket __AW_SUFFIXED__(WSASocket)
WINSOCK_API_LINKAGE SOCKET WINAPI WSASocketA (int, int, int, LPWSAPROTOCOL_INFOA, GROUP, DWORD);
WINSOCK_API_LINKAGE SOCKET WINAPI WSASocketW (int, int, int, LPWSAPROTOCOL_INFOW, GROUP, DWORD);

#define WSAStringToAddress __AW_SUFFIXED__(WSAStringToAddress)
WINSOCK_API_LINKAGE INT WINAPI WSAStringToAddressA (LPSTR, INT, LPWSAPROTOCOL_INFOA, LPSOCKADDR, LPINT);
WINSOCK_API_LINKAGE INT WINAPI WSAStringToAddressW (LPWSTR, INT, LPWSAPROTOCOL_INFOW, LPSOCKADDR, LPINT);

WINSOCK_API_LINKAGE DWORD WINAPI WSAWaitForMultipleEvents (DWORD, const WSAEVENT *, BOOL, DWORD, BOOL);

typedef SOCKET (WINAPI *LPFN_WSAACCEPT) (SOCKET, struct sockaddr *, LPINT, LPCONDITIONPROC, DWORD);

#define LPFN_WSAADDRESSTOSTRING __AW_SUFFIXED__(LPFN_WSAADDRESSTOSTRING)
typedef INT (WINAPI *LPFN_WSAADDRESSTOSTRINGA) (LPSOCKADDR, DWORD, LPWSAPROTOCOL_INFOA, LPSTR, LPDWORD);
typedef INT (WINAPI *LPFN_WSAADDRESSTOSTRINGW) (LPSOCKADDR, DWORD, LPWSAPROTOCOL_INFOW, LPWSTR, LPDWORD);

typedef BOOL (WINAPI *LPFN_WSACLOSEEVENT) (WSAEVENT);
typedef int (WINAPI *LPFN_WSACONNECT) (SOCKET, const struct sockaddr *, int, LPWSABUF, LPWSABUF, LPQOS, LPQOS);
typedef WSAEVENT (WINAPI *LPFN_WSACREATEEVENT) (void);

#define LPFN_WSADUPLICATESOCKET __AW_SUFFIXED__(LPFN_WSADUPLICATESOCKET)
typedef int (WINAPI *LPFN_WSADUPLICATESOCKETA) (SOCKET, DWORD, LPWSAPROTOCOL_INFOA);
typedef int (WINAPI *LPFN_WSADUPLICATESOCKETW) (SOCKET, DWORD, LPWSAPROTOCOL_INFOW);

#define LPFN_WSAENUMNAMESPACEPROVIDERS __AW_SUFFIXED__(LPFN_WSAENUMNAMESPACEPROVIDERS)
typedef INT (WINAPI *LPFN_WSAENUMNAMESPACEPROVIDERSA) (LPDWORD, LPWSANAMESPACE_INFOA);
typedef INT (WINAPI *LPFN_WSAENUMNAMESPACEPROVIDERSW) (LPDWORD, LPWSANAMESPACE_INFOW);

typedef int (WINAPI *LPFN_WSAENUMNETWORKEVENTS) (SOCKET, WSAEVENT, LPWSANETWORKEVENTS);

#define LPFN_WSAENUMPROTOCOLS __AW_SUFFIXED__(LPFN_WSAENUMPROTOCOLS)
typedef int (WINAPI *LPFN_WSAENUMPROTOCOLSA) (LPINT, LPWSAPROTOCOL_INFOA, LPDWORD);
typedef int (WINAPI *LPFN_WSAENUMPROTOCOLSW) (LPINT, LPWSAPROTOCOL_INFOW, LPDWORD);

typedef int (WINAPI *LPFN_WSAEVENTSELECT) (SOCKET, WSAEVENT, long);
typedef BOOL (WINAPI *LPFN_WSAGETOVERLAPPEDRESULT) (SOCKET, LPWSAOVERLAPPED, LPDWORD, BOOL, LPDWORD);
typedef BOOL (WINAPI *LPFN_WSAGETQOSBYNAME) (SOCKET, LPWSABUF, LPQOS);

#define LPFN_WSAGETSERVICECLASSINFO __AW_SUFFIXED__(LPFN_WSAGETSERVICECLASSINFO)
typedef INT (WINAPI *LPFN_WSAGETSERVICECLASSINFOA) (LPGUID, LPGUID, LPDWORD, LPWSASERVICECLASSINFOA);
typedef INT (WINAPI *LPFN_WSAGETSERVICECLASSINFOW) (LPGUID, LPGUID, LPDWORD, LPWSASERVICECLASSINFOW);

#define LPFN_WSAGETSERVICECLASSNAMEBYCLASSID __AW_SUFFIXED__(LPFN_WSAGETSERVICECLASSNAMEBYCLASSID)
typedef INT (WINAPI *LPFN_WSAGETSERVICECLASSNAMEBYCLASSIDA) (LPGUID, LPSTR, LPDWORD);
typedef INT (WINAPI *LPFN_WSAGETSERVICECLASSNAMEBYCLASSIDW) (LPGUID, LPWSTR, LPDWORD);

typedef int (WINAPI *LPFN_WSAHTONL) (SOCKET, unsigned long, unsigned long *);
typedef int (WINAPI *LPFN_WSAHTONS) (SOCKET, unsigned short, unsigned short *);

#define LPFN_WSAINSTALLSERVICECLASS __AW_SUFFIXED__(LPFN_WSAINSTALLSERVICECLASS)
typedef INT (WINAPI *LPFN_WSAINSTALLSERVICECLASSA) (LPWSASERVICECLASSINFOA);
typedef INT (WINAPI *LPFN_WSAINSTALLSERVICECLASSW) (LPWSASERVICECLASSINFOW);

typedef int (WINAPI *LPFN_WSAIOCTL) (SOCKET, DWORD, LPVOID, DWORD, LPVOID, DWORD, LPDWORD, LPWSAOVERLAPPED, LPWSAOVERLAPPED_COMPLETION_ROUTINE);
typedef SOCKET (WINAPI *LPFN_WSAJOINLEAF) (SOCKET, const struct sockaddr *, int, LPWSABUF, LPWSABUF, LPQOS, LPQOS, DWORD);

#define LPFN_WSALOOKUPSERVICEBEGIN __AW_SUFFIXED__(LPFN_WSALOOKUPSERVICEBEGIN)
typedef INT (WINAPI *LPFN_WSALOOKUPSERVICEBEGINA) (LPWSAQUERYSETA, DWORD, LPHANDLE);
typedef INT (WINAPI *LPFN_WSALOOKUPSERVICEBEGINW) (LPWSAQUERYSETW, DWORD, LPHANDLE);

#define LPFN_WSALOOKUPSERVICENEXT __AW_SUFFIXED__(LPFN_WSALOOKUPSERVICENEXT)
typedef INT (WINAPI *LPFN_WSALOOKUPSERVICENEXTA) (HANDLE, DWORD, LPDWORD, LPWSAQUERYSETA);
typedef INT (WINAPI *LPFN_WSALOOKUPSERVICENEXTW) (HANDLE, DWORD, LPDWORD, LPWSAQUERYSETW);

typedef INT (WINAPI *LPFN_WSALOOKUPSERVICEEND) (HANDLE);
typedef int (WINAPI *LPFN_WSANSPIoctl) (HANDLE, DWORD, LPVOID, DWORD, LPVOID, DWORD, LPDWORD, LPWSACOMPLETION);
typedef int (WINAPI *LPFN_WSANTOHL) (SOCKET, unsigned long, unsigned long *);
typedef int (WINAPI *LPFN_WSANTOHS) (SOCKET, unsigned short, unsigned short *);
typedef int (WINAPI *LPFN_WSARECV) (SOCKET, LPWSABUF, DWORD, LPDWORD, LPDWORD, LPWSAOVERLAPPED, LPWSAOVERLAPPED_COMPLETION_ROUTINE);
typedef int (WINAPI *LPFN_WSARECVDISCONNECT) (SOCKET, LPWSABUF);
typedef int (WINAPI *LPFN_WSARECVFROM) (SOCKET, LPWSABUF, DWORD, LPDWORD, LPDWORD, struct sockaddr *, LPINT, LPWSAOVERLAPPED, LPWSAOVERLAPPED_COMPLETION_ROUTINE);
typedef INT (WINAPI *LPFN_WSAREMOVESERVICECLASS) (LPGUID);
typedef BOOL (WINAPI *LPFN_WSARESETEVENT) (WSAEVENT);
typedef int (WINAPI *LPFN_WSASEND) (SOCKET, LPWSABUF, DWORD, LPDWORD, DWORD, LPWSAOVERLAPPED, LPWSAOVERLAPPED_COMPLETION_ROUTINE);
typedef int (WINAPI *LPFN_WSASENDDISCONNECT) (SOCKET, LPWSABUF);
typedef int (WINAPI *LPFN_WSASENDTO) (SOCKET, LPWSABUF, DWORD, LPDWORD, DWORD, const struct sockaddr *, int, LPWSAOVERLAPPED, LPWSAOVERLAPPED_COMPLETION_ROUTINE);
typedef BOOL (WINAPI *LPFN_WSASETEVENT) (WSAEVENT);

#define LPFN_WSASETSERVICE  __AW_SUFFIXED__(LPFN_WSASETSERVICE)
typedef INT (WINAPI *LPFN_WSASETSERVICEA) (LPWSAQUERYSETA, WSAESETSERVICEOP, DWORD);
typedef INT (WINAPI *LPFN_WSASETSERVICEW) (LPWSAQUERYSETW, WSAESETSERVICEOP, DWORD);

#define LPFN_WSASOCKET __AW_SUFFIXED__(LPFN_WSASOCKET)
typedef SOCKET (WINAPI *LPFN_WSASOCKETA) (int, int, int, LPWSAPROTOCOL_INFOA, GROUP, DWORD);
typedef SOCKET (WINAPI *LPFN_WSASOCKETW) (int, int, int, LPWSAPROTOCOL_INFOW, GROUP, DWORD);

#define LPFN_WSASTRINGTOADDRESS __AW_SUFFIXED__(LPFN_WSASTRINGTOADDRESS)
typedef INT (WINAPI *LPFN_WSASTRINGTOADDRESSA) (LPSTR, INT, LPWSAPROTOCOL_INFOA, LPSOCKADDR, LPINT);
typedef INT (WINAPI *LPFN_WSASTRINGTOADDRESSW) (LPWSTR, INT, LPWSAPROTOCOL_INFOW, LPSOCKADDR, LPINT);

typedef DWORD (WINAPI *LPFN_WSAWAITFORMULTIPLEEVENTS) (DWORD, const WSAEVENT *, BOOL, DWORD, BOOL);

_END_C_DECLS

#undef __WINSOCK2_H_SOURCED__
#endif	/* !_WINSOCK_H included prematurely */
#endif	/* _WINSOCK2_H: $RCSfile: winsock2.h,v $: end of file */

/*
 * winsock.h
 *
 * Definitions for WinSock Version 1.1 API; also includes a subset of the
 * definitions which become applicable for WinSock Version 2, filtered such
 * that they are exposed only when this file is included by <winsock2.h>
 *
 *
 * $Id: winsock.h,v a346ddcc5d76 2017/11/28 13:28:34 keith $
 *
 * Adaptation by Anders Norlander <anorland@hem2.passagen.se>
 * Copyright (C) 1998-2004, 2012, 2016, 2017, MinGW.org Project.
 *
 * Portions Copyright (C) 1980, 1983, 1988, 1993
 * The Regents of the University of California.  All rights reserved.
 *
 * Portions Copyright (C) 1993 by Digital Equipment Corporation.
 *
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notices, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 */
#ifndef _WINSOCK_H
#pragma GCC system_header
#define _WINSOCK_H

#define _GNU_H_WINDOWS32_SOCKETS
#define __WINSOCK_H_SOURCED__ 1

#include <windows.h>
#include <winerror.h>
#include <sys/bsdtypes.h>
#include <sys/time.h>

#ifndef WINSOCK_API_LINKAGE
/* Historically, this was defined (and used) within <winsock2.h>, but not
 * <winsock.h>, to qualify function declarations which are common to both;
 * for consistency, we now define, (and subsequently use it here), while
 * preserving the effect of its previous absence, within <winsock.h>, by
 * ensuring that it expands to nothing in this context.
 *
 * FIXME: Is this logical?  Perhaps <winsock.h> should adopt the effect,
 * exactly as it was previously implemented exclusively in <winsock2.h>?
 */
#if defined _WINSOCK2_H && defined __W32API_USE_DLLIMPORT__
/* To preserve backward compatibility, DECLSPEC_IMPORT option is
 * available only to WinSock v2 clients, which request it...
 */
#define WINSOCK_API_LINKAGE  DECLSPEC_IMPORT

#else
/* ...whereas WinSock v1.1 clients, and those WinSock v2 clients which
 * do not request DECLSPEC_IMPORT, will always use default linkage.
 */
#define WINSOCK_API_LINKAGE
#endif
#endif

#if ! defined _USE_SYS_TYPES_FD_SET && defined USE_SYS_TYPES_FD_SET
/* Originally defined by the deprecated name, USE_SYS_TYPES_FD_SET, users
 * may specify this to suppress warnings, in the event that (incompatible)
 * fd_set manipulation macros may have been inherited from <sys/types.h>;
 * accommodate use of the deprecated feature test name.
 */
#warning "Feature test macro USE_SYS_TYPES_FD_SET is deprecated."
#warning "Use the _USE_SYS_TYPES_FD_SET feature test macro instead."
#define _USE_SYS_TYPES_FD_SET  1
#endif

#ifndef __WINSOCK2_DEPRECATED
/* Some of the WinSock v1.1 declarations have become deprecated in
 * WinSock v2.  If <winsock2.h> has been included, this deprecation
 * attribute macro should already have been defined; if not, we now
 * define it to do nothing.
 */
#define __WINSOCK2_DEPRECATED
#endif

_BEGIN_C_DECLS

typedef u_int  SOCKET;

#ifndef FD_SETSIZE
#define FD_SETSIZE				  64
#endif

/* shutdown() how types */
#define SD_RECEIVE				0x00
#define SD_SEND 				0x01
#define SD_BOTH 				0x02

#ifndef _SYS_TYPES_FD_SET
/* fd_set may have been defined by the newlib <sys/types.h>, if the
 * internal __USE_W32_SOCKETS feature test has not been enabled.
 */
#undef fd_set
typedef
struct fd_set
{ u_int 	fd_count;
  SOCKET	fd_array[FD_SETSIZE];
} fd_set;

#ifndef FD_ISSET
int FD_ISSET (SOCKET, fd_set *);
#define FD_ISSET( __fd, __set )  __FD_ISSET ((__fd), (__set))

/* Microsoft provide this library function equivalent of the FD_ISSET
 * macro, and erroneously claim that it is neccessary to implement the
 * macro.  We could just as easily implement it entirely inline...
 */
int PASCAL __WSAFDIsSet (SOCKET, fd_set *);
/* ...but, given the availability of the library function, we may just
 * as well use it.
 */
__CRT_ALIAS int __FD_ISSET( SOCKET __fd, fd_set *__set )
{ return __WSAFDIsSet (__fd, __set); }
#endif	/* ! defined FD_ISSET */

#ifndef FD_SET
#if !_WINSOCK_ANOMALOUS_TYPEDEFS
/* WinSock is intended to mimic the Berkeley Sockets API, for which
 * POSIX.1 provides a reference specification; this states that FD_SET
 * may be implemented as either a macro, or as a function.  The reference
 * <winsock.h> implementation at http://www.sockets.com/winsock.htm#WinsockH
 * includes a typedef for FD_SET, which a) conflicts with the latter POSIX.1
 * provision, and b) creates potential confusion with the former.  Thus, we
 * prefer to conform with POSIX.1 functional semantics, and recommend that
 * users avoid the potentially confusing FD_SET typedefs, so allowing us
 * to provide this function prototype:
 */
void FD_SET (SOCKET, fd_set *);

#else	/* _WINSOCK_ANOMALOUS_TYPEDEFS */
/* However, for users who insist on eschewing standard C/C++ syntax, and
 * for whatever reason must use FD_SET as a data type, instead of correctly
 * referring to fd_set, or for pointer references, use PFD_SET or LPFD_SET
 * instead of standard fd_set * references, we make these anomalous types
 * visible, when the _WINSOCK_ANOMALOUS_TYPEDEFS feature test macro is
 * defined with a non-zero value.
 */
#warning "FD_SET, PFD_SET, and LPFD_SET data types are non-portable."
#warning "Use portable fd_set, and fd_set * type references instead."

typedef struct fd_set FD_SET, *PFD_SET, *LPFD_SET;
#endif
#define FD_SET( __fd, __set )  __FD_SET ((__fd), (__set))
__CRT_ALIAS void __FD_SET (SOCKET __fd, fd_set *__set)
{ if( (__set->fd_count < FD_SETSIZE) && ! FD_ISSET (__fd, __set) )
    __set->fd_array[__set->fd_count++] = __fd;
}
#endif	/* ! defined FD_SET */

#ifndef FD_CLR
void FD_CLR (SOCKET, fd_set *);
#define FD_CLR( __fd, __set )  __FD_CLR ((__fd), (__set))
__CRT_ALIAS void __FD_CLR (SOCKET __fd, fd_set *__set)
{ u_int __m, __n; for (__m = __n = 0; __n < __set->fd_count; __n++)
  { if (__fd != __set->fd_array[__n])
    { if (__m < __n) __set->fd_array[__m] = __set->fd_array[__n];
      ++__m;
    }
  } __set->fd_count = __m;
}
#endif	/* ! defined FD_CLR */

#ifndef FD_ZERO
void FD_ZERO (fd_set *);
#define FD_ZERO( __set )  __FD_ZERO (__set)
__CRT_ALIAS void __FD_ZERO (fd_set *__set)
{ __set->fd_count = 0; }
#endif	/* ! defined FD_ZERO */

#elif ! defined _USE_SYS_TYPES_FD_SET
/* Definitions from <sys/types.h> probably aren't what the user wants;
 * if they know what they are doing, and they are sure that this really
 * is what they want, then they may enable the _USE_SYS_TYPES_FD_SET
 * feature test macro, to suppress this warning.
 */
#warning "fd_set and associated macros have been defined in <sys/types.h>"
#warning "Your <sys/types.h> may cause runtime problems with W32 sockets."
#endif	/* !_SYS_TYPES_FD_SET */

#ifndef __INSIDE_MSYS__

struct hostent
{ char		 *h_name;
  char		**h_aliases;
  short 	  h_addrtype;
  short 	  h_length;
# define	  h_addr  h_addr_list[0]
  char		**h_addr_list;
};

struct linger
{ u_short	  l_onoff;
  u_short	  l_linger;
};

#endif	/* !__INSIDE_MSYS__ */

#define IOCPARM_MASK			      0x7F
#define IOC_VOID			0x20000000
#define IOC_OUT 			0x40000000
#define IOC_IN				0x80000000
#define IOC_INOUT		    (IOC_IN | IOC_OUT)

#ifndef __INSIDE_MSYS__

#define _IO(x,y)	(IOC_VOID|((x)<<8)|(y))
#define _IOR(x,y,t)	(IOC_OUT|(((long)sizeof(t)&IOCPARM_MASK)<<16)|((x)<<8)|(y))
#define _IOW(x,y,t)	(IOC_IN|(((long)sizeof(t)&IOCPARM_MASK)<<16)|((x)<<8)|(y))

#define FIONBIO 		_IOW('f', 126, u_long)

#endif	/* !__INSIDE_MSYS__ */

#define FIONREAD		_IOR('f', 127, u_long)
#define FIOASYNC		_IOW('f', 125, u_long)
#define SIOCSHIWAT		_IOW('s',  0, u_long)
#define SIOCGHIWAT		_IOR('s',  1, u_long)
#define SIOCSLOWAT		_IOW('s',  2, u_long)
#define SIOCGLOWAT		_IOR('s',  3, u_long)
#define SIOCATMARK		_IOR('s',  7, u_long)

#ifndef __INSIDE_MSYS__

struct netent
{ char		 *n_name;
  char		**n_aliases;
  short 	  n_addrtype;
  u_long	  n_net;
};

struct servent
{ char		 *s_name;
  char		**s_aliases;
  short 	  s_port;
  char		 *s_proto;
};

struct protoent
{ char		 *p_name;
  char		**p_aliases;
  short 	  p_proto;
};

#endif	/* !__INSIDE_MSYS__ */

#define IPPROTO_IP				   0
#define IPPROTO_ICMP				   1
#define IPPROTO_IGMP				   2
#define IPPROTO_GGP				   3
#define IPPROTO_TCP				   6
#define IPPROTO_PUP				  12
#define IPPROTO_UDP				  17
#define IPPROTO_IDP				  22
#define IPPROTO_ND				  77

#define IPPROTO_RAW				 255
#define IPPROTO_MAX				 256

#define IPPORT_ECHO				   7
#define IPPORT_DISCARD				   9
#define IPPORT_SYSTAT				  11
#define IPPORT_DAYTIME				  13
#define IPPORT_NETSTAT				  15
#define IPPORT_FTP				  21
#define IPPORT_TELNET				  23
#define IPPORT_SMTP				  25
#define IPPORT_TIMESERVER			  37
#define IPPORT_NAMESERVER			  42
#define IPPORT_WHOIS				  43
#define IPPORT_MTP				  57
#define IPPORT_TFTP				  69
#define IPPORT_RJE				  77
#define IPPORT_FINGER				  79
#define IPPORT_TTYLINK				  87
#define IPPORT_SUPDUP				  95
#define IPPORT_EXECSERVER			 512
#define IPPORT_LOGINSERVER			 513
#define IPPORT_CMDSERVER			 514
#define IPPORT_EFSSERVER			 520
#define IPPORT_BIFFUDP				 512
#define IPPORT_WHOSERVER			 513
#define IPPORT_ROUTESERVER			 520
#define IPPORT_RESERVED 			1024

#define IMPLINK_IP				 155
#define IMPLINK_LOWEXPER			 156
#define IMPLINK_HIGHEXPER			 158

struct in_addr
#define s_addr				      S_un.S_addr
#define s_host				      S_un.S_un_b.s_b2
#define s_net				      S_un.S_un_b.s_b1
#define s_imp				      S_un.S_un_w.s_w2
#define s_impno 			      S_un.S_un_b.s_b4
#define s_lh				      S_un.S_un_b.s_b3
{ union
  { struct { u_char s_b1,s_b2,s_b3,s_b4; }	S_un_b;
    struct { u_short s_w1,s_w2; }		S_un_w;
    u_long					S_addr;
  }					      S_un;
};

#define IN_CLASSA(i)	    (((long)(i) & 0x80000000) == 0)
#define IN_CLASSA_NET			  0xFF000000
#define IN_CLASSA_NSHIFT			  24
#define IN_CLASSA_HOST			  0x00FFFFFF
#define IN_CLASSA_MAX				 128
#define IN_CLASSB(i)	    (((long)(i) & 0xC0000000) == 0x80000000)
#define IN_CLASSB_NET			  0xFFFF0000
#define IN_CLASSB_NSHIFT			  16
#define IN_CLASSB_HOST			  0x0000FFFF
#define IN_CLASSB_MAX			       65536
#define IN_CLASSC(i)	    (((long)(i) & 0xE0000000) == 0xC0000000)
#define IN_CLASSC_NET			  0xFFFFFF00
#define IN_CLASSC_NSHIFT		           8
#define IN_CLASSC_HOST			        0xFF
#define INADDR_ANY			  (u_long)(0)
#define INADDR_LOOPBACK 		  0x7F000001
#define INADDR_BROADCAST	 (u_long)(0xFFFFFFFF)
#define INADDR_NONE			  0xFFFFFFFF

struct sockaddr_in
{ short 		 sin_family;
  u_short		 sin_port;
  struct in_addr	 sin_addr;
  char			 sin_zero[8];
};

#define WSADESCRIPTION_LEN			 256
#define WSASYS_STATUS_LEN			 128

typedef
struct WSAData
{ WORD			 wVersion;
  WORD			 wHighVersion;
  char			 szDescription[WSADESCRIPTION_LEN+1];
  char			 szSystemStatus[WSASYS_STATUS_LEN+1];
  unsigned short	 iMaxSockets;
  unsigned short	 iMaxUdpDg;
  char			*lpVendorInfo;
} WSADATA, *LPWSADATA;

#ifndef __INSIDE_MSYS__

#define IP_OPTIONS				   1
#define SO_DEBUG				   1
#define SO_ACCEPTCONN				   2
#define SO_REUSEADDR				   4
#define SO_KEEPALIVE				   8
#define SO_DONTROUTE				  16
#define SO_BROADCAST				  32
#define SO_USELOOPBACK				  64
#define SO_LINGER				 128
#define SO_OOBINLINE				 256

#define SO_DONTLINGER			 (u_int)(~SO_LINGER)

#define SO_SNDBUF			      0x1001
#define SO_RCVBUF			      0x1002
#define SO_SNDLOWAT			      0x1003
#define SO_RCVLOWAT			      0x1004
#define SO_SNDTIMEO			      0x1005
#define SO_RCVTIMEO			      0x1006
#define SO_ERROR			      0x1007
#define SO_TYPE 			      0x1008

#endif	/* !__INSIDE_MSYS__ */

#ifndef _WINSOCK2_H
/* The following IP defines are specific to WinSock v1.1 (wsock32.dll).
 * They may cause errors, or produce unexpected results, if exposed when
 * compiling application code which is intended to use the getsockopts(),
 * or setsockopts() APIs, as exported from the WinSock v2 system library,
 * ws2_32.dll.  Please refer to <ws2tcpip.h> for further information.
 */
#define IP_MULTICAST_IF 			   2
#define IP_MULTICAST_TTL			   3
#define IP_MULTICAST_LOOP			   4
#define IP_ADD_MEMBERSHIP			   5
#define IP_DROP_MEMBERSHIP			   6

#define IP_DEFAULT_MULTICAST_TTL		   1
#define IP_DEFAULT_MULTICAST_LOOP		   1
#define IP_MAX_MEMBERSHIPS			  20

struct ip_mreq
{ struct in_addr	 imr_multiaddr;
  struct in_addr	 imr_interface;
};
#endif	/* !_WINSOCK2_H */

#define INVALID_SOCKET			 (SOCKET)(~0)
#define SOCKET_ERROR				 (-1)
#define SOCK_STREAM				   1
#define SOCK_DGRAM				   2
#define SOCK_RAW				   3
#define SOCK_RDM				   4
#define SOCK_SEQPACKET				   5
#define TCP_NODELAY			      0x0001
#define AF_UNSPEC				   0
#define AF_UNIX 				   1
#define AF_INET 				   2
#define AF_IMPLINK				   3
#define AF_PUP					   4
#define AF_CHAOS				   5
#define AF_IPX					   6
#define AF_NS					   6
#define AF_ISO					   7

#define AF_OSI				      AF_ISO

#define AF_ECMA 				   8
#define AF_DATAKIT				   9
#define AF_CCITT				  10
#define AF_SNA					  11
#define AF_DECnet				  12
#define AF_DLI					  13
#define AF_LAT					  14
#define AF_HYLINK				  15
#define AF_APPLETALK				  16
#define AF_NETBIOS				  17
#define AF_VOICEVIEW				  18
#define AF_FIREFOX				  19
#define AF_UNKNOWN1				  20
#define AF_BAN					  21
#define AF_ATM					  22
#define AF_INET6				  23

#ifndef __INSIDE_MSYS__

#define AF_MAX					  24

struct sockaddr
{ u_short		 sa_family;
  char			 sa_data[14];
};

#endif	/* !__INSIDE_MSYS__ */

struct sockproto
{ u_short		 sp_family;
  u_short		 sp_protocol;
};

#define PF_UNSPEC			   AF_UNSPEC
#define PF_UNIX 			     AF_UNIX
#define PF_INET 			     AF_INET
#define PF_IMPLINK			  AF_IMPLINK
#define PF_PUP				      AF_PUP
#define PF_CHAOS			    AF_CHAOS
#define PF_NS				       AF_NS
#define PF_IPX				      AF_IPX
#define PF_ISO				      AF_ISO
#define PF_OSI				      AF_OSI
#define PF_ECMA 			     AF_ECMA
#define PF_DATAKIT			  AF_DATAKIT
#define PF_CCITT			    AF_CCITT
#define PF_SNA				      AF_SNA
#define PF_DECnet			   AF_DECnet
#define PF_DLI				      AF_DLI
#define PF_LAT				      AF_LAT
#define PF_HYLINK			   AF_HYLINK
#define PF_APPLETALK			AF_APPLETALK
#define PF_VOICEVIEW			AF_VOICEVIEW
#define PF_FIREFOX			  AF_FIREFOX
#define PF_UNKNOWN1			 AF_UNKNOWN1
#define PF_BAN				      AF_BAN
#define PF_ATM				      AF_ATM
#define PF_INET6			    AF_INET6
#define PF_MAX				      AF_MAX

#define SOL_SOCKET			      0xFFFF

#ifndef __INSIDE_MSYS__

/* This definition of SOMAXCONN is correct for WinSock v1.1, but not
 * for WinSock v2; we define it thus here, but note that, if included
 * by <winsock2.h>, it will subsequently be overridden by the correct
 * WinSock v2 definition.
 */
#define SOMAXCONN				   5

#define MSG_OOB 				   1
#define MSG_PEEK				   2
#define MSG_DONTROUTE				   4

#endif  /* !__INSIDE_MSYS__ */

#define MSG_MAXIOVLEN				  16
#define MSG_PARTIAL			      0x8000
#define MAXGETHOSTSTRUCT			1024

enum
{ /* Enumerate the flags used to represent the events which may be
   * detected on any socket, when monitored via an fd_set array.
   */
  FD_READ_BIT = 0,
# define FD_READ		      (1 << FD_READ_BIT)

  FD_WRITE_BIT,
# define FD_WRITE		      (1 << FD_WRITE_BIT)

  FD_OOB_BIT,
# define FD_OOB 		      (1 << FD_OOB_BIT)

  FD_ACCEPT_BIT,
# define FD_ACCEPT		      (1 << FD_ACCEPT_BIT)

  FD_CONNECT_BIT,
# define FD_CONNECT		      (1 << FD_CONNECT_BIT)

  FD_CLOSE_BIT,
# define FD_CLOSE		      (1 << FD_CLOSE_BIT)

# ifdef _WINSOCK2_H
/* WinSock v1.1 defines no further events, beyond FD_CLOSE (1 << 5 = 32).
 * The following are specific to WinSock v2; for convenience, they may be
 * enumerated here, but they are exposed only when <winsock.h> is included
 * indirectly, by way of including <winsock2.h>
 */
  FD_QOS_BIT,
# define FD_QOS 		      (1 << FD_QOS_BIT)

  FD_GROUP_QOS_BIT,
# define FD_GROUP_QOS		      (1 << FD_GROUP_QOS_BIT)

  FD_ROUTING_INTERFACE_CHANGE_BIT,
# define FD_ROUTING_INTERFACE_CHANGE  (1 << FD_ROUTING_INTERFACE_CHANGE_BIT)

  FD_ADDRESS_LIST_CHANGE_BIT,
# define FD_ADDRESS_LIST_CHANGE       (1 << FD_ADDRESS_LIST_CHANGE_BIT)

# endif /* _WINSOCK2_H */
  /* Regardless of WinSock version, FD_MAX_EVENTS represents the first
   * unused flag bit, whence we may deduce FD_ALL_EVENTS, as a mask for
   * all supported event flags, specific to the WinSock version in use.
   */
  FD_MAX_EVENTS,
# define FD_ALL_EVENTS			((1 << FD_MAX_EVENTS) - 1)
};

#define WSANO_ADDRESS			WSANO_DATA

#ifndef __INSIDE_MSYS__

#define h_errno 			WSAGetLastError()
#define HOST_NOT_FOUND			WSAHOST_NOT_FOUND
#define TRY_AGAIN			WSATRY_AGAIN
#define NO_RECOVERY			WSANO_RECOVERY
#define NO_DATA 			WSANO_DATA
#define NO_ADDRESS			WSANO_ADDRESS

#endif	/* !__INSIDE_MSYS__ */

WINSOCK_API_LINKAGE SOCKET PASCAL accept (SOCKET, struct sockaddr *, int *);

WINSOCK_API_LINKAGE int PASCAL bind (SOCKET, const struct sockaddr *, int);
WINSOCK_API_LINKAGE int PASCAL closesocket (SOCKET);
WINSOCK_API_LINKAGE int PASCAL connect (SOCKET, const struct sockaddr *, int);
WINSOCK_API_LINKAGE int PASCAL ioctlsocket (SOCKET, long, u_long *);
WINSOCK_API_LINKAGE int PASCAL getpeername (SOCKET, struct sockaddr *, int *);
WINSOCK_API_LINKAGE int PASCAL getsockname (SOCKET, struct sockaddr *, int *);
WINSOCK_API_LINKAGE int PASCAL getsockopt (SOCKET, int, int, char *, int *);

WINSOCK_API_LINKAGE unsigned long PASCAL inet_addr (const char *);

WINSOCK_API_LINKAGE DECLARE_STDCALL_P (char *) inet_ntoa (struct in_addr);

WINSOCK_API_LINKAGE int PASCAL listen (SOCKET, int);
WINSOCK_API_LINKAGE int PASCAL recv (SOCKET, char *, int, int);
WINSOCK_API_LINKAGE int PASCAL recvfrom (SOCKET, char *, int, int, struct sockaddr *, int *);
WINSOCK_API_LINKAGE int PASCAL send (SOCKET, const char *, int, int);
WINSOCK_API_LINKAGE int PASCAL sendto (SOCKET, const char *, int, int, const struct sockaddr *, int);
WINSOCK_API_LINKAGE int PASCAL setsockopt (SOCKET, int, int, const char *, int);
WINSOCK_API_LINKAGE int PASCAL shutdown (SOCKET, int);

WINSOCK_API_LINKAGE SOCKET PASCAL socket (int, int, int);

WINSOCK_API_LINKAGE DECLARE_STDCALL_P (struct hostent *)  gethostbyaddr (const char *, int, int);
WINSOCK_API_LINKAGE DECLARE_STDCALL_P (struct hostent *)  gethostbyname (const char *);
WINSOCK_API_LINKAGE DECLARE_STDCALL_P (struct servent *)  getservbyport (int, const char *);
WINSOCK_API_LINKAGE DECLARE_STDCALL_P (struct servent *)  getservbyname (const char *, const char *);
WINSOCK_API_LINKAGE DECLARE_STDCALL_P (struct protoent *) getprotobynumber (int);
WINSOCK_API_LINKAGE DECLARE_STDCALL_P (struct protoent *) getprotobyname (const char *);

WINSOCK_API_LINKAGE int PASCAL WSAStartup (WORD, LPWSADATA);
WINSOCK_API_LINKAGE int PASCAL WSACleanup (void);
WINSOCK_API_LINKAGE void PASCAL WSASetLastError (int);
WINSOCK_API_LINKAGE int PASCAL WSAGetLastError (void);

/* The following four pseudo-blocking functions are provided
 * to support WinSock v1.1, but have been marked as deprecated
 * in WinSock v2; they remain available, but it is recommended
 * that threads should be used instead!
 */
WINSOCK_API_LINKAGE BOOL PASCAL WSAIsBlocking (void) __WINSOCK2_DEPRECATED;
WINSOCK_API_LINKAGE int PASCAL WSAUnhookBlockingHook (void) __WINSOCK2_DEPRECATED;
WINSOCK_API_LINKAGE FARPROC PASCAL WSASetBlockingHook (FARPROC) __WINSOCK2_DEPRECATED;
WINSOCK_API_LINKAGE int PASCAL WSACancelBlockingCall (void) __WINSOCK2_DEPRECATED;

WINSOCK_API_LINKAGE HANDLE PASCAL WSAAsyncGetServByName (HWND, u_int, const char *, const char *, char *, int);
WINSOCK_API_LINKAGE HANDLE PASCAL WSAAsyncGetServByPort (HWND, u_int, int, const char *, char *, int);
WINSOCK_API_LINKAGE HANDLE PASCAL WSAAsyncGetProtoByName (HWND, u_int, const char *, char *, int);
WINSOCK_API_LINKAGE HANDLE PASCAL WSAAsyncGetProtoByNumber (HWND, u_int, int, char *, int);
WINSOCK_API_LINKAGE HANDLE PASCAL WSAAsyncGetHostByName (HWND, u_int, const char *, char *, int);
WINSOCK_API_LINKAGE HANDLE PASCAL WSAAsyncGetHostByAddr (HWND, u_int, const char *, int, int, char *, int);

WINSOCK_API_LINKAGE int PASCAL WSACancelAsyncRequest (HANDLE);
WINSOCK_API_LINKAGE int PASCAL WSAAsyncSelect (SOCKET, HWND, u_int, long);

#ifndef __INSIDE_MSYS__

WINSOCK_API_LINKAGE u_long PASCAL htonl (u_long);
WINSOCK_API_LINKAGE u_long PASCAL ntohl (u_long);
WINSOCK_API_LINKAGE u_short PASCAL htons (u_short);
WINSOCK_API_LINKAGE u_short PASCAL ntohs (u_short);
WINSOCK_API_LINKAGE int PASCAL select (int nfds, fd_set *, fd_set *, fd_set *, const struct timeval *);

#endif	/* !__INSIDE_MSYS__ */

WINSOCK_API_LINKAGE int PASCAL gethostname (char *, int);

#define WSAMAKEASYNCREPLY(b,e)			MAKELONG(b,e)
#define WSAMAKESELECTREPLY(e,error)		MAKELONG(e,error)
#define WSAGETASYNCBUFLEN(l)			LOWORD(l)
#define WSAGETASYNCERROR(l)			HIWORD(l)
#define WSAGETSELECTEVENT(l)			LOWORD(l)
#define WSAGETSELECTERROR(l)			HIWORD(l)

typedef struct sockaddr SOCKADDR, *PSOCKADDR, *LPSOCKADDR;
typedef struct sockaddr_in SOCKADDR_IN, *PSOCKADDR_IN, *LPSOCKADDR_IN;
typedef struct linger LINGER, *PLINGER, *LPLINGER;
typedef struct in_addr IN_ADDR, *PIN_ADDR, *LPIN_ADDR;
typedef struct hostent HOSTENT, *PHOSTENT, *LPHOSTENT;
typedef struct servent SERVENT, *PSERVENT, *LPSERVENT;
typedef struct protoent PROTOENT, *PPROTOENT, *LPPROTOENT;
typedef struct timeval TIMEVAL, *PTIMEVAL, *LPTIMEVAL;

_END_C_DECLS

#ifndef _WINSOCK2_H
/* MSDN documentation indicates that the MS-specific extensions exported
 * from mswsock.dll, (i.e. the AcceptEx(), TransmitFile(), WSARecEx(), and
 * GetAcceptExSockaddrs() functions), are declared in <mswsock.h>.  These
 * extensions are not supported on Win9x or WinCE.  However, WinSock v1.1
 * dependent code may expect that the declarations and associated defines
 * will be in this header; thus we include <mswsock.h> here.
 *
 * When linking against the WinSock v1.1 library, wsock32.dll, the mswsock
 * functions are automatically routed to mswsock.dll (on platforms which
 * support it).  The WinSock v2 library, ws2_32.dll, does not contain any
 * references to the mswsock extensions.
 */
#include <mswsock.h>
#endif

#undef	__WINSOCK_H_SOURCED__
#endif	/* _WINSOCK_H: $RCSfile: winsock.h,v $: end of file */

/* ES40 emulator.
 * Copyright (C) 2007 by Camiel Vanderhoeven
 *
 * Website: www.camicom.com
 * E-mail : camiel@camicom.com
 * 
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 * 
 * Although this is not required, the author would appreciate being notified of, 
 * and receiving any modifications you may make to the source code that might serve
 * the general public.
 */

/** 
 * \file
 * Contains telnet declarations used by the serial port emulator and lock-step code.
 *
 * \author Camiel Vanderhoeven (camiel@camicom.com / http://www.camicom.com)
 **/

#if !defined(INCLUDED_TELNET_H)
#define INCLUDED_TELNET_H

#if defined(_WIN32)
#include <winsock.h>
#define ssize_t size_t
#define socklen_t int
#endif

#if defined(__VMS)
#include <socket.h>
#include <in.h>
#include <inet.h>
#define INVALID_SOCKET -1
#define socklen_t unsigned int
#endif

#if defined(_WIN32) || defined(__VMS)

#define	IAC	255		/* interpret as command: */
#define	DONT	254		/* you are not to use option */
#define	DO	253		/* please, you use option */
#define	WONT	252		/* I won't use option */
#define	WILL	251		/* I will use option */
#define	SB	250		/* interpret as subnegotiation */
#define	GA	249		/* you may reverse the line */
#define	EL	248		/* erase the current line */
#define	EC	247		/* erase the current character */
#define	AYT	246		/* are you there */
#define	AO	245		/* abort output--but let prog finish */
#define	IP	244		/* interrupt process--permanently */
#define	BREAK	243		/* break */
#define	DM	242		/* data mark--for connect. cleaning */
#define	NOP	241		/* nop */
#define	SE	240		/* end sub negotiation */
#define EOR     239             /* end of record (transparent mode) */
#define	ABORT	238		/* Abort process */
#define	SUSP	237		/* Suspend process */
#define	xEOF	236		/* End of file: EOF is already used... */

#define SYNCH	242		/* for telfunc calls */
#define TELOPT_ECHO	1	/* echo */
#define	TELOPT_SGA	3	/* suppress go ahead */
#define	TELOPT_NAWS	31	/* window size */
#define	TELOPT_LFLOW	33	/* remote flow control */

#else // defined(_WIN32) || defined(__VMS)

#include <arpa/inet.h>
#include <arpa/telnet.h>
#include <netinet/in.h>
#include <sys/select.h>
#include <sys/time.h>
#include <unistd.h>
#define INVALID_SOCKET 1

#endif // defined (_WIN32) || defined(__VMS)

#endif // !defined(INCLUDED_TELNET_H)
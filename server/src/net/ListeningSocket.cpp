/*
 *  This file is part of dsmmorpg.
 *  
 *  dsmmorpg is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *  
 *  dsmmorpg is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *  
 *  You should have received a copy of the GNU General Public License
 *  along with dsmmorpg.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "ListeningSocket.hpp"

ListeningSocket :: ListeningSocket ()
{
	m_descriptor = socket (AF_INET, SOCK_STREAM, IPPROTO_TCP);
	
	if (m_descriptor == -1)
	{
		throw errno;
	}
	
	int reuseaddr = 1;
	int error = setsockopt (m_descriptor, SOL_SOCKET, SO_REUSEADDR, (char *)(&reuseaddr), sizeof (reuseaddr));
	if (error == -1)
	{
		throw errno;
	}
}

void ListeningSocket :: Bind (unsigned short int port)
{
	struct sockaddr_in address;
	
	address.sin_family = AF_INET;
	address.sin_port = htons (port);
	address.sin_addr.s_addr = htonl (INADDR_ANY);
	bzero(&address.sin_zero, 0);
	
	int error = bind (m_descriptor, (struct sockaddr *)(&address), sizeof (struct sockaddr));
	if (error == -1)
	{
		throw errno;
	}
}

void ListeningSocket :: Listen ()
{
	int error  = listen (m_descriptor, 8);
	if (error == -1)
	{
		throw errno;
	}
}

void ListeningSocket :: SetNonBlockingFlag (bool nonblocking)
{
	#ifdef WIN32
		unsigned long mode = nonblocking;
		
		int error = ioctlsocket (m_descriptor, FIONBIO, &mode);
		if (error == -1)
		{
			throw WSAGetLastError();
		}
	#else
		int flags = fcntl (m_descriptor, F_GETFL, 0);
		if (nonblocking == true)
		{
			flags |= O_NONBLOCK;
		}
		else
		{
			flags &= ~O_NONBLOCK;
		}
		
		int error = fcntl (m_descriptor, F_SETFL, flags);
		if (error == -1)
		{
			throw errno;
		}
	#endif
}

int ListeningSocket :: Accept ()
{
	struct sockaddr_in address;
	
	socklen_t size = sizeof (struct sockaddr);
	return ::accept (m_descriptor, (struct sockaddr *)(&address), &size);
}

void ListeningSocket :: Close ()
{
	#ifdef WIN32
		int error = ::closesocket (m_descriptor);
	#else
		int error = ::close (m_descriptor);
	#endif
	
	if (error == -1)
	{
		throw errno;
	}
	
	m_descriptor = -1;
}

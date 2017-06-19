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

#ifndef LISTENINGSOCKET_HPP_
#define LISTENINGSOCKET_HPP_

	#include "../platform.hpp"
	
	#ifdef WIN32
	
		#include "winsock2.h"
		#include "Ws2tcpip.h"
		
		#ifndef socklen_t
			typedef int socklen_t;
		#endif
	
	#else
	
		#include <sys/socket.h>
		#include <errno.h>
		#include <netinet/in.h>
		#include <fcntl.h>
		#include <strings.h>
	
	#endif
	
	class ListeningSocket
	{
		public:
			
			ListeningSocket ();
			
			void Bind (unsigned short int port);
			
			void Listen ();
			
			void SetNonBlockingFlag (bool value);
			
			int Accept ();
			
			void Close ();
			
			int data () {return m_descriptor;}
			
		private:
			
			int m_descriptor;
	};

#endif /* LISTENINGSOCKET_HPP_ */

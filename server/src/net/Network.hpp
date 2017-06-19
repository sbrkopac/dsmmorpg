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

#ifndef NETWORK_HPP_
#define NETWORK_HPP_

	#include "ListeningSocket.hpp"
	#include "Connection.hpp"
	
	#include <list>
	using std::list;
	
	/*
	 * 
	 */
	class Network
	{
		public:
			
			Network ();
			~Network ();
			
			void Bind (u_int16_t port);
			
			void Listen ();
			
		private:
			
			void Accept ();
			void Receive ();
			
			ListeningSocket m_listening;
			set<int> m_sockets;
			list<Connection> m_connections;
			fd_set m_descriptors;
			fd_set m_active;
			
			#ifdef WIN32
			
				WSADATA m_wsadata;
			
			#else
			
			
			
			#endif
	};
	
	extern Network network;

#endif /* NETWORK_HPP_ */

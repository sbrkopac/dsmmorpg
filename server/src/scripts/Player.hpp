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

#ifndef PLAYER_HPP_
#define PLAYER_HPP_

	#include "../go/Go.hpp"
	
	class Connection;
	
	class Player : public GoScriptComponent
	{
		public:
			
			Player (Connection * connection, Go * go);
			
			void OnGoHandleMessage (const WorldMessage & message);
			
			string Name () const
			{
				return "player";
			}
			
		private:
			
			Connection * m_connection;
	};

#endif /* PLAYER_HPP_ */

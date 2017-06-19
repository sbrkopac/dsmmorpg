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

#ifndef WORLDSTATE_HPP_
#define WORLDSTATE_HPP_

    #include "Packet.hpp"

    class Connection;

    class WorldState
    {
        public:

            WorldState (Connection * client) : m_connection (client) {}

            virtual ~WorldState () {};

            virtual void OnEnter () = 0;

            virtual void Handle (const char * buffer) = 0;

            virtual void OnExit () = 0;

        protected:

            Connection * m_connection;
    };

#endif /* WORLDSTATE_HPP_ */
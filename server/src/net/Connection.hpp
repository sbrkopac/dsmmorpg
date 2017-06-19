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

#ifndef CONNECTION_HPP_
#define CONNECTION_HPP_

    #include "../platform.hpp"
    #include <sys/socket.h>
    #include <errno.h>
    #include <netinet/in.h>
    #include <fcntl.h>

    #include "WorldState.hpp"

    class Connection
    {
        public:

            Connection (int descriptor);

            void SetNonBlockingFlag (bool nonblocking);

            int Send (const char * buffer, int size);
            int Receive ();

            void Close ();

            int data () {return m_descriptor;}

            WorldState * State () const;
            void SetWorldState (WorldState * state);

        private:

            int m_descriptor;
            bool m_connected;
            WorldState * m_state;

            char m_buffer[1024];
    };

#endif /* CONNECTION_HPP_ */
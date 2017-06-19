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

#ifndef PACKET_HPP_
#define PACKET_HPP_

    #include "../platform.hpp"
    #include <netinet/in.h> // endian converting functions
    #include <string> // string type & memcpy

    using namespace std;

    class Packet
    {
        public:

            Packet (); // outgoing packet

            Packet (const char * buffer); // incoming packet

            ~Packet ();

            void WriteUInt32 (u_int32_t data);
            void WriteInt32 (int32_t data);
            void WriteUInt16 (u_int16_t data);
            void WriteInt16 (int16_t data);
            void WriteUInt8 (u_int8_t data);
            void WriteInt8 (int8_t data);
            void WriteFloat (float data);
            void WriteString (const string & buffer);

            u_int32_t ReadUInt32 ();
            int32_t ReadInt32 ();
            u_int16_t ReadUInt16 ();
            int16_t ReadInt16 ();
            u_int8_t ReadUInt8 ();
            int8_t ReadInt8 ();
            float ReadFloat ();
            string ReadString ();

            u_int16_t Size ();
            const char * Data ();

        private:

            void Append (const char * buffer, u_int16_t size);

            u_int16_t m_size;
            u_int16_t m_position;
            char * m_data;
    };

#endif /* PACKET_HPP_ */
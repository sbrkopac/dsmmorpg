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

#ifndef NODE_HPP_
#define NODE_HPP_

    #include "../Log.hpp"
    #include "../platform.hpp"

    class Node
    {
        public:

            Node (u_int32_t id, float x, float y, float z, u_int8_t rotation);

            u_int32_t Id () const;

            float X () const;
            float Y () const;
            float Z () const;

            u_int8_t Rotation () const;

        private:

            u_int32_t m_id;
            float m_x;
            float m_y;
            float m_z;
            u_int8_t m_rotation;
    };

#endif /* NODE_HPP_ */
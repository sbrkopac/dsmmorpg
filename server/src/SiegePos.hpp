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

#ifndef SIEGEPOS_HPP_
#define SIEGEPOS_HPP_

    #include "platform.hpp"

    struct SiegePos
    {
        SiegePos () : Node (0), X (0.0f), Y (0.0f), Z (0.0f) {}

        SiegePos (u_int32_t id, float x, float y, float z) : Node (id), X (x), Y (y), Z (z) {}

        bool IsValid () const {return Node != 0x00000000;}

        u_int32_t Node;
        float X;
        float Y;
        float Z;
    };

#endif /* SIEGEPOS_HPP_ */
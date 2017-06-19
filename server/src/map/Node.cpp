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

#include "Node.hpp"

Node :: Node (u_int32_t id, float x, float y, float z, u_int8_t rotation) : m_id (id), m_x (x), m_y (y), m_z (z), m_rotation (rotation)
{
}

u_int32_t Node :: Id () const
{
    return m_id;
}

float Node :: X () const
{
    return m_x;
}

float Node :: Y () const
{
    return m_y;
}

float Node :: Z () const
{
    return m_z;
}

u_int8_t Node :: Rotation () const
{
    return m_rotation;
}
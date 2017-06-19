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

#include "../Engine.hpp"
#include "WorldMessage.hpp"

WorldMessage :: WorldMessage (eWorldEvent event, Go * from, Go * to, const string & data) : m_WorldEvent (event), m_SendFrom (from), m_SendTo (to), m_Data (data)
{
}

eWorldEvent WorldMessage :: WorldEvent () const
{
    return m_WorldEvent;
}

Go * WorldMessage :: SendFrom () const
{
    return m_SendFrom;
}

Go * WorldMessage :: SendTo () const
{
    return m_SendTo;
}

string WorldMessage :: Data () const
{
    return m_Data;
}

void SendWorldMessage (eWorldEvent event, Go * from, Go * to, const string & data)
{
    engine.HandleWorldMessage (WorldMessage (event, from, to, data));
}

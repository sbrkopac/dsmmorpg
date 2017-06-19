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
#include "SendWorldMessageEvent.hpp"

SendWorldMessageEvent :: SendWorldMessageEvent (eWorldEvent event, Go * from, Go * to, const string & data, int64_t delay) : Event (delay), m_WorldEvent (event), m_SendFrom (from), m_SendTo (to), m_Data (data)
{
}

void SendWorldMessageEvent :: Execute ()
{
	SendWorldMessage (m_WorldEvent, m_SendFrom, m_SendTo, m_Data);
}

void PostWorldMessage (eWorldEvent event, Go * from, Go * to, const string & data, uint64_t delay)
{
	engine.RegisterEvent (new SendWorldMessageEvent (event, from, to, data, CurrentTime() + delay));
}

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

#ifndef WORLDMESSAGE_HPP_
#define WORLDMESSAGE_HPP_

    #include "../enum/eWorldEvent.hpp"

    #include "../platform.hpp"

    #include <string>
    using std::string;

    class WorldMessage
    {
        public:

            WorldMessage (eWorldEvent event, Go * from, Go * to, const string & data);

            eWorldEvent WorldEvent () const;

            Go * SendFrom () const;

            Go * SendTo () const;

            string Data () const;

        private:

            eWorldEvent m_WorldEvent;
            Go * m_SendFrom;
            Go * m_SendTo;
            string m_Data;
    };

    void SendWorldMessage (eWorldEvent event, Go * from, Go * to, const string & data);

#endif /*WORLDMESSAGE_HPP_*/
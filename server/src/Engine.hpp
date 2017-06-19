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

#ifndef ENGINE_HPP_
#define ENGINE_HPP_

    #include <queue>
    #include <vector>
    #include <iostream>
    #include "CurrentTime.hpp"

    #include "map/WorldMap.hpp"

    #include "events/Event.hpp"
    #include "msg/WorldMessage.hpp"

    #include "AIQuery.hpp"

    using namespace std;

    class Engine
    {
        public:

            Engine ();
            ~Engine ();

            bool IsRunning ();

            void Loop ();

            void RegisterEvent (Event * event);

            void HandleWorldMessage (const WorldMessage & message);

        private:

            void MessageKnown (Go * go, const WorldMessage & message);
            void MessageAllPlayers (const WorldMessage & message);

            void AddGoToRegion (Go * go, const string & data);
            void RemoveGoFromRegion (Go * go);

            void CalculateFrustums ();

            bool m_Running;
            priority_queue<Event *, vector<Event *>, EventComparison> m_EventRegistry;

            GopSet m_players;
    };

    extern Engine engine;

#endif /* ENGINE_HPP_ */
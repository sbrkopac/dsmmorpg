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

#ifndef REGION_HPP_
#define REGION_HPP_

    #include "Node.hpp"
    #include "../go/GoDb.hpp"

    #include "../vector_3.hpp"

    #include <cmath>

    class Region
    {
        friend class AIQuery;
        public:

            Region (const string & filename);

            ~Region ();

            GopSet & Objects ();

        private:

            vector_3 MakeLocalPosition (const SiegePos & position);

            double GetSiegeDistance (const SiegePos & position, const SiegePos & destination);

            GopSet m_objects;
            map<u_int32_t, Node *> m_nodes;
    };

#endif /* REGION_HPP_ */
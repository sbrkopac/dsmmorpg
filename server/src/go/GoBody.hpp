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

#ifndef GOBODY_HPP_
#define GOBODY_HPP_

    #include "GoComponent.hpp"

    class GoBody : public GoComponent
    {
        public:

            GoBody (Go * go);
            GoBody (Go * go, xmlNode * node);

            float AvgMoveVelocity () const;
            float MaxMoveVelocity () const;
            float MinMoveVelocity () const;
            void SetAvgMoveVelocity (float velocity);

        private:

            float m_avg_move_velocity;
            float m_max_move_velocity;
            float m_min_move_velocity;
    };

#endif /* GOBODY_HPP_ */
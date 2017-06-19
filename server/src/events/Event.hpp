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

#ifndef EVENT_HPP_
#define EVENT_HPP_

    #include "../CurrentTime.hpp"

    class Event
    {
        public:

            Event (int64_t executiontime) : m_ExecutionTime (executiontime) {}

            virtual ~Event () {};

            int64_t ExecutionTime () const
            {
                return m_ExecutionTime;
            }

            virtual void Execute () = 0;

        private: // protected? need to modify if we have a "load" function?

            int64_t m_ExecutionTime;
    };

    class EventComparison : public std::binary_function<Event *, Event *, bool>
    {
        public:

            bool operator () (const first_argument_type & left, const second_argument_type & right)
            {
                return left->ExecutionTime() > right->ExecutionTime();
            }
    };

#endif /*EVENT_HPP_*/
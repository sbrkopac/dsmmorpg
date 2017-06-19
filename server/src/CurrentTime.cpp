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

#include "CurrentTime.hpp"

#ifdef WIN32

    class Win32Counter
    {
        public:

            Win32Counter ()
            {
                QueryPerformanceFrequency ((LARGE_INTEGER *)(&m_frequency));
                m_frequency = m_frequency / 1000;
            }

            int64_t m_frequency;
    };

    Win32Counter win32counter;

#endif

int64_t CurrentTime ()
{
    #ifdef WIN32

        int64_t s;
        QueryPerformanceCounter ((LARGE_INTEGER *)(&s));

        return s / win32counter.m_frequency;

    #else

        struct timeval tv;
        int64_t s;

        gettimeofday (&tv, 0);

        s = tv.tv_sec;
        s *= 1000;

        s += tv.tv_usec / 1000;

        return s;

    #endif
}
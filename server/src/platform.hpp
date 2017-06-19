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

#ifndef PLATFORM_HPP_
#define PLATFORM_HPP_

    #include <string>
    using std::string;

    #ifdef WIN32

        typedef unsigned char u_int8_t;
        typedef signed char int8_t;
        typedef unsigned short int u_int16_t;
        typedef signed short int int16_t;
        typedef unsigned long int u_int32_t;
        typedef signed long int int32_t;
        typedef unsigned __int64 u_int64_t;
        typedef __int64 int64_t;

        #define bzero(b,len) (memset((b), '\0', (len)), (void) 0)

    #else

        #include <sys/types.h>

    #endif

#endif /* PLATFORM_HPP_ */
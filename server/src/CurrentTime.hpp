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

#ifndef CURRENTTIME_HPP_
#define CURRENTTIME_HPP_

	#include <time.h>
	#include "platform.hpp"
	
	#ifdef WIN32
		#include "windows.h"
	#else
		#include <sys/time.h>
	#endif
	
	int64_t CurrentTime ();

#endif /*CURRENTTIME_HPP_*/
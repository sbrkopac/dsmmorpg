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

#ifndef ELIFESTATE_HPP_
#define ELIFESTATE_HPP_

	#include <string>
	using std::string;
	
	enum eLifeState
	{
		ls_ignore = 0,
		ls_alive_conscious = 1,
		ls_alive_unconscious = 2,
		ls_dead_normal = 3,
		ls_dead_charred = 4,
		ls_decay_fresh = 5,
		ls_decay_bones = 6,
		ls_decay_dust = 7,
		ls_gone = 8,
		ls_ghost = 9,
	};
	
	inline string ToString (eLifeState e)
	{
		switch (e)
		{
			case ls_ignore: return "ls_ignore";
			case ls_alive_conscious: return "ls_alive_conscious";
			case ls_alive_unconscious: return "ls_alive_unconscious";
			case ls_dead_charred: return "ls_dead_charred";
			case ls_decay_fresh: return "ls_decay_fresh";
			case ls_decay_bones: return "ls_decay_bones";
			case ls_decay_dust: return "ls_decay_dust";
			case ls_gone: return "ls_gone";
			case ls_ghost: return "ls_ghost";
			
			default: break;
		} /* switch (e) */
		
		return "";
	}
	
	inline bool FromString (const string & value, eLifeState & e)
	{
		if (value == "ls_ignore")
		{
			e = ls_ignore;
		}
		else if (value == "ls_alive_conscious")
		{
			e = ls_alive_conscious;
		}
		else if (value == "ls_alive_unconscious")
		{
			e = ls_alive_unconscious;
		}
		else if (value == "ls_dead_charred")
		{
			e = ls_dead_charred;
		}
		else if (value == "ls_decay_fresh")
		{
			e = ls_decay_fresh;
		}
		else if (value == "ls_decay_bones")
		{
			e = ls_decay_bones;
		}
		else if (value == "ls_decay_dust")
		{
			e = ls_decay_dust;
		}
		else if (value == "ls_gone")
		{
			e = ls_gone;
		}
		else if (value == "ls_ghost")
		{
			e = ls_ghost;
		}
		else
		{
			return false;
		}
		
		return true;
	}

#endif /* ELIFESTATE_HPP_ */

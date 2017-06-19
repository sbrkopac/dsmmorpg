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

#ifndef GOPLACEMENT_HPP_
#define GOPLACEMENT_HPP_

	#include "GoComponent.hpp"
	#include "../SiegePos.hpp"
	
	class Region;
	
	class GoPlacement : public GoComponent
	{
		public:
			
			GoPlacement (Go * go);
			GoPlacement (Go * go, xmlNode * node);
			
			bool IsDirty () const;
			void MarkAsClean ();
			
			string GetRegion () const;
			void SetRegion (const string & region);
			
			SiegePos Position () const;
			void SetPosition (const SiegePos & position);
			
		private:
			
			bool m_dirty;
			string m_region;
			SiegePos m_position;
	};

#endif /* GOPLACEMENT_HPP_ */

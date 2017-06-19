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

#ifndef GOCOMMON_HPP_
#define GOCOMMON_HPP_

	#include "GoComponent.hpp"
	
	class GoCommon : public GoComponent
	{
		public:
			
			GoCommon (Go * go);
			GoCommon (Go * go, xmlNode * node);
			
			string AutoExpirationClass () const;
			string ForcedExpirationClass () const;
			string ScreenName () const;
			void SetScreenName (const string & name);
			
		private:
			
			string m_auto_expiration_class;
			string m_forced_expiration_class;
			string m_screen_name;
	};

#endif /* GOCOMMON_HPP_ */

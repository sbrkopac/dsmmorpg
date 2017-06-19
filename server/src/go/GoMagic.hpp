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

#ifndef GOMAGIC_HPP_
#define GOMAGIC_HPP_

	#include "GoComponent.hpp"
	
	class GoMagic : public GoComponent
	{
		public:
			
			GoMagic (Go * go);
			GoMagic (Go * go, xmlNode * node);
			
			bool IsCastableOn (Go * go) const;
			bool IsDefensive () const;
			bool IsOffensive () const;
			bool Cast (Go * go);
			float CastRange () const;
			int32_t CastReloadDelay () const;
			u_int8_t CastSubAnimation () const;
			int32_t EffectDuration () const;
			string SkillClass () const;
			
		private:
			
			string m_skill_class;
			float required_level;
			u_int8_t m_cast_sub_animation;
			float m_cast_range;
			int32_t cast_reload_delay;
			int32_t effect_duration;
			bool m_defensive;
			bool m_offensive;
	};

#endif /* GOMAGIC_HPP_ */

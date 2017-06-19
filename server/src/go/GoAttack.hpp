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

#ifndef GOATTACK_HPP_
#define GOATTACK_HPP_

	#include "GoComponent.hpp"
	
	class GoAttack : public GoComponent
	{
		public:
			
			GoAttack (Go * go);
			GoAttack (Go * go, xmlNode * node);
			
			float AttackRange () const;
			float CriticalHitChance () const;
			float DamageMax () const;
			float DamageMin () const;
			bool IsInProjectileRange (const Go * go);
			bool IsTwoHanded () const;
			float ReloadDelay () const;
			
		private:
			
			float m_attack_range;
			float m_critical_hit_chance;
			float m_damage_max;
			float m_damage_min;
			bool m_two_handed;
			int16_t m_reload_delay;
	};

#endif /* GOATTACK_HPP_ */

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

#ifndef GOMIND_HPP_
#define GOMIND_HPP_

	#include "GoComponent.hpp"
	
	#include "../enum/eJobAbstractType.hpp"
	#include "../enum/eEquipSlot.hpp"
	#include "../CurrentTime.hpp"
	#include "../SiegePos.hpp"
	
	class GoMind : public GoComponent
	{
		public:
			
			GoMind (Go * go);
			GoMind (Go * go, xmlNode * node);
			
			int64_t TimeElapsedSinceLastMeleeAttack () const;
			int64_t TimeElapsedSinceLastRangedAttack () const;
			int64_t TimeElapsedSinceLastSpellCast () const;
			
			void Stop ();
			void Move (const SiegePos & position);
			void Get (Go * item);
			void Drop (Go * item);
			void Equip (eEquipSlot slot, Go * item);
			void Unequip (eEquipSlot slot);
			void AttackMelee (Go * target);
			void AttackRanged (Go * target);
			void Cast (Go * target);
			
			void ContinueLastAction ();
			
			eJobAbstractType ActionJat () const;
			SiegePos ActionPosition () const;
			float ActionDistance () const;
			Go * ActionObject () const;
			eEquipSlot ActionSlot () const;
			
		private:
			
			int64_t m_melee;
			int64_t m_ranged;
			int64_t m_casting;
			
			eJobAbstractType m_jat;
			SiegePos m_position;
			float m_distance;
			Go * m_object;
			eEquipSlot m_slot;
	};

#endif /* GOMIND_HPP_ */

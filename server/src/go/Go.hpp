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

#ifndef GO_HPP_
#define GO_HPP_

	#include "../SiegePos.hpp"
	
	#include "GopSet.hpp"
	
	#include "GoActor.hpp"
	#include "GoAspect.hpp"
	#include "GoAttack.hpp"
	#include "GoBody.hpp"
	#include "GoCommon.hpp"
	#include "GoDefend.hpp"
	#include "GoInventory.hpp"
	#include "GoMind.hpp"
	#include "GoPlacement.hpp"
	#include "GoScriptComponent.hpp"
	
	/*
	 * GoActor
	 * GoAspect
	 * GoAttack
	 * GoBody
	 * GoCommon
	 * GoDefend
	 * GoGui
	 * GoInventory
	 * GoMagic
	 * GoMind
	 * GoParty
	 * GoPlacement
	 */
	
	struct sqlResult; // temp until sql implemented
	
	class Go
	{
		public:
			
			Go (xmlNode * node); // ONLY USED FOR CREATING NEW TEMPLATES
			Go (sqlResult * query); // only used for loading a 'save game'
			Go (u_int32_t id, const Go * go); // used for creating a new go from either [an existing go, or a template]
			~Go ();
			
			GoActor * Actor () const;
			void AddChild (Go * child);
			GoAspect * Aspect () const;
			GoAttack * Attack () const;
			GoBody * Body () const;
			const GopSet & Children () const;
			void ClearParent ();
			GoCommon * Common () const;
			// GoConversation * Conversation () const;
			GoDefend * Defend () const;
			const GopSet & Frustum ();
			GoScriptComponent * GetComponent (const string & component) const;
			u_int32_t Goid () const;
			// GoGui * Gui () const;
			bool HasActor () const;
			bool HasAspect () const;
			bool HasAttack () const;
			bool HasBody () const;
			bool HasChild (Go * child) const;
			bool HasCommon () const;
			bool HasComponent (const string & component) const;
			bool HasConversation () const; // code me
			bool HasDefend () const;
			bool HasGui () const; // code me
			bool HasInventory () const;
			bool HasMagic () const; // has magic
			bool HasMind () const;
			// bool HasParty () const; 
			bool HasPlacement () const;
			GoInventory * Inventory () const;
			bool IsActor () const;
			// bool IsAnyHumanPartyMember () const;
			bool IsArmor () const;
			bool IsBreakable () const; // code me
			bool IsContainer () const; // code me
			bool IsEquipped () const;
			bool IsGhost () const; // code me!
			bool IsInsideInventory () const;
			bool IsItem () const;
			bool IsMeleeWeapon () const;
			bool IsRangedWeapon () const;
			bool IsSpell () const; // code me
			bool IsSpellBook () const; // code me
			bool IsTeamMember (const Go * go) const; // code me
			bool IsWeapon () const;
			eLifeState LifeState () const;
			// GoMagic * Magic () const;
			GoMind * Mind () const;
			Go * Parent () const;
			GoPlacement * Placement () const;
			void RemoveAllChildren ();
			void RemoveChild (Go * child);
			void Send (const WorldMessage & message);
			void SetParent (Go * parent);
			// void SetPlayer( const PlayerId * ) ??????
			string TemplateName () const;
			
			
			// depreciate please
			void AddComponent (GoScriptComponent * component);
			void RemoveComponent (const string & component);
			
		private:
			
			u_int32_t m_goid;
			string m_template_name;
			
			GopSet m_objects;
			
			Go * m_parent;
			GopSet m_children;
			
			GoActor * m_actor;
			GoAspect * m_aspect;
			GoAttack * m_attack;
			GoBody * m_body;
			GoCommon * m_common;
			GoDefend * m_defend;
			GoInventory * m_inventory;
			GoMind * m_mind;
			GoPlacement * m_placement;
			
			map<string, GoScriptComponent*> m_scripts;
	};

#endif /* GO_HPP_ */

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

#include "GoDb.hpp"
#include "GoInventory.hpp"

#include "../map/WorldMap.hpp"
#include "../msg/WorldMessage.hpp"

GoInventory :: GoInventory (Go * go) : GoComponent (go)
{
	/*
	GopSet::iterator iterator = m_go->Inventory()->m_inventory.begin();
	while (iterator != m_go->Inventory()->m_inventory.end())
	{
		Go * item = *iterator;
		
		Go * clone = NULL;
		if (item->TemplateName() != "")
		{
			clone = godb.CloneGo (item->TemplateName());
		}
		else
		{
			clone = godb.CloneGo (*item);
		}
		
		if (clone)
		{
			m_inventory.insert (clone);
			// SendWorldMessage (we_entered_world, copy->Id(), copy->Id(), "");
		}
		
		iterator++;
	}
	*/
}

GoInventory :: GoInventory (Go * go, xmlNode * node) : GoComponent (go)
{
	if (node != NULL)
	{
		xmlNode * current = NULL;
		for (current = node->children; current != NULL; current = current->next)
		{
			if (current->type != XML_ELEMENT_NODE) continue;
			
			if (xmlStrEqual (current->name, (const xmlChar *) "item") != 0)
			{
				string template_name = xml::ReadAttribute<string> (current, "template_name", "");
				u_int32_t id = xml::ReadAttribute<u_int32_t> (current, "id", 0);
				
				if (id != 0)
				{
					//Goid g (id);
					// add g to our inventory :)
				}
				else if (template_name != "")
				{
					// Go * item = godb.CloneGo (template_name);
					// add item to our inventory :)
				}
			}
		}
	}
}

bool GoInventory :: Add (Go * item)
{
	if (item != NULL)
	{
		if (Contains (item) != true)
		{
			/*
			 * check if we can actually add this item
			 */
			
			m_inventory.insert (item);
			
			item->SetParent (m_go);
			m_go->AddChild (item);
			
			return true;
		}
	}
	
	return false;
}

bool GoInventory :: Contains (const Go * item) const
{
	if (item != NULL)
	{
		GopSet::const_iterator iterator = m_inventory.find ((Go *)item);
		return iterator != m_inventory.end();
	}
	
	return false;
}

bool GoInventory :: Equip (eEquipSlot slot, Go * item)
{
	if (IsSlotEquipped (slot) != false)
	{
		return false;
	}
	
	if (IsEquipped (item) != false)
	{
		return false;
	}
	
	if (Contains (item) != true)
	{
		return false;
	}
	
	if (item != NULL)
	{
		/*
		 * check if we can actually equip this item
		 */
		
		m_equipment[slot] = item;
		
		return true;
	}
	
	return false;
}

Go * GoInventory :: GetEquipped (eEquipSlot slot) const
{
	map<eEquipSlot, Go *>::const_iterator iterator = m_equipment.find (slot);
	return iterator != m_equipment.end() ? iterator->second : NULL;
}

eEquipSlot GoInventory :: GetEquippedSlot (const Go * item) const
{
	if  (item != NULL)
	{
		map<eEquipSlot, Go *>::const_iterator iterator = m_equipment.begin();
		while (iterator != m_equipment.end())
		{
			if (iterator->second->Goid() == item->Goid())
			{
				return iterator->first;
			}
			
			iterator++;
		}
	}
	
	return es_none;
}

bool GoInventory :: IsAnyWeaponEquipped () const
{
	Go * item;
	
	item = GetEquipped (es_shield_hand);
	if (item != NULL)
	{
		if (item->IsWeapon())
		{
			return true;
		}
	}
	
	item = GetEquipped (es_shield_hand);
	if (item != NULL)
	{
		if (item->IsWeapon())
		{
			return true;
		}
	}
	
	return false;
}

bool GoInventory :: IsEquipped (const Go * item) const
{
	if  (item != NULL)
	{
		map<eEquipSlot, Go *>::const_iterator iterator = m_equipment.begin();
		while (iterator != m_equipment.end())
		{
			if (iterator->second->Goid() == item->Goid())
			{
				return true;
			}
			
			iterator++;
		}
	}
	
	return false;
}

bool GoInventory :: IsMeleeWeaponEquipped () const
{
	Go * item;
	
	item = GetEquipped (es_shield_hand);
	if (item != NULL)
	{
		if (item->IsMeleeWeapon())
		{
			return true;
		}
	}
	
	item = GetEquipped (es_shield_hand);
	if (item != NULL)
	{
		if (item->IsMeleeWeapon())
		{
			return true;
		}
	}
	
	return false;
}

bool GoInventory :: IsRangedWeaponEquipped () const
{
	Go * item;
	
	item = GetEquipped (es_shield_hand);
	if (item != NULL)
	{
		if (item->IsRangedWeapon())
		{
			return true;
		}
	}
	
	item = GetEquipped (es_shield_hand);
	if (item != NULL)
	{
		if (item->IsRangedWeapon())
		{
			return true;
		}
	}
	
	return false;
}

bool GoInventory :: IsSlotEquipped (eEquipSlot slot) const
{
	map<eEquipSlot, Go *>::const_iterator iterator = m_equipment.find (slot);
	return iterator != m_equipment.end();
}

const GopSet & GoInventory :: ListItems () const
{
	return m_inventory;
}

bool GoInventory :: Remove (Go * item)
{
	if (item != NULL)
	{
		if (Contains (item) != false)
		{
			/*
			 * check if we can actually remove this item 
			 */
			
			m_inventory.erase (item);
			
			item->ClearParent();
			m_go->RemoveChild (item);
			
			return true;
		}
	}
	
	return false;
}

bool GoInventory :: Unequip (eEquipSlot slot)
{
	map<eEquipSlot, Go *>::iterator iterator = m_equipment.find (slot);
	if (iterator != m_equipment.end())
	{
		/*
		 * check if we can actually unequip this item
		 */
		
		m_equipment.erase (iterator);
		
		return true;
	}
	
	return false;
}

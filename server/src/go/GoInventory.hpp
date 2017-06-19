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

#ifndef GOINVENTORY_HPP_
#define GOINVENTORY_HPP_

    #include "../enum/eEquipSlot.hpp"
    #include "GoComponent.hpp"

    #include <map>
    using std::map;

    #include <set>
    using std::set;

    class GoInventory : public GoComponent
    {
        public:

            GoInventory (Go * go);
            GoInventory (Go * go, xmlNode * node);

            bool Add (Go * item);
            bool Contains (const Go * item) const;
            bool Equip (eEquipSlot slot, Go * item);
            Go * GetEquipped (eEquipSlot slot) const;
            eEquipSlot GetEquippedSlot (const Go * item) const;
            bool IsAnyWeaponEquipped () const;
            bool IsEquipped (const Go * item) const;
            bool IsMeleeWeaponEquipped () const;
            bool IsRangedWeaponEquipped () const;
            bool IsSlotEquipped (eEquipSlot slot) const;
            const GopSet & ListItems () const;
            bool Remove (Go * item);
            bool Unequip (eEquipSlot slot);

        private:

            GopSet m_inventory;
            map<eEquipSlot, Go *> m_equipment;
    };

#endif /* GOINVENTORY_HPP_ */
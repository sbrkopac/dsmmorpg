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

#ifndef EEQUIPSLOT_HPP_
#define EEQUIPSLOT_HPP_

    #include <string>
    using std::string;

    enum eEquipSlot
    {
        es_shield_hand = 0,
        es_weapon_hand = 1,
        es_feet = 2,
        es_chest = 3,
        es_head = 4,
        es_forearms = 5,
        es_amulet = 6,
        es_spellbook = 7,
        es_ring_0 = 8,
        es_ring_1 = 9,
        es_ring_2 = 10,
        es_ring_3 = 11,
        es_ring = 12,
        es_none = 13,
        es_any = 14,
    };

    inline string ToString (eEquipSlot e)
    {
        switch (e)
        {
            case es_shield_hand: return "es_shield_hand";
            case es_weapon_hand: return "es_weapon_hand";
            case es_feet: return "es_feet";
            case es_chest: return "es_chest";
            case es_head: return "es_head";
            case es_forearms: return "es_forearms";
            case es_amulet: return "es_amulet";
            case es_ring_0: return "es_ring_0";
            case es_ring_1: return "es_ring_1";
            case es_ring_2: return "es_ring_2";
            case es_ring_3: return "es_ring_3";
            case es_ring: return "es_ring";
            case es_none: return "es_none";
            case es_any: return "es_any";

            default: break;
        } /* switch (e) */

        return "";
    }

#endif /* EEQUIPSLOT_HPP_ */
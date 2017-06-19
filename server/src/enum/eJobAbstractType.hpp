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

#ifndef EJOBABSTRACTTYPE_HPP_
#define EJOBABSTRACTTYPE_HPP_

    enum eJobAbstractType
    {
        jat_none = 0,
        jat_attack,
        jat_attack_position,
        jat_cast,
        jat_cast_position,
        jat_brain,
        jat_die,
        jat_drink,
        jat_drop,
        jat_equip,
        jat_unequip,
        jat_get,
        jat_give,
        jat_move,
        jat_use,

        jat_attack_object_melee,
        jat_attack_object_ranged,
        jat_approach, // O RLY?
    };

#endif /* EJOBABSTRACTTYPE_HPP_ */
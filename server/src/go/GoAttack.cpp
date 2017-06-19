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

#include "Go.hpp"
#include "../AIQuery.hpp"
#include "GoAttack.hpp"

GoAttack :: GoAttack (Go * go) : GoComponent (go)
{
}

GoAttack :: GoAttack (Go * go, xmlNode * node) : GoComponent (go)
{
    if (node != NULL)
    {
        xmlNode * current = NULL;
        for (current = node->children; current != NULL; current = current->next)
        {
            if (current->type != XML_ELEMENT_NODE) continue;

            if (xmlStrEqual (current->name, (const xmlChar *) "attack_range") != 0)
            {
                m_attack_range = xml::ReadAttribute<float> (current, "value", 1.0);
            }
            else if (xmlStrEqual (current->name, (const xmlChar *) "critical_hit_chance") != 0)
            {
                m_critical_hit_chance = xml::ReadAttribute<float> (current, "value", 0.0);
            }
            else if (xmlStrEqual (current->name, (const xmlChar *) "damage_max") != 0)
            {
                m_damage_max = xml::ReadAttribute<float> (current, "value", 0.0);
            }
            else if (xmlStrEqual (current->name, (const xmlChar *) "damage_min") != 0)
            {
                m_damage_min = xml::ReadAttribute (current, "value", 0.0);
            }
            else if (xmlStrEqual (current->name, (const xmlChar *) "is_two_handed") != 0)
            {
                m_two_handed = xml::ReadAttribute<int16_t> (current, "value", false);
            }
            else if (xmlStrEqual (current->name, (const xmlChar *) "reload_delay") != 0)
            {
                m_reload_delay = xml::ReadAttribute<int16_t> (current, "value", 1000);
            }
        }
    }
}

float GoAttack :: AttackRange () const
{
    return m_attack_range;
}

float GoAttack :: CriticalHitChance () const
{
    return m_critical_hit_chance;
}

float GoAttack :: DamageMax () const
{
    return m_damage_max;
}

float GoAttack :: DamageMin () const
{
    return m_damage_min;
}

bool GoAttack :: IsInProjectileRange (const Go * go)
{
    return query.IsInRange (m_go, go, m_attack_range);
}

bool GoAttack :: IsTwoHanded () const
{
    return m_two_handed;
}

float GoAttack :: ReloadDelay () const
{
    return m_reload_delay;
}
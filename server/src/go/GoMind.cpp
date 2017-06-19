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
#include "GoMind.hpp"

#include "../AIQuery.hpp"

#include <iostream>
using namespace std;

GoMind :: GoMind (Go * go) : GoComponent (go)
{
    m_melee = 0;
}

GoMind :: GoMind (Go * go, xmlNode * node) : GoComponent (go)
{
    m_melee = 0;
}

int64_t GoMind :: TimeElapsedSinceLastMeleeAttack () const
{
    return m_melee;
}

void GoMind :: Stop ()
{
    m_jat = jat_none;
    m_position = m_go->Placement()->Position();
    m_distance = 0.0f;
    m_object = NULL;
    m_slot = es_none;
}

void GoMind :: Move (const SiegePos & position)
{
    m_jat = jat_move;
    m_position = position;
    m_distance = 0.0f;
    m_object = NULL;
    m_slot = es_none;

    SendWorldMessage (we_mind_processing_new_job, m_go, m_go, "jat_move");
}

void GoMind :: Get (Go * item)
{
    if (item != NULL)
    {
        if (m_go->Inventory()->Contains(item) != true)
        {
            if (query.IsInRange (m_go, item, 2.5f))
            {
                m_jat = jat_get;
                m_position = m_go->Placement()->Position();
                m_distance = 0.0f;
                m_object = item;
                m_slot = es_none;

                SendWorldMessage (we_mind_processing_new_job, m_go, item, "jat_get");

                Stop();
            }
            else
            {
                m_jat = jat_get;
                m_position = item->Placement()->Position();
                m_distance = 2.0f;
                m_object = item;
                m_slot = es_none;

                SendWorldMessage (we_mind_processing_new_job, m_go, item, "jat_approach");
            }

            return;
        }
    }

    Stop();
}

void GoMind :: Drop (Go * item)
{
    if (item != NULL)
    {
        if (m_go->Inventory()->Contains (item))
        {
            if (m_go->Inventory()->IsEquipped (item))
            {
                m_jat = jat_drop;
                m_position = m_go->Placement()->Position();
                m_distance = 0.0f;
                m_object = item;
                m_slot = m_go->Inventory()->GetEquippedSlot (item);

                SendWorldMessage (we_mind_processing_new_job, m_go, item, "jat_unequip");

                ContinueLastAction();
            }
            else
            {
                m_jat = jat_drop;
                m_position = m_go->Placement()->Position();
                m_distance = 0.0f;
                m_object = item;
                m_slot = es_none;

                SendWorldMessage (we_mind_processing_new_job, m_go, item, "jat_drop");

                Stop();
            }

            return;
        }
    }

    Stop();
}

void GoMind :: Equip (eEquipSlot slot, Go * item)
{
    if (item != NULL)
    {
        if (slot != es_none)
        {
            if (m_go->Inventory()->Contains (item))
            {
                Go * existing = m_go->Inventory()->GetEquipped (slot);
                if (m_go->Inventory()->IsEquipped (item))
                {
                    cout << "eww 1" << endl;
                    m_jat = jat_equip;
                    m_position = m_go->Placement()->Position();
                    m_distance = 0.0f;
                    m_object = item;
                    m_slot = m_go->Inventory()->GetEquippedSlot (item);

                    SendWorldMessage (we_mind_processing_new_job, m_go, item, "jat_unequip");

                    ContinueLastAction();
                }
                else if (existing != NULL)
                {
                    cout << "eww 2" << endl;
                    m_jat = jat_equip;
                    m_position = m_go->Placement()->Position();
                    m_distance = 0.0f;
                    m_object = item;
                    m_slot = slot;

                    SendWorldMessage (we_mind_processing_new_job, m_go, existing, "jat_unequip");

                    ContinueLastAction();
                }
                else
                {
                    m_jat = jat_equip;
                    m_position = m_go->Placement()->Position();
                    m_distance = 0.0f;
                    m_object = item;
                    m_slot = slot;

                    SendWorldMessage (we_mind_processing_new_job, m_go, item, "jat_equip");

                    Stop();
                }

                return;
            }
        }
    }

    Stop();
}

void GoMind :: Unequip (eEquipSlot slot)
{
    Go * item = m_go->Inventory()->GetEquipped (slot);
    if (item != NULL)
    {
        m_jat = jat_unequip;
        m_position = m_go->Placement()->Position();
        m_distance = 0.0f;
        m_object = item;
        m_slot = slot;

        SendWorldMessage (we_mind_processing_new_job, m_go, item, "jat_unequip");
    }

    Stop();
}

void GoMind :: AttackMelee (Go * target)
{
    if (target != NULL)
    {
        int64_t now = CurrentTime();
        {
            if (query.IsInRange (m_go, target, 2.5f))
            {
                m_jat = jat_attack_object_melee;
                m_position = m_go->Placement()->Position();
                m_distance = 0.0f;
                m_object = target;
                m_slot = es_none;

                SendWorldMessage (we_mind_processing_new_job, m_go, target, "jat_attack_object_melee");

                m_melee = now;
            }
            else
            {
                m_jat = jat_attack_object_melee;
                m_position = target->Placement()->Position();
                m_distance = 2.4f;
                m_object = target;
                m_slot = es_none;

                SendWorldMessage (we_mind_processing_new_job, m_go, target, "jat_approach");
            }
        }

        return;
    }

    Stop();
}

void GoMind :: AttackRanged (Go * target)
{
    if (target != NULL)
    {
        int64_t now = CurrentTime();
        {
            if (query.IsInRange (m_go, target, 12.5f))
            {
                m_jat = jat_attack_object_ranged;
                m_position = m_go->Placement()->Position();
                m_distance = 0.0f;
                m_object = target;
                m_slot = es_none;

                SendWorldMessage (we_mind_processing_new_job, m_go, target, "jat_attack_object_ranged");

                m_ranged = now;
            }
            else
            {
                m_jat = jat_attack_object_ranged;
                m_position = target->Placement()->Position();
                m_distance = 12.4f;
                m_object = target;
                m_slot = es_none;

                SendWorldMessage (we_mind_processing_new_job, m_go, target, "jat_approach");
            }
        }

        return;
    }

    Stop();
}

void GoMind :: ContinueLastAction ()
{
    switch (m_jat)
    {
        case jat_get:
        {
            if (m_object != NULL)
            {
                Get (m_object);
            }
        }
        break;

        case jat_drop:
        {
            if (m_object != NULL)
            {
                Drop (m_object);
            }
        }
        break;

        case jat_equip:
        {
            if (m_object != NULL && m_slot != es_none)
            {
                Equip (m_slot, m_object);
            }
        }
        break;

        case jat_attack_object_melee:
        {
            if (m_object != NULL)
            {
                AttackMelee (m_object);
            }
        }
        break;

        case jat_attack_object_ranged:
        {
            if (m_object != NULL)
            {
                AttackRanged (m_object);
            }
        }
        break;

        default: break;
    } /* switch (m_jat) */
}

eJobAbstractType GoMind :: ActionJat () const
{
    return m_jat;
}

SiegePos GoMind :: ActionPosition () const
{
    return m_position;
}

float GoMind :: ActionDistance () const
{
    return m_distance;
}

Go * GoMind :: ActionObject () const
{
    return m_object;
}

eEquipSlot GoMind :: ActionSlot () const
{
    return m_slot;
}
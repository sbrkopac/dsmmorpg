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

#include "Player.hpp"
#include "../net/packets.hpp"
#include "../net/Connection.hpp"

#include <iostream>
using namespace std;

Player :: Player (Connection * connection, Go * go) : GoScriptComponent (go), m_connection (connection)
{
}

void Player :: OnGoHandleMessage (const WorldMessage & message)
{
    // cout << "recevied event " << ToString (message.WorldEvent()) << " from " << message.SendFrom() << " to " << message.SendTo() << endl;
    eWorldEvent event = message.WorldEvent();
    Go * from = message.SendFrom();
    Go * to = message.SendTo();

    switch (event)
    {
        case we_entered_world:
        {
            if (from->HasCommon())
            {
                string message = from->Common()->ScreenName() + " has entered the world";

                Packet packet;
                packet.WriteUInt8 (RCDISPLAYMESSAGE);
                packet.WriteString (message);

                m_connection->Send (packet.Data(), packet.Size());
            }
        }
        break;

        case we_left_world:
        {
            if (from->HasCommon())
            {
                string message = from->Common()->ScreenName() + " has left the world";

                Packet packet;
                packet.WriteUInt8 (RCDISPLAYMESSAGE);
                packet.WriteString (message);

                m_connection->Send (packet.Data(), packet.Size());
            }
        }
        break;

        case we_entered_frustum:
        {
            if (from->IsActor())
            {
                Packet packet;
                packet.WriteUInt8 (RCCREATEACTOR);
                packet.WriteUInt32 (from->Goid());
                packet.WriteString (from->Common()->ScreenName());
                packet.WriteString (from->Aspect()->Model());
                packet.WriteUInt8 (from->Actor()->Alignment());
                packet.WriteFloat (from->Aspect()->RenderScale());
                packet.WriteString (from->Aspect()->GetDynamicTexture (0));
                packet.WriteString (from->Aspect()->GetDynamicTexture (1));
                packet.WriteUInt32 (from->Placement()->Position().Node);
                packet.WriteFloat (from->Placement()->Position().X);
                packet.WriteFloat (from->Placement()->Position().Y);
                packet.WriteFloat (from->Placement()->Position().Z);

                for (int i = 0; i < 12; i++)
                {
                    Go * equipment = from->Inventory()->GetEquipped ((eEquipSlot) i);

                    if (equipment != NULL)
                    {
                        packet.WriteUInt32 (equipment->Goid());
                        packet.WriteString (equipment->Aspect()->Model());
                    }
                    else
                    {
                        packet.WriteUInt32 (0);
                        packet.WriteUInt8 (0);
                    }
                }

                m_connection->Send (packet.Data(), packet.Size());

                return;
            }

            if (from->IsItem())
            {
                Packet packet;
                packet.WriteUInt8 (RCCREATEITEM);
                packet.WriteUInt32 (from->Goid());
                packet.WriteString (from->Common()->ScreenName());
                packet.WriteString (from->Aspect()->Model());
                packet.WriteUInt32 (from->Placement()->Position().Node);
                packet.WriteFloat (from->Placement()->Position().X);
                packet.WriteFloat (from->Placement()->Position().Y);
                packet.WriteFloat (from->Placement()->Position().Z);

                m_connection->Send (packet.Data(), packet.Size());

                return;
            }
        }
        break;

        case we_left_frustum:
        {
            if (from != NULL)
            {
                Packet packet;
                packet.WriteUInt8 (RCDESTROYGO);
                packet.WriteUInt32 (from->Goid());

                m_connection->Send (packet.Data(), packet.Size());
            }
        }
        break;

        case we_player_changed:
        {
            if (to->IsActor())
            {
                Packet packet;
                packet.WriteUInt8 (RCSETSCREENHERO);
                packet.WriteUInt32 (to->Goid());

                // stats
                packet.WriteFloat (to->Actor()->GetSkillLevel("strength"));
                packet.WriteFloat (to->Actor()->GetSkillLevel("intelligence"));
                packet.WriteFloat (to->Actor()->GetSkillLevel("dexterity"));
                packet.WriteFloat (to->Actor()->GetSkillLevel("melee"));
                packet.WriteFloat (to->Actor()->GetSkillLevel("ranged"));
                packet.WriteFloat (to->Actor()->GetSkillLevel("nature magic"));
                packet.WriteFloat (to->Actor()->GetSkillLevel("combat magic"));

                // inventory
                const GopSet & inventory = to->Inventory()->ListItems();
                packet.WriteUInt8 (inventory.size());
                for (GopSet::const_iterator iterator = inventory.begin(); iterator != inventory.end(); iterator++)
                {
                    Go * item = *iterator;
                    eEquipSlot slot = to->Inventory()->GetEquippedSlot (item);

                    packet.WriteUInt32 (item->Goid());
                    packet.WriteString (item->Common()->ScreenName());
                    packet.WriteUInt8 (slot);
                    packet.WriteString (item->Aspect()->Model());
                }

                m_connection->Send (packet.Data(), packet.Size());
            }
        }
        break;

        case we_req_talk:
        {
            if (from != NULL)
            {
                Packet packet;
                if (to->HasCommon())
                {
                    string msg = "<" + from->Common()->ScreenName() + "> : " + message.Data();
                    packet.WriteUInt8 (RCDISPLAYMESSAGE);
                    packet.WriteString (msg);
                }

                m_connection->Send (packet.Data(), packet.Size());
            }
        }
        break;

        case we_picked_up:
        {
            if (to->IsItem())
            {
                Packet packet;
                packet.WriteUInt8 (RCGET);
                packet.WriteUInt32 (to->Goid());
                packet.WriteString (to->Common()->ScreenName());
                packet.WriteString (to->Aspect()->Model());

                m_connection->Send (packet.Data(), packet.Size());
            }
        }
        break;

        case we_dropped:
        {
            if (to->IsItem())
            {
                Packet packet;
                packet.WriteUInt8 (RCDROP);
                packet.WriteUInt32 (to->Goid());

                m_connection->Send (packet.Data(), packet.Size());
            }
        }
        break;

        case we_engaged_hit_lived:
        {
            //cout << "player heard we_engaged_hit" << endl;

            eJobAbstractType jat = from->Mind()->ActionJat();
            if (jat == jat_attack_object_melee)
            {
                Packet packet;
                packet.WriteUInt8 (RCATTACKMELEE);
                packet.WriteUInt32 (from->Goid());
                packet.WriteUInt32 (to->Goid());
                packet.WriteUInt8 (1);

                m_connection->Send (packet.Data(), packet.Size());
            }

            else if (jat == jat_attack_object_ranged)
            {
                Packet packet;
                packet.WriteUInt8 (RCATTACKRANGED);
                packet.WriteUInt32 (from->Goid());
                packet.WriteUInt32 (to->Goid());
                packet.WriteUInt8 (1);

                m_connection->Send (packet.Data(), packet.Size());
            }
        }
        break;

        case we_engaged_missed:
        {
            //cout << "player heard we_engaged_missed" << endl;

            eJobAbstractType jat = from->Mind()->ActionJat();
            if (jat == jat_attack_object_melee)
            {
                Packet packet;
                packet.WriteUInt8 (RCATTACKMELEE);
                packet.WriteUInt32 (from->Goid());
                packet.WriteUInt32 (to->Goid());
                packet.WriteUInt8 (2);

                m_connection->Send (packet.Data(), packet.Size());
            }

            else if (jat == jat_attack_object_ranged)
            {
                Packet packet;
                packet.WriteUInt8 (RCATTACKRANGED);
                packet.WriteUInt32 (from->Goid());
                packet.WriteUInt32 (to->Goid());
                packet.WriteUInt8 (2);

                m_connection->Send (packet.Data(), packet.Size());
            }
        }
        break;

        case we_mind_processing_new_job:
        {
            if (from->HasMind())
            {
                string job = message.Data();

                if (job == "jat_move")
                {
                    SiegePos destination = from->Mind()->ActionPosition();

                    Packet packet;
                    packet.WriteUInt8 (RCMOVE);
                    packet.WriteUInt32 (from->Goid());
                    packet.WriteUInt32 (destination.Node);
                    packet.WriteFloat (destination.X);
                    packet.WriteFloat (destination.Y);
                    packet.WriteFloat (destination.Z);

                    m_connection->Send (packet.Data(), packet.Size());
                }

                else if (job == "jat_approach")
                {
                    SiegePos destination = from->Mind()->ActionPosition();
                    float distance = from->Mind()->ActionDistance();

                    Packet packet;
                    packet.WriteUInt8 (RCAPPROACH);
                    packet.WriteUInt32 (from->Goid());
                    packet.WriteUInt32 (destination.Node);
                    packet.WriteFloat (destination.X);
                    packet.WriteFloat (destination.Y);
                    packet.WriteFloat (destination.Z);
                    packet.WriteFloat (distance);

                    m_connection->Send (packet.Data(), packet.Size());
                }

                else if (job == "jat_equip")
                {
                    eEquipSlot slot = from->Mind()->ActionSlot();

                    Packet packet;
                    packet.WriteUInt8 (RCEQUIP);
                    packet.WriteUInt32 (from->Goid());
                    packet.WriteUInt8 (slot);
                    packet.WriteUInt32 (to->Goid());
                    packet.WriteString (to->Aspect()->Model());

                    m_connection->Send (packet.Data(), packet.Size());
                }

                else if (job == "jat_unequip")
                {
                    eEquipSlot slot = from->Mind()->ActionSlot();

                    Packet packet;
                    packet.WriteUInt8 (RCUNEQUIP);
                    packet.WriteUInt32 (from->Goid());
                    packet.WriteUInt8 (slot);

                    m_connection->Send (packet.Data(), packet.Size());
                }
            }
        }
        break;

        default: break;
    } /* switch (event) */

}
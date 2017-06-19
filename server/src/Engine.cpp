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

#include "Engine.hpp"
#include "events/SendWorldMessageEvent.hpp"

Engine engine;

Engine :: Engine ()
{
    m_Running = true;
}

Engine :: ~Engine ()
{
    while (m_EventRegistry.size())
    {
        Event * event = m_EventRegistry.top();
        delete event;
        m_EventRegistry.pop();
    }
}

bool Engine :: IsRunning ()
{
    return m_Running;
}

void Engine :: Loop ()
{
    int64_t current = CurrentTime();

    while (m_EventRegistry.size() > 0 && m_EventRegistry.top()->ExecutionTime() <= current)
    {
        Event * event = m_EventRegistry.top();
        m_EventRegistry.pop();

        try
        {
            event->Execute();
        }
        catch (...)
        {
        }

        delete event;
    }
}

void Engine :: RegisterEvent (Event * event)
{
    m_EventRegistry.push (event);
}

void Engine :: HandleWorldMessage (const WorldMessage & message)
{
    eWorldEvent event = message.WorldEvent();
    Go * from = message.SendFrom();
    Go * to = message.SendTo();

    switch (event)
    {
        case we_entered_world:
        {
            if (from->HasPlacement())
            {
                if (message.Data().empty() != true)
                {
                    AddGoToRegion (from, message.Data());
                }
            }
        }
        break;

        case we_left_world:
        {
            if (from->HasPlacement())
            {
                if (from->Placement()->GetRegion().empty() != true)
                {
                    RemoveGoFromRegion (from);
                }
            }
        }
        break;

        case we_entered_frustum:
        {
            if (from->HasPlacement() && to->HasPlacement())
            {
                from->Send (WorldMessage (we_entered_frustum, to, from, ""));
                if (from->Goid() != to->Goid())
                {
                    to->Send (WorldMessage (we_entered_frustum, from, to, ""));
                }
            }
        }
        break;

        case we_left_frustum:
        {
            if (from->HasPlacement() && to->HasPlacement())
            {
                from->Send (WorldMessage (we_left_frustum, to, from, ""));
                if (from->Goid() != to->Goid())
                {
                    to->Send (WorldMessage (we_left_frustum, from, to, ""));
                }
            }
        }
        break;

        case we_picked_up:
        {
            if (from->HasInventory() && to->IsItem())
            {
                string region = to->Placement()->GetRegion();
                if (region.empty() != true)
                {
                    RemoveGoFromRegion (to);
                }

                to->Send (message); // scripting event
                from->Send (message);
            }
        }
        break;

        case we_dropped:
        {
            if (from->HasInventory() && to->IsItem())
            {
                string region = from->Placement()->GetRegion();
                if (region.empty() != true)
                {
                    to->Placement()->SetPosition (from->Placement()->Position());
                    AddGoToRegion (to, region);
                }

                to->Send (message); // scripting event
                from->Send (message);
            }
        }
        break;

        case we_equipped:
        {
            if (from->IsActor() && to->IsItem())
            {
                to->Send (message); // scripting event
                from->Send (message);
            }
        }
        break;

        case we_unequipped:
        {
            if (from->IsActor() && to->IsItem())
            {
                to->Send (message); // scripting event
                from->Send (message);
            }
        }
        break;

        case we_req_talk:
        {
            MessageKnown (from, message);
        }
        break;

        case we_engaged_hit_lived:
        {
            MessageKnown (from, message);
            // scripting
        }
        break;

        case we_engaged_missed:
        {
            MessageKnown (from, message);
            // scripting
        }
        break;

        case we_mind_processing_new_job:
        {
            string job = message.Data();

            if (job == "")
            {
                from->Mind()->ContinueLastAction();
            }

            else if (job == "jat_move")
            {
                // if canLeaveCurrentRegion (from) && canEnterNextRegion (from)
                MessageKnown (from, message);
            }

            else if (job == "jat_approach")
            {
                MessageKnown (from, message);
            }

            else if (job == "jat_get")
            {
                if (from->IsActor() && to->IsItem())
                {
                    if (from->Inventory()->Add (to))
                    {
                        HandleWorldMessage (WorldMessage (we_picked_up, from, to, ""));
                    }
                    else
                    {
                        from->Mind()->Stop();
                    }
                }
            }

            else if (job == "jat_drop")
            {
                if (from->IsActor() && to->IsItem())
                {
                    if (from->Inventory()->Remove (to))
                    {
                        HandleWorldMessage (WorldMessage (we_dropped, from, to, ""));
                    }
                    else
                    {
                        from->Mind()->Stop();
                    }
                }
            }

            else if (job == "jat_equip")
            {
                if (from->IsActor() && to->IsItem())
                {
                    eEquipSlot slot = from->Mind()->ActionSlot();
                    if (from->Inventory()->Equip (slot, to))
                    {
                        MessageKnown (from, message);
                        HandleWorldMessage (WorldMessage (we_equipped, from, to, ""));
                    }
                    else
                    {
                        from->Mind()->Stop();
                    }
                }
            }

            else if (job == "jat_unequip")
            {
                if (from->IsActor() && to->IsItem())
                {
                    eEquipSlot slot = from->Mind()->ActionSlot();
                    cout << "engine says unequip " << to->Goid() << " from " << slot << endl;
                    if (from->Inventory()->Unequip (slot))
                    {
                        cout << "successfully unequipped" << endl;
                        MessageKnown (from, message);
                        HandleWorldMessage (WorldMessage (we_unequipped, from, to, ""));
                    }
                    else
                    {
                        from->Mind()->Stop();
                    }
                }
            }

            else if (job == "jat_attack_object_melee")
            {
                if (from->IsActor() && to->IsActor()) // fix me!
                {
                    int rnd = rand() % 10 + 1;
                    if (rnd <= 8)
                    {
                        float hp = to->Aspect()->CurrentLife();

                        int dmg = rand() % 10 + 1;

                        hp -= (float) dmg;

                        if (hp <= 0.0)
                        {
                            // we_engaged_hit_killed
                            cout << "killed, rezzing" << endl;
                            hp = to->Aspect()->MaxLife();
                            HandleWorldMessage (WorldMessage (we_engaged_hit_lived, from, to, ""));
                        }
                        else
                        {
                            HandleWorldMessage (WorldMessage (we_engaged_hit_lived, from, to, ""));

                            PostWorldMessage (we_mind_processing_new_job, from, to, "", 2510);
                        }
                    }
                    else
                    {
                        HandleWorldMessage (WorldMessage (we_engaged_missed, from, to, ""));

                        PostWorldMessage (we_mind_processing_new_job, from, to, "", 2510);
                    }
                }
            }

            else if (job == "jat_attack_object_ranged")
            {
                if (from->IsActor() && to->IsActor()) // fix me!
                {
                    int rnd = rand() % 10 + 1;
                    if (rnd <= 8)
                    {
                        float hp = to->Aspect()->CurrentLife();

                        int dmg = rand() % 10 + 1;

                        hp -= (float) dmg;

                        if (hp <= 0.0)
                        {
                            // we_engaged_hit_killed
                            cout << "killed, rezzing" << endl;
                            hp = to->Aspect()->MaxLife();
                            HandleWorldMessage (WorldMessage (we_engaged_hit_lived, from, to, ""));
                        }
                        else
                        {
                            HandleWorldMessage (WorldMessage (we_engaged_hit_lived, from, to, ""));

                            PostWorldMessage (we_mind_processing_new_job, from, to, "", 4510);
                        }
                    }
                    else
                    {
                        HandleWorldMessage (WorldMessage (we_engaged_missed, from, to, ""));

                        PostWorldMessage (we_mind_processing_new_job, from, to, "", 4510);
                    }
                }
            }
        }
        break;

        case we_frustum_active_state_changed:
        {
            CalculateFrustums ();

            PostWorldMessage (we_frustum_active_state_changed, NULL, NULL, "", 1000);
        }
        break;

        default: break;
    } /* switch (event) */
}

void Engine :: MessageKnown (Go * go, const WorldMessage & message)
{
    if (go != NULL)
    {
        const GopSet & frustum = go->Frustum();
        for (GopSet::const_iterator iterator = frustum.begin(); iterator != frustum.end(); iterator++)
        {
            (*iterator)->Send (message);
        }
    }
}

void Engine :: MessageAllPlayers (const WorldMessage & message)
{
    for (GopSet::iterator iterator = m_players.begin(); iterator != m_players.end(); iterator++)
    {
        (*iterator)->Send (message);
    }
}

void Engine :: AddGoToRegion (Go * go, const string & data)
{
    Region * region;
    if (go != NULL)
    {
        if (data.empty() != true)
        {
            try
            {
                region = world.GetRegion (data);
                go->Placement()->SetRegion (data);
            }
            catch (exception & e)
            {
                // log a useful error
                return;
            }

            GopSet & available = region->Objects();
            available.insert (go);

            for (GopSet::iterator iterator = available.begin(); iterator != available.end(); iterator++)
            {
                Go * object = *iterator;

                if (query.IsInRange (go, object, 45.0))
                {
                    HandleWorldMessage (WorldMessage (we_entered_frustum, go, object, ""));
                }
            }

            if (go->HasComponent ("player"))
            {
                /*
                if (region->Players().size() == 1)
                {
                    world.Regions().insert (region);
                }
                */
            }
        }
    }
}

void Engine :: RemoveGoFromRegion (Go * go)
{
    Region * region;
    if (go != NULL)
    {
        try
        {
            region = world.GetRegion (go->Placement()->GetRegion());
            go->Placement()->SetRegion ("");
        }
        catch (exception & e)
        {
            // log useful error
            return;
        }

        GopSet & available = region->Objects();
        available.erase (go);

        const GopSet & frustum = go->Frustum();
        for (GopSet::const_iterator iterator = frustum.begin(); iterator != frustum.end(); iterator++)
        {
            HandleWorldMessage (WorldMessage (we_left_frustum, go, *iterator, ""));
        }

        if (go->HasComponent ("player"))
        {
            /*
            if (region->Players().size() == 0)
            {
                world.Regions().erase (region);
            }
            */
        }
    }
}

void Engine :: CalculateFrustums ()
{
    set<Region *> & regions = world.Regions();
    for (set<Region *>::iterator iterator = regions.begin(); iterator != regions.end(); iterator++)
    {
        Region * region = *iterator;

        GopSet & objects = region->Objects();

        GopSet::iterator i = objects.begin();
        while (i != objects.end())
        {
            Go * object = *i;

            GopSet::iterator j = i++;

            while (j != objects.end())
            {
                Go * go = *j;

                if (go->Placement()->IsDirty())
                {
                    if (go->Goid() != object->Goid())
                    {
                        //cout << go->Id() << " is grinding " << object->Id() << endl;
                        bool is_in_frustum = object->Frustum().find (go) != object->Frustum().end();
                        bool should_be_in_frustum = query.IsInRange (go, object, 45.0);

                        if (is_in_frustum == true && should_be_in_frustum == false)
                        {
                            HandleWorldMessage (WorldMessage (we_left_frustum, object, go, ""));
                        }
                        else if (is_in_frustum == false && should_be_in_frustum == true)
                        {
                            HandleWorldMessage (WorldMessage (we_entered_frustum, object, go, ""));
                        }
                    }
                }

                j++;
            }

            object->Placement()->MarkAsClean();
        }
    }

    //cout << "resolving frustums @ " << CurrentTime() << endl;
}
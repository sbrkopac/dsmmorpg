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

#include "../map/WorldMap.hpp"
#include "../scripts/test_script.hpp"
#include <sys/types.h>

Go :: Go (xmlNode * node) : m_parent (NULL), m_actor (NULL), m_aspect (NULL), m_attack (NULL), m_body (NULL), m_common (NULL), m_defend (NULL), m_inventory (NULL), m_mind (NULL), m_placement (NULL)
{
    if (node != NULL)
    {
        m_goid = xml::ReadAttribute<u_int32_t> (node, "id", 0);
        m_template_name = xml::ReadAttribute<string> (node, "template_name", "");

        xmlNode * current = NULL;
        for (current = node->children; current != NULL; current = current->next)
        {
            if (current->type != XML_ELEMENT_NODE) continue;

            if (xmlStrEqual (current->name, (const xmlChar *) "actor") != 0)
            {
                if (m_actor == NULL) m_actor = new GoActor (this, current);
            }
            else if (xmlStrEqual (current->name, (const xmlChar *) "aspect") != 0)
            {
                if (m_aspect == NULL) m_aspect = new GoAspect (this, current);
            }
            else if (xmlStrEqual (current->name, (const xmlChar *) "attack") != 0)
            {
                if (m_attack == NULL) m_attack = new GoAttack (this, current);
            }
            else if (xmlStrEqual (current->name, (const xmlChar *) "body") != 0)
            {
                if (m_body == NULL) m_body = new GoBody (this, current);
            }
            else if (xmlStrEqual (current->name, (const xmlChar *) "common") != 0)
            {
                if (m_common == NULL) m_common = new GoCommon (this, current);
            }
            else if (xmlStrEqual (current->name, (const xmlChar *) "defend") != 0)
            {
                if (m_defend == NULL) m_defend = new GoDefend (this, current);
            }
            else if (xmlStrEqual (current->name, (const xmlChar *) "inventory") != 0)
            {
                if (m_inventory == NULL) m_inventory = new GoInventory (this, current);
            }
            else if (xmlStrEqual (current->name, (const xmlChar *) "mind") != 0)
            {
                if (m_mind == NULL) m_mind = new GoMind (this, current);
            }
            else if (xmlStrEqual (current->name, (const xmlChar *) "placement") != 0)
            {
                if (m_placement == NULL) m_placement = new GoPlacement (this, current);
            }
            else if (xmlStrEqual (current->name, (const xmlChar *) "scripts") != 0)
            {
                xmlNode * a = NULL;
                for (a = current->children; a != NULL; a = a->next)
                {
                    if (a->type != XML_ELEMENT_NODE) continue;

                    // cout << "found name = " << a->name << endl;

                    if (xmlStrEqual (a->name, (const xmlChar *) "test_script") != 0)
                    {
                        // add class test_script to m_scripts
                        map<string, GoScriptComponent *>::iterator iterator = m_scripts.find ("test_script");
                        if (iterator == m_scripts.end())
                        {
                            m_scripts["test_script"] = new test_script (this);
                        }
                    }
                }
            }
        }
    }
}

Go :: Go (u_int32_t id, const Go * go) : m_parent (NULL), m_actor (NULL), m_aspect (NULL), m_attack (NULL), m_body (NULL), m_common (NULL), m_defend (NULL), m_inventory (NULL), m_placement (NULL)
{
    m_goid = id;
    m_template_name = go->m_template_name;

    if (go->m_actor != NULL) m_actor = new GoActor (this);
    if (go->m_aspect != NULL) m_aspect = new GoAspect (this);
    if (go->m_attack != NULL) m_attack = new GoAttack (this);
    if (go->m_body != NULL) m_body = new GoBody (this);
    if (go->m_common != NULL) m_common = new GoCommon (this);
    if (go->m_defend != NULL) m_defend = new GoDefend (this);
    if (go->m_inventory != NULL) m_inventory = new GoInventory (this);
    if (go->m_mind != NULL) m_mind = new GoMind (this);
    if (go->m_placement != NULL) m_placement = new GoPlacement (this);
}

Go :: ~Go ()
{
    if (m_actor) delete m_actor;
    if (m_aspect) delete m_aspect;
    if (m_attack) delete m_attack;
    if (m_body) delete m_body;
    if (m_common) delete m_common;
    if (m_defend) delete m_defend;
    if (m_inventory) delete m_inventory;
    if (m_mind) delete m_mind;
    if (m_placement) delete m_placement;

    map<string, GoScriptComponent *>::iterator iterator = m_scripts.begin();
    while (iterator != m_scripts.end())
    {
        delete iterator->second;
    }
}

void Go :: AddChild (Go * child)
{
    if (child != NULL)
    {
        m_children.insert (child);
    }
}

GoBody * Go :: Body () const
{
    if (m_body != NULL)
    {
        return m_body;
    }

    throw logic_error ("null pointer referenced");
}

void Go :: ClearParent ()
{
    m_parent = NULL;
}

GoScriptComponent * Go :: GetComponent (const string & component) const
{
    map<string, GoScriptComponent *>::const_iterator iterator = m_scripts.find (component);
    if (iterator != m_scripts.end())
    {
        return iterator->second;
    }

    throw logic_error ("null pointer referenced");
}

bool Go :: HasActor () const
{
    return m_actor != NULL;
}

bool Go :: HasAspect () const
{
    return m_aspect != NULL;
}

bool Go :: HasAttack () const
{
    return m_aspect != NULL;
}

bool Go :: HasBody () const
{
    return m_body != NULL;
}

bool Go :: HasChild (Go * child) const
{
    GopSet::const_iterator iterator = m_children.find (child);
    return iterator != m_children.end();
}

bool Go :: HasCommon () const
{
    return m_common != NULL;
}

bool Go :: HasComponent (const string & component) const
{
    map<string, GoScriptComponent *>::const_iterator iterator = m_scripts.find (component);
    return iterator != m_scripts.end();
}

bool Go :: HasConversation () const
{
    return false;
}

bool Go :: HasDefend () const
{
    return m_defend != NULL;
}

bool Go :: HasGui () const
{
    return false;
}

bool Go :: HasInventory () const
{
    return m_inventory != NULL;
}

bool Go :: HasMagic () const
{
    return false;
}

bool Go :: HasMind () const
{
    return m_mind != NULL;
}

bool Go :: HasPlacement () const
{
    return m_placement != NULL;
}

bool Go :: IsActor () const
{
    return m_actor != NULL && m_aspect != NULL && m_common != NULL && m_mind != NULL && m_placement != NULL;
}

bool Go :: IsArmor () const
{
    return m_actor == NULL && m_aspect != NULL && m_common != NULL && m_defend != NULL && m_mind == NULL && m_placement != NULL;
}

bool Go :: IsBreakable () const
{
    return false;
}

bool Go :: IsContainer () const
{
    return false;
}

bool Go :: IsEquipped () const
{
    if (m_parent != NULL)
    {
        return m_parent->Inventory()->IsEquipped (this);
    }

    return false;
}

bool Go :: IsGhost () const
{
    return false;
}

bool Go :: IsInsideInventory () const
{
    if (m_parent != NULL)
    {
        return m_parent->Inventory()->Contains (this);
    }

    return false;
}

bool Go :: IsItem () const
{
    return m_actor == NULL && m_aspect != NULL && m_common != NULL && m_mind == NULL && m_placement != NULL;
}

bool Go :: IsMeleeWeapon () const
{
    if (m_attack != NULL)
    {
        //return m_attack->IsMelee();
    }

    return false;
}

bool Go :: IsRangedWeapon () const
{
    if (m_attack != NULL)
    {
        //return m_attack->IsRanged();
    }

    return false;
}

bool Go :: IsSpell () const
{
    return false;
}

bool Go :: IsSpellBook () const
{
    return false;
}

bool Go :: IsTeamMember (const Go * go) const
{
    return false;
}

bool Go :: IsWeapon () const
{
    return m_actor == NULL && m_aspect != NULL && m_attack != NULL && m_common != NULL && m_mind == NULL && m_placement != NULL;
}

void Go :: RemoveAllChildren ()
{
    m_children.clear();
}

void Go :: RemoveChild (Go * child)
{
    if (child != NULL)
    {
        m_children.erase (child);
    }
}

void Go :: Send (const WorldMessage & message)
{
    eWorldEvent event = message.WorldEvent();
    Go * from = message.SendFrom();

    switch (event)
    {
        case we_entered_frustum:
        {
            if (from != NULL)
            {
                m_objects.insert (from);
            }
        }
        break;

        case we_left_frustum:
        {
            if (from != NULL)
            {
                m_objects.erase (from);
            }
        }
        break;

        default: break;
    } /* switch (event) */

    for (map<string, GoScriptComponent *>::iterator iterator = m_scripts.begin(); iterator != m_scripts.end(); iterator++)
    {
        GoScriptComponent * script = iterator->second;
        script->OnGoHandleMessage (message);
    }
}

void Go :: SetParent (Go * parent)
{
    if (parent != NULL)
    {
        m_parent = parent;
    }
}

GoActor * Go :: Actor () const
{
    if (m_actor != NULL)
    {
        return m_actor;
    }

    throw logic_error ("null pointer referenced");
}

GoAspect * Go :: Aspect () const
{
    if (m_aspect != NULL)
    {
        return m_aspect;
    }

    throw logic_error ("null pointer referenced");
}

GoAttack * Go :: Attack () const
{
    if (m_attack != NULL)
    {
        return m_attack;
    }

    throw logic_error ("null pointer referenced");
}

const GopSet & Go :: Children () const
{
    return m_children;
}

GoCommon * Go :: Common () const
{
    if (m_common != NULL)
    {
        return m_common;
    }

    throw logic_error ("null pointer referenced");
}

GoDefend * Go :: Defend () const
{
    if (m_defend != NULL)
    {
        return m_defend;
    }

    throw logic_error ("null pointer referenced");
}

u_int32_t Go :: Goid () const
{
    return m_goid;
}

GoInventory * Go :: Inventory () const
{
    if (m_inventory != NULL)
    {
        return m_inventory;
    }

    throw logic_error ("null pointer referenced");
}

eLifeState Go :: LifeState () const
{
    if (m_aspect != NULL)
    {
        return m_aspect->LifeState();
    }

    return ls_ignore;
}

GoMind * Go :: Mind () const
{
    if (m_mind != NULL)
    {
        return m_mind;
    }

    throw logic_error ("null pointer referenced");
}

Go * Go :: Parent () const
{
    if (m_parent != NULL)
    {
        return m_parent;
    }

    throw logic_error ("null pointer referenced");
}

GoPlacement * Go :: Placement () const
{
    if (m_placement != NULL)
    {
        return m_placement;
    }

    throw logic_error ("null pointer referenced");
}

string Go :: TemplateName () const
{
    return m_template_name;
}

const GopSet & Go :: Frustum ()
{
    return m_objects;
}

void Go :: AddComponent (GoScriptComponent * component)
{
    if (component != NULL)
    {
        if (component->Name().empty() != true)
        {
            map<string, GoScriptComponent *>::iterator iterator = m_scripts.find (component->Name());
            if (iterator == m_scripts.end())
            {
                m_scripts[component->Name()] = component;
            }
        }
    }
}

void Go :: RemoveComponent (const string & component)
{
    map<string, GoScriptComponent *>::iterator iterator = m_scripts.find (component);
    if (iterator != m_scripts.end())
    {
        m_scripts.erase (iterator);
    }
}
/*
int Go :: GetComponentInt (const string & component, const string & property)
{
    map<string, GoScriptComponent *>::iterator iterator = m_scripts.find (component);
    if (iterator != m_scripts.end())
    {
        GoScriptComponent * script = iterator->second;
        return script->GetComponentInt (property);
    }

    return 0;
}

float Go :: GetComponentFloat (const string & component, const string & property)
{
    map<string, GoScriptComponent *>::iterator iterator = m_scripts.find (component);
    if (iterator != m_scripts.end())
    {
        GoScriptComponent * script = iterator->second;
        return script->GetComponentFloat (property);
    }

    return 0.0f;
}

bool Go :: GetComponentBool (const string & component, const string & property)
{
    map<string, GoScriptComponent *>::iterator iterator = m_scripts.find (component);
    if (iterator != m_scripts.end())
    {
        GoScriptComponent * script = iterator->second;
        return script->GetComponentBool (property);
    }

    return false;
}

string Go :: GetComponentString (const string & component, const string & property)
{
    map<string, GoScriptComponent *>::iterator iterator = m_scripts.find (component);
    if (iterator != m_scripts.end())
    {
        GoScriptComponent * script = iterator->second;
        return script->GetComponentString (property);
    }

    return "";
}

void Go :: SetComponentInt (const string & component, const string & property, int value)
{
    map<string, GoScriptComponent*>::iterator iterator = m_scripts.find (component);
    if (iterator != m_scripts.end())
    {
        GoScriptComponent * script = iterator->second;
        script->SetComponentInt (property, value);
    }
}

void Go :: SetComponentFloat (const string & component, const string & property, float value)
{
    map<string, GoScriptComponent *>::iterator iterator = m_scripts.find (component);
    if (iterator != m_scripts.end())
    {
        GoScriptComponent * script = iterator->second;
        script->SetComponentFloat (property, value);
    }
}

void Go :: SetComponentBool (const string & component, const string & property, bool value)
{
    map<string, GoScriptComponent *>::iterator iterator = m_scripts.find (component);
    if (iterator != m_scripts.end())
    {
        GoScriptComponent * script = iterator->second;
        script->SetComponentBool (property, value);
    }
}

void Go :: SetComponentString (const string & component, const string & property, const string & value)
{
    map<string, GoScriptComponent *>::iterator iterator = m_scripts.find (component);
    if (iterator != m_scripts.end())
    {
        GoScriptComponent * script = iterator->second;
        script->SetComponentString (property, value);
    }
}
*/
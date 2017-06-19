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
#include "GoPlacement.hpp"

GoPlacement :: GoPlacement (Go * go) : GoComponent (go)
{
    m_region = go->Placement()->m_region;
    m_position.Node = go->Placement()->m_position.Node;
    m_position.X = go->Placement()->m_position.X;
    m_position.Y = go->Placement()->m_position.Y;
    m_position.Z = go->Placement()->m_position.Z;
}

GoPlacement :: GoPlacement (Go * go, xmlNode * node) : GoComponent (go)
{
    if (node != NULL)
    {
        m_region = xml::ReadAttribute<string> (node, "region", "");

        xmlNode * current = NULL;
        for (current = node->children; current != NULL; current = current->next)
        {
            if (current->type != XML_ELEMENT_NODE) continue;

            if (xmlStrEqual (current->name, (const xmlChar *) "position") != 0)
            {
                m_position.Node = xml::ReadAttribute<u_int32_t> (current, "node", 0);
                m_position.X = xml::ReadAttribute<float> (current, "x", 0.0f);
                m_position.Y = xml::ReadAttribute<float> (current, "y", 0.0f);
                m_position.Z = xml::ReadAttribute<float> (current, "z", 0.0f);
            }
        }
    }
}

bool GoPlacement :: IsDirty () const
{
    return m_dirty;
}

void GoPlacement :: MarkAsClean ()
{
    m_dirty = false;
}

string GoPlacement :: GetRegion () const
{
    return m_region;
}

void GoPlacement :: SetRegion (const string & region)
{
    m_region = region;
}

SiegePos GoPlacement :: Position () const
{
    return m_position;
}

void GoPlacement :: SetPosition (const SiegePos & position)
{
    m_dirty = true;
    m_position = position;
}
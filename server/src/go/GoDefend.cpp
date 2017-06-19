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

#include "GoDefend.hpp"

GoDefend :: GoDefend (Go * go) : GoComponent (go)
{
}

GoDefend :: GoDefend (Go * go, xmlNode * node) : GoComponent (go)
{
    if (node != NULL)
    {
        xmlNode * current = NULL;
        for (current = node->children; current != NULL; current = current->next)
        {
            if (current->type != XML_ELEMENT_NODE) continue;

            if (xmlStrEqual (current->name, (const xmlChar *) "defense") != 0)
            {
                m_defense = xml::ReadAttribute<float> (current, "value", 1.0);
            }
        }
    }
}

float GoDefend :: Defense () const
{
    return m_defense;
}
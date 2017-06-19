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
#include "GoCommon.hpp"

GoCommon :: GoCommon (Go * go) : GoComponent (go)
{
}

GoCommon :: GoCommon (Go * go, xmlNode * node) : GoComponent (go)
{
    if (node != NULL)
    {
        xmlNode * current = NULL;
        for (current = node->children; current != NULL; current = current->next)
        {
            if (current->type != XML_ELEMENT_NODE) continue;

            if (xmlStrEqual (current->name, (const xmlChar *) "auto_expiration_class") != 0)
            {
                m_auto_expiration_class = xml::XReadString (current, "value", "");
            }
            else if (xmlStrEqual (current->name, (const xmlChar *) "forced_expiration_class") != 0)
            {
                m_forced_expiration_class = xml::XReadString (current, "value", "");
            }
            else if (xmlStrEqual (current->name, (const xmlChar *) "screen_name") != 0)
            {
                m_screen_name = xml::XReadString (current, "value", "");
            }
        }
    }
}

string GoCommon :: AutoExpirationClass () const
{
    return m_auto_expiration_class;
}

string GoCommon :: ForcedExpirationClass () const
{
    return m_forced_expiration_class;
}

string GoCommon :: ScreenName () const
{
    return m_screen_name;
}

void GoCommon :: SetScreenName (const string & name)
{
    m_screen_name = name;
}
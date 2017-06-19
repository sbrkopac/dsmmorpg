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

#include "GoDb.hpp"
#include "../Engine.hpp"

GoDb godb;

GoDb :: GoDb ()
{
}

GoDb :: ~GoDb ()
{
    {map<u_int32_t, Go *>::iterator iterator = m_godb.begin();
    while (iterator != m_godb.end())
    {
        delete iterator->second;
        iterator++;
    }}

    {map<string, Go *>::iterator iterator = m_contentdb.begin();
    while (iterator != m_contentdb.end())
    {
        delete iterator->second;
        iterator++;
    }}
}

void GoDb :: LoadGoDb (const string & filename)
{
    xmlDoc * document = xmlReadFile (filename.c_str(), NULL, 0);
    if (document == NULL)
    {
        throw runtime_error ("file does not exist");
    }

    xmlNode * root = xmlDocGetRootElement (document);
    if (root == NULL)
    {
        xmlFree (document);
        throw runtime_error ("file is not valid xml");
    }

    xmlNode * node = NULL;
    for (node = root->children; node != NULL; node = node->next)
    {
        if (node->type != XML_ELEMENT_NODE) continue;

        if (xmlStrEqual (node->name, (const xmlChar *) "go") != 0)
        {
            u_int32_t id = xml::ReadAttribute<u_int32_t> (node, "id", 0);

            map<u_int32_t, Go *>::iterator iterator = m_godb.find (id);
            if (iterator != m_godb.end())
            {
                throw runtime_error ("go already exists in godb");
            }

            if (id != 0)
            {
                try
                {
                    Go * t = new Go (node);
                    m_godb[id] = t;

                    if (t->HasPlacement())
                    {
                        string region = t->Placement()->GetRegion();
                        if (region.empty() != true)
                        {
                            SendWorldMessage (we_entered_world, t, t, region);
                        }
                    }
                }
                catch (exception & e)
                {
                    logger.WriteF ("go %u was not loaded because : %s", id, e.what());
                }
            }
        }
    }

    xmlFreeDoc (document);
}

void GoDb :: LoadContentDb (const string & filename)
{
    xmlDoc * document = xmlReadFile (filename.c_str(), NULL, 0);
    if (document == NULL)
    {
        throw runtime_error ("file does not exist");
    }

    xmlNode * root = xmlDocGetRootElement (document);
    if (root == NULL)
    {
        xmlFree (document);
        throw runtime_error ("file is not valid xml");
    }

    xmlNode * node = NULL;
    for (node = root->children; node != NULL; node = node->next)
    {
        if (node->type != XML_ELEMENT_NODE) continue;

        if (xmlStrEqual (node->name, (const xmlChar *) "template") != 0)
        {
            string name = xml::ReadAttribute<string> (node, "template_name", "");

            map<string, Go *>::iterator iterator = m_contentdb.find (name);
            if (iterator != m_contentdb.end())
            {
                throw runtime_error ("template already exists in contentdb");
            }

            if (name.empty() != true)
            {
                try
                {
                    Go * t = new Go (node);
                    m_contentdb[name] = t;
                }
                catch (exception & e)
                {
                    logger.WriteF ("template %s was not loaded because : %s", name.c_str(), e.what());
                }
            }
        }
    }

    xmlFreeDoc (document);
}

Go * GoDb :: FindGoById (u_int32_t id)
{
    if (id == 0)
    {
        return NULL;
    }

    map<u_int32_t, Go *>::iterator iterator = m_godb.find (id);
    return iterator != m_godb.end() ? iterator->second : NULL;
}

Go * GoDb :: CloneGo (const Go * go)
{
    u_int32_t id = NextId();

    Go * clone = new Go (id, go);
    m_godb[id] = clone;

    return clone;
}

Go * GoDb :: CloneGo (const string & template_name)
{
    map<string, Go *>::iterator iterator = m_contentdb.find (template_name);
    if (iterator != m_contentdb.end())
    {
        u_int32_t id = NextId();

        Go * go = new Go (id, iterator->second);
        m_godb[id] = go;

        return go;
    }

    return NULL;
}

void GoDb :: MarkGoForDeletion (u_int32_t id)
{
    map<u_int32_t, Go *>::iterator iterator = m_godb.find (id);

    if (iterator != m_godb.end())
    {
        delete iterator->second;
        m_godb.erase (iterator);
    }
}

void GoDb :: MarkGoAndChildrenForDeletion (u_int32_t id)
{
    // temporary
    MarkGoForDeletion (id);
}

u_int32_t GoDb::NextId()
{
    if (m_godb.size() == 0)
    {
        return 1;
    }

    if (m_godb.size() == m_godb.rbegin()->first)
    {
        return m_godb.size() + 1;
    }

    u_int32_t open = 0;
    u_int32_t previous = 0;
    map<u_int32_t, Go *>::iterator iterator = m_godb.begin();

    while (!open)
    {
        if (iterator->first != previous + 1)
        {
            open = previous + 1;
        }
        else
        {
            previous = iterator->first;
        }

        ++iterator;
    }

    return open;
}
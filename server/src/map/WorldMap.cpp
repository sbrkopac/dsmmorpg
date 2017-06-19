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

#include "WorldMap.hpp"

WorldMap world;

WorldMap :: ~WorldMap ()
{
    map<string, Region *>::iterator iterator = m_regions.begin();
    while (iterator != m_regions.end())
    {
        delete iterator->second;
        iterator++;
    }
}

void WorldMap :: LoadMap (const string & filename)
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

        if (xmlStrEqual (node->name, (const xmlChar *) "region") != 0)
        {
            string name = xml::ReadAttribute<string> (node, "name", "");
            string description = xml::ReadAttribute<string> (node, "description", "");
            string filename = xml::ReadAttribute<string> (node, "filename", "");

            map<string, Region *>::iterator iterator = m_regions.find (name);
            if (iterator != m_regions.end())
            {
                throw runtime_error ("region already exists in this map");
            }

            if (name.empty() != true)
            {
                try
                {
                    Region * region = new Region (filename);
                    m_regions[name] = region;
                    m_active.insert (region);
                }
                catch (exception & e)
                {
                    logger.WriteF ("region %s was not loaded because : %s", name.c_str(), e.what());
                }
            }
        }
    }

    xmlFreeDoc (document);
}

Region * WorldMap :: GetRegion (const string & name)
{
    map<string, Region *>::iterator iterator = m_regions.find (name);
    if (iterator != m_regions.end())
    {
        return iterator->second;
    }

    throw range_error ("region does not exist in this map");
}
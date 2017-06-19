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

#include "Region.hpp"

Region :: Region (const string & filename)
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
		
		if (xmlStrEqual (node->name, (const xmlChar *) "node") != 0)
		{
			u_int32_t id = xml::ReadAttribute<u_int32_t> (node, "id", 0);
			float x = xml::ReadAttribute<float> (node, "x", 0.0f);
			float y = xml::ReadAttribute<float> (node, "y", 0.f);
			float z = xml::ReadAttribute<float> (node, "z", 0.0f);
			u_int8_t rotation = xml::ReadAttribute<int> (node, "rotation", 0);
			
			map<u_int32_t, Node *>::iterator iterator = m_nodes.find (id);
			if (iterator != m_nodes.end())
			{
				throw runtime_error ("node already exists in this region");
			}
			
			if (id != 0)
			{
				Node * node = new Node (id, x, y, z, rotation);
				m_nodes[id] = node;
			}
		}
	}
	
	xmlFreeDoc (document);
}

Region :: ~Region ()
{
	map<u_int32_t, Node *>::iterator iterator = m_nodes.begin();
	while (iterator != m_nodes.end())
	{
		delete iterator->second;
	}
}

GopSet & Region :: Objects ()
{
	return m_objects;
}
/*
set<Player *> & Region :: Players ()
{
	return m_players;
}
*/
vector_3 Region :: MakeLocalPosition (const SiegePos & position)
{
	map<u_int32_t, Node *>::iterator iterator = m_nodes.find (position.Node);
	if (iterator != m_nodes.end())
	{
		Node * node = iterator->second;
		
		vector_3 local;
		local.x = node->X();
		local.y = node->Y();
		local.z = node->Z();
		
		int rotation = node->Rotation();
		switch (rotation)
		{
			case 1:
			{
				local.x -= position.X;
				local.z += position.Z;
			}
			break;
			
			case 2:
			{
				local.x += position.Z;
				local.z += position.X;
			}
			break;
			
			case 3:
			{
				local.x += position.X;
				local.z -= position.Z;
			}
			break;
			
			case 4:
			{
				local.x += position.Z;
				local.z -= position.X;
			}
			break;
			
			default:
			{
				throw runtime_error ("invalid node");
			}
			break;
		} /* switch (rotation) */
		
		return local;
	}
	
	throw range_error ("node does not exist in this region");
}

double Region :: GetSiegeDistance (const SiegePos & position, const SiegePos & destination)
{
	vector_3 p;
	vector_3 d;
	
	try
	{
		p = MakeLocalPosition (position);
		d = MakeLocalPosition (destination);
	}
	catch (exception & e)
	{
		logger.WriteF ("caught an exception while calling GetSiegeDistance : %s", e.what());
		return 0.0;
	}
	 
	double x = p.x - d.x;
	double y = p.y - d.y;
	double z = p.z - d.z;
	
	return sqrt (x * x + y * y + z * z);
}

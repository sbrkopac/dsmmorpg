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

#include "GoScriptComponent.hpp"

GoScriptComponent :: GoScriptComponent (Go * go) : GoComponent (go)
{
}

/*
int GoScriptComponent :: GetComponentInt (const string & property)
{
	map<string, int>::iterator iterator = m_integers.find (property);
	return iterator != m_integers.end() ? iterator->second : 0;
}

float GoScriptComponent :: GetComponentFloat (const string & property)
{
	map<string, float>::iterator iterator = m_floats.find (property);
	return iterator != m_floats.end() ? iterator->second : 0.0f;
}

bool GoScriptComponent :: GetComponentBool (const string & property)
{
	map<string, bool>::iterator iterator = m_booleans.find (property);
	return iterator != m_booleans.end() ? iterator->second : false;
}

string GoScriptComponent :: GetComponentString (const string & property)
{
	map<string, string>::iterator iterator = m_strings.find (property);
	return iterator != m_strings.end() ? iterator->second : "";
}

void GoScriptComponent :: SetComponentInt (const string & property, int value)
{
	m_integers[property] = value;
}

void GoScriptComponent :: SetComponentFloat (const string & property, float value)
{
	m_floats[property] = value;
}

void GoScriptComponent :: SetComponentBool (const string & property, bool value)
{
	m_booleans[property] = value;
}

void GoScriptComponent :: SetComponentString (const string & property, const string & value)
{
	m_strings[property] = value;
}
*/

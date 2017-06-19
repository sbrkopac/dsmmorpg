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
#include "GoAspect.hpp"

GoAspect :: GoAspect (Go * go) : GoComponent (go)
{
	//m_model = go->Aspect()->m_model;
}

GoAspect :: GoAspect (Go * go, xmlNode * node) : GoComponent (go)
{
	if (node != NULL)
	{
		xmlNode * current = NULL;
		for (current = node->children; current != NULL; current = current->next)
		{
			if (current->type != XML_ELEMENT_NODE) continue;
			
			if (xmlStrEqual (current->name, (const xmlChar *) "bounding_sphere_radius") != 0)
			{
				m_bounding_sphere_radius = xml::ReadAttribute<float> (current, "value", 0.0);
			}
			else if (xmlStrEqual (current->name, (const xmlChar *) "current_life") != 0)
			{
				m_current_life = xml::ReadAttribute<float> (current, "value", 0.0);
			}
			else if (xmlStrEqual (current->name, (const xmlChar *) "current_mana") != 0)
			{
				m_current_mana = xml::ReadAttribute<float> (current, "value", 0.0);
			}
			else if (xmlStrEqual (current->name, (const xmlChar *) "flesh") != 0)
			{
				m_textures[0] = xml::XReadString (current, "value", "");
			}
			else if (xmlStrEqual (current->name, (const xmlChar *) "cloth") != 0)
			{
				m_textures[1] = xml::XReadString (current, "value", "");
			}
			else if (xmlStrEqual (current->name, (const xmlChar *) "is_invincible") != 0)
			{
				m_invincible = xml::ReadAttribute<bool> (current, "value", false);
			}
			else if (xmlStrEqual (current->name, (const xmlChar *) "is_visible") != 0)
			{
				m_visible = xml::ReadAttribute<float> (current, "value", true);
			}
			else if (xmlStrEqual (current->name, (const xmlChar *) "life_recovery_period") != 0)
			{
				m_life_recovery_period = xml::ReadAttribute<int16_t> (current, "value", 0);
			}
			else if (xmlStrEqual (current->name, (const xmlChar *) "life_recovery_unit") != 0)
			{
				m_life_recovery_unit = xml::ReadAttribute<float> (current, "value", 0.0);
			}
			else if (xmlStrEqual (current->name, (const xmlChar *) "life_state") != 0)
			{
				string life_state = xml::XReadString (current, "value", "ls_ignore");
				if (FromString (life_state, m_life_state) != true) m_life_state = ls_ignore;
			}
			else if (xmlStrEqual (current->name, (const xmlChar *) "mana_recovery_period") != 0)
			{
				m_mana_recovery_period = xml::ReadAttribute<int16_t> (current, "value", 0);
			}
			else if (xmlStrEqual (current->name, (const xmlChar *) "mana_recovery_unit") != 0)
			{
				m_mana_recovery_unit = xml::ReadAttribute<float> (current, "value", 0.0);
			}
			else if (xmlStrEqual (current->name, (const xmlChar *) "max_life") != 0)
			{
				m_max_life = xml::ReadAttribute<float> (current, "value", 0.0);
			}
			else if (xmlStrEqual (current->name, (const xmlChar *) "max_mana") != 0)
			{
				m_max_mana = xml::ReadAttribute<float> (current, "value", 0.0);
			}
			else if (xmlStrEqual (current->name, (const xmlChar *) "model") != 0)
			{
				m_model = xml::XReadString (current, "value", "");
			}
			else if (xmlStrEqual (current->name, (const xmlChar *) "render_scale") != 0)
			{
				m_render_scale = xml::ReadAttribute<float> (current, "value", 1.0);
			}
		}
	}
}

float GoAspect :: BoundingSphereRadius () const
{
	return m_bounding_sphere_radius;
}

float GoAspect :: CurrentLife () const
{
	return m_current_life;
}

float GoAspect :: CurrentMana () const
{
	return m_current_mana;
}

string GoAspect :: GetDynamicTexture (int index)
{
	if (index == 0 || index == 1)
	{
		return m_textures[index];
	}
	
	return "";
}

bool GoAspect :: IsInvincible () const
{
	return m_invincible;
}

bool GoAspect :: IsVisible () const
{
	return m_visible;
}

int16_t GoAspect :: LifeRecoveryPeriod () const
{
	return m_life_recovery_period;
}

float GoAspect :: LifeRecoveryUnit () const
{
	return m_life_recovery_unit;
}

eLifeState GoAspect :: LifeState () const
{
	return m_life_state;
}

int16_t GoAspect :: ManaRecoveryPeriod () const
{
	return m_mana_recovery_period;
}

float GoAspect :: ManaRecoveryUnit () const
{
	return m_mana_recovery_unit;
}

float GoAspect :: MaxLife () const
{
	return m_max_life;
}

float GoAspect :: MaxMana () const
{
	return m_max_mana;
}

string GoAspect :: Model () const
{
	return m_model;
}

float GoAspect :: RenderScale () const
{
	return m_render_scale;
}

void GoAspect :: SetCurrentLife (float life)
{
	m_current_life = life;
}

void GoAspect :: SetCurrentMana (float mana)
{
	m_current_mana = mana;
}

void GoAspect :: SetDynamicTexture (int index, const string & texture)
{
	if (index == 0 || index == 1)
	{
		m_textures[index] = texture;
	}
}

void GoAspect :: SetIsVisible (bool visible)
{
	m_visible = visible;
}

void GoAspect :: SetLifeState (eLifeState state)
{
	m_life_state = state;
}

void GoAspect :: SetMaxLife (float life)
{
	m_max_life = life;
}

void GoAspect :: SetMaxMana (float mana)
{
	m_max_mana = mana;
}

void GoAspect :: SetModel (const string & model)
{
	m_model = model;
}

void GoAspect :: SetRenderScale (float scale)
{
	m_render_scale = scale;
}

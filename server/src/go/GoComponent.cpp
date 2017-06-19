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

#include "GoComponent.hpp"

Go * GoComponent :: GetGo ()
{
    if (m_go != NULL)
    {
        return m_go;
    }

    throw logic_error ("null pointer referenced");
}

//GoComponent :: GoComponent () : m_go (NULL)
//{
//}

GoComponent::GoComponent(Go * go) : m_go(go)
{
    if (go == NULL)
    {
        throw invalid_argument("null pointer passed as argument");
    }
}
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

#include "AIQuery.hpp"

AIQuery query;

bool AIQuery :: IsInRange (const Go * a, const Go * b, double range)
{
    if (a == NULL || b == NULL)
    {
        return false;
    }

    if (a->HasPlacement() != true || b->HasPlacement() != true)
    {
        return false;
    }

    if (a->Placement()->GetRegion() != b->Placement()->GetRegion())
    {
        return false;
    }

    if (a->Placement()->GetRegion().empty())
    {
        return false;
    }

    Region * region = world.GetRegion (a->Placement()->GetRegion());

    return range >= region->GetSiegeDistance (a->Placement()->Position(), b->Placement()->Position());
}
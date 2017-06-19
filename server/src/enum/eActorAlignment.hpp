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

#ifndef EACTORALIGNMENT_HPP_
#define EACTORALIGNMENT_HPP_

    #include <string>
    using std::string;

    enum eActorAlignment
    {
        aa_good = 0,
        aa_neutral = 1,
        aa_evil = 2,
    };

    inline string ToString (eActorAlignment e)
    {
        switch (e)
        {
            case aa_good: return "aa_good";
            case aa_neutral: return "aa_neutral";
            case aa_evil: return "aa_evil";

            default: break;
        } /* switch (e) */

        return "";
    }

    inline bool FromString (const string & value, eActorAlignment & e)
    {
        if (value == "aa_good")
        {
            e = aa_good;
        }
        else if (value == "aa_neutral")
        {
            e = aa_neutral;
        }
        else if (value == "aa_evil")
        {
            e = aa_evil;
        }
        else
        {
            return false;
        }

        return true;
    }

#endif /* EACTORALIGNMENT_HPP_ */
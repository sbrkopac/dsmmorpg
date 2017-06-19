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

#ifndef GOSCRIPTCOMPONENT_HPP_
#define GOSCRIPTCOMPONENT_HPP_

    #include "GoComponent.hpp"
    #include "../msg/WorldMessage.hpp"

    class GoScriptComponent : public GoComponent
    {
        public:

            GoScriptComponent (Go * go);

            virtual ~GoScriptComponent () {};

            virtual string Name () const = 0;

            virtual void OnGoHandleMessage (const WorldMessage & message) = 0;
    };

#endif /* GOSCRIPTCOMPONENT_HPP_ */
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

#ifndef GOACTOR_HPP_
#define GOACTOR_HPP_

    #include "Skill.hpp"
    #include "../enum/eActorAlignment.hpp"
    #include "GoComponent.hpp"

    class GoActor : public GoComponent
    {
        public:

            GoActor (Go * go);
            GoActor (Go * go, xmlNode * node); // should be GoActor (xmlNode * node);
            ~GoActor ();

            eActorAlignment Alignment () const;
            void ChangeSkillLevel (const string & skill, float delta);
            float GetSkillLevel (const string & skill) const;
            float HighestSkillLevel () const;
            void SetAlignment (eActorAlignment alignment);
            void SetSkillLevel (const string & skill, float value);

        private:

            eActorAlignment m_alignment;
            map<string, Skill *> m_skills;
    };

#endif /* GOACTOR_HPP_ */
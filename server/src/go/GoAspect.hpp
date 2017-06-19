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

#ifndef GOASPECT_HPP_
#define GOASPECT_HPP_

    #include "GoComponent.hpp"
    #include "../enum/eLifeState.hpp"

    #include <map>
    using std::map;

    class GoAspect : public GoComponent
    {
        public:

            GoAspect (Go * go);
            GoAspect (Go * go, xmlNode * node);

            float BoundingSphereRadius () const;
            float CurrentLife () const;
            float CurrentMana () const;
            string GetDynamicTexture (int index);
            bool IsInvincible () const;
            bool IsVisible () const;
            int16_t LifeRecoveryPeriod () const;
            float LifeRecoveryUnit () const;
            eLifeState LifeState () const;
            int16_t ManaRecoveryPeriod () const;
            float ManaRecoveryUnit () const;
            float MaxLife () const;
            float MaxMana () const;
            string Model () const;
            float RenderScale () const;
            void SetCurrentLife (float life);
            void SetCurrentMana (float mana);
            void SetDynamicTexture (int index, const string & texture);
            void SetIsVisible (bool visible);
            void SetLifeState (eLifeState state);
            void SetMaxLife (float life);
            void SetMaxMana (float mana);
            void SetModel (const string & model);
            void SetRenderScale (float scale);

        private:

            float m_bounding_sphere_radius;
            float m_current_life;
            float m_current_mana;
            string m_textures[2];
            bool m_invincible;
            bool m_visible;
            int16_t m_life_recovery_period;
            float m_life_recovery_unit;
            eLifeState m_life_state;
            int16_t m_mana_recovery_period;
            float m_mana_recovery_unit;
            float m_max_life;
            float m_max_mana;
            string m_model;
            float m_render_scale;
    };

#endif /* GOASPECT_HPP_ */
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

#ifndef EWORLDEVENT_HPP_
#define EWORLDEVENT_HPP_

    #include <string>
    using std::string;

    enum eWorldEvent
    {
        we_invalid = 0,
        we_constructed,
        we_destructed,
        we_entered_world,
        we_left_world,
        we_entered_frustum,
        we_left_frustum,
        we_expired_auto,
        we_expired_forced,

        we_frustum_active_state_changed,

        /*
         * we_collided
         * we_glanced
         * we_damaged
         * we_healed
         * we_killed
         * we_leveled_up
         * we_lost_consciousness
         * we_gained_consciousness
         * we_resurrected
         * we_weapon_launched
         * we_weapon_swung
         *
         * we_engaged_hit
         * we_engaged_missed
         * we_engaged_killed
         */

        we_engaged_hit_killed,
        we_engaged_hit_lived,
        we_engaged_missed,


        we_mind_processing_new_job,
        we_job_failed,
        we_job_finished,
        we_job_reached_travel_distance,


        we_req_delete,
        we_player_changed,
        we_req_talk,
        we_player_ready,
        we_picked_up,
        we_dropped,
        we_equipped,
        we_unequipped,
    };

    inline string ToString (eWorldEvent e)
    {
        switch (e)
        {
            case we_invalid: return "we_invalid";
            case we_constructed: return "we_constructed";
            case we_destructed: return "we_destructed";
            case we_entered_world: return "we_entered_world";
            case we_left_world: return "we_left_world";
            case we_entered_frustum: return "we_entered_frustum";
            case we_left_frustum: return "we_left_frustum";
            case we_expired_auto: return "we_expired_auto";
            case we_expired_forced: return "we_expired_fored";

            case we_frustum_active_state_changed: return "we_frustum_active_state_changed";



            case we_engaged_hit_killed: return "we_engaged_killed";
            case we_engaged_hit_lived: return "we_engaged_hit";
            case we_engaged_missed: return "we_engaged_missed";



            case we_mind_processing_new_job: return "we_mind_processing_new_job";
            case we_job_failed: return "we_job_failed";
            case we_job_finished: return "we_job_finished";
            case we_job_reached_travel_distance: return "we_job_reached_travel_distance";


            case we_req_delete: return "we_req_delete";
            case we_player_changed: return "we_player_changed";
            case we_req_talk: return "we_req_talk";
            case we_player_ready: return "we_player_ready";
            case we_picked_up: return "we_picked_up";
            case we_dropped: return "we_dropped";
            case we_equipped: return "we_equipped";
            case we_unequipped: return "we_unequipped";

            default: break;
        } /* switch (e) */

        return "";
    }

#endif /* EWORLDEVENT_HPP_ */
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

#ifndef TEST_SCRIPT_HPP_
#define TEST_SCRIPT_HPP_

    #include "../go/GoScriptComponent.hpp"

    #include <iostream>
    using namespace std;

    class test_script : public GoScriptComponent
    {
        public:

            test_script (Go * go) : GoScriptComponent (go)
            {
                // cout << "test script constructed" << endl;
            }

            string Name () const
            {
                return "test_script";
            }

            void OnGoHandleMessage (const WorldMessage & message)
            {
                //cout << "test_script handled a message" << endl;
            }
    };

#endif /* TEST_SCRIPT_HPP_ */
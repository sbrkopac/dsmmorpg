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

#include "Engine.hpp"
#include "net/Network.hpp"
#include "map/WorldMap.hpp"
#include "server/Server.hpp"
#include "events/SendWorldMessageEvent.hpp"
#include <iostream>
#include <unistd.h>

using namespace std;

int main (int argc, char ** argv)
{
	cout << "dsmmorpg v1.01" << endl;
	
	srand (time (NULL));
	
	/*
	 * catch any standard berkley socket errors
	 */
	try
	{
		network.Bind (4000);
	}
	catch (int & e)
	{
		cout << "fatal network error : " << e << endl;
		
		return -1;
	}
	
	/*
	 * load resources in tthe following order :
	 * map, items, items which can hold items, actors, players
	 */
	try
	{
		world.LoadMap ("/home/aaron/Projects/server/data/static/map/main.xml");
		
		godb.LoadGoDb ("/home/aaron/Projects/server/data/dynamic/items.xml");
		godb.LoadGoDb ("/home/aaron/Projects/server/data/dynamic/actors.xml");
		
		// godb.LoadContentDb ("/home/aaron/Projects/server/data/static/items.xml");
		godb.LoadContentDb ("/home/aaron/Projects/server/data/static/actors.xml");
		
		server.LoadAccounts ("/home/aaron/Projects/server/data/dynamic/accounts.xml");
	}
	catch (exception & e)
	{
		cout << "exception caught : " << e.what() << endl;
		xmlCleanupParser();
		
		return -1;
	}
	
	try
	{
		/*
		 * tell the engine to start resolving frustums
		 */
		PostWorldMessage (we_frustum_active_state_changed, 0, 0, "", 2500);
		
		while (engine.IsRunning())
		{
			network.Listen();
			engine.Loop();
			
			usleep (1);
		}
	}
	catch (exception & e)
	{
		cout << "exception caught : " << e.what() << endl;
	}
	catch (int & e)
	{
		cout << "network error caught : " << e << endl;
	}
	
	xmlCleanupParser();
	
	return 0;
}

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

#include "../MainMenu.hpp"
#include "Network.hpp"

Network network;

Network :: Network ()
{
	#ifdef WIN32
		WSAStartup (MAKEWORD (2, 2), &m_wsadata);
	#endif

	FD_ZERO (& m_descriptors);
	FD_ZERO (& m_active);
}

Network :: ~Network ()
{
	m_listening.Close();

	list<Connection>::iterator iterator = m_connections.begin();
	while (iterator != m_connections.end())
	{
		iterator->Close();
		iterator++;
	}

	#ifdef WIN32
		WSACleanup();
	#endif
}

void Network :: Bind (u_int16_t port)
{
	m_listening.Bind (port);
	m_listening.Listen();
	m_listening.SetNonBlockingFlag (true);
	FD_SET (m_listening.data(), &m_descriptors);
}

void Network :: Listen ()
{
	Accept();
	Receive();
}

void Network :: Accept ()
{
	fd_set fdsr;

	FD_ZERO (&fdsr);
	FD_SET (m_listening.data(), &fdsr);

	timeval tv = {0, 0};

	int activity = select (m_listening.data() + 1, &fdsr, 0, 0, &tv);

	if (activity > 0)
	{
		if (FD_ISSET (m_listening.data(), &fdsr) != 0) // listening socket has activity
		{
			int descriptor = m_listening.Accept();
			if (descriptor != -1)
			{
				if (FD_SETSIZE - m_sockets.size() > 0)
				{
					try
					{
						Connection c (descriptor);

						m_connections.push_back (c);

						Connection & p = *m_connections.rbegin();

						p.SetNonBlockingFlag (true);
						p.SetWorldState (new MainMenu (p));

						m_sockets.insert (p.data());
						FD_SET (p.data(), &m_descriptors);
					}
					catch (int & error)
					{
						if (error != EWOULDBLOCK)
						{
							throw error;
						}
					}
				}
				else
				{
					/*
					 * this is the part where we inform the client that
					 * there is no more room left on the server ...
					 *
					 * but i mean really ... is dsmmorpg going to be that popular?
					 * if you are running a server that is that popular
					 * you can implement the code here
					 */
				}
			}
		}
	}
}

void Network :: Receive ()
{
	int activity = 0;
	if (m_sockets.size() > 0)
	{
		timeval tv = {0, 0};
		m_active = m_descriptors;

		activity = select (*m_sockets.rbegin() + 1, &m_active, 0, 0, &tv);
	}

	if (activity > 0)
	{
		list<Connection>::iterator iterator = m_connections.begin();
		list<Connection>::iterator connection;

		while (iterator != m_connections.end())
		{
			connection = iterator++;

			if (FD_ISSET (connection->data(), &m_active) != 0) // this connection has activity
			{
				try
				{
					int error;
					error = connection->Receive();
				}
				catch (int & e)
				{
					m_sockets.erase (connection->data());
					FD_CLR (connection->data(), &m_descriptors);
					connection->Close();
					m_connections.erase (connection);
				}

				if (--activity <= 0)
				{
					break;
				}
			}
		}
	}
}
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

#include "Connection.hpp"
#include "Packet.hpp"

Connection :: Connection (int descriptor) : m_descriptor (descriptor), m_connected (false), m_state (NULL)
{
    if (m_descriptor != -1)
    {
        m_connected = true;
    }
}

void Connection :: SetNonBlockingFlag (bool nonblocking)
{
    int flags = fcntl (m_descriptor, F_GETFL, 0);
    if (flags == -1)
    {
        throw errno;
    }

    if (nonblocking == true)
    {
        flags |= O_NONBLOCK;
    }
    else
    {
        flags &= ~O_NONBLOCK;
    }

    int error = fcntl (m_descriptor, F_SETFL, flags);
    if (error == -1)
    {
        throw errno;
    }
}

int Connection :: Send (const char * buffer, int size)
{
    int error;
    error = ::send (m_descriptor, buffer, size, 0);

    if (error == -1)
    {
        int e = errno;

        if (e != EWOULDBLOCK)
        {
            throw e;
        }

        error = 0;
    }

    return error;
}

int Connection :: Receive ()
{
    int error;
    error = ::recv (m_descriptor, m_buffer, 1024, 0);

    if (error == 0)
    {
        throw errno; // "EConnectionClosed"
    }
    if (error == -1)
    {
        int & e = errno;

        if (e == ECONNRESET)
        {
            m_connected = false;
        }

        throw errno;
    }

    if (m_state != NULL)
    {
        u_int16_t position = 0;
        while (error > 2)
        {
            u_int16_t size;
            memcpy ((char *)(&size), m_buffer + position, sizeof (u_int16_t));
            size = ntohs (size);

            if (size == 0) break;

            if (size <= error)
            {
                m_state->Handle (m_buffer + position);
            }

            error -= size;
            position += size;
        }
    }

    return error;
}

void Connection :: Close ()
{
    int error;
    if (m_connected != false)
    {
        error = shutdown (m_descriptor, 2);
        if (error == -1)
        {
            throw errno;
        }
    }

    error = ::close (m_descriptor);
    if (error == -1)
    {
        throw errno;
    }

    m_descriptor = -1;
    m_connected = false;

    if (m_state != NULL)
    {
        m_state->OnExit();
        delete m_state;
        m_state = NULL;
    }
}

WorldState * Connection :: State () const
{
    return m_state;
}

void Connection::SetWorldState(WorldState * state)
{
    if (m_state != NULL)
    {
        m_state->OnExit();
        delete m_state;
        m_state = NULL;
    }

    m_state = state;
    m_state->OnEnter();
}
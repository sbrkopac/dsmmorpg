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

#include "Packet.hpp"

Packet :: Packet () : m_size (2), m_position (2), m_data (NULL)
{
    m_data = (char *) malloc (2);
}

Packet :: Packet (const char * buffer) : m_size (0), m_position (2), m_data (NULL)
{
    u_int16_t size;
    memcpy ((char*)(&size), buffer, sizeof (u_int16_t));
    m_size = ntohs (size);

    m_data = (char *) malloc (m_size);
    memcpy (m_data, buffer, m_size);
}

Packet :: ~Packet ()
{
    m_size = 0;
    m_position = 0;

    if (m_data)
    {
        free (m_data);
        m_data = NULL;
    }
}

void Packet :: WriteUInt32 (u_int32_t data)
{
    u_int32_t _data = htonl (data);
    Append ((const char*)(&_data), sizeof (u_int32_t));
}

void Packet :: WriteInt32 (int32_t data)
{
    int32_t _data = htonl (data);
    Append ((const char*)(&_data), sizeof (int32_t));
}

void Packet :: WriteUInt16 (u_int16_t data)
{
    u_int16_t _data = htons (data);
    Append ((const char*)(&_data), sizeof (u_int16_t));
}

void Packet :: WriteInt16 (int16_t data)
{
    int16_t _data = htons (data);
    Append ((const char*)(&_data), sizeof (int16_t));
}

void Packet :: WriteUInt8 (u_int8_t data)
{
    Append ((const char*)(&data), sizeof (u_int8_t));
}

void Packet :: WriteInt8 (int8_t data)
{
    Append ((const char*)(&data), sizeof (int8_t));
}

void Packet :: WriteFloat (float data)
{
    Append ((const char*)(&data), sizeof (float));
}

void Packet :: WriteString (const string & buffer)
{
    u_int16_t size = buffer.size() + 1;
    m_data = (char*) realloc (m_data, m_size + size);
    memcpy ((m_data + m_size), buffer.c_str(), size);

    m_size += size;
    m_data[m_size - 1] = '\0';
}

u_int32_t Packet :: ReadUInt32 ()
{
    u_int16_t size = sizeof (u_int32_t);

    u_int32_t data;
    memcpy (((char*)(&data)), (m_data + m_position), size);
    m_position += size;

    return ntohl (data);
}

int32_t Packet :: ReadInt32 ()
{
    u_int16_t size = sizeof (int32_t);

    int32_t data;
    memcpy (((char*)(&data)), (m_data + m_position), size);
    m_position += size;

    return ntohl (data);
}

u_int16_t Packet :: ReadUInt16 ()
{
    u_int16_t size = sizeof (u_int16_t);

    u_int16_t data;
    memcpy (((char*)(&data)), (m_data + m_position), size);
    m_position += size;

    return ntohs (data);
}

int16_t Packet :: ReadInt16 ()
{
    u_int16_t size = sizeof (int16_t);

    int16_t data;
    memcpy (((char*)(&data)), (m_data + m_position), size);
    m_position += size;

    return ntohs (data);
}

u_int8_t Packet :: ReadUInt8 ()
{
    return (u_int8_t)(*(m_data + m_position++));
}

int8_t Packet :: ReadInt8 ()
{
    return (int8_t)(*(m_data + m_position++));
}

float Packet :: ReadFloat ()
{
    u_int16_t size = sizeof (float);

    float data;
    memcpy (((char*)(&data)), (m_data + m_position), size);
    m_position += size;

    return data;
}

string Packet :: ReadString ()
{
    string buffer;

    try
    {
        while (m_position < m_size)
        {
            if (m_data[m_position++] == '\0') break;

            buffer += m_data[m_position - 1];
        }
    }
    catch (...)
    {
        return "";
    }

    return buffer;
}

u_int16_t Packet :: Size ()
{
    return m_size;
}

const char * Packet :: Data ()
{
    u_int16_t size = htons (m_size);
    memcpy (m_data, (char*)(&size), sizeof (u_int16_t));

    return m_data;
}

void Packet :: Append (const char * buffer, u_int16_t size)
{
    m_data = (char*) realloc (m_data, m_size + size);
    memcpy ((m_data + m_size), buffer, size);

    m_size += size;
}
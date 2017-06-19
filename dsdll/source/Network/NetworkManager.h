
#ifndef _NETMANAGER_H_
#define _NETMANAGER_H_

    // Include Libraries

    #include <vector>
    #include <algorithm>
    #include <stdio.h>
    #include <string>

    #include "../GPG.h"
    #include "wsa.h"
    #include "Socket.h"
    #include "Packet.h"

    void midcopy ( char * p_input, char * p_output, int p_start, int p_stop )
    {
        int p_index = 0;

        for ( int i = p_start; i < p_stop; i++ )
        {
            p_output[p_index] = p_input[i];
            p_index++;
        }

        p_output[p_index] = '\0';
    }

    class NetworkManager : public Socket, public Singleton <NetworkManager>
    {
        public:

            #define gNetworkManager NetworkManager::GetSingleton ();

            NetworkManager ()
            {
            }

            ~NetworkManager ()
            {
                ClearAllPackets ();
                Socket::Close ();
            }

            FEX int Connect (const char * ip, Port port)
            {
                int error = Socket::Connect (GetIpAddress (ip), port);

                if (error == -1)
                {
                    return (-1);
                }
                Socket::SetBlocking (false);

                return (error);
            }

            FEX bool IsConnected ()
            {
                return (Socket::IsConnected());
            }

            FEX int Send (Packet * p_Packet)
            {
                int bytes = ::send (m_Socket, (const char *)p_Packet->Data(), p_Packet->Size(), 0);

                delete (p_Packet);

                return (bytes);
            }

            FEX int Receive ( void )
            {
                if (!Socket::IsConnected())
                {
                    return -1;
                }

                int count = 0;

                int bytes = recv (m_Socket, m_buffer, 8192, 0);

                if (bytes > 0)
                {
                    int position = 0;

                    while (bytes > 2)
                    {
                        u_int16_t size;
                        memcpy ((unsigned char*)(&size), m_buffer + position, sizeof (size));
                        size = ntohs (size);

                        if (size == -1)
                        {
                            return -10;
                        }

                        if (size <= bytes)
                        {
                            Packet * packet = new Packet ((unsigned char *)(m_buffer + position));
                            m_PacketStream.push_back (packet);

                            count++;
                        }

                        bytes -= size;
                        position += size;
                    }

                    return count;
                }

                return 0;
            }

            FEX Packet * NextPacket ()
            {
                std::vector <Packet *>::iterator p_sIterator = m_PacketStream.begin();

                if (p_sIterator != m_PacketStream.end())
                {
                    return (* p_sIterator);
                }

                return (NULL);
            }

            FEX Packet * CreatePacket ()
            {
                return (new Packet());
            }

            FEX void DiscardPacket (Packet * p_Packet)
            {
                std::vector <Packet *>::iterator p_sIterator = std::find (m_PacketStream.begin(), m_PacketStream.end(), p_Packet);

                if (p_sIterator != m_PacketStream.end())
                {
                    delete (* p_sIterator);

                    m_PacketStream.erase (p_sIterator);
                }
            }

            FEX void Disconnect ()
            {
                Socket::Close();
            }

        private:

            void ClearAllPackets ()
            {
                std::vector <Packet *>::iterator iterator;
                for (iterator = m_PacketStream.begin(); iterator != m_PacketStream.end(); iterator++)
                {
                    delete (* iterator);
                    m_PacketStream.erase (iterator);
                }
            }

            FUBI_SINGLETON_CLASS (NetworkManager, "Author(s): Sam Brkopac");

        protected:

            char m_buffer[8192];
            std::vector <Packet *> m_PacketStream;
    };

    NetworkManager g_NetworkManager;

#endif
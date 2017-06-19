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

#ifndef MAINMENU_HPP_
#define MAINMENU_HPP_

    #include "net/Connection.hpp"
    #include "server/Server.hpp"

    #include "net/packets.hpp"
    #include "InGame.hpp"

    #include "scripts/Player.hpp"

    class MainMenu : public WorldState
    {
        public:

            MainMenu (Connection & connection) : WorldState (&connection)
            {
                cout << "main menu entered" << endl;
            }

            ~MainMenu ()
            {
            }

            void OnEnter ()
            {
            }

            void OnExit ()
            {
            }

            void Handle (const char * buffer)
            {
                Packet incoming (buffer);

                u_int8_t type = incoming.ReadUInt8();
                switch (type)
                {
                    case RSAUTHENTICATION:
                    {
                        string username = incoming.ReadString();
                        string password = incoming.ReadString();

                        cout << "authentication request for " << username << " with password " << password << endl;

                        Account * account = server.GetAccount (username);
                        if (account != NULL)
                        {
                            bool authenticated = password == account->Password();

                            Packet outgoing;
                            outgoing.WriteUInt8 (RCAUTHENTICATION);
                            outgoing.WriteUInt8 (authenticated == true ? 1 : 0);
                            m_connection->Send (outgoing.Data(), outgoing.Size());

                            if (authenticated == true)
                            {
                                Go * go = account->GetGo();
                                if (go == NULL)
                                {
                                    cout << "huge error, null go for player!" << endl;
                                    return;
                                }

                                cout << "main menu grabbed player " << account->Username() << " and go with id " << go->Goid() << endl;

                                go->AddComponent (new Player (m_connection, go));
                                m_connection->SetWorldState (new InGame (*m_connection, go));
                            }
                        }
                        else
                        {
                            Packet outgoing;
                            outgoing.WriteUInt8 (RCAUTHENTICATION);
                            outgoing.WriteUInt8 (0);
                            m_connection->Send (outgoing.Data(), outgoing.Size());
                        }
                    }
                    break;

                    default:
                    {
                    }
                    break;
                } /* switch (type) */
            }

        protected:

            // string m_username;
            // string m_password;
    };

#endif /* MAINMENU_HPP_ */
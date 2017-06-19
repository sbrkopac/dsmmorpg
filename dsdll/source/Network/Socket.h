

#ifndef SOCKET_H
#define SOCKET_H

    // Include Libraries

    #include <string>

    #include "Net.h"
    #include "wsa.h"

    // Socket Class

    class Socket
    {
        public:

            Socket ( void )
            {
                // Invalidate the socket
                m_Socket = -1;

                // Set the socket as blocking by default
                m_bIsBlocking = true;

                // Set the socket as disconnected by default
                m_bIsConnected = false;
            }

            inline SOCKET GetSocket ( void ) const
            {
                // Return the socket
                return ( m_Socket );
            }

            inline Port GetLocalPort ( void ) const
            {
                // Return the local port
                return ( ntohs ( m_LocalInfo.sin_port ) );
            }

            inline Port GetRemotePort ( void ) const
            {
                // Return the remote port
                return ( ntohs ( m_RemoteInfo.sin_port ) );
            }

            inline Ip GetLocalAddress ( void ) const
            {
                // Return the local ip
                return ( m_LocalInfo.sin_addr.s_addr );
            }

            inline Ip GetRemoteAddress ( void ) const
            {
                // Return the remote address
                return ( m_RemoteInfo.sin_addr.s_addr );
            }

            void SetBlocking ( bool bIsBlocking )
            {
                // Declare the error message
                int Error;

                // Determine the blocking mode
                unsigned long iMode = !bIsBlocking;

                // Configure the socket
                Error = ioctlsocket ( m_Socket, FIONBIO, &iMode );

                // Store the state of the socket
                m_bIsBlocking = bIsBlocking;
            }

            int Connect ( Ip ipAddress, Port Port )
            {
                // Declare a variable to hold the return errors
                int error;

                if ( m_bIsConnected )
                {
                    // Ensure a connection does not already exist
                    //throw ( Exception ( WSAEISCONN ) );
                    return (-1);
                }

                if ( m_Socket == -1 )
                {
                    // Set the socket
                    m_Socket = socket ( AF_INET, SOCK_STREAM, IPPROTO_TCP );

                    if ( m_Socket == -1 )
                    {
                        // Throw any connection errors
                        return (-1);
                    }
                }

                // Set the remote information properties
                m_RemoteInfo.sin_family = AF_INET;
                m_RemoteInfo.sin_port = htons ( Port );
                m_RemoteInfo.sin_addr.s_addr = ipAddress;

                // Copy over the remote properties
                memset ( &( m_RemoteInfo.sin_zero ), 0, 8 );

                // Declare the struct size
                socklen_t Size = sizeof ( struct sockaddr );

                // Connect the socket
                error = connect ( m_Socket, ( struct sockaddr * )( &m_RemoteInfo ), Size );

                if ( error == -1 )
                {
                    // Throw any connection errors
                    return (-1);
                }

                // Store the state of the connection
                m_bIsConnected = true;

                // Set the socket
                error = getsockname ( m_Socket, ( struct sockaddr * )( &m_LocalInfo ), &Size );

                if ( error != 0 )
                {
                    // Throw any socket errors
                    return (-1);
                }

                return (error);
            }

            bool IsConnected ( void )
            {
                // Return the state of the connection
                return ( m_bIsConnected );
            }

            int Send ( const char * strBuffer, int Size )
            {
                // Declare a variable to hold the return errors
                int error;

                if ( !m_bIsConnected )
                {
                    // Ensure a connection already exists
                    //throw ( Exception ( WSAENOTCONN ) );
                    return (-1);
                }

                // Send the data through the socket
                error = send ( m_Socket, strBuffer, Size, 0 );

                if ( error == -1 )
                {
                    // Declare the last error
                    int wsa = WSAGetLastError();

                    if ( wsa == WSAEWOULDBLOCK )
                    {
                        // Ensure the action will not block the socket
                        throw ( wsa );
                    }

                    // Set the number of bytes sent to zero
                    error = 0;
                }

                // Return the number of bytes sent
                return ( error );
            }

            int Receive ( char * strBuffer, int Size )
            {
                // Declare a variable to hold the return errors
                int error;

                if ( !m_bIsConnected )
                {
                    return (-1);
                }

                // Receive the data through the socket
                error = recv ( m_Socket, strBuffer, Size, 0 );

                if ( error == 0 )
                {
                    return (-1);
                }

                if ( error == -1 )
                {
                    return (-1);
                }

                // Return the number of bytes received
                return ( error );
            }

            void Close ( void )
            {
                if ( m_bIsConnected )
                {
                    // Shut down the socket in the proper mode
                    shutdown ( m_Socket, 2 );
                }

                // Close the socket
                closesocket ( m_Socket );

                // Invalidate the socket
                m_Socket = -1;

                // Store the connection state of the socket
                m_bIsConnected = false;
            }

        protected:

            SOCKET m_Socket;
            struct sockaddr_in m_LocalInfo;
            struct sockaddr_in m_RemoteInfo;
            bool m_bIsBlocking;
            bool m_bIsConnected;
    };

#endif
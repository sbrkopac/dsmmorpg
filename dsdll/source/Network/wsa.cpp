

    // Include Libraries

    #include "wsa.h"

    // wsa Class

    class wsa
    {
        public:

            wsa ( void )
            {
                // Start the winsock library
                WSAStartup ( MAKEWORD ( 2, 2 ), &m_wsaData );
            }

            ~wsa ( void )
            {
                // Close the winsock library
                WSACleanup();
            }

        protected:

            WSADATA m_wsaData;
    };

    // Declare Exports

    wsa g_wsa;

    // Function Definitions

    bool IsIpAddress ( const char * p_strAddress )
    {
        for ( size_t p_iIterator = 0; p_iIterator < strlen ( p_strAddress ); p_iIterator++ )
        {
            if ( ( p_strAddress[p_iIterator] < '0' || p_strAddress[p_iIterator] > '9' ) && p_strAddress[p_iIterator] != '.' )
            {
                // Return a false on the ip address
                return ( false );
            }
        }

        // Return a true on the ip address
        return ( true );
    }

    Ip GetIpAddress ( const char * p_strAddress )
    {
        if ( IsIpAddress ( p_strAddress ) )
        {
            // Declare the ip address
            Ip p_ipAddress = inet_addr ( p_strAddress );

            if ( p_ipAddress == INADDR_NONE )
            {
                // Throw an invalid address error
                throw ( WSAHOST_NOT_FOUND );
            }

            // Return the address
            return ( p_ipAddress );
        }
        else
        {
            // Declare a host
            struct hostent * p_Host = gethostbyname ( p_strAddress );

            if ( p_Host == 0 )
            {
                // Throw any errors
                throw ( WSAGetLastError() );
            }

            // Return the address
            return ( *( ( Ip * ) p_Host->h_addr ) );
        }
    }
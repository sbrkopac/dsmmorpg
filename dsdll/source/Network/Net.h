

#ifndef NET_H
#define NET_H

    // Include Libraries

    #include <winsock2.h>

    // Type Definitions

    typedef unsigned short int Port;
    typedef unsigned long int Ip;

    #ifndef socklen_t
        typedef int socklen_t;
    #endif

#endif
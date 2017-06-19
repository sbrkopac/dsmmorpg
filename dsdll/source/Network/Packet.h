#ifndef Packet_H_
#define Packet_H_

    #include "../Types.h"
    #include <winsock2.h>
    #include <string>

    using namespace std;

    class Packet
    {
        public:

            /*
             *
             */
            Packet () : m_size (2), m_position (2), m_data (NULL)
            {
                m_data = (unsigned char *) realloc (m_data, 2);
            }

            /*
             *
             */
            Packet :: Packet (unsigned char * buffer) : m_size (0), m_position (2), m_data (NULL)
            {
                u_int16_t size;
                memcpy ((unsigned char *)(&size), buffer, sizeof (u_int16_t));
                m_size = ntohs (size);

                m_data = (unsigned char *) malloc (m_size);
                memcpy (m_data, buffer, m_size);
            }

            /*
             *
             */
            ~Packet ()
            {
                m_size = 0;
                m_position = 0;

                if (m_data)
                {
                    free (m_data);
                    m_data = NULL;
                }
            }

            FEX void WriteUInt32 (u_int32_t data)
            {
                u_int32_t _data = htonl (data);
                Append ((unsigned char *)(&_data), sizeof (u_int32_t));
            }

            FEX void WriteInt32 (s_int32_t data)
            {
                s_int32_t _data = htonl (data);
                Append ((unsigned char *)(&_data), sizeof (s_int32_t));
            }

            FEX void WriteUInt16 (u_int16_t data)
            {
                u_int16_t _data = htonl (data);
                Append ((unsigned char *)(&_data), sizeof (u_int16_t));
            }

            FEX void WriteInt16 (s_int16_t data)
            {
                s_int16_t _data = htonl (data);
                Append ((unsigned char *)(&_data), sizeof (s_int16_t));
            }

            FEX void WriteUInt8 (u_int8_t data)
            {
                Append ((unsigned char *)(&data), sizeof (u_int8_t));
            }

            FEX void WriteInt8 (s_int8_t data)
            {
                Append ((unsigned char *)(&data), sizeof (s_int8_t));
            }

            FEX void WriteFloat (float data)
            {
                /*
                union
                {
                    float f;
                    u_int32_t i;
                } swap;

                swap.f = data;
                swap.i = htonl (swap.i);*/

                Append ((unsigned char *)(&data), sizeof (u_int32_t));
            }

            FEX void WriteString (const char * data)
            {
                u_int16_t size = strlen (data) + 1;
                m_data = (unsigned char *) realloc (m_data, m_size + size);
                memcpy ((m_data + m_size), data, size);

                m_size += size;
                m_data[m_size - 1] = '\0';
            }

            FEX u_int32_t ReadUInt32 ()
            {
                u_int16_t size = sizeof (u_int32_t);

                u_int32_t data;
                memcpy (((unsigned char *)(&data)), (m_data + m_position), size);
                m_position += size;

                return ntohl (data);
            }

            FEX s_int32_t ReadInt32 ()
            {
                u_int16_t size = sizeof (s_int32_t);

                s_int32_t data;
                memcpy (((unsigned char *)(&data)), (m_data + m_position), size);
                m_position += size;

                return ntohl (data);
            }

            FEX u_int16_t ReadUInt16 ()
            {
                u_int16_t size = sizeof (u_int16_t);

                u_int16_t data;
                memcpy (((unsigned char *)(&data)), (m_data + m_position), size);
                m_position += size;

                return ntohs (data);
            }


            FEX s_int16_t ReadInt16 ()
            {
                u_int16_t size = sizeof (s_int16_t);

                s_int16_t data;
                memcpy (((unsigned char *)(&data)), (m_data + m_position), size);
                m_position += size;

                return ntohs (data);
            }

            FEX u_int8_t ReadUInt8 ()
            {
                return (u_int8_t)(*(m_data + m_position++));
            }

            FEX s_int8_t ReadInt8 ()
            {
                return (s_int8_t)(*(m_data + m_position++));
            }

            FEX float ReadFloat ()
            {/*
                union
                {
                    float f;
                    u_int32_t i;
                } swap;

                u_int16_t size = sizeof (u_int32_t);
                memcpy (((unsigned char *)(&swap.i)), (m_data + m_position), size);
                m_position += size;

                swap.i = ntohl (swap.i);

                return swap.f;*/

                u_int16_t size = sizeof (float);

                float data;
                memcpy (((char*)(&data)), (m_data + m_position), size);
                m_position += size;

                return data;
            }

            FEX const char * ReadString ()
            {
                int i = 0;
                while (m_position < m_size)
                {
                    if (m_data[m_position++] == '\0') break;

                    m_string[i++] = m_data[m_position - 1];
                }

                m_string[i] = '\0';
                return (const char*)m_string;
            }

            u_int16_t Size ()
            {
                return m_size;
            }

            unsigned char * Data ()
            {
                u_int16_t size = htons (m_size);
                memcpy (m_data, (unsigned char *)(&size), sizeof (u_int16_t));

                return m_data;
            }

        private:

            void Append (unsigned char * buffer, u_int16_t size)
            {
                m_data = (unsigned char *) realloc (m_data, m_size + size);
                memcpy ((m_data + m_size), buffer, size);

                m_size += size;
            }

            u_int16_t m_size;
            u_int16_t m_position;
            unsigned char * m_data;
            unsigned char m_string[256]; // memory management amirite?


        protected:
    };

#endif /*Packet_H_*/

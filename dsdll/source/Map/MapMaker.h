
#ifndef _MAPMAKER_H_
#define _MAPMAKER_H_

    #include <vector>
    #include <fstream>
    #include <string>

    #include "../GPG.h"

    using namespace std;

    class MapMaker : public Singleton <MapMaker>
    {
        public:

            #define gMapMaker MapMaker::GetSingleton ();

            MapMaker ()
            {
            }

            FEX int ReadNodesDotGasFrom (const char * filename)
            {
                fstream file (filename, ios::in);

                if (!file.is_open())
                {
                    return -1;
                }

                int count = 0;

                char buffer[256];
                while (file.good())
                {
                    file.getline (buffer, 256, '\n');

                    if (strstr (buffer, "[t:snode,n:"))
                    {
                        unsigned int node;

                        string sbuffer = buffer;
                        char guid[11];

                        memcpy (guid, buffer+12, 10);
                        guid[10] = '\0';

                        int p_return = sscanf (guid, "%x", &node);

                        if (p_return == 1)
                        {
                            m_Nodes.push_back (node);
                            count++;
                        }
                    }
                }

                return count;
            }

            FEX unsigned int GetNodeGuidAt (unsigned int index)
            {
                if (index < m_Nodes.size())
                {
                    return m_Nodes[index];
                }

                return 0;
            }

        private:

            FUBI_SINGLETON_CLASS (MapMaker, "Author(s): Sam Brkopac");

            vector<unsigned long int> m_Nodes;
    };

    MapMaker g_MapMaker;

#endif



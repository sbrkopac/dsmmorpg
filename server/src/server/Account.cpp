
#include "Account.hpp"

Account :: Account (xmlNode * node)
{
    if (node != NULL)
    {
        m_username = xml::ReadAttribute<string> (node, "username", "");
        m_password = xml::ReadAttribute<string> (node, "password", "");

        xmlNode * current = NULL;
        for (current = node->children; current != NULL; current =  current->next)
        {
            if (current->type != XML_ELEMENT_NODE) continue;

            if (xmlStrEqual (current->name, (const xmlChar *) "go") != 0)
            {
                u_int32_t id = xml::ReadAttribute<u_int32_t> (current, "id", 0);

                Go * go = godb.FindGoById (id);
                if (go != NULL)
                {
                    m_objects.push_back (go);
                }
            }
        }
    }
}

string Account :: Username () const
{
    return m_username;
}

string Account :: Password () const
{
    return m_password;
}
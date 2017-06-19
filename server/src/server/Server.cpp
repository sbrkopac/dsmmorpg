
#include "Server.hpp"

Server server;

Server :: ~Server ()
{
    map<string, Account *>::iterator iterator = m_accounts.begin();
    while (iterator != m_accounts.end())
    {
        delete iterator->second;
        iterator++;
    }
}

void Server :: LoadAccounts (const string & filename)
{
    xmlDoc * document = xmlReadFile (filename.c_str(), NULL, 0);
    if (document == NULL)
    {
        return; // throw
    }

    xmlNode * root = xmlDocGetRootElement (document);
    if (root == NULL)
    {
        xmlFree (document);
        return; // throw
    }

    xmlNode * node = NULL;
    for (node = root->children; node != NULL; node = node->next)
    {
        if (node->type != XML_ELEMENT_NODE) continue;

        if (xmlStrEqual (node->name, (const xmlChar *) "account") != 0)
        {
            string username = xml::ReadAttribute<string> (node, "username", "");
            if (username.empty() != true)
            {
                Account * account = new Account (node);
                m_accounts[username] = account;
            }
        }
    }

    xmlFreeDoc (document);
}

Account * Server :: GetAccount (const string & account)
{
    map<string, Account *>::iterator iterator = m_accounts.find (account);

    return (iterator != m_accounts.end() ? iterator->second : NULL);
}
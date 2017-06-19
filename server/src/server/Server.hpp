#ifndef SERVER_HPP_
#define SERVER_HPP_

    #include "Account.hpp"

    #include <map>
    using std::map;

    class Server
    {
        public:

            ~Server ();

            void LoadAccounts (const string & filename);

            Account * GetAccount (const string & account);

        private:

            map<string, Account *> m_accounts;
    };

    extern Server server;

#endif /* SERVER_HPP_ */
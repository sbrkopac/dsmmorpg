#ifndef ACCOUNT_HPP_
#define ACCOUNT_HPP_

	#include "../go/GoDb.hpp"
	#include "../net/Connection.hpp"
	
	#include <vector>
	using std::vector;
	
	class Account
	{
		public:
			
			Account (xmlNode * node);
			
			string Username () const;
			string Password () const;
			
			// <temp>
			Go * GetGo ()
			{
				return m_objects.at (0);
			}
			// </temp>
			
		private:
			
			string m_username;
			string m_password;
			
			vector<Go *> m_objects;
	};

#endif /* ACCOUNT_HPP_ */

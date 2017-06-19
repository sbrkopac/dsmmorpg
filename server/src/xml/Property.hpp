#ifndef PROPERTY_HPP_
#define PROPERTY_HPP_

	#include <libxml/tree.h>
	#include <libxml/parser.h>
	#include "../platform.hpp"
	
	#include <string>
	using std::string;
	
	#include <sstream>
	using std::stringstream;
	
	namespace xml
	{
		template< typename type >
		type ReadAttribute (xmlNode * node, const string & attribute, const type & d)
		{
			xmlChar * data = xmlGetProp (node, (const xmlChar *) attribute.c_str());
			if (data != NULL)
			{
				type value;
				stringstream stream ((const char *) data);
				stream >> value;
				
				xmlFree (data);
				
				return value;
			}
			
			return d;
		}
		
		inline string XReadString (xmlNode * node, const string & attribute, const string & d)
		{
			xmlChar * data = xmlGetProp (node, (const xmlChar *) attribute.c_str());
			if (data != NULL)
			{
				string value = (const char *) data;
				
				xmlFree (data);
				
				return value;
			}
			
			return d;
		}
	}

#endif /* PROPERTY_HPP_ */

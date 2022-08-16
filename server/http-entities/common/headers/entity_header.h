#ifndef HTTP_ENTITIES_COMMON_HEADERS_ENTITY_HEADER_H
#define HTTP_ENTITIES_COMMON_HEADERS_ENTITY_HEADER_H

#include "http_header.h"
#include <map>
#include <string>

namespace http
{
	namespace headers
	{
		class EntityHeader: public HttpHeader
		{
		public:
			const std::map<std::string, std::string>& get() const;
			const std::string& get(const std::string& key) const;
			void append_line(char* line);
		protected:
			std::map<std::string, std::string> fields_;
		};
	};
};

#endif
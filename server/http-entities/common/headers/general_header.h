#ifndef HTTP_ENTITIES_COMMON_HEADERS_GENERAL_HEADER_H
#define HTTP_ENTITIES_COMMON_HEADERS_GENERAL_HEADER_H

#include <ctime>
#include <string>
#include <set>

#include "http_header.h"

namespace http
{
	namespace headers
	{
		class GeneralHeader: public HttpHeader
		{
		public:
			GeneralHeader();
			~GeneralHeader();

			void set_date(const char* date);
			void set_date(const struct tm* date_struct);
			const std::tm* get_date_struct() const;
			const std::string& get_date() const;

			void add_pragma_directive(const char* pragma_directive);
			const std::set<std::string>& get_pragma_directives() const;

			void append_line(char* line);
		protected:
			void set_date_string();

			struct tm* date_;
			std::string date_string_;
			std::set<std::string> pragma_directives_;
		};
	};
};

#endif
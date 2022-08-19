#ifndef HTTP_ENTITIES_COMMON_TOOLS_HEADER_TYPE_DEFINE_H
#define HTTP_ENTITIES_COMMON_TOOLS_HEADER_TYPE_DEFINE_H

#include <string>

namespace http
{
	namespace tools
	{
		class HeaderTypeDefine
		{
		public:
			HeaderTypeDefine() = delete;

			static bool is_header_general(const char* field_name);
			static bool is_header_general(const std::string& field_name);

			static bool is_header_entity(const char* field_name);
			static bool is_header_entity(const std::string& field_name);

			static bool is_header_request(const char* field_name);
			static bool is_header_request(const std::string& field_name);

			static bool is_header_response(const char* field_name);
			static bool is_header_response(const std::string& field_name);
		};
	};
};

#endif

#include "header_type_define.h"
#include <cstring>
#include <cctype>

using namespace http::tools;

bool HeaderTypeDefine::is_header_general(const char* field_name)
{
	return (
		!strcmp(field_name, "date") ||
		!strcmp(field_name, "pragma")
	);
}

bool HeaderTypeDefine::is_header_general(const std::string& field_name)
{
	return is_header_general(field_name.c_str());
}


bool HeaderTypeDefine::is_header_entity(const char* field_name)
{
	return (
		!strcmp(field_name, "allow") ||
		!strcmp(field_name, "content-encoding") ||
		!strcmp(field_name, "content-length") ||
		!strcmp(field_name, "content-type") ||
		!strcmp(field_name, "expires") ||
		!strcmp(field_name, "last-modified")
	);
}

bool HeaderTypeDefine::is_header_entity(const std::string& field_name)
{
	return is_header_entity(field_name.c_str());
}


bool HeaderTypeDefine::is_header_request(const char* field_name)
{
	return (
		!strcmp(field_name, "authorization" ) ||
		!strcmp(field_name, "from") ||
		!strcmp(field_name, "if-modified-since") ||
		!strcmp(field_name, "referer") ||
		!strcmp(field_name, "user-agent")
	);
}

bool HeaderTypeDefine::is_header_request(const std::string& field_name)
{
	return is_header_request(field_name.c_str());
}


bool HeaderTypeDefine::is_header_response(const char* field_name)
{
	return (
		!strcmp(field_name, "location") ||
		!strcmp(field_name, "server") ||
		!strcmp(field_name, "www-authenticate")
	);
}

bool HeaderTypeDefine::is_header_response(const std::string& field_name)
{
	return is_header_response(field_name.c_str());
}


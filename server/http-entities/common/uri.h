#ifndef HTTP_ENTITIES_COMMON_URI_H
#define HTTP_ENTITIES_COMMON_URI_H

#include <string>

namespace http
{
	class Uri
	{
	public:
		Uri(const char* uri);

		const std::string& get_protocol() const;
		const std::string& get_host() const;
		const int get_port() const;
		const std::string& get_resource_path() const;
		const std::string& get_query() const;
		const std::string& get_fragment() const;

		const std::string& get() const;
	protected:
		void parse(char* uri);
		void parse_protocol(char** resource);
		void parse_host(char** resource);
		void parse_path(char** resource);
		void parse_query(char** resource);
		void parse_fragment(char** resource);

		std::string protocol_;
		std::string host_;
		int port_;
		std::string resource_path_;
		std::string query_;
		std::string fragment_;

		std::string full_uri_;
	};
};

#endif

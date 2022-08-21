#include "uri.h"
#include <cstring>
#include <cstdlib>

using namespace http;

Uri::Uri(const char* uri)
{
	full_uri_ = uri;

	char* mod_uri = new char[strlen(uri) + 1];
	mod_uri[strlen(uri)] = '\0';
	strncpy(mod_uri, uri, strlen(uri));

	parse(mod_uri);
	if (!resource_path_.size())
		resource_path_ = "/";

	delete[] mod_uri;
}

const std::string& Uri::get_protocol() const
{
	return protocol_;
}

const std::string& Uri::get_host() const
{
	return host_;
}

const int Uri::get_port() const
{
	return port_;
}

const std::string& Uri::get_resource_path() const
{
	return resource_path_;
}

const std::string& Uri::get_query() const
{
	return query_;
}

const std::string& Uri::get_fragment() const
{
	return fragment_;
}

const std::string& Uri::get() const
{
	return full_uri_;
}

void Uri::parse(char* uri)
{
	parse_protocol(&uri);
	parse_host(&uri);
	parse_path(&uri);
	parse_query(&uri);
	parse_fragment(&uri);
}

void Uri::parse_protocol(char** resource)
{
	if (!resource || !*resource)
		return;

	char* double_slash = strstr(*resource, "//");
	if (double_slash && *resource != double_slash)
	{
		*(double_slash - 1) = '\0';
		protocol_ = *resource;
		*resource = double_slash;
	}
}

void Uri::parse_host(char** resource)
{
	if (!resource || !*resource)
		return;

	char* double_slash = strstr(*resource, "//");
	if (double_slash)
	{
		*resource += 2;
		char* path = strpbrk(*resource, "/");
		if (path)
			*path = '\0';
		char* port = strpbrk(*resource, ":");
		if (port)
		{
			*(port++) = '\0';
			port_ = atoi(port);
		}
		host_ = *resource;
		if (path)
			*path = '/';
		*resource = path;
	}
}

void Uri::parse_path(char** resource)
{
	if (!resource || !*resource)
		return;

	char* q = strpbrk(*resource, "?#");
	if (q)
	{
		char prev_sym = *q;
		*q = '\0';
		resource_path_ = *resource;
		*q = prev_sym;
	} else
		resource_path_ = *resource;
	*resource = q;
}

void Uri::parse_query(char** resource)
{
	if (!resource || !*resource)
		return;

	if (**resource != '?')
		return;
	++(*resource);

	char* sharp = strpbrk(*resource, "#");
	if (sharp)
	{
		*sharp = '\0';
		query_ = *resource;
		*sharp = '#';
	} else
		query_ = *resource;
	*resource = sharp;
}

void Uri::parse_fragment(char** resource)
{
	if (!resource || !*resource)
		return;

	fragment_ = ++(*resource);
}

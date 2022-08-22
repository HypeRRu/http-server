#include "http_version.h"
#include <cstring>
#include <cstdlib>

using namespace http;

void HttpVersion::parse_string(const char* version)
{
	if (!version)
		return;

	if (strstr(version, "HTTP/") != version)
		return;

	version += 5;
	version_ = atof(version);
}

HttpVersion::HttpVersion(const char* version):
	version_{0},
	major_{0},
	minor_{0}
{
	parse_string(version);
	init_version();
}

HttpVersion::HttpVersion(float version):
	version_{version}
{
	init_version();
}

void HttpVersion::update(const char* version)
{
	parse_string(version);
	init_version();
}

void HttpVersion::update(float version)
{
	version_ = version;
	init_version();
}

void HttpVersion::init_version()
{
	major_ = static_cast<int>(version_);
	float rem = version_ - major_;
	if (rem != 0)
	{
		while (rem < 1)
			rem *= 10;
	}
	minor_ = static_cast<int>(rem);
}

const float HttpVersion::get() const
{
	return version_;
}

const int HttpVersion::major() const
{
	return major_;
}

const int HttpVersion::minor() const
{
	return minor_;
}

#ifndef HTTP_ENTITIES_COMMON_HTTP_VERSION_H
#define HTTP_ENTITIES_COMMON_HTTP_VERSION_H

#include <string>

namespace http
{
	class HttpVersion
	{
	public:
		HttpVersion(const std::string& version);
		HttpVersion(const float version);

		const float get() const;
		const int major() const;
		const int minor() const;
	protected:
		float version_;
	};
};

#endif

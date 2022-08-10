#ifndef HTTP_ENTITIES_COMMON_URI_H
#define HTTP_ENTITIES_COMMON_URI_H

#include <string>

namespace http
{
	class Uri
	{
	public:
		Uri(const std::string& uri);

		const std::string& get() const;
	protected:
		std::string resource_location_;
	};
};

#endif

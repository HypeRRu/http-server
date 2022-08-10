#ifndef HTTP_ENTITIES_COMMON_METHOD_H
#define HTTP_ENTITIES_COMMON_METHOD_H

#include <string>

namespace http
{
	class Method
	{
	public:
		Method(const std::string& m);
		const std::string& get() const;
	protected:
		std::string method_;
	};
};

#endif

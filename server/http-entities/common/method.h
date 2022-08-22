#ifndef HTTP_ENTITIES_COMMON_METHOD_H
#define HTTP_ENTITIES_COMMON_METHOD_H

#include <string>

namespace http
{
	enum class HttpMethod
	{
		GET,
		HEAD,
		POST,
		/*PUT,
		DELETE,
		LINK,
		UNLINK,*/
		UNSUPPORTED
	};

	class Method
	{
	public:
		Method(const char* m);

		const std::string& get_name() const;
		HttpMethod get() const;
	protected:
		std::string method_name_;
		HttpMethod method_;
	};
};

#endif

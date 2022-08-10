#ifndef HTTP_ENTITIES_COMMON_HTTP_VERSION_H
#define HTTP_ENTITIES_COMMON_HTTP_VERSION_H

namespace http
{
	class HttpVersion
	{
	public:
		HttpVersion(const char* version);
		HttpVersion(const float version);

		const float get() const;
		const int major() const;
		const int minor() const;
	protected:
		void init_version();

		float version_;
		int major_;
		int minor_;
	};
};

#endif

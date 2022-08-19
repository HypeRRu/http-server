#ifndef HTTP_ENTITIES_COMMON_HTTP_VERSION_H
#define HTTP_ENTITIES_COMMON_HTTP_VERSION_H

namespace http
{
	class HttpVersion
	{
	public:
		HttpVersion(const char* version);
		HttpVersion(float version = 1.0);

		void update(const char* version);
		void update(float version);

		const float get() const;
		const int major() const;
		const int minor() const;
	protected:
		void parse_string(const char* version);
		void init_version();

		float version_;
		int major_;
		int minor_;
	};
};

#endif

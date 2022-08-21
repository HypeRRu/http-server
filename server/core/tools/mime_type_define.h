#ifndef CORE_TOOLS_MIME_TYPE_DEFINE
#define CORE_TOOLS_MIME_TYPE_DEFINE

#include <string>
#include <map>

namespace core
{
	namespace tools
	{
		class MimeTypeDefine
		{
		public:
			static std::string mime_from_extension(
				const std::string& extension
			);
			static std::string extension_from_mime(
				const std::string& mime_type
			);
		protected:
			static std::map<std::string, std::string> mfe_;
			static std::map<std::string, std::string> efm_;
		};
	};
};

#endif

#include "mime_type_define.h"

using namespace core::tools;

std::string MimeTypeDefine::mime_from_extension(
	const std::string& extension
)
{
	auto mime = mfe_.find(extension);
	if (mime == mfe_.end())
		return "application/octet-stream";
	return mime->second;
}

std::string MimeTypeDefine::extension_from_mime(
	const std::string& mime_type
)
{
	auto extension = efm_.find(mime_type);
	if (extension == efm_.end())
		return "bin";
	return extension->second;
}

std::map<std::string, std::string> MimeTypeDefine::mfe_ = {
	{ "aac", "audio/aac" },
	{ "abw", "application/x-abiword" },
	{ "arc", "application/x-freearc" },
	{ "avi", "video/x-msvideo" },
	{ "azw", "application/vnd.amazon.ebook" },
	{ "bin", "application/octet-stream" },
	{ "bmp", "image/bmp" },
	{ "bz", "application/x-bzip" },
	{ "bz2", "application/x-bzip2" },
	{ "csh", "application/x-csh" },
	{ "css", "text/css" },
	{ "csv", "text/csv" },
	{ "doc", "application/msword" },
	{ "docx", "application/vnd.openxmlformats-officedocument.wordprocessingml.document" },
	{ "eot", "application/vnd.ms-fontobject" },
	{ "epub", "application/epub+zip" },
	{ "gz", "application/gzip" },
	{ "gif", "image/gif" },
	{ "htm", "text/html" },
	{ "html", "text/html" },
	{ "ico", "image/vnd.microsoft.icon" },
	{ "ics", "text/calendar" },
	{ "jar", "application/java-archive" },
	{ "jpeg", "image/jpeg" },
	{ "jpg", "image/jpeg" },
	{ "js", "text/javascript" },
	{ "json", "application/json" },
	{ "jsonld", "application/ld+json" },
	{ "mid", "audio/midi" },
	{ "midi", "audio/midi" },
	{ "mjs", "text/javascript" },
	{ "mp3", "audio/mpeg" },
	{ "mpeg", "video/mpeg" },
	{ "mpkg", "application/vnd.apple.installer+xml" },
	{ "odp", "application/vnd.oasis.opendocument.presentation" },
	{ "ods", "application/vnd.oasis.opendocument.spreadsheet" },
	{ "odt", "application/vnd.oasis.opendocument.text" },
	{ "oga", "audio/ogg" },
	{ "ogv", "video/ogg" },
	{ "ogx", "application/ogg" },
	{ "opus", "audio/opus" },
	{ "otf", "font/otf" },
	{ "png", "image/png" },
	{ "pdf", "application/pdf" },
	{ "php", "application/x-httpd-php" },
	{ "ppt", "application/vnd.ms-powerpoint" },
	{ "pptx", "application/vnd.openxmlformats-officedocument.presentationml.presentation" },
	{ "rar", "application/vnd.rar" },
	{ "rtf", "application/rtf" },
	{ "sh", "application/x-sh" },
	{ "svg", "image/svg+xml" },
	{ "swf", "application/x-shockwave-flash" },
	{ "tar", "application/x-tar" },
	{ "tif", "image/tiff" },
	{ "tiff", "image/tiff" },
	{ "ts", "video/mp2t" },
	{ "ttf", "font/ttf" },
	{ "txt", "text/plain" },
	{ "vsd", "application/vnd.visio" },
	{ "wav", "audio/wav" },
	{ "weba", "audio/webm" },
	{ "webm", "video/webm" },
	{ "webp", "image/webp" },
	{ "woff", "font/woff" },
	{ "woff2", "font/woff2" },
	{ "xhtml", "application/xhtml+xml" },
	{ "xls", "application/vnd.ms-excel" },
	{ "xlsx", "application/vnd.openxmlformats-officedocument.spreadsheetml.sheet" },
	{ "xml", "application/xml" },
	{ "xul", "application/vnd.mozilla.xul+xml" },
	{ "zip", "application/zip" },
	{ "3gp", "video/3gpp" },
	{ "3g2", "video/3gpp2" },
	{ "7z", "application/x-7z-compressed" }
};

std::map<std::string, std::string> MimeTypeDefine::efm_ = {
	{ "audio/aac", "aac" },
	{ "application/x-abiword", "abw" },
	{ "application/x-freearc", "arc" },
	{ "video/x-msvideo", "avi" },
	{ "application/vnd.amazon.ebook", "azw" },
	{ "application/octet-stream", "bin" },
	{ "image/bmp", "bmp" },
	{ "application/x-bzip", "bz" },
	{ "application/x-bzip2", "bz2" },
	{ "application/x-csh", "csh" },
	{ "text/css", "css" },
	{ "text/csv", "csv" },
	{ "application/msword", "doc" },
	{ "application/vnd.openxmlformats-officedocument.wordprocessingml.document", "docx" },
	{ "application/vnd.ms-fontobject", "eot" },
	{ "application/epub+zip", "epub" },
	{ "application/gzip", "gz" },
	{ "image/gif", "gif" },
	{ "text/html", "htm" },
	{ "text/html", "html" },
	{ "image/vnd.microsoft.icon", "ico" },
	{ "text/calendar", "ics" },
	{ "application/java-archive", "jar" },
	{ "image/jpeg", "jpeg" },
	{ "image/jpeg", "jpg" },
	{ "text/javascript", "js" },
	{ "application/json", "json" },
	{ "application/ld+json", "jsonld" },
	{ "audio/midi", "mid" },
	{ "audio/midi", "midi" },
	{ "text/javascript", "mjs" },
	{ "audio/mpeg", "mp3" },
	{ "video/mpeg", "mpeg" },
	{ "application/vnd.apple.installer+xml", "mpkg" },
	{ "application/vnd.oasis.opendocument.presentation", "odp" },
	{ "application/vnd.oasis.opendocument.spreadsheet", "ods" },
	{ "odt", "application/vnd.oasis.opendocument.text" },
	{ "audio/ogg", "oga" },
	{ "video/ogg", "ogv" },
	{ "application/ogg", "ogx" },
	{ "audio/opus", "opus" },
	{ "font/otf", "otf" },
	{ "image/png", "png" },
	{ "application/pdf", "pdf" },
	{ "application/x-httpd-php", "php" },
	{ "application/vnd.ms-powerpoint", "ppt" },
	{ "application/vnd.openxmlformats-officedocument.presentationml.presentation", "pptx" },
	{ "application/vnd.rar", "rar" },
	{ "application/rtf", "rtf" },
	{ "application/x-sh", "sh" },
	{ "image/svg+xml", "svg" },
	{ "application/x-shockwave-flash", "swf" },
	{ "application/x-tar", "tar" },
	{ "image/tiff", "tif" },
	{ "image/tiff", "tiff" },
	{ "video/mp2t", "ts" },
	{ "font/ttf", "ttf" },
	{ "text/plain", "txt" },
	{ "application/vnd.visio", "vsd" },
	{ "audio/wav", "wav" },
	{ "audio/webm", "weba" },
	{ "video/webm", "webm" },
	{ "image/webp", "webp" },
	{ "font/woff", "woff" },
	{ "woff2", "font/woff2" },
	{ "application/xhtml+xml", "xhtml" },
	{ "application/vnd.ms-excel", "xls" },
	{ "application/vnd.openxmlformats-officedocument.spreadsheetml.sheet", "xlsx" },
	{ "application/xml", "xml" },
	{ "application/vnd.mozilla.xul+xml", "xul" },
	{ "application/zip", "zip" },
	{ "video/3gpp", "3gp" },
	{ "video/3gpp2", "3g2" },
	{ "application/x-7z-compressed", "7z" }
};
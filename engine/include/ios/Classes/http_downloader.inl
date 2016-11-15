#ifndef _HTTP_DOWNLOADER_INL_
#define _HTTP_DOWNLOADER_INL_

HttpDownloader::Headers::Headers(HttpDownloader::Headers::HeadersImpl *impl_)
	: impl(impl_)
{}

std::string HttpDownloader::Headers::GetHeader(const std::string &name) const
{
	Assert(impl.get());
	return impl->GetHeader(name);
}

HttpDownloader::HttpDownloader()
	: impl(new DownloaderImpl)
{}

HttpDownloader::~HttpDownloader()
{
	Assert(impl.get());
}

void HttpDownloader::DownloadFile(const std::string &url, const HttpDownloader::DownloadCompleteCallback &callback)
{
	Assert(impl.get());
	impl->DownloadFile(url, callback, HttpNativePreprocessCallback());
}

void HttpDownloader::DownloadFileWithNativePreprocess(const std::string &url, const HttpDownloader::DownloadCompleteCallback &callback,
		const HttpNativePreprocessCallback &nativePreprocess)
{
	Assert(impl.get());
	impl->DownloadFile(url, callback, nativePreprocess);
}

void HttpDownloader::SetTimeout(int seconds)
{
	Assert(impl.get());
	impl->SetTimeout(seconds);
}

void HttpDownloader::UseCache(bool use)
{
	Assert(impl.get());
	impl->UseCache(use);
}

void HttpDownloader::CatchRedirection(bool catchRedirection)
{
#ifdef ENGINE_TARGET_ANDROID
	Assert(impl.get());
	impl->CatchRedirection(catchRedirection);
#endif
}

#endif /* _HTTP_DOWNLOADER_INL_ */

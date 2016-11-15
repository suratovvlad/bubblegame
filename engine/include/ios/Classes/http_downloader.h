#ifndef _IOS_HTTP_DOWNLOADER_H_
#define _IOS_HTTP_DOWNLOADER_H_

#include <string>
#include <map>
#include <boost/function.hpp>
#include <boost/noncopyable.hpp>

#ifdef __OBJC__
typedef boost::function< NSData* (NSData *data) > HttpNativePreprocessCallback;
	// вызывается при успешном скачивании файла (status==200), до вызова DownloadCompleteCallback
	// принимает скачанные данные, возвращает обработанные или nil, если есть какие-то ошибки
	// например, так проще трансформировать картинки с фейсбука к одному формату
	// !!! выполняется в фоновом потоке, может понадобиться отдельная синхронизация (RunInMainThread и т.д.)
#endif

class HttpDownloader
	: private boost::noncopyable
{
public:

	class DownloaderImpl;

	class Headers
		: private boost::noncopyable
	{
	public:

		std::string GetHeader(const std::string &name) const;

	private:

		friend class DownloaderImpl;

		class HeadersImpl;

		Headers(HeadersImpl *impl);

		std::unique_ptr<HeadersImpl> impl;

	};

	typedef boost::function< void(int httpStatus, const std::vector<uint8_t> &data, const Headers &headers) > DownloadCompleteCallback;
		// httpStatus == 200 - все скачалось
		// httpStatus == -1 - проблемы с подключением к серверу (нет интернета, таймаут, выключен сервер, что-то отключено или не настроено и т.д.)
		// httpStatus == 2xx, 3xx, 4xx, 5xx - код ответа сервера
		// !!! выполняется в фоновом потоке, может понадобиться отдельная синхронизация (RunInMainThread и т.д.)

	HttpDownloader();

	~HttpDownloader();

	void DownloadFile(const std::string &url, const DownloadCompleteCallback &callback);

#if defined(__OBJC__) || defined(ENGINE_TARGET_ANDROID)
	void DownloadFileWithNativePreprocess(const std::string &url, const DownloadCompleteCallback &callback,
			const HttpNativePreprocessCallback &nativePreprocess);
#endif

	void SetTimeout(int seconds);

	void UseCache(bool use);
	// при подключении к одному адресу может быть переадресация на другой (статус подключения при этом 302 (HTTP_MOVED_TEMP))
	// чтобы все таки загрузить изображение нужно это ловить
	// для загрузки аватарок с facebook`а идет переадресация на другой адрес
	void CatchRedirection(bool catchRedirection);
private:

	std::unique_ptr<DownloaderImpl> impl;

};

#endif /* _IOS_HTTP_DOWNLOADER_H_ */
